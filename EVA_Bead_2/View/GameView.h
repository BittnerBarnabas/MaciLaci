#pragma once

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <memory>

#include "Implementation/ImplGame.h"
#include "ui_eva_bead_2.h"
#include "ViewGridLabel.h"

namespace View
{

	class EVA_2_Beadando : public QMainWindow
	{
		using BoardContainer_t = std::vector<std::vector<std::unique_ptr<gridLabel>>>;

		Q_OBJECT;
	public:
		EVA_2_Beadando(QWidget *parent = nullptr);
		~EVA_2_Beadando();
		void createNewGame();

		public slots:
		void updateElapsedTimeLabel(int millisec);
		void openNewMap();
		void newGameInit();
		void updateGameBoard();
		void gameEnded(int result);
		void updateFoodToEat(int num);
		void togglePauseButton();

	signals:
		void startNewGame(QString path);
		void playerMoveRequest(Implementation::direction_t);

	private:
		Ui::EVA_Bead_2Class ui;
		std::unique_ptr<Implementation::MagicGameImpl> impl;
		BoardContainer_t boardCont;
		void initGameBoard(); 
		void drawObjectsToGrid();

	protected:
		void keyPressEvent(QKeyEvent *ev) override;
		
	};
}