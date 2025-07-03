#include "ctitlebar.h"

#include <qt_windows.h>

#include <QHBoxLayout>
#include <QWindow>
#pragma comment(lib, "user32.lib")

CTitleBar::CTitleBar(QWidget* parent) { Init(); }

void CTitleBar::Init()
{
    this->setStyleSheet("background-color:rgb(50,180,80)");
    m_pLogo = new QLabel(this);
    m_pLogo->setFixedSize(32, 32);

    m_pTitleTextLabel = new QLabel(this);
    m_pTitleTextLabel->setText(u8"无边框窗口");
    m_pTitleTextLabel->setFixedWidth(120);

    m_pSetBtn = new QPushButton(this);
    m_pSetBtn->setFixedSize(32, 32);

    m_pMinBtn = new QPushButton(this);
    m_pMinBtn->setFixedSize(32, 32);

    m_pMaxBtn = new QPushButton(this);
    m_pMaxBtn->setFixedSize(32, 32);

    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setFixedSize(32, 32);

    // 设置布局
    QHBoxLayout* pHlay = new QHBoxLayout(this);
    pHlay->addWidget(m_pLogo);
    pHlay->addSpacing(20);
    pHlay->addWidget(m_pTitleTextLabel);
    pHlay->addStretch();
    pHlay->addWidget(m_pSetBtn);
    pHlay->addWidget(m_pMinBtn);
    pHlay->addWidget(m_pMaxBtn);
    pHlay->addWidget(m_pCloseBtn);

    pHlay->setContentsMargins(5, 5, 5, 5);
}

// void CTitleBar::mousePressEvent(QMouseEvent* event)
// {
//     if (ReleaseCapture()) {
//         QWidget* pWindow = this->window();
//         if (pWindow->isTopLevel()) {
//             SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
//         }
//     }
//     // event->ignore();
// }

void CTitleBar::mousePressEvent(QMouseEvent* event)
{
    QWidget* pWindow = this->window();
    if (pWindow->isTopLevel()) {
        QWindow* windowHandle = pWindow->windowHandle();
        if (windowHandle) {
            windowHandle->startSystemMove();
        }
    }
    // event->ignore();
}
