#ifndef MATCHCARDWIDGET_H
#define MATCHCARDWIDGET_H

#include <QWidget>

#include <soundfx.h>
#include <modelutils.h>
#include <broadcastmodel.h>
#include <proto/common.pb.h>
#include <proto/play.pb.h>

namespace Ui {
class MatchCardWidget;
}

class MatchCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatchCardWidget(QWidget *parent = nullptr);
    ~MatchCardWidget();

    void setSfx(SoundFx *sfx);

    void setBroadcast(const openfoxwq::BroadcastInfo& broadcast, const ModelUtils& modelUtils);
    void setMatch(const openfoxwq::MatchStartEvent& matchStartEvent, const ModelUtils& modelUtils);

    void setMainTime(int t);
    void setByoyomi(int p, int t);
    void setHandicap(int h, bool chineseRules);

    void setBlackTime(int t);
    void setBlackTimerPaused(bool value);
    void setBlackPeriodsLeft(int p);
    void setBlackCaptures(int c);
    void setBlackCountdown(bool value);

    void setWhiteTime(int t);
    void setWhiteTimerPaused(bool value);
    void setWhitePeriodsLeft(int p);
    void setWhiteCaptures(int c);
    void setWhiteCountdown(bool value);


signals:

private:
    Ui::MatchCardWidget *ui;
    SoundFx* m_sfx;

};

#endif // MATCHCARDWIDGET_H
