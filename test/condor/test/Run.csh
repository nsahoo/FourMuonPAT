#!/bin/csh
source /cvmfs/cms.cern.ch/cmsset_default.csh
setenv SCRAM_ARCH slc6_amd64_gcc472
eval `scramv1 project CMSSW CMSSW_5_3_32`
cd CMSSW_5_3_32/src
eval `scramv1 runtime -csh` # cmsenv is an alias not on the workers
cd ${_CONDOR_SCRATCH_DIR}
root -b -q -l FILENAME
