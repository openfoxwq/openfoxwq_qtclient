#include "soundfx.h"

#include <QString>
#include <QDebug>

/*
 * Common:
 *   101-2052: match/broadcast bell
 *   102-2052: coins
 *   103-2052: play stone and capture many
 *   104-2052: play stone and capture some
 *   105-2052: play stone and capture one
 *   106-2052: ???
 *   107-2052: ???
 *   108-2052: ???
 *   109-2052: ???
 *   110-2052: win bell
 *   111-2052: ???
 *   112-2052: play stone
 *   113-2052: ???
 *   114-2052: ???
 *   115-2052: ???
 *   116-2052: ???
 *   117-2052: ???
 *   118-2052: ???
 *   119-2052: ???
 *   120-2052: ???
 *
 * Localized:
 *   101-2052: 1
 *   102-2052: 2
 *   103-2052: 3
 *   104-2052: 4
 *   105-2052: 5
 *   106-2052: 6
 *   107-2052: 7
 *   108-2052: 8
 *   109-2052: 9
 *   110-2052: 10
 *   111-2052: Someone invites you to play.
 *   112-2052: Last byoyomi.
 *   113-2052: Two byoyomi left.
 *   114-2052: Upgraded successfully. Congratulations.
 *   115-2052: Start to play.
 *   116-2052: Byoyomi now starts.
 *   117-2052: Lose by timeout.
 *
 */

SoundFx::SoundFx(QLocale::Language language)
{
    m_playStone.setSource(QUrl::fromLocalFile(":/assets/sound/common/112-2052.wav"));
    m_playStoneCaptureOne.setSource(QUrl::fromLocalFile(":/assets/sound/common/105-2052.wav"));
    m_playStoneCaptureSome.setSource(QUrl::fromLocalFile(":/assets/sound/common/104-2052.wav"));
    m_playStoneCaptureMany.setSource(QUrl::fromLocalFile(":/assets/sound/common/103-2052.wav"));
    m_winBell.setSource(QUrl::fromLocalFile(":/assets/sound/common/110-2052.wav"));

    setLanguage(language);
}

const QLocale::Language &SoundFx::language() const
{
    return m_language;
}

void SoundFx::setLanguage(const QLocale::Language &newLanguage)
{
    m_language = newLanguage;
    switch (m_language) {
    case QLocale::Language::English:
        loadLocalized("en");
        break;
    case QLocale::Language::Japanese:
        loadLocalized("jp");
        break;
    case QLocale::Language::Korean:
        loadLocalized("kr");
        break;
    default:
        qDebug() << "Unsupported language: " << m_language;
        break;
    }
}

void SoundFx::loadLocalized(QString code) {
    m_startToPlay.setSource(QUrl::fromLocalFile(QString(":/assets/sound/%1/115-2052.wav").arg(code)));
    m_byoyomiStarts.setSource(QUrl::fromLocalFile (QString(":/assets/sound/%1/116-2052.wav").arg(code)));
    m_twoByoyomiLeft.setSource(QUrl::fromLocalFile(QString(":/assets/sound/%1/113-2052.wav").arg(code)));
    m_lastByoyomi.setSource(QUrl::fromLocalFile(QString(":/assets/sound/%1/112-2052.wav").arg(code)));
    for (int i = 1; i <= 10; ++i) {
        m_countdown[i].setSource(QUrl::fromLocalFile(QString(":/assets/sound/%1/1%2-2052.wav").arg(code).arg(i, 2, 10, QChar('0'))));
    }
}

void SoundFx::playStone() { m_playStone.play(); }
void SoundFx::playStoneCaptureOne() { m_playStoneCaptureOne.play(); }
void SoundFx::playStoneCaptureSome() { m_playStoneCaptureSome.play(); }
void SoundFx::playStoneCaptureMany() { m_playStoneCaptureMany.play(); }
void SoundFx::winBell(){ m_winBell.play(); }

void SoundFx::startToPlay(){ m_startToPlay.play(); }
void SoundFx::byoyomiStarts(){ m_byoyomiStarts.play(); }
void SoundFx::twoByoyomiLeft(){ m_twoByoyomiLeft.play(); }
void SoundFx::lastByoyomi(){ m_lastByoyomi.play(); }
void SoundFx::countdown(int n) { m_countdown[n].play(); }
