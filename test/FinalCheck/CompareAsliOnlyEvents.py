file_Muonia = open("Muonia2012NoTightMuonClean.txt","r")
file_DoubleMu = open("DoubleMu2012NoTightMuonClean.txt","r")
file_MuoniaAsliOnly = open("EventsThatAre_OnlyASLI_MuOnia.txt","r")
file_DoubleMuAsliOnly = open("EventsThatAre_OnlyASLI_DoubleMu.txt","r")

file_out_Muonia = open("sharedMuonia.txt","w")
file_out_DoubleMu = open("shareddoublemu.txt","w")



L_Muonia = file_Muonia.read()
L_Muonia = L_Muonia.split("\n")
del L_Muonia[len(L_Muonia)-1]
# remove the \r character from the lines
i = 0
while i<len(L_Muonia):
	L_Muonia[i] = L_Muonia[i].strip("\r")
	i+=1
#print L_default


L_DoubleMu = file_DoubleMu.read()
L_DoubleMu = L_DoubleMu.split("\n")
del L_DoubleMu[len(L_DoubleMu)-1]
# remove the \r character from the lines
i = 0
while i<len(L_DoubleMu):
	L_DoubleMu[i] = L_DoubleMu[i].strip("\r")
	i+=1

L_MuoniaAsliOnly = file_MuoniaAsliOnly.read()
L_MuoniaAsliOnly = L_MuoniaAsliOnly.split("\n")
del L_MuoniaAsliOnly[len(L_MuoniaAsliOnly)-1]
# remove the \r character from the lines
i = 0
while i<len(L_MuoniaAsliOnly):
	L_MuoniaAsliOnly[i] = L_MuoniaAsliOnly[i].strip("\r")
	i+=1



L_DoubleMuAsliOnly = file_DoubleMuAsliOnly.read()
L_DoubleMuAsliOnly = L_DoubleMuAsliOnly.split("\n")
del L_DoubleMuAsliOnly[len(L_DoubleMuAsliOnly)-1]
# remove the \r character from the lines
i = 0
while i<len(L_DoubleMuAsliOnly):
	L_DoubleMuAsliOnly[i] = L_DoubleMuAsliOnly[i].strip("\r")
	i+=1




for x in L_Muonia:
	if x in L_MuoniaAsliOnly:
		file_out_Muonia.write(x+"\n")

for x in L_DoubleMu:
	if x in L_DoubleMuAsliOnly:
		file_out_DoubleMu.write(x+"\n")
