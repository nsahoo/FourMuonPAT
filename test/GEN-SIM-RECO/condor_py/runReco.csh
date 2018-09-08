#! /bin/tcsh -f

#setenv SCRAM_ARCH slc5_amd64_gcc434
#setenv SCRAM_ARCH slc5_amd64_gcc462
#source /uscmst1/prod/sw/cms/setup/cshrc prod

#setenv SRM_PATH /uscms/home/sdurgut/srm
#setenv PATH /uscms/home/sdurgut/srm/bin:$PATH


cd /uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src/Analysis/FourMuonPAT/test/GEN-SIM-RECO/condor_py

eval `scramv1 runtime -csh`
cd $_CONDOR_SCRATCH_DIR
setenv CMSSW_SEARCH_PATH `pwd`:$CMSSW_SEARCH_PATH
setenv CMSSW_SEARCH_PATH /opt/gLite-3.2.8-0/d-cache/srm/bin:$CMSSW_SEARCH_PATH


cp /uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src/Analysis/FourMuonPAT/test/GEN-SIM-RECO/condor_py/Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_${1}.py . 

cmsRun Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_${1}.py


if ( $? != 0 ) then
echo 'CMSSW exited with error code'
rm Step2_Upsilon1SMuMu_RECO_${1}.root
exit 1

else 
	#mv Step2_Upsilon1SMuMu_RECO_*.root /eos/uscms/store/user/sdurgut/FourMuon/GEN-SIM-RECO-H02UpsMuMu_ArtifactTest/.
	xrdcp Step2_Upsilon1SMuMu_RECO_${1}.root root://cmseos.fnal.gov//store/user/sdurgut/FourMuon/GEN-SIM-RECO-H02UpsMuMu_ArtifactTest/Step2_Upsilon1SMuMu_RECO_${1}.root
	rm Step2_Upsilon1SMuMu_RECO_${1}.root
endif

