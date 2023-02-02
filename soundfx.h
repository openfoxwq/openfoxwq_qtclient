#ifndef SOUNDFX_H
#define SOUNDFX_H

#include <QSoundEffect>
#include <QLocale>

class SoundFx
{
public:
    SoundFx(QLocale::Language lang);

    const QLocale::Language &language() const;
    void setLanguage(const QLocale::Language &newLanguage);

    void playStone();
    void playStoneCaptureOne();
    void playStoneCaptureSome();
    void playStoneCaptureMany();
    void winBell();

    void startToPlay();
    void byoyomiStarts();
    void twoByoyomiLeft();
    void lastByoyomi();
    void countdown(int d);

private:
    QLocale::Language m_language;

    QSoundEffect m_playStone;
    QSoundEffect m_playStoneCaptureOne;
    QSoundEffect m_playStoneCaptureSome;
    QSoundEffect m_playStoneCaptureMany;
    QSoundEffect m_winBell;

    QSoundEffect m_startToPlay;
    QSoundEffect m_byoyomiStarts;
    QSoundEffect m_twoByoyomiLeft;
    QSoundEffect m_lastByoyomi;
    QSoundEffect m_countdown[11];

    void loadLocalized(QString code);
};

#endif // SOUNDFX_H
