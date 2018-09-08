#!/bin/csh
source /cvmfs/cms.cern.ch/cmsset_default.csh
cd CMSSWDIR
cmsenv
cd ${_CONDOR_SCRATCH_DIR}
cmsRun FILENAME

mv FILENAME /eos/uscms/store/user/sdurgut/FourMuon/GEN-SIM-RECO-H02UpsMuMu_ArtifactTest/.
