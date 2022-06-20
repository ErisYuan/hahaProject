#include "stockrecord.h"

StockRecord::StockRecord()
{

}

DateType StockRecord::getDate() const {return this->date;}
QString StockRecord::getName() const {return this->stockName;}
Price StockRecord::getPrice() const {return this->price;}

StockRecord::StockRecord(const QString & data)
{
   QStringList str = data.split(",", Qt::SkipEmptyParts);
   date = DateType(str[0]);
   stockName = str[1];
   str.pop_front();str.pop_front();
   price = Price(str);
}
StockRecord::StockRecord(const StockRecord &sr) {
    stockName = sr.stockName;
    date = sr.date;
    price = sr.price;
}
int operator < (const StockRecord &a, const StockRecord &b)
{
    if (a.stockName == b.stockName) {
        return a.date < b.date;
    }
    return a.stockName < b.stockName;
}
