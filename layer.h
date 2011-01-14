// Defines attributes of a layer.
#ifndef LAYER_H
#define LAYER_H

#include "medium.h"

class Layer : public Medium
{	

public:
	Layer(void);
	Layer(double mu_a, double mu_s, double ref_index,
		  double depth_init,	double depth_end);
	~Layer(void);


	double	getAbsorpCoeff(void) 	{return mu_a;}
	double	getScatterCoeff(void)	{return mu_s;}
	double	getTransCoeff(void)	{return mu_t;}
	double	getAlbedo(void) {return albedo;}
	double	getAnisotropy(void) {return g;}

	void	setAbsorpCoeff(const double absorption);
	void	setScatterCoeff(const double scatter);

	
private:
	// Anisotropy factor.
	double g;
	
	// Absorption coefficient
	double mu_a;
	
	// Scattering coefficient
	double mu_s;
	
	// Transmission coefficient
	double mu_t;
	
	// The refractive index of the layer
	double ref_index;
	
	// The width of the layer.
	//double radial_size;
	
	// z-coordinate value at which the layer starts.
	double depth_init;
	
	// z-coordinate value at which the layer ends.
	double depth_end;
	
	// Albedo of the layer.
	double albedo;	
	
};

#endif // end LAYER_H


