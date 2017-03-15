/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

class timer
{
private:

public:
	float t, dt, fps;
	
	// Lorentz factor and coordinate time (t is proper time along the time-like world line where and when this timer was started).
	float g = 1;
	float dtau, tau;

	timer();

	~timer();
	
	void start();
	void update();
};