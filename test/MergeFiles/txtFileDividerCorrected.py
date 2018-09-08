fin = open("D12.txt","r")
L = fin.read()
L = L.split()
columnLength = 195
fout = open("D12_0.txt","w")
idx = 0
for x in L:
	if (idx+1)*columnLength == (L.index(x)):
		fout.write(x+"\n")
		fout.close()
		idx = idx+1
		print idx, L.index(x)
		fout = open("D12_"+str(idx)+".txt","w")
	else:
		fout.write(x+"\n")
fout.close()
fin.close()
	
