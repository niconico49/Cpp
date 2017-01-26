#ifndef HTMLPAGE_H
#define HTMLPAGE_H

#include <QWidget>
#include <QString>
#include <QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>
#include "abstractnoscriptobject.h"

class HtmlPage : public QWebEngineView
{
    Q_OBJECT
private:
    QWebChannel channel;            // Channel for C++ to Javascript comms
    AbstractNoScriptObject* abstractNoScriptObject;

public:
    explicit HtmlPage(QWidget* parent = 0);
    virtual ~HtmlPage();
    Q_INVOKABLE void loadUrl(QString value);
    Q_INVOKABLE QString getTest(QString value);
    Q_INVOKABLE void close();
};

#endif // HTMLPAGE_H
