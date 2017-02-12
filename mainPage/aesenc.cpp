#include "aesenc.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;
#define Nb 4

unsigned char in[16], out[16], state[4][4];
unsigned char RoundKey[240];
unsigned char Key[32];
int Nk=0;
int Nr=0;
//Start of the retrieved functions
int getSBoxValue(int num)
{
    int sbox[256] =   {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F
    return sbox[num];
}

// The round constant word array, Rcon[i], contains the values given by
// x to th e power (i-1) being powers of x (x is denoted as {02}) in the field GF(28)
// Note that i starts at 1, not 0).
int Rcon[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
    0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a,
    0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc,
    0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b,
    0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35,
    0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63,
    0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd,
    0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb  };

// This function produces Nb(Nr+1) round keys. The round keys are used in each round to encrypt the states.
void KeyExpansion()
{
    int i,j;
    unsigned char temp[4],k;

    // The first round key is the key itself.
    for(i=0;i<Nk;i++)
    {
        RoundKey[i*4]=Key[i*4];
        RoundKey[i*4+1]=Key[i*4+1];
        RoundKey[i*4+2]=Key[i*4+2];
        RoundKey[i*4+3]=Key[i*4+3];
    }

    // All other round keys are found from the previous round keys.
    while (i < (Nb * (Nr+1)))
    {
                    for(j=0;j<4;j++)
                    {
                        temp[j]=RoundKey[(i-1) * 4 + j];
                    }
                    if (i % Nk == 0)
                    {
                        // This function rotates the 4 bytes in a word to the left once.
                        // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

                        // Function RotWord()
                        {
                            k = temp[0];
                            temp[0] = temp[1];
                            temp[1] = temp[2];
                            temp[2] = temp[3];
                            temp[3] = k;
                        }

                        // SubWord() is a function that takes a four-byte input word and
                        // applies the S-box to each of the four bytes to produce an output word.

                        // Function Subword()
                        {
                            temp[0]=getSBoxValue(temp[0]);
                            temp[1]=getSBoxValue(temp[1]);
                            temp[2]=getSBoxValue(temp[2]);
                            temp[3]=getSBoxValue(temp[3]);
                        }

                        temp[0] =  temp[0] ^ Rcon[i/Nk];
                    }
                    else if (Nk > 6 && i % Nk == 4)
                    {
                        // Function Subword()
                        {
                            temp[0]=getSBoxValue(temp[0]);
                            temp[1]=getSBoxValue(temp[1]);
                            temp[2]=getSBoxValue(temp[2]);
                            temp[3]=getSBoxValue(temp[3]);
                        }
                    }
                    RoundKey[i*4+0] = RoundKey[(i-Nk)*4+0] ^ temp[0];
                    RoundKey[i*4+1] = RoundKey[(i-Nk)*4+1] ^ temp[1];
                    RoundKey[i*4+2] = RoundKey[(i-Nk)*4+2] ^ temp[2];
                    RoundKey[i*4+3] = RoundKey[(i-Nk)*4+3] ^ temp[3];
                    i++;
    }
}

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
void AddRoundKey(int round)
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] ^= RoundKey[round * Nb * 4 + i * Nb + j];
        }
    }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
void SubBytes()
{
    int i,j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[i][j] = getSBoxValue(state[i][j]);

        }
    }
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
void ShiftRows()
{
    unsigned char temp;

    // Rotate first row 1 columns to left
    temp=state[1][0];
    state[1][0]=state[1][1];
    state[1][1]=state[1][2];
    state[1][2]=state[1][3];
    state[1][3]=temp;

    // Rotate second row 2 columns to left
    temp=state[2][0];
    state[2][0]=state[2][2];
    state[2][2]=temp;

    temp=state[2][1];
    state[2][1]=state[2][3];
    state[2][3]=temp;

    // Rotate third row 3 columns to left
    temp=state[3][0];
    state[3][0]=state[3][3];
    state[3][3]=state[3][2];
    state[3][2]=state[3][1];
    state[3][1]=temp;
}

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// MixColumns function mixes the columns of the state matrix
void MixColumns()
{
    int i;
    unsigned char Tmp,Tm,t;
    for(i=0;i<4;i++)
    {
        t=state[0][i];
        Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i] ;
        Tm = state[0][i] ^ state[1][i] ; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp ;
        Tm = state[1][i] ^ state[2][i] ; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp ;
        Tm = state[2][i] ^ state[3][i] ; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp ;
        Tm = state[3][i] ^ t ; Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp ;
    }
}

// Cipher is the main function that encrypts the PlainText.
void Cipher()
{
    int i,j,round=0;

    //Copy the input PlainText to state array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            state[j][i] = in[i*4 + j];
        }
    }

    // Add the First round key to the state before starting the rounds.
    AddRoundKey(0);

    // There will be Nr rounds.
    // The first Nr-1 rounds are identical.
    // These Nr-1 rounds are executed in the loop below.
    for(round=1;round<Nr;round++)
    {
        SubBytes();
        ShiftRows();
        MixColumns();
        AddRoundKey(round);
    }

    // The last round is given below.
    // The MixColumns function is not here in the last round.
    SubBytes();
    ShiftRows();
    AddRoundKey(Nr);

    // The encryption process is over.
    // Copy the state array to output array.
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            out[i*4+j]=state[j][i];
        }
    }
}










//End of the retrieved functions

AESenc::AESenc(QWidget *parent) : QWidget(parent)
{
    PlainText = new QLineEdit();
    key_value = new QLineEdit();
    key_value->setPlaceholderText("Enter your key(in hex)");
    CipherText = new QLabel("Click Encrypt");
    choose_key = new QLabel("Choose Key Size: ");
    key = new QComboBox();
    key->addItem("128");
    key->addItem("192");
    key->addItem("256");
    mygrid = new QGridLayout;
    VLayout = new QVBoxLayout;
    perform = new QPushButton("Encrypt");
    PlainText->setPlaceholderText("Enter Plain Text(in hex)");
    connect(perform,SIGNAL(clicked()),this,SLOT(compute()));
    setGrid();
    setVertical();
    setLayout(VLayout);

}
void AESenc::setGrid(){
    mygrid->addWidget(key_value,0,0,0,2);
    mygrid->addWidget(choose_key,1,0);
    mygrid->addWidget(key,1,1);
    mygrid->addWidget(PlainText,2,0,2,2);


}
void AESenc::setVertical(){
    VLayout->addItem(mygrid);
    VLayout->addWidget(perform);
    VLayout->addWidget(CipherText);
}
void AESenc::compute(){


    QString selected = key->currentText();
    int myKey = selected.toInt();


    Nr = myKey;
    Nk = Nr / 32;
    Nr = Nk + 6;
    QString key_written = key_value->text();

    int key_place = (myKey/4)+15;

    QString plaintext_written =PlainText->text();
    //////////////////Key Code///////////////////////////
    QByteArray array = key_written.toLocal8Bit();
    char* hex = array.data();
    //cout<<"Key Size is:"<<key_written.size()<<endl;
    if(key_written.size()!=key_place){

        QPalette palette;
        palette.setColor(QPalette::Background,Qt::red);

        key_value->setPalette(palette);
        CipherText->setText("Key is not of correct size!");

    }else{
        char *p;
        int cnt = (strlen(hex) + 1) / 3; // Whether or not there's a trailing space
        unsigned char *result = (unsigned char *)malloc(cnt), *r;
        unsigned char c;

        for (p = hex, r = result; *p; p += 3) {
            if (sscanf(p, "%02X", (unsigned int *)&c) != 1) {
                break; // Didn't parse as expected
            }
            *r++ = c;
        }
        ///////////////////////////////End Key Code///////////////////////////////////////////

        /////////////////////////////Plain Text Code////////////////////////
        //cout<<"size of plain:"<<plaintext_written.size()<<endl;
        if(plaintext_written.size()!=key_place){
            QPalette palette1;
            palette1.setColor(QPalette::Background,Qt::red);

            PlainText->setPalette(palette1);
            CipherText->setText("PlainText is not of correct size!");

        }else{
            QByteArray array2 = plaintext_written.toLocal8Bit();
            char* hex2 = array2.data();
            //cout<<"Plain Text:"<<hex2<<endl;
            //cout<<"Size:"<<strlen(hex2)<<endl;
            char *p2;
            int cnt2 = (strlen(hex2) + 1) / 3;
            unsigned char *result2 = (unsigned char *)malloc(cnt2), *r2;
            unsigned char c2;
            for (p2 = hex2, r2 = result2; *p2; p2 += 3) {
                if (sscanf(p2, "%02X", (unsigned int *)&c2) != 1) {
                    break; // Didn't parse as expected
                }
                *r2++ = c2;
            }
            /*
            QPalette palette;
            palette.setColor(QPalette::Background,Qt::red);
            palette.setColor(QPalette::Text,Qt::white);
            PlainText->setPalette(palette);
            */
            //unsigned char temp[16] = {0x0  ,0x01  ,0x02  ,0x03  ,0x04  ,0x05  ,0x06  ,0x07  ,0x08  ,0x09  ,0x0a  ,0x0b  ,0x0c  ,0x0d  ,0x0e  ,0x0f};
            unsigned char temp2[16]= {0x00  ,0x11  ,0x22  ,0x33  ,0x44  ,0x55  ,0x66  ,0x77  ,0x88  ,0x99  ,0xaa  ,0xbb  ,0xcc  ,0xdd  ,0xee  ,0xff};
            int i;
            //cout<<"temp:"<<temp<<endl;
            for(i=0;i<Nk*4;i++)
            {

                Key[i]=result[i];
                in[i]=result2[i];
            }
            KeyExpansion();
            Cipher();
            QString newtemp;
            QString disp="";
            for(i=0;i<Nk*4;i++)
                {
                    //newtemp = QString ::number(out[i]);
                    newtemp.setNum(out[i],16);
                    disp = disp + " "+ newtemp;
                    printf("%02x ",out[i]);
                }

           printf("\n\n");
           CipherText->setText("Cipher Text is:"+disp);
        }


    }

}
