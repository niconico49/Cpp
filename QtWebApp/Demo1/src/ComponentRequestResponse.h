//#pragma once
#include <QObject>

class ComponentRequestResponse : public QObject {
    Q_OBJECT
private:
    QString request;
    QString response;
public:
    Q_INVOKABLE void setRequest(QString value);
    Q_INVOKABLE QString getRequest();
    Q_INVOKABLE void setResponse(QString value);
    Q_INVOKABLE QString getResponse();
};
