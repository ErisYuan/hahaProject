#include "datetype.h"

DateType::DateType()
{  
}
DateType::DateType(const QString &date)
{
    auto str = date.split("-");
    year = str[0].toInt();
    month = str[1].toInt();
    day = str[2].toInt();
}

int operator < (const DateType &a, const DateType &b) {
    if(a.year == b.year)
    {
        if(a.month == b.month)
            return a.day < b.day;
        else
            return a.month < b.month;

    }
    else return a.year < b.year;
}

QString DateType::toQString() const {
    return QString::number(year)+"-"+QString::number(month)+"-"+QString::number(day);
}
