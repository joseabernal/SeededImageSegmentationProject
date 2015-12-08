#include "src/gui/application.h"
#include "src/gui/mainwindow.h"

int main(int argc, char *argv[])
{
    Application application(argc, argv);
    MainWindow window;
    window.show();

    return application.exec();
}
