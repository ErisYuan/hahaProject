#ifndef DATETYPE_H
#define DATETYPE_H
#include <QString>
#include <QList>

struct DateType
{
    int year, month, day;
public:
    DateType();
    DateType(const QString &);

    friend int operator < (const DateType &a, const DateType &b);
    QString toQString () const;
};

#endif // DATETYPE_H
