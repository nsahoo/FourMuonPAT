#! /bin/tcsh -f

set i=1 
#foreach file (/eos/uscms/store/user/lpcbphy/Suleyman/FourMuon/MC/GEN_SIM_Higgs_Upsilon1SMuMu_NoEtaCut/*.root )
foreach file (/eos/uscms/store/user/sdurgut/FourMuon/GEN-SIM-RECO-H02JpsiMuMu/GEN-SIM-H02JpsiMuMu/crab_Step2_H02JpsiMuMu/161128_154916/0000/*.root )
  set new =  "`echo ${file:t}`"
  echo $new
  echo $i

  sed -e "s/FILENAME/${new}/g" runFourMuonPAT_data_Run2012ABCDCMSSW53X.py  > TMP.py
  sed -e "s/RUNNO/${i}/g" TMP.py > runFourMuonPAT_data_Run2012ABCDCMSSW53X_${i}.py
  sed -e "s/RUNNO/${i}/g" condorReco_jdf > submits/condorReco_${i}

  condor_submit submits/condorReco_${i}
  @ i++
end

