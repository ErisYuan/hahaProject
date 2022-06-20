#ifndef STOCKRECORD_H
#define STOCKRECORD_H
#include "datetype.h"
#include "price.h"
#include <QString>

class StockRecord
{
    QString stockName;
    DateType date;
    Price price;
public:
    QString getName() const;
    DateType getDate() const;
    Price getPrice() const;
    StockRecord();
    StockRecord(const QString &);
    StockRecord(const StockRecord &);

    StockRecord operator = (const StockRecord &rec) {
        stockName = rec.stockName;
        date = rec.date;
        price = rec.price;
        return *this;
    }

    friend int operator < (const StockRecord &a, const StockRecord &b);
};



#endif // STOCKRECORD_H
