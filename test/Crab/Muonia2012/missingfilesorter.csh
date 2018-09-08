#! /bin/tcsh -f

set i=1
#   while ( $i < 1548)
#   while ( $i < 759)
	while	( $i < 2467)

#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/muonia/2012Brepair/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i} 
#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/muonia/2012Crepair/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i} 
#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/muonia/2011Brepair/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i} 
#[ -s /eos/uscms/store/user/lpcbphy/noreplica/yik/mymumuKKNtpl/muonia/2012A/MuOniaRun2012_MuMuKKPAT_ntpl_${i}_*.root ]  || echo ${i}
#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/doublemuparked/2012Bcrab/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i}
#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/singlemuon/2012Dcrab/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i}
#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/muoniaparked/2012Bcrab/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i}
#[ -s /eos/uscms/store/user/yik/mymumueeNtpl/doubleelectron/2012A/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root ]  || echo ${i}
#[ -s /eos/uscms/store/user/yik/myfourmuonNtpl/doublemu/2011B/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i}
[ -s /eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Muonia2012B/Run2012_FourMuon_ntuple_${i}_*.root ]  || echo ${i}
#test -e /eos/uscms/store/user/sdurgut/MuMuEE/MuoniaParkedRun2012D/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root || echo ${i}

#echo "File Not there"



#	while	( $i < 1846)
#	while	( $i < 1819)
	#test -e /pnfs/cms/WAX/11/store/user/mhaytmyr/QCD_HT100To250/QCD_Ht100to250_patntuple_${i}_*.root


	#test -e /eos/uscms/store/user/mhaytmyr/DoubleMuNtpl/DoubleEle2012AJan22/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root
#	test -e /eos/uscms/store/user/mhaytmyr/DoubleMuNtpl/DoubleEle2012DJan22/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/DoubleMuNtpl/Parked2012CJan22/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/DoubleMuNtpl/Parked2012BJan22/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/DoubleMuNtpl/Parked2012AJan22/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/DoubleMuNtpl/Parked2012DJan22/MuOniaRun2012_MuMuEEPAT_ntpl_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/MuOniaNtpl/Run2011ANov08/Run2011_FourMuon_ntuple_${i}_*.root
#hehe =test -e /eos/uscms/store/user/mhaytmyr/MuOniaNtpl/Run2011ANov08/Run2011_FourMuon_ntuple_99999_*.root  
#test -e /eos/uscms/store/user/yik/myfourmuonNtpl/muonia/2012Brepair/Run2012_FourMuon_ntuple_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/MuOniaNtpl/Run2012BJan22/Run2012_FourMuon_ntuple_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/MuOniaNtpl/Run2012CJan22/Run2012_FourMuon_ntuple_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/MuOniaNtpl/Run2012DJan22/Run2012_FourMuon_ntuple_${i}_*.root
#test -e /eos/uscms/store/user/mhaytmyr/MuOniaNtpl/Run2011BNov19/Run2011_FourMuon_ntuple_${i}_*.root

	#dc_dccp /pnfs/cms/WAX/11/store/user/mhaytmyr/QCD_HT250To500/QCD_Ht250to500_patntuple_${i}_*.root /eos/uscms/store/user/mhaytmyr/QCD_HT250To500/	
 #        if ($? == 0) then 
 #              #  echo This file is already done: ${i} #>> existing
 #        else  
 #              echo "${i},\c" >> missing 
 #        endif 
     
  @ i++

end

