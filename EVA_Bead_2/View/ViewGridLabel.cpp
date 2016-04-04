#include "ViewGridLabel.h"

namespace View
{
	gridLabel::gridLabel(QWidget *parent /*= nullptr*/, Implementation::player_t ow) : QLabel(parent)
	{
		setFixedHeight(35);
		setFixedWidth(35);
		setIcon(ow);
		setStyleSheet(gridBorderStyle);
	}
	
	void gridLabel::setIcon(Implementation::player_t ow)
	{
		QPixmap Icon;
		switch (ow)
		{
		case Implementation::player_t::MaciLaci:
			Icon = QPixmap(":/EVA_Bead_2/Resources/Icons/bear_icon.png");
			break;
		case Implementation::player_t::Tree:
			Icon = QPixmap(":/EVA_Bead_2/Resources/Icons/tree_icon.png");
			break;
		case Implementation::player_t::Hunter:
			Icon = QPixmap(":/EVA_Bead_2/Resources/Icons/hunter_icon.jpg");
			break;
		case Implementation::player_t::InHunterRange:
			Icon = QPixmap(":/EVA_Bead_2/Resources/Icons/hunter_area_icon.png");
			break;
		case Implementation::player_t::Food:
			Icon = QPixmap(":/EVA_Bead_2/Resources/Icons/food_icon.png");
			break;
		default:
			break;
		}
        if(!Icon.isNull()) 
        {
            setPixmap(Icon.scaled(35, 35));
        }
        else
        {
            setPixmap(QPixmap());
        }
	}
}