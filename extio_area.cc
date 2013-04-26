#include "extio.h"


//External IO AREA. Does not include PHY or decap, includes only IO active circuit.

int Extio::extio_area(double io_area)
{

	//Area per IO, assuming drive stage and ODT are shared

	double single_io_area = ioarea_c + (ioarea_k0/r_on)+(1/r_on)*(ioarea_k1*g_ip->bus_freq + ioarea_k2*g_ip->bus_freq*g_ip->bus_freq + ioarea_k3*g_ip->bus_freq*g_ip->bus_freq*g_ip->bus_freq); // IO Area in sq.mm.

	//Area per IO if ODT requirements are more stringent than the Ron requirements in determining size of driver

	if (2*rtt1_dq_read < r_on) {
	  single_io_area = ioarea_c + (ioarea_k0/(2*rtt1_dq_read))+(1/r_on)*(ioarea_k1*g_ip->bus_freq + ioarea_k2*g_ip->bus_freq*g_ip->bus_freq + ioarea_k3*g_ip->bus_freq*g_ip->bus_freq*g_ip->bus_freq);
	}

	//Total IO area

	io_area = (g_ip->num_dq + g_ip->num_dqs + g_ip->num_ca + g_ip->num_clk)*single_io_area;
	

	//OUTPUTS

	printf("IO Area (sq.mm) = ");
	cout << io_area << endl;

}
