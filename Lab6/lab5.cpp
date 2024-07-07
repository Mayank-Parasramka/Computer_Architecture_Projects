#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Inscrease the SIZE if the input file has more than 25 lines 
#define SIZE 25

// Function to change the register alias to the standard name
string ChangeRegisterAlias(string reg)
{
    if(reg == "zero") return "x0";
    else if(reg == "ra") return "x1";
    else if(reg == "sp") return "x2";
    else if(reg == "gp") return "x3";
    else if(reg == "tp") return "x4";
    else if(reg == "t0") return "x5";
    else if(reg == "t1") return "x6";
    else if(reg == "t2") return "x7";
    else if(reg == "s0" || reg == "fp") return "x8";
    else if(reg == "s1") return "x9";
    else if(reg == "a0") return "x10";
    else if(reg == "a1") return "x11";
    else if(reg == "a2") return "x12";
    else if(reg == "a3") return "x13";
    else if(reg == "a4") return "x14";
    else if(reg == "a5") return "x15";
    else if(reg == "a6") return "x16";
    else if(reg == "a7") return "x17";
    else if(reg == "s2") return "x18";
    else if(reg == "s3") return "x19";
    else if(reg == "s4") return "x20";
    else if(reg == "s5") return "x21";
    else if(reg == "s6") return "x22";
    else if(reg == "s7") return "x23";
    else if(reg == "s8") return "x24";
    else if(reg == "s9") return "x25";
    else if(reg == "s10") return "x26";
    else if(reg == "s11") return "x27";
    else if(reg == "t3") return "x28";
    else if(reg == "t4") return "x29";
    else if(reg == "t5") return "x30";
    else if(reg == "t6") return "x31";
    else return reg;
}

// Function to insert nops in the instructions if data forwarding and hazard detection was not implemented
void NoForwarding(string line[], string rd[], string rs1[], string rs2[], int Total_lines)
{
    fstream output_file;
    int New_Total_lines = Total_lines;
    output_file.open("output.txt", ios::out); 
    output_file<<"No Data Forwarding and No Hazard Detection are implemented:"<<endl;
    cout<<"No Data Forwarding and Hazard Detection are implemented:"<<endl;
    for(int i=0; i<Total_lines; i++)
    {
        if(line[i].find("(")!= -1 && (line[i][0]=='s' || line[i][4]=='s' || line[i][8]=='s')) continue;
        if(rd[i]=="x0") continue;
        for(int j=i+1; j<i+3 ; j++)
        {
            if(rd[i] == rs1[j] || rd[i] == rs2[j])
            {
                if(j==i+1)
                {
                    if(line[j].find("nop\n") == -1)
                    {
                        line[j].insert(0,"nop\nnop\n");
                        New_Total_lines+=2;
                    }
                    else
                    {
                        line[j].insert(0,"nop\n");
                        New_Total_lines++;
                    }
                    break;
                }
                else if(j==i+2)
                {
                    line[j].insert(0,"nop\n");
                    New_Total_lines++;
                }
            }
        }
    }
    for(int i=0; i<Total_lines; i++)
    {
        output_file<< line[i] << endl;
        cout<< line[i] << endl;
    }
    output_file<< "Total: " << New_Total_lines + 4 <<" cycles\n" << endl;
    cout<< "Total: " << New_Total_lines + 4 <<" cycles\n" << endl;
    output_file.close();
}

// Function to insert nops in the instructions if data forwarding and hazard detection was implemented
void Forwarding(string line[], string rd[], string rs1[], string rs2[], int Total_lines)
{
    fstream output_file;
    output_file.open("output.txt", ios::out | ios::app); 
    output_file<<"Data Forwarding and Hazard Detection are implemented:"<<endl;
    cout<<"Data Forwarding and Hazard Detection are implemented:"<<endl;
    int New_Total_lines = Total_lines;
    for(int i=0; i<Total_lines; i++)
    {
        if(line[i].find("(")!= -1 && (line[i][0]=='l' || line[i][4]=='l'))
        {
            if(rd[i] == rs1[i+1 ] && rs2[i+1] == rs1[i+1])
            {
                line[i+1].insert(0,"nop\n");
                New_Total_lines++;
            }
            else if(rd[i] == rs1[i+1] && (line[i+1].find("(")!= -1 && (line[i+1][0]=='s' || line[i+1][4]=='s')))
            {
                continue;
            }
            else if(rd[i] == rs1[i+1] || rd[i] == rs2[i+1])
            {
                line[i+1].insert(0,"nop\n");
                New_Total_lines++;
            }
        }
    }
    for(int i=0; i<Total_lines; i++)
    {
        output_file<< line[i] << endl;
        cout<< line[i] << endl;
    }
    output_file<< "Total: " << New_Total_lines + 4 <<" cycles" << endl;
    cout<< "Total: " << New_Total_lines + 4 <<" cycles" << endl;
    output_file.close();
}

int main() 
{
    fstream input_file;
    string line[SIZE];
    string rs1[SIZE];
    string rs2[SIZE];
    string rd[SIZE];

    // Reading the input file line by line and storing the instructions in an array of strings
    int Total_lines = 0;
    input_file.open("input.txt", ios::in); 
    if (input_file.is_open()) 
    { 
        while (!input_file.eof()) 
        { 
            getline(input_file, line[Total_lines]);
            line[Total_lines].erase(line[Total_lines].find_last_not_of(" \n\r\t")+1);
            Total_lines++;
        }
        if(line[Total_lines-1].empty())
        {
            Total_lines--;
        }
    }
    else
    {
        cout<< "File not found" << endl;
    }  
    
    // Parsing the input file to get the registers
    for(int j = 0; j < Total_lines; j++)
    {
        if(line[j].find("(") == -1)
        {
            int index_start = line[j].find(" ");
            int index_end = line[j].find(",");
            int n = index_end - index_start -1;
            rd[j] = line[j].substr(index_start + 1, n);

            index_start = index_end + 1;
            index_end = line[j].find(",", index_start);
            n = index_end - index_start -1;
            rs1[j] = line[j].substr(index_start + 1, n);
            
            index_start = index_end + 1;
            index_end = line[j].length() - 1;
            n = index_end - index_start ;
            rs2[j] = line[j].substr(index_start + 1, n);   // rs2 becomes the immediate value for the I-type instruction (only the 2nd column of the risc-V card)
        }
        else if(line[j][0]=='l')   // for load instructions
        {
            int index_start = line[j].find(" ");
            int index_end = line[j].find(",");
            int n = index_end - index_start -1;
            rd[j] = line[j].substr(index_start + 1, n);

            index_start = index_end + 1;
            index_end = line[j].find("(");
            n = index_end - index_start - 1;
            rs2[j] = line[j].substr(index_start + 1, n);   // rs2 becomes the immediate value for the load type instruction 

            index_start = line[j].find("(");
            index_end = line[j].find(")");
            n = index_end - index_start -1;
            rs1[j] = line[j].substr(index_start + 1, n);
        }
        else if(line[j][0]=='s')   // for store instructions
        {
            int index_start = line[j].find("(");
            int index_end = line[j].find(")");
            int n = index_end - index_start -1;
            rs2[j] = line[j].substr(index_start + 1, n);

            index_start = line[j].find(" ");
            index_end = line[j].find(",");
            n = index_end - index_start -1;
            rs1[j] = line[j].substr(index_start + 1, n);

            index_start = index_end + 1;
            index_end = line[j].find("(");
            n = index_end - index_start - 1;
            rd[j] = line[j].substr(index_start + 1, n);   // rd becomes the immediate value for the store type instruction 
        }
    }
    
    // Changing the register alias to the standard name 
    for(int i=0; i<Total_lines; i++)
    {
        if(rd[i].find("x") == -1)
        {
            rd[i] = ChangeRegisterAlias(rd[i]);
        }
        if(rs1[i].find("x") == -1)
        {
            rs1[i] = ChangeRegisterAlias(rs1[i]);
        }
        if(rs2[i].find("x") == -1)
        {
            rs2[i] = ChangeRegisterAlias(rs2[i]);
        }
    }

    // Copying the registers and instructions to use in the functions
    string line_copy[SIZE];
    string rs1_copy[SIZE];
    string rs2_copy[SIZE];
    string rd_copy[SIZE];
    for(int i=0; i<Total_lines; i++)
    {
        line_copy[i] = line[i];
        rs1_copy[i] = rs1[i];
        rs2_copy[i] = rs2[i];
        rd_copy[i] = rd[i];
    }
    // Inserting nops in the instructions for no forwarding and no hazard detection case.
    NoForwarding(line_copy, rd_copy, rs1_copy, rs2_copy, Total_lines);
    // Copying the registers and instructions to use in the functions.
    for(int i=0; i<Total_lines; i++)
    {
        line_copy[i] = line[i];
        rs1_copy[i] = rs1[i];
        rs2_copy[i] = rs2[i];
        rd_copy[i] = rd[i];
    }
    // Inserting nops in the instructions for forwarding and no hazard detection case.
    Forwarding(line_copy, rd_copy, rs1_copy, rs2_copy, Total_lines);
    
    input_file.close();
    return 0;
}
