#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 1. 初始化列表控件

    // 1.1 共有4列，并添加列的名称
    ui->twStudent->setColumnCount(4);

    QStringList horizontalHeader;
    horizontalHeader << "姓名";
    horizontalHeader << "性别";
    horizontalHeader << "年龄";
    horizontalHeader << "籍贯";

    ui->twStudent->setHorizontalHeaderLabels(horizontalHeader);

    // 1.2 设置列的宽度
    // 先设置自适应宽度，再单独设置某一列的宽度规则
    ui->twStudent->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //
                                                                                   //
                                                                                   // 先自适应宽度
    // 然后，可以单独设置某一列根据内容调整宽度
    //    ui->twStudent->horizontalHeader()->setSectionResizeMode(0,
    // QHeaderView::ResizeToContents);
    // 或者，可以单独设置某一列为固定宽度
    //    ui->twStudent->horizontalHeader()->setSectionResizeMode(0,
    // QHeaderView::Fixed);
    //    ui->twStudent->setColumnWidth(0, 80);

    // 1.3 添加几行初始化数据
    appendOneRow("李雷",  "男", 12, "广东");
    appendOneRow("韩梅梅", "女", 11, "北京");
    appendOneRow("林涛",  "男", 13, "上海");

    // 2. 设置行表头是否显示
    // 首先根据在属性窗口中设置的属性，初始化复选框
    if (ui->twStudent->horizontalHeader()->isHidden()) {
        ui->cboHHeader->setChecked(false);
    } else {
        ui->cboHHeader->setChecked(true);
    }

    // 点击复选框时，显示或者隐藏行表头
    connect(ui->cboHHeader, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            ui->twStudent->horizontalHeader()->show();
        } else if (state == Qt::Unchecked) {
            ui->twStudent->horizontalHeader()->hide();
        }
    });

    // 3. 设置列表头是否显示
    // 首先根据在属性窗口中设置的属性，初始化复选框
    if (ui->twStudent->verticalHeader()->isHidden()) {
        ui->cboVHeader->setChecked(false);
    } else {
        ui->cboVHeader->setChecked(true);
    }

    // 点击复选框时，显示或者隐藏列表头
    connect(ui->cboVHeader, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            ui->twStudent->verticalHeader()->show();
        } else if (state == Qt::Unchecked) {
            ui->twStudent->verticalHeader()->hide();
        }
    });

    // 4. 交替显示行的背景色
    // 首先根据在属性窗口中设置的属性，初始化复选框
    if (ui->twStudent->alternatingRowColors()) {
        ui->cboAlternate->setChecked(true);
    } else {
        ui->cboAlternate->setChecked(false);
    }

    // 点击复选框时，使能或者禁能交替背景色
    connect(ui->cboAlternate, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            ui->twStudent->setAlternatingRowColors(true);
        } else if (state == Qt::Unchecked) {
            ui->twStudent->setAlternatingRowColors(false);
        }
    });

    // 5. 设置单元格是否可编辑
    // 首先根据在属性窗口中设置的属性，初始化复选按钮
    int trigger = ui->twStudent->editTriggers();

    if (trigger == QAbstractItemView::NoEditTriggers) {
        ui->cboEditCell->setChecked(false);
    } else {
        ui->cboEditCell->setChecked(true);
    }

    // 点击复选按钮时，使能或者禁能单元格编辑
    connect(ui->cboEditCell, &QCheckBox::stateChanged, this, [ = ](int state) {
        if (state == Qt::Checked) {
            // 当双击单元格/选中单元格然后单击/按下编辑键F2，都可以编辑单元格。
            ui->twStudent->setEditTriggers(QAbstractItemView::DoubleClicked |
                                           QAbstractItemView::SelectedClicked |
                                           QAbstractItemView::EditKeyPressed);
        } else if (state == Qt::Unchecked) {
            ui->twStudent->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    });

    // 6. 设置行选择还是单元格选择
    // 首先根据在属性窗口中设置的属性，初始化单选按钮的选中状态
    int selectionBehavior = ui->twStudent->selectionBehavior();

    if (selectionBehavior == QAbstractItemView::SelectItems) {
        ui->rbCell->setChecked(true);
    } else if (selectionBehavior == QAbstractItemView::SelectRows) {
        ui->rbRow->setChecked(true);
    }

    // 点击单选按钮时，使能单元格选中或者行选中
    mButtonGroupSelection = new QButtonGroup(this);
    mButtonGroupSelection->addButton(ui->rbCell, 0);
    mButtonGroupSelection->addButton(ui->rbRow,  1);
    connect(ui->rbCell,
            &QRadioButton::clicked,
            this,
            &Widget::onSelectionRadioButtonClicked);
    connect(ui->rbRow,
            &QRadioButton::clicked,
            this,
            &Widget::onSelectionRadioButtonClicked);

    // 7. 单元格点击时， 将对应行的数据显示到文本框
    connect(ui->twStudent,
            &QTableWidget::itemClicked,
            this,
            &Widget::onItemClicked);
}

Widget::~Widget()
{
    delete ui;
}

