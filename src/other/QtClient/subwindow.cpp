#include "subwindow.h"

#include "ui_subwindow.h"

SubWindow::SubWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SubWindow) {
    ui->setupUi(this);
    // 创建饼图系列
    QPieSeries *series = new QPieSeries();

    // 添加切片数据
    series->append("SQL Injection", 30);  // 假设 SQL 注入攻击占 30%
    series->append("XSS Attack", 40);     // XSS 攻击占 40%
    series->append("DoS Attack", 30);     // DoS 攻击占 30%

    // 创建饼图
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTheme(QChart::ChartThemeBlue);  // 设置图表主题

    // 创建图表视图并设置偏好的大小
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(300, 300);

    // 设置饼图的美化
    for (int i = 0; i < series->count(); ++i) {
        QPieSlice *slice = series->slices().at(i);
        QColor color = slice->color();   // 获取当前切片的颜色
        color.setAlpha(200);             // 设置半透明
        slice->setBrush(color);          // 设置切片的填充颜色
        slice->setPen(QPen(Qt::NoPen));  // 移除边框
    }

    // 设置图表的标签和百分比显示
    chart->setTitle("Attack Types Distribution");
    chart->legend()->setVisible(true);
    series->setLabelsVisible(true);
    series->setPieSize(0.6);     // 设置饼图的半径占比
    series->setHoleSize(0.6);    // 设置饼图的中心孔径占比
    series->setStartAngle(180);  // 设置饼图的起始角度

    // 创建布局并添加图表视图
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    layout->setContentsMargins(0, 0, 0, 0);

    // 设置窗口标题和大小
    setWindowTitle("Qt Pie Chart Example");
    resize(400, 400);
}

SubWindow::~SubWindow() {
    delete ui;
}
