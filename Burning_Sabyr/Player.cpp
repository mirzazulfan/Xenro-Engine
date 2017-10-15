#include "Player.h"
#include <SDL/SDL.h>
#include <XenroEngine\GLTexture.h>

Player::Player()
{
}


Player::~Player()
{
}

void Player::init(float speed, glm::vec2 pos, Xenro::InputManager* inputManager) {

	m_speed = speed;
	m_position = pos;
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;
	m_inputManager = inputManager;

}

void Player::update(const std::vector<std::string>& WorldData) {

	if (m_inputManager->isDown(SDLK_w)) {
		m_position.y += m_speed;
		setMoveDir(MoveDir::UP);
	}
	else if (m_inputManager->isDown(SDLK_s)) {
		m_position.y -= m_speed;
		setMoveDir(MoveDir::DOWN);
	}

	if (m_inputManager->isDown(SDLK_d)) {
		m_position.x += m_speed;

		//Determine direction.
		if (m_inputManager->isDown(SDLK_w)) {
			setMoveDir(MoveDir::UPRIGHT);
		}
		else if (m_inputManager->isDown(SDLK_s)) {
			setMoveDir(MoveDir::DOWNRIGHT);
		}
		else {
			setMoveDir(MoveDir::RIGHT);
		}
	}
	else if (m_inputManager->isDown(SDLK_a)) {
		m_position.x -= m_speed;

		//Determine direction.
		if (m_inputManager->isDown(SDLK_w)) {
			setMoveDir(MoveDir::UPLEFT);
		}
		else if (m_inputManager->isDown(SDLK_s)) {
			setMoveDir(MoveDir::DOWNLEFT);
		}
		else {
			setMoveDir(MoveDir::LEFT);
		}
	}

	//If none of the directions are being pressed.
	if (!(m_inputManager->isDown(SDLK_a) || m_inputManager->isDown(SDLK_w) || m_inputManager->isDown(SDLK_s) || m_inputManager->isDown(SDLK_d))) {
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
