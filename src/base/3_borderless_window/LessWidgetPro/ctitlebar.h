#ifndef CTITLEBAR_H
#define CTITLEBAR_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class CTitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit CTitleBar(QWidget* parent = nullptr);
    ~CTitleBar();

private:
    void InitUI();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;

private slots:
    void onClicked();

signals:
    void sig_close();

private:
    QLabel* m_pLogo;            // logo
    QLabel* m_pTitleTextLabel;  // 窗口标题

    QPushButton* m_pSetBtn;    // 设置按钮
    QPushButton* m_pMinBtn;    // 最小化按钮
    QPushButton* m_pMaxBtn;    // 最大化按钮
    QPushButton* m_pCloseBtn;  // 关闭按钮
};

#endif  // CTITLEBAR_H
