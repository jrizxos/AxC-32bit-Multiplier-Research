''' Finds a path/paths of AFAs and HA from the output up to the partial products
    from "axc_wallace_32x32.vhd".
'''

vhd_f = open('axc_wallace_32x32.vhd')
vhd_data = vhd_f.readlines()
vhd_f.close()

# consult "axc_wallace_32x32.vhd" to find the output AFA ids that you want
# for example the 35th bit of prodA is "prodA(34) <= s80034;" (line 143)
# so you need the id "80034"
list_id = ['50056', '50059', '60057', '80051', '80053', '80054', '70052', '60055', '70058']
p = ['fa','ha']     # possible prefixes

items = set()       # this set will contain AFAs included the paths

def strip_named(named):
    if(named[0]=='p'):
        return None
    return named[1:]

def clear_list(lst):
    lst2 = []
    for i in lst:
        if(i!=None):
            lst2.append(i)
    return lst2

def find_item(item):
    for line in vhd_data:
        if line.startswith(p[0]+item):
            item = p[0]+item
            items.add(item)
            l_lst = line.split(' ')
            l_map = l_lst[4].split(',')
            a = strip_named(l_map[0].replace('map(',''))
            b = strip_named(l_map[1])
            c = strip_named(l_map[2])
            return clear_list((a,b,c))
        if line.startswith(p[1]+item):
            item = p[1]+item
            items.add(item)
            l_lst = line.split(' ')
            l_map = l_lst[4].split(',')
            a = l_map[0].replace('map(','')
            b = l_map[1]
            return clear_list((a,b))
    return ()

for item in list_id:            # recursively finds the path of the item, also finds what prefix the items in the path have
    found = find_item(item)
    while(len(found)>0):
        new_item = found.pop()
        new_found = find_item(new_item)
        for i in new_found:
            found.append(i)

print(items)
print(len(items))