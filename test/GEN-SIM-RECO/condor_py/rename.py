from subprocess import call

f1= open("b.txt", "r")
f2 = open("a.txt","r")
L1 = f1.read()
L1 = L1.split()
L2 = f2.read()
L2 = L2.split()
print L1
i=0
while i< len(L1):
	call("mv " + L1[i] + " " + L2[i], shell=True)
	i = i+1

f1.close()
f2.close()

# for x in L1:

# 	if abs(float(x[1])-9.46) < abs(float(x[0])-9.46):
# 		x[1],x[0] = x[0],x[1]
# 		x[14],x[13]=x[13],x[14]
# 		x[16],x[15]=x[15],x[16]
# 	for y in x:
# 		if x.index(y) != (len(x)-1):
# 			fout.write(y+" ")
# 		else:
# 			fout.write(y)
# 	fout.write("\n")

# fout.close()
# fin.close()
