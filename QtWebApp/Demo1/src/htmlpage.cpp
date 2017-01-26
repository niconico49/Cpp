#include "htmlpage.h"
#include "abstractnoscriptobject.h"

HtmlPage::HtmlPage(QWidget* parent) :
   QWebEngineView(parent)
{
    /*
    // Set up the communications channel
    this->page()->setWebChannel(&channel);
    channel.registerObject("widget", this);

    this->abstractNoScriptObject = AbstractNoScriptObject::getInstance("TestNickTestNick");
    channel.registerObject("AbstractNoScriptObject", this->abstractNoScriptObject);

    channel.registerObject("ComponentDevelopment", this->abstractNoScriptObject->getComponentDevelopment());
    channel.registerObject("ComponentRequestResponse", this->abstractNoScriptObject->getComponentRequestResponse());

    // Set the page content
    setUrl(QUrl("qrc:/index.html"));
*/
}

void HtmlPage::loadUrl(QString value) {
    this->page()->setWebChannel(&channel);
    channel.registerObject("widget", this);

    this->abstractNoScriptObject = AbstractNoScriptObject::getInstance("TestNickTestNick");
    channel.registerObject("AbstractNoScriptObject", this->abstractNoScriptObject);

    channel.registerObject("ComponentDevelopment", this->abstractNoScriptObject->getComponentDevelopment());
    channel.registerObject("ComponentRequestResponse", this->abstractNoScriptObject->getComponentRequestResponse());

    // Set the page content
    setUrl(QUrl("qrc:/index.html"));
}

void HtmlPage::close() {
    QWebEngineView::close();
    QString result = this->abstractNoScriptObject->getComponentRequestResponse()->getResponse();
    //QTextStream(stdout) << "c++result = " << result << "\r\n";
}

HtmlPage::~HtmlPage()
{
}

QString HtmlPage::getTest(QString value) {
    //QTextStream(stdout) << value << "\r\n";
    return value + "TestTest";
}
