#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QMenu>
#include <QWidget>

// 视频分屏类型
enum VideoLayoutType
{
    OneVideo = 0,
    TwoVideo,
    ThreeVideo,
    FourVideo,
    FiveVideo,
    SixVideo,
    SeventVideo,
    EightVideo,
    NineVideo
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    void initWidget();
    void initMenu();

    // 菜单事件
    void contextMenuEvent(QContextMenuEvent* event);

private:
    // 切换不同布局
    void switchLayout(VideoLayoutType type);

private:
    // 保存视频区域
    QList<QLabel*>     m_videoLabelList;
    QMenu*             m_switchMenu;
    QMap<QString, int> m_strTypeMap;
};
#endif  // WIDGET_H
