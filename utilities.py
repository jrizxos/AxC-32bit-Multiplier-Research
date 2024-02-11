import base64
import numpy as np
import pandas as pd
from typing import List
from bitarray import bitarray
from score_tree import load_raw, load_tree, find_individual
from search import VAR_N, BIT_W, get_ints, individual, EXACT, UNITS

def convert_64_to_vals(s:str):
    """Converts a base64 Individual name to the list of corresponding variable values

        Args:
            s (str): base64 encoded str

        Returns:
            vals (list of ints): the variable values
    """
    vals = []
    dec_bytes = base64.standard_b64decode(s)
    enc_bits = bitarray(endian='big')               # get a bitarray object
    enc_bits.frombytes(dec_bytes)                   # get bitarray from bytes
    enc_str = enc_bits.to01()                       # get str of bits
    enc_str = enc_str[len(enc_str)-BIT_W*VAR_N:]
    vals = get_ints(enc_str)
    return vals

def convert_64_to_16(s:str):
    """Converts a base64 Individual name to the corresponding base16 Individual name

        Args:
            s (str): base64 encoded str

        Returns:
            (str): corresponding base16 str
    """
    vals = convert_64_to_vals(s)
    ind = individual(vals)
    return ind.loaded_id

def convert_16_to_vals(s:str):
    dec_int = int(s, base=16)
    enc_bits = bitarray(endian='big')
    enc_bits.frombytes(dec_int.to_bytes(length=25,byteorder='big'))
    enc_str = enc_bits.to01()
    enc_str = enc_str[len(enc_str)-BIT_W*VAR_N:]
    vals = get_ints(enc_str)
    return vals

def convert_16_to_64(s:str):
    """Converts a base16 Individual name to the corresponding base64 Individual name

        Args:
            s (str): base16 encoded str

        Returns:
            (str): corresponding base64 str
    """
    vals = convert_16_to_vals(s)
    ind = individual(vals)
    return ind.shorter_name()

def convert_int_to_vals(i:int):
    enc_bits = bitarray(endian='big')
    enc_bits.frombytes(i.to_bytes(length=25,byteorder='big'))
    enc_str = enc_bits.to01()
    enc_str = enc_str[len(enc_str)-BIT_W*VAR_N:]
    vals = get_ints(enc_str)
    return vals

def get_dataframe(highscores:List[individual]):
    """Creates a pandas dataframe from an idividual database dictionary.

        Args:
            highscores (dict[name: individual]): idividual database dictionary

        Returns:
            dt (DataFrame): generated pandas dataframe
    """
    dt = pd.DataFrame(columns = ['id', 'mae', 'area', 'time', 'power', 'vars'])

    for ind in highscores:
        dt.loc[len(dt.index)] = [ind.loaded_id, ind.mae, ind.area, ind.time, ind.power, ind.vars]
    return dt

def describe_dataframe(dt:pd.DataFrame, name):
    """Prints a summary of the data of a dataframe created with utilities.get_dataframe()

        Args:
            dt (DataFrame): generated pandas dataframe

        Returns:
            None
    """
    print(name,'stats:')
    print('sample count =', len(dt))
    if(not len(dt)>0):
        print()
        return
    dt_describe = dt.describe()
    dt_describe.loc['norm'] = EXACT
    dt_describe.rename(columns={'area':'area ('+UNITS['area']+')', 
                                'time':'time ('+UNITS['time']+')', 
                                'power':'power ('+UNITS['power']+')'}, inplace=True)
    #dt_describe.loc['units'] = UNITS
    print(dt_describe.iloc[[1,2,3,7,8]], '\n')
    return

def worst_case_MAE():
    """Calculates the worst case maximum MSE that might be achieved with
        the inputs from cppsim/inp.bin. Needed for NSGA-II partial order sorting.

        Args:
            None

        Returns:
            error (int): maximum possible error
    """
    TEST_INP = 10000000
    MAX_LONG = 18446744073709551615 #(64bits)
    HALF_MAX = 4294967295

    inp_file = open('cppsim/inp.bin', 'rb')

    error = 0
    for i in range(TEST_INP):
        by1 = inp_file.read(4)
        by2 = inp_file.read(4)
        a =  int.from_bytes(by1, byteorder='little')
        b =  int.from_bytes(by2, byteorder='little')
        exp = a*b
        if(exp>HALF_MAX):
            error += int(exp/TEST_INP)
        else:
            error += int((MAX_LONG - exp)/TEST_INP)

    inp_file.close()
    return error
    
############################################## TEST ###############################################

if __name__ == '__main__':
    describe_dataframe(get_dataframe(load_raw(FILE='pareto-final.json')), 'pareto-final')
    describe_dataframe(get_dataframe(load_raw(FILE='pareto-optimized.json')), 'pareto-optimized')