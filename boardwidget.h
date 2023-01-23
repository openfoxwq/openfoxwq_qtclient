#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QIcon>
#include <QSound>
#include <QPushButton>
#include <ui_boardwidget.h>

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    enum class PointState {
        kEmpty = 0,
        kBlack = 1,
        kWhite = -1,
    };
    explicit BoardWidget(QWidget *parent = nullptr, int boardSize = 19);
    ~BoardWidget();

    void paintEvent(QPaintEvent *) override;
    void setPoint(int r, int c, PointState state);
    PointState getPoint(int r, int c) const;

signals:
    void pointClicked(int r, int c);

private:
    Ui::BoardWidget *ui;
    const int boardSize;
    QIcon blackStone, whiteStone;
    QSound placeStone;
    QVector<QVector<PointState>> pointState;
    QVector<QVector<QPushButton*>> pointButtons;

    void drawBoardLines(QPainter&);
};

#endif // BOARDWIDGET_H
