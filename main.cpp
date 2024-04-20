#include "form_principal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    form_principal w;
    w.show();
    return a.exec();
}
