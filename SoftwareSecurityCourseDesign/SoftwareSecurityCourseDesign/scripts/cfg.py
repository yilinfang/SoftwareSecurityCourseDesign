import re
import sys

def cfg(source_file, check_file):
    programe_s = ''
    programe_c = ''

    func_name_list1 = []
    func_name_list2 = []

    func_body_list1 = []
    func_body_list2 = []

    x = ['+', '-', '=', '/', '*', '%', '!', '>',
         '<', '&', '|', '^', '~', '(', '[', '{', '.']

    with open(source_file, 'r', encoding='UTF-8', errors='ignore') as f:
        for line_s in f:
            if line_s.find('#include') != -1 or line_s.find('using') != -1:
                continue
            elif line_s.find('#define') != -1 or line_s.find('#DEFINE') != -1:
                continue
            elif line_s.find('typedef') != -1:
                continue
            elif line_s == '\n':
                continue
            temp = reduce_line(line_s)
            find_func_name(temp, x, func_name_list1)
            programe_s += temp.replace('\t', '')
    programe_s = programe_s.replace('\n', '')
    programe_s = programe_s.replace(' ', '')
    find_func_relation(programe_s, func_name_list1, func_body_list1)
    res1 = get_func_table(func_name_list1, func_body_list1, programe_s)

    with open(check_file, 'r', encoding='UTF-8', errors='ignore') as f1:
        for line_c in f1:
            if line_c.find('#include') != -1 or line_c.find('using') != -1:
                continue
            elif line_c.find('#define') != -1 or line_c.find('#DEFINE') != -1:
                continue
            elif line_c.find('typedef') != -1:
                continue
            elif line_c == '\n':
                continue
            temp = reduce_line(line_c)
            find_func_name(temp, x, func_name_list2)
            programe_c += temp.replace('\t', '')
    programe_c = programe_c.replace('\n', '')
    programe_c = programe_c.replace(' ', '')
    find_func_relation(programe_c, func_name_list2, func_body_list2)
    res2 = get_func_table(func_name_list2, func_body_list2, programe_c)
    rate = comp_simi(res1, res2)
    if rate > 90.0:
        rate = str(rate)
        rate = rate + "     *"
        return rate
    rate = str(rate)
    f.close()
    f1.close()
    return rate


def reduce_line(line):
    # 利用正则表达式去掉双引号内容和注释
    line = re.sub('/\*(?<=/\*).+?(?=\*/)\*/', ' ', line, 0, 0)
    line = re.sub('//.*', ' ', line, 0, 0)
    return line


def find_func_name(line, x, list):
    if line.find('(') == -1:
        return
    tag = 0
    for i in line:
        if i == '(':
            pos1 = line.rfind(' ', 0, tag)
            pos2 = line.rfind('\t', 0, tag)
            pos3 = -1
            for op in x:
                temp = line.rfind(op, 0, tag)
                if temp > pos3:
                    pos3 = temp
            pos = pos1
            if pos2 > pos:
                pos = pos2
            if pos3 > pos:
                pos = pos3

            word = line[pos + 1:tag]
            word = word.replace(' ', '')
            flag = check_func_name(word)
            if flag == 1:
                if word not in list:
                    list.append(word)
        tag += 1
    tag += 1


def check_func_name(word):
    if word == '':
        return -1
    if word == 'if' or word == 'for' or word == 'while' or word == 'switch':
        return -1
    if re.search('[^a-zA-Z0-9_]', word) is None:
        return 1
    else:
        return -1


def find_func_relation(programe, func, body):
    end = len(programe)
    for name in func:
        start = 0
        while start <= end:
            pos = programe.find(name, start)
            if pos == -1:
                break

            start = pos + len(name)

            tag1 = programe.find(';', pos)
            tag2 = programe.find('{', pos)
            if tag1 < tag2 or tag2 == -1:
                continue
            flag = 0
            i = tag2
            while True:
                if programe[i] == '{':
                    flag += 1
                elif programe[i] == '}':
                    flag -= 1
                if programe[i] == '}' and flag == 0:
                    break
                i += 1
            tag3 = i
            body.append([name, tag2, tag3])
    temp = []
    for i in body:
        k = 0
        for j in body:
            if i[1] > j[1] and i[2] < j[2]:
                k = 1
                break
        if k == 0:
            temp.append(i)
    body.clear()
    for i in temp:
        k = 0
        for j in temp:
            if i[1] == j[1] and i[2] == j[2]:
                if len(i[0]) < len(j[0]):
                    k = 1
                    break
        if k == 0:
            body.append(i)


def get_func_table(func_name_list1, func_body_list1, programe):
    length = len(func_name_list1)
    table = [[0 for i in range(length)] for i in range(length)]
    for each_body in func_body_list1:
        word = each_body[0]
        start = each_body[1]
        end = each_body[2]
        pos1 = func_name_list1.index(word)
        for func in func_name_list1:
            if programe.find(func, start, end) != -1:
                pos2 = func_name_list1.index(func)
                table[pos1][pos2] = 1
    return table


def comp_simi(res1, res2):  # 使用空间向量的余弦定理来判定两个矩阵的相似度
    matrix1 = res1
    matrix2 = res2
    matrix1.sort()
    matrix2.sort()
    vector1 = []
    vector2 = []
    tem = 0
    tem2 = 0
    while tem < len(matrix1):
        tem2 = 0
        while tem2 < len(matrix1[tem]):
            vector1.append(matrix1[tem][tem2])
            tem2 = tem2 + 1
        tem = tem + 1
    tem = 0
    tem2 = 0
    while tem < len(matrix2):
        tem2 = 0
        while tem2 < len(matrix2[tem]):
            vector2.append(matrix2[tem][tem2])
            tem2 = tem2 + 1
        tem = tem + 1

    if len(vector2) < len(vector1):
        value = len(vector1) - len(vector2)
        for i in range(value):
            vector2.insert(0, 0)
    elif len(vector2) > len(vector1):
        value = len(vector2) - len(vector1)
        for i in range(value):
            vector1.insert(0, 0)
    result = euclidean(vector1, vector2)
    return result


def euclidean(p, q):
    # 如果两数据集数目不同，计算两者之间都对应有的数
    same = 0
    for i in p:
        if i in q:
            same += 1
    # 计算欧几里德距离,并将其标准化
    e = sum([(p[i] - q[i]) ** 2 for i in range(same)])
    return 1 / (1 + e ** .5)


filePath1 = sys.argv[1]
filePath2 = sys.argv[2]
filePath3 = sys.argv[3]

rate = cfg(filePath2, filePath1)

f3 = open(filePath3, "w")
f3.write("代码相似比例为:" + str(rate) + "\n")
print(rate)
f3.close()
