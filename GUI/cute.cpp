#include "cute.hpp"

int main(int argc, char *argv[]) {
	Game game;
	vector<coup::Player> players;

    QApplication app(argc, argv);

	MainWindow window(game,players);

    window.setFixedSize(300, 200);

    window.setWindowTitle("Coup : set players");
    window.show();

    return app.exec();
}