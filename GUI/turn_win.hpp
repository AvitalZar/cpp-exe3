#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "roles/player.hpp"

using namespace coup;

class TurnWindow : public QWidget {
    Q_OBJECT

public:
    explicit TurnWindow(Player* player, QWidget* parent = nullptr);

signals:
    void turnEnded();

private slots:
    void onActionClicked();

private:
    Player* currentPlayer;
    QLabel* nameLabel;
    QLabel* coinsLabel;
    QPushButton* actionButton;
};
