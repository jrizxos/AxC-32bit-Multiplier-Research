import base64
import random
import struct
from bitarray import bitarray
from typing import List

VAR_N = 918                         # number of variables per individual
VAR_D = ['full_adder',              # domain of each variable
         'full_adder_i',
         'full_adder_ii',
         'full_adder_iii']                            \
      + ['full_adder_'+str(i) for i in range(1,9)]    \
      + ['full_adder_'+str(i) for i in range(10,18)]  \
      + ['full_adder_'+str(i) for i in range(19,28)]

BIT_W = 5                           # number of possible variables bit width (e.g. 32 possible = 5 bits) 

# individual name / loaded_id abbreviations:
# ld = loaded from highscores file into tree
# lr = loaded from file raw into list of individuals
# in = generated from random intialization
# cm = generated from combination
# mt = generated from random mutation 

class individual:

    def __init__(self, initial_vals: List[int], name:str):
        """Initializes an individual object.

        Args:
            self (individual): self
            initial_score (int): precalculated score for this individual
            initial_vals (list of ints): initial values for the variables

        Returns:
            New individual
        """
        # variable values
        if(initial_vals == None):
            self.rand_init()
        else:
            self.vars = initial_vals
        # evaluation results
        self.mae = None
        self.area = None
        self.time = None
        self.power = None
        # simple name
        self.loaded_id = name
        # NSGA-II values
        self.rank = None
        self.distance = None
        self.dominates = None
        self.dom_count = None
        return
    
    def rand_init(self):
        """Initializes an individual's variables to random values.

        Args:
            self (individual): self

        Returns:
            None
        """
        self.vars = []
        for i in range(VAR_N):
            self.vars.append(random.choice(range(len(VAR_D))))
        return

    def name(self):
        """Returns an individual's name based on it's variable values.

        Args:
            self (individual): self

        Returns:
            name(str): the individual's name
        """
        name = ''
        for var in self.vars[:-1]:
            name += str(var) + '.'
        name += str(self.vars[-1])
        return name

    def shorter_name(self):
        """Returns an individual's base 64 name based on it's variable values.

        Args:
            self (individual): self

        Returns:
            number(str): the individual's b64 name
        """
        number = self.number()
        num_bytes = number.to_bytes(length=25, byteorder='big')
        enc_bytes = base64.b64encode(num_bytes)
        return str(enc_bytes)[2:-1]

    def number(self):
        """Returns an individual's hash number based on it's variable values.

        Args:
            self (individual): self

        Returns:
            hash(int): the individual's hash
        """
        binary = ''
        for var in self.vars:
            binary += get_binary(var)
        hash = int(binary, base=2)
        return hash

    def report(self):
        """Returns a string reporting the individual's performance in simulation.

        Args:
            self (individual): self

        Returns:
            print_out(str): the individual's report
        """
        print_out = 'MAE = ' + str(self.mae) + '\n'
        print_out += 'area = '+ str(self.area) + ' μm^2\n'
        print_out += 'slack = '+ str(self.time) + ' ps\n'
        print_out += 'power = '+ str(self.power) + 'W \n'
        return print_out

    def __str__(self):
        """Returns the individual's string descriptor.

        Args:
            self (individual): self

        Returns:
            print_out (str): object as str
        """
        print_out = "Individual \"" + str(self.loaded_id) + '\"\n'
        print_out += 'Report:\n' + self.report()
        return print_out 

def get_binary(a:int):
    """Creates a binary string of length BIT_W with the bits of a

        Args:
            a (int): a number to conver to binary

        Returns:
            bits (str): the bits of a
    """
    enc_bits = bitarray(endian='little')            # get a bitarray object
    enc_bytes = struct.pack('i', a)                 # get bytes of number
    enc_bits.frombytes(enc_bytes)                   # get bitarray from bytes
    return enc_bits[0:BIT_W].to01()[::-1]           # export bits as string, sliced down to BIT_W and reversed