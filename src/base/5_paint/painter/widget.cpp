#include "widget.h"

#include <QDebug>

#include "./ui_widget.h"
#include "paintwidget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initUI();

    // 关联信号槽
    void (QComboBox::*pCbo)(const QString &) = &QComboBox::activated;
    connect(ui->cboShape, pCbo, this, &Widget::shapeChange);

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
}

void Widget::shapeChange()
{
    int index = ui->cboShape->currentIndex();

    Shape shape = static_cast<Shape>(ui->cboShape->itemData(index).toInt());
    ui->paintWidget->setShape(shape);
    // qDebug() << ui->cboShape->itemData(index).toString();
    // qDebug() << ui->cboShape->currentText();
}
