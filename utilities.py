import base64
import numpy as np
import pandas as pd
from typing import List
from bitarray import bitarray
from score_tree import load_raw
from search import VAR_N, BIT_W, individual, EXACT, UNITS

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
