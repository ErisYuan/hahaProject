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
    QString Month = QString::number(month); if(Month.length() == 1) Month = "0"+Month;
    QString Day = QString::number(day); if(Day.length() == 1) Day = "0"+Day;

    return QString::number(year)+"-"+Month+"-"+Day;
}
