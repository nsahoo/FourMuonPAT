#include "myntupleAnaInclV_RUNNO.C"

void runJobs_RUNNO()
{
  
	TChain * chain = new TChain("mkcands/X_data",""); 
  	// TChain * chain = new TChain("X_data","");


	// chain->Add("/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/muonia/reduced/ReducedAnyCHGMuonia2012C_0.root");
	// chain->Add("root://cmseos.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/muonia/merged/doublemu2011B_4.root");
	// chain->Add("root://cmseos.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/muonia/reduced/doublemu2011B_4.root");
	chain->Add("root://cmseos.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/doublemu/merged/doublemu2011B_4.root");
	// chain->Add("root://cmseos.fnal.gov//store/user/lpcbphy/myfourmuonNtpl/doublemu/reduced/doublemu2011B_4.root");

  	myntuple _myntuple(chain);  
  	//myntuple _myntuple;
  	_myntuple.Loop();

}
