#pragma once
#include <vector>

#define NO_CURRENT_SCREEN_INDEX -1

namespace Xenro{


	class Game;
	class IScreen;

class ScreenList
{
public:
	ScreenList(Game* game);
	~ScreenList();

	IScreen* moveNext();
	IScreen* movePrevious();

	void setScreen(int nextScreen);
	void addScreen(IScreen* newScreen);

	void destroyScreen();
	void destroyScreen(int screen);

	IScreen* getCurrScreen();

protected:
	std::vector<IScreen*> m_screens;
	int m_currScreenIndex = NO_CURRENT_SCREEN_INDEX;
	Game* m_game;
};

}