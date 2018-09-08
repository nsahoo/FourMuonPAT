#Suleyman Durgut
#How to use: ls -lrth $file path$ > a.txt
#
import subprocess

fin = open("a.txt","r")
L = fin.read()
L = L.split("\n")
del L[len(L)-1]
#print L
for x in L:
		tmp = x.split("Merged")
		newname = tmp[0]+tmp[1]
		subprocess.call(["mv", x , newname])



