fshort = open("myfourmuonsignal1selected.txt","r")
flong = open("myfourmuonsignal1selectedwithctau.txt","r")
fout = open("myFinalfourmuonsignal.txt","w")

Lshort = fshort.read()
Llong = flong.read()



Lshort  = Lshort.split("\n")
Llong = Llong.split("\n")

del Lshort[len(Lshort)-1]
del Llong[len(Llong)-1]


for x in Llong:
	tmpLongList = x.split(" ")
	#print tmpLongList
	isExist = False
	for y in Lshort:
		tmpShortList = y.split(" ")
		if( (tmpShortList[0] == tmpLongList[0]) and
			(tmpShortList[1] == tmpLongList[1]) and
			(tmpShortList[12] == tmpLongList[12]) and 
			(tmpShortList[13] == tmpLongList[13]) and 
			(tmpShortList[14] == tmpLongList[14]) ) :
			isExist = True
			break

	if isExist: 
		fout.write(x + "\n")


fshort.close()
flong.close()
fout.close()





# print Lshort 