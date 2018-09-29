import sys
import re

def RemoveComent(str1):
    _str = re.sub('\/\*[\s\S]*\*\/|\/\/.*','',str1)
    return _str

arg1 = sys.argv[1]
arg2 = sys.argv[2]

f1 = open(arg1, "r")
str1 = f1.read()
backup = f1.read()
f1.close()
f1 = open(arg1, "w")
str1 = RemoveComent(str1)
f1.write(str1)
f1.close()
f1 = open(arg1, "r")
f2 = open(arg2, "w")
_lines = f1.readlines()
for line in _lines:
    data = line.strip()
    if(len(data)):
        f2.write(data + "\n")
f1.close()
f2.close()
f1 = open(arg1, "w")
f1.write(backup)
f1.close()