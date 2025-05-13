#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>
#include <QScrollArea>
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    QListWidget* m_pListWidget = nullptr;
    QScrollArea* m_pScrollArea = nullptr;
    QStringList  m_textList;
};
#endif  // WIDGET_H
