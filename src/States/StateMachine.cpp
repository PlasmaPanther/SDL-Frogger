#include "StateMachine.h"
std::vector<GameState*> StateMachine::m_GameStateVector;

void StateMachine::addState(GameState* state) {
	m_GameStateVector.push_back(state);
	m_GameStateVector.back()->onEnter();
}

void StateMachine::killState() {
	if (!m_GameStateVector.empty()) {
		if (m_GameStateVector.back()->onExit())
		{ 
		    m_GameStateVector.pop_back();
		}
	}
}

void StateMachine::Render()
{
	if (!m_GameStateVector.empty())
	{ 
		m_GameStateVector.back()->Render();
	}
}

void StateMachine::Update()
{
	if (!m_GameStateVector.empty()) 
	{ 
		m_GameStateVector.back()->Update();
	}
}

void StateMachine::switchState(GameState* state) {
	if (!m_GameStateVector.empty()) {

		m_GameStateVector.back()->onExit();
		m_GameStateVector.pop_back();
		
	}
	m_GameStateVector.push_back(state);
	m_GameStateVector.back()->onEnter();

}

void StateMachine::KillAllStates() {
	if (!m_GameStateVector.empty()) {
		
		m_GameStateVector.back()->onExit();
		m_GameStateVector.pop_back();

		m_GameStateVector.clear(); //Kills every stored state
		m_GameStateVector.shrink_to_fit(); // Sets capacity back to 0
		
		printf("vector cleared\n");
	}

}