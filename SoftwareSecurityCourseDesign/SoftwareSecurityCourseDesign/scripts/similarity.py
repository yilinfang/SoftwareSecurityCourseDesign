import sys

def check_line(line, res):
    i = 0
    for word in res:
        flag = line.find(word[0])
        if flag == -1:
            i = i + 1
            continue
        res[i][1] = res[i][1] + 1
        i = i + 1


def sim(source_file, check_file):
    res1 = [['int', 0],
            ['long', 0],
            ['short', 0],
            ['float', 0],
            ['double', 0],
            ['char', 0],
            ['unsigned', 0],
            ['signed', 0],
            ['const', 0],
            ['void', 0],
            ['volatile', 0],
            ['enum', 0],
            ['struct', 0],
            ['union', 0],
            ['if', 0],
            ['else', 0],
            ['goto', 0],
            ['switch', 0],
            ['case', 0],
            ['do', 0],
            ['while', 0],
            ['for', 0],
            ['continue', 0],
            ['break', 0],
            ['return', 0],
            ['default', 0],
            ['auto', 0],
            ['register', 0],
            ['extern', 0],
            ['static', 0],
            ['sizeof', 0],
            ['printf', 0],
            ['scanf', 0],
            ['fopen', 0],
            ['fclose', 0]]
    with open(source_file, 'r', encoding='UTF-8', errors='ignore') as f:
        for line_s in f:
            check_line(line_s, res1)
    res1[0][1] = res1[0][1] - res1[31][1]

    res2 = [['int', 0],
            ['long', 0],
            ['short', 0],
            ['float', 0],
            ['double', 0],
            ['char', 0],
            ['unsigned', 0],
            ['signed', 0],
            ['const', 0],
            ['void', 0],
            ['volatile', 0],
            ['enum', 0],
            ['struct', 0],
            ['union', 0],
            ['if', 0],
            ['else', 0],
            ['goto', 0],
            ['switch', 0],
            ['case', 0],
            ['do', 0],
            ['while', 0],
            ['for', 0],
            ['continue', 0],
            ['break', 0],
            ['return', 0],
            ['default', 0],
            ['auto', 0],
            ['register', 0],
            ['extern', 0],
            ['static', 0],
            ['sizeof', 0],
            ['printf', 0],
            ['scanf', 0],
            ['fopen', 0],
            ['fclose', 0]]

    with open(check_file, 'r', encoding='UTF-8', errors='ignore') as f1:
        for line_c in f1:
            check_line(line_c, res2)
    res2[0][1] = res2[0][1] - res2[31][1]

    rate = calculate_homology(res1, res2)
    if rate > 90.0:
        rate = str(rate)
        rate = rate
        return rate
    rate = str(rate)
    f.close()
    f1.close()
    return rate


def calculate_homology(res1, res2):
    i = 0
    j = 0
    for temp in res1:
        if res1[i][1] == res2[i][1]:
            j = j + 1
            i = i + 1
            continue
        i = i + 1
    result = (j / i) * 100
    return result

filePath1 = sys.argv[1]
filePath2 = sys.argv[2]
filePath3 = sys.argv[3]

rate = sim(filePath2, filePath1)

f3 = open(filePath3, "w")
f3.write("代码相似比例为:" + str(rate) + "\n")
print(rate)
f3.close()