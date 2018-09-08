#!/bin/bash

cmsswDir="/uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src"
inputFiles=""
#dcacheDirIn="/uscmst1b_scratch/lpc1/lpcphys/yik/myfourmuonNtpl/muonia/reducedcopy/"
#dcacheDirIn="/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/muonia/merged"
dcacheDirIn="/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/muonia/reduced/"
#dcacheDirIn="/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/CrossSection/FourMuonNtuple/Muonia2012D/MuOnia/crab_Run2012D/160509_201959/0000/"
#dcacheDirIn="/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/CrossSection/FourMuonNtuple/Muonia2012C/MuOnia/crab_Run2012C/160509_201058/0000/"
#dcacheDirIn="/eos/uscms/store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5"
#dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/muonia/merged"
dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/muonia/reduced"
#dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/noreplica/sdurgut/CrossSection/FourMuonNtuple/Muonia2012C/MuOnia/crab_Run2012C/160509_201058/0000/"
#dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/noreplica/sdurgut/CrossSection/FourMuonNtuple/Muonia2012D/MuOnia/crab_Run2012D/160509_201959/0000/"
##dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/noreplica/sdurgut/FourMuon/Ntuple_OMC_Higgs2MuMu_m18p5"
j=0
for files in `ls  $dcacheDirIn | grep root` # this is for running all the files
#for files in `ls  $dcacheDirIn | grep 2012`
do 
	inputFiles=$files;
	echo $inputFiles;
	jobNb=${j};
	let j=${j}+1;
	#anaHeader="myntuple_${jobNb}.h";
	#anaCScript="myntuple_${jobNb}.C";
	command="../myntuple_C.so,../myntuple_C.d";
	jobCScript="runJobs_${jobNb}.C";
	scriptName="Run_${jobNb}.csh";
	condorScriptName="runOnCondor_${jobNb}";
	#cat myntuple.h | sed "s/NUMBER/${jobNb}/g" > ${anaHeader};
	#cat myntuple.C | sed "s/NUMBER/${jobNb}/g" > ${anaCScript};
	cat runJobs.C | sed "s-INPUTPATH-${dcacheDirInNew}-" | sed "s-INPUTFILE-${inputFiles}-" | sed "s/NUMBER/${jobNb}/g" > ${jobCScript};
	cat Run.csh | sed "s-FILENAME-${jobCScript}-" | sed "s-CMSSWDIR-${cmsswDir}-" > ${scriptName};
	chmod +x ${scriptName}
	cat runOnCondor | sed "s/SCRIPT/${scriptName}/" | sed "s-COMMAND-${command}-" | sed "s/JOBC/${jobCScript}/" > ${condorScriptName}
	condor_submit ${condorScriptName}
done
