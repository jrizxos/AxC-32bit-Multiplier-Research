
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Approximate Full Adder

-- Module Name: full_adder_13

-- Revisions:
-- 
-- Additional Comments: Carry Approximation
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder_13 is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           c 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end full_adder_13;

architecture Behavioral of full_adder_13 is

begin

--============= APPROXIMATE CARRY ===============

--AFA13
sum 	<= (a xor b xor c); --NO APPROX
carry <= c;

end Behavioral;