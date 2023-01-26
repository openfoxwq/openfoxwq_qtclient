#ifndef BOARDTESTWINDOW_H
#define BOARDTESTWINDOW_H

#include <QMainWindow>
#include <boardbutton.h>

namespace Ui {
class BoardTestWindow;
}

class BoardTestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BoardTestWindow(QWidget *parent = nullptr);
    ~BoardTestWindow();

private:
    Ui::BoardTestWindow *ui;
    PointState m_curState = PointState::kBlack;
};

#endif // BOARDTESTWINDOW_H
