#include "extio.h"


int Extio::extio_power_phy(double phy_power)
{
	
		// PHY Static Power Coefficients (mW)

	    double phy_datapath_s = 0; // Datapath Static Power
	    double phy_phase_rotator_s = 10; // Phase Rotator Static Power
	    double phy_clock_tree_s = 0; // Clock Tree Static Power
	    double phy_rx_s = 10; // Receiver Static Power
	    double phy_dcc_s = 0; // Duty Cycle Correction Static Power
	    double phy_deskew_s = 0; // Deskewing Static Power
	    double phy_leveling_s = 0; // Write and Read Leveling Static Power
	    double phy_pll_s = 10; // PHY PLL Static Power


            // PHY Dynamic Power Coefficients (mW/Gbps)

	    double phy_datapath_d = 0.5; // Datapath Dynamic Power
	    double phy_phase_rotator_d = 0.01; // Phase Rotator Dynamic Power
	    double phy_clock_tree_d = 0.5; // Clock Tree Dynamic Power
	    double phy_rx_d = 0.5; // Receiver Dynamic Power
	    double phy_dcc_d = 0.05; // Duty Cycle Correction Dynamic Power
	    double phy_deskew_d = 0.1; // Deskewing Dynamic Power
	    double phy_leveling_d = 0.05; // Write and Read Leveling Dynamic Power
	    double phy_pll_d = 0.05; // PHY PLL Dynamic Power



if (g_ip->dram_type == 'L')
{

	// PHY Static Power Coefficients (mW)

	    phy_datapath_s = 0; // Datapath Static Power
	    phy_phase_rotator_s = 5; // Phase Rotator Static Power
	    phy_clock_tree_s = 0; // Clock Tree Static Power
	    phy_rx_s = 3; // Receiver Static Power
	    phy_dcc_s = 0; // Duty Cycle Correction Static Power
	    phy_deskew_s = 0; // Deskewing Static Power
	    phy_leveling_s = 0; // Write and Read Leveling Static Power
	    phy_pll_s = 2; // PHY PLL Static Power


            // PHY Dynamic Power Coefficients (mW/Gbps)

	    phy_datapath_d = 0.3; // Datapath Dynamic Power
	    phy_phase_rotator_d = 0.01; // Phase Rotator Dynamic Power
	    phy_clock_tree_d = 0.4; // Clock Tree Dynamic Power
	    phy_rx_d = 0.2; // Receiver Dynamic Power
	    phy_dcc_d = 0; // Duty Cycle Correction Dynamic Power
	    phy_deskew_d = 0; // Deskewing Dynamic Power
	    phy_leveling_d = 0; // Write and Read Leveling Dynamic Power
	    phy_pll_d = 0.05; // PHY PLL Dynamic Power

}



if (g_ip->dram_type == 'W')
{

// PHY Static Power Coefficients (mW)

	    phy_datapath_s = 0; // Datapath Static Power
	    phy_phase_rotator_s = 1; // Phase Rotator Static Power
	    phy_clock_tree_s = 0; // Clock Tree Static Power
	    phy_rx_s = 0; // Receiver Static Power
	    phy_dcc_s = 0; // Duty Cycle Correction Static Power
	    phy_deskew_s = 0; // Deskewing Static Power
	    phy_leveling_s = 0; // Write and Read Leveling Static Power
	    phy_pll_s = 0; // PHY PLL Static Power


            // PHY Dynamic Power Coefficients (mW/Gbps)

	    phy_datapath_d = 0.3; // Datapath Dynamic Power
	    phy_phase_rotator_d = 0.01; // Phase Rotator Dynamic Power
	    phy_clock_tree_d = 0.2; // Clock Tree Dynamic Power
	    phy_rx_d = 0.1; // Receiver Dynamic Power
	    phy_dcc_d = 0; // Duty Cycle Correction Dynamic Power
	    phy_deskew_d = 0; // Deskewing Dynamic Power
	    phy_leveling_d = 0; // Write and Read Leveling Dynamic Power
	    phy_pll_d = 0; // PHY PLL Dynamic Power


}




	//PHY POWER


	double phy_static_power = phy_datapath_s + phy_phase_rotator_s + phy_clock_tree_s + phy_rx_s + phy_dcc_s + phy_deskew_s + phy_leveling_s + phy_pll_s; // Sum of PHY static power components in mW

	double phy_dynamic_power = phy_datapath_d + phy_phase_rotator_d + phy_clock_tree_d + phy_rx_d + phy_dcc_d + phy_deskew_d + phy_leveling_d + phy_pll_d; // Sum of PHY dynamic ower components in mW/Gbps


	phy_power = phy_static_power + g_ip->bus_bw * 8 * phy_dynamic_power; // Total PHY power in mW


	//OUTPUTS

	printf("PHY Power (mW) = ");
	cout << phy_power << endl;
	
}
