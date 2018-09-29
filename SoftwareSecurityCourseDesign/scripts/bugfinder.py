import regex as re
import sys


def NumberOverflow(filename, collector):
    fin = open(filename, mode='r', encoding='UTF-8')
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
            print(leftVar)
            print(rightVar)
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
    fin = open(filename, mode='r', encoding='UTF-8')
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
    print(unsignedNum)
    leftInt = re.findall(r'(?<=int\s)[a-zA-Z0-9_]+(?=,)', txt)
    midInt = re.findall(r'(?<=int.*,)[a-zA-Z0-9_]+?(?=,)', txt)
    rightInt = re.findall(r'(?<=int.*,)[a-zA-Z0-9_]+(?=;)', txt)
    sigInt = re.findall(
        r'(?<=int\s)[a-zA-Z0-9_]+(?=;)*', txt)
    intNum = list(set(leftInt+midInt+rightInt+sigInt))
    print(intNum)
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
                print(lineNumber, "行有＝号warning")
                print("左侧unsigned", leftVar[0], "右侧signed", rightVar[0])
            if((rightVar[0] in unsignedNum) and (leftVar[0] in intNum)):
                print(lineNumber, "行有＝号warning")
                print("左侧signed", leftVar[0], "右侧unsigned", rightVar[0])
        if('>' in line):
            leftVar = re.findall(
                r'[a-zA-Z0-9_]+(?=\s\>?)*', line)
            rightVar = re.findall(
                r'(?<=\>\s)[a-zA-Z0-9_]+(?=\))*', line)
            if(not leftVar or not rightVar):
                continue
            if((leftVar[0] in unsignedNum) and (rightVar[0] in intNum)):
                print(lineNumber, "行有>号warning")
                print("左侧unsigned", leftVar[0], "右侧signed", rightVar[0])
            if((rightVar[0] in unsignedNum) and (leftVar[0] in intNum)):
                print(lineNumber, "行有>号warning")
                print("左侧signed", leftVar[0], "右侧unsigned", rightVar[0])
        if('<' in line):
            leftVar = re.findall(
                r'[a-zA-Z0-9_]+(?=\s\<)*', line)
            rightVar = re.findall(
                r'(?<=\<\s)[a-zA-Z0-9_]+(?=\))*', line)
            if(not leftVar or not rightVar):
                continue
            if((leftVar[0] in unsignedNum) and (rightVar[0] in intNum)):
                print(lineNumber, "行有<号warning")
                print("左侧unsigned", leftVar[0], "右侧signed", rightVar[0])
            if((rightVar[0] in unsignedNum) and (leftVar[0] in intNum)):
                print(lineNumber, "行有<号warning")
                print("左侧signed", leftVar[0], "右侧unsigned", rightVar[0])
    fin.close()


def StackAndHeapOverflow(filename, collector):
    fin = open(filename, mode='r', encoding='UTF-8')
    txt = fin.read()
    var = re.findall(r'(?<=char\s)[a-zA-Z0-9_]+(?=\[[0-9]+\])', txt)
    numchar = re.findall(r'(?<=char.*\[)[0-9]+(?=\])', txt)
    var2 = re.findall(r'(?<=char\s)[a-zA-Z0-9_]+(?=\[\])', txt)
    numchar2 = re.findall(r'(?<=char.*\").*(?=\")', txt)
    chars = re.findall(
        r'(?<=char\*\s)[a-zA-Z0-9_]+(?=\s\=\s\()', txt)
    numchar3 = re.findall(r'(?<=malloc\()[a-zA-Z0-9_]+(?=\*)', txt)
    print(numchar3)
    linenumber = 0
    dict = {1: 'strcpy', 2: 'strncpy', 3: 'memcpy', 4: 'strcat', 5: 'strcat', 6: 'sprintf', 7: 'vsprintf', 8: 'gets',
            9: 'getchar', 10: 'fgetc', 11: 'getc', 12: 'read', 13: 'scanf', 14: 'fscanf', 15: 'vfscanf', 16: 'vsscanf'}
    fin.seek(0)
    for line in fin:
        linenumber += 1
        # print(line)
        for i in range(1, 16):
            if((dict[i]) in line):
                for j in range(0, len(var)):
                    if((var[j] in line) == True):
                        print(linenumber)
                        print(var[j], numchar[j])
                for q in range(0, len(var2)):
                    if((var2[q] in line) == True):
                        print(linenumber)
                        print(var2[q], numchar2[q])
                for t in range(0, len(chars)):
                    if((chars[t] in line) == True):
                        print(linenumber)
                        print(chars[t], numchar3[t])
    fin.close()


arg1 = sys.argv[1]
arg2 = sys.argv[2]
arg3 = sys.argv[3]
f2 = open(arg2, "w")
if(arg3 == "1"):
    NumberOverflow(arg1, f2.write)
if(arg3 == "2"):
    SignOverflow(arg1, f2.write)
if(arg3 == "3"):
    StackAndHeapOverflow(arg1, f2.write)
f2.close()
