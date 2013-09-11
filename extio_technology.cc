#include "extio_technology.h"

/* This file contains configuration parameters for external IO, including
 * default configuration for DDR3, LPDDR2 and WIDEIO. The configuration
 * parameters include technology parameters - voltage, load capacitances, IO
 * area coefficients, timing parameters, as well as topology parameters -
 * termination values, voltage noise coefficients and voltage/timing noise
 * sensitivity parameters.*/

IOTechParam::IOTechParam(InputParameter * g_ip) 
{
  num_mem_ca  = g_ip->num_mem_dq * (g_ip->num_dq/g_ip->mem_data_width); 
  num_mem_clk =  g_ip->num_mem_dq *
                (g_ip->num_dq/g_ip->mem_data_width)/(g_ip->num_clk/2); 
	max_bw = g_ip->num_dq / 8 * 2 *g_ip->bus_freq * 1e-3; 

	max_capacity = (g_ip->mem_density/8) * g_ip->num_mem_dq * 
                 (g_ip->num_dq/g_ip->mem_data_width); 

  /* If ECC is enabled, then the modified bandwidth and capacity is accounted
   * for here. The below equation assumes 8 bits of ECC per 64 bit channel */
	if (g_ip->dram_ecc == 'Y'){
	  max_bw=max_bw*(g_ip->num_dq-8)/g_ip->num_dq;
	  max_capacity=max_capacity*(g_ip->num_dq-8)/g_ip->num_dq;

  }


  if (g_ip->dram_type == 'L') { //LPDDR
    //Technology Parameters

    vdd_io = 1.2;
    v_sw_clk =  1;

    // Loading paramters
    c_int = 1.5; 
    c_tx = 2;  
    c_data = 1.5;
    c_addr = 0.75;
    i_bias =  5; 
    i_leak = 1000; 

    // IO Area coefficients

    ioarea_c = 0.01; 
    ioarea_k0 = 0.5; 
    ioarea_k1 = 0.00008; 
    ioarea_k2 = 0.000000030; 
    ioarea_k3 = 0.000000000008; 

    // Timing parameters (ps)
    t_ds = 250; 
    t_is = 250;
    t_dh = 250;
    t_ih = 250; 
    t_dcd_soc = 50;
    t_dcd_dram = 50; 
    t_error_soc = 50;
    t_skew_setup = 50;
    t_skew_hold = 50;
    t_dqsq = 250; 
    t_qhs = 250; 
    t_soc_setup = 50;
    t_soc_hold = 50;
    t_jitter_setup = 200; 
    t_jitter_hold = 200; 
    t_jitter_addr_setup = 200;
    t_jitter_addr_hold = 200; 

    //Topology Parameters //FIXME Topology term has different usage

    r_diff_term = 240;
    rtt1_dq_read = 100000; 
    rtt2_dq_read = 100000; 
    rtt1_dq_write = 100000; 
    rtt2_dq_write = 100000; 
    rtt_ca = 240; 
    rs1_dq = 0; 
    rs2_dq = 0; 
    r_stub_ca = 0; 
    r_on = 50; 
    r_on_ca = 50;
    z0 = 50;
    t_flight = 0.5;
    t_flight_ca = 0.5;

    // Voltage noise coeffecients
    k_noise_write = 0.2; 
    k_noise_read = 0.2; 
    k_noise_addr = 0.2; 
    v_noise_independent_write = 0.1; 
    v_noise_independent_read = 0.1; 
    v_noise_independent_addr = 0.1; 

    //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE

    k_noise_write_sen = k_noise_write * (1 + 0.2*(r_on/34 - 1) +
        0.2*(g_ip->num_mem_dq/2 - 1));
    k_noise_read_sen = k_noise_read * (1 + 0.2*(r_on/34 - 1) +
        0.2*(g_ip->num_mem_dq/2 - 1));
    k_noise_addr_sen = k_noise_addr * (1 + 0.1*(rtt_ca/100 - 1) +
        0.2*(r_on/34 - 1) + 0.2*(num_mem_ca/16 - 1));

    t_jitter_setup_sen = t_jitter_setup * (1  + 0.1*(r_on/34 - 1) +
        0.3*(g_ip->num_mem_dq/2 - 1));
    t_jitter_hold_sen = t_jitter_hold * (1 + 0.1*(r_on/34 - 1) +
        0.3*(g_ip->num_mem_dq/2 - 1));
    t_jitter_addr_setup_sen = t_jitter_addr_setup * (1 + 0.2*(rtt_ca/100 - 1) +
        0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));
    t_jitter_addr_hold_sen = t_jitter_addr_hold * (1 + 0.2*(rtt_ca/100 - 1) +
        0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));

  }
   else if (g_ip->dram_type == 'W') { //WIDEIO 
     //Technology Parameters
     vdd_io = 1.2;
     v_sw_clk =  1.2;

     // Loading parameters
     c_int = 0.5; 
     c_tx = 0.5;  
     c_data = 0.5;  
     c_addr = 0.35; 
     i_bias =  0; 
     i_leak = 500; 

     // IO Area coefficients
     ioarea_c = 0.003; 
     ioarea_k0 = 0.2; 
     ioarea_k1 = 0.00004; 
     ioarea_k2 = 0.000000020; 
     ioarea_k3 = 0.000000000004; 

     // Timing parameters (ps)
     t_ds = 250; 
     t_is = 250;  
     t_dh = 250; 
     t_ih = 250; 
     t_dcd_soc = 50;  
     t_dcd_dram = 50; 
     t_error_soc = 50; 
     t_skew_setup = 50;  
     t_skew_hold = 50;  
     t_dqsq = 250;  
     t_qhs = 250; 
     t_soc_setup = 50; 
     t_soc_hold = 50; 
     t_jitter_setup = 200; 
     t_jitter_hold = 200; 
     t_jitter_addr_setup = 200; 
     t_jitter_addr_hold = 200; 

     //Topology Parameters

     r_diff_term = 100000;
     rtt1_dq_read = 100000; 
     rtt2_dq_read = 100000; 
     rtt1_dq_write = 100000; 
     rtt2_dq_write = 100000; 
     rtt_ca = 240; 
     rs1_dq = 0; 
     rs2_dq = 0; 
     r_stub_ca = 0; 
     r_on = 75; 
     r_on_ca = 75; 
     z0 = 50;
     t_flight = 0.05;
     t_flight_ca = 0.05;

     // Voltage noise coeffecients
     k_noise_write = 0.2; 
     k_noise_read = 0.2; 
     k_noise_addr = 0.2; 
     v_noise_independent_write = 0.1; 
     v_noise_independent_read = 0.1; 
     v_noise_independent_addr = 0.1; 

     //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE

     /* This is a user-defined section that depends on the channel sensitivity
      * to IO and DRAM parameters. The t_jitter_* and k_noise_* are the
      * parameters that are impacted based on the channel analysis. The user
      * can define any relationship between the termination, loading and
      * configuration parameters AND the t_jitter/k_noise parameters. E.g. a
      * linear relationship, a non-linear analytical relationship or a lookup
      * table. The sensitivity coefficients are based on channel analysis
      * performed on the channel of interest.Given below is an example of such
      * a sensitivity relationship */

     k_noise_write_sen = k_noise_write * (1 + 0.2*(r_on/50 - 1) + 
         0.2*(g_ip->num_mem_dq/2 - 1));
     k_noise_read_sen = k_noise_read * (1 + 0.2*(r_on/50 - 1) + 
         0.2*(g_ip->num_mem_dq/2 - 1));
     k_noise_addr_sen = k_noise_addr * (1 + 0.2*(r_on/50 - 1) + 
         0.2*(num_mem_ca/16 - 1));


     t_jitter_setup_sen = t_jitter_setup * (1  + 0.1*(r_on/50 - 1) + 
         0.3*(g_ip->num_mem_dq/2 - 1));
     t_jitter_hold_sen = t_jitter_hold * (1 + 0.1*(r_on/50 - 1) + 
         0.3*(g_ip->num_mem_dq/2 - 1));
     t_jitter_addr_setup_sen = t_jitter_addr_setup * (1 + 0.1*(r_on/50 - 1) + 
         0.4*(num_mem_ca/16 - 1));
     t_jitter_addr_hold_sen = t_jitter_addr_hold * (1 + 0.1*(r_on/50 - 1) + 
         0.4*(num_mem_ca/16 - 1));

   }
   else { //Default parameters for DDR3
     // IO Supply voltage (V) 
     vdd_io = 1.5;
     v_sw_clk =  0.75;

     // Loading parameters
     c_int = 1.5; 
     c_tx = 2;  
     c_data = 1.5; 
     c_addr = 0.75; 
     i_bias =  15; 
     i_leak = 1000; 

     // IO Area coefficients
     ioarea_c = 0.01; 
     ioarea_k0 = 0.5; 
     ioarea_k1 = 0.00015; 
     ioarea_k2 = 0.000000045; 
     ioarea_k3 = 0.000000000015; 

     // Timing parameters (ps)
     t_ds = 150;  
     t_is = 150; 
     t_dh = 150;
     t_ih = 150;
     t_dcd_soc = 50; 
     t_dcd_dram = 50;
     t_error_soc = 25; 
     t_skew_setup = 25; 
     t_skew_hold = 25; 
     t_dqsq = 100; 
     t_qhs = 100; 
     t_soc_setup = 50; 
     t_soc_hold = 50; 
     t_jitter_setup = 100; 
     t_jitter_hold = 100; 
     t_jitter_addr_setup = 100;
     t_jitter_addr_hold = 100;

     //Termination Parameters
     r_diff_term = 1000000;

     // ODT related termination resistor values (Ohm)
     rtt1_dq_read = 60; 
     rtt2_dq_read = 60; 
     rtt1_dq_write = 60;
     rtt2_dq_write = 60; 
     rtt_ca = 50; 
     rs1_dq = 15; 
     rs2_dq = 15; 
     r_stub_ca = 0; 
     r_on = 34; 
     r_on_ca = 50; 
     z0 = 50;
     t_flight = 1;
     t_flight_ca = 2;

     // Voltage noise coeffecients

     k_noise_write = 0.2; 
     k_noise_read = 0.2; 
     k_noise_addr = 0.2; 
     v_noise_independent_write = 0.1; 
     v_noise_independent_read = 0.1; 
     v_noise_independent_addr = 0.1; 

     //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE

     /* This is a user-defined section that depends on the channel sensitivity
      * to IO and DRAM parameters. The t_jitter_* and k_noise_* are the
      * parameters that are impacted based on the channel analysis. The user
      * can define any relationship between the termination, loading and
      * configuration parameters AND the t_jitter/k_noise parameters. E.g. a
      * linear relationship, a non-linear analytical relationship or a lookup
      * table. The sensitivity coefficients are based on channel analysis
      * performed on the channel of interest.Given below is an example of such
      * a sensitivity relationship */

     k_noise_write_sen = k_noise_write * (1 + 0.1*(rtt1_dq_write/60 - 1) +
         0.2*(rtt2_dq_write/60 - 1) + 0.2*(r_on/34 - 1) +
         0.2*(g_ip->num_mem_dq/2 - 1));

     k_noise_read_sen = k_noise_read * (1 + 0.1*(rtt1_dq_read/60 - 1) +
         0.2*(rtt2_dq_read/60 - 1) + 0.2*(r_on/34 - 1) +
         0.2*(g_ip->num_mem_dq/2 - 1));

     k_noise_addr_sen = k_noise_addr * (1 + 0.1*(rtt_ca/50 - 1) +
         0.2*(r_on/34 - 1) + 0.2*(num_mem_ca/16 - 1));


     t_jitter_setup_sen = t_jitter_setup * (1 + 0.2*(rtt1_dq_write/60 - 1) + 
         0.3*(rtt2_dq_write/60 - 1) + 0.1*(r_on/34 - 1) + 
         0.3*(g_ip->num_mem_dq/2 - 1));

     t_jitter_hold_sen = t_jitter_hold * (1 + 0.2*(rtt1_dq_write/60 - 1) + 
         0.3*(rtt2_dq_write/60 - 1) + 
         0.1*(r_on/34 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

     t_jitter_addr_setup_sen = t_jitter_addr_setup * (1 + 0.2*(rtt_ca/50 - 1) + 
         0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));

     t_jitter_addr_hold_sen = t_jitter_addr_hold * (1 + 0.2*(rtt_ca/50 - 1) + 
         0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));


   }



   //SWING AND TERMINATION CALCULATIONS

   //R|| calculation
   rpar_write =(rtt1_dq_write + rs1_dq)*(rtt2_dq_write + rs2_dq)/
        (rtt1_dq_write + rs1_dq + rtt2_dq_write + rs2_dq);
   rpar_read =(rtt1_dq_read)*(rtt2_dq_read + rs2_dq)/
        (rtt1_dq_read + rtt2_dq_read + rs2_dq);

   //Swing calculation
   v_sw_data_read_load1 =vdd_io * (rtt1_dq_read)*(rtt2_dq_read + rs2_dq) / 
      ((rtt1_dq_read + rtt2_dq_read + rs2_dq)*(r_on + rs1_dq + rpar_read)); 
   v_sw_data_read_load2 =vdd_io * (rtt1_dq_read)*(rtt2_dq_read) / 
      ((rtt1_dq_read + rtt2_dq_read + rs2_dq)*(r_on + rs1_dq + rpar_read)); 
   v_sw_data_read_line =vdd_io * rpar_read / (r_on + rs1_dq + rpar_read); 
   v_sw_addr =vdd_io * rtt_ca / (50 + rtt_ca); 
   v_sw_data_write_load1 =vdd_io * (rtt1_dq_write)*(rtt2_dq_write + rs2_dq) / 
      ((rtt1_dq_write + rs1_dq + rtt2_dq_write + rs2_dq)*(r_on + rpar_write)); 
   v_sw_data_write_load2 =vdd_io * (rtt2_dq_write)*(rtt1_dq_write + rs1_dq) / 
      ((rtt1_dq_write + rs1_dq + rtt2_dq_write + rs2_dq)*(r_on + rpar_write));
   v_sw_data_write_line =vdd_io * rpar_write / (r_on + rpar_write); 

}

IOTechParam::~IOTechParam() 
{}
