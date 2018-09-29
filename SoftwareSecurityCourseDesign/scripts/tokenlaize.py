import regex as re
import sys

def Modifier(str1):
    keywords = ["printf","int", "float", "char", "scanf", "memcpy", "strcmp", "strcat", "for", "while", "if", "else","main","return","long"]
    str2 = str1
    str2 = re.sub('".*"',"_STRING",str2)
    str2 = re.sub("'.*'", "_CHAR", str2)
    for word in keywords:
        str2 = re.sub(word,'_KEYWORD',str2)
    str2 = re.sub("[a-z][0-9a-z\_]*", "_ID", str2)
    return str2

arg1 = sys.argv[1]
arg2 = sys.argv[2]
f1 = open(arg1,"r")
str1 = f1.read()
f1.close()
str1 = Modifier(str1)
f2 = open(arg2, "w")
f2.write(str1)
f2.close()