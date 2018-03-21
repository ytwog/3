#ifndef FILES_H
#define FILES_H

#include <QDate>
#include <qvector.h>
#include <QTimeZone>


class files
{
public:
    files();
    files(QString _name, qint64 _size, QDateTime _date, short _attributes);
    QString getname();
    QString getdate();
    qint64 getsize();
    short getattr();
private:
    QString name;
    qint64 size;
    QDateTime date;
    short attributes; // = 0   | No attributes
};                    // += 1  | Read-only
                      // += 2  | System
                      // += 4  | Hidden
                      // += 8  | Archive
                      // += 16 | Directory


void addToVec(QVector<files> &Vec, files *Obj);

#endif // FILES_H
