#include "stdio.h"
#include "photon.h"
#include "medium.h"
#include "layer.h"
#include <time.h>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_THREADS = 30;
const int MAX_PHOTONS = 50000;

#define DEBUG 1

int main()
{
	
	// Each Photon inherits a Thread object.
	vector<Photon> photons(MAX_THREADS);
	vector<Photon>::iterator currPhoton;
	 

	// Create the medium in which the photons will be fired.
	Layer tissue;


	/*
	time_t start, end;
	double duration = 0;
	time(&start);
	*/
	
	clock_t start, end;
	start = clock();
	
	// Set attributes for the number of threads (i.e., Photons) and start their
	// execution.
	for (currPhoton = photons.begin(); currPhoton != photons.end(); ++currPhoton) {
		// Set the layer the current Photon will be propogated through.
		currPhoton->setLayer(&tissue);	
		
		// In order to extract the highest level of concurrency we set each thread
		// (i.e., Photon) to be executed a number of times that evenly distributes
		// the work (i.e., propogation through medium).
		currPhoton->setIterations(MAX_PHOTONS / MAX_THREADS);
		
		// Create the photon and execute hop, drop, and spin until it dies.
		currPhoton->launch();
	}
	
	for (currPhoton = photons.begin(); currPhoton != photons.end(); ++currPhoton) {
		currPhoton->join();
	}
	
	/*
	time(&end);
	duration = difftime(end, start);         // time in milliseconds
	cout << "Execution time: " << duration << endl << endl;
	 */
	
	end = ((double)clock() - start) / CLOCKS_PER_SEC;
	cout << "Time elapsed: " << end << endl;
	
//#ifdef DEBUG
	Medium *p = &tissue;
	p->printGrid();
//#endif

				

	return 0;
}
