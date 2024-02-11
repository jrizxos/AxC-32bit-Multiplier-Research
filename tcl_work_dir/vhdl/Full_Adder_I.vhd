
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Approximate Full Adder

-- Module Name: full_adder_i

-- Revisions:
-- 
-- Additional Comments: Carry Approximation
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder_i is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           c 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end full_adder_i;

architecture Behavioral of full_adder_i is

begin

--============= APPROXIMATE CARRY ===============

--AFA I
sum 	<= (a xor b xor c); --NO APPROX
carry <= (not (a xor b xor c)); --!sum

end Behavioral;