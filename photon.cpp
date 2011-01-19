
#include "debug.h"
#include "photon.h"
#include <cmath>



Photon::Photon(void)
{
#ifdef DEBUG
	cout << "Creating Photon...\n";
#endif
	// seed the random number generator.
	srand(time(0));

	// Photon was just created, so it is alive.
	status = ALIVE;

	// starting at the surface of the medium.
	x = 0;
	y = 0;
	z = 0;

	// Randomly set photon trajectory upon creation to yield isotropic source.
	cos_theta = 2.0 * getRandNum() - 1.0;
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);	// sin_theta is always positive.
	psi = 2.0*PI*getRandNum();
	
	// By setting all directions except 'z' to zero we are simulating a collimated beam.
	dirx = 0;
	diry = 0;
	dirz = 1.0;
	
	// Number of times Photon (i.e., thread) will run.
	iterations = 0;
	
	weight = 1;
	step = 0;
}

Photon::Photon(double x, double y, double z,
		double dirx, double diry, double dirz)
{
	iterations = 0;
	status = ALIVE;
	this->x = x;
	this->y = y;
	this->z = z;
	
	this->dirx = dirx;
	this->diry = diry;
	this->dirz = dirz;

	cos_theta = 2.0*getRandNum() - 1.0;
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	psi = 2.0*PI*getRandNum();

	weight = 1;
	step = 0;
}

Photon::~Photon(void)
{
#ifdef DEBUG	
	cout << "Destructing Photon...\n";
#endif
}


void Photon::setIterations(const int num)
{
	iterations = num;
}

void Photon::run()
{
	int cnt = 0;
	
	// Execute this photon (i.e. thread) the given number of iterations, thus
	// allowing the work to be split up.
	while (cnt < iterations) {
		
		while (isAlive()) {
#ifdef DEBUG
			cout << "Running thread( " << Thread::getThreadID() << ")...";
			cout << "..hop(), drop(), spin().  Propogated " << cnt << " times.\n";
#endif
			hop();
			drop();
			spin();
		}
		
		cnt++;
		reset();
	}
	
	// The thread has done its portion of the work, time to exit.
	//Thread::exit();
}

void Photon::reset()
{
#ifdef DEBUG
	cout << "Reseting Photon...\n";
#endif
	// seed the random number generator.
	srand(time(0));
	
	// Photon was just created, so it is alive.
	status = ALIVE;
	
	// starting at the surface of the medium.
	x = y = z = 0;
	
	// Randomly set photon trajectory upon creation to yield isotropic source.
	cos_theta = 2.0 * getRandNum() - 1.0;
	sin_theta = sqrt(1.0 - cos_theta*cos_theta);	// sin_theta is always positive.
	psi = 2.0*PI*getRandNum();
	
	// By setting all directions except 'z' to zero we are simulating a collimated beam.
	dirx = 0;
	diry = 0;
	dirz = 1.0;
	
	weight = 1;
	step = 0;
}

// Step photon to new position.
void Photon::hop()
{
#ifdef DEBUG
	cout << "Hopping...\n";
#endif	
	// 'step' = stepsize of photon in the medium.
	// 'dirx, diry, dirz' are cosines of current photon trajectory.
	step = -log(getRandNum())/(l->getAbsorpCoeff() + l->getScatterCoeff());
	x += step * dirx;
	y += step * diry;
	z += step * dirz;
}

// Drop absorbed energy from photon weight into bin.
void Photon::drop()
{
#ifdef DEBUG
	cout << "Dropping...\n";
#endif	
	double absorb = weight*(1 - l->getAlbedo());
	weight -= absorb;
	
	// planar 
	r = fabs(z);				// Current planar radial position.
	l->absorbEnergy(r, absorb);	// Drop absorbed energy into bin.
}


void Photon::spin()
{
#ifdef DEBUG
	cout << "Spinning...\n";
#endif	
	double g = l->getAnisotropy();
	double rnd = getRandNum();
	if (g == 0.0) {
		cos_theta = (2.0*rnd) - 1.0;
	}
	else {
		double temp = (1.0 - g*g)/(1.0 - g + 2*g*rnd);
		cos_theta = (1.0 + g*g - temp*temp)/(2.0*g);
		
		// Sanity check 
		if (cos_theta < -1)
			cos_theta = -1;
		else if (cos_theta > 1)
			cos_theta = 1;
	}
	sin_theta = sqrt(1.0 - cos_theta*cos_theta);	// sqrt() is faster
													// than sin().
	// Update our trajectory for our next move.	
	updateTrajectory();												
	
		
}

void Photon::updateTrajectory(void)
{
	// Sample psi.
	// ------------------------
	psi = 2.0 * PI * getRandNum();
	double cos_psi = cos(psi);
	double sin_psi;
	if (psi < PI)
		sin_psi = sqrt(1.0 - cos_psi * cos_psi);	// sqrt() is faster than sin().
	else
		sin_psi = -sqrt(1.0 - cos_psi * cos_psi);
		
	// Calculate new trajectory.
	// ----------------------------
	if (1 - fabs(dirz) <= ONE_MINUS_COSZERO) {  // Close to perpendicular.
		// Update direction in the x,y,z axes.
		dirx = sin_theta * cos_psi;
		diry = sin_theta * sin_psi;
		dirz = cos_theta * (dirz >= 0 ? 1 : -1);
	}
	else {	// More commonly encounter this since rarely do we move perpindicular.
		double temp = sqrt(1.0 - dirz*dirz);
		// Captcher the current directions so we don't lose them when updating below.
		double tx = dirx;
		double ty = diry;
		double tz = dirz;
		// Update direction in the x,y,z axes.
		dirx = sin_theta * (tx*tz*cos_psi - ty*sin_psi)/temp + tx*cos_theta;
		diry = sin_theta * (ty*tz*cos_psi + tx*sin_psi)/temp + ty*cos_theta;
		dirz = -sin_theta*cos_psi*temp + tz*cos_theta;
	}
	
	// Check if we need to perform roulette
	if (weight < THRESHOLD)
		performRoulette();
}

void Photon::performRoulette(void)
{
	if (getRandNum() <= CHANCE)
		weight /= CHANCE;
	else
		status = DEAD;
}



double Photon::getRandNum(void)
{
	double rnd = (double)rand()/(double)RAND_MAX;
	while ((rnd == 0) || (rnd == 1)) { // produces 0 < rnd < 1
		rnd = (double)rand()/(double)RAND_MAX;
	}
	return rnd;
}


void Photon::specularReflectance(double n1, double n2)
{
	// update the weight after specular reflectance has occurred.
	weight = weight - (pow((n1 - n2), 2) / pow((n1 + n2), 2)) * weight;
}

