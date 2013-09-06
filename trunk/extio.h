#ifndef _extio_H_
#define _extio_H_
#include "parameter.h"
#include "component.h"

class Extio : public Component
{
public: 
     
    Extio(){}; 
   //The power calculation 
    	
	int extio_area(double io_area); 

	int extio_eye(double io_tmargin, double io_vmargin); 

	int extio_power_dynamic(double io_power_dynamic); 

	int extio_power_phy(double phy_power); 

	int extio_power_term(double io_power_term); 

 
int extio_power_area_timing(double io_power, double phy_power, double io_area, double io_tmargin, double io_vmargin); 

 
}; 
 
 
#endif  // _extio_H_ 
