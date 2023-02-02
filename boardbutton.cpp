#include "boardbutton.h"

#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

QIcon BoardButton::whiteStoneIcon() {
    static QIcon whiteStone(":/assets/whiteStone.png");
    return whiteStone;
}

QIcon BoardButton::blackStoneIcon() {
    static QIcon blackStone(":/assets/blackStone.png");
    return blackStone;
}

QPoint BoardButton::quarterTrianglePoints[3] = {
    QPoint(kCellHalfSize, kCellHalfSize),
    QPoint(kCellSize-2, kCellHalfSize),
    QPoint(kCellHalfSize, kCellSize-2),
};

BoardButton::BoardButton(QWidget* parent) :
    QPushButton(parent),
    m_state(openfoxwq::Color::COL_NONE),
    m_annotation(Annotation{}),
    m_hoveredColor(Qt::transparent)
{
    setIcon(QIcon());
    setStyleSheet(QString("QPushButton {border: 0px;}"));
    setFlat(true);
    setFocusPolicy(Qt::NoFocus);
    setContentsMargins(0,0,0,0);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
}

void BoardButton::setState(openfoxwq::Color state) {
    m_state = state;
    switch (m_state) {
    case openfoxwq::Color::COL_NONE:
        setIcon(QIcon());
        break;
    case openfoxwq::Color::COL_BLACK:
        setIcon(blackStoneIcon());
        break;
    case openfoxwq::Color::COL_WHITE:
        setIcon(whiteStoneIcon());
        break;
    }
}

openfoxwq::Color BoardButton::getState() const {
    return m_state;
}

void BoardButton::setAnnotation(const Annotation &newAnnotation)
{
    m_annotation = newAnnotation;
    repaint();
}

void BoardButton::clearAnnotation() {
    m_annotation.type = AnnotationType::kNone;
    repaint();
}

void BoardButton::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);

    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

    p.drawPixmap(0, 0, icon().pixmap(icon().actualSize(QSize(kCellSize,kCellSize))));

    drawAnnotation(p, m_annotation);

    if (opt.state & QStyle::State_MouseOver) {
        drawAnnotation(p, Annotation{AnnotationType::kSmallSquare, m_hoveredColor, ""});
    }
}

void BoardButton::drawAnnotation(QPainter& p, const Annotation& annotation) {
    p.setPen(annotation.color);
    p.setBrush(annotation.color);

    switch (annotation.type) {
    case AnnotationType::kNone:
        break;
    case AnnotationType::kQuarterTriangle:
        p.drawConvexPolygon(quarterTrianglePoints, 3);
        break;
    case AnnotationType::kSmallSquare:
        p.drawRect(kCellSize/4 + 2, kCellSize/4 + 2, kCellHalfSize - 4, kCellHalfSize - 4);
        break;
    case AnnotationType::kTriangle:
        // TODO implement
        break;
    case AnnotationType::kCircle:
        // TODO implement
        break;
    case AnnotationType::kSquare:
        // TODO implement
        break;
    case AnnotationType::kCross:
        // TODO implement
        break;
    case AnnotationType::kText:
        // TODO implement
        break;
    }
}

void BoardButton::setHoveredColor(const QColor &newHoveredColor)
{
    m_hoveredColor = newHoveredColor;
}

void BoardButton::mouseMoveEvent(QMouseEvent *event) {
    if (event->type() == QEvent::MouseMove) {
        emit pointHover();
    }
}
