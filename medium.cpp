#include "debug.h"
#include "medium.h"


Medium::Medium()
{
	radial_size = 3.0;
	num_radial_pos = MAX_BINS-1;
	radial_bin_size = radial_size / num_radial_pos;
	
	// Initialize all the bins to zero since they will serve as accumulators.
	for (int i = 0; i < MAX_BINS; i++) {
		Cplanar[i] = 0;
	}
	
	
	// Create the mutex used to prevent race conditions of threads (i.e. photons)
	// updating values in the grid.
	p_mutex = new Mutex();
}

Medium::~Medium()
{
	if (p_mutex != NULL)
		delete(p_mutex);
}


void Medium::absorbEnergy(double r, double energy)
{
	int index = (int)(r/radial_bin_size);
	if (index >= num_radial_pos)
		index = num_radial_pos;		// Last bin is for overflow.
#ifdef DEBUG
	cout << "Updating bin...\n";
#endif
	
	// Lock access, eliminating any race conditions between photons trying to
	// deposit energy.
	p_mutex->Lock();
	Cplanar[index] += energy;
	p_mutex->UnLock();
}


void Medium::printGrid()
{
	cout << " ";
	for (int i = 0; i < MAX_BINS; i++) {
		if ((i%10)== 0) cout << endl;
		cout << Cplanar[i] << " ";
	}
}
