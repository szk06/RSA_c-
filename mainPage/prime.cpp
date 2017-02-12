
#include "prime.h"
#include<iostream>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

#define ll long long

using namespace std;


//Fast ----------------
ll modular_pow(ll base, ll exponent, int modulus)
{
    ll result = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}






//Miller functions-------------

ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/*
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll p,int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2==0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}





//---------------


int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b%a, a);
}

// A simple method to evaluate Euler Totient Function
int phi(unsigned int n)
{
    unsigned int result = 1;
    for (int i=2; i < n; i++)
        if (gcd(i, n) == 1)
            result++;
    return result;
}



prime::prime(QWidget *parent) : QWidget(parent)
{
    prime_button = new QPushButton("Compute Prime factorization");
    prime_num =new QLineEdit();
    prime_num->setPlaceholderText("Enter your Number here");
    prime_out= new QLabel("Prime Factors:");
    prime_grid = new QGridLayout;
    prime_grid->setMargin(10);
    prime_grid->setHorizontalSpacing(5);
    prime_grid->setVerticalSpacing(10);
    VLayout = new QVBoxLayout;
    prime_title =new QLabel("Prime factorization");
    prime_sep =new QFrame;
    prime_sep->setFrameShape(QFrame::HLine);
    //Euler Part///////

    euler_out = new QLabel("Euler of num");
    euler_button = new QPushButton("Compute Euler Function");
    euler_num = new QLineEdit();
    euler_num->setPlaceholderText("Enter number here for Euler");

    //--------

    //Miller Part------------------
    miller_out =new QLabel("Miller Test: ");
    miller_button = new QPushButton("Perform Prime Test");
    miller_num = new QLineEdit();
    miller_num->setPlaceholderText("Enter Number to be tested");
    miller_iteration = new QLineEdit();
    miller_iteration->setPlaceholderText("Enter number of iterations");



    //------------

    //Fast Part--------------
    fast_out =new QLabel("Fast exponentiation: ");
    fast_button = new QPushButton("Perform exponentiation ");
    fast_base = new QLineEdit();
    fast_base->setPlaceholderText("Enter Base");
    fast_exp = new QLineEdit();
    fast_exp->setPlaceholderText("Enter exponent");
    fast_mod = new QLineEdit();
    fast_mod->setPlaceholderText("Enter mod value");



    //------------
    setGrid();
    setVertical();
    setLayout(VLayout);
    connect(prime_button,SIGNAL(clicked()),this,SLOT(compute_prime()));
    connect(euler_button,SIGNAL(clicked()),this,SLOT(compute_euler()));
    connect(miller_button,SIGNAL(clicked()),this,SLOT(compute_miller()));
    connect(fast_button,SIGNAL(clicked()),this,SLOT(compute_fast()));


}
void prime:: setGrid(){
    //prime_grid->addWidget(prime_title,0,0);
    prime_grid->addWidget(prime_num,0,0);
    prime_grid->addWidget(prime_button,0,1);
    prime_grid->addWidget(prime_out,0,2);
    prime_grid->addWidget(euler_num,1,0);
    prime_grid->addWidget(euler_button,1,1);
    prime_grid->addWidget(euler_out,1,2);
    prime_grid->addWidget(miller_num,2,0);
    prime_grid->addWidget(miller_iteration,2,1);
    prime_grid->addWidget(miller_button,2,2);
    prime_grid->addWidget(miller_out,2,3);
    prime_grid->addWidget(fast_base,3,0);
    prime_grid->addWidget(fast_exp,3,1);
    prime_grid->addWidget(fast_mod,3,2);
    prime_grid->addWidget(fast_button,3,3);
    prime_grid->addWidget(fast_out,3,4);
    prime_grid->addWidget(prime_sep,4,0,4,4);

}
void prime ::setVertical(){
    VLayout->addItem(prime_grid);

}
void prime::compute_prime(){
    QString prime_text = prime_num->text();
    int number = prime_text.toInt();
    if(prime_text=="" || number<0){
        prime_out->setText("Can't be empty or -ve");
    }else{
        QString out= "";
        QString temp ="";

        int counter=0;
        for(int i=2; i<=number; i++){
                //cout<<"i="<<i<<"number="<<number<<endl;
                while(number% i ==0){
                    number = number/i;
                    cout<<"Factor: "<<i<<endl;
                    temp = QString::number(i);
                    if(counter>0){
                        out = out+", "+temp;
                    }
                    else if (counter==0){
                        out = temp +out;
                    }
                    counter++;
                }

            }
            cout<<"Last factor: "<<number<<endl;
            temp = QString::number(number);
            out = out+ ", "+temp;
            prime_out->setText("Factors are: "+out);
    }

}
void prime::compute_euler(){
    QString s = euler_num->text();

    int i = s.toInt();
    if(i<0 || s==""){
        QPalette palette;
        palette.setColor(QPalette::Background,Qt::red);

        euler_num->setPalette(palette);
        if(s==""){
            euler_out->setText("You should enter a number!");
        }else{
            euler_out->setText("You can't enter a -ve number bro!");
        }


    }else{

        int disp= phi(i);
        QString on = QString::number(disp);
        euler_out->setText("phi("+s+") is: "+on);
    }

}
void prime::compute_miller(){
    QString iter_str = miller_iteration->text();
    int iteration = iter_str.toInt();
    QString num_str = miller_num->text();
    int num_int = num_str.toInt();
    ll num = num_str.toLongLong();
    if(num_int<0 || iter_str==""){
        QPalette palette_miller;
        palette_miller.setColor(QPalette::Background,Qt::red);
        miller_num->setPalette(palette_miller);
        miller_out->setText("You can't enter a -ve number bro!");

    }else{

        if (Miller(num, iteration))
        {
            cout<<num<<" is prime"<<endl;
            miller_out->setText(num_str+" Maybe Prime!");

        }
        else{
            cout<<num<<" is not prime"<<endl;
            miller_out->setText(num_str+" is: Not Prime");
        }
    }


}
void prime::compute_fast(){
    ll x, y, out;
    int mod;
    QString mod_str = fast_mod->text();
    mod = mod_str.toInt();
    x = fast_base->text().toLongLong();
    y=  fast_exp->text().toLongLong();
    out = modular_pow(x, y , mod);
    QString paste =QString::number(out);
    fast_out->setText("Exponentiation output: "+paste+" mod "+mod_str);
}
