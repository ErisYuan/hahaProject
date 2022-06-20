#include "price.h"
#include "qdebug.h"

Price::Price()
{
}
Price::Price(const QList<QString> &list)
{
    auto it = list.begin();
    if(list.size() != 10) {
        qDebug() << "Exception at \"price.cpp\", constructor Price::Price(const QList<QString> &list)";
        return;
    }
    auto &str = *it;
    start=str.toFloat();
    it++;
    max=str.toFloat();
    it++;
    min=str.toFloat();
    it++;
    end=str.toFloat();
    it++;
    fluctuation1=str.toFloat();
    it++;
    flurate=str.toFloat();
    it++;
    amount=str.toFloat();
    it++;
    total=str.toFloat();
    it++;
    fluctuation2=str.toFloat();
    it++;
    exchange=str.toFloat();
    it++;
}
Price::Price(const QString &str)
    :Price(str.split(",", Qt::SkipEmptyParts))
{
}
QString Price::toQString() {
    return QString::number(start)+','+QString::number(max)+','+QString::number(min)
            +','+QString::number(end)+','+QString::number(fluctuation1)+','+QString::number(flurate)+','+
            QString::number(amount)+','+QString::number(total)+','+QString::number(fluctuation2)+','+QString::number(exchange);
}
