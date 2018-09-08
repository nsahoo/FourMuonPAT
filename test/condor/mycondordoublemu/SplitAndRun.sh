#!/bin/bash

cmsswDir="/uscms_data/d3/sdurgut/SL6/CMSSW_5_3_32/src/"
inputFiles=""
# dcacheDirIn="/uscmst1b_scratch/lpc1/lpcphys/yik/myfourmuonNtpl/doublemu/reducedcopy/"
# dcacheDirIn="/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/doublemu/merged"
dcacheDirIn="/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/doublemu/reduced"
#dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/doublemu/merged"
dcacheDirInNew="root://cmsxrootd.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/doublemu/reduced"

j=0
for files in `ls $dcacheDirIn | grep root` # this to run all root files in the directory
#for files in `ls $dcacheDirIn | grep 2012`
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
