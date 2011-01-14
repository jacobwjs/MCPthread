#ifndef MEDIUM_H
#define MEDIUM_H

#include <vector>
#include <pthread.h>
#include "mutex.h"
using namespace std;

const int MAX_BINS = 101;

class Medium
{
	
public:

	Medium();
	~Medium();
	
	void absorbEnergy(double r, double energy);
	void printGrid();
	
protected:
	//double radial_size;	// maximum radial size of medium

	
private:
	double	radial_size; 
	int		num_radial_pos;			// Number of radial positions.
	double	radial_bin_size;		// Radial bin size of the medium.
	double	Cplanar[MAX_BINS];
	
	Mutex *p_mutex;		// Pointer to the Mutex object.
};

#endif	// MEDIUM_H

