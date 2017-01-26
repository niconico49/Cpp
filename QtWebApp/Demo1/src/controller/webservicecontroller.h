#ifndef WEBSERVICECONTROLLER_H
#define WEBSERVICECONTROLLER_H

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"
#include <QtWebEngineWidgets>

/**
  This controller dumps the received HTTP request in the response.
*/

class WebServiceController : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(WebServiceController)
private:
  QWaitCondition* waiter;
  QString result;
/*
  QString params;
  void run()
  {
    //do stuff
    emit loadUrl(QString("file:///%1/Demo1/index.html").arg(QFileInfo(".").absolutePath()), this->params);
    //do more stuff
  }
*/
public:
    /** Constructor */
    WebServiceController();
/*
    void setParams(QString params) {
        this->params = params;
    }
*/
    /** Generates the response */
    void service(HttpRequest& request, HttpResponse& response);
signals:
    void loadUrl(QString url, QString params);
public slots:
    void wake(QString result);
};

#endif // WEBSERVICECONTROLLER_H
