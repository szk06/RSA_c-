#include <QApplication>
#include "mainPage/main_widget.h"

int main (int argc, char** argv)
{
    QApplication app (argc, argv);

    main_widget main;
    main.setMinimumSize(450,450);
    main.show();

    return app.exec();
}
