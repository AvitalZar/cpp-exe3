//tchykzr@gmail.com
#include <QApplication>
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>

#include "roles/player.hpp"
#include "roles/headers/baron.hpp"
#include "roles/headers/general.hpp"
#include "roles/headers/governor.hpp"
#include "roles/headers/judge.hpp"
#include "roles/headers/merchant.hpp"
#include "roles/headers/spy.hpp"
#include "game.hpp"
#include <functional>
#include "turn_win.hpp"

using namespace coup;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Game& g, vector<Player*>& p, QWidget *parent = nullptr);

	~MainWindow();

private:
    Game& game;
	vector<Player*>& players;

	QPushButton *add_player;
	QWidget *central;
	QVBoxLayout *layout;
	QLineEdit *name_line;
	QListWidget *playerList;
	QPushButton *tafkidim[6];
	QHBoxLayout *roles;
	QWidget *keep_roles;

	QPushButton* startButton;
	TurnWindow* turnWin;

	using PlayerFactory = std::function<Player*(Game&, const std::string)>;
	int findTurn();


private slots:
	void showInputLine();
	void createNewPlayer(PlayerFactory factory);
	void startGame();
	void showNextTurn();
	
	void setRolesButtons();
};
