foriginal = open("myfourmuonsignal1selected.txt","r")
flong = open("DoubleMu2011.txt","r")
fout = open("DoubleMu2011Final.txt","w")
# flong = open("Muonia2012.txt","r")
# fout = open("Muonia2012Final.txt","w")


Loriginal = foriginal.read()
Llong = flong.read()



Loriginal  = Loriginal.split("\n")
Llong = Llong.split("\n")

del Loriginal[len(Loriginal)-1]
del Llong[len(Llong)-1]


massOriginal = []
massLong = []
tmp  = []


for x in Loriginal:
	massOriginal.append(x.split(" ")[0])


for x in Llong:
	massLong.append(x.split(" ")[0])


#print Llong

for x in Llong:
	if x in Loriginal:
		if x not in tmp:
			print x
			tmp.append(x)
			fout.write(x + "\n")






# print Loriginal 