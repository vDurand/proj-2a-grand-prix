#include <unistd.h>
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include <QNetworkProxy>
#include <stdlib.h>

#include "grandprix.h"
#include "headless.h"


int main(int argc, char *argv[])
{
    if (argc == 1) {
        QApplication a(argc, argv);

        // Detect current locale name
        QString localeName = QLocale::system().name();

        // Load translation files
        QTranslator translator;
        // "helloworld_"  is a prefix for our translation files.
        // "../HelloWorld" is a path to the folder containing translation files.
        translator.load(QString("GrandPrix_") + localeName, QString(":/"));
        // Install translations
        a.installTranslator(&translator);

        /*
         *  (NO LONGER USED, Seb. F.)
         */
        //  Set proxy
        //        char *http_proxy = getenv("http_proxy");
        //        if (http_proxy == NULL) {
        //            http_proxy = getenv("HTTP_PROXY");
        //        }
        //        if (http_proxy != NULL) {
        //            QString tmp(http_proxy);
        //            QRegExp re("[^/]//([^:]+):(\\d+)");
        //            re.indexIn(tmp);

        //            QStringList res = re.capturedTexts();

        //            if (res.length() == 3 && res.at(1).length() != 0 && res.at(2).length() != 0) {
        //                QNetworkProxy proxy;
        //                proxy.setType(QNetworkProxy::HttpProxy);
        //                proxy.setHostName(res[1]);
        //                proxy.setPort(res.at(2).toInt());
        //                QNetworkProxy::setApplicationProxy(proxy);
        //                qWarning() << a.tr("Connection through proxy %1:%2").arg(res[1]).arg(res[2]);
        //            } else {
        //                qWarning() << a.tr("Failed to parse HTTP_PROXY=`%1', connection whithout proxy.").arg(tmp);
        //            }
        //        } else {
        //            qWarning() << a.tr("Connection without proxy (HTTP_PROXY undefined)");
        //        }

        GrandPrix w;
        w.show();
        return a.exec();
    } else if (argc == 5) {
        bool ok;
        Headless a(argc, argv, &ok);
        if (ok)
            return a.exec();
        else
            return 1;
    } else {
        qCritical("./GrandPrix tracks/<map> drivers/<driver1> drivers/<driver2> drivers/<driver3>");
    }
}
