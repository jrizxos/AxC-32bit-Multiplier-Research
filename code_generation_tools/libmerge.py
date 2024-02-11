import os

'''Generates the .lib file from the gf180mcu-pdk to be used
    by Cadence Genus 21.
    (requires that you run "git submodule update --init --recursive" in this repository)
'''

LIBRARY = 'gf180mcu-pdk'
SUB_1 = 'libraries'
SUB_2 = 'gf180mcu_fd_sc_mcu7t5v0'
SUB_3 = 'latest'
CELL_FLDR = 'cells'
LIB_FLDR = 'liberty'
SUFFIX = '_025C_1v80'
END = SUFFIX + '.lib'
OUT = 'gf180mcu.lib'
CWD = os.getcwd()

def remove_comments(lines):
    popidx = []
    for i,line in enumerate(lines):
        if(line.strip().startswith('/*')):
            popidx.append(i)
        elif(line.strip().startswith('*')):
            popidx.append(i)
        elif(line.strip().startswith('*/')):
            popidx.append(i)
    popidx.sort(reverse=True)

    for i in popidx:
        lines.pop(i)
    
    return

# get main file lines
MAIN_PATH = os.path.join(CWD, LIBRARY, SUB_1, SUB_2, SUB_3, LIB_FLDR)
MAIN_LIST = os.listdir(MAIN_PATH)
MAIN_NAME = None
for filename in MAIN_LIST:
    if(filename[-len(END):]==END):
        MAIN_NAME = filename
        break
MAIN_FILE = open(os.path.join(MAIN_PATH, MAIN_NAME))
MAIN_LINES = MAIN_FILE.readlines()
MAIN_FILE.close()
remove_comments(MAIN_LINES)
MAIN_END = MAIN_LINES.pop(-1)

# append to main file lines all the cell lines
CELL_PATH = os.path.join(CWD, LIBRARY, SUB_1, SUB_2, SUB_3, CELL_FLDR)
CELL_LIST = os.listdir(CELL_PATH)
for cell in CELL_LIST:
    CELL_DIR = os.path.join(CELL_PATH, cell)
    CELL_DIR_LIST = os.listdir(CELL_DIR)
    CELL_NAMES = []
    for filename in CELL_DIR_LIST:
        if(filename[-len(END):]==END):
            CELL_NAMES.append(filename)
    for filename in CELL_NAMES:
        CELL_FILE = open(os.path.join(CELL_DIR, filename))
        CELL_LINES = CELL_FILE.readlines()
        CELL_FILE.close()
        remove_comments(CELL_LINES)
        MAIN_LINES += CELL_LINES

MAIN_LINES.append(MAIN_END)

out_file = open(OUT, mode='w')
for line in MAIN_LINES:
    out_file.write(line)

out_file.close()