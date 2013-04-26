
//This file contains configuration parameters for external IO, including default configuration for DDR3, LPDDR2 and WIDEIO. The configuration parameters include technology parameters - voltage, load capacitances, IO area coefficients, timing parameters, as well as topology parameters - termination values, voltage noise coefficients and voltage/timing noise sensitivity parameters.

int Extio::extio_cfg()
{

    	double num_mem_ca = g_ip->num_mem_dq * (g_ip->num_dq/g_ip->mem_data_width); //Calculates the number of loads on the address bus based on total number of memories in the channel.For registered DIMMs or buffered topologies, the num_mem_dq and num_mem_ca is per buffer.

    	double num_mem_clk =  g_ip->num_mem_dq * (g_ip->num_dq/g_ip->mem_data_width)/(g_ip->num_clk/2); //Cacluates the number of loads on the clock as total memories in the channel / number of clock lines available

	double max_bw = g_ip->num_dq / 8 * 2 *g_ip->bus_freq * 1e-3; //Max. bandwidth achievable if data bus is operating at max. data-rate (in GBytes per second)

	double max_capacity = (g_ip->mem_density/8) * g_ip->num_mem_dq * (g_ip->num_dq/g_ip->mem_data_width); //Max. capacity based on memory density and number of memories (in GB)


	//If ECC is enabled, then the modified bandwidth and capacity is accounted for here. The below equation assumes 8 bits of ECC per 64 bit channel

	if (g_ip->dram_ecc == 'Y'){
	  max_bw=max_bw*(g_ip->num_dq-8)/g_ip->num_dq;
	  max_capacity=max_capacity*(g_ip->num_dq-8)/g_ip->num_dq;

	}

    

///Default parameters for DDR3
	  
	    
		//Technology Parameters

       		// IO Supply voltage (V) 

	    double vdd_io = 1.5;

            	// Voltage swing on CLK/CLKB (V) (swing on the CLK pin if it is differentially terminated).

	    double v_sw_clk =  0.75;

            	// Loading parameters

	    double c_int = 1.5; //Internal IO loading (pF) (loading within the IO, due to predriver nets)

	    double c_tx = 2;  //IO TX self-load including package (pF) (loading at the CPU TX pin)

	    double c_data = 1.5;  //Device loading per memory data pin (pF) (DRAM device load for DQ per die)

	    double c_addr = 0.75; //Device loading per memory address pin (pF) (DRAM device load for CA per die)



            // Bias current (mA) (includes bias current for the whole memory bus due to RX Vref based receivers

	    double i_bias =  15; 

            // Active leakage current per pin (nA) 

	    double i_leak = 1000; 



            // IO Area coefficients

	    double ioarea_c = 0.01; // sq.mm. (IO Area baseline coeeficient for control circuitry and overhead)

	    double ioarea_k0 = 0.5; // sq.mm * ohms (IO Area coefficient for the driver, for unit drive strength or output impedance)

	    double ioarea_k1 = 0.00015; // sq.mm * ohms / MHz (IO Area coefficient for the predriver final stage, based on fanout needed)

	    double ioarea_k2 = 0.000000045; // sq.mm * ohms / MHz^2 (IO Area coefficient for predriver middle stage, based on fanout needed)

	    double ioarea_k3 = 0.000000000015; // sq.mm * ohms / MHz^3 (IO Area coefficient for predriver first stage, based on fanout needed)


            // Timing parameters (ps)

	    double t_ds = 150;  //DQ setup time at DRAM

	    double t_is = 150;  //CA setup time at DRAM

	    double t_dh = 150;  //DQ hold time at DRAM

	    double t_ih = 150;  //CA hold time at DRAM

	    double t_dcd_soc = 50;  //Duty-cycle distortion at the CPU/SOC

	    double t_dcd_dram = 50;  //Duty-cycle distortion at the DRAM

	    double t_error_soc = 25;  //Timing error due to edge placement uncertainty of the DLL

	    double t_skew_setup = 25;  //Setup skew between DQ/DQS or CA/CLK after deskewing the lines

	    double t_skew_hold = 25;  //Hold skew between DQ/DQS or CA/CLK after deskewing the lines

	    double t_dqsq = 100;  //DQ-DQS skew at the DRAM output during Read

	    double t_qhs = 100; //DQ-DQS hold factor at the DRAM output during Read
	      
	    double t_soc_setup = 50; //Setup time at SOC input dueing Read

	    double t_soc_hold = 50;  //Hold time at SOC input during Read

	    double t_jitter_setup = 100; //Half-cycle jitter on the DQS at DRAM input affecting setup time

	    double t_jitter_hold = 100; //Half-cycle jitter on the DQS at the DRAM input affecting hold time

	    double t_jitter_addr_setup = 100; //Half-cycle jitter on the CLK at DRAM input affecting setup time

	    double t_jitter_addr_hold = 100; //Half-cycle jitter on the CLK at the DRAM input affecting hold time


     

	    	//Termination Parameters

            // Differential termination resister if used for CLK (Ohm) 

	    double r_diff_term = 1000000;


            // ODT related termination resistor values (Ohm)

	    double rtt1_dq_read = 60; //DQ Read termination at CPU

	    double rtt2_dq_read = 60; //DQ Read termination at inactive DRAM

	    double rtt1_dq_write = 60; //DQ Write termination at active DRAM

	    double rtt2_dq_write = 60; //DQ Write termination at inactive DRAM

	    double rtt_ca = 50; //CA fly-by termination

	    double rs1_dq = 15; //Series resistor at active DRAM

	    double rs2_dq = 15; //Series resistor at inactive DRAM

	    double r_stub_ca = 0; //Series resistor for the fly-by channel

	    double r_on = 34; //Driver impedance

	    double r_on_ca = 50; //CA driver impedance



 		//Line impedance (ohms): Characteristic impedance of the route.

	    double z0 = 50;

 

        	// Flight time of the interconnect (ns) (approximately 180ps/inch for FR4)

	    double t_flight = 1;

        	// Flight time of the Control/Address (CA) interconnect (ns) (approximately 180ps/inch for FR4)

	    double t_flight_ca = 2;


     		// Voltage noise coeffecients

	    double k_noise_write = 0.2; //Proportional noise coefficient for Write mode

	    double k_noise_read = 0.2; //Proportional noise coefficient for Read mode

	    double k_noise_addr = 0.2; //Proportional noise coefficient for Address bus

	    double v_noise_independent_write = 0.1; //Independent noise voltage for Write mode

	    double v_noise_independent_read = 0.1; //Independent noise voltage for Read mode

	    double v_noise_independent_addr = 0.1; //Independent noise voltage for Address bus


	    //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE


	    //This is a user-defined section that depends on the channel sensitivity to IO and DRAM parameters. The t_jitter_* and k_noise_* are the parameters that are impacted based on the channel analysis. The user can define any relationship between the termination, loading and configuration parameters AND the t_jitter/k_noise parameters. E.g. a linear relationship, a non-linear analytical relationship or a lookup table. The sensitivity coefficients are based on channel analysis performed on the channel of interest.Given below is an example of such a sensitivity relationship

	    double k_noise_write_sen = k_noise_write * (1 + 0.1*(rtt1_dq_write/60 - 1) + 0.2*(rtt2_dq_write/60 - 1) + 0.2*(r_on/34 - 1) + 0.2*(g_ip->num_mem_dq/2 - 1));

	    double k_noise_read_sen = k_noise_read * (1 + 0.1*(rtt1_dq_read/60 - 1) + 0.2*(rtt2_dq_read/60 - 1) + 0.2*(r_on/34 - 1) + 0.2*(g_ip->num_mem_dq/2 - 1));

	    double k_noise_addr_sen = k_noise_addr * (1 + 0.1*(rtt_ca/50 - 1) + 0.2*(r_on/34 - 1) + 0.2*(num_mem_ca/16 - 1));


	    double t_jitter_setup_sen = t_jitter_setup * (1 + 0.2*(rtt1_dq_write/60 - 1) + 0.3*(rtt2_dq_write/60 - 1) + 0.1*(r_on/34 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

	    double t_jitter_hold_sen = t_jitter_hold * (1 + 0.2*(rtt1_dq_write/60 - 1) + 0.3*(rtt2_dq_write/60 - 1) + 0.1*(r_on/34 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

	    double t_jitter_addr_setup_sen = t_jitter_addr_setup * (1 + 0.2*(rtt_ca/50 - 1) + 0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));

	    double t_jitter_addr_hold_sen = t_jitter_addr_hold * (1 + 0.2*(rtt_ca/50 - 1) + 0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));




///LPDDR


	if (g_ip->dram_type == 'L')
	  {
	    
	    //Technology Parameters

            // IO Supply voltage (V) 

	    vdd_io = 1.2;

            // Voltage swing on CLK/CLKB (V) (swing on the CLK pin if it is differentially terminated).

	    v_sw_clk =  1;

            // Loading parameters

	    c_int = 1.5; //Internal IO loading (pF) (loading within the IO, due to predriver nets)

	    c_tx = 2;  //IO TX self-load including package (pF) (loading at the CPU TX pin)

	    c_data = 1.5;  //Device loading per memory data pin (pF) (DRAM device load for DQ per die)

	    c_addr = 0.75; //Device loading per memory address pin (pF) (DRAM device load for CA per die)


            // Bias current (mA) (includes bias current for the whole memory bus due to RX Vref based receivers

	    i_bias =  5; 

            // Active leakage current per pin (nA) 

	    i_leak = 1000; 



            // IO Area coefficients

	    ioarea_c = 0.01; // sq.mm. (IO Area baseline coeeficient for control circuitry and overhead)

	    ioarea_k0 = 0.5; // sq.mm * ohms (IO Area coefficient for the driver, for unit drive strength or output impedance)

	    ioarea_k1 = 0.00008; // sq.mm * ohms / MHz (IO Area coefficient for the predriver final stage, based on fanout needed)

	    ioarea_k2 = 0.000000030; // sq.mm * ohms / MHz^2 (IO Area coefficient for predriver middle stage, based on fanout needed)

	    ioarea_k3 = 0.000000000008; // sq.mm * ohms / MHz^3 (IO Area coefficient for predriver first stage, based on fanout needed)


            // Timing parameters (ps)

	    t_ds = 250;  //DQ setup time at DRAM

	    t_is = 250;  //CA setup time at DRAM

	    t_dh = 250;  //DQ hold time at DRAM

	    t_ih = 250;  //CA hold time at DRAM

	    t_dcd_soc = 50;  //Duty-cycle distortion at the CPU/SOC

	    t_dcd_dram = 50;  //Duty-cycle distortion at the DRAM

	    t_error_soc = 50;  //Timing error due to edge placement uncertainty of the DLL

	    t_skew_setup = 50;  //Setup skew between DQ/DQS or CA/CLK after deskewing the lines

	    t_skew_hold = 50;  //Hold skew between DQ/DQS or CA/CLK after deskewing the lines

	    t_dqsq = 250;  //DQ-DQS skew at the DRAM output during Read

	    t_qhs = 250; //DQ-DQS hold factor at the DRAM output during Read
	      
	    t_soc_setup = 50; //Setup time at SOC input dueing Read

	    t_soc_hold = 50;  //Hold time at SOC input during Read

	    t_jitter_setup = 200; //Half-cycle jitter on the DQS at DRAM input affecting setup time

	    t_jitter_hold = 200; //Half-cycle jitter on the DQS at the DRAM input affecting hold time

	    t_jitter_addr_setup = 200; //Half-cycle jitter on the CLK at DRAM input affecting setup time

	    t_jitter_addr_hold = 200; //Half-cycle jitter on the CLK at the DRAM input affecting hold time





	    //Topology Parameters



            // Differential termination resister if used for CLK (Ohm) 

	    r_diff_term = 240;


            // ODT related termination resistor values (Ohm)

	    rtt1_dq_read = 100000; //DQ Read termination at CPU

	    rtt2_dq_read = 100000; //DQ Read termination at inactive DRAM

	    rtt1_dq_write = 100000; //DQ Write termination at active DRAM

	    rtt2_dq_write = 100000; //DQ Write termination at inactive DRAM

	    rtt_ca = 240; //CA fly-by termination

	    rs1_dq = 0; //Series resistor at active DRAM

	    rs2_dq = 0; //Series resistor at inactive DRAM

	    r_stub_ca = 0; //Series resistor for the fly-by channel

	    r_on = 50; //Driver impedance

	    r_on_ca = 50; //CA driver impedance

		 
		 //Line impedance (ohms): Characteristic impedance of the route.

	    z0 = 50;



            // Flight time of the interconnect (ns) (approximately 180ps/inch for FR4)

	    t_flight = 0.5;

            // Flight time of the Control/Address (CA) interconnect (ns) (approximately 180ps/inch for FR4)

	    t_flight_ca = 0.5;



            // Voltage noise coeffecients

	    k_noise_write = 0.2; //Proportional noise coefficient for Write mode

	    k_noise_read = 0.2; //Proportional noise coefficient for Read mode

	    k_noise_addr = 0.2; //Proportional noise coefficient for Address bus

	    v_noise_independent_write = 0.1; //Independent noise voltage for Write mode

	    v_noise_independent_read = 0.1; //Independent noise voltage for Read mode

	    v_noise_independent_addr = 0.1; //Independent noise voltage for Address bus
	    

	    //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE


	    //This is a user-defined section that depends on the channel sensitivity to IO and DRAM parameters. The t_jitter_* and k_noise_* are the parameters that are impacted based on the channel analysis. The user can define any relationship between the termination, loading and configuration parameters AND the t_jitter/k_noise parameters. E.g. a linear relationship, a non-linear analytical relationship or a lookup table. The sensitivity coefficients are based on channel analysis performed on the channel of interest.Given below is an example of such a sensitivity relationship

	    k_noise_write_sen = k_noise_write * (1 + 0.2*(r_on/34 - 1) + 0.2*(g_ip->num_mem_dq/2 - 1));

	    k_noise_read_sen = k_noise_read * (1 + 0.2*(r_on/34 - 1) + 0.2*(g_ip->num_mem_dq/2 - 1));

	    k_noise_addr_sen = k_noise_addr * (1 + 0.1*(rtt_ca/100 - 1) + 0.2*(r_on/34 - 1) + 0.2*(num_mem_ca/16 - 1));


	    t_jitter_setup_sen = t_jitter_setup * (1  + 0.1*(r_on/34 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

	    t_jitter_hold_sen = t_jitter_hold * (1 + 0.1*(r_on/34 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

	    t_jitter_addr_setup_sen = t_jitter_addr_setup * (1 + 0.2*(rtt_ca/100 - 1) + 0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));

	    t_jitter_addr_hold_sen = t_jitter_addr_hold * (1 + 0.2*(rtt_ca/100 - 1) + 0.1*(r_on/34 - 1) + 0.4*(num_mem_ca/16 - 1));




	  }




///WIDEIO


        if (g_ip->dram_type == 'W')
	  {
	    
	    //Technology Parameters

            // IO Supply voltage (V) 

	    vdd_io = 1.2;

            // Voltage swing on CLK/CLKB (V) (swing on the CLK pin if it is differentially terminated).

	    v_sw_clk =  1.2;

            // Loading parameters

	    c_int = 0.5; //Internal IO loading (pF) (loading within the IO, due to predriver nets)

	    c_tx = 0.5;  //IO TX self-load including package (pF) (loading at the CPU TX pin)

	    c_data = 0.5;  //Device loading per memory data pin (pF) (DRAM device load for DQ per die)

	    c_addr = 0.35; //Device loading per memory address pin (pF) (DRAM device load for CA per die)


            // Bias current (mA) (includes bias current for the whole memory bus due to RX Vref based receivers

	    i_bias =  0; 

            // Active leakage current per pin (nA) 

	    i_leak = 500; 



            // IO Area coefficients

	    ioarea_c = 0.003; // sq.mm. (IO Area baseline coeeficient for control circuitry and overhead)

	    ioarea_k0 = 0.2; // sq.mm * ohms (IO Area coefficient for the driver, for unit drive strength or output impedance)

	    ioarea_k1 = 0.00004; // sq.mm * ohms / MHz (IO Area coefficient for the predriver final stage, based on fanout needed)

	    ioarea_k2 = 0.000000020; // sq.mm * ohms / MHz^2 (IO Area coefficient for predriver middle stage, based on fanout needed)

	    ioarea_k3 = 0.000000000004; // sq.mm * ohms / MHz^3 (IO Area coefficient for predriver first stage, based on fanout needed)


            // Timing parameters (ps)

	    t_ds = 250;  //DQ setup time at DRAM

	    t_is = 250;  //CA setup time at DRAM

	    t_dh = 250;  //DQ hold time at DRAM

	    t_ih = 250;  //CA hold time at DRAM

	    t_dcd_soc = 50;  //Duty-cycle distortion at the CPU/SOC

	    t_dcd_dram = 50;  //Duty-cycle distortion at the DRAM

	    t_error_soc = 50;  //Timing error due to edge placement uncertainty of the DLL

	    t_skew_setup = 50;  //Setup skew between DQ/DQS or CA/CLK after deskewing the lines

	    t_skew_hold = 50;  //Hold skew between DQ/DQS or CA/CLK after deskewing the lines

	    t_dqsq = 250;  //DQ-DQS skew at the DRAM output during Read

	    t_qhs = 250; //DQ-DQS hold factor at the DRAM output during Read
	      
	    t_soc_setup = 50; //Setup time at SOC input dueing Read

	    t_soc_hold = 50;  //Hold time at SOC input during Read

 	    t_jitter_setup = 200; //Half-cycle jitter on the DQS at DRAM input affecting setup time

	    t_jitter_hold = 200; //Half-cycle jitter on the DQS at the DRAM input affecting hold time

	    t_jitter_addr_setup = 200; //Half-cycle jitter on the CLK at DRAM input affecting setup time

	    t_jitter_addr_hold = 200; //Half-cycle jitter on the CLK at the DRAM input affecting hold time

            



	    //Topology Parameters



            // Differential termination resister if used for CLK (Ohm) 

	    r_diff_term = 100000;


            // ODT related termination resistor values (Ohm)

	    rtt1_dq_read = 100000; //DQ Read termination at CPU

	    rtt2_dq_read = 100000; //DQ Read termination at inactive DRAM

	    rtt1_dq_write = 100000; //DQ Write termination at active DRAM

	    rtt2_dq_write = 100000; //DQ Write termination at inactive DRAM

	    rtt_ca = 240; //CA fly-by termination

	    rs1_dq = 0; //Series resistor at active DRAM

	    rs2_dq = 0; //Series resistor at inactive DRAM

	    r_stub_ca = 0; //Series resistor for the fly-by channel

	    r_on = 75; //Driver impedance

	    r_on_ca = 75; //CA driver impedance
 


		//Line impedance (ohms): Characteristic impedance of the route.

	    z0 = 50;




            // Flight time of the interconnect (ns) (approximately 180ps/inch for FR4)

	    t_flight = 0.05;

            // Flight time of the Control/Address (CA) interconnect (ns) (approximately 180ps/inch for FR4)

	    t_flight_ca = 0.05;



            // Voltage noise coeffecients

	    k_noise_write = 0.2; //Proportional noise coefficient for Write mode

	    k_noise_read = 0.2; //Proportional noise coefficient for Read mode

	    k_noise_addr = 0.2; //Proportional noise coefficient for Address bus

	    v_noise_independent_write = 0.1; //Independent noise voltage for Write mode

	    v_noise_independent_read = 0.1; //Independent noise voltage for Read mode

	    v_noise_independent_addr = 0.1; //Independent noise voltage for Address bus


	    //SENSITIVITY INPUTS FOR TIMING AND VOLTAGE NOISE


	    //This is a user-defined section that depends on the channel sensitivity to IO and DRAM parameters. The t_jitter_* and k_noise_* are the parameters that are impacted based on the channel analysis. The user can define any relationship between the termination, loading and configuration parameters AND the t_jitter/k_noise parameters. E.g. a linear relationship, a non-linear analytical relationship or a lookup table. The sensitivity coefficients are based on channel analysis performed on the channel of interest.Given below is an example of such a sensitivity relationship

	    k_noise_write_sen = k_noise_write * (1 + 0.2*(r_on/50 - 1) + 0.2*(g_ip->num_mem_dq/2 - 1));

	    k_noise_read_sen = k_noise_read * (1 + 0.2*(r_on/50 - 1) + 0.2*(g_ip->num_mem_dq/2 - 1));

	    k_noise_addr_sen = k_noise_addr * (1 + 0.2*(r_on/50 - 1) + 0.2*(num_mem_ca/16 - 1));


	    t_jitter_setup_sen = t_jitter_setup * (1  + 0.1*(r_on/50 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

	    t_jitter_hold_sen = t_jitter_hold * (1 + 0.1*(r_on/50 - 1) + 0.3*(g_ip->num_mem_dq/2 - 1));

	    t_jitter_addr_setup_sen = t_jitter_addr_setup * (1 + 0.1*(r_on/50 - 1) + 0.4*(num_mem_ca/16 - 1));

	    t_jitter_addr_hold_sen = t_jitter_addr_hold * (1 + 0.1*(r_on/50 - 1) + 0.4*(num_mem_ca/16 - 1));






	  }



	//SWING AND TERMINATION CALCULATIONS

	//R|| calculation

        double rpar_write =(rtt1_dq_write + rs1_dq)*(rtt2_dq_write + rs2_dq)/(rtt1_dq_write + rs1_dq + rtt2_dq_write + rs2_dq);

        double rpar_read =(rtt1_dq_read)*(rtt2_dq_read + rs2_dq)/(rtt1_dq_read + rtt2_dq_read + rs2_dq);

	//Swing calculation

        double v_sw_data_read_load1 =vdd_io * (rtt1_dq_read)*(rtt2_dq_read + rs2_dq) / ((rtt1_dq_read + rtt2_dq_read + rs2_dq)*(r_on + rs1_dq + rpar_read)); //Swing for DQ at dram1 during READ

        double v_sw_data_read_load2 =vdd_io * (rtt1_dq_read)*(rtt2_dq_read) / ((rtt1_dq_read + rtt2_dq_read + rs2_dq)*(r_on + rs1_dq + rpar_read)); //Swing for DQ at dram2 during READ

        double v_sw_data_read_line =vdd_io * rpar_read / (r_on + rs1_dq + rpar_read); //Swing for DQ on the line during READ

	double v_sw_addr =vdd_io * rtt_ca / (50 + rtt_ca); //Swing for the address bus
	
	double v_sw_data_write_load1 =vdd_io * (rtt1_dq_write)*(rtt2_dq_write + rs2_dq) / ((rtt1_dq_write + rs1_dq + rtt2_dq_write + rs2_dq)*(r_on + rpar_write)); //Swing for DQ at dram1 during WRITE

        double v_sw_data_write_load2 =vdd_io * (rtt2_dq_write)*(rtt1_dq_write + rs1_dq) / ((rtt1_dq_write + rs1_dq + rtt2_dq_write + rs2_dq)*(r_on + rpar_write)); //Swing for DQ at dram2 during WRITE

        double v_sw_data_write_line =vdd_io * rpar_write / (r_on + rpar_write); //Swing for DQ on the line during WRITE





	
}
