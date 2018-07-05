#include <QCoreApplication>

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

#include "note.h"
#include "scale.h"
#include "tuning.h"

QByteArray readJsonFile(QFile &file)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();

    return jsonData;
}

QList<Tuning> tuningJasonList(QByteArray &jasonData)
{
    QList<Tuning> tuningList;

    QJsonDocument tuningDocument = QJsonDocument::fromJson(jasonData);
    QJsonObject tuningObject = tuningDocument.object();

    QJsonValue value = tuningObject.value("Tuning");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue &v, array)
    {
        QList<Note> noteList;
        QString tuningName = v.toObject().value("name").toString();
        QJsonArray array2 = v.toObject().value("notes").toArray();
        foreach (const QJsonValue &v2, array2)
        {
            Note n (v2.toObject().value("note").toString(), v2.toObject().value("octave").toInt());
            noteList.append(n);
        }
        tuningList.append(Tuning(tuningName, noteList));
    }
    return tuningList;
}

QList<Scale> scaleJsonData(QByteArray &jasonData)
{
    QList<Scale> scaleList;

    QJsonDocument scaleDocument = QJsonDocument::fromJson(jasonData);
    QJsonObject scaleObject = scaleDocument.object();

    QJsonValue scaleValue = scaleObject.value("Scale");
    QJsonArray intervalArray = scaleValue.toArray();
    foreach (const QJsonValue &v, intervalArray)
    {
        QList<int> interval;
        QString name = v.toObject().value("name").toString();
        QJsonArray array2 = v.toObject().value("interval").toArray();
        foreach (const QJsonValue &v2, array2)
        {
            interval.append(v2.toInt());
        }
        QString hint = v.toObject().value("hint").toString();
        Hint myHint;
        if (hint == "BOX_PATTERN")
            myHint = BOX_PATTERN;
        if (hint == "THREE_NOTES")
            myHint = THREE_NOTES;
        if (hint == "FOUR_NOTES")
            myHint = FOUR_NOTES;
        scaleList.append(Scale (name, interval, myHint));
    }
    return scaleList;
}

// Template function for printing two different QList<Tuning> and QList<scale>
template <typename T>
void printOut(const T &list)
{
    for (const auto &t : list)
        qDebug() << t;
    qDebug() << endl;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile tuning(":/tuning/tuning.json");
    QByteArray tuningData = readJsonFile(tuning);
    QList<Tuning> tuningList = tuningJasonList(tuningData);
    printOut(tuningList);

    QFile scale(":/tuning/scale.json");
    QByteArray scaleData = readJsonFile(scale);
    QList<Scale> scaleList = scaleJsonData(scaleData);
    printOut(scaleList);

    return a.exec();
}
