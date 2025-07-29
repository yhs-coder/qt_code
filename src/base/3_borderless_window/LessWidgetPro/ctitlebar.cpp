#include "ctitlebar.h"

#include <qt_windows.h>

#include <QDebug>
#include <QHBoxLayout>
#include <QWindow>

#pragma comment(lib, "user32.lib")

CTitleBar::CTitleBar(QWidget* parent)
{
    // 用于控制窗口关闭时对象销毁行为的属性设置
    // 窗口在关闭时会自动删除（销毁）该对象
    this->setAttribute(Qt::WA_DeleteOnClose);
    InitUI();

    connect(m_pMinBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
    connect(m_pMaxBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
    connect(m_pCloseBtn, &QPushButton::clicked, this, &CTitleBar::onClicked);
}

CTitleBar::~CTitleBar() { qDebug() << "auto delete CTitleBar..."; }

void CTitleBar::InitUI()
{
    // 禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    this->setFixedHeight(32 + 5 * 2);

    this->setStyleSheet("background-color: rgb(30, 30, 30); color: #CCCCCC;");

    m_pLogo = new QLabel(this);
    m_pLogo->setFixedSize(32, 32);
    m_pLogo->setStyleSheet(R"(
    QLabel {
        background-image: url(:/resource/title_icon.png);
        background-repeat: no-repeat;
        background-position: center;
        border: none;
        padding: 5px;
    }
    )");
    m_pTitleTextLabel = new QLabel(this);
    m_pTitleTextLabel->setText("无边框窗口");
    m_pTitleTextLabel->setFixedWidth(120);
    m_pTitleTextLabel->setStyleSheet(R"(
    QLabel {
        font-family: 'Microsoft YaHei';
        font-size: 16px;
        font-weight: 500;
        color: #E1E6F0;
        background-color: transparent; /* 透明背景更专业 */
        padding-left: 10px;
    })");
    QString buttonStyle = R"(
    QPushButton {
        background-color: transparent;
        border: none;
        padding: 5px;
        min-width: 32px;
        min-height: 32px;
    }
    QPushButton:hover {
        background-color: rgba(255, 255, 255, 0.1); /* 半透明悬停效果 */
        border-radius: 4px;
    }
    QPushButton:pressed {
        background-color: rgba(255, 255, 255, 0.15);
        padding-left: 6px;
        padding-top: 6px; /* 按下效果 */
    }
)";

    m_pSetBtn = new QPushButton(this);
    m_pSetBtn->setFixedSize(32, 32);
    m_pSetBtn->setStyleSheet(buttonStyle + R"(
    QPushButton {
        background-image: url(:/resource/set.svg);
        background-repeat: no-repeat;
        background-position: center;
    }
    QPushButton:hover {
        background-image: url(:/resource/set_hover.svg);
    }
    )");
    m_pMinBtn = new QPushButton(this);
    m_pMinBtn->setFixedSize(32, 32);
    m_pMinBtn->setStyleSheet(buttonStyle + R"(
    QPushButton {
        background-image: url(:/resource/min.svg);
        background-repeat: no-repeat;
        background-position: center;
    }
    QPushButton:hover {
        background-image: url(:/resource/min_hover.svg);
    }
    )");
    m_pMaxBtn = new QPushButton(this);
    m_pMaxBtn->setFixedSize(32, 32);
    m_pMaxBtn->setStyleSheet(buttonStyle + R"(
    QPushButton {
        background-image: url(:/resource/normal.svg);
        background-repeat: no-repeat;
        background-position: center;
    }
    QPushButton:hover {
        background-image: url(:/resource/normal_hover.svg);
        background-color: rgba(232, 17, 35, 0.2);
    }
    )");
    m_pCloseBtn = new QPushButton(this);
    m_pCloseBtn->setFixedSize(32, 32);
    m_pCloseBtn->setStyleSheet(buttonStyle + R"(
    QPushButton {
        background-image: url(:/resource/close.svg);
        background-repeat: no-repeat;
        background-position: center;
    }
    QPushButton:hover {
        background-image: url(:/resource/close_hover.svg);
        background-color: rgba(232, 17, 35, 0.2); /* 红色警示背景 */
    }
    )");
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
//     // 使用Windows系统原生的API
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
    // 使用qt自带的API
    QWidget* pWindow = this->window();
    if (pWindow->isWindow()) {
        QWindow* windowHandle = pWindow->windowHandle();
        if (windowHandle) {
            windowHandle->startSystemMove();
        }
    }
    // event->ignore();
}

void CTitleBar::mouseDoubleClickEvent(QMouseEvent* event) { emit m_pMaxBtn->clicked(); }

void CTitleBar::onClicked()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());
    QWidget*     pWindow = this->window();
    if (pButton == m_pMinBtn) {
        pWindow->showMinimized();
    } else if (pButton == m_pMaxBtn) {
        // 当前窗口最大化时，再次点击变为正常大小，否租为最大化
        if (pWindow->isMaximized()) {
            pWindow->showNormal();
            m_pMaxBtn->setStyleSheet(
                "QPushButton{background-image:url(:/resource/normal.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/resource/normal_hover.svg);border:none;}");
        } else {
            pWindow->showMaximized();
            m_pMaxBtn->setStyleSheet(
                "QPushButton{background-image:url(:/resource/max.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/resource/max_hover.svg);border:none;}");
        }
    } else if (pButton == m_pCloseBtn) {
        // 发射信号，父控件进行关闭窗口处理
        emit sig_close();
    }
}
