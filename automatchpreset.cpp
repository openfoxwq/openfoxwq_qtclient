#include "automatchpreset.h"

AutomatchPreset::AutomatchPreset()
{

}

int AutomatchPreset::id() const
{
    return m_id;
}

void AutomatchPreset::setId(int newId)
{
    m_id = newId;
}

const QString &AutomatchPreset::nameCn() const
{
    return m_nameCn;
}

void AutomatchPreset::setNameCn(const QString &newNameCn)
{
    m_nameCn = newNameCn;
}

const QString &AutomatchPreset::nameTc() const
{
    return m_nameTc;
}

void AutomatchPreset::setNameTc(const QString &newNameTc)
{
    m_nameTc = newNameTc;
}

const QString &AutomatchPreset::nameJap() const
{
    return m_nameJap;
}

void AutomatchPreset::setNameJap(const QString &newNameJap)
{
    m_nameJap = newNameJap;
}

const QString &AutomatchPreset::nameEng() const
{
    return m_nameEng;
}

void AutomatchPreset::setNameEng(const QString &newNameEng)
{
    m_nameEng = newNameEng;
}

const QString &AutomatchPreset::nameHan() const
{
    return m_nameHan;
}

void AutomatchPreset::setNameHan(const QString &newNameHan)
{
    m_nameHan = newNameHan;
}

int AutomatchPreset::boardSize() const
{
    return m_boardSize;
}

void AutomatchPreset::setBoardSize(int newBoardSize)
{
    m_boardSize = newBoardSize;
}

int AutomatchPreset::rule() const
{
    return m_rule;
}

void AutomatchPreset::setRule(int newRule)
{
    m_rule = newRule;
}

int AutomatchPreset::mainTimeSecs() const
{
    return m_mainTimeSecs;
}

void AutomatchPreset::setMainTimeSecs(int newMainTimeSecs)
{
    m_mainTimeSecs = newMainTimeSecs;
}

int AutomatchPreset::byoyomiTimeSecs() const
{
    return m_byoyomiTimeSecs;
}

void AutomatchPreset::setByoyomiTimeSecs(int newByoyomiTimeSecs)
{
    m_byoyomiTimeSecs = newByoyomiTimeSecs;
}

int AutomatchPreset::byotomiPeriods() const
{
    return m_byoyomiPeriods;
}

void AutomatchPreset::setByoyomiPeriods(int newByoyomiPeriods)
{
    m_byoyomiPeriods = newByoyomiPeriods;
}

void AutomatchPreset::read(const QJsonObject& json) {
    if (json.contains("field_id")) m_id = json["field_id"].toInt();
    if (json.contains("field_name_cn")) m_nameCn = json["field_name_cn"].toString();
    if (json.contains("field_name_tc")) m_nameTc = json["field_name_tc"].toString();
    if (json.contains("field_name_jap")) m_nameJap = json["field_name_jap"].toString();
    if (json.contains("field_name_eng")) m_nameEng = json["field_name_eng"].toString();
    if (json.contains("field_name_han")) m_nameHan = json["field_name_han"].toString();
    if (json.contains("board_size")) m_boardSize = json["board_size"].toInt();
    if (json.contains("chess_rule")) m_rule = json["chess_rule"].toInt();
    if (json.contains("jushi_time")) m_mainTimeSecs = json["jushi_time"].toInt();
    if (json.contains("dumiao_time")) m_byoyomiTimeSecs = json["dumiao_time"].toInt();
    if (json.contains("dumiao_num")) m_byoyomiPeriods = json["dumiao_num"].toInt();
}
