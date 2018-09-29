import Levenshtein
import sys

filePath1 = sys.argv[1]
filePath2 = sys.argv[2]
filePath3 = sys.argv[3]

f1 = open(filePath1,"r")
f2 = open(filePath2, "r")
f3 = open(filePath3, "w")
hit = 0
lines1 = f1.readlines()
lines2 = f2.readlines()
for line1 in lines1:
    for line2 in lines2:
        if(Levenshtein.ratio(line1,line2) > 0.95):
            hit = hit + 1
            break
rate = hit / len(lines1)
print(rate)
f3.write("代码抄袭比例为:" + str(rate))
f1.close()
f2.close()
f3.close()
    