foriginal = open("myfourmuonsignal1selected.txt","r")
f = open("a.txt","r")
fout = open("difference.txt","w")

Loriginal = foriginal.read()
L = f.read()



Loriginal  = Loriginal.split("\n")
L = L.split("\n")

del Loriginal[len(Loriginal)-1]
del L[len(L)-1]

runListOriginal = []
evtListOriginal = []
lumiListOriginal = []
massOriginal = []
massErrorOriginal = []

runList = []
evtList = []
lumiList = []
mass = []
massError = []



for x in L:
	mass.append(x.split(" ")[0])
	massError.append(x.split(" ")[1])
	runList.append( x.split(" ")[12])
	evtList.append( x.split(" ")[13])
	lumiList.append( x.split(" ")[14])


for x in Loriginal:
	massOriginal.append(x.split(" ")[0])
	massErrorOriginal.append(x.split(" ")[1])
	runListOriginal.append( x.split(" ")[12])
	evtListOriginal.append( x.split(" ")[13])
	lumiListOriginal.append( x.split(" ")[14])




# for x in Loriginal:
# 	if x.split(" ")[13] == '545035779':
# 		print x.split(" ")



i = 0
while i < len(evtListOriginal):
	if evtListOriginal[i] not in evtList:
		print evtListOriginal[i], massOriginal[i]
	i += 1



fout.close()
# print Loriginal 
