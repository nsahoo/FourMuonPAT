file_Default = open("FourMuonFinalList.txt","r")
file_Muonia = open("2012MuoniaClean.txt","r")
file_DoubleMu = open("2012DoubleMuonClean.txt","r")

file_out_Muonia = open("2012MuoniaCleanFinal.txt","w")
file_out_DoubleMu = open("2012DoubleMuonCleanFinal.txt","w")



L_default = file_Default.read()
L_default = L_default.split("\n")
del L_default[len(L_default)-1]
# remove the \r character from the lines
i = 0
while i<len(L_default):
	L_default[i] = L_default[i].strip("\r")
	i+=1
#print L_default



L_Muonia = file_Muonia.read()
L_Muonia = L_Muonia.split("\n")
del L_Muonia[len(L_Muonia)-1]
# remove the \r character from the lines
i = 0
while i<len(L_Muonia):
	L_Muonia[i] = L_Muonia[i].strip("\r")
	i+=1
#print L_Muonia


L_DoubleMu = file_DoubleMu.read()
L_DoubleMu = L_DoubleMu.split("\n")
del L_DoubleMu[len(L_DoubleMu)-1]
# remove the \r character from the lines
i = 0
while i<len(L_DoubleMu):
	L_DoubleMu[i] = L_DoubleMu[i].strip("\r")
	i+=1


print len(L_default),len(L_Muonia),len(L_DoubleMu)

#print L_default


L_MuoniaFinalList = []

for x in L_Muonia:
	if x in L_default and int(x.split()[1])>185000:
		file_out_Muonia.write(x+"\n")
		L_MuoniaFinalList.append(x)


for x in L_DoubleMu:
	if x in L_default and int(x.split()[1])>185000 and x not in L_MuoniaFinalList:
		file_out_DoubleMu.write(x+"\n")

file_out_DoubleMu.close()
file_out_Muonia.close()
