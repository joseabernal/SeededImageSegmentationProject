#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QMessageBox>
#include <QDebug>

/*
 * This class extends from QApplication. The basic difference is that once an
 * exception is detected, the application show an error message. The window is 
 * not closed.
 *
 * @see https://rohieb.wordpress.com/2010/07/08/qt-throw-exceptions-from-signals-and-slots/
 *
 * @author Jose Bernal
 */
class Application : public QApplication {
    public:
        /*
         * Class constructor
         */
        Application(int& argc, char ** argv);

        /*
         * Class destructor
         */
        virtual ~Application() { }

        /*
         * Documentation inherited.
         */
        virtual bool notify(QObject * receiver, QEvent * event) {
            try {
                return QApplication::notify(receiver, event);
            }
            catch(std::exception& e) {
                QMessageBox::warning(
                  NULL, tr("Exception thrown"), e.what());
                qCritical() << "Exception thrown:" << e.what();
            }
            return false;
        }
};

#endif