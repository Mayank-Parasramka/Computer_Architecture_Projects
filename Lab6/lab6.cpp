#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <iomanip>
#include <bitset>
#include <time.h> 

using namespace std;

#define SIZE 3000

string CacheTag[SIZE][SIZE];
int FIFO[SIZE];
int Clock[SIZE][SIZE];


int powerof2(int num)
{
    int result = 0;
    while(1)
    {
        if(num == 1)
            break;
        num = num/2;
        result++;
    }
    return result;
}

string hextobin(string& inHex)
{
    stringstream temp;
    temp << hex << inHex;
    unsigned bin;
    temp >> bin;
    bitset<32> b(bin);
    string binary = b.to_string();
    return binary;
}

string bintohex(const string& binary) {
    bitset<32> bits(binary);
    unsigned hex = bits.to_ulong();
    stringstream ss;
    ss << std::hex << hex;
    return ss.str();
}

string allocate(int associativity, string replacement_policy, string Index, string Tag)
{
    int index = stoi(Index, 0, 2);
    // cout<<index<<endl;
    if(replacement_policy[0]=='F')
    {
        for(int j=0; j<associativity; j++)
        {
            if(CacheTag[index][j] == Tag)
            {    
                return "Hit";
            }
            else if(CacheTag[index][j] == "")
            {
                CacheTag[index][j] = Tag;
                return "Miss";
            }
        }
        CacheTag[index][FIFO[index]] = Tag;
        FIFO[index] = (FIFO[index] + associativity +1) % associativity;
        return "Miss";
    }   

    else if(replacement_policy[0]=='R')
    {
        for(int j=0; j<associativity; j++)
        {
            if(CacheTag[index][j] == Tag)
            {    
                return "Hit";
            }
            else if(CacheTag[index][j] == "")
            {
                CacheTag[index][j] = Tag;
                return "Miss";
            }
        }
        srand(time(0));
        int random = rand() % associativity;
        CacheTag[index][random] = Tag;
        return "Miss";
    }

    else if(replacement_policy[0]=='L')
    {
        for(int j=0; j<associativity; j++)
        {
            if(CacheTag[index][j] == Tag)
            {
                Clock[index][j]=0;
                for(int l=0; l<associativity; l++)
                {
                    if(l==j) continue;
                    Clock[index][l]++;
                }    
                return "Hit";
            }
            else if(CacheTag[index][j] == "")
            {
                CacheTag[index][j] = Tag;
                return "Miss";
            }
        }
        int lru=0;
        for(int l=0; l<associativity; l++)
        {
            if(Clock[index][l]>Clock[index][lru])
                lru = l;
        }
        CacheTag[index][lru] = Tag;
        Clock[index][lru] = 0;
        for(int l=0; l<associativity; l++)
        {
            if(l==lru) continue;
            Clock[index][l]++;
        }
        return "Miss";
    }
    return "";
}

string notallocate(int associativity, string replacement_policy, string Index, string Tag)
{
    int index = stoi(Index, 0, 2);
    for(int j=0; j<associativity; j++)
    {
        if(CacheTag[index][j] == Tag)
        {    
            return "Hit";
        }
    }
    return "Miss";
}

int main() 
{
    int cacheSize;
    int blockSize;
    int associativity;
    string replacementPolicy;
    string writePolicy;
    
    fstream input_file;
    input_file.open("cacheconfig.txt", ios::in); 
    string line;
    if (input_file.is_open()) 
    { 
        getline(input_file, line);
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        cacheSize = stoi(line);
        getline(input_file, line);
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        blockSize = stoi(line);
        getline(input_file, line);
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        associativity = stoi(line);
        getline(input_file, line);
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        replacementPolicy = line;
        getline(input_file, line);
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        writePolicy = line;
    }
    else
    {
        cout<< "File not found" << endl;
    }
    input_file.close();
    if(associativity==0)
        associativity = cacheSize/blockSize;
    int number_of_sets = cacheSize/(blockSize*associativity);
    int n = powerof2(number_of_sets);
    int m = powerof2(blockSize);
    string line2;
    string Tag[SIZE];
    string Index[SIZE];
    string Offset[SIZE];
    string Address[SIZE];

    bool IsRead[SIZE];
    int address_count = 0;
    input_file.open("cacheaccess.txt", ios::in); 
    if (input_file.is_open()) 
    { 
        while(!input_file.eof())
        {
            getline(input_file, line2);
            if(line2 == "") continue;
            line2.erase(line2.find_last_not_of(" \n\r\t")+1);
            if(line2[0] == 'R')
                IsRead[address_count] = true;
            else if(line2[0] == 'W')
                IsRead[address_count] = false;
            line2.erase(0, 3);

            Address[address_count] = line2;
            string binary = hextobin(line2);
            Tag[address_count] = binary.substr(0, 32-m-n);
            Index[address_count] = binary.substr(32-m-n, n);
            Offset[address_count] = binary.substr(32-m,m);
            // cout << "tag: " << Tag[address_count] << endl;
            // cout << "index: " << Index[address_count] << endl;
            // cout << "offset: " << Offset[address_count] << endl;
            address_count++;
        }
    }
    else
    {
        cout<< "File not found" << endl;
    }
    input_file.close();
    
    FIFO[SIZE] = {0};
    Clock[SIZE][SIZE] = {0};
    string status[address_count];
    if(n==0)
    {
        for(int i=0; i<address_count; i++)
        {
            Index[i] = "0";
        }
    }
    // int index = stoi(Index[0], 0, 2);
    // cout<<Index[0]<<endl<<index<<endl;
    // cout<<CacheTag<<endl;

    for(int i=0; i<address_count; i++)
    {
        if(IsRead[i] || ((!IsRead[i]) && writePolicy.find("WB")!=-1))
        {
            status[i]= allocate(associativity, replacementPolicy, Index[i], Tag[i]);
            cout<<"Address: "<<Address[i]<<", Set: 0x"<<bintohex(Index[i])<<", "<< status[i]<< ", Tag: 0x"<<bintohex(Tag[i])<<endl; 
        }
        else
        {
            status[i]= notallocate(associativity, replacementPolicy, Index[i], Tag[i]);
            cout<<"Address: "<<Address[i]<<", Set: 0x"<<bintohex(Index[i])<<", "<< status[i]<< ", Tag: 0x"<<bintohex(Tag[i])<<endl; 
        }
    }

    return 0;
}