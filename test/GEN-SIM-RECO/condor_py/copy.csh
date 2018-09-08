#! /bin/tcsh -f

# set i=1
foreach file (`cat a.txt`)

	# set new =  "`echo ${file:t}`"
	echo $file
	# set a=`echo $file | awk -F"." '{print $1}'`
	# echo "$a"
	# srmcp -2 file:////eos/uscms/store/user/sdurgut/ParkedData/Parked2012Dv1_22Jan/$file "srm://cmssrm.fnal.gov:8443/srm/managerv2?SFN=/11/store/user/sdurgut/ParkedData/Parked2012D_Jan22/$file"
	mv $file /eos/uscms/store/user/sdurgut/MONTECARLO/MC_D0toMuMu_Ntpl/.
	# done
	# @ i++
	#done 
end
