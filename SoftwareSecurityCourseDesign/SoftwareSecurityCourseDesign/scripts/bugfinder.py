import regex as re
import sys
import os

def NumberOverflow(filename, collector):
    fin = open(filename, mode='r')
    txt = fin.read()
    leftShort = re.findall(
        r'(?<=short\s)[a-zA-Z0-9_]+(?=,)', txt)
    midShort = re.findall(
        r'(?<=short\s.*,)[a-zA-Z0-9_]+?(?=,)', txt)
    rightShort = re.findall(
        r'(?<=short\s.*,)[a-zA-Z0-9_]+(?=;)', txt)
    sigShort = re.findall(
        r'(?<=short\s)[a-zA-Z0-9_]*', txt)
    shortNum = list(set(leftShort+midShort+rightShort+sigShort))
    leftLong = re.findall(r'(?<=long\s)[a-zA-Z0-9_]+(?=,)', txt)
    midLong = re.findall(r'(?<=long\s.*,)[a-zA-Z0-9_]+?(?=,)', txt)
    rightLong = re.findall(r'(?<=long\s.*,)[a-zA-Z0-9_]+(?=;)', txt)
    sigLong = re.findall(
        r'(?<=long\s)[a-zA-Z0-9_]*', txt)
    longNum = list(set(leftLong+midLong+rightLong+sigLong))
    leftInt = re.findall(r'(?<=int\s)[a-zA-Z0-9_]+(?=,)', txt)
    midInt = re.findall(r'(?<=int.*,)[a-zA-Z0-9_]+?(?=,)', txt)
    rightInt = re.findall(r'(?<=int.*,)[a-zA-Z0-9_]+(?=;)', txt)
    sigInt = re.findall(
        r'(?<=int\s)[a-zA-Z0-9_]*', txt)
    intNum = list(set(leftInt+midInt+rightInt+sigInt))
    lineNumber = 0
    fin.seek(0)
    for line in fin:
        lineNumber += 1
        if('=' in line):
            leftVar = re.findall(r'[a-zA-Z0-9_]+(?=\s\=)', line)
            rightVar = re.findall(
                r'(?<=\=\s)[a-zA-Z0-9_]*', line)
            if(not leftVar or not rightVar):
                continue
            if((leftVar[0] in shortNum) and ((rightVar[0] in intNum) or (rightVar[0] in longNum))):
                # print("坐标",linenumber)
                collector("第" + str(lineNumber) +
                          "行(整数宽度溢出):左边为short,右边为int或long.\n")
            if((leftVar[0] in intNum) and (rightVar[0] in longNum)):
                # print("坐标",linenumber)
                collector("第" + str(lineNumber) +
                          "行(整数宽度溢出):左边为int,右边为long.\n")
    fin.close()


def SignOverflow(filename, collector):
    fin = open(filename, mode='r')
    txt = fin.read()
    leftUnsigned = re.findall(
        r'(?<=unsigned\s)[a-zA-Z0-9_]+(?=,)', txt)
    midUnsigned = re.findall(
        r'(?<=unsigned.*,)[a-zA-Z0-9_]+?(?=,)', txt)
    rightUnsigned = re.findall(
        r'(?<=unsigned.*,)[a-zA-Z0-9_]+(?=;)', txt)
    sigUnsigned = re.findall(
        r'(?<=unsigned\s)[a-zA-Z0-9_]*', txt)
    unsignedNum = list(set(leftUnsigned+midUnsigned+rightUnsigned+sigUnsigned))
    leftInt = re.findall(r'(?<=int\s)[a-zA-Z0-9_]+(?=,)', txt)
    midInt = re.findall(r'(?<=int.*,)[a-zA-Z0-9_]+?(?=,)', txt)
    rightInt = re.findall(r'(?<=int.*,)[a-zA-Z0-9_]+(?=;)', txt)
    sigInt = re.findall(
        r'(?<=int\s)[a-zA-Z0-9_]*', txt)
    intNum = list(set(leftInt+midInt+rightInt+sigInt))
    lineNumber = 0
    fin.seek(0)
    for line in fin:
        lineNumber += 1
        if('=' in line):
            leftVar = re.findall(r'[a-zA-Z0-9_]+(?=\s\=)', line)
            rightVar = re.findall(
                r'(?<=\=\s)[a-zA-Z0-9_]+(?=;)*', line)
            if(not leftVar or not rightVar):
                continue
            if((leftVar[0] in unsignedNum) and (rightVar[0] in intNum)):
                collector(str(lineNumber) + "行＝号(整数符号溢出)\n")
                collector("左侧unsigned:" + leftVar[0] + "右侧signed:" + rightVar[0] + "\n")
            if((rightVar[0] in unsignedNum) and (leftVar[0] in intNum)):
                collector(str(lineNumber) + "行＝号(整数符号溢出)\n")
                collector("左侧signed:" + leftVar[0] + "右侧unsigned:" + rightVar[0] + "\n")
        if('>' in line):
            leftVar = re.findall(
                r'[a-zA-Z0-9_]+(?=\s\>?)*', line)
            rightVar = re.findall(
                r'(?<=\>\s)[a-zA-Z0-9_]+(?=\))*', line)
            if(not leftVar or not rightVar):
                continue
            if((leftVar[0] in unsignedNum) and (rightVar[0] in intNum)):
                collector(str(lineNumber) + "行>号(整数符号溢出)\n")
                collector("左侧unsigned:" + leftVar[0] + "右侧signed:" + rightVar[0] + "\n")
            if((rightVar[0] in unsignedNum) and (leftVar[0] in intNum)):
                collector(str(lineNumber) + "行>号(整数符号溢出)\n")
                collector("左侧signed:" + leftVar[0] + "右侧unsigned:" + rightVar[0] + "\n")
        if('<' in line):
            leftVar = re.findall(
                r'[a-zA-Z0-9_]+(?=\s\<)*', line)
            rightVar = re.findall(
                r'(?<=\<\s)[a-zA-Z0-9_]+(?=\))*', line)
            if(not leftVar or not rightVar):
                continue
            if((leftVar[0] in unsignedNum) and (rightVar[0] in intNum)):
                collector(str(lineNumber) + "行<号(整数符号溢出)" + "\n")
                collector("左侧unsigned:" + leftVar[0] + "右侧signed:" + rightVar[0] + "\n")
            if((rightVar[0] in unsignedNum) and (leftVar[0] in intNum)):
                collector(str(lineNumber) + "行<号(整数符号溢出)" + "\n")
                collector("左侧signed:" + leftVar[0] + "右侧unsigned:" + rightVar[0] + "\n")
    fin.close()


def StackAndHeapOverflow(filename, collector):
    fin = open(filename, mode='r')
    txt = fin.read()
    var = re.findall(r'(?<=char\s)[a-zA-Z0-9_]+(?=\[[0-9]+\])', txt)
    numchar = re.findall(r'(?<=char.*\[)[0-9]+(?=\])', txt)
    var2 = re.findall(r'(?<=char\s)[a-zA-Z0-9_]+(?=\[\])', txt)
    numchar2 = re.findall(r'(?<=char.*\").*(?=\")', txt)
    chars = re.findall(
        r'(?<=char\*\s)[a-zA-Z0-9_]+(?=\s\=\s\()', txt)
    numchar3 = re.findall(r'(?<=malloc\()[a-zA-Z0-9_]+(?=\*)', txt)
    linenumber = 0
    dict = {1: 'strcpy', 2: 'strncpy', 3: 'memcpy', 4: 'strcat', 5: 'strcat', 6: 'sprintf', 7: 'vsprintf', 8: 'gets',
            9: 'getchar', 10: 'fgetc', 11: 'getc', 12: 'read', 13: 'scanf', 14: 'fscanf', 15: 'vfscanf', 16: 'vsscanf'}
    fin.seek(0)
    for line in fin:
        linenumber += 1
        for i in range(1, 16):
            if((dict[i]) in line):
                for j in range(0, len(var)):
                    if((var[j] in line) == True):
                        collector(str(linenumber) + "行可能存在缓冲区溢出错误")
                        collector(var[j] + "," + numchar[j] + "\n")
                for q in range(0, len(var2)):
                    if((var2[q] in line) == True):
                        collector(str(linenumber) + "行可能存在缓冲区溢出错误\n")
                        collector(var2[q] + "," + numchar2[q] + "\n")
                for t in range(0, len(chars)):
                    if((chars[t] in line) == True):
                        collector(str(linenumber) + "行可能存在缓冲区溢出错误\n")
                        collector(chars[t] + "," + numchar3[t] + "\n")
    fin.close()


arg1 = sys.argv[1]
arg2 = sys.argv[2]
arg3 = sys.argv[3]
f2 = open(arg2, "a")
if(arg3 == "1"):
    f2.write(arg1 + "\n")
    NumberOverflow(arg1, f2.write)
if(arg3 == "2"):
    f2.write(arg1 + "\n")
    SignOverflow(arg1, f2.write)
if(arg3 == "3"):
    f2.write(arg1 + "\n")
    StackAndHeapOverflow(arg1, f2.write)
f2.close()
