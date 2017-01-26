#include "webservicecontroller.h"
#include <QVariant>
#include <QDateTime>

#include <QWebChannel>
#include <QWebEngineView>
#include "../abstractnoscriptobject.h"
#include "../htmlpage.h"
#include "../webform.h"

WebServiceController::WebServiceController()
{}

void WebServiceController::wake(QString result) {
    this->waiter->wakeAll();
    this->result = result;
}

void WebServiceController::service(HttpRequest& request, HttpResponse& response)
{
    response.setHeader("Access-Control-Allow-Origin", "*");
    response.setHeader("Access-Control-Allow-Methods", "GET,POST");
    response.setHeader("Access-Control-Allow-Headers", "origin, x-requested-with, content-type");
/*
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");
    response.setCookie(HttpCookie("firstCookie", "hello", 600));
    response.setCookie(HttpCookie("secondCookie", "world", 600));
 */
    QString bodyJson = request.getBody();

    QMutex* mutex = new QMutex();
    mutex->lock();
    QString url = QString("file:///%1/Demo1/index.html").arg(QFileInfo(".").absolutePath());
    emit loadUrl(url, bodyJson);
    this->waiter = new QWaitCondition();
    waiter->wait(mutex);
    //QTextStream(stdout) << "after wait" << "\r\n";
    mutex->unlock();
    //QTextStream(stdout) << "after unlock" << "\r\n";

    //QTextStream(stdout) << QByteArray::fromHex(this->result.toLatin1()) << "\r\n";
    //QString result = abstractNoScriptObject->getComponentRequestResponse()->getResponse();
    //response.write(QByteArray::fromHex(this->result.toLatin1()));
    //QByteArray array (this->result.toStdString().c_str());
    response.write(this->result.toStdString().c_str());

    //http://stackoverflow.com/questions/9777911/how-do-i-create-a-window-in-different-qt-threads
}
