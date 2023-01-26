#ifndef RANK_H
#define RANK_H

#include <QString>

class Rank
{
public:
    Rank();
    Rank(const Rank&) = default;
    Rank(Rank&&) = default;
    Rank& operator=(const Rank&) = default;
    Rank& operator=(Rank&&) = default;

    static Rank ofString(QString);

    int getValue() const { return m_value; }
    const QString& getType() const { return m_type; }
    bool isKyu() const { return m_type == "K"; }
    bool isDan() const { return m_type == "D"; }
    bool isPro() const { return m_type == "P"; }

    QString toString() const { return QString::number(m_value) + m_type; }

private:
    Rank(int value, QString type);

    int m_value;
    QString m_type;
};

#endif // RANK_H
