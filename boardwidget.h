#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QSet>
#include <boardbutton.h>
#include <proto/common.pb.h>

namespace Ui {
class BoardWidget;
}

class BoardWidget : public QWidget
{
    Q_OBJECT

public:
    static constexpr int kMaxCellSize = 52;

    explicit BoardWidget(QWidget *parent = nullptr, int boardSize = 19);
    ~BoardWidget();

    int boardSize() const { return m_boardSize; }
    void paintEvent(QPaintEvent *) override;
    bool movePiece(int r, int c, openfoxwq::Color state, int *captureCount = nullptr);
    openfoxwq::Color turn() const;
    void toggleTurn();
    void setAnnotation(int r, int c, Annotation);
    openfoxwq::Color getPoint(int r, int c) const;
    void clearAnnotations();

    bool interactive() const;
    void setInteractive(bool newInteractive);
    void toggleInteractive();

    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *event) override;

signals:
    void pointClicked(int r, int c, openfoxwq::Color state);

private:
    Ui::BoardWidget *ui;
    const int m_boardSize;
    QVector<QVector<BoardButton*>> pointButtons;
    bool m_interactive = false;
    QPair<int, int> m_lastPoint = {-1, -1};
    openfoxwq::Color m_lastState = openfoxwq::Color::COL_WHITE;
    QSet<QString> m_previousPositions;

    int cellSize() const;
    int halfCellSize() const;
    void drawBoardLines(QPainter&);

    using Point = QPair<int, int>;
    using Group = QVector<Point>;
    using PointSet = QSet<Point>;

    openfoxwq::Color getExtendedState(int r, int c, const QMap<Point, openfoxwq::Color> &additionalPoints);
    void collectGroup(openfoxwq::Color col, int r, int c, Group& group, PointSet& used, const QMap<Point, openfoxwq::Color> &additionalPoints);
    QMap<openfoxwq::Color, QVector<Group>> computeDeadGroups(const QMap<Point, openfoxwq::Color> &additionalPoints);
};

#endif // BOARDWIDGET_H
