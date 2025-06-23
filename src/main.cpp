#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    app.setApplicationName("ACT");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Sakuya");
    
    MainWindow window;
    window.show();
    
    return app.exec();
}
