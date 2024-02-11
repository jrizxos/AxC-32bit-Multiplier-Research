
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Half Adder

-- Module Name: half_adder

-- Revisions:
-- 
-- Additional Comments: 
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity half_adder is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end half_adder;

architecture Behavioral of half_adder is

begin

sum 	<= a xor b;
carry <= a and b;

end Behavioral;
