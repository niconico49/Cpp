/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include "requestmapper.h"
#include "filelogger.h"
#include "staticfilecontroller.h"
#include "controller/webservicecontroller.h"
#include "controller/dumpcontroller.h"
#include "controller/templatecontroller.h"
#include "controller/formcontroller.h"
#include "controller/fileuploadcontroller.h"
#include "controller/sessioncontroller.h"

#include "abstractnoscriptobject.h"
#include "webform.h"

/** Redirects log messages to a file */
extern FileLogger* logger;

/** Controller for static files */
extern StaticFileController* staticFileController;

RequestMapper::RequestMapper(QObject* parent)
    :HttpRequestHandler(parent)
{
    qDebug("RequestMapper: created");
    QWebEngineView *qWebEngineView = new QWebEngineView(0);
    //QTextStream(stdout) << QDir::currentPath() << "\r\n";
    qWebEngineView->load(QUrl(QString("file:///%1/Demo1/etc/docroot/index.html").arg(QFileInfo(".").absolutePath())));
    qWebEngineView->show();

    webServiceController = new WebServiceController();
    connect(webServiceController, &WebServiceController::loadUrl, this, &RequestMapper::loadUrl);
    connect(this, &RequestMapper::wake, webServiceController, &WebServiceController::wake);
    //connect(webServiceController, &WebServiceController::loadUrl, this, &RequestMapper::loadUrl, Qt::BlockingQueuedConnection);
}

RequestMapper::~RequestMapper()
{
    qDebug("RequestMapper: deleted");
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path = request.getPath();
    qDebug("RequestMapper: path=%s", path.data());

    // For the following pathes, each request gets its own new instance of the related controller.

    if (path.startsWith("/webresources/api/execute"))
    {
        //WebServiceController().service(request, response);
        webServiceController->service(request, response);
    }
    else if (path.startsWith("/dump"))
    {
        DumpController().service(request, response);
    }
    else if (path.startsWith("/template"))
    {
        TemplateController().service(request, response);
    }
    else if (path.startsWith("/form"))
    {
        FormController().service(request, response);
    }
    else if (path.startsWith("/file"))
    {
        FileUploadController().service(request, response);
    }
    else if (path.startsWith("/session"))
    {
        SessionController().service(request, response);
    }
    // All other pathes are mapped to the static file controller.
    // In this case, a single instance is used for multiple requests.
    else
    {
        staticFileController->service(request, response);
    }

    qDebug("RequestMapper: finished request");

    // Clear the log buffer
    if (logger)
    {
       logger->clear();
    }
}

void RequestMapper::loadUrl(QString url, QString bodyJson) {
    QWebChannel* channel = new QWebChannel();

    WebForm* qWebEngineView = new WebForm();

    connect(qWebEngineView, &WebForm::closeEvent, this, &RequestMapper::closeEvent);
    qWebEngineView->page()->setWebChannel(channel);
    channel->registerObject("widget", qWebEngineView);

    //QTextStream(stdout) << bodyJson << "\r\n";
    //AbstractNoScriptObject* abstractNoScriptObject = AbstractNoScriptObject::getInstance(bodyJson);
    abstractNoScriptObject = AbstractNoScriptObject::getInstance(bodyJson);
    channel->registerObject("AbstractNoScriptObject", abstractNoScriptObject);

    channel->registerObject("ComponentDevelopment", abstractNoScriptObject->getComponentDevelopment());
    channel->registerObject("ComponentRequestResponse", abstractNoScriptObject->getComponentRequestResponse());

    //qWebEngineView->load(QUrl(QString("file:///%1/Demo1/index.html").arg(QFileInfo(".").absolutePath())));
    qWebEngineView->load(QUrl(url));
    //qWebEngineView->show();
}

void RequestMapper::closeEvent(QCloseEvent *event)
{
    //this->close();
    QString result = abstractNoScriptObject->getComponentRequestResponse()->getResponse();
    //QTextStream(stdout) << "c++result = " << result << "\r\n";
    event->accept();
    emit wake(result);
}
