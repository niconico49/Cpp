#include "ComponentRequestResponse.h"

void ComponentRequestResponse::setRequest(QString value) {
    this->request = value;
}

QString ComponentRequestResponse::getRequest() {
    return this->request;
}

void ComponentRequestResponse::setResponse(QString value) {
    this->response = value;
}

QString ComponentRequestResponse::getResponse() {
    return this->response;
}
