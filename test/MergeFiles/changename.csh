#! /bin/tcsh -f

set i=1

 foreach file (/eos/uscms/store/user/lpcbphy/Suleyman/FourMuonNtpl/Muonia/reduced/*.root)

	set new =  "`echo ${file:t}`"
	echo $new
	echo $i

	sed -e "s/Merged/Reduced/g" TMP_${i}.C > Reduce_${i}.C
	#sed -e "s/RUNNO/${i}/g" TMP.C > TMP1.C
#	sed -e "s/RUNNO/${i}/g" TMP.C > myReduce_${i}.C
#	sed -e "s/RUNNO/${i}/g" myntuple.C > TMP2.C
#	sed -e "s/RUNNO/${i}/g" TMP2.C > myntuple_${i}.C

#	sed -e "s/RUNNO/${i}/g" condorReco_jdf > submits/condorReco_${i}
#	condor_submit submits/condorReco_${i}

	@ i++

end

