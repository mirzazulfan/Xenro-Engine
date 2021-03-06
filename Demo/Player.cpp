#include "Player.h"
#include "globals.h"
#include <SDL/SDL.h>
#include <XenroEngine\GLTexture.h>

Player::Player(float speed, glm::vec2 pos, Xenro::InputManager* inputManager)
	: m_inputManager(inputManager)
{
	//Asign players color to white.
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;

	//Set Actor's speed
	m_speed = speed;

	//Set Actor's position
	m_position = pos;
}


Player::~Player()
{
	//Empty
}


void Player::update(const std::vector<std::string>& WorldData) {

	float speed = m_speed;
	if (m_inputManager->isDown(Xenro::Button::X) || m_inputManager->isDown(SDLK_LSHIFT)) {
		speed = m_speed + RUNSPEED;
	}


	if (m_inputManager->isDown(SDLK_w) || m_inputManager->isDown(Xenro::Button::DPAD_UP)) {
		m_position.y += speed;
		setMoveDir(MoveDir::UP);
	}
	else if (m_inputManager->isDown(SDLK_s) || m_inputManager->isDown(Xenro::Button::DPAD_DOWN)) {
		m_position.y -= speed;
		setMoveDir(MoveDir::DOWN);
	}

	if (m_inputManager->isDown(SDLK_d) || m_inputManager->isDown(Xenro::Button::DPAD_RIGHT)) {
		m_position.x += speed;

		//Determine direction.
		if (m_inputManager->isDown(SDLK_w) || m_inputManager->isDown(Xenro::Button::DPAD_UP)) {
			setMoveDir(MoveDir::UPRIGHT);
		}
		else if (m_inputManager->isDown(SDLK_s) || m_inputManager->isDown(Xenro::Button::DPAD_DOWN)) {
			setMoveDir(MoveDir::DOWNRIGHT);
		}
		else {
			setMoveDir(MoveDir::RIGHT);
		}
	}
	else if (m_inputManager->isDown(SDLK_a) || m_inputManager->isDown(Xenro::Button::DPAD_LEFT)) {
		m_position.x -= speed;

		//Determine direction.
		if (m_inputManager->isDown(SDLK_w) || m_inputManager->isDown(Xenro::Button::DPAD_UP)) {
			setMoveDir(MoveDir::UPLEFT);
		}
		else if (m_inputManager->isDown(SDLK_s) || m_inputManager->isDown(Xenro::Button::DPAD_DOWN)) {
			setMoveDir(MoveDir::DOWNLEFT);
		}
		else {
			setMoveDir(MoveDir::LEFT);
		}
	}

	/*Controller stuff*/
	if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGUP)) {
		m_position.y += speed;
		setMoveDir(MoveDir::UP);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGDOWN)) {
		m_position.y -= speed;
		setMoveDir(MoveDir::DOWN);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGRIGHT)) {
		m_position.x += speed;
		setMoveDir(MoveDir::RIGHT);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGUPRIGHT)) {
		m_position.x += speed /1.41f;
		m_position.y += speed /1.41f;
		setMoveDir(MoveDir::UPRIGHT);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGDOWNRIGHT)) {
		m_position.x += speed / 1.41f;
		m_position.y -= speed / 1.41f;
		setMoveDir(MoveDir::DOWNRIGHT);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGLEFT)) {
		m_position.x -= speed;
		setMoveDir(MoveDir::LEFT);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGUPLEFT)) {
		m_position.x -= speed / 1.41f;
		m_position.y += speed / 1.41f;
		setMoveDir(MoveDir::UPLEFT);
	}
	else if (m_inputManager->isDown(Xenro::Axis::LEFTANALOGDOWNLEFT)) {
		m_position.x -= speed / 1.41f;
		m_position.y -= speed / 1.41f;
		setMoveDir(MoveDir::DOWNLEFT);
	}

	//If none of the directions are being pressed.
	if (!(m_inputManager->isDown(SDLK_a) || m_inputManager->isDown(SDLK_w) || m_inputManager->isDown(SDLK_s) || m_inputManager->isDown(SDLK_d) || m_inputManager->getLeftAnalogAngle() != -1
		|| m_inputManager->isDown(Xenro::Button::DPAD_UP) || m_inputManager->isDown(Xenro::Button::DPAD_LEFT) || m_inputManager->isDown(Xenro::Button::DPAD_RIGHT) ||
		m_inputManager->isDown(Xenro::Button::DPAD_DOWN))) {
		setMoveDir(MoveDir::IDLE);
	}

	if(m_frameSpeed % 8 == 0){
		switch (m_moveDir) {
			case MoveDir::RIGHT:
				if (m_currFrameIndex < 27 || m_currFrameIndex >= 31) {
					m_currFrameIndex = 28;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::UP:
				if (m_currFrameIndex < 19 || m_currFrameIndex >= 23) {
					m_currFrameIndex = 20;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::UPLEFT:
				if (m_currFrameIndex < 7 || m_currFrameIndex >= 11) {
					m_currFrameIndex = 8;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::UPRIGHT:
				if (m_currFrameIndex < 3 || m_currFrameIndex >= 7) {
					m_currFrameIndex = 4;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::DOWN:
				if (m_currFrameIndex < 23 || m_currFrameIndex >= 27) {
					m_currFrameIndex = 24;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::DOWNLEFT:
				if (m_currFrameIndex < 15 || m_currFrameIndex >= 19) {
					m_currFrameIndex = 16;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::DOWNRIGHT:
				if (m_currFrameIndex < 11 || m_currFrameIndex >= 15) {
					m_currFrameIndex = 12;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::IDLE:
				if (m_currFrameIndex >= 3) {
					m_currFrameIndex = 0;
				}
				else {
					m_currFrameIndex++;
				}
				break;
			case MoveDir::LEFT:
				if (m_currFrameIndex < 31 || m_currFrameIndex >= 35) {
					m_currFrameIndex = 32;
				}
				else {
					m_currFrameIndex++;
				}
				break;
		}
	}
	
	m_frameSpeed++;

	setFrameIndex(m_currFrameIndex);
	collideWithWorld(WorldData);
}
