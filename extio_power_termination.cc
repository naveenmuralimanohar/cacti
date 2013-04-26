#include "extio.h"


int Extio::extio_power_term(double io_power_term)
{

	//IO Termination and Bias Power

		//Bias and Leakage Power
	  
	power_bias = i_bias * vdd_io + i_leak * (g_ip->num_dq + g_ip->num_dqs + g_ip->num_clk + g_ip->num_ca) * vdd_io / 1000000;
	

		//Termination Power

	power_termination_read = 1000 * (g_ip->num_dq + g_ip->num_dqs) * vdd_io * vdd_io * 0.25 * (1/(r_on + rpar_read + rs1_dq) + 1/(rtt1_dq_read) + 1/(rtt2_dq_read)) + 1000 * g_ip->num_ca * vdd_io * vdd_io * (0.5 / (2 * (r_on_ca + rtt_ca)));

	power_termination_write = 1000 * (g_ip->num_dq + g_ip->num_dqs) * vdd_io * vdd_io * 0.25 * (1/(r_on + rpar_write) + 1/(rtt1_dq_write) + 1/(rtt2_dq_write)) + 1000 * g_ip->num_ca * vdd_io * vdd_io * (0.5 / (2 * (r_on_ca + rtt_ca)));

        power_clk_bias = vdd_io * v_sw_clk / r_diff_term * 1000;


	//Combining the power terms based on STATE (READ/WRITE/IDLE/SLEEP)

	if (g_ip->iostate == 'R')
	  {
	    io_power_term = g_ip->duty_cycle * (power_termination_read + power_bias + power_clk_bias);
	  }
	else if (g_ip->iostate == 'W')
	  {
	    io_power_term = g_ip->duty_cycle * (power_termination_write + power_bias + power_clk_bias);
	  }
	else if (g_ip->iostate == 'I')
	  {
	    io_power_term = g_ip->duty_cycle * (power_termination_write + power_bias + power_clk_bias);
	  }
	else if (g_ip->iostate == 'S')
	  {
	    io_power_term = i_leak*vdd_io;
	  }
	else
	  {
	    io_power_term = 0;
	  }




	//OUTPUTS


	printf("IO Termination and Bias Power (mW) = ");
	cout << io_power_term << endl;
}
