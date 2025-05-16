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

private slots:
    void slotItemClicked(QListWidgetItem* item);
    void slotValueChanged(int value);

private:
    QListWidget* m_pListWidget = nullptr;
    QScrollArea* m_pScrollArea = nullptr;
    QStringList  m_textList;

    std::vector<QWidget*> m_vecWidget;
    CBaseSetWidget*       m_pBaseSetWidget;

    QWidget* m_pYunpanSetWidget;
    QWidget* m_pDownloadWidget;
    QWidget* m_pJieguanWidget;
    QWidget* m_pRenwuWidget;
    QWidget* m_pTixingWidget;
    QWidget* m_pXuanfuWidget;
    // GaojiSetWidget* m_pGaojiWidget;
    bool signFlag = false;
};
#endif  // WIDGET_H
