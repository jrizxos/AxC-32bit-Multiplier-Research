
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Approximate Full Adder

-- Module Name: full_adder_17

-- Revisions:
-- 
-- Additional Comments: Sum & Carry Approximation
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder_17 is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           c 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end full_adder_17;

architecture Behavioral of full_adder_17 is

begin

--========== APPROX SUM & CARRY ============

--AFA17
sum <= ((not a) and (not c)) or ((not b) and (not c)) or (a and b and c);
carry <= ((not a) and c) or ((not b) and c) or (a and b and (not c));

end Behavioral;