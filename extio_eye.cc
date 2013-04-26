#include "extio.h"


int Extio::extio_eye(double io_tmargin, double io_vmargin)
{

	//VOLTAGE MARGINS


	//Voltage noise calculations based on proportional and independent noise sources for WRITE, READ and CA

	double v_noise_write = k_noise_write_sen * v_sw_data_write_line + v_noise_independent_write;
	
	double v_noise_read = k_noise_read_sen * v_sw_data_read_line + v_noise_independent_read;
	
	double v_noise_addr = k_noise_addr_sen * v_sw_addr + v_noise_independent_addr;
	
	
	//Worst-case voltage margin (Swing/2 - Voltage noise) calculations per state depending on DQ voltage margin and CA voltage margin (lesser or the two is reported)

	if (g_ip->iostate == 'R')
	  {
	    if ((v_sw_data_read_line/2 - v_noise_read)<(v_sw_addr/2 - v_noise_addr))
	      {
		io_vmargin = v_sw_data_read_line/2 - v_noise_read;
	      }
	    else 
	      {
		io_vmargin = v_sw_addr/2 - v_noise_addr;
	      }
	  }
	else if (g_ip->iostate == 'W')
	  {
	    if ((v_sw_data_write_line/2 - v_noise_write)<(v_sw_addr/2 - v_noise_addr))
	      {
		io_vmargin = v_sw_data_write_line/2 - v_noise_write;
	      }
	    else 
	      {
		io_vmargin = v_sw_addr/2 - v_noise_addr;
	      }		       
	  }
	else
	  {
	    io_vmargin = 0;
	  }


	

	//TIMING MARGINS
	
	
	//Setup and Hold timing margins for DQ WRITE, DQ READ and CA based on timing budget


	double t_margin_write_setup = (1e6/(4*g_ip->bus_freq)) - t_ds - t_error_soc - t_jitter_setup_sen - t_skew_setup;
	
	double t_margin_write_hold = (1e6/(4*g_ip->bus_freq)) - t_dh - t_dcd_soc - t_error_soc - t_jitter_hold_sen - t_skew_hold;
	

	
	double t_margin_read_setup = (1e6/(4*g_ip->bus_freq)) - t_soc_setup - t_error_soc - t_jitter_setup_sen - t_skew_setup - t_dqsq;

	double t_margin_read_hold = (1e6/(4*g_ip->bus_freq)) - t_soc_hold - t_dcd_dram - t_dcd_soc - t_error_soc - t_jitter_hold_sen - t_skew_hold - t_qhs;

	
	
	double t_margin_addr_setup = (1e6*g_ip->addr_timing/(4*g_ip->bus_freq)) - t_is - t_error_soc - t_jitter_addr_setup_sen - t_skew_setup;

	if (g_ip->addr_timing==1.0) {
	  t_margin_addr_setup = (1e6*g_ip->addr_timing/(2*g_ip->bus_freq)) - t_is - t_error_soc - t_jitter_addr_setup_sen - t_skew_setup;
	}
	else if (g_ip->addr_timing==2.0){
	  t_margin_addr_setup = (1e6*g_ip->addr_timing/(g_ip->bus_freq)) - t_is - t_error_soc - t_jitter_addr_setup_sen - t_skew_setup;
	}
	else if (g_ip->addr_timing==3.0){
	  t_margin_addr_setup = (3*1e6*g_ip->addr_timing/(2*g_ip->bus_freq)) - t_is - t_error_soc - t_jitter_addr_setup_sen - t_skew_setup;
	}
	
	
	double t_margin_addr_hold = (1e6*g_ip->addr_timing/(4*g_ip->bus_freq)) - t_ih - t_dcd_soc - t_error_soc - t_jitter_addr_hold_sen - t_skew_hold;
	

	
	if (g_ip->addr_timing==1.0) {
	  t_margin_addr_hold = (1e6*g_ip->addr_timing/(2*g_ip->bus_freq)) - t_ih - t_error_soc - t_jitter_addr_hold_sen - t_skew_hold;
	}
	else if (g_ip->addr_timing==2.0){
	  t_margin_addr_hold = (1e6*g_ip->addr_timing/(g_ip->bus_freq)) - t_ih - t_error_soc - t_jitter_addr_hold_sen - t_skew_hold;
	}
	else if (g_ip->addr_timing==3.0){
	  t_margin_addr_hold = (3*1e6*g_ip->addr_timing/(2*g_ip->bus_freq)) - t_ih - t_error_soc - t_jitter_addr_hold_sen - t_skew_hold;
	}



	//Worst-case timing margin per state depending on DQ and CA timing margins
	

	if (g_ip->iostate == 'R')
	  {
	    io_tmargin = t_margin_read_setup < t_margin_read_hold ? t_margin_read_setup : t_margin_read_hold;
	    io_tmargin = io_tmargin < t_margin_addr_setup ? io_tmargin : t_margin_addr_setup;
	    io_tmargin = io_tmargin < t_margin_addr_hold ? io_tmargin : t_margin_addr_hold;
	  }
	else if (g_ip->iostate == 'W')
	  {
	    io_tmargin = t_margin_write_setup < t_margin_write_hold ? t_margin_write_setup : t_margin_write_hold;
	    io_tmargin = io_tmargin < t_margin_addr_setup ? io_tmargin : t_margin_addr_setup;
	    io_tmargin = io_tmargin < t_margin_addr_hold ? io_tmargin : t_margin_addr_hold;
	  }
	else
	  {
	    io_tmargin = 0;
	  }





	//OUTPUTS


	printf("IO Timing Margin (ps) = ");
	cout << io_tmargin <<endl;
	printf("IO Votlage Margin (V) = ");
	cout << io_vmargin << endl;

}
