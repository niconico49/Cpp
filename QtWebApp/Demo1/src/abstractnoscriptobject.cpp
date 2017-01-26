#include "abstractnoscriptobject.h"
#include <QTextStream>

//AbstractNoScriptObject::AbstractNoScriptObject() {}

AbstractNoScriptObject* AbstractNoScriptObject::getInstance(QString value) {
    AbstractNoScriptObject* abstractNoScriptObject = new AbstractNoScriptObject();
    abstractNoScriptObject->setComponentDevelopment(new ComponentDevelopment());
    ComponentRequestResponse* componentRequestResponse = new ComponentRequestResponse();
    componentRequestResponse->setRequest(value);
    abstractNoScriptObject->setComponentRequestResponse(componentRequestResponse);
    //connect(abstractNoScriptObject, SIGNAL(getComponentDevelopmentSignal()), abstractNoScriptObject, SLOT(getComponentDevelopment()));
    //connect(abstractNoScriptObject, &AbstractNoScriptObject::getComponentDevelopmentSignal, abstractNoScriptObject, &AbstractNoScriptObject::getComponentDevelopment);
    //connect(abstractNoScriptObject, &AbstractNoScriptObject::getTestSignal, abstractNoScriptObject, &AbstractNoScriptObject::getTest);
    return abstractNoScriptObject;
}

QString AbstractNoScriptObject::getTest(QString value) {
    QTextStream(stdout) << value << "\r\n";
    return value + "TestTest";
}

ComponentDevelopment* AbstractNoScriptObject::getComponentDevelopment() {
    //emit AbstractNoScriptObject::getComponentDevelopmentSignal();
    return this->componentDevelopment;
}

void AbstractNoScriptObject::setComponentDevelopment(ComponentDevelopment* componentDevelopment) {
    this->componentDevelopment = componentDevelopment;
}

ComponentRequestResponse* AbstractNoScriptObject::getComponentRequestResponse() {
    return this->componentRequestResponse;
}

void AbstractNoScriptObject::setComponentRequestResponse(ComponentRequestResponse* componentRequestResponse) {
    this->componentRequestResponse = componentRequestResponse;
}
