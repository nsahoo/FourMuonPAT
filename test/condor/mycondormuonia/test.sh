#!/bin/bash

cmsswDir="/uscms_data/d2/yik/CMSSW_5_3_7_patch5/src/"
inputFiles=""
dcacheDirIn="/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/doublemu/reduced/"
#dcacheDirIn="/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/doublemu/merged/"
#dcacheDirIn="/uscmst1b_scratch/lpc1/lpcphys/yik/myfourmuonNtpl/doublemu/reducedcopy/"
myeospath="root://cmsxrootd.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/doublemu/reduced/"


j=0
for files in `ls $dcacheDirIn | grep root`
#for files in `ls $dcacheDirIn | grep 2011`

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
#	cat runJobs.C | sed "s-INPUTPATH-${dcacheDirIn}-" | sed "s-INPUTFILE-${inputFiles}-" | sed "s/NUMBER/${jobNb}/g" > ${jobCScript};
        cat runJobs.C | sed "s-INPUTPATH-${myeospath}-" | sed "s-INPUTFILE-${inputFiles}-" | sed "s/NUMBER/${jobNb}/g" > ${jobCScript};
	cat Run.csh | sed "s-FILENAME-${jobCScript}-" | sed "s-CMSSWDIR-${cmsswDir}-" > ${scriptName};
	chmod +x ${scriptName}
	cat runOnCondor | sed "s/SCRIPT/${scriptName}/" | sed "s-COMMAND-${command}-" | sed "s/JOBC/${jobCScript}/" > ${condorScriptName}
	condor_submit ${condorScriptName}
done
