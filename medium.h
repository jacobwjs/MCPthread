#ifndef MEDIUM_H
#define MEDIUM_H

#include <vector>
#include <pthread.h>
#include "mutex.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAX_BINS = 101;

class Medium
{
	
public:

	Medium();
	~Medium();
	
	void absorbEnergy(double r, double energy);
	void printGrid(const int numPhotons, const int mu_a);
		
protected:
	//double radial_size;	// maximum radial size of medium

	
private:
	double	radial_size; 
	int		num_radial_pos;			// Number of radial positions.
	double	radial_bin_size;		// Radial bin size of the medium.
	
	// The 
	double	Cplanar[MAX_BINS];		// Planar photon concentration.
	double	Ccylinder[MAX_BINS];	// Clindrical photon concentration.
	double	Cspherical[MAX_BINS];	// Spherical photon concentration.
	
	Mutex *p_mutex;		// Pointer to the Mutex object.
};

#endif	// MEDIUM_H

