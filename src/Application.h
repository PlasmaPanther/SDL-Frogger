#pragma once
#include "Graphics.h"
#include "States/StateMachine.h"

class Application
{
public:
	static Application* Instance();
	void DestroyInstance();
	
	void MainLoop();
	static SDL_Event GetEvent();

private:
	static Application* s_Instance;
	
	static SDL_Event s_Event;

	//==============Place your own classes here===============//

	Graphics* m_Graphics;

	StateMachine _StateMachine;

	//=======================================================//

	bool m_Running;

	Application();
	~Application();
};

