#ifndef TUNING_H
#define TUNING_H

#include <QString>

#include "note.h"

class Tuning
{
public:
    Tuning(QString &name, QList<Note> &noteList);

    QString getName() const {return my_name;}
    QList<Note> getNoteList() const {return my_noteList;}

private:
    QString my_name;
    QList<Note> my_noteList;
};

inline QDebug operator<<(QDebug out, const Tuning &tuning)
{
    out.nospace() << "(" << tuning.getName() << "," << tuning.getNoteList() << ")";
    return out;
}

#endif // TUNING_H
