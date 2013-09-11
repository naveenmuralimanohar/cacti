#ifndef _extio_H_
#define _extio_H_
#include "parameter.h"
#include "component.h"
#include "extio_technology.h"

class Extio : public Component
{
public: 
  
  Extio(IOTechParam *); 
    	
	int extio_area(); 

	int extio_eye(double io_tmargin, double io_vmargin); 

	int extio_power_dynamic(double io_power_dynamic); 

	int extio_power_phy(); 

	int extio_power_term(); 

  int extio_power_area_timing(double io_power, double phy_power, double io_area, double io_tmargin, double io_vmargin); 

private:
  IOTechParam *io_param;  

  double io_area;

  double io_power_term;
  double power_termination_write;
  double power_termination_read;
  double power_bias;
  double power_clk_bias;

  double phy_power;
  double phy_static_power;
  double phy_dynamic_power;
 
}; 
 
 
#endif  // _extio_H_ 
