#ifndef PRIME_H
#define PRIME_H

#include <QWidget>
#include<QtWidgets>
#include<QFrame>

class prime : public QWidget
{
    Q_OBJECT
public:
    explicit prime(QWidget *parent = 0);
    QGridLayout *prime_grid;
    QVBoxLayout *VLayout;

    //prime factor//
    QPushButton *prime_button;
    QLineEdit *prime_num;
    QLabel *prime_out;
    QLabel *prime_title;
    QFrame *prime_sep;
    //-----------------------
    //euler///
    QLabel *euler_out;
    QLineEdit *euler_num;
    QPushButton *euler_button;


    //------

    //Miller-///////////////
    QLabel *miller_out;
    QLineEdit *miller_iteration;
    QLineEdit *miller_num;
    QPushButton *miller_button;


    //------------------


    //Fast------------------
    QLabel *fast_out;
    QLineEdit *fast_base;
    QLineEdit *fast_exp;
    QLineEdit *fast_mod;
    QPushButton *fast_button;



    //-----------------------------


    //Chineese
    void setGrid();
    void setVertical();

signals:

public slots:
    void compute_prime();
    void compute_euler();
    void compute_miller();
    void compute_fast();
};

#endif // PRIME_H
