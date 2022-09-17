#include <algorithm>
#include <fstream>
#include <iostream>

#include "Frog.h"
#include "Turtle.h"
#include "../Input.h"
#include "../CollisionManager.h"
#include "../TimerModule.h"
#include "../States/StateMachine.h"
#include "Levels/LevelManager.h"

void Frog::Init(Vector2 _pos)
{
	m_Position = _pos;
	m_StartingPosition = _pos;

	m_AnimatedFrogTexture.LoadAnimation("frogger_sprites.png", m_StartingPosition, 32, 24, 0, Vector2(1.5f, 1.5f));
	m_FrogTexture.LoadClippedTexture("frogger_sprites.png", 0, 365, m_StartingPosition, 23, 17, Vector2(1.35f, 1.5f));

	m_HomeTextures.resize(5);
	m_IsHome.fill(false);

	for (int i = 0; i < m_HomeTextures.size(); ++i) {
		m_HomeTextures[i].LoadClippedTexture("frogger_sprites.png", 107, 234, Vector2(35 + (i * 170), 66), 18, 17, Vector2(2.35f, 2.0f));
	}
	
	m_FrogLivesTextures.resize(2);

	for (int i = 0; i < m_FrogLivesTextures.size(); ++i) {
		m_FrogLivesTextures[i].first.LoadClippedTexture("frogger_sprites.png", 0, 365, Vector2(5 + (i * 30), 565), 23, 17, Vector2(1.0f, 0.9f));
		m_FrogLivesTextures[i].second = true; //set render flag to true
	}

	m_TimerBox.Place(Vector2(400, 580), Vector2(300, 20));

	//will be used to show remaining time and other messages
	m_BlackBox.Place(Vector2(310, 305), Vector2(140, 25));

	m_BlackBoxText.Load("Emulogic.ttf", 20, "Time", Colors::RED);

	m_FrogStatus = Status::UP; //will be used to render different frog textures

	m_Velocity = { 0.0f, 0.0f };

	m_Score = 0;

	m_FrogLives = 2;

	m_TimeRemaining = 60.0f;

	m_BlackBoxTimer = 0.0f;
	m_BlackBoxMaxTime = 5.0f;

	m_BlackBoxRenderFlag = false;
	m_Dead = false; //this is used when the frog is out of lifes'

	CollisionManager::AddCollider(&m_FrogTexture, "player");
}

void Frog::Update()
{
	//Boundary Check

	//Left side
	if (m_FrogTexture.GetRect().x <= 0.0f || m_AnimatedFrogTexture.GetRect().x <= 0.0f) {

		m_FrogTexture.GetRect().x = 0.0f;
		m_AnimatedFrogTexture.GetRect().x = 0.0f;
	}

	//Right side
	if (m_FrogTexture.GetRect().x + m_FrogTexture.GetRect().w >= 800.0f || m_AnimatedFrogTexture.GetRect().x + m_AnimatedFrogTexture.GetRect().w >= 800.0f) {
		
		m_FrogTexture.GetRect().x = 800.0f - m_FrogTexture.GetRect().w;
		m_AnimatedFrogTexture.GetRect().x = 800.0f - m_AnimatedFrogTexture.GetRect().w;
	}

	//Bottom side
	if (m_FrogTexture.GetRect().y > 530.0f || m_AnimatedFrogTexture.GetRect().y > 530.0f) {

		m_FrogTexture.GetRect().y = 530.0f;
		m_AnimatedFrogTexture.GetRect().y = 530.0f;
	}
	//==================

	//=========Collision Check==========
	if (CollisionManager::CheckGroupCollision("player", ("short_logs"))) {

		m_FrogTexture.Move(Vector2(40.0f, 0.0f) * TimerModule::GetDelta());
		m_AnimatedFrogTexture.Move(Vector2(40.0f, 0.0f) * TimerModule::GetDelta());

	}
	
	if (CollisionManager::CheckGroupCollision("player", "medium_logs")) {

		m_FrogTexture.Move(Vector2(65.0f, 0.0f) * TimerModule::GetDelta());
		m_AnimatedFrogTexture.Move(Vector2(65.0f, 0.0f) * TimerModule::GetDelta());

	}
	
	if (CollisionManager::CheckGroupCollision("player", "long_logs")) {

		m_FrogTexture.Move(Vector2(80.0f, 0.0f) * TimerModule::GetDelta());
		m_AnimatedFrogTexture.Move(Vector2(80.0f, 0.0f) * TimerModule::GetDelta());

	}
	
	if (CollisionManager::CheckGroupCollision("player", "turtles")) {

		m_FrogTexture.Move(Vector2(-65.0f, 0.0f) * TimerModule::GetDelta());
		m_AnimatedFrogTexture.Move(Vector2(-65.0f, 0.0f) * TimerModule::GetDelta());

	}

	if (CollisionManager::CheckGroupCollision("player", "enviorment")) {

		m_FrogStatus = Status::DEAD;

		m_Drown.PlaySFX("frogger-plunk.wav", 0, -1);

	}
	
	if (CollisionManager::CheckGroupCollision("player", "vehicles")) {

		m_FrogStatus = Status::DEAD;

		m_RunOver.PlaySFX("frogger-squash.wav", 0, -1);

	}
	//================================

	for (int i = 0; i < 5; ++i) {

		if (CollisionManager::CheckGroupCollision("player", "home" + std::to_string(i))) {

			if (m_IsHome[i]) { //check to see if a frog is in its home

				m_FrogStatus = Status::DEAD; 

				m_Drown.PlaySFX("frogger-plunk.wav", 0, -1);

				break; //exit the loop
			}
			
			m_FrogTexture.GetRect().x = m_StartingPosition.x;
			m_FrogTexture.GetRect().y = m_StartingPosition.y;

			m_AnimatedFrogTexture.GetRect().x = m_StartingPosition.x;
			m_AnimatedFrogTexture.GetRect().y = m_StartingPosition.y;

			m_IsHome[i] = true;

			m_Score += 50;
			m_Score += m_TimeRemaining * 10.0f;

			m_TimerBox.GetRect().x = 400;
			m_TimerBox.GetRect().w = 300;

			m_BlackBoxRenderFlag = true;

			int TimeRemaining = m_TimeRemaining; //avoid printing decimals
			m_BlackBoxText.ChangeText("Time " + std::to_string(TimeRemaining), Colors::RED);

			m_TimeRemaining = 60.0f;
		}
		
	}

	if (std::all_of(m_IsHome.begin(), m_IsHome.end(), [](bool v) {return v; })) { //find if all the frogs have arrived home
		m_IsHome.fill(false); //if they have then stop rendering them so it looks like the level has been reset
		//this will change when I feel like implementing more levels

		m_BlackBoxRenderFlag = true;

		m_BlackBoxText.ChangeText("Start", Colors::RED);
		m_BlackBox.GetRect().w = 105;

	}

	if (m_FrogStatus != Status::DEAD && !m_Dead) {

		if (Input::KeyPressed(SDL_SCANCODE_W)) {
			m_FrogStatus = Status::UP;
			m_Score += 10;

			m_Velocity = { 0.0f, -38.3f };

			m_FrogTexture.Move(m_Velocity);
			m_AnimatedFrogTexture.Move(m_Velocity);

			m_Hop.PlaySFX("frogger-hop.wav", 0, -1);
		}

		if (Input::KeyPressed(SDL_SCANCODE_S)) {
			m_FrogStatus = Status::DOWN;

			m_Velocity = { 0.0f, 38.3f };

			m_FrogTexture.Move(m_Velocity);
			m_AnimatedFrogTexture.Move(m_Velocity);

			m_Hop.PlaySFX("frogger-hop.wav", 0, -1);
		}

		if (Input::KeyPressed(SDL_SCANCODE_A)) {
			m_FrogStatus = Status::LEFT;

			m_Velocity = { -30.0f, 0.0f };
			
			m_FrogTexture.Move(m_Velocity);
			m_AnimatedFrogTexture.Move(m_Velocity);

			m_Hop.PlaySFX("frogger-hop.wav", 0, -1);
		}

		if (Input::KeyPressed(SDL_SCANCODE_D)) {
			m_FrogStatus = Status::RIGHT;

			m_Velocity = { 30.0f, 0.0f };
			
			m_FrogTexture.Move(m_Velocity);
			m_AnimatedFrogTexture.Move(m_Velocity);

			m_Hop.PlaySFX("frogger-hop.wav", 0, -1);
		}
	}

	if (m_FrogStatus == Status::DEAD) {

		m_FrogTexture.GetRect().x = m_StartingPosition.x;
		m_FrogTexture.GetRect().y = m_StartingPosition.y;

		if (m_AnimatedFrogTexture.GetCurrentFrame() >= 7) {
			
			m_FrogStatus = Status::UP;
			m_AnimatedFrogTexture.ResetAnimation();

			m_AnimatedFrogTexture.GetRect().x = m_StartingPosition.x;
			m_AnimatedFrogTexture.GetRect().y = m_StartingPosition.y;

			m_FrogLives--;

			m_FrogLivesTextures.at(m_FrogLives).second = false; //set render flag to false

			m_TimerBox.GetRect().x = 400;
			m_TimerBox.GetRect().w = 300;

			m_TimeRemaining = 60.0f;

		}
	}

	if (m_TimeRemaining <= 0.0f) {

		m_FrogStatus = Status::DEAD;

		m_RunOver.PlaySFX("frogger-squash.wav", 0, -1);

		m_TimeRemaining = 60.0f;
	}

	if (m_FrogStatus != Status::DEAD) {

		m_TimeRemaining -= TimerModule::GetDelta();
		
		//Doing this gives the illusion that the timer shrinks from left to right
		m_TimerBox.GetRect().x += TimerModule::GetDelta() * 5; //move the timer to the right
		m_TimerBox.GetRect().w -= TimerModule::GetDelta() * 5; //while reducing its width
		//delta is multiplied by 5 because its the result of the width of the box (300) divided by the time limit (60 secs)

	}

	if (m_FrogLives == 0) {

		m_BlackBoxRenderFlag = true;

		m_BlackBoxText.ChangeText("Game Over!", Colors::RED);
		m_BlackBox.GetRect().w = 200;

		m_IsHome.fill(false);

		for (int i = 0; i < m_FrogLivesTextures.size(); ++i) {
			m_FrogLivesTextures[i].second = true;
		}

		m_FrogLives = 2;

		m_Dead = true;

	}

	if (m_BlackBoxRenderFlag) {

		m_BlackBoxTimer += TimerModule::GetDelta();

		if (m_BlackBoxTimer >= m_BlackBoxMaxTime) {
			
			m_BlackBoxTimer = 0.0f;
			m_BlackBoxRenderFlag = false;

			m_BlackBox.GetRect().w = 140;

			m_Dead = false; //set to false even if it hasn't been changed
		}

	}

}

void Frog::Render()
{

	for (int i = 0; i < m_HomeTextures.size(); ++i) {

		if (m_IsHome[i]) {
			m_HomeTextures[i].RenderClippedTexture();
		}

	}

	switch (m_FrogStatus) {
	
		case Status::UP:
			m_FrogTexture.RenderClippedTexture(0.0f, !m_Dead); //render if not dead
			break;

		case Status::DOWN:
			m_FrogTexture.RenderClippedTexture(180.0f, !m_Dead); //rotate 180 degrees
			break;

		case Status::LEFT:
			m_FrogTexture.RenderClippedTexture(-90.0f, !m_Dead);
			break;

		case Status::RIGHT:
			m_FrogTexture.RenderClippedTexture(90.0f, !m_Dead);
			break;
	
		case Status::DEAD:
			m_AnimatedFrogTexture.RenderAnimation(35, 425, 500, 8, 0);
			break;

		default:
			break;
	}
												//render if true
	m_BlackBox.RenderRect(0, 0, 0, 255,		 m_BlackBoxRenderFlag);
	m_BlackBoxText.Render(Vector2(310, 305), m_BlackBoxRenderFlag);

	for (int i = 0; i < m_FrogLives; ++i) {
		
		if (m_FrogLivesTextures[i].second) { //check render flag

			m_FrogLivesTextures[i].first.RenderClippedTexture();

		}
	}

	if (m_TimerBox.GetRect().w <= 60) {

		m_TimerBox.RenderRect(255, 0, 0); //render in red color

		if (m_TimerBox.GetRect().w >= 59) {
			m_LowTime.PlaySFX("frogger-time.wav", 0, -1);
		}
	}
	else {
		m_TimerBox.RenderRect(0, 255, 0); //render in green color
	}
}

void Frog::Clean()
{
	//Textures are freed by the Texture2D class when closing the application

	//Needs to be removed to avoid re-adding when switching between game states
	CollisionManager::RemoveCollider("player");

	if (m_Score > 0) {

		std::ifstream Input;

		Input.open("src/Frogger/Score.txt");

		if (!Input.is_open() || !Input.good()) {
			std::cout << "Cannot read from file" << std::endl;
		}

		std::vector<int> Data;

		std::string Score;

		while (!Input.eof()) {

			std::getline(Input, Score); //im using strings to read from file since empty lines are treated as duplicates of the last read int

			if (!Score.empty()) { //avoid pushing empty strings
				Data.push_back(std::stoi(Score)); //turn string into int
			}
		}

		Input.close();
		
		Data.push_back(m_Score); //add player score

		std::sort(Data.rbegin(), Data.rend()); //sort in descending order

		Data.pop_back(); //delete lowest score

		std::ofstream Output;

		Output.open("src/Frogger/Score.txt");

		if (!Output.is_open() || !Output.good()) {
			std::cout << "Cannot write to file" << std::endl;
		}

		for (const auto& score : Data) {
			Output << score << "\n"; //write to file
		}

		Output.close();
	}
}

void Frog::EntranceRender(bool inHorizontalPos, bool AllInPosition, bool renderFlag)
{
	if (renderFlag) {

		if (inHorizontalPos) { //checks to see if a frog is in position
			m_AnimatedFrogTexture.RenderAnimation(35, 366, 300, 1, 0, SDL_FLIP_NONE, !AllInPosition); //render standing frog

			if (AllInPosition) { //check to see if all the frogs are in position
				m_AnimatedFrogTexture.RenderAnimation(35, 366, 300, 2, 0); //play walking up animation
			}

		}
		else {
			m_AnimatedFrogTexture.RenderAnimation(35, 337, 300, 2, 2); //play walking left animation
		}
	}
}

int Frog::GetScore() const
{
	return m_Score;
}
