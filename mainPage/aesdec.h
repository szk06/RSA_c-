#ifndef AESDEC_H
#define AESDEC_H

#include <QWidget>
#include <QtWidgets>
class aesdec : public QWidget
{
    Q_OBJECT
public:
    explicit aesdec(QWidget *parent = 0);
    QPushButton *decrypt;
    QLineEdit *Cipher_text;
    QLineEdit *key_value;
    QComboBox *key;
    QGridLayout *mygrid;
    QVBoxLayout *VLayout;
    QLabel *PlainText;
    QLabel *choose_key;
    void setGrid();
    void setVertical();
signals:

public slots:
    void compute();
};

#endif // AESDEC_H
