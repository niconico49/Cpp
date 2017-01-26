/**
  @file
  @author Stefan Frings
*/

//#include <QCoreApplication>
#include <QApplication>
#include <QDir>
#include <QWebEngineView>
#include "httplistener.h"
#include "templatecache.h"
#include "httpsessionstore.h"
#include "staticfilecontroller.h"
#include "filelogger.h"
#include "requestmapper.h"
#include "webform.h"

/** Cache for template files */
TemplateCache* templateCache;

/** Storage for session cookies */
HttpSessionStore* sessionStore;

/** Controller for static files */
StaticFileController* staticFileController;

/** Redirects log messages to a file */
FileLogger* logger;

/** Search the configuration file */
QString searchConfigFile()
{
    //QString binDir = QCoreApplication::applicationDirPath();
    //QString appName = QCoreApplication::applicationName();
    QString binDir = QApplication::applicationDirPath();
    QString appName = QApplication::applicationName();
    QString fileName(appName + ".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(QString("%1/etc").arg(binDir));
    searchList.append(QString("%1/../etc").arg(binDir));
    searchList.append(QString("%1/../../etc").arg(binDir)); // for development without shadow build
    searchList.append(QString("%1/../%2/etc").arg(binDir).arg(appName)); // for development with shadow build
    searchList.append(QString("%1/../../%2/etc").arg(binDir).arg(appName)); // for development with shadow build
    searchList.append(QString("%1/../../../%2/etc").arg(binDir).arg(appName)); // for development with shadow build
    searchList.append(QString("%1/../../../../%2/etc").arg(binDir).arg(appName)); // for development with shadow build
    searchList.append(QString("%1/../../../../../%2/etc").arg(binDir).arg(appName)); // for development with shadow build
    searchList.append(QString("%1etc/opt").arg(QDir::rootPath()));
    searchList.append(QString("%1etc").arg(QDir::rootPath()));

    foreach (QString dir, searchList)
    {
        QFile file(dir + "/" + fileName);
        if (file.exists())
        {
            // found
            fileName = QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s", qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found", qPrintable(dir), qPrintable(fileName));
    }
    qFatal("Cannot find config file %s", qPrintable(fileName));
    return 0;
}


/**
  Entry point of the program.
*/
int main(int argc, char *argv[])
{
    QTextStream(stdout) << "QFileInfo: " << QFileInfo(".").absolutePath() << "\r\n";

    //QCoreApplication app(argc, argv);
    QApplication app(argc, argv);

    app.setApplicationName("Demo1");
    app.setOrganizationName("Butterfly");

    // Find the configuration file
    QString configFileName = searchConfigFile();

    // Configure logging into a file
    /*
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    logSettings->beginGroup("logging");
    FileLogger* logger=new FileLogger(logSettings,10000,&app);
    logger->installMsgHandler();
    */

    // Configure template loader and cache
    QSettings* templateSettings = new QSettings(configFileName, QSettings::IniFormat, &app);
    templateSettings->beginGroup("templates");
    templateCache = new TemplateCache(templateSettings, &app);

    // Configure session store
    QSettings* sessionSettings = new QSettings(configFileName, QSettings::IniFormat, &app);
    sessionSettings->beginGroup("sessions");
    sessionStore  = new HttpSessionStore(sessionSettings, &app);

    // Configure static file controller
    QSettings* fileSettings = new QSettings(configFileName, QSettings::IniFormat, &app);
    fileSettings->beginGroup("docroot");
    staticFileController = new StaticFileController(fileSettings, &app);

    // Configure and start the TCP listener
    QSettings* listenerSettings = new QSettings(configFileName, QSettings::IniFormat, &app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings, new RequestMapper(&app), &app);

    qWarning("Application has started");

    app.exec();

    qWarning("Application has stopped");
}
