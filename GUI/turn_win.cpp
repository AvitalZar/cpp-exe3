//tchykzr@gmail.com
#include "turn_win.hpp"
#include <QString>
#include <QMessageBox>
#include <QInputDialog>

TurnWindow::TurnWindow(Player* player, std::vector<Player*>& allPlayers, QWidget* parent)
    : QWidget(parent), currentPlayer(player), players(allPlayers)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // שמות וסטטוס
    QVBoxLayout* infoLayout = new QVBoxLayout;
    nameLabel = new QLabel(QString::fromStdString(currentPlayer->name()), this);
    coinsLabel = new QLabel("Coins: " + QString::number(currentPlayer->getCoins()), this);
    infoLayout->addWidget(nameLabel);
    infoLayout->addWidget(coinsLabel);

    // פעולות רגילות
    regularActionsWidget = new QWidget(this);
    regularLayout = new QVBoxLayout(regularActionsWidget);
    QStringList regularNames = {"Gather", "Tax", "Bribe", "Arrest", "Sanction", "Coup"};
    for (int i = 0; i < 6; i++) {
        regularButtons[i] = new QPushButton(regularNames[i], this);
        regularLayout->addWidget(regularButtons[i]);
        connect(regularButtons[i], &QPushButton::clicked, this, &TurnWindow::onRegularActionClicked);
    }

    // פעולות מיוחדות
    specialActionsWidget = new QWidget(this);
    specialLayout = new QVBoxLayout(specialActionsWidget);

    undoButton = new QPushButton("Undo", this);
    peekButton = new QPushButton("Peek", this);
    preventArrestButton = new QPushButton("Prevent Arrest", this);
    investButton = new QPushButton("Invest", this);

    specialLayout->addWidget(undoButton);
    specialLayout->addWidget(peekButton);
    specialLayout->addWidget(preventArrestButton);
    specialLayout->addWidget(investButton);

    connect(undoButton, &QPushButton::clicked, this, &TurnWindow::onSpecialActionClicked);
    connect(peekButton, &QPushButton::clicked, this, &TurnWindow::onSpecialActionClicked);
    connect(preventArrestButton, &QPushButton::clicked, this, &TurnWindow::onSpecialActionClicked);
    connect(investButton, &QPushButton::clicked, this, &TurnWindow::onInvestClicked);

    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(regularActionsWidget);
    mainLayout->addWidget(specialActionsWidget);
    setLayout(mainLayout);
}

TurnWindow::~TurnWindow() {
	delete nameLabel;
    delete coinsLabel;

    // פעולות רגילות
    delete regularActionsWidget;
    delete regularLayout;
	for(int i = 0; i < 6; i++){
		delete regularButtons[i];
	}
    // פעולות מיוחדות
    delete specialActionsWidget;
    delete specialLayout;
    delete peekButton;
    delete undoButton;
    delete preventArrestButton;
    delete investButton;

}

void TurnWindow::onRegularActionClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString actionName = btn->text();

    try {
        if (actionName == "Gather") {
            currentPlayer->gather();
        }
        else if (actionName == "Tax") {
            currentPlayer->tax();
        }
        else if (actionName == "Bribe") {
            currentPlayer->bribe();
        }
        else if (actionName == "Arrest") {
            Player* target = selectTargetPlayer();
            if (!target) return;
            currentPlayer->arrest(*target);
        }
        else if (actionName == "Sanction") {
            Player* target = selectTargetPlayer();
            if (!target) return;
            currentPlayer->sanction(*target);
        }
        else if (actionName == "Coup") {
            Player* target = selectTargetPlayer();
            if (!target) return;
            currentPlayer->coup(*target);
        }
        else {
            QMessageBox::warning(this, "Error", "Unknown action: " + actionName);
            return;
        }

        QMessageBox::information(this, "Success", "Action " + actionName + " executed.");
        emit turnEnded();

    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

Player* TurnWindow::selectTargetPlayer() {
    QStringList names;
    for (auto p : players) {
        names << QString::fromStdString(p->name());  // כולל את עצמך
    }
    bool ok;
    QString chosenName = QInputDialog::getItem(this, "Select Player", "Choose a player:", names, 0, false, &ok);
    if (!ok || chosenName.isEmpty())
        return nullptr;

    for (auto p : players) {
        if (QString::fromStdString(p->name()) == chosenName)
            return p;
    }
    return nullptr;
}

void TurnWindow::onSpecialActionClicked() {
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString actionName = btn->text();

    Player* target = selectTargetPlayer();
    if (!target) return; // בוטל

    try {
        if (actionName == "Undo") {
            currentPlayer->undo(*target);
        }
        else if (actionName == "Peek") {
            currentPlayer->peekCoins(*target);
        }
        else if (actionName == "Prevent Arrest") {
            currentPlayer->prevent_arrest(*target);
        }
        else {
            QMessageBox::warning(this, "Error", "Unknown special action: " + actionName);
            return;
        }

        QMessageBox::information(this, "Success", "Special action " + actionName + " executed.");
        emit turnEnded();

    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void TurnWindow::onInvestClicked() {
    try {
        currentPlayer->invest();
        QMessageBox::information(this, "Success", "Invest executed.");
        emit turnEnded();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}
