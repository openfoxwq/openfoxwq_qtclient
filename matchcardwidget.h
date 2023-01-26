#ifndef MATCHCARDWIDGET_H
#define MATCHCARDWIDGET_H

#include <QWidget>

#include <modelutils.h>
#include <broadcastroommodel.h>

namespace Ui {
class MatchCardWidget;
}

class MatchCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatchCardWidget(QWidget *parent = nullptr);
    ~MatchCardWidget();

    void setRoom(BroadcastRoom room, const ModelUtils& modelUtils);
    void setMainTime(int t);
    void setByoyomi(int p, int t);
    void setHandicap(int h, bool chineseRules);

    void setBlackTime(int t);
    void setBlackTimerPaused(bool value);
    void setBlackInByoyomi();
    void setBlackPeriodsLeft(int p);
    void setBlackCaptures(int c);

    void setWhiteTime(int t);
    void setWhiteTimerPaused(bool value);
    void setWhiteInByoyomi();
    void setWhitePeriodsLeft(int p);
    void setWhiteCaptures(int c);


signals:

private:
    Ui::MatchCardWidget *ui;

};

#endif // MATCHCARDWIDGET_H
