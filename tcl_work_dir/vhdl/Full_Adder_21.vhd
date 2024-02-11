
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Approximate Full Adder

-- Module Name: full_adder_21

-- Revisions:
-- 
-- Additional Comments: Sum & Carry Approximation
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder_21 is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           c 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end full_adder_21;

architecture Behavioral of full_adder_21 is

begin

--========== APPROX SUM & CARRY ============

--AFA21
sum <= (b and (not c)) or (a and (not c)) or (a and b);
carry   <= c;

end Behavioral;