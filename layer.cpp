

#include "layer.h"

Layer::Layer(void)
{	
	// Default values if nothing is specified.
	mu_a = 1.0;		// cm^-1
	mu_s = 100;		// cm^-1
	mu_t = mu_a + mu_s;
	albedo = mu_s/(mu_s + mu_a);
	g = 0.90;
	ref_index = 1.37;
	//radial_size = 3.0;	
	depth_init = 0;
	depth_end = 10;
}

Layer::Layer(double mu_a, double mu_s, double ref_index,
			 double depth_init, double depth_end)
{
	this->mu_a = mu_a;
	this->mu_s = mu_s;
	this->mu_t = mu_a + mu_s;
	albedo = mu_s/(mu_s + mu_a);
	g = 0.90;
	//radial_size = 3.0;
	this->ref_index = ref_index;
	
	this->depth_init = depth_init;
	this->depth_end = depth_end;
}

Layer::~Layer(void)
{
	// FINISH ME
}

void Layer::setAbsorpCoeff(double mu_a)
{
	this->mu_a = mu_a;
	
	// If we ever update the absorption coefficient we need to update the
	// transmission coefficient similarly.
	this->mu_t = mu_a + mu_s;
}

void Layer::setScatterCoeff(double mu_s)
{
	this->mu_s = mu_s;

	// If we ever update the scattering coefficient we need to update the
	// transmission coefficient similarly.
	this->mu_t = mu_a + mu_s;
}

/*
void Layer::absorbEnergy(double r, double energy)
{
	
}
*/
		


