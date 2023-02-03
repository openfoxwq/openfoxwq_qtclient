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

int BoardButton::cellSize() const {
    return std::min(width(), height());
}

int BoardButton::halfCellSize() const {
    return cellSize() / 2;
}

QVector<QPoint> BoardButton::quarterTrianglePoints() const {
    return {
        QPoint(halfCellSize(), halfCellSize()),
        QPoint(cellSize()-2, halfCellSize()),
        QPoint(halfCellSize(), cellSize()-2),
    };
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

    p.drawPixmap(0, 0, icon().pixmap(icon().actualSize(size())));

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
        p.drawConvexPolygon(quarterTrianglePoints());
        break;
    case AnnotationType::kSmallSquare:
        p.drawRect(cellSize()/4 + 2, cellSize()/4 + 2, halfCellSize() - 4, halfCellSize() - 4);
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
