#include "extio.h"


int Extio::extio_power_dynamic(double io_power_dynamic)
{

	//Line capacitance calculations for effective c_line

        double c_line =1e6/(z0*2*g_ip->bus_freq); //For DDR signals: DQ, DQS, CLK
        double c_line_ca=c_line; //For DDR CA
	double c_line_sdr=1e6/(z0*g_ip->bus_freq); //For SDR CA
	double c_line_2T=1e6*2/(z0*g_ip->bus_freq); //For 2T timing
	double c_line_3T=1e6*3/(z0*g_ip->bus_freq); //For 3T timing

	//Line capacitance if flight time is less than half the bit period
	
	if (t_flight < 1e3/(4*g_ip->bus_freq)){
	  c_line = 1e3*t_flight/z0;
	}

	if (t_flight_ca < 1e3/(4*g_ip->bus_freq)){
	  c_line_ca = 1e3*t_flight/z0;
	}

	if (t_flight_ca < 1e3/(2*g_ip->bus_freq)){
	  c_line_sdr = 1e3*t_flight/z0;
	}

	if (t_flight_ca < 1e3*2/(2*g_ip->bus_freq)){
	  c_line_2T = 1e3*t_flight/z0;
	}

	if (t_flight_ca < 1e3*3/(2*g_ip->bus_freq)){
	  c_line_3T = 1e3*t_flight/z0;
	}

	//Line capacitance calculation for the address bus, depending on what address timing is chosen (DDR/SDR/2T/3T)

	if (g_ip->addr_timing==1.0) {
	  c_line_ca = c_line_sdr;
	}
	else if (g_ip->addr_timing==2.0){
	  c_line_ca = c_line_2T;
	}
	else if (g_ip->addr_timing==3.0){
	  c_line_ca = c_line_3T;
	}





	//Dynamic power per signal group for WRITE and READ modes

	power_dq_write = g_ip->num_dq * g_ip->activity_dq * (c_tx +  c_line) * vdd_io * v_sw_data_write_line * g_ip->bus_freq / 1000 + g_ip->num_dq * g_ip->activity_dq * c_data * vdd_io * v_sw_data_write_load1 * g_ip->bus_freq / 1000 + g_ip->num_dq * g_ip->activity_dq * ((g_ip->num_mem_dq-1) * c_data) * vdd_io * v_sw_data_write_load2 * g_ip->bus_freq / 1000  + g_ip->num_dq * g_ip->activity_dq * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;

	power_dqs_write = g_ip->num_dqs * (c_tx +  c_line) * vdd_io * v_sw_data_write_line * g_ip->bus_freq / 1000 + g_ip->num_dqs * c_data * vdd_io * v_sw_data_write_load1 * g_ip->bus_freq / 1000 + g_ip->num_dqs * ((g_ip->num_mem_dq-1) * c_data) * vdd_io * v_sw_data_write_load2 *g_ip->bus_freq / 1000  + g_ip->num_dqs * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;

	power_ca_write = g_ip->num_ca * g_ip->activity_ca * (c_tx + num_mem_ca * c_addr + c_line_ca) * vdd_io * v_sw_addr * g_ip->bus_freq / 1000 + g_ip->num_ca * g_ip->activity_ca * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;

	power_dq_read = g_ip->num_dq * g_ip->activity_dq * (c_tx +  c_line) * vdd_io * v_sw_data_read_line * g_ip->bus_freq / 1000 + g_ip->num_dq * g_ip->activity_dq * c_data * vdd_io * v_sw_data_read_load1 * g_ip->bus_freq / 1000 + g_ip->num_dq *g_ip->activity_dq * ((g_ip->num_mem_dq-1) * c_data) * vdd_io * v_sw_data_read_load2 * g_ip->bus_freq / 1000  + g_ip->num_dq * g_ip->activity_dq * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;

	power_dqs_read = g_ip->num_dqs * (c_tx +  c_line) * vdd_io * v_sw_data_read_line * g_ip->bus_freq / 1000 + g_ip->num_dqs * c_data * vdd_io * v_sw_data_read_load1 * g_ip->bus_freq / 1000 + g_ip->num_dqs * ((g_ip->num_mem_dq-1) * c_data) * vdd_io * v_sw_data_read_load2 * g_ip->bus_freq / 1000  + g_ip->num_dqs * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;

	power_ca_read = g_ip->num_ca * g_ip->activity_ca * (c_tx + num_mem_ca * c_addr + c_line_ca) * vdd_io * v_sw_addr * g_ip->bus_freq / 1000 + g_ip->num_ca * g_ip->activity_ca * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;

	power_clk = g_ip->num_clk * (c_tx + num_mem_clk * c_data + c_line) * vdd_io * v_sw_clk *g_ip->bus_freq / 1000 + g_ip->num_clk * c_int * vdd_io * vdd_io * g_ip->bus_freq / 1000;


	//Combining the power terms based on STATE (READ/WRITE/IDLE/SLEEP)

	if (g_ip->iostate == 'R')
	  {
	    io_power_dynamic = g_ip->duty_cycle * (power_dq_read + power_ca_read + power_dqs_read + power_clk);
	  }
	else if (g_ip->iostate == 'W')
	  {
	    io_power_dynamic = g_ip->duty_cycle * (power_dq_write + power_ca_write + power_dqs_write + power_clk);
	  }
	else if (g_ip->iostate == 'I')
	  {
	    io_power_dynamic = g_ip->duty_cycle * (power_clk);
	  }
	else if (g_ip->iostate == 'S')
	  {
	    io_power_dynamic = 0;
	  }
	else
	  {
	    io_power_dynamic = 0;
	  }



	//OUTPUTS


	printf("IO Dynamic Power (mW) = ");
	cout << io_power_dynamic << endl;
}
