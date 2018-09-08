fin = open("a.txt","r")
L = fin.read()
L = L.split("\n")
del L[len(L)-1]
newL = ""
for x in L:
	if x.isdigit():
		newL += ","
		newL += x
		#print x

#print L
print newL
# columnLength = 200
# fout = open("B_0.txt","w")
# idx = 0
# for x in L:
# 	#fout.write(x+"\n")
# 	if (idx+1)*columnLength == L.index(x):
# 		fout.close()
# 		idx = idx+1
# 		print idx, L.index(x)
# 		fout = open("B_"+str(idx)+".txt","w")
# 	else:
# 		fout.write(x+"\n")
# fout.close()
# fin.close()
	
