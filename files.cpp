#include "files.h"

files::files()
{
    name = "";
    size = 0;
    date = QDateTime(QDate(2000, 1, 1), QTime(0, 0), QTimeZone());
    attributes = 0;
}



QString files::getdate()
{
    return date.toString();
}

QString files::getname()
{
    return name;
}

short files::getattr()
{
    return attributes;
}

qint64 files::getsize()
{
    return size;
}

files::files(QString _name, qint64 _size, QDateTime _date, short _attributes)
{
    name = _name;
    size = _size;
    date = _date;
    attributes =  _attributes;
}



void addToVec(QVector<files> &Vec, files *Obj)
{
    Vec.append(*Obj);
}
