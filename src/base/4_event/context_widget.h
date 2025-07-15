#ifndef CONTEXT_WIDGET_H
#define CONTEXT_WIDGET_H

#include <QAction>
#include <QWidget>

class ContextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContextWidget(QWidget* parent = nullptr);

private slots:
    void slotAction();

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    QAction* m_cut;
    QAction* m_copy;
    QAction* m_paste;
    QAction* m_toUpper;
    QAction* m_toLower;
    QAction* m_hide;
};

#endif  // CONTEXT_WIDGET_H
