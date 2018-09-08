#!/bin/bash

cmsswDir="/uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src"
inputFiles=""
dcacheDirIn="/eos/uscms/store/user/sdurgut/FourMuon/GEN-SIM-H02UpsMuMu_ArtifactTest/crab_H02UpsMuMu_ArtifactTest/160524_003521/0000/"
dcacheDirInNew="/eos/uscms/store/user/sdurgut/FourMuon/GEN-SIM-H02UpsMuMu_ArtifactTest/crab_H02UpsMuMu_ArtifactTest/160524_003521/0000/"
j=0
for files in `ls  $dcacheDirIn | grep root`
do 

	inputFiles=$files;
	echo $inputFiles;
	jobNb=${j};
	let j=${j}+1;
	command="../myntuple_C.so,../myntuple_C.d";
	jobCScript="Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO_${jobNb}.py";
	scriptName="Run_${jobNb}.csh";
	condorScriptName="runOnCondor_${jobNb}";
	cat Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO.py | sed "s-INPUTPATH-${dcacheDirInNew}-" | sed "s-INPUTFILE-${inputFiles}-" | sed "s/NUMBER/${jobNb}/g" > ${jobCScript};
	cat Run.csh | sed "s-FILENAME-${jobCScript}-" | sed "s-CMSSWDIR-${cmsswDir}-" > ${scriptName};
	chmod +x ${scriptName}
	cat runOnCondor | sed "s/SCRIPT/${scriptName}/" | sed "s/JOBC/${jobCScript}/" > ${condorScriptName}
	condor_submit ${condorScriptName}
done
