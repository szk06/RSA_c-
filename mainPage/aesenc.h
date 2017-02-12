#ifndef AESENC_H
#define AESENC_H

#include <QWidget>
#include <QtWidgets>
class AESenc : public QWidget
{
    Q_OBJECT
public:
    explicit AESenc(QWidget *parent = 0);
    QLabel *CipherText;
    QLabel *choose_key;

    QLineEdit *PlainText;
    QLineEdit *key_value;
    QPushButton *perform;
    QComboBox *key;
    QGridLayout *mygrid;
    QVBoxLayout *VLayout;
    void setGrid();
    void setVertical();


signals:

public slots:
    void compute();
};

#endif // AESENC_H
