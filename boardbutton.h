#ifndef BOARDBUTTON_H
#define BOARDBUTTON_H

#include <QPushButton>
#include <QIcon>

#include <proto/common.pb.h>

enum class AnnotationType {
    kNone,
    kQuarterTriangle,
    kSmallSquare,
    kTriangle,
    kCircle,
    kSquare,
    kCross,
    kText,
};

struct Annotation {
    AnnotationType type = AnnotationType::kNone;
    QColor color = Qt::transparent;
    QString data = "";
};

class BoardButton : public QPushButton
{
    Q_OBJECT

public:

    static constexpr int kCellSize = 52;
    static constexpr int kCellHalfSize = kCellSize / 2;
    static constexpr int kStarPointSize = kCellSize / 10;

    static QPair<int,int> pointCoord(int r, int c) {
        return {
            kCellSize*c+kCellHalfSize,
            kCellSize*r+kCellHalfSize,
        };
    }

    BoardButton(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    void setState(openfoxwq::Color state);
    void setAnnotation(const Annotation &newAnnotation);
    void clearAnnotation();

    openfoxwq::Color getState() const;

    void setHoveredColor(const QColor &newHoveredColor);

signals:
    void pointHover();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    openfoxwq::Color m_state;
    Annotation m_annotation;
    QColor m_hoveredColor;

    static QPoint quarterTrianglePoints[3];
    static QIcon whiteStoneIcon();
    static QIcon blackStoneIcon();

    void drawAnnotation(QPainter& p, const Annotation& annotation);
};

#endif // BOARDBUTTON_H
