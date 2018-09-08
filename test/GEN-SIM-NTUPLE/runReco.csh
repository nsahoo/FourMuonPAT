#! /bin/tcsh -f

#setenv SCRAM_ARCH slc5_amd64_gcc434
#setenv SCRAM_ARCH slc5_amd64_gcc462
#source /uscmst1/prod/sw/cms/setup/cshrc prod

#setenv SRM_PATH /uscms/home/sdurgut/srm
#setenv PATH /uscms/home/sdurgut/srm/bin:$PATH


cd /uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src/Analysis/FourMuonPAT/test/GEN-SIM-NTUPLE

eval `scramv1 runtime -csh`
cd $_CONDOR_SCRATCH_DIR
setenv CMSSW_SEARCH_PATH `pwd`:$CMSSW_SEARCH_PATH
setenv CMSSW_SEARCH_PATH /opt/gLite-3.2.8-0/d-cache/srm/bin:$CMSSW_SEARCH_PATH


cp /uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src/Analysis/FourMuonPAT/test/GEN-SIM-NTUPLE/runFourMuonPAT_data_Run2012ABCDCMSSW53X_${1}.py . 

cmsRun runFourMuonPAT_data_Run2012ABCDCMSSW53X_${1}.py


if ( $? != 0 ) then
echo 'CMSSW exited with error code'
rm Run2012_FourMuon_ntuple_${1}.root
exit 1

else 
	#mv Step2_Upsilon1SMuMu_RECO_*.root /eos/uscms/store/user/sdurgut/FourMuon/GEN-SIM-RECO-H02UpsMuMu_ArtifactTest/.
	xrdcp Run2012_FourMuon_ntuple_${1}.root root://cmseos.fnal.gov//store/user/sdurgut/FourMuon/NTUPLE-H02MuMuMuMu/Run2012_FourMuon_ntuple_${1}.root
	rm Run2012_FourMuon_ntuple_${1}.root
endif

