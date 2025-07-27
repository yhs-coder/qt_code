#include "widget.h"

#include <QColorDialog>
#include <QDebug>

#include "./ui_widget.h"
#include "paintwidget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();

    // 关联信号槽
    void (QComboBox::*pCbo)(const QString &) = &QComboBox::activated;
    void (QSpinBox::*pSb)(int)               = &QSpinBox::valueChanged;
    // 图形形状
    connect(ui->cboShape, pCbo, this, &Widget::shapeChange);
    // 画笔宽度
    connect(ui->sbPenWidth, pSb, this, &Widget::penChange);
    // 画笔颜色
    connect(ui->btnPenColor, &QPushButton::clicked, this, &Widget::onBbtnPenColorClicked);
    // 画笔样式
    connect(ui->cboPenStyle, pCbo, this, &Widget::penChange);
    // 画笔连接
    connect(ui->cboPenJoin, pCbo, this, &Widget::penChange);
    // 画笔末端
    connect(ui->cboPenCap, pCbo, this, &Widget::penChange);

    // 画刷颜色
    connect(ui->btnBrushColor, &QPushButton::clicked, this, &Widget::onBtnBrushColorClicked);
    connect(ui->cboBrushStyle, pCbo, this, &Widget::brushChange);

    // 抗锯齿
    connect(ui->chkAntialiasing, &QCheckBox::toggled, this, &Widget::antialiasChange);

    // 默认绘制当前选项的形状
    shapeChange();
}

Widget::~Widget() { delete ui; }

void Widget::initUI()
{
    // 1. 形状
    ui->cboShape->addItem("Point", static_cast<int>(_Point));
    ui->cboShape->addItem("Line", static_cast<int>(_Line));

    ui->cboShape->addItem("Rectangle", static_cast<int>(_Rect));
    ui->cboShape->addItem("Rounded Rectangle", static_cast<int>(_RoundedRect));
    ui->cboShape->addItem("Ellipse", static_cast<int>(_Ellipse));

    ui->cboShape->addItem("Arc", static_cast<int>(_Arc));
    ui->cboShape->addItem("Pie", static_cast<int>(_Pie));
    ui->cboShape->addItem("Chord", static_cast<int>(_Chord));

    ui->cboShape->addItem("Polyline", static_cast<int>(_Polyline));
    ui->cboShape->addItem("Polygon", static_cast<int>(_Polygon));

    ui->cboShape->addItem("Path", static_cast<int>(_Path));

    ui->cboShape->addItem("Text", static_cast<int>(_Text));
    ui->cboShape->addItem("Pixmap", static_cast<int>(_Pixmap));

    // 2. 画笔宽度范围
    ui->sbPenWidth->setRange(1, 10);

    // 3. 画笔样式
    // 3.1 线型
    ui->cboPenStyle->addItem("Solid", static_cast<int>(Qt::SolidLine));  // 实线
    ui->cboPenStyle->addItem("Dash", static_cast<int>(Qt::DashLine));    // 虚线
    ui->cboPenStyle->addItem("Dot", static_cast<int>(Qt::DotLine));      // 点画线
    ui->cboPenStyle->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
    ui->cboPenStyle->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));
    ui->cboPenStyle->addItem("None", static_cast<int>(Qt::NoPen));

    // 3.2线的端点样式
    ui->cboPenCap->addItem("Flat", static_cast<int>(Qt::FlatCap));
    ui->cboPenCap->addItem("Square", static_cast<int>(Qt::SquareCap));
    ui->cboPenCap->addItem("Round", static_cast<int>(Qt::RoundCap));

    // 3.3 连接-两根线的连接处的样式
    ui->cboPenJoin->addItem("Miter", static_cast<int>(Qt::MiterJoin));
    ui->cboPenJoin->addItem("Bevel", static_cast<int>(Qt::BevelJoin));
    ui->cboPenJoin->addItem("Round", static_cast<int>(Qt::RoundJoin));

    // 4. 画刷样式
    // tr() 是一个 Qt 提供的国际化（i18n）宏，全称是 “translate”。
    // 它的作用是把括号里的字符串标记为“需要翻译的文本”，在运行时根据当前语言环境自动返回对应语言的翻译版本。
    ui->cboBrushStyle->addItem(tr("Linear Gradient"), static_cast<int>(Qt::LinearGradientPattern));
    ui->cboBrushStyle->addItem(tr("Radial Gradient"), static_cast<int>(Qt::RadialGradientPattern));
    ui->cboBrushStyle->addItem(tr("Conical Gradient"), static_cast<int>(Qt::ConicalGradientPattern));
    ui->cboBrushStyle->addItem(tr("Texture"), static_cast<int>(Qt::TexturePattern));
    ui->cboBrushStyle->addItem(tr("Solid"), static_cast<int>(Qt::SolidPattern));
    ui->cboBrushStyle->addItem(tr("Horizontal"), static_cast<int>(Qt::HorPattern));
    ui->cboBrushStyle->addItem(tr("Vertical"), static_cast<int>(Qt::VerPattern));
    ui->cboBrushStyle->addItem(tr("Cross"), static_cast<int>(Qt::CrossPattern));
    ui->cboBrushStyle->addItem(tr("Backward Diagonal"), static_cast<int>(Qt::BDiagPattern));
    ui->cboBrushStyle->addItem(tr("Forward Diagonal"), static_cast<int>(Qt::FDiagPattern));
    ui->cboBrushStyle->addItem(tr("Diagonal Cross"), static_cast<int>(Qt::DiagCrossPattern));
    ui->cboBrushStyle->addItem(tr("Dense 1"), static_cast<int>(Qt::Dense1Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 2"), static_cast<int>(Qt::Dense2Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 3"), static_cast<int>(Qt::Dense3Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 4"), static_cast<int>(Qt::Dense4Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 5"), static_cast<int>(Qt::Dense5Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 6"), static_cast<int>(Qt::Dense6Pattern));
    ui->cboBrushStyle->addItem(tr("Dense 7"), static_cast<int>(Qt::Dense7Pattern));
    ui->cboBrushStyle->addItem(tr("None"), static_cast<int>(Qt::NoBrush));

    // 6.初始化画笔颜色
    // 回显画笔颜色
    QPalette pal = ui->btnPenColor->palette();
    pal.setColor(QPalette::Button, QColor(255, 0, 0));
    ui->btnPenColor->setPalette(pal);
    ui->btnPenColor->setAutoFillBackground(true);
    ui->btnPenColor->setFlat(true);

    // 7. 初始化画刷设置
    pal = ui->btnBrushColor->palette();
    pal.setColor(QPalette::Button, QColor(80, 200, 150));
    ui->btnBrushColor->setPalette(pal);
    ui->btnBrushColor->setAutoFillBackground(true);
    ui->btnBrushColor->setFlat(true);

    penChange();
    brushChange();
}

void Widget::shapeChange()
{
    int index = ui->cboShape->currentIndex();

    Shape shape = static_cast<Shape>(ui->cboShape->itemData(index).toInt());
    ui->paintWidget->setShape(shape);
    // qDebug() << ui->cboShape->itemData(index).toString();
    // qDebug() << ui->cboShape->currentText();
}

void Widget::penChange()
{
    // 获取画笔宽度
    int width = ui->sbPenWidth->value();

    // 获取画笔颜色
    QPalette pal   = ui->btnPenColor->palette();
    QColor   color = pal.color(QPalette::Button);

    int          styleIndex = ui->cboPenStyle->currentIndex();
    Qt::PenStyle style      = (Qt::PenStyle)ui->cboPenStyle->itemData(styleIndex).toInt();

    int              joinIndex = ui->cboPenJoin->currentIndex();
    Qt::PenJoinStyle join      = (Qt::PenJoinStyle)ui->cboPenJoin->itemData(joinIndex).toInt();

    int             capIndex = ui->cboPenCap->currentIndex();
    Qt::PenCapStyle cap      = (Qt::PenCapStyle)ui->cboPenCap->itemData(capIndex).toInt();

    ui->paintWidget->setPen(QPen(color, width, style, cap, join));
}

void Widget::onBbtnPenColorClicked()
{
    // 弹出模态颜色窗口，用于设置颜色
    QColor color = QColorDialog::getColor(QColor(255, 0, 0), this, "画笔颜色");
    // 如果用户取消选择颜色对话框，则无效
    if (!color.isValid()) {
        return;
    }

    // 回显画笔颜色
    // 获取调色板
    QPalette pal = ui->btnPenColor->palette();
    // 将指定颜色渲染在按钮上
    pal.setColor(QPalette::Button, color);
    // 将配置好的调色板设置回按钮中
    ui->btnPenColor->setPalette(pal);
    ui->btnPenColor->setAutoFillBackground(true);
    // ui->btnPenColor->setFlat(true);

    penChange();
}

void Widget::onBtnBrushColorClicked()
{
    // 弹出模态颜色窗口，用于设置颜色
    QColor color = QColorDialog::getColor(QColor(255, 0, 0), this, "画笔颜色");
    // 如果用户取消选择颜色对话框，则无效
    if (!color.isValid()) {
        return;
    }

    // 回显画刷颜色
    QPalette pal = ui->btnBrushColor->palette();
    pal.setColor(QPalette::Button, color);
    ui->btnBrushColor->setPalette(pal);
    ui->btnBrushColor->setAutoFillBackground(true);
    ui->btnBrushColor->setFlat(true);

    brushChange();
}

void Widget::brushChange()
{
    // 获取画刷颜色
    QPalette pal   = ui->btnBrushColor->palette();
    QColor   color = pal.color(QPalette::Button);

    // 获取画刷样式
    int            index = ui->cboBrushStyle->currentIndex();
    Qt::BrushStyle style = (Qt::BrushStyle)ui->cboBrushStyle->itemData(index).toInt();

    // 设置画刷

    // 线性渐变
    if (style == Qt::LinearGradientPattern) {
        // 定义了渐变的起点(0, 50)和终点坐标(100,50)
        // 这是一条 水平方向 的渐变线，从左到右。
        QLinearGradient linearGradient(0, 50, 100, 50);
        // 0% - 20%: 从white逐渐变为color
        // 20% - 100% : 从color逐渐变为黑色
        linearGradient.setColorAt(0.0, Qt::white);
        linearGradient.setColorAt(0.2, color);
        linearGradient.setColorAt(1.0, Qt::black);
        ui->paintWidget->setBrush(linearGradient);

    } else if (style == Qt::RadialGradientPattern) {
        // 线径向渐变
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::white);
        radialGradient.setColorAt(0.2, color);
        radialGradient.setColorAt(1.0, Qt::black);
        ui->paintWidget->setBrush(radialGradient);

    } else if (style == Qt::ConicalGradientPattern) {
        // 锥形渐变
        // QConicalGradient(qreal cx, qreal cy, qreal startAngle)
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::white);
        conicalGradient.setColorAt(0.2, color);
        conicalGradient.setColorAt(1.0, Qt::black);
        ui->paintWidget->setBrush(conicalGradient);

    } else if (style == Qt::TexturePattern) {
        // 纹理样式
        ui->paintWidget->setBrush(QBrush(QPixmap(":/images/brick.png")));
    } else {
        // 其他
        ui->paintWidget->setBrush(QBrush(color, style));
    }
}

void Widget::antialiasChange() { ui->paintWidget->setAntialias(ui->chkAntialiasing->isChecked()); }
