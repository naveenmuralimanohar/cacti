#include "extio.h"


int Extio::extio_power_phy(double phy_power)
{
	

	//PHY POWER


	double phy_static_power = phy_datapath_s + phy_phase_rotator_s + phy_clock_tree_s + phy_rx_s + phy_dcc_s + phy_deskew_s + phy_leveling_s + phy_pll_s; // Sum of PHY static power components in mW

	double phy_dynamic_power = phy_datapath_d + phy_phase_rotator_d + phy_clock_tree_d + phy_rx_d + phy_dcc_d + phy_deskew_d + phy_leveling_d + phy_pll_d; // Sum of PHY dynamic ower components in mW/Gbps


	phy_power = phy_static_power + g_ip->bus_bw * 8 * phy_dynamic_power; // Total PHY power in mW


	//OUTPUTS

	printf("PHY Power (mW) = ");
	cout << phy_power << endl;
	
}
