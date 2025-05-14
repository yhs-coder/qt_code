#ifndef WIDGET_H
#define WIDGET_H

#include <QListWidget>
#include <QScrollArea>
#include <QWidget>

#include "cbasesetwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

    // private slots:
    //     // void slotItemClicked(QListWidgetItem* item);
    //     // void slotValueChanged(int value);

private:
    QListWidget* m_pListWidget = nullptr;
    QScrollArea* m_pScrollArea = nullptr;
    QStringList  m_textList;

    CBaseSetWidget* m_pBaseSetWidget;
};
#endif  // WIDGET_H
