#ifndef SCALE_H
#define SCALE_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QDebug>

enum Hint { BOX_PATTERN, THREE_NOTES, FOUR_NOTES };

class Scale
{
public:
    Scale(QString &name,  QList<int> &interval, Hint hint);

    QStringList getScaleNote(const QString &root);
    QString getName() const {return name;}
    QList<int> getInterval() const {return interval;}
    Hint getHint() const {return hint;}

private:
    QString name;
    QList<int> interval;
    Hint hint;
    QStringList noteList = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    QStringList notes;
};

inline QDebug operator<<(QDebug out, const Scale &scale)
{
    out.nospace() << "(" << scale.getName() << "," << scale.getInterval() << "," << scale.getHint() << ")";
    return out;
}

#endif // SCALE_H
