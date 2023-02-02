#ifndef AUTOMATCHPRESET_H
#define AUTOMATCHPRESET_H

#include <QString>
#include <QJsonObject>

class AutomatchPreset
{
public:
    AutomatchPreset();

    int id() const;
    void setId(int newId);
    const QString &nameCn() const;
    void setNameCn(const QString &newNameCn);
    const QString &nameTc() const;
    void setNameTc(const QString &newNameTc);
    const QString &nameJap() const;
    void setNameJap(const QString &newNameJap);
    const QString &nameEng() const;
    void setNameEng(const QString &newNameEng);
    const QString &nameHan() const;
    void setNameHan(const QString &newNameHan);
    int boardSize() const;
    void setBoardSize(int newBoardSize);
    int rule() const;
    void setRule(int newRule);
    int mainTimeSecs() const;
    void setMainTimeSecs(int newMainTimeSecs);
    int byoyomiTimeSecs() const;
    void setByoyomiTimeSecs(int newByoyomiTimeSecs);
    int byotomiPeriods() const;
    void setByoyomiPeriods(int newByoyomiPeriods);

    void read(const QJsonObject& json);

private:
    int m_id; // field_id
    QString m_nameCn; // field_name_cn
    QString m_nameTc; // field_name_tc
    QString m_nameJap; // field_name_jap
    QString m_nameEng; // field_name_eng
    QString m_nameHan; // field_name_han
    int m_boardSize; // board_size
    int m_rule; // chess_rule
    int m_mainTimeSecs; // jushi_time
    int m_byoyomiTimeSecs; // dumiao_time
    int m_byoyomiPeriods; // dumiao_num
};

#endif // AUTOMATCHPRESET_H
