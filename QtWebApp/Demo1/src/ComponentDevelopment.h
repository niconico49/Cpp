//#pragma once
#include <QObject>
#include <iostream>

class ComponentDevelopment : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE static void displayValue(QString value);
};
