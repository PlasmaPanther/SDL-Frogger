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

	static void Shutdown();

private:

	void Exit();

private:

	static Application* s_Instance;
	
	static SDL_Event s_Event;

	Graphics* m_Graphics;

	StateMachine _StateMachine;

	static inline bool s_Running;

	Application();
	~Application();
};

