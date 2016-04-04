#include "GameView.h"

namespace View
{

	EVA_2_Beadando::EVA_2_Beadando(QWidget *parent)
		: QMainWindow(parent), impl(nullptr)
	{
		ui.setupUi(this);
		ui.pauseButton->setEnabled(false);
		createNewGame();
		connect(ui.actionOpen_new_map, SIGNAL(triggered()), this, SLOT(openNewMap()));
		connect(ui.openNewMapButton, SIGNAL(clicked()), this, SLOT(openNewMap()));
	}

	EVA_2_Beadando::~EVA_2_Beadando()
	{

	}

	void EVA_2_Beadando::createNewGame()
	{
		impl.reset();
		impl = std::make_unique<Implementation::MagicGameImpl>();
		connect(impl.get(), SIGNAL(updatedHunters()), this, SLOT(updateGameBoard()));
		connect(impl.get(), SIGNAL(updatedPlayer()), this, SLOT(updateGameBoard()));
		connect(impl.get(), SIGNAL(endGame(int)), this, SLOT(gameEnded(int)));
		connect(impl.get(), SIGNAL(elapsedTime(int)), this, SLOT(updateElapsedTimeLabel(int)));
		connect(impl.get(), SIGNAL(newGameStarted()), this, SLOT(newGameInit()));
		connect(impl.get(), SIGNAL(sendFoodToEat(int)), this, SLOT(updateFoodToEat(int)));
		connect(ui.pauseButton, SIGNAL(clicked()), impl.get(), SLOT(pauseGame()));
		connect(this, SIGNAL(startNewGame(QString)), impl.get(), SLOT(newGame(QString)));
		connect(this, SIGNAL(playerMoveRequest(Implementation::direction_t)), impl.get(), SLOT(movePlayer(Implementation::direction_t)));

	}

	void EVA_2_Beadando::newGameInit()
	{
		initGameBoard();
		drawObjectsToGrid();
		ui.pauseButton->setEnabled(true);
	}

	void EVA_2_Beadando::updateElapsedTimeLabel(int sec)
	{
		auto msecToTimeStr = [](int ms)
		{
			QString t;
			return t.append(QString::number(ms / 60)).append(':').append(QString::number(ms % 60));

		};
		ui.elapsedTimeDisplay->setText(msecToTimeStr(sec));
	}

	void EVA_2_Beadando::openNewMap() //!< Slot, opens the file dialog to browse maps to open
	{
        QString pathToDefaultMaps = "../Maps";
        if (QDir("./Maps").exists()) pathToDefaultMaps = "./Maps";
		QString p = QFileDialog::getOpenFileName(this, "Open a map", pathToDefaultMaps, "Map files (*.map)");
		if (p != QString("")) emit(startNewGame(p));
	}

	void EVA_2_Beadando::keyPressEvent(QKeyEvent * ev)
	{
		switch (ev->key())
		{
		case Qt::Key_W:
			emit(playerMoveRequest(Implementation::direction_t::UP));
			break;
		case Qt::Key_S:
			emit(playerMoveRequest(Implementation::direction_t::DOWN));
			break;
		case Qt::Key_D:
			emit(playerMoveRequest(Implementation::direction_t::RIGHT));
			break;
		case Qt::Key_A:
			emit(playerMoveRequest(Implementation::direction_t::LEFT));
			break;
		default:
			break;
		}
	}

	void EVA_2_Beadando::initGameBoard()
	{
		boardCont.clear();
		const auto& implBoard = impl->getBoardRepr();
		boardCont.resize(implBoard.boardSize);
		for (auto & row : boardCont)
		{
			row.resize(implBoard.boardSize);
		}

		for (int i = 0; i < implBoard.boardSize;++i)
		{
			for (int j = 0; j < implBoard.boardSize; ++j)
			{
				boardCont[i][j] = std::make_unique<gridLabel>(nullptr,implBoard.gameBoard[i][j]);
			}
		}
	}

	void EVA_2_Beadando::drawObjectsToGrid()
	{
		int siz = boardCont.size();
		for (int i = 0; i < siz; ++i)
		{
			for (int j = 0; j < siz; ++j)
			{
				ui.GameBoardGrid->addWidget(boardCont[i][j].get(),i,j);
			}
		}
	}

	void EVA_2_Beadando::updateGameBoard()
	{
		const auto& implBoard = impl->getBoardRepr();
		for (int i = 0; i < implBoard.boardSize; ++i)
		{
			for (int j = 0; j < implBoard.boardSize; ++j)
			{
				boardCont[i][j]->setIcon(implBoard.gameBoard[i][j]);
			}
		}
	}

	void EVA_2_Beadando::gameEnded(int result)
	{
		QString str;
		switch (result)
		{
		case 1:
			str = "You won!";
			break;
		case 0:
			str = "You lost!";
			break;
		default:
			break;
		}
		ui.pauseButton->setEnabled(false);
		updateGameBoard();
		QMessageBox winnerBox;
		winnerBox.setText(str);
		winnerBox.exec();
		boardCont.clear();
		createNewGame();
		
	}

	void EVA_2_Beadando::updateFoodToEat(int num)
	{
		ui.foodToEatDisplay->setText(QString::number(num));
	}

}
