
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Output Register (64 bits)

-- Module Name: out_reg

-- Revisions:
-- 
-- Additional Comments: 
--
--------------------------------------------------------------------------------------

Library IEEE;
use IEEE.std_logic_1164.all;

entity out_reg is
	
	port ( signal out_reg_wr	 : in std_logic; 
			 signal out_reg_rst	 : in std_logic; 
			 signal clk				 : in std_logic;
			 signal out_reg_input : in  std_logic_vector(63 downto 0) ;
			 signal out_reg_output: out std_logic_vector(63 downto 0));
end out_reg;

architecture Behavioral of out_reg is

begin

process(clk) is
   begin
		
		if rising_edge(clk) then
			
			if(out_reg_wr = '1') then		
		
				out_reg_output <= out_reg_input;
			 
			elsif (out_reg_rst = '1') then
			
				out_reg_output <= "0000000000000000000000000000000000000000000000000000000000000000";--64
			
			end if;
			
		end if;
		
end process;

end Behavioral;
