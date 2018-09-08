fin = open("2011and2012combinedsortRemoveNotMatchedbetween13and26GeVRemoveMultipleCandsby4mvtxprobApplyseconddimumasscut.txt","r")
fd = open("d.txt","r")
fm = open("m.txt","r")

foutd = open("foutd.txt","w")
foutm = open("foutm.txt", "w")

Lin = fin.read()
Ld = fd.read()
Lm = fm.read()

Lin = Lin.split("\n")
Ld = Ld.split("\n")
Lm = Lm.split("\n")



del Lin[len(Lin)-1]
del Ld[len(Ld)-1]
del Lm[len(Lm)-1]

runNumMuonia = []
evtNumMuonia = []
lumiNumMuonia = []

runNumDoubleMu = []
evtNumDoubleMu = []
lumiNumDoubleMu = []

for x in Lm:
	tmp = x.split()
	runNumMuonia.append(tmp[0])
	evtNumMuonia.append(tmp[1])
	lumiNumMuonia.append(tmp[2])

for x in Ld:
	tmp = x.split()
	runNumDoubleMu.append(tmp[0])
	evtNumDoubleMu.append(tmp[1])
	lumiNumDoubleMu.append(tmp[2])

# print evtNumDoubleMu
# print runNumMuonia

for x in Lin:
	tmp = x.split()
	if (tmp[10] in runNumMuonia) and (tmp[11] in evtNumMuonia) and (tmp[12] in lumiNumMuonia):
		foutm.write(tmp[0] + " " + tmp[1] + " " + tmp[2] + " " + tmp[3] + " " + tmp[4] + " " + tmp[5] + " " + 
			tmp[6] + " " + tmp[7] + " " + tmp[8] + " " + tmp[9] + " " + tmp[10] + " " + tmp[11] + " " + tmp[12] + "\n")


for x in Lin:
	tmp = x.split()
	if (tmp[10] in runNumDoubleMu) and (tmp[11] in evtNumDoubleMu) and (tmp[12] in lumiNumDoubleMu):
		foutd.write(tmp[0] + " " + tmp[1] + " " + tmp[2] + " " + tmp[3] + " " + tmp[4] + " " + tmp[5] + " " + 
			tmp[6] + " " + tmp[7] + " " + tmp[8] + " " + tmp[9] + " " + tmp[10] + " " + tmp[11] + " " + tmp[12] + "\n")