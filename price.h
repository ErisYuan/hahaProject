#ifndef PRICE_H
#define PRICE_H
#include<QString>
#include<QList>
struct Price
{
    float start,max,min,end,fluctuation1,flurate,amount,total,fluctuation2,exchange;
public:
    Price();
    Price(const QString &str);
    Price(const QList<QString>& list);

    QString toQString();
};

#endif // PRICE_H
