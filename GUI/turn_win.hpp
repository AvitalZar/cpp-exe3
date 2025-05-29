//tchykzr@gmail.com
#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QInputDialog>
#include <vector>
#include <functional>
#include "roles/player.hpp"

using namespace coup;

class TurnWindow : public QWidget {
    Q_OBJECT

public:
    explicit TurnWindow(Player* player, std::vector<Player*>& allPlayers, QWidget* parent = nullptr);

	~TurnWindow();

signals:
    void turnEnded();

private slots:
    void onRegularActionClicked();
    void onSpecialActionClicked();
    void onInvestClicked();

private:
    Player* currentPlayer;
    std::vector<Player*>& players;  // כל השחקנים במשחק
    QLabel* nameLabel;
    QLabel* coinsLabel;

    // פעולות רגילות
    QWidget* regularActionsWidget;
    QVBoxLayout* regularLayout;
    QPushButton* regularButtons[6];

    // פעולות מיוחדות
    QWidget* specialActionsWidget;
    QVBoxLayout* specialLayout;
    QPushButton* peekButton;
    QPushButton* undoButton;
    QPushButton* preventArrestButton;
    QPushButton* investButton;

    void performAction(std::function<void()> action);
    Player* selectTargetPlayer();
};
