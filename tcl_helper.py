import os
import shutil
from subprocess import Popen

TOP_DIR = 'tcl_work_dir'
TEMP_DIR = 'temp'
SRC_DIR = 'vhdl'
OUT_DIR = 'tcl_out'
MAIN_SCR = 'main_high.tcl'
MAIN_RTL = 'axc_wallace.vhd'
CWD = os.getcwd()

# maps adder name with variable index
ADDER_MAP = ['fa10002', 'fa10003', 'fa10004', 'fa10005', 'fa10006', 'fa10007', 'fa10008', 'fa10009', 'fa10010', 'fa10011', 'fa10012', 'fa10013', 'fa10014', 'fa10015', 'fa10016', 'fa10017', 'fa10018', 'fa10019', 'fa10020', 'fa10021', 'fa10022', 'fa10023', 'fa10024', 'fa10025', 'fa10026', 'fa10027', 'fa10028', 'fa10029', 'fa10030', 'fa10031', 'fa10032', 'fa10033', 'fa10034', 'fa10035', 'fa10036', 'fa10037', 'fa10038', 'fa10039', 'fa10040', 'fa10041', 'fa10042', 'fa10043', 'fa10044', 'fa10045', 'fa10046', 'fa10047', 'fa10048', 'fa10049', 'fa10050', 'fa10051', 'fa10052', 'fa10053', 'fa10054', 'fa10055', 'fa10056', 'fa10057', 'fa10058', 'fa10059', 'fa10060', 'fa10105', 'fa10106', 'fa10107', 'fa10108', 'fa10109', 'fa10110', 'fa10111', 'fa10112', 'fa10113', 'fa10114', 'fa10115', 'fa10116', 'fa10117', 'fa10118', 'fa10119', 'fa10120', 'fa10121', 'fa10122', 'fa10123', 'fa10124', 'fa10125', 'fa10126', 'fa10127', 'fa10128', 'fa10129', 'fa10130', 'fa10131', 'fa10132', 'fa10133', 'fa10134', 'fa10135', 'fa10136', 'fa10137', 'fa10138', 'fa10139', 'fa10140', 'fa10141', 'fa10142', 'fa10143', 'fa10144', 'fa10145', 'fa10146', 'fa10147', 'fa10148', 'fa10149', 'fa10150', 'fa10151', 'fa10152', 'fa10153', 'fa10154', 'fa10155', 'fa10156', 'fa10157', 'fa10208', 'fa10209', 'fa10210', 'fa10211', 'fa10212', 'fa10213', 'fa10214', 'fa10215', 'fa10216', 'fa10217', 'fa10218', 'fa10219', 'fa10220', 'fa10221', 'fa10222', 'fa10223', 'fa10224', 'fa10225', 'fa10226', 'fa10227', 'fa10228', 'fa10229', 'fa10230', 'fa10231', 'fa10232', 'fa10233', 'fa10234', 'fa10235', 'fa10236', 'fa10237', 'fa10238', 'fa10239', 'fa10240', 'fa10241', 'fa10242', 'fa10243', 'fa10244', 'fa10245', 'fa10246', 'fa10247', 'fa10248', 'fa10249', 'fa10250', 'fa10251', 'fa10252', 'fa10253', 'fa10254', 'fa10311', 'fa10312', 'fa10313', 'fa10314', 'fa10315', 'fa10316', 'fa10317', 'fa10318', 'fa10319', 'fa10320', 'fa10321', 'fa10322', 'fa10323', 'fa10324', 'fa10325', 'fa10326', 'fa10327', 'fa10328', 'fa10329', 'fa10330', 'fa10331', 'fa10332', 'fa10333', 'fa10334', 'fa10335', 'fa10336', 'fa10337', 'fa10338', 'fa10339', 'fa10340', 'fa10341', 'fa10342', 'fa10343', 'fa10344', 'fa10345', 'fa10346', 'fa10347', 'fa10348', 'fa10349', 'fa10350', 'fa10351', 'fa10414', 'fa10415', 'fa10416', 'fa10417', 'fa10418', 'fa10419', 'fa10420', 'fa10421', 'fa10422', 'fa10423', 'fa10424', 'fa10425', 'fa10426', 'fa10427', 'fa10428', 'fa10429', 'fa10430', 'fa10431', 'fa10432', 'fa10433', 'fa10434', 'fa10435', 'fa10436', 'fa10437', 'fa10438', 'fa10439', 'fa10440', 'fa10441', 'fa10442', 'fa10443', 'fa10444', 'fa10445', 'fa10446', 'fa10447', 'fa10448', 'fa10517', 'fa10518', 'fa10519', 'fa10520', 'fa10521', 'fa10522', 'fa10523', 'fa10524', 'fa10525', 'fa10526', 'fa10527', 'fa10528', 'fa10529', 'fa10530', 'fa10531', 'fa10532', 'fa10533', 'fa10534', 'fa10535', 'fa10536', 'fa10537', 'fa10538', 'fa10539', 'fa10540', 'fa10541', 'fa10542', 'fa10543', 'fa10544', 'fa10545', 'fa10620', 'fa10621', 'fa10622', 'fa10623', 'fa10624', 'fa10625', 'fa10626', 'fa10627', 'fa10628', 'fa10629', 'fa10630', 'fa10631', 'fa10632', 'fa10633', 'fa10634', 'fa10635', 'fa10636', 'fa10637', 'fa10638', 'fa10639', 'fa10640', 'fa10641', 'fa10642', 'fa10723', 'fa10724', 'fa10725', 'fa10726', 'fa10727', 'fa10728', 'fa10729', 'fa10730', 'fa10731', 'fa10732', 'fa10733', 'fa10734', 'fa10735', 'fa10736', 'fa10737', 'fa10738', 'fa10739', 'fa10826', 'fa10827', 'fa10828', 'fa10829', 'fa10830', 'fa10831', 'fa10832', 'fa10833', 'fa10834', 'fa10835', 'fa10836', 'fa10929', 'fa10930', 'fa10931', 'fa10932', 'fa10933', 'fa20003', 'fa20004', 'fa20005', 'fa20006', 'fa20007', 'fa20008', 'fa20009', 'fa20010', 'fa20011', 'fa20012', 'fa20013', 'fa20014', 'fa20015', 'fa20016', 'fa20017', 'fa20018', 'fa20019', 'fa20020', 'fa20021', 'fa20022', 'fa20023', 'fa20024', 'fa20025', 'fa20026', 'fa20027', 'fa20028', 'fa20029', 'fa20030', 'fa20031', 'fa20032', 'fa20033', 'fa20034', 'fa20035', 'fa20036', 'fa20037', 'fa20038', 'fa20039', 'fa20040', 'fa20041', 'fa20042', 'fa20043', 'fa20044', 'fa20045', 'fa20046', 'fa20047', 'fa20048', 'fa20049', 'fa20050', 'fa20051', 'fa20052', 'fa20053', 'fa20054', 'fa20055', 'fa20056', 'fa20057', 'fa20058', 'fa20059', 'fa20061', 'fa20107', 'fa20109', 'fa20110', 'fa20111', 'fa20112', 'fa20113', 'fa20114', 'fa20115', 'fa20116', 'fa20117', 'fa20118', 'fa20119', 'fa20120', 'fa20121', 'fa20122', 'fa20123', 'fa20124', 'fa20125', 'fa20126', 'fa20127', 'fa20128', 'fa20129', 'fa20130', 'fa20131', 'fa20132', 'fa20133', 'fa20134', 'fa20135', 'fa20136', 'fa20137', 'fa20138', 'fa20139', 'fa20140', 'fa20141', 'fa20142', 'fa20143', 'fa20144', 'fa20145', 'fa20146', 'fa20147', 'fa20148', 'fa20149', 'fa20150', 'fa20151', 'fa20152', 'fa20153', 'fa20154', 'fa20155', 'fa20212', 'fa20213', 'fa20214', 'fa20215', 'fa20216', 'fa20217', 'fa20218', 'fa20219', 'fa20220', 'fa20221', 'fa20222', 'fa20223', 'fa20224', 'fa20225', 'fa20226', 'fa20227', 'fa20228', 'fa20229', 'fa20230', 'fa20231', 'fa20232', 'fa20233', 'fa20234', 'fa20235', 'fa20236', 'fa20237', 'fa20238', 'fa20239', 'fa20240', 'fa20241', 'fa20242', 'fa20243', 'fa20244', 'fa20245', 'fa20246', 'fa20247', 'fa20248', 'fa20249', 'fa20250', 'fa20252', 'fa20316', 'fa20318', 'fa20319', 'fa20320', 'fa20321', 'fa20322', 'fa20323', 'fa20324', 'fa20325', 'fa20326', 'fa20327', 'fa20328', 'fa20329', 'fa20330', 'fa20331', 'fa20332', 'fa20333', 'fa20334', 'fa20335', 'fa20336', 'fa20337', 'fa20338', 'fa20339', 'fa20340', 'fa20341', 'fa20342', 'fa20343', 'fa20344', 'fa20345', 'fa20346', 'fa20421', 'fa20422', 'fa20423', 'fa20424', 'fa20425', 'fa20426', 'fa20427', 'fa20428', 'fa20429', 'fa20430', 'fa20431', 'fa20432', 'fa20433', 'fa20434', 'fa20435', 'fa20436', 'fa20437', 'fa20438', 'fa20439', 'fa20440', 'fa20441', 'fa20443', 'fa20525', 'fa20527', 'fa20528', 'fa20529', 'fa20530', 'fa20531', 'fa20532', 'fa20533', 'fa20534', 'fa20535', 'fa20536', 'fa20537', 'fa20630', 'fa20631', 'fa20632', 'fa20634', 'fa30004', 'fa30006', 'fa30007', 'fa30008', 'fa30009', 'fa30010', 'fa30011', 'fa30012', 'fa30013', 'fa30014', 'fa30015', 'fa30016', 'fa30017', 'fa30018', 'fa30019', 'fa30020', 'fa30021', 'fa30022', 'fa30023', 'fa30024', 'fa30025', 'fa30026', 'fa30027', 'fa30028', 'fa30029', 'fa30030', 'fa30031', 'fa30032', 'fa30033', 'fa30034', 'fa30035', 'fa30036', 'fa30037', 'fa30038', 'fa30039', 'fa30040', 'fa30041', 'fa30042', 'fa30043', 'fa30044', 'fa30045', 'fa30046', 'fa30047', 'fa30048', 'fa30049', 'fa30050', 'fa30051', 'fa30052', 'fa30053', 'fa30054', 'fa30055', 'fa30056', 'fa30057', 'fa30058', 'fa30060', 'fa30110', 'fa30113', 'fa30114', 'fa30115', 'fa30116', 'fa30117', 'fa30118', 'fa30119', 'fa30120', 'fa30121', 'fa30122', 'fa30123', 'fa30124', 'fa30125', 'fa30126', 'fa30127', 'fa30128', 'fa30129', 'fa30130', 'fa30131', 'fa30132', 'fa30133', 'fa30134', 'fa30135', 'fa30136', 'fa30137', 'fa30138', 'fa30139', 'fa30140', 'fa30141', 'fa30142', 'fa30143', 'fa30144', 'fa30145', 'fa30146', 'fa30147', 'fa30148', 'fa30149', 'fa30150', 'fa30151', 'fa30153', 'fa30217', 'fa30219', 'fa30220', 'fa30221', 'fa30222', 'fa30223', 'fa30224', 'fa30225', 'fa30226', 'fa30227', 'fa30228', 'fa30229', 'fa30230', 'fa30231', 'fa30232', 'fa30233', 'fa30234', 'fa30235', 'fa30236', 'fa30237', 'fa30238', 'fa30239', 'fa30240', 'fa30241', 'fa30242', 'fa30243', 'fa30244', 'fa30246', 'fa30247', 'fa30324', 'fa30326', 'fa30327', 'fa30328', 'fa30329', 'fa30330', 'fa30331', 'fa30332', 'fa30333', 'fa30334', 'fa30335', 'fa30336', 'fa30337', 'fa30338', 'fa30340', 'fa30431', 'fa30433', 'fa40006', 'fa40008', 'fa40009', 'fa40010', 'fa40011', 'fa40012', 'fa40013', 'fa40014', 'fa40015', 'fa40016', 'fa40017', 'fa40018', 'fa40019', 'fa40020', 'fa40021', 'fa40022', 'fa40023', 'fa40024', 'fa40025', 'fa40026', 'fa40027', 'fa40028', 'fa40029', 'fa40030', 'fa40031', 'fa40032', 'fa40033', 'fa40034', 'fa40035', 'fa40036', 'fa40037', 'fa40038', 'fa40039', 'fa40040', 'fa40041', 'fa40042', 'fa40043', 'fa40044', 'fa40045', 'fa40046', 'fa40047', 'fa40048', 'fa40049', 'fa40050', 'fa40051', 'fa40052', 'fa40053', 'fa40054', 'fa40055', 'fa40056', 'fa40057', 'fa40058', 'fa40116', 'fa40118', 'fa40119', 'fa40120', 'fa40121', 'fa40122', 'fa40123', 'fa40124', 'fa40125', 'fa40126', 'fa40127', 'fa40128', 'fa40129', 'fa40130', 'fa40131', 'fa40132', 'fa40133', 'fa40134', 'fa40135', 'fa40136', 'fa40137', 'fa40138', 'fa40139', 'fa40140', 'fa40141', 'fa40142', 'fa40143', 'fa40144', 'fa40145', 'fa40146', 'fa40147', 'fa40148', 'fa40226', 'fa40228', 'fa40229', 'fa40230', 'fa40231', 'fa40232', 'fa40233', 'fa40234', 'fa40235', 'fa40236', 'fa40237', 'fa40238', 'fa50007', 'fa50009', 'fa50011', 'fa50012', 'fa50013', 'fa50014', 'fa50015', 'fa50016', 'fa50017', 'fa50018', 'fa50019', 'fa50020', 'fa50021', 'fa50022', 'fa50023', 'fa50024', 'fa50025', 'fa50026', 'fa50027', 'fa50028', 'fa50029', 'fa50030', 'fa50031', 'fa50032', 'fa50033', 'fa50034', 'fa50035', 'fa50036', 'fa50037', 'fa50038', 'fa50039', 'fa50040', 'fa50041', 'fa50042', 'fa50043', 'fa50044', 'fa50045', 'fa50046', 'fa50047', 'fa50048', 'fa50049', 'fa50050', 'fa50051', 'fa50052', 'fa50053', 'fa50054', 'fa50056', 'fa50059', 'fa50123', 'fa50125', 'fa50127', 'fa50129', 'fa50130', 'fa50131', 'fa50132', 'fa50133', 'fa50134', 'fa50135', 'fa50136', 'fa50137', 'fa50138', 'fa50139', 'fa50140', 'fa50141', 'fa60010', 'fa60013', 'fa60015', 'fa60017', 'fa60019', 'fa60020', 'fa60021', 'fa60022', 'fa60023', 'fa60024', 'fa60025', 'fa60026', 'fa60027', 'fa60028', 'fa60029', 'fa60030', 'fa60031', 'fa60032', 'fa60033', 'fa60034', 'fa60035', 'fa60036', 'fa60037', 'fa60038', 'fa60039', 'fa60040', 'fa60041', 'fa60042', 'fa60043', 'fa60044', 'fa60045', 'fa60046', 'fa60047', 'fa60048', 'fa60049', 'fa60050', 'fa60051', 'fa60055', 'fa60057', 'fa60060', 'fa70014', 'fa70016', 'fa70018', 'fa70022', 'fa70024', 'fa70026', 'fa70027', 'fa70028', 'fa70029', 'fa70030', 'fa70031', 'fa70032', 'fa70033', 'fa70034', 'fa70035', 'fa70036', 'fa70037', 'fa70038', 'fa70039', 'fa70040', 'fa70041', 'fa70042', 'fa70043', 'fa70044', 'fa70049', 'fa70052', 'fa70058', 'fa70061', 'fa80017', 'fa80019', 'fa80023', 'fa80025', 'fa80028', 'fa80032', 'fa80033', 'fa80034', 'fa80039', 'fa80042', 'fa80045', 'fa80050', 'fa80053', 'fa80062']

VAR_D = ['full_adder',              # domain of each variable
         'full_adder_i',
         'full_adder_ii',
         'full_adder_iii']                            \
      + ['full_adder_'+str(i) for i in range(1,9)]    \
      + ['full_adder_'+str(i) for i in range(10,18)]  \
      + ['full_adder_'+str(i) for i in range(19,28)]

def create_files(name):
    """Creates files for Genus sythesis.
    Edits the main TCL script for import directories and output directories

        Args:
            name (str): the name of the individual, which is going to be simulated and syhtesized 

        Returns:
            new_dir (str): path to the temporary directory created
    """
    if(not os.path.exists(os.path.join(TOP_DIR, TEMP_DIR))):
            os.mkdir(os.path.join(TOP_DIR, TEMP_DIR))

    # copy files
    new_dir = os.path.join(TOP_DIR, TEMP_DIR, name)     # temporary dir path
    if os.path.exists(new_dir):                         # if it exists erase
        shutil.rmtree(new_dir)
    os.mkdir(new_dir)                                   # create temporary dir
    get_dir = os.path.join(CWD, TOP_DIR, SRC_DIR)       # get vhdl files from here
    src_dir = os.path.join(CWD, new_dir, SRC_DIR)       # put vhdl files here
    shutil.copytree(get_dir, src_dir)                   # copy files
    get_dir = os.path.join(CWD, TOP_DIR, MAIN_SCR)      # get tcl script from here
    put_dir = os.path.join(CWD, new_dir)                # put tcl script from here
    shutil.copy(get_dir, put_dir)                       # copy files

    # edit main tcl script
    scr_dir = os.path.join(put_dir, MAIN_SCR)           
    with open(scr_dir, 'r') as file:
        data = file.readlines()
        file.close()
    lib_dir = os.path.join(CWD, TOP_DIR) 
    out_dir = os.path.join(CWD, TOP_DIR, OUT_DIR) 
    for i,line in enumerate(data):
        if(line.startswith('set_db init_lib_search_path')):
            data[i] = 'set_db init_lib_search_path {' + lib_dir + '}  -quiet\n'
            continue
        elif(line.startswith('set_db init_hdl_search_path')):
            data[i] = 'set_db init_hdl_search_path {' + src_dir + '}  -quiet\n'
            continue
        elif(line.startswith('report_timing')):
            data[i] = 'report_timing > ' + out_dir + '/' + name + '_time.rpt\n'
            continue
        elif(line.startswith('report_power')):
            data[i] = 'report_power > ' + out_dir + '/' + name + '_power.rpt\n'
            continue
        elif(line.startswith('report_area')):
            data[i] = 'report_area > ' + out_dir + '/' + name + '_area.rpt\n'
            continue

    with open(scr_dir, 'w') as file:
        file.writelines( data )
        file.close()

    return new_dir

def build_rtl(name, vars):
    """Builds the RTL description of the multiplier based on the vars passed as argument.

        Args:
            name (str): the name of the temporaty directory that contains the rtl files
            vars (list): specific adders to put at each location in the design

        Returns:
            None
    """
    # edit rtl file
    rtl_dir = os.path.join(CWD, TOP_DIR, TEMP_DIR, name, SRC_DIR, MAIN_RTL)
    with open(rtl_dir, 'r') as file:
        data = file.readlines()
        file.close()
    for i,line in enumerate(data):
        try:
            j = ADDER_MAP.index(line[0:len(ADDER_MAP[0])])
        except:
            continue
        ports = line.index(' port')
        colon = line.index(' : ')
        data[i] = line[0:colon+3] + str(vars[j]) + line[ports:]
    with open(rtl_dir, 'w') as file:
        file.writelines( data )
        file.close()
    return

def run_tcl(name, out):
    """Runs the TCL script in the temporaty directory given as argument.

        Args:
            name (str): the name of the temporaty directory that contains the scipt
            out (bool): whether to print on stdout/stderr or not

        Returns:
            p (Popen): process created
    """
    command = 'genus -f '+MAIN_SCR+' -batch'
    if(not out):
        command += ' > /dev/null 2>&1'
    work_dir = os.path.join(CWD, TOP_DIR, TEMP_DIR, name)
    p = Popen(command, cwd = work_dir, shell=True)
    return p

def get_scores(name):
    """Reads Genus report values for an individual with given name from the tcl_out directory.

        Args:
            name (str): the name of the individual

        Returns:
            time (int): clock slack in picoseconds
            area (float): area in micrometers^2
            power (float): power consumption in milliwatts
    """

    area = -1
    time = -1
    power = -1

    # read area report
    area_dir = os.path.join(CWD, TOP_DIR, OUT_DIR, name + '_area.rpt')
    if os.path.exists(area_dir):
        with open(area_dir, 'r') as file:
            data = file.readlines()
            file.close()
        for i,line in enumerate(data):
            if(line.startswith('main')):
                line_lst = line.split(' ')[::-1]
                for item in line_lst:
                    try:
                        temp_flt = float(item)
                        area = temp_flt
                        break
                    except:
                        continue
                break
    if(area == -1):
        raise Exception('TCL_HELPER Error! Failed to read area from: ' + area_dir)
    
    # read time report
    time_dir = os.path.join(CWD, TOP_DIR, OUT_DIR, name + '_time.rpt')
    if os.path.exists(time_dir):
        with open(time_dir, 'r') as file:
            data = file.readlines()
            file.close()
        time = []
        for i,line in enumerate(data):
            if(line.startswith('Path 1:')):
                a = line.index('(')+1
                b = line.index(' ps)')
                time = int(line[a:b])
    if(time == -1):
        raise Exception('TCL_HELPER Error! Failed to read time from: ' + time_dir)

    # read power report
    power_dir = os.path.join(CWD, TOP_DIR, OUT_DIR, name + '_power.rpt')
    if os.path.exists(power_dir):
        with open(power_dir, 'r') as file:
            data = file.readlines()
            file.close()
        for i,line in enumerate(data):
            if(line.startswith('    Subtotal')):
                line_lst = line.split(' ')[::-1]
                for item in line_lst:
                    try:
                        temp_flt = float(item)
                        power = temp_flt
                        break
                    except:
                        continue
                break
    if(power == -1):
        raise Exception('TCL_HELPER Error! Failed to read power from: ' + power_dir)

    return area, -time, power*1000

############################################## TEST ###############################################

if __name__ == '__main__':
    import random
    random.seed(43)
    name = 'test_1'
    l = [random.randrange(len(VAR_D)) for i in range(918)]
    print(name,': Creating files...')
    create_files(name)
    build_rtl(name, [VAR_D[i] for i in l]) 
    p = run_tcl(name, True)
    p.communicate()
    
    score = get_scores(name)
    print(name,':',score)

    print(name,': Done')