#! /bin/tcsh -f

set i=1 
foreach file (/eos/uscms/store/user/sdurgut/FourMuon/GEN_SIM_Higgs_DPS_UpsUps/*.root )

  set new =  "`echo ${file:t}`"
  echo $new
  echo $i

  sed -e "s/FILENAME/${new}/g" Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO.py  > TMP.py
  sed -e "s/RUNNO/${i}/g" TMP.py > Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_${i}.py
  sed -e "s/RUNNO/${i}/g" condorReco_jdf > submits/condorReco_${i}

  condor_submit submits/condorReco_${i}
  @ i++
end

