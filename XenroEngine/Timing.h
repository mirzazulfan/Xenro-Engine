/*************************************************************************/
/*                             Timing.h                                  */
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

#ifndef XENRO_TIMING_DEFINED
#define XENRO_TIMING_DEFINED

namespace Xenro{

class FPSlimiter {
public:
	FPSlimiter();
	~FPSlimiter();

	//Setters
	void setFrameCap(float frameCap) { m_frameCap = frameCap; }
	void setLimiting(bool limit) { m_isLimiting = limit; }

	//Getters
	float getFPS() const { return m_fps; }
	
	//Grabs number of ticks at begining of frame limiting.
	void startLimiting();

	//Gets final number of ticks and delays according to frameCap.
	float endLimiting();

private:
	//counts the number of gameticks every second, then calculates how many frames each second.
	void calculateFPS();
	bool m_isLimiting;
	float m_fps, m_frameCap, m_beginTime, m_frameTime;
};

}

#endif //XENRO_TIMING_DEFINED