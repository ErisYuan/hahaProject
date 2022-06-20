#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qcandlestickset.h>
#include<QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void CandleChart(QString,QDate);
private:
    void initChart(QString,QDate);         // 初始化绘制图表
    QList<QCandlestickSet *> getData();  // 获取需要绘制数据
    Ui::Widget *ui;
};
#endif // WIDGET_H
