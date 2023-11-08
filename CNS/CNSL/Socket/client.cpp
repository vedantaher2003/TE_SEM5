#include <bits/stdc++.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;

void gbn(int);
void sr(int);

struct msg {
	char data;
	int sequence_number;
};

struct rmsg {
	bool isAck;
	int sequence_number;
};

int main() {
	cout<<"--------------CLIENT SIDE--------------"<<endl;
	int cfd;
	cfd = socket(AF_INET,SOCK_STREAM, 0);
	if (cfd == -1) {
		cout << "socket not created" << endl;;
		exit(1);
	}

	struct sockaddr_in my_addr,peer_addr;

	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(0);
	inet_aton("127.0.0.1",&my_addr.sin_addr);


	memset(&peer_addr, 0, sizeof(struct sockaddr_in));
	peer_addr.sin_family = AF_INET;
	peer_addr.sin_port = htons(8080);
	inet_aton("127.0.0.1", &peer_addr.sin_addr);

	// my_addr.sin_addr=(in_addr)INADDR_LOOPBACK;
	if (bind(cfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) == -1) {
		cout << "error in binding" << endl;
		exit(errno);
	}

	if (connect(cfd, (struct sockaddr *) &peer_addr, sizeof(peer_addr)) == -1) {
		cout << "error in connecting" << endl;
		exit(errno);
	}

	cout << "Connected to the server! (127.0.0.1)" << endl;
	int choice = 0;
	cout << "Sliding Window Protocols: \n1.GO Back N\n2.Selective Repeat"<<endl;
	cout << "Enter your choice : ";
	cin >> choice;
	if (choice == 1) {
		gbn(cfd);
	}
	else if (choice == 2) {
		sr(cfd);
	}

	return 0;
}


int m;
int min_seq_num = 0;
int max_seq_num;
int current_sequence_number = min_seq_num;
int acknowledgement_remaining = min_seq_num;
int size_of_sliding_window;
int maximum_sequence_number;
int acknowledgedDataIndex = -1;
mutex m1;


void sendFramesGBN(int cfd, string data) {
	unique_lock<mutex> l(m1,defer_lock);
	int dataIndex = 0;
	bool flagDataSent = false;
	while (true) {	
		for (int i = 0; i < size_of_sliding_window - 1 ; i++) {
			if (dataIndex >= data.size()) {
				flagDataSent = true;
				break;
			}
			cout << "Sending frame " << data[dataIndex] << " with sequence number " << current_sequence_number << endl;
			l.lock();
			msg m1 = msg {data[dataIndex++], current_sequence_number};
			send(cfd, &m1, sizeof(m1), 0);
			current_sequence_number = (current_sequence_number + 1) % (size_of_sliding_window + 1);
			l.unlock();
			cout << "Frame sent" << endl;
			this_thread::sleep_for(chrono::seconds(1));
		}
		l.lock();
		if (acknowledgement_remaining != current_sequence_number) {
			cout << "Waiting for acknowledgement for frame number " << acknowledgement_remaining << endl;
			cout << "waiting for 3 seconds" << endl;
			this_thread::sleep_for(chrono::seconds(3));
			if (acknowledgement_remaining != current_sequence_number) {
				cout << "resending frames, starting from frame number " << acknowledgement_remaining << endl;
				dataIndex = acknowledgedDataIndex+1;
				flagDataSent = false;
				current_sequence_number = acknowledgement_remaining;	
			}
		} else if (flagDataSent) {
			// close(cfd);
			exit(0);
		}
		l.unlock();
	}
	cout<<endl;
}


bool check(int a, int b, int c) {
	if (a < b) {
		if (a < c && c < b) return true;
		else return false;
	} else { 
		// b < a
		 if (b < c && c < a) return false;   // if in [b, a] then not in [a, b]
	  else return true;
	}

}

void recvAcksGBN(int cfd) {
	unique_lock<mutex> l(m1,defer_lock);
	struct timeval tv;
	fd_set cfds;
	FD_ZERO(&cfds);
	FD_SET(cfd, &cfds);
	tv.tv_sec = 1;

	while (true) {
		int ack;	
		recv(cfd, &ack, sizeof(int), 0);
		cout << "acknowledgment received, requesting number " << ack << endl;
		//cout << "->" << min_seq_num << " " << maximum_sequence_number << endl;
		if (check(min_seq_num, maximum_sequence_number, ack)) {
			l.lock();
			acknowledgedDataIndex++;
			int number_of_frames_acknowledged = abs(ack - acknowledgement_remaining) % (size_of_sliding_window-1);
			acknowledgement_remaining = ack;
			//cout << "acknowledgement_remaining changed to " << acknowledgement_remaining << endl;
			min_seq_num = ack;
			maximum_sequence_number = (maximum_sequence_number + number_of_frames_acknowledged) % (size_of_sliding_window + 1);
			l.unlock();
		}
	}
	cout<<endl;
}


void gbn(int cfd) {
	cout << "Enter the size of bit sequence (m): " ;
	cin >> m;
	max_seq_num = pow(2,m) - 1;
	size_of_sliding_window = pow(2, m) - 1;
	maximum_sequence_number = current_sequence_number + size_of_sliding_window - 1;
	cout << "Sequence number possible from " << min_seq_num << " to " << max_seq_num << endl;
	cout << "Size of the sliding window is " << size_of_sliding_window << endl;
	cout << "Current Sliding window " << acknowledgement_remaining << " to " << maximum_sequence_number << endl;
	cout << "Enter the data to be sent : ";
	string data;
	cin >> data;
	std::random_device dev;

	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distBin(0,1);					
	// std::cout << distBin(rng) << std::endl;
	thread t2(sendFramesGBN, cfd, data);
	thread t1(recvAcksGBN, cfd);
	t2.join();
	t1.join();
}

vector<pair<int,bool>> receivedAcknowledgments;
vector<char> chars;
int dataIndex = 0;
int dataIndexTemp = 0;


void sendFramesSR(int cfd, string data) {
	unique_lock<mutex> l(m1,defer_lock);
	// int dataIndex = 0;
	bool flagDataSent = false;
	while (true) {
		/*
		receivedAcknowledgments.clear();
		for (int i = min_seq_num; i <= maximum_sequence_number; i++) {
			receivedAcknowledgments.push_back({i,false});
		}
		*/
		for (int i = 0; i < size_of_sliding_window ; i++) {
			if (!receivedAcknowledgments[i].second) {	
				cout << "Sending frame " << chars[current_sequence_number] << " with sequence number " << current_sequence_number << endl;
				l.lock();
				msg m1 = msg {chars[current_sequence_number], current_sequence_number};
				send(cfd, &m1, sizeof(m1), 0);
				current_sequence_number = (current_sequence_number + 1) % (max_seq_num + 1);
				l.unlock();
				cout << "Frame sent" << endl;
				this_thread::sleep_for(chrono::seconds(1));
				if (dataIndexTemp == data.size()+size_of_sliding_window) {
					flagDataSent = true;
					break;
				}
			}
		}

		if (flagDataSent) {
			exit(0);
		}
		bool allNotReceived = true;
		for (int i = 0; i < receivedAcknowledgments.size(); i++) {
			if (receivedAcknowledgments[i].second) {
				allNotReceived = false;
				break;
			}
		}
		l.lock();
		if (!allNotReceived) {
			for (int i = 0; i < receivedAcknowledgments.size(); i++) {
				if (!receivedAcknowledgments[i].second) {
					cout << "Waiting for acknowledgement for frame having sequence number " << receivedAcknowledgments[i].first << endl;
					cout << "waiting for 3 seconds" << endl;
					this_thread::sleep_for(chrono::seconds(3));
					if (!receivedAcknowledgments[i].second) {
						cout << "resending frames, starting from frame number " << receivedAcknowledgments[i].first << endl;
						dataIndex = acknowledgedDataIndex+1;
						flagDataSent = false;
						current_sequence_number = receivedAcknowledgments[i].first;
						break;
					}
				} 
			}
		}
		cout<<endl;
		l.unlock();

	}
}

void recvAcksSR(int cfd, string data) {
	unique_lock<mutex> l(m1,defer_lock);
	struct timeval tv;
	fd_set cfds;
	FD_ZERO(&cfds);
	FD_SET(cfd, &cfds);
	tv.tv_sec = 1;

	while (true) {
		rmsg ack;
		recv(cfd, &ack, sizeof(ack), 0);
		// cout << "acknowledgment received, requesting frame having sequence number " << ack << endl;
		// cout << "->" << min_seq_num << " " << maximum_sequence_number << endl;

		if (ack.isAck) {
			cout << "Acknowledgement Received " << ack.sequence_number << endl;
			l.lock();
			/*
			cout << "Before :: " << endl;
			for (int i = 0; i < receivedAcknowledgments.size(); i++) {
				cout << receivedAcknowledgments[i].first << " ";
			}
			cout << endl;	
			*/
			for (int i = 0; i < receivedAcknowledgments.size(); i++) {
				// cout << "comparing " << receivedAcknowledgments[i].first << " with " << ack.sequence_number << endl;
				if (receivedAcknowledgments[i].first == ack.sequence_number) {
					break;
				}
				// cout << "deleting " << (receivedAcknowledgments.begin()+i)->first << endl;
				receivedAcknowledgments.erase(receivedAcknowledgments.begin() + i);
				maximum_sequence_number = (maximum_sequence_number + 1) % (max_seq_num + 1);
				if (dataIndex+1 <= data.size()) {
					chars[maximum_sequence_number] = data[dataIndex++];
				}
				dataIndexTemp++;
				if (dataIndex == data.size()+size_of_sliding_window) {
					dataIndex = dataIndex-1;
				}
				// dataIndex = (dataIndex + 1) % data.size();
				// cout << "dataIndex =" << data[dataIndex] << " " << dataIndex << endl;
				receivedAcknowledgments.push_back({maximum_sequence_number, false});
				// receivedAcknowledgments[i].second = true;
				acknowledgedDataIndex++;
				i--;
			}
			cout << "sliding window shifted : " << endl;
			for (int i = 0; i < receivedAcknowledgments.size(); i++) {
				cout << receivedAcknowledgments[i].first << " ";
			}
			/*
			for (int i = 0; i < receivedAcknowledgments.size(); i++) {
				cout << receivedAcknowledgments[i].second << " ";
			}
			*/
			cout << endl;
			// int number_of_frames_acknowledged = i;
			// acknowledgement_remaining = receivedAcknowledgments[i].first;
			min_seq_num = ack.sequence_number;
			// maximum_sequence_number = (maximum_sequence_number + number_of_frames_acknowledged) % (size_of_sliding_window + 1);
			l.unlock();
		} else {
			cout << "Negaive Acknowledgement Received" << endl;
			l.lock();
			for (int i = 0; i < receivedAcknowledgments.size(); i++) {
				if (ack.sequence_number == receivedAcknowledgments[i].first) {
					receivedAcknowledgments[i].second = false;
				}
			}
			l.unlock();
		}
		
		/*for (int i = min_seq_num; i != maximum_sequence_number; i = (i + 1)%(max_seq_num)) {
			if (receivedAcknowledgments[i].first == (((ack.sequence_number-1)+(max_seq_num))%(max_seq_num))) {
				receivedAcknowledgments[i].second = false;
			}
		}*/
		
	}
	cout<<endl;
}



void sr(int cfd) {
	cout << "Enter the size of bit sequence (m): ";
	cin >> m;
	max_seq_num = pow(2, m) - 1;
	size_of_sliding_window = pow(2, m - 1);
	maximum_sequence_number = current_sequence_number + size_of_sliding_window - 1;
	cout << "Sequence number possible from " << min_seq_num << " to " << max_seq_num << endl;
	cout << "Size of the sliding window is " << size_of_sliding_window << endl;
	cout << "Current Sliding window " << acknowledgement_remaining << " to " << maximum_sequence_number << endl;
	cout << "Enter the data you want to send : ";
	string data;
	vector<char> temp(max_seq_num + 1);
	chars = temp;
	cin >> data;
	dataIndex = 0;
	for (int i = min_seq_num; i <= maximum_sequence_number; i++) {
		chars[i] = data[dataIndex++];
		dataIndexTemp++;
		receivedAcknowledgments.push_back({i,false});
	}
	thread t2(sendFramesSR, cfd, data);
	thread t1(recvAcksSR, cfd, data);
	t2.join();
	t1.join();
}

