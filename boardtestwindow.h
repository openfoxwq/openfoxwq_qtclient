#ifndef BOARDTESTWINDOW_H
#define BOARDTESTWINDOW_H

#include <QMainWindow>
#include <boardbutton.h>
#include <proto/common.pb.h>

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
};

#endif // BOARDTESTWINDOW_H
