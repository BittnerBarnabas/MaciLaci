#pragma once
#include <QObject>
#include <QLabel>
#include <QPixmap>

#include "Implementation/ImpTypes.h"

namespace View
{
	class gridLabel : public QLabel
	{
		const QString gridBorderStyle = "border: 1px solid black; ";
		Q_OBJECT
	public:
		explicit gridLabel(QWidget *parent, Implementation::player_t owner);
		void setIcon(Implementation::player_t ow); //!< Sets the icon of the gridLabel
	};
}