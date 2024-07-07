#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


int hexToBinary(const char* hexString, char* binString) 
{
    char* bin;
    for(int i = 0; i < 8; i++) 
    {
        switch(hexString[i]) 
        {
            case '0': bin = "0000";break;
            case '1': bin = "0001";break;
            case '2': bin = "0010";break;
            case '3': bin = "0011";break;
            case '4': bin = "0100";break;
            case '5': bin = "0101";break;
            case '6': bin = "0110";break;
            case '7': bin = "0111";break;
            case '8': bin = "1000";break;
            case '9': bin = "1001";break;
            case 'A': case 'a': bin = "1010";break;
            case 'B': case 'b': bin = "1011";break;
            case 'C': case 'c': bin = "1100";break;
            case 'D': case 'd': bin = "1101";break;
            case 'E': case 'e': bin = "1110";break;
            case 'F': case 'f': bin = "1111";break;
            default: bin = NULL;
        }
        if(bin == NULL) 
        {
            printf("Invalid hex character: %c\n", hexString[i]);
        }
        strcat(binString, bin);
    }
    binString[32]='\0';
    // printf("%s\n", binString);
    return 0;
}
int binaryToDecimal(char* binaryString) 
{
    int length = strlen(binaryString);
    int decimal = 0;
    int i = length - 1, j = 0;
    while(i >= 0) 
    {
        if (binaryString[i] == '1') 
        {
            decimal += pow(2, j);
        }
        i--; 
        j++;
    }
    return decimal;
}
int binaryToDecimalsigned(char* binaryString) 
{
    int length = strlen(binaryString);
    int decimal = 0;
    int sign_bit = 0;
    char dubstr[100];
    strcpy(dubstr,binaryString);
    if (dubstr[0] == '1')
    {
        sign_bit = 1;
        // Invert the bits and add 1 to calculate the absolute value
        for (int i = 0; i < length; i++) 
        {
            dubstr[i] = (dubstr[i] == '0') ? '1' : '0';
        }
        // Add 1 to complete two's complement conversion
        for (int i = length - 1; i >= 0; i--) 
        {
            if (dubstr[i] == '0') 
            {
                dubstr[i] = '1';
                break;
            } 
            else 
            {
                dubstr[i] = '0';
            }
        }
    }
    int i = length - 1, j = 0;
    while(i >= 0) 
    {
        if (dubstr[i] == '1') 
        {
            decimal += pow(2, j);
        }
        i--; 
        j++;
    }
    return (sign_bit == 1) ? -decimal : decimal;
}
int findOpcode(char* binString, char* string)
{
    for(int i=25; i<32; i++)
    {
        string[i-25]=binString[i];
    }
    string[8]='\0';
    return 0;
}
int findfunct3(char* binString, char* string)
{
    for(int i=17; i<20; i++)
    {
        string[i-17]=binString[i];
    }
    string[3]='\0';
    return 0;
}
int findfunct7(char* binString, char* string)
{
    for(int i=0; i<7; i++)
    {
        string[i]=binString[i];
    }
    string[7]='\0';
    return 0;
}
int findrs1(char* binString, char* string)
{
    for(int i=12; i<17; i++)
    {
        string[i-12]=binString[i];
    }
    string[5]='\0';
    return 0;
}
int findrs2(char* binString, char* string)
{
    for(int i=7; i<12; i++)
    {
        string[i-7]=binString[i];
    }
    string[5]='\0';
    return 0;
}
int findrd(char* binString, char* string)
{
    for(int i=20; i<25; i++)
    {
        string[i-20]=binString[i];
    }
    string[5]='\0';
    return 0;
}
int R_format(char* str)
{
    char funct3[20], rs1[20], rs2[20], rd[20], funct7[20];
    findfunct3(str, funct3);
    findfunct7(str, funct7);
    findrs1(str, rs1);
    findrs2(str, rs2);
    findrd(str, rd);
    // printf("%s\n", str);
    // printf("%s %s %s %s %s\n",funct7,rs2,rs1,funct3,rd);
    int dec_rs2 = binaryToDecimal(rs2);
    int dec_rs1 = binaryToDecimal(rs1);
    int dec_rd = binaryToDecimal(rd);
    if(strcmp(funct3,"000")==0)
    {
        if(strcmp(funct7,"0000000")==0)
        {
            printf("add x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
        }
        else if(strcmp(funct7,"0100000")==0)
        {
            printf("sub x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
        }
    }
    else if(strcmp(funct3,"101")==0)
    {
        if(strcmp(funct7,"0000000")==0)
        {
            printf("srl x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
        }
        if(strcmp(funct7,"0100000")==0)
        {
            printf("sra x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
        }
    }
    else if(strcmp(funct3,"100")==0)
    {
        printf("xor x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
    }
    else if(strcmp(funct3,"110")==0)
    {
        printf("or x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
    }
    else if(strcmp(funct3,"111")==0)
    {
        printf("and x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
    }
    else if(strcmp(funct3,"001")==0)
    {
        printf("sll x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
    }
    else if(strcmp(funct3,"010")==0)
    {
        printf("slt x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
    }
    else if(strcmp(funct3,"011")==0)
    {
        printf("sltu x%d, x%d, x%d\n", dec_rd, dec_rs1, dec_rs2);
    }
    return 0; 
}
int I_format_1(char* str)
{
    char funct3[20], rs1[20], rd[20];
    findfunct3(str, funct3);
    findrs1(str, rs1);
    findrd(str, rd);  
    if(strcmp(funct3,"101")==0 || strcmp(funct3,"001")==0)
    {
        char imm1[20],imm2[20];
        for(int i=6; i<12; i++)
        {
            imm1[i-6]=str[i];
        }
        imm1[6]='\0';
        for(int i=0; i<6; i++)
        {
            imm2[i]=str[i];
        }
        imm2[6]='\0';
        int dec_imm = binaryToDecimalsigned(imm1); 
        int dec_rs1 = binaryToDecimal(rs1);
        int dec_rd = binaryToDecimal(rd);
        if(strcmp(funct3,"101")==0 && strcmp(imm2,"000000")==0)
        {
            printf("srli x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm); 
        }
        else if(strcmp(funct3,"101")==0 && strcmp(imm2,"010000")==0)
        {
            printf("srai x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm); 
        }
        else if(strcmp(funct3,"001")==0)
        {
            printf("slli x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm); 
        }
    }
    else
    {
        char Imm[20];
        for(int i=0; i<12; i++)
        {
            Imm[i]=str[i];
        }
        Imm[12]='\0';
        int dec_rs1 = binaryToDecimal(rs1);
        int dec_rd = binaryToDecimal(rd); 
        int dec_imm = binaryToDecimalsigned(Imm);   

        if(strcmp(funct3,"000")==0)
        {
            printf("addi x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm);
        }
        else if(strcmp(funct3,"100")==0)
        {
            printf("xori x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm);
        }
        else if(strcmp(funct3,"110")==0)
        {
            printf("ori x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm);
        }
        else if(strcmp(funct3,"111")==0)
        {
            printf("andi x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm);
        } 
        else if(strcmp(funct3,"010")==0)
        {
            printf("slti x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm);
        }
        else if(strcmp(funct3,"011")==0)
        {
            printf("sltiu x%d, x%d, %d\n", dec_rd, dec_rs1, dec_imm);
        }
    }
    // printf("%s %s %s\n",rs1,funct3,rd);
    return 0; 
}
int I_format_2(char* str)
{
    char funct3[20], rs1[20], rd[20], opcode[20];
    findfunct3(str, funct3);
    findrs1(str, rs1);
    findrd(str, rd);
    findOpcode(str, opcode);
    char Imm[20];
    for(int i=0; i<12; i++)
    {
        Imm[i]=str[i];
    }
    Imm[12]='\0';
    int dec_rs1 = binaryToDecimal(rs1);
    int dec_rd = binaryToDecimal(rd); 
    int dec_imm = binaryToDecimalsigned(Imm);   
    if(strcmp(funct3,"000")==0 && strcmp(opcode,"1100111")==0)
    {
        printf("jal x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"000")==0 && strcmp(opcode,"0000011")==0)
    {
        printf("lb x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"001")==0)
    {
        printf("lh x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"010")==0)
    {
        printf("lw x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"011")==0)
    {
        printf("ld x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    } 
    else if(strcmp(funct3,"100")==0)
    {
        printf("lbu x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"101")==0)
    {
        printf("lhu x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"101")==0)
    {
        printf("lwu x%d, %d(x%d)\n", dec_rd, dec_imm, dec_rs1);
    }
    // printf("%s %s %s\n",rs1,funct3,rd);
    return 0; 
}
int S_format(char* str)
{
    char funct3[20], rs1[20], rs2[20], Imm[20];
    findfunct3(str, funct3);
    findrs1(str, rs1);
    findrs2(str, rs2);
    int i=24;
    while(i>19)
    {
        Imm[i-13]=str[i];
        i--;
    }
    i=6;
    while(i>=0)
    {
        Imm[i]=str[i];
        i--;
    }
    Imm[12]='\0';
    // printf("%s\n", Imm);
    // printf("%s %s %s %s %s\n",funct7,rs2,rs1,funct3,rd);
    int dec_rs2 = binaryToDecimal(rs2);
    int dec_rs1 = binaryToDecimal(rs1);
    int dec_imm = binaryToDecimalsigned(Imm); 
    if(strcmp(funct3,"000")==0)
    {
        printf("sb x%d, %d(x%d)\n", dec_rs2, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"001")==0)
    {
        printf("sh x%d, %d(x%d)\n", dec_rs2, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"010")==0)
    {
        printf("sw x%d, %d(x%d)\n", dec_rs2, dec_imm, dec_rs1);
    }
    else if(strcmp(funct3,"011")==0)
    {
        printf("sd x%d, %d(x%d)\n", dec_rs2, dec_imm, dec_rs1);
    }
}
int B_format(char* str, int currentLine, int* Label, int* Labelcheck, int* Index)
{
    char funct3[20], rs1[20], rs2[20], Imm[20];
    findfunct3(str, funct3);
    findrs1(str, rs1);
    findrs2(str, rs2);
    Imm[1]=str[24];
    Imm[0]=str[0];
    for(int i=1; i<7 ; i++)
    {
        Imm[i+1]=str[i];
        Imm[i+7]=str[i+19];
    }
    Imm[12]='\0';
    int dec_rs2 = binaryToDecimal(rs2);
    int dec_rs1 = binaryToDecimal(rs1);
    int dec_imm = 2 * binaryToDecimalsigned(Imm);
    int offset;
    offset = dec_imm/4;
    if(Labelcheck[currentLine + offset] != (currentLine + offset))
    {
        Labelcheck[currentLine + offset] = (currentLine + offset);
        Label[currentLine + offset] = *Index;
        (*Index)+=1;
    }
    if(strcmp(funct3,"000")==0)
    {
        printf("beq x%d, x%d, L%d\n", dec_rs1, dec_rs2, Label[currentLine+offset]);
    }
    else if(strcmp(funct3,"001")==0)
    {
        printf("bne x%d, x%d, L%d\n", dec_rs1, dec_rs2, Label[currentLine+offset]);
    }
    else if(strcmp(funct3,"100")==0)
    {
        printf("blt x%d, x%d, L%d\n", dec_rs1, dec_rs2, Label[currentLine+offset]);
    }
    else if(strcmp(funct3,"101")==0)
    {
        printf("bge x%d, x%d, L%d\n", dec_rs1, dec_rs2, Label[currentLine+offset]);
    } 
    else if(strcmp(funct3,"110")==0)
    {
        printf("bltu x%d, x%d, L%d\n", dec_rs1, dec_rs2, Label[currentLine+offset]);
    }
    else if(strcmp(funct3,"111")==0)
    {
        printf("bgeu x%d, x%d, L%d\n", dec_rs1, dec_rs2, Label[currentLine+offset]);
    }
    return 0;
}
int J_format(char* str, int currentLine, int* Label, int* Labelcheck, int* Index)
{
    char Imm[30], rd[20];
    findrd(str, rd);
    Imm[0]=str[0];
    Imm[9]=str[11];
    for(int i=1; i<9 ; i++)
    {
        Imm[i]=str[i+11];
    }
    for(int i=1; i<11 ; i++)
    {
        Imm[i+9]=str[i];
    }
    Imm[20]='\0';
    int dec_imm = 2*binaryToDecimalsigned(Imm);
    int dec_rd = binaryToDecimal(rd);
    int offset;
    offset = dec_imm/4;
    if(Labelcheck[currentLine + offset] != (currentLine + offset))
    {
        Labelcheck[currentLine + offset] = (currentLine + offset);
        Label[currentLine + offset] = *Index;
        (*Index)+=1;
    }
    printf("jal x%d, L%d\n", dec_rd, Label[currentLine + offset]);
    return 0;
}
int U_format(char* str, char* opcode)
{
    char Imm[30], rd[20];
    findrd(str, rd);
    for(int i=0; i<20 ; i++)
    {
        Imm[i]=str[i];
    }
    Imm[20]='\0';
    int dec_imm = binaryToDecimalsigned(Imm);
    int dec_rd = binaryToDecimal(rd);
    if(strcmp(opcode,"0110111")==0)
    {
        printf("lui x%d, %d\n", dec_rd, dec_imm);
    }
    else if(strcmp(opcode,"0010111")==0)
    {
        printf("auipc x%d, %d\n", dec_rd, dec_imm);
    }
    return 0;
}
int main() 
{
    int Labelcheck[20], Label[20];
    int Index; 
    char hexString[20][9]= {"01400193",
"05000213",
"004181b3",
"00619193",
"004181b3",
"00c000ef",    
"00125213",
"404181b3"};
    int lineCount = 8;
    for(int n=0; n<20; n++)
    {
        hexString[n][8]='\0';
    }
    int currentLine = 0;
    for(int m=0; m<20; m++)
    {
        Labelcheck[m]=-1;
        Label[m]=-1;
    }
    Index = 1; 
    char binString[20][32];
    char opcode[20][8];
    while(currentLine < lineCount)
    {
        hexToBinary(hexString[currentLine], binString[currentLine]);
        findOpcode(binString[currentLine], opcode[currentLine]);
        if(Labelcheck[currentLine]==currentLine)
        {
            printf("L%d: ", Label[currentLine]);
        }

        if(strcmp(opcode[currentLine],"0110011")==0)
        {
            R_format(binString[currentLine]);
        }
        else if(strcmp(opcode[currentLine],"0010011")==0)
        {
            I_format_1(binString[currentLine]);
        }
        else if(strcmp(opcode[currentLine],"0000011")==0)
        {
            I_format_2(binString[currentLine]);
        }
        else if(strcmp(opcode[currentLine],"0100011")==0)
        {
            S_format(binString[currentLine]);
        }
        else if(strcmp(opcode[currentLine],"1100011")==0)
        {
            B_format(binString[currentLine], currentLine, Label, Labelcheck, &Index);
        }
        else if(strcmp(opcode[currentLine],"1101111")==0)
        {
            J_format(binString[currentLine], currentLine, Label, Labelcheck, &Index);
        }
        else if(strcmp(opcode[currentLine],"0110111")==0 || strcmp(opcode[currentLine],"0010111")==0)
        {
            U_format(binString[currentLine],opcode[currentLine]);
        }
        currentLine++;
    }
    return 0;
}
