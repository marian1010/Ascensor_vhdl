------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Tue Dec 14 12:09:27 2021 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--   C_NUM_REG                    -- Number of software accessible registers
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Reset                 -- Bus to IP reset
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    --USER generics added here
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_REG                      : integer              := 4
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    S : out  STD_LOGIC_VECTOR (3 downto 0);
    R : in  STD_LOGIC_VECTOR (3 downto 0);
	control_motor: out std_logic_vector (3 downto 0); 
	sonido                     	  : out  std_logic;
    -- ADD USER PORTS ABOVE THIS LINE ------------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Reset                   : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(0 to C_SLV_DWIDTH-1);
    Bus2IP_BE                      : in  std_logic_vector(0 to C_SLV_DWIDTH/8-1);
    Bus2IP_RdCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    Bus2IP_WrCE                    : in  std_logic_vector(0 to C_NUM_REG-1);
    IP2Bus_Data                    : out std_logic_vector(0 to C_SLV_DWIDTH-1);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute MAX_FANOUT : string;
  attribute SIGIS : string;

  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Reset  : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  --USER signal declarations added here, as needed for user logic
	constant motor_inic: std_logic_vector(0 to 7):="01000000";
	
    component teclaDetect is
    Port ( reloj : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           S : out  STD_LOGIC_VECTOR (3 downto 0);
           R : in  STD_LOGIC_VECTOR (3 downto 0);
           KeyCode : out  STD_LOGIC_VECTOR (3 downto 0);
			  keyPressed: out std_logic
	);
	end component;
  -- Signals for user logic slave model s/w accessible register example
  
    SIGNAL cs : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  SIGNAL q : std_logic;
   signal motor_ctl                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal motor_step                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  ------------------------------------------
  signal slv_reg0                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg1                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg2                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg3                       : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_reg_write_sel              : std_logic_vector(0 to 3);
  signal slv_reg_read_sel               : std_logic_vector(0 to 3);
  signal slv_ip2bus_data                : std_logic_vector(0 to C_SLV_DWIDTH-1);
  signal slv_read_ack                   : std_logic;
  signal slv_write_ack                  : std_logic;
  
  signal   motor_ce, motor_clk, clk_fast :   STD_LOGIC;
  signal   dir :   STD_LOGIC;
  signal         stop :  STD_LOGIC;
  signal         halfstep :  STD_LOGIC;
  signal         step : STD_LOGIC_VECTOR (0 to 2);
  signal internal_dir, internal_stop, internal_halfstep : std_logic;
  signal KeyCode, signalS :  STD_LOGIC_VECTOR (3 downto 0);
  signal keyPressed:  std_logic;

  signal reloj12,reloj, rst: std_logic;
begin
S<= signalS;
  --USER logic implementation added here

  ------------------------------------------
  -- Example code to read/write user logic slave model s/w accessible registers
  -- 
  -- Note:
  -- The example code presented here is to show you one way of reading/writing
  -- software accessible registers implemented in the user logic slave model.
  -- Each bit of the Bus2IP_WrCE/Bus2IP_RdCE signals is configured to correspond
  -- to one software accessible register by the top level template. For example,
  -- if you have four 32 bit software accessible registers in the user logic,
  -- you are basically operating on the following memory mapped registers:
  -- 
  --    Bus2IP_WrCE/Bus2IP_RdCE   Memory Mapped Register
  --                     "1000"   C_BASEADDR + 0x0
  --                     "0100"   C_BASEADDR + 0x4
  --                     "0010"   C_BASEADDR + 0x8
  --                     "0001"   C_BASEADDR + 0xC
  -- 
  ------------------------------------------
  slv_reg_write_sel <= Bus2IP_WrCE(0 to 3);
  slv_reg_read_sel  <= Bus2IP_RdCE(0 to 3);
  slv_write_ack     <= Bus2IP_WrCE(0) or Bus2IP_WrCE(1) or Bus2IP_WrCE(2) or Bus2IP_WrCE(3);
  slv_read_ack      <= Bus2IP_RdCE(0) or Bus2IP_RdCE(1) or Bus2IP_RdCE(2) or Bus2IP_RdCE(3);

  TeclaDetecInst: teclaDetect
	port map
	(reloj => reloj12,
	reset=> rst,
	S => signalS,
	R => R ,
	KeyCode => KeyCode,
	keyPressed => keyPressed
	);
  reloj <= Bus2IP_Clk;
  rst<= not Bus2IP_Reset;

divisor:
  -- divide entre 4 la frecuencia de reloj
  PROCESS (rst, reloj)
  --  CONSTANT timeOut: std_logic_vector (19 DOWNTO 0) := "10011000100101101000";
CONSTANT num: std_logic_vector (3 DOWNTO 0) :=	"0010";
   VARIABLE count: std_logic_vector (3 DOWNTO 0);
  BEGIN
   IF (rst='0') THEN
      count := (OTHERS=>'0');
		reloj12<= '0';
    ELSIF (reloj'EVENT AND reloj='1') THEN
      IF (count=num) THEN
       reloj12<= not reloj12;
		 count := (OTHERS=>'0');
      ELSE 
		count := count + 1;
      END IF;
    END IF;
  END PROCESS divisor;	
  
  
  
	 motor_step_entity:  entity my_multiple_periferic_v1_00_a.motorstep 
		port map ( clk => motor_clk,
			   rst =>not Bus2IP_Reset ,
			   dir => dir,
			   stop => stop,
				  halfstep => halfstep,
			   motor => control_motor,
				  step => step);

	divisor_frec: entity my_multiple_periferic_v1_00_a.one_hundred_k_counter 
		port map ( clk => Bus2IP_Clk,
			   rst =>not Bus2IP_Reset ,
				  clk_10 =>motor_clk, -- 256 count
			   ce_10=> motor_ce);
				  


	internal_dir      <= motor_ctl(0);
	internal_stop     <= motor_ctl(1);
	internal_halfstep <= motor_ctl(2);

	dir <= internal_dir;
	stop <= internal_stop;
	halfstep <= internal_halfstep;



	process (Bus2IP_Clk, Bus2IP_Reset)
	begin
	if (Bus2IP_Reset='1') then
	  motor_step <= (others => '0');
	  elsif (Bus2IP_Clk'event and Bus2IP_Clk='1') then 
	  motor_step (0 to 2) <= step;
	end if;
	end process;

  
  
  -- implement slave model software accessible register(s)
  SLAVE_REG_WRITE_PROC : process( Bus2IP_Clk ) is
  begin

    if Bus2IP_Clk'event and Bus2IP_Clk = '1' then
      if Bus2IP_Reset = '1' then
        slv_reg0 <= (others => '0');
        slv_reg1 <= (others => '0');
        slv_reg2 <= (others => '0');
        slv_reg3 <= (others => '0');
		motor_ctl(0 to 7) <= motor_inic;
		motor_ctl (8 to 31) <= (others => '0');
      else
        case slv_reg_write_sel is
          when "1000" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg0(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0100" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg1(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0010" =>
             for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                motor_ctl(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when "0001" =>
            for byte_index in 0 to (C_SLV_DWIDTH/8)-1 loop
              if ( Bus2IP_BE(byte_index) = '1' ) then
                slv_reg3(byte_index*8 to byte_index*8+7) <= Bus2IP_Data(byte_index*8 to byte_index*8+7);
              end if;
            end loop;
          when others =>
			if (keyPressed = '1') then
					 slv_reg0(0 to 3) <= KeyCode(3 downto 0); -- La tecla pulsada se carga bits 0-3
			end if;
			if (internal_stop='0') then
				if (motor_ce='1') then
					if (motor_ctl(4 to 7)=("0000")) then
						motor_ctl(1) <= '1'; -- se detiene el motor
					else
						motor_ctl(4 to 7) <= motor_ctl(4 to 7) - 1; -- decrementa n_steps
					end if;
				end if;
			end if;	
        end case;
      end if;
    end if;

  end process SLAVE_REG_WRITE_PROC;

  -- implement slave model software accessible register(s) read mux
  SLAVE_REG_READ_PROC : process( slv_reg_read_sel, slv_reg0, slv_reg1,motor_ctl, motor_step ) is
  begin

    case slv_reg_read_sel is
      when "1000" => slv_ip2bus_data <= slv_reg0;  --teclado
      when "0100" => slv_ip2bus_data <= slv_reg1;  --speker
      when "0010" => slv_ip2bus_data <= motor_ctl; --motor
      when "0001" => slv_ip2bus_data <= motor_step;--motor
      when others => slv_ip2bus_data <= (others => '0');
    end case;

  end process SLAVE_REG_READ_PROC;

  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= slv_ip2bus_data when slv_read_ack = '1' else
                  (others => '0');

  IP2Bus_WrAck <= slv_write_ack;
  IP2Bus_RdAck <= slv_read_ack;
  IP2Bus_Error <= '0';
  

  --------------------------
  -- GENERADOR DEL SONIDO --
  --------------------------
  altavoz_p: PROCESS(Bus2IP_Clk, Bus2IP_Reset)
  BEGIN
    IF(Bus2IP_Reset='1')THEN
      q <= '0';
		cs <= (OTHERS=>'0');
    ELSIF(Bus2IP_Clk'event and Bus2IP_Clk='1') THEN	
		 IF (slv_write_ack = '1') THEN
			q <= '0';
			cs <= (OTHERS=>'0');
		 ELSIF (slv_reg1 = cs) THEN
			cs <= (OTHERS=>'0');
			q <= not q;
		 ELSE
			cs <= cs + 1;
			q <= q;
		 END IF;
    END IF;
   END PROCESS;
	
	sonido <= q;

end IMP;
