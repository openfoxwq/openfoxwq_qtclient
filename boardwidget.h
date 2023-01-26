#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QSoundEffect>
#include <boardbutton.h>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BoardWidget(QWidget *parent = nullptr, int boardSize = 19);
    ~BoardWidget();

    void paintEvent(QPaintEvent *) override;
    bool movePiece(int r, int c, PointState state);
    void setAnnotation(int r, int c, Annotation);
    PointState getPoint(int r, int c) const;
    void clearAnnotations();

    bool interactive() const;
    void setInteractive(bool newInteractive);
    void setSound(bool value);

signals:
    void pointClicked(int r, int c);

private:
    Ui::BoardWidget *ui;
    const int boardSize;
    QIcon blackStone, whiteStone;
    QSoundEffect placeStoneSound, captureSound;
    QVector<QVector<BoardButton*>> pointButtons;
    bool m_interactive = false;
    bool m_soundEnabled = false;
    QPair<int, int> m_lastPoint = {-1, -1};
    PointState m_lastState = PointState::kWhite;

    void drawBoardLines(QPainter&);

    using Point = QPair<int, int>;
    using Group = QVector<Point>;
    using PointSet = QSet<Point>;

    PointState getExtendedState(int r, int c, const QMap<Point, PointState> &additionalPoints);
    void collectGroup(PointState col, int r, int c, Group& group, PointSet& used, const QMap<Point, PointState> &additionalPoints);
    QMap<PointState, QVector<Group>> computeDeadGroups(const QMap<Point, PointState> &additionalPoints);
};

#endif // BOARDWIDGET_H
