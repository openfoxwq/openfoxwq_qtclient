#include "timeddecisiondialog.h"
#include "ui_timeddecisiondialog.h"

TimedDecisionDialog::TimedDecisionDialog(QWidget *parent, QString title, QString mainText, QString infoText, int timeSec) :
    QDialog(parent),
    ui(new Ui::TimedDecisionDialog)
{
    ui->setupUi(this);

    setModal(true);
    setWindowTitle(title);
    ui->mainTextLabel->setText(mainText);
    ui->informativeTextLabel->setText(infoText);
    ui->progressBar->setMaximum(timeSec);
    ui->progressBar->setValue(timeSec);

    connect(&m_timer, &QTimer::timeout, this, &TimedDecisionDialog::on_timer);
    m_timer.setSingleShot(false);
    m_timer.start(1000);
}

TimedDecisionDialog::~TimedDecisionDialog()
{
    delete ui;
}

void TimedDecisionDialog::on_acceptButton_clicked()
{
    accept();
}


void TimedDecisionDialog::on_refuseButton_clicked()
{
    reject();
}

void TimedDecisionDialog::on_timer() {
    const int newValue = ui->progressBar->value() - 1;
    if (newValue < 0) {
        reject();
    } else {
        ui->progressBar->setValue(newValue);
    }
}

