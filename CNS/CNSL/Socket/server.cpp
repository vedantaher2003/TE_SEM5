#include <bits/stdc++.h>
#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

void gbn(int);
void sr(int);

int m;
int min_seq_num = 0;
int max_seq_num;

int current_sequence_number = min_seq_num;
int acknowledgement_remaining = min_seq_num;
int size_of_sliding_window;
int maximum_sequence_number;

struct msg {
        char data;
        int sequence_number;
};

struct rmsg {
	bool isAck;
	int sequence_number;
};

int main() {
	cout<<"--------------SERVER SIDE--------------"<<endl;
	int sfd,cfd;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1) {
		cout << "socket not created" << endl;;
		exit(1);
	}
	struct sockaddr_in my_addr,peer_addr;
	memset(&my_addr, 0, sizeof(struct sockaddr_in));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(8080);
	inet_aton("0.0.0.0",&my_addr.sin_addr);
	// my_addr.sin_addr=(in_addr)INADDR_LOOPBACK;
	if (bind(sfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in)) == -1) {
		cout << "error in binding" << endl;
		exit(1);
	}
	if (listen(sfd,50) == -1) {
		cout << "error in listening" << endl;
		exit(1);
	}
	socklen_t peer_addr_size;
	peer_addr_size = sizeof(struct sockaddr_in);
	int choice = 0;
	cout << "Sliding Window Protocols: \n1.GO Back N\n2.Selective Repeat"<<endl;
        cout << "Enter your choice : ";
        cin >> choice;
        if (choice == 1) {
		cout << "Enter the size of bit sequence (m) : " ;
	        cin >> m;
		max_seq_num = pow(2,m) - 1;
		cout << "Sequence number possible from " << min_seq_num << " to " << max_seq_num << endl;
		while (true) {
			cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);	
			cout << cfd <<  " connected ip " << inet_ntoa(peer_addr.sin_addr) << ":" << peer_addr.sin_port << endl;
	                gbn(cfd);
		}

        }
        else if (choice == 2) {
		cout << "Enter the size of bit sequence (m) : ";
		cin >> m;
		max_seq_num = pow(2,m) - 1;
		size_of_sliding_window = pow(2, m - 1);
	        maximum_sequence_number = current_sequence_number + size_of_sliding_window - 1;
		cout << "Sequence number possible from " << min_seq_num << " to " << max_seq_num << endl;
		cout << "Receiver sliding window size : " << size_of_sliding_window << endl;
		cout << "From " << min_seq_num << " to " << maximum_sequence_number << endl;
		while (true) {
			cfd = accept(sfd, (struct sockaddr *) &peer_addr, &peer_addr_size);	
			cout << cfd <<  " connected ip " << inet_ntoa(peer_addr.sin_addr) << ":" << peer_addr.sin_port << endl;
                	sr(cfd);
		}
        }

	return 0;

}


void gbn(int cfd) {
	int expected_sequence_number = min_seq_num;
        std::random_device dev;
 
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distBin(0,1);                                  
	while (true) {
		msg m1;
		int received_sequence_number;
		int res = recv(cfd, &m1, sizeof(m1), 0);
		if (res == 0) {
			break;
			return;
		}
		received_sequence_number = m1.sequence_number;
		cout << "data received : " << m1.data << endl; 
		cout << "received frame number " << received_sequence_number << " while expecting " << expected_sequence_number << endl;
		if (distBin(rng)) {
			cout << "Randomly discarding this frame" << endl;
			continue;
		}
		if (received_sequence_number == expected_sequence_number) {
			cout << "frame received correctly" << endl;
			expected_sequence_number = (expected_sequence_number + 1) % (max_seq_num + 1);
		};
		cout << "requesting for frame number " << expected_sequence_number << endl;
		cout<<endl;
		// this_thread::sleep_for(chrono::seconds(2));
		send(cfd, &expected_sequence_number, sizeof(int), 0);
	}
}

void sr(int cfd) {
	vector<pair<int,bool>> backlog;
	bool nakSent = false;
	for (int i = min_seq_num; i <= maximum_sequence_number; i++) {
		backlog.push_back({i,false});
	}
	std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> distBin(0,1);
	while (true) {
		msg m1;
		int received_sequence_number;
		for (int i = 0; i < backlog.size(); i++) {
			cout << backlog[i].first << " ";
		}
		cout << endl;
		
		int res = recv(cfd, &m1, sizeof(m1), 0);
		if (res == 0) {
			break;
			return;
		}
		received_sequence_number = m1.sequence_number;
		cout << "data received : " << m1.data << endl;
		cout << "received frame number " << received_sequence_number << " while expecting " << backlog.begin()->first << endl;
		if (distBin(rng)) {
			cout << "Randomly discarding this frame" << endl;
			continue;
		}
		for (int i = 0; i < backlog.size(); i++) {
			if (backlog[i].first == received_sequence_number) {
				backlog[i].second = true;
				break;
			}
		}
		if (!nakSent && !backlog.begin()->second) {
			cout << "sending Negative Acknowledgement" << endl;
			int nak = backlog.begin()->first;
			rmsg m1;
			m1.sequence_number = nak;
			m1.isAck = false;
			send(cfd, &m1, sizeof(m1), 0);
			nakSent = true;
		}
		int i = 0;
		while (backlog[i].second) {
			i = (i + 1) % (max_seq_num+1);
		}
//		cout << "--->" << i << endl;
		if (backlog[((i-1) + (max_seq_num + 1)) % (max_seq_num+1)].first == received_sequence_number) {
			cout << "sending Acknowledgement" << endl;
			int ack = (backlog[((i-1) + (max_seq_num + 1)) % (max_seq_num+1)].first + 1) % (max_seq_num + 1);
			rmsg m1;
			m1.sequence_number = ack;
			m1.isAck = true;
			send(cfd, &m1, sizeof(m1), 0);
			for (int i = 0; i < backlog.size(); i++) {
				if (backlog[i].second) {
					backlog.erase(backlog.begin() + i);
					backlog.push_back({(backlog.back().first+1) % (max_seq_num + 1), false});
					i--;
				}
			}
			cout<<endl;
			/*for (int i = ack; i != (ack + size_of_sliding_window) % (size_of_sliding_window); i = (i + 1) % (max_seq_num + 1)) {
				backlog.push_back({i,false});
			}*/
		}
	}
}

