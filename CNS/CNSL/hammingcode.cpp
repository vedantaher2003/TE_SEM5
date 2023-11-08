#include <bits/stdc++.h>
using namespace std;

char generate_parity_1(string bin, int n)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (bin[i] == '1')
        {
            counter++;
        }
    }
    if (counter % 2 == 0)
    {
        return '0';
    }
    else
    {
        return '1';
    }
}

char generate_parity(char bin[], int n)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (bin[i] == '1')
        {
            counter++;
        }
    }
    if (counter % 2 == 0)
    {
        return '0';
    }
    else
    {
        return '1';
    }
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitly, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

int main()
{
    string s;
    cout << "Enter a String :" << endl;
    cin >> s;

    char p1, p2, p4, p8, hamming[11], p1_a[5], p2_a[5], p4_a[3], p8_a[3];
    for (int i = 0; i < s.length(); i++)
    {
        int c_ascii = int(s[i]);
        char bin[7];
        char bin_cpy[7];
        cout << "Character:" << s[i] << endl;
        cout << "Decimal:" << c_ascii << endl;
        cout << "Binary:";
        itoa(c_ascii, bin, 2);
        // bin_cpy[0]='0';
        int counter = 0;
        for (int i = 0; i <= 7; i++)
        {
            bin_cpy[i] = bin[counter];
            counter++;
        }
        for (int i = 0; i < 7; i++)
        {
            cout << bin_cpy[i];
        }

        cout << endl;

        // b0 b1 b2 b3 b4 b5 b6
        // d3 d5 d6 d7 d9 d10 d11

        // p1: p1:: d3 d5 d7 d9 d11
        // p2: p2:: d3 d6 d7 d10 d11
        // p4: p4:: d5 d6 d7
        // p8: p8:: d9 d10 d11

        for (int i = 0; i < 5; i++)
        {
            if (i == 0)
            {
                p1_a[i] = bin_cpy[0];
                p2_a[i] = bin_cpy[0];
                p4_a[i] = bin_cpy[1];
                p8_a[i] = bin_cpy[4];
            }
            else if (i == 1)
            {
                p1_a[i] = bin_cpy[1];
                p2_a[i] = bin_cpy[2];
                p4_a[i] = bin_cpy[2];
                p8_a[i] = bin_cpy[5];
            }
            else if (i == 2)
            {
                p1_a[i] = bin_cpy[3];
                p2_a[i] = bin_cpy[3];
                p4_a[i] = bin_cpy[3];
                p8_a[i] = bin_cpy[6];
            }
            else if (i == 3)
            {
                p1_a[i] = bin_cpy[4];
                p2_a[i] = bin_cpy[5];
            }
            else
            {
                p1_a[i] = bin_cpy[6];
                p2_a[i] = bin_cpy[6];
            }
        }

        // for (int i = 0; i < 5; i++)
        // {
        //     cout<<p1_a[i];
        // }
        // cout<<endl;
        // for (int i = 0; i < 5; i++)
        // {
        //     cout<<p2_a[i];
        // }
        // cout<<endl;
        // for (int i = 0; i < 3; i++)
        // {
        //     cout<<p4_a[i];
        // }
        // cout<<endl;
        // for (int i = 0; i < 3; i++)
        // {
        //     cout<<p8_a[i];
        // }
        // cout<<endl;

        p1 = generate_parity(p1_a, 5);
        p2 = generate_parity(p2_a, 5);
        p4 = generate_parity(p4_a, 3);
        p8 = generate_parity(p8_a, 3);

        hamming[0] = p1;
        hamming[1] = p2;
        int counter1 = 0;
        for (int i = 2; i < 11; i++)
        {
            if (i == 3)
            {
                hamming[i] = p4;
            }
            else if (i == 7)
            {
                hamming[i] = p8;
            }
            else
            {
                hamming[i] = bin_cpy[counter1];
                counter1++;
            }
        }

        cout << endl;
        cout << "p1:" << p1 << endl;
        cout << "p2:" << p2 << endl;
        cout << "p4:" << p4 << endl;
        cout << "p8:" << p8 << endl;
        cout << "Do you want to corrupt the data word ? (y/n)" << endl;
        char ch;
        bool flag;
        cin >> ch;
        if (ch == 'y')
        {
            flag = true;
            cout << "Enter the bit position to corrupt:" << endl;
            int pos;
            cin >> pos;
            if (hamming[pos - 1] == '1')
            {
                hamming[pos - 1] = '0';
            }
            else
            {
                hamming[pos - 1] = '1';
            }
            cout << "Corrupted Code Word: ";
            for (int i = 0; i < 11; i++)
            {
                cout << hamming[i];
            }
            cout << endl;
        }
        else
        {
            flag = false;
            cout << "Uncorrupted Code Word:";
            for (int i = 0; i < 11; i++)
            {
                cout << hamming[i];
            }
        }
        cout << endl;

        cout << "RECEIVER SIDE" << endl;
        string p1_check = "";
        string p2_check = "";
        string p4_check = "";
        string p8_check = "";
        p1_check = p1_check + hamming[0] + hamming[2] + hamming[4] + hamming[6] + hamming[8] + hamming[10]; // 0 2 4 6 8 10
        // cout<<p1_check<<endl;
        p2_check = p2_check + hamming[1] + hamming[2] + hamming[5] + hamming[6] + hamming[9] + hamming[10]; // 1 2 5 6 9 10
        // cout<<p2_check<<endl;

        p4_check = p4_check + hamming[3] + hamming[4] + hamming[5] + hamming[6]; // 3 4 5 6
        // cout<<p4_check<<endl;

        p8_check = p8_check + hamming[7] + hamming[8] + hamming[9] + hamming[10]; // 7 8 9 10
        // cout<<p8_check<<endl;

        char p1_rec = generate_parity_1(p1_check, 6);
        char p2_rec = generate_parity_1(p2_check, 6);
        char p4_rec = generate_parity_1(p4_check, 4);
        char p8_rec = generate_parity_1(p8_check, 4);

        cout << "p1:" << p1_rec << endl;
        cout << "p2:" << p2_rec << endl;
        cout << "p4:" << p4_rec << endl;
        cout << "p8:" << p8_rec << endl;

        string pos = "";
        pos = pos + p8_rec + p4_rec + p2_rec + p1_rec;

        int pos_no = stoi(pos, nullptr, 2);
        cout << pos_no << endl;
       
        if(flag == true)
        {
            if (hamming[pos_no - 1] == '1')
            {
                hamming[pos_no - 1] = '0';
            }
            else
            {
                hamming[pos_no - 1] = '1';
            }
            cout<<"Corrected Code Word is : ";
            for(int k = 0; k <= 11; k++)
            {
                cout<<hamming[k];
            }
        }
       
        cout<<endl<<"Data Word : ";
        for(int k = 0; k <= i; k++)
        {
            cout<<s[k];
        }
        cout<<endl<<"========================="<<endl;
    }

    return 0;
}