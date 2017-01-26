/**
  @file
  @author Stefan Frings
*/

#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "controller/webservicecontroller.h"
#include "abstractnoscriptobject.h"

/**
  The request mapper dispatches incoming HTTP requests to controller classes
  depending on the requested path.
*/

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(RequestMapper)
private:
    WebServiceController* webServiceController;
    AbstractNoScriptObject* abstractNoScriptObject;
public:
    /**
      Constructor.
      @param parent Parent object
    */
    RequestMapper(QObject* parent=0);

    /**
      Destructor.
    */
    ~RequestMapper();

    /**
      Dispatch incoming HTTP requests to different controllers depending on the URL.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(HttpRequest& request, HttpResponse& response);
    void loadUrl(QString url, QString bodyJson);
signals:
    void wake(QString result);
public slots:
    void closeEvent(QCloseEvent *event);
};

#endif // REQUESTMAPPER_H
