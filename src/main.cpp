#include <QApplication>
#include "mainwindow.h"
#include <qfile.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");
    

    QFile data(":/assets/style.qss");

    if(!data.open(QFile::ReadOnly))
    {
        qWarning() << "打不开";
        return -1;
    }
    QTextStream out(&data);
    a.setStyleSheet(out.readAll());

    
    MainWindow w;
    w.show();

    return a.exec();
}
