
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Input Register (32 bits)

-- Module Name: in_reg

-- Revisions:
-- 
-- Additional Comments: 
--
--------------------------------------------------------------------------------------

Library IEEE;
use IEEE.std_logic_1164.all;

entity in_reg is
	
	port ( signal in_reg_wr		: in std_logic; 
			 signal in_reg_rst	: in std_logic; 
			 signal clk				: in std_logic;
			 signal in_reg_input : in  std_logic_vector(31 downto 0) ;
			 signal in_reg_output: out std_logic_vector(31 downto 0));
end in_reg;

architecture Behavioral of in_reg is

begin

process(clk) is
   begin
		
		if rising_edge(clk) then
			
			if(in_reg_wr = '1') then		
		
				in_reg_output <= in_reg_input;
			 
			elsif (in_reg_rst = '1') then
			
				in_reg_output <= "00000000000000000000000000000000";--32
			
			end if;
			
		end if;
		
end process;

end Behavioral;
