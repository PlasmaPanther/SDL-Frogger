#include "Application.h"
#include "TimerModule.h"
#include "Input.h"
#include "States/SplashMenu.h"
#include "States/PlayState.h"
#include "CollisionManager.h"

Application* Application::s_Instance = nullptr;
SDL_Event Application::s_Event;

Application* Application::Instance() {

	if (s_Instance == nullptr) {
		s_Instance = new Application();
	}
	
	return s_Instance;
}

Application::Application() {
	m_Running = true;

	m_Graphics = Graphics::Instance();
	if (!m_Graphics->Initialized()) {
		m_Running = false;
	}

	TimerModule::UpdateDelta();

	//_StateMachine.addState(SplashMenu::GetInstance());
	_StateMachine.addState(PlayState::GetInstance());

}

Application::~Application() {

	_StateMachine.KillAllStates();

	m_Graphics->DestroyInstance();
	m_Graphics = nullptr;
}

void Application::DestroyInstance() {
	delete s_Instance;
	s_Instance = nullptr;
}

void Application::MainLoop() {
	while (m_Running)
	{

		TimerModule::UpdateDelta();

		while (SDL_PollEvent(&s_Event) != 0) {

			if (s_Event.type == SDL_QUIT) {
				m_Running = false;
			}
			
			switch (s_Event.window.event)
			{
			case SDL_WINDOWEVENT_MINIMIZED:
				while (SDL_WaitEvent(&s_Event))
				{
					if (s_Event.window.event == SDL_WINDOWEVENT_RESTORED)
					{
						break;
					}
				}
				break;
			}
			break;
		}

		Input::InputUpdate(s_Event);
		CollisionManager::Update();

		m_Graphics->Update();
		_StateMachine.Update();

		///////////////////Everything to render goes in between here/////////////////////////
		
		_StateMachine.Render();

		////////////////////////////////////////////////////////////////////////////////////i
		m_Graphics->Render();

		SDL_Delay(10);
	}
}

SDL_Event Application::GetEvent()
{
	return s_Event;
}
