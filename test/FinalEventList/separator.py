foriginal = open("myfourmuonsignal1selected.txt","r")
fMuonia2011 = open("Muonia2011.txt","r")
fMuonia2012 = open("Muonia2012.txt","r")
fDoubleMu2011 = open("DoubleMu2011.txt","r")
fDoubleMu2012 = open("DoubleMu2012.txt","r")

foutMuonia2011 = open("Muonia2011Final.txt","w")
foutMuonia2012 = open("Muonia2012Final.txt","w")
foutDoubleMu2011 = open("DoubleMu2011Final.txt","w")
foutDoubleMu2012 = open("DoubleMu2012Final.txt","w")



foutMuonia2011Diff = open("Muonia2011FinalDiff.txt","w")
foutMuonia2012Diff = open("Muonia2012FinalDiff.txt","w")
foutDoubleMu2011Diff = open("DoubleMu2011FinalDiff.txt","w")
foutDoubleMu2012Diff = open("DoubleMu2012FinalDiff.txt","w")




Loriginal = foriginal.read()
LMuonia2011 = fMuonia2011.read()
LMuonia2012 = fMuonia2012.read()
LDoubleMu2011 = fDoubleMu2011.read()
LDoubleMu2012 = fDoubleMu2012.read()


Loriginal  = Loriginal.split("\n")
LMuonia2011  = LMuonia2011.split("\n")
LMuonia2012  = LMuonia2012.split("\n")
LDoubleMu2011  = LDoubleMu2011.split("\n")
LDoubleMu2012  = LDoubleMu2012.split("\n")

#print LDoubleMu2012


del Loriginal[len(Loriginal)-1]
del LMuonia2011[len(LMuonia2011)-1]
del LMuonia2012[len(LMuonia2012)-1]
del LDoubleMu2011[len(LDoubleMu2011)-1]
del LDoubleMu2012[len(LDoubleMu2012)-1]

tmp = []

# print len(Loriginal), len(LMuonia2011), len(LMuonia2012), len(LDoubleMu2011), len(LDoubleMu2012)

for x in LMuonia2011:
	if x in Loriginal:
		if x not in tmp:
			tmp.append(x)
			foutMuonia2011.write(x + "\n")

for x in LMuonia2012:
	if x in Loriginal:
		if x not in tmp:
			tmp.append(x)
			foutMuonia2012.write(x + "\n")
for x in LDoubleMu2011:
	if x in Loriginal:
		if x not in tmp:
			tmp.append(x)
			foutDoubleMu2011.write(x + "\n")
for x in LDoubleMu2012:
	if x in Loriginal:
		if x not in tmp:
			tmp.append(x)
			foutDoubleMu2012.write(x + "\n")





# for x in Loriginal:
# 	tmporg = x.split(" ") 
# 	isExist = False
# 	for y in LMuonia2011:
# 		tmp = y.split(" ") 

# 		if( 
# 			(tmp[0] == tmporg[0]) and # 4 mu mass
# 			(tmp[1] == tmporg[1]) and # 4 mu mass error
# 			(tmp[2] == tmporg[8]) and # 4mu vertex prob
# 			(tmp[22] == tmporg[12]) and # run num
# 			(tmp[23] == tmporg[13]) and  # evt num
# 			(tmp[24] == tmporg[14]) ) : # lumi num
# 		# if(tmp[23] == tmporg[13]):
# 			print "First pass"
# 			isExist = True
# 			break
# 	if isExist: 
# 		foutMuonia2011.write(x + "\n")
# 	# else:
# 	# 	foutMuonia2011Diff.write(x + "\n")
		


# for x in Loriginal:
# 	tmporg = x.split(" ") 
# 	isExist = False
# 	for y in LMuonia2012:
# 		tmp = y.split(" ") 
# 		if( 
# 			(tmp[0] == tmporg[0]) and # 4 mu mass
# 			(tmp[1] == tmporg[1]) and # 4 mu mass error
# 			(tmp[2] == tmporg[8]) and # 4mu vertex prob
# 			(tmp[22] == tmporg[12]) and # run num
# 			(tmp[23] == tmporg[13]) and  # evt num
# 			(tmp[24] == tmporg[14]) ) : # lumi num
# 		# if(tmp[23] == tmporg[13]):
# 			print "Second pass"
# 			isExist = True
# 			break
# 	if isExist: 
# 		foutMuonia2012.write(x + "\n")
# 	# else:
# 	# 	foutMuonia2012Diff.write(x + "\n")
		

# for x in Loriginal:
# 	tmporg = x.split(" ") 
# 	isExist = False
# 	for y in LDoubleMu2011:
# 		tmp = y.split(" ") 
# 		if( 
# 			(tmp[0] == tmporg[0]) and # 4 mu mass
# 			(tmp[1] == tmporg[1]) and # 4 mu mass error
# 			(tmp[2] == tmporg[8]) and # 4mu vertex prob
# 			(tmp[22] == tmporg[12]) and # run num
# 			(tmp[23] == tmporg[13]) and  # evt num
# 			(tmp[24] == tmporg[14]) ) : # lumi num
# 		# if(tmp[23] == tmporg[13]):
# 			print "Third pass"
# 			isExist = True
# 			break
# 	if isExist: 
# 		foutDoubleMu2011.write(x + "\n")
# 	# else:
# 	# 	foutDoubleMu2011Diff.write(x + "\n")



# for x in Loriginal:
# 	tmporg = x.split(" ") 
# 	isExist = False
# 	for y in LDoubleMu2012:
# 		tmp = y.split(" ") 
# 		if( 
# 			(tmp[0] == tmporg[0]) and # 4 mu mass
# 			(tmp[1] == tmporg[1]) and # 4 mu mass error
# 			(tmp[2] == tmporg[8]) and # 4mu vertex prob
# 			(tmp[22] == tmporg[12]) and # run num
# 			(tmp[23] == tmporg[13]) and  # evt num
# 			(tmp[24] == tmporg[14]) ) : # lumi num
# 		#if(tmp[23] == tmporg[13]):
# 			print "Fourth pass"
# 			isExist = True
# 			break
# 	if isExist: 
# 		foutDoubleMu2012.write(x + "\n")
# 	# else:
# 	# 	foutDoubleMu2012Diff.write(x + "\n")

foriginal.close()
fMuonia2011.close()
fMuonia2012.close()
fDoubleMu2011.close()
fDoubleMu2012.close()


foutMuonia2011.close()
foutMuonia2012.close()
foutDoubleMu2011.close()
foutDoubleMu2012.close()


foutMuonia2011Diff.close()
foutMuonia2012Diff.close()
foutDoubleMu2011Diff.close()
foutDoubleMu2012Diff.close()



