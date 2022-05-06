-------------------------------------------------------------------------------
-- Practica2_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity Practica2_stub is
  port (
    RX_pin : in std_logic;
    TX_pin : out std_logic;
    Rst_pin : in std_logic;
    Clk_pin : in std_logic;
    lcd_rw_pin : out std_logic;
    lcd_rs_pin : out std_logic;
    lcd_e_pin : out std_logic;
    lcd_data_pin : out std_logic_vector(7 downto 0);
    sonido_pin : out std_logic;
    control_motor_pin : out std_logic_vector(3 downto 0);
    S_pin : out std_logic_vector(3 downto 0);
    R_pin : in std_logic_vector(3 downto 0)
  );
end Practica2_stub;

architecture STRUCTURE of Practica2_stub is

  component Practica2 is
    port (
      RX_pin : in std_logic;
      TX_pin : out std_logic;
      Rst_pin : in std_logic;
      Clk_pin : in std_logic;
      lcd_rw_pin : out std_logic;
      lcd_rs_pin : out std_logic;
      lcd_e_pin : out std_logic;
      lcd_data_pin : out std_logic_vector(7 downto 0);
      sonido_pin : out std_logic;
      control_motor_pin : out std_logic_vector(3 downto 0);
      S_pin : out std_logic_vector(3 downto 0);
      R_pin : in std_logic_vector(3 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of Practica2 : component is "user_black_box";

begin

  Practica2_i : Practica2
    port map (
      RX_pin => RX_pin,
      TX_pin => TX_pin,
      Rst_pin => Rst_pin,
      Clk_pin => Clk_pin,
      lcd_rw_pin => lcd_rw_pin,
      lcd_rs_pin => lcd_rs_pin,
      lcd_e_pin => lcd_e_pin,
      lcd_data_pin => lcd_data_pin,
      sonido_pin => sonido_pin,
      control_motor_pin => control_motor_pin,
      S_pin => S_pin,
      R_pin => R_pin
    );

end architecture STRUCTURE;

