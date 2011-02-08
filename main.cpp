/*
 * Copyright BMPI 2010
 * J.W. Staley - MIRA, 
 *               Biomedical Photonics Imaging Group (BMPI), 
 *				 University of Twente
 *
 */

/* FIXME:
 * ------
 * - Set default thread stack size
 * - Update printGrid to calculate fluences based on layers. 
 */



#include "stdio.h"
#include "photon.h"
#include "medium.h"
#include "layer.h"
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_THREADS = 33;
const int MAX_PHOTONS = 10000000;

//#define DEBUG 1

int main()
{
	
	// Each Photon inherits a Thread object.
	vector<Photon> photons(MAX_THREADS);
	vector<Photon>::iterator currPhoton;
	
	
	// Create the medium in which the photons will be fired.
	Medium *tissue = new Medium();
	// Add the layer to the medium.  NOTE:  destruction of the 'Layer' object is
	// handled in the 'tissue' object.
	tissue->addLayer(new Layer());
	
	
	// Capture the time before launching photons into the medium.
	clock_t start, end;
	start = clock();
	
	// Set attributes for the number of threads (i.e., Photons) and start their
	// execution.
	for (currPhoton = photons.begin(); currPhoton != photons.end(); ++currPhoton) {
		// Set the 'medium' the current Photon will be propagated through.
		currPhoton->setMedium(tissue);	
		
		// In order to extract the highest level of concurrency we set each thread
		// (i.e., Photon) to be executed a number of times that evenly distributes
		// the work (i.e., propagation through medium).
		currPhoton->setIterations(MAX_PHOTONS / MAX_THREADS);
		
		// Create the photon and execute hop, drop, and spin until it dies.
		currPhoton->launch();
	}
	
	for (currPhoton = photons.begin(); currPhoton != photons.end(); ++currPhoton) {
		currPhoton->join();
	}
	
	// Print out the elapsed time it took from beginning to end.
	end = ((double)clock() - start) / CLOCKS_PER_SEC;
	cout << "Time elapsed: " << end << endl;
	
	
	
	
	// Print the matrix of the photon absorptions to file.
	//Medium *ptrMedium = &tissue;
	tissue->printGrid(MAX_PHOTONS);
	delete tissue;
	
	
	return 0;
}
