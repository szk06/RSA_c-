#include "main_widget.h"
#include<iostream>
#include<QVariant>
using namespace std;

main_widget::main_widget(QWidget *parent) : QWidget(parent)
{
    Go = new QPushButton("Go");
    //connect(Go,SIGNAL(clicked(),this,SLOT(button_pressed());
    connect (Go,SIGNAL(clicked()),this,SLOT(button_pressed()));
    select = new QLabel("Select the project you want");
    projects= new QComboBox();
    QString s = "AES encryption";
    projects->addItem(s);
    s = "AES Decryption";
    projects->addItem(s);
    s = "Prime Factorizations";
    projects->addItem(s);
    set_horizontal_layout();
    set_stacked_layout();
    set_vertical_layout();
    setLayout(VLayout);

}

void main_widget::set_stacked_layout(){
    SLayout = new QStackedLayout();

    hello = new QLabel("Welcome to 455 Project!");
    SLayout->addWidget(hello);

    AESenc_widg = new AESenc();
    SLayout->addWidget(AESenc_widg);


    AESdec_widg = new aesdec();
    SLayout->addWidget(AESdec_widg);

    prime_widg = new prime();
    SLayout->addWidget(prime_widg);
}

void main_widget::set_vertical_layout(){
    VLayout = new QVBoxLayout();
    VLayout->addLayout(HLayout);
    VLayout->addLayout(SLayout);
}
void main_widget::set_horizontal_layout(){
    HLayout = new QHBoxLayout();
    HLayout->addWidget(select);
    HLayout->addWidget(projects);
    HLayout->addWidget(Go);

}
void main_widget::button_pressed(){

    QString selected = projects->currentText();


    if(selected =="AES encryption"){
        SLayout->setCurrentWidget(AESenc_widg);

    }
    if(selected=="AES Decryption"){
        SLayout->setCurrentWidget(AESdec_widg);
    }
    if(selected=="Prime Factorizations"){
        SLayout->setCurrentWidget(prime_widg);

    }

}
