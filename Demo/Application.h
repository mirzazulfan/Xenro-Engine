#ifndef APPLICATION_DEFINED
#define APPLICATION_DEFINED

#include <XenroEngine\Game.h>
#include <XenroEngine/LevelEditor.h>

class GameplayScreen;
class MainMenuScreen;
class OptionsScreen;
class PhysicsScreen;

class Application :public Xenro::Game
{
public:
	Application();
	~Application();

	//Called on initialization.
	virtual void onInit() override;

	//Used to add screens.
	virtual void addScreens() override;

	//Called upon exiting.
	virtual void onExit() override;

private:
	GameplayScreen* m_gameplayScreen;
	MainMenuScreen* m_mainMenuScreen;
	OptionsScreen* m_optionsScreen;
	PhysicsScreen* m_physicsScreen;
	Xenro::LevelEditor* m_levelEditor;
};

#endif //APPLICATION_DEFINED