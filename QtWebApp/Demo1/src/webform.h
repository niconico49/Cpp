#ifndef WEBFORM_H
#define WEBFORM_H

#include <QtWebEngineWidgets>

// gui component holder which will be moved to main thread
class WebForm : public QWebEngineView
{
    Q_OBJECT
  signals:
    void closeEvent(QCloseEvent* event);
  public slots:
    void finish() {
        emit this->closeEvent(new QCloseEvent());
    }
};
#endif // WEBFORM_H
