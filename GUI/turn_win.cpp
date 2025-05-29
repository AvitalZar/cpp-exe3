#include "turn_win.hpp"
#include <QString>

TurnWindow::TurnWindow(Player* player, QWidget* parent)
    : QWidget(parent), currentPlayer(player)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    nameLabel = new QLabel(QString::fromStdString(currentPlayer->name()), this);
    coinsLabel = new QLabel("Coins: " + QString::number(currentPlayer->getCoins()), this);

    actionButton = new QPushButton("Do Action", this);
    connect(actionButton, &QPushButton::clicked, this, &TurnWindow::onActionClicked);

    layout->addWidget(nameLabel);
    layout->addWidget(coinsLabel);
    layout->addWidget(actionButton);

    setLayout(layout);
}

void TurnWindow::onActionClicked() {
    currentPlayer->gather();
    emit turnEnded();
}
