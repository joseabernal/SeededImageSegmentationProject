#include "GUI/application.h"
#include "GUI/mainwindow.h"

int main(int argc, char *argv[])
{
    Application application(argc, argv);
    MainWindow window;
    window.show();

    return application.exec();
}
