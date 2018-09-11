#include <QApplication>
#include "mainwindow.h"
#include "plc.h"

#ifdef LINUX
#include <signal.h>
#endif

static MainWindow* mw = nullptr;

#ifdef LINUX
void sig_handler(int) {
    if (mw!=nullptr)
        QMetaObject::invokeMethod(mw,"sysSIGPIPE");
}
#endif

int main(int argc, char *argv[])
{
#ifdef LINUX
    struct sigaction pipe;
    pipe.sa_handler = sig_handler;
    sigemptyset(&pipe.sa_mask);
    pipe.sa_flags = 0;
    pipe.sa_flags |= SA_RESTART;
    sigaction(SIGPIPE, &pipe, nullptr);
#endif
    qRegisterMetaType<CWP>("CWP");
    qRegisterMetaType<CWPList>("CWPList");
    qRegisterMetaType<CPairing>("CPairing");

    QApplication a(argc, argv);
    MainWindow w;
    mw = &w;
    w.show();
    
    return a.exec();
}
