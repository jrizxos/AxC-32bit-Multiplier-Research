'''Generates the cpp code for /cppsim/mul32.cpp
    Creates a file "out.txt" in CWD that includes the sum code and the final placement of sums in outputs
    Also prints an addermap for /tcl_helper.py
'''

vhd_f = open('axc_wallace_32x32.vhd')
vhd_data = vhd_f.readlines()
vhd_f.close()

out_f = open('out.txt', 'w')

ADDER_MAP = [] # also make adder map for tcl helper

sum_count = 0
adder_count = 0
for line in vhd_data:
    if(line.startswith('--')):
        continue
    elif(line.startswith('prod')):
        l_lst = line.replace('  ',' ').split(' ')
        if('\'0\'' in l_lst[2]):
            continue
        else:
            c_line = line[:5] + ' |= ('
            if(l_lst[2].startswith('p')):
                idx = int(l_lst[0][l_lst[0].index('(')+1:l_lst[0].index(')')])
                num = int(l_lst[2][l_lst[2].index('(')+1:l_lst[2].index(')')])
                numA = int(num/32)
                numB = num%32
                shift = '' if(idx==0) else ' << '+str(idx)
                c_line += '(int)partials[' + str(numA) + '][' + str(numB) + '])' + shift + ';'
            else:
                idx = int(l_lst[0][l_lst[0].index('(')+1:l_lst[0].index(')')])
                if((idx)>30):
                        c_line += '(long)'
                if(l_lst[2].startswith('s')):
                    c_line += 'sums[' + l_lst[2].replace('\n','').replace(';','') + ']&1) << ' + str(idx) + ';'
                else:
                    c_line += 'sums[' + l_lst[2].replace('c','s').replace('\n','').replace(';','') + ']&2) << ' + str(idx-1) + ';'
            out_f.write(c_line+'\n')
    elif(line.startswith('fa')):
        l_lst = line.split(' ')
        ADDER_MAP.append(l_lst[0])
        l_map = l_lst[4].split(',')
        c_line = '    sums[' + l_map[3] + '] = ax_full_adder('

        a = l_map[0].replace('map(','')
        if(a.startswith('c')):
            a = a.replace('c','s')
            a = '(sums[' + a + ']&2)>>1'
        elif(a.startswith('s')):
            a = 'sums[' + a + ']&1'
        elif(a.startswith('p')):
            num = int(a[a.index('(')+1:a.index(')')])
            numA = int(num/32)
            numB = num%32
            a = 'partials[' + str(numA) + '][' + str(numB) + ']'

        b = l_map[1]
        if(b.startswith('c')):
            b = b.replace('c','s')
            b = '(sums[' + b + ']&2)>>1'
        elif(b.startswith('s')):
            b = 'sums[' + b + ']&1'
        elif(b.startswith('p')):
            num = int(b[b.index('(')+1:b.index(')')])
            numA = int(num/32)
            numB = num%32
            b = 'partials[' + str(numA) + '][' + str(numB) + ']'

        c = l_map[2]
        if(c.startswith('c')):
            c = c.replace('c','s')
            c = '(sums[' + c + ']&2)>>1'
        elif(c.startswith('s')):
            c = 'sums[' + c + ']&1'
        elif(c.startswith('p')):
            num = int(c[c.index('(')+1:c.index(')')])
            numA = int(num/32)
            numB = num%32
            c = 'partials[' + str(numA) + '][' + str(numB) + ']'

        c_line += a +', '+ b +', '+ c +', vars['+ str(sum_count) +']);'
        out_f.write(c_line+'\n')
        sum_count += 1
        adder_count += 1
    elif(line.startswith('ha')):
        l_lst = line.split(' ')
        l_map = l_lst[4].split(',')
        c_line = '    sums[' + l_map[2] + '] = half_adder('

        a = l_map[0].replace('map(','')
        if(a.startswith('c')):
            a = a.replace('c','s')
            a = '(sums[' + a + ']&2)>>1'
        elif(a.startswith('s')):
            a = 'sums[' + a + ']&1'
        elif(a.startswith('p')):
            num = int(a[a.index('(')+1:a.index(')')])
            numA = int(num/32)
            numB = num%32
            a = 'partials[' + str(numA) + '][' + str(numB) + ']'

        b = l_map[1]
        if(b.startswith('c')):
            b = b.replace('c','s')
            b = '(sums[' + b + ']&2)>>1'
        elif(b.startswith('s')):
            b = 'sums[' + b + ']&1'
        elif(b.startswith('p')):
            num = int(b[b.index('(')+1:b.index(')')])
            numA = int(num/32)
            numB = num%32
            b = 'partials[' + str(numA) + '][' + str(numB) + ']'
        
        c_line += a +', '+ b +');'
        out_f.write(c_line+'\n')
        adder_count += 1

print('ADDER_MAP =',ADDER_MAP)