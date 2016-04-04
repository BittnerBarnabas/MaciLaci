
#include "View/GameView.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	{
		QApplication a(argc, argv);
		View::EVA_2_Beadando w{};
		w.show();
		a.exec();
	}
	return 0;
}
