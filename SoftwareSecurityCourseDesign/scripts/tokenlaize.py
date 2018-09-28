import re
import sys

def Modifier(str):
    keywords = ["printf","int", "float", "char", "scanf", "memcpy", "strcmp", "strcat", "for", "while", "if", "else","main","return","long"]
    _str = RemoveComent(str)
    print(_str)
    _str = re.sub('".*"',"_STRING",_str)
    _str = re.sub("'.*'", "_CHAR", _str)
    for word in keywords:
        _str = re.sub(word,'_KEYWORD',_str)
    _str = re.sub("[a-z][0-9a-z\_]*", "_ID", _str)
    return _str

def RemoveComent(str):
    _str = re.sub('\/\*[\s\S]*\*\/|\/\/.*','',str)
    return _str

str1 = sys.argv[1]
str2 = sys.argv[2]

f1 = open(str1,"r")

str1 = f1.read()

f1.close()
str1 = Modifier(str1)
f2 = open(str2, "w")
f2.write(str1)
f2.close()

f3 = open(str2,"r")
_lines = f3.readlines()
lines = []
for line in _lines:
    data = line.strip()
    if(len(data)):
        lines.append(data)
print(lines)
f3.close()

        

