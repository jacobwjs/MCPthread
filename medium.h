#ifndef MEDIUM_H
#define MEDIUM_H

#include "mutex.h"
#include "layer.h"

#include <vector>
#include <pthread.h>
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
	
	// Absorb energy from the photon at a given depth and store it in the grid.
	void absorbEnergy(const double z, const double energy);

	// Print the grid of the medium.
	void printGrid(const int num_photons);

	// Add a layer to the medium.
	void addLayer(Layer *layer);

	// Returns the absorption coefficient (mu_a) for a given depth (i.e. a layer).
	double getLayerAbsorption(double depth);

	// Returns the scattering coefficient (mu_s) for a given depth (i.e. a layer).
	double getLayerScatter(double depth);

	// Return the anisotropy ('g') value for a given depth (i.e. a layer).
	double getAnisotropyFromDepth(double depth);

	// Return layer from depth passed in.
	Layer * getLayerFromDepth(double depth);



		
protected:
	//double radial_size;	// maximum radial size of medium

	
private:
	double	radial_size;			// Maximum radial size.
	int		num_radial_pos;			// Number of radial positions (i.e. NR).
	double	radial_bin_size;		// Radial bin size of the medium (i.e dr).
	
	// The arrays that hold the weights dropped during interaction points.
	double	Cplanar[MAX_BINS];		// Planar photon concentration.
	double	Ccylinder[MAX_BINS];	// Clindrical photon concentration.
	double	Cspherical[MAX_BINS];	// Spherical photon concentration.
	
	Mutex *p_mutex;		// Pointer to the Mutex object.
	
	// Create a vector to hold the layers of the medium.
	vector<Layer *> p_layers;
};

#endif	// MEDIUM_H

