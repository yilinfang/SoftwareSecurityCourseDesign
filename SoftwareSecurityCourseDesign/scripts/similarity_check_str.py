import Levenshtein
import sys

str1 = sys.argv[1]
str2 = sys.argv[2]
out = sys.argv[3]

rate = Levenshtein.ratio(str1, str2)
with open(out, "w") as f:
    print(str(rate),file = out,flush = True)
    