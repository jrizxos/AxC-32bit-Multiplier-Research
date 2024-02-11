
--------------------------------------------------------------------------------------
-- Company Name: Department of Computer Science & Engineering / University of Ioannina 

-- Engineer: Georgios Papatheodorou

-- Module: Full Adder

-- Module Name: full_adder

-- Revisions:
-- 
-- Additional Comments: 
--
--------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder is
    port ( a 		: in  STD_LOGIC;
           b 		: in  STD_LOGIC;
           c 		: in  STD_LOGIC;
           sum 	: out  STD_LOGIC;
           carry 	: out  STD_LOGIC);
end full_adder;

architecture Behavioral of full_adder is

begin

--Non AxC Full Adder
sum 	<= (a xor b xor c);
carry <= (a and b) or (c and (a xor b));

--========== APPROX SUM & CARRY ============

--AFA23
--sum   <= c;
--carry <= (b and (not c)) or (a and (not c)) or (a and b);

--AFA22
--sum 	<= b;
--carry <= a;

--AFA21
--sum <= (b and (not c)) or (a and (not c)) or (a and b);
--carry   <= c;
  
--AFA20
--sum <= (not c) or (a and b);
--carry <= c or (a and b);

--AFA19
--sum <= c or ((not a) and b) or (a and (not b));
--carry <= a and b;

--AFA17
--sum <= ((not a) and (not c)) or ((not b) and (not c)) or (a and b and c);
--carry <= ((not a) and c) or ((not b) and c) or (a and b and (not c));

--AFA15
--sum <= ((not a) and (not c)) or ((not b) and (not c));
--carry <= c or (a and b);

--AFA12
--sum <= a;
--carry <= a;

--AFA11
--sum <= ((not a) or b) and c;
--carry <= a;

--AFA10
--sum <= ((not a) and (not b)) or ((not b) and (not c));
--carry <= b or (a and c);

--AFA8
--sum <= ((not a) and (not b) and c) or (a and b and c);
--carry <= b or (a and c);

--AFA1
--sum <= (not a) or (b and c);
--carry <= a;

--============= NON  APPROXIMATE CARRY ===============

--AFA24
--sum   <= ((not a) and (not b)) or (a and b);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA26
--sum   <= a or b or c;
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA27
--sum   <= a and b and c;
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA16
--sum   <= ((not a) and (not b)) or ((not a) and (not c));
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA5
--sum   <= (not a) or (b and c);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA3
--sum   <= ((not a) or b) and c;
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA28
--sum   <= ((not a) and (not b)) or ((not a) and (not c)) or ((not b) and (not c));
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA25
--sum   <= ((not a) and (not b) and c) or (a and b and c);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA18
--sum   <= ((not a) and (not b)) or (a and b);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA14
--sum   <= c or ((not a) and b) or (a and (not b));
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA9
--sum   <= ((not a) and (not b)) or ((not a) and (not c)) or ((not b) and (not c));
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA6
--sum   <= ((not a) and (not b)) or ((not a) and (not c)) or ((not b) and (not c));
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA2
--sum   <= ((not a) and (b or c)) or (b and c);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA7
--sum   <= ((not b) and (not c)) or ((not a) and (not c)) or ((not a) and (not b)) or ((not a) and (not b) and c);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--AFA4
--sum   <= ((not a) and (not b)) or ((not a) and (not c)) or ((not b) and (not c)) or (a and b and c);
--carry <= (a and b) or (c and (a xor b)); ---NO APPROX

--============= NON  APPROXIMATE SUM ===============

--AFA13
--sum 	<= (a xor b xor c); --NO APPROX
--carry <= c;

--AFA I
--sum 	<= (a xor b xor c); --NO APPROX
--carry <= (not sum);

--AFA II
--sum 	<= (a xor b xor c); --NO APPROX
--carry <= a;

--AFA III
--sum 	<= (a xor b xor c); --NO APPROX
--carry <= b;



end Behavioral;