
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Approximate Full Adder

-- Module Name: full_adder_7

-- Revisions:
-- 
-- Additional Comments: Sum Approximation
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder_7 is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           c 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end full_adder_7;

architecture Behavioral of full_adder_7 is

begin

--============= APPROXIMATE SUM ===============

--AFA7
sum   <= ((not b) and (not c)) or ((not a) and (not c)) or ((not a) and (not b)) or ((not a) and (not b) and c);
carry <= (a and b) or (c and (a xor b)); ---NO APPROX

end Behavioral;