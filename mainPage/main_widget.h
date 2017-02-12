#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>

#include <QDebug>
#include<QPushButton>
#include<QLabel>
#include <QtWidgets>
#include"aesenc.h"
#include"aesdec.h"
#include "prime.h"

class main_widget : public QWidget
{
    Q_OBJECT
public:
    explicit main_widget(QWidget *parent = 0);


    QPushButton *Go;
    QLabel *select;
    QComboBox *projects;
    QLabel *hello;
    QVBoxLayout *VLayout;//!<The vertical layout where elements are stored
    QHBoxLayout *HLayout;//!<The horizontal layout where elements are stored
    QStackedLayout *SLayout;//!<The stacked layout where different specific windows are stored
    aesdec *AESdec_widg;
    prime *prime_widg;
    AESenc *AESenc_widg;
    void set_vertical_layout();
    void set_horizontal_layout();
    void set_stacked_layout();
signals:

public slots:
    void button_pressed();
};

#endif // MAIN_WIDGET_H
