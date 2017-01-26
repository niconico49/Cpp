#ifndef ABSTRACTNOSCRIPTOBJECT_H
#define ABSTRACTNOSCRIPTOBJECT_H

//#pragma once

#include <QWebEngineView>
#include "ComponentDevelopment.h"
#include "ComponentRequestResponse.h"

class AbstractNoScriptObject : public QWebEngineView {
    Q_OBJECT
private:
    ComponentDevelopment* componentDevelopment;
    ComponentRequestResponse* componentRequestResponse;
public:
    //AbstractNoScriptObject();
    static AbstractNoScriptObject* getInstance(QString value);
    void setComponentDevelopment(ComponentDevelopment* componentDevelopment);
    void setComponentRequestResponse(ComponentRequestResponse* componentRequestResponse);
//public slots:
    Q_INVOKABLE ComponentDevelopment* getComponentDevelopment();
    Q_INVOKABLE ComponentRequestResponse* getComponentRequestResponse();
    Q_INVOKABLE QString getTest(QString);
//signals:
    //ComponentDevelopment* getComponentDevelopmentSignal();
    //QString getTestSignal(QString);
};

#endif // ABSTRACTNOSCRIPTOBJECT_H
