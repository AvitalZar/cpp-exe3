//tchykzr@gmail.com
#include "main_win.hpp"

MainWindow::MainWindow(Game &g, vector<Player*>& p, QWidget *parent)
    : QMainWindow(parent), game(g), players(p)
{
    add_player = new QPushButton("Add a player", this);
	connect(add_player, &QPushButton::clicked,
            this, &MainWindow::showInputLine);
	central = new QWidget(this);
    layout = new QVBoxLayout(central);

	name_line = new QLineEdit(this);
	name_line->setPlaceholderText("Name: ");
	layout->addWidget(name_line);
	name_line->hide();

	setRolesButtons();

	

    layout->addWidget(add_player);

	playerList = new QListWidget(this);
	layout->addWidget(playerList);

	startButton = new QPushButton("Play", this);
	layout->addWidget(startButton);
	connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);

    central->setLayout(layout);
    setCentralWidget(central);
    
}

void MainWindow::createNewPlayer(PlayerFactory factory) {
	QString name = name_line->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Missing Name", "You should insert a name");
        return;
    }

    try {
        players.emplace_back(new Player(factory(game,name.toStdString())));
        qDebug() << "a player named " << name << "added";
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
		return;
    }

    name_line->hide();
	keep_roles->hide();
	playerList->addItem(name);
}

void MainWindow::startGame() {
	if (players.empty()) return;

    turnWin = new TurnWindow(players[findTurn()],players);
    connect(turnWin, &TurnWindow::turnEnded, this, &MainWindow::showNextTurn);

    turnWin->show();
    this->hide();
}

void MainWindow::showNextTurn() {
	turnWin->hide();
    delete turnWin;

    turnWin = new TurnWindow(players[findTurn()],players);
    connect(turnWin, &TurnWindow::turnEnded, this, &MainWindow::showNextTurn);
    turnWin->show();
}

void MainWindow::setRolesButtons() {
	keep_roles = new QWidget(this);
	roles = new QHBoxLayout(keep_roles);
	tafkidim[0] = new QPushButton("Governor", this);
	connect(tafkidim[0], &QPushButton::clicked, [this]() {
    createNewPlayer([](coup::Game& g, const std::string& n) { return Governor(g, n); });
});

	tafkidim[1] = new QPushButton("Spy", this);
	connect(tafkidim[1], &QPushButton::clicked, [this]() {
    createNewPlayer([](coup::Game& g, const std::string& n) { return Spy(g, n); });
});
	tafkidim[2] = new QPushButton("Baron", this);
	connect(tafkidim[2], &QPushButton::clicked, [this]() {
    createNewPlayer([](coup::Game& g, const std::string& n) { return Baron(g, n); });
});
	tafkidim[3] = new QPushButton("Judge", this);
	connect(tafkidim[3], &QPushButton::clicked, [this]() {
    createNewPlayer([](coup::Game& g, const std::string& n) { return Judge(g, n); });
});
	tafkidim[4] = new QPushButton("General", this);
	connect(tafkidim[4], &QPushButton::clicked, [this]() {
    createNewPlayer([](coup::Game& g, const std::string& n) { return General(g, n); });
});
	tafkidim[5] = new QPushButton("Merchant", this);
	connect(tafkidim[5], &QPushButton::clicked, [this]() {
    createNewPlayer([](coup::Game& g, const std::string& n) { return Merchant(g, n); });
});
	for(int i = 0; i < 6; i++){
		roles->addWidget(tafkidim[i]);
	}
	layout->addWidget(keep_roles);
	keep_roles->hide();
	
}

void MainWindow::showInputLine() {
	name_line->clear();
    name_line->show();
	keep_roles->show();
}

MainWindow::~MainWindow(){
	delete add_player;
	delete central;
	delete layout;
	delete name_line;
	delete playerList;
	delete tafkidim;
	delete roles;
	delete keep_roles;

	delete startButton;
	delete turnWin;
	
}

int MainWindow::findTurn(){
	for(unsigned int i = 0; i < players.size(); i++){
		if(players[i]->name() == game.turn())
			return i;
	}
	return -1;
}