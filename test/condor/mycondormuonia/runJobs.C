void runJobs_NUMBER()
 {
	gSystem->Load("myntuple_C.so");
	TChain * chain = new TChain("X_data","");
	// TChain * chain = new TChain("mkcands/X_data","");
	chain->Add("INPUTPATH/INPUTFILE");
	// chain->Add("root://cmsxrootd.fnal.gov/INPUTPATH/INPUTFILE");
	// chain->Add("INPUTPATH/INPUTFILE");
	myntuple a(chain);
	a.Loop("output_NUMBER.root");
 }
