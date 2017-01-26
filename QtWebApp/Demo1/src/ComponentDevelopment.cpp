#include "ComponentDevelopment.h"
#include <QTextStream>
#include <string>

void ComponentDevelopment::displayValue(QString value) {
    QTextStream(stdout) << value << "\r\n";
}
