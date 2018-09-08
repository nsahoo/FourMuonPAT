#! /bin/tcsh -f

set i=1
 
foreach file (Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_*)

if ( -f "/eos/uscms/store/user/lpcbphy/Suleyman/FourMuon/MC/GEN_SIM_RECO_Higgs_Upsilon1SMuMu_NoEtaCut/Step2_Upsilon1SMuMu_RECO_${i}.root" ) then
		echo "Step2_Upsilon1SMuMu_RECO_${i}.root exists!"
else
	echo "Step2_Upsilon1SMuMu_RECO_${i}.root file does not exist, resubmitting..."
	condor_submit submits/condorReco_${i}
endif

@ i++

end

echo "bombili bombili bombom!"
