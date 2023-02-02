#include "playerinfodialog.h"
#include "ui_playerinfodialog.h"


PlayerInfoDialog::PlayerInfoDialog(QWidget *parent, const openfoxwq::GetPlayerInfoResponse& playerInfo, const ModelUtils& modelUtils) :
    QDialog(parent),
    ui(new Ui::PlayerInfoDialog)
{
    ui->setupUi(this);
    ui->currentRoomsTable->setHorizontalHeaderLabels(QStringList{"Activity", "Room"});

    ui->usernameLabel->setText(QString::fromStdString(playerInfo.register_info().name()));
    ui->nameLabel->setText(QString::fromStdString(playerInfo.register_info().name_native()));
    if (playerInfo.register_info().has_country()) {
        openfoxwq::Country country = playerInfo.register_info().country();
        ui->countryFlagLabel->setPixmap(modelUtils.flagForCountry(country).pixmap(32,32));
        ui->locationClubLabel->setText(ModelUtils::countryString(country));
    }
    ui->ratingWrStaminaLabel->setText(QString("%1 / %2 / %3")
                .arg(playerInfo.overall_results().rating())
                .arg(playerInfo.overall_results().wr())
                .arg(playerInfo.overall_results().stamina())
    );
    ui->foxCoinsLabel->setText(QString::number(playerInfo.foxcoin()));

    const auto [rankNumber, rankType] = ModelUtils::rankNumberTypeString(playerInfo.rank());
    ui->rankNumberLabel->setText(rankNumber);
    ui->rankTypeLabel->setText(rankType);

    for (int i = 0; i < playerInfo.results_size(); ++i) {
        const QString labelText = QString("%1 W / %2 L")
                                             .arg(playerInfo.results(i).wins())
                                             .arg(playerInfo.results(i).losses());
        switch (playerInfo.results(i).type()) {
        case openfoxwq::GetPlayerInfoResponse_ResultsType::GetPlayerInfoResponse_ResultsType_OVERALL:
            ui->overallResultsLabel->setText(labelText);
            break;
        case openfoxwq::GetPlayerInfoResponse_ResultsType::GetPlayerInfoResponse_ResultsType_RANKED:
            ui->rankedResultsLabel->setText(labelText);
            break;
        case openfoxwq::GetPlayerInfoResponse_ResultsType::GetPlayerInfoResponse_ResultsType_FREE:
            ui->freeResultsLabel->setText(labelText);
            break;
        case openfoxwq::GetPlayerInfoResponse_ResultsType::GetPlayerInfoResponse_ResultsType_CURRENT:
            ui->currentResultsLabel->setText(labelText);
            ui->recentRecordCurrentWinsLabel->setText(QString::number(playerInfo.results(i).wins()) + " W");
            ui->recentRecordCurrentLossesLabel->setText(QString::number(playerInfo.results(i).losses()) + " L");
            break;
        default:
            // shrug
            break;
        }
    }

    QString summaryStr = "<html><head/><body><p>";
    for (const char c : playerInfo.recent_record().streak()) {
        switch (c) {
        case '+':
            summaryStr += "<span style=\" font-size:24pt; color:#21da59;\">O</span>";
            break;
        case '-':
            summaryStr += "<span style=\" font-size:24pt; color:#dd292b;\">X</span>";
            break;
        }
    }
    summaryStr += "</p></body></html>";
    ui->recentRecordSummaryLabel->setText(summaryStr);

    ui->currentRoomsTable->setRowCount(playerInfo.rooms().rooms_size());
    for (int i = 0; i < playerInfo.rooms().rooms_size(); ++i) {
        const auto& room = playerInfo.rooms().rooms(i);
        const QString activity = (room.unknown_field_2() == 1) ? "Watching" : "Playing";
        const QString id = ModelUtils::roomIdString(room.id());
        ui->currentRoomsTable->setItem(i, 0, new QTableWidgetItem(activity));
        ui->currentRoomsTable->setItem(i, 1, new QTableWidgetItem(id));
        m_roomIds.push_back(room.id());
    }
}

PlayerInfoDialog::~PlayerInfoDialog()
{
    delete ui;
}

void PlayerInfoDialog::on_closeButton_clicked()
{
    close();
}


void PlayerInfoDialog::on_currentRoomsTable_cellDoubleClicked(int row, int /* column */)
{
    emit roomClicked(m_roomIds[row]);
}

