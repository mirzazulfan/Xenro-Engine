/*************************************************************************/
/*                            Timing.cpp                                 */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           Xenro Engine                                */
/*             https://github.com/Jmiller7023/Xenro-Engine               */
/*************************************************************************/
/*                 Copyright  11-3-2017 Joseph Miller.                   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#include "Timing.h"
#include <SDL\SDL.h>

namespace Xenro{

FPSlimiter::FPSlimiter()
	:m_fps(60.0f), m_maxFPS(60.0f), m_lastTime(0.0f), m_frames(0)
{
	//Empty
}

FPSlimiter::~FPSlimiter()
{
	//Empty
}

void FPSlimiter::setTargetFPS(float targetFPS) {

	m_maxFPS = targetFPS;
}

void FPSlimiter::calculateFPS() {
	
	m_currTicks = (float)SDL_GetTicks();
	m_frames++;
	//if it's been one second since last calculation.
	if (m_currTicks - m_lastTime >= 1000.0f) {
		m_fps =  m_frames;
		m_frames = 1;
		m_lastTime += 1000.0f;
	}
}

float FPSlimiter::limitFPS() {

	float delay = ((float)SDL_GetTicks() - m_currTicks);

	if ( 1000.0f / m_maxFPS > delay) {
		SDL_Delay((Uint32)(1000.f / m_maxFPS - delay));
	}
	return m_fps;
}

}