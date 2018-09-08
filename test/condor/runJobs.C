#include "myntupleAnaInclV.C"

void runJobs()
{
  
//  TChain * chain = new TChain("mkcands/X_data",""); 
  TChain * chain = new TChain("X_data","");


// chain->Add("/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/muonia/reduced/ReducedAnyCHGMuonia2012C_0.root");
chain->Add("/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/muonia/merged/Muonia2012C_7.root");


  myntuple _myntuple(chain);  
  //myntuple _myntuple;
  _myntuple.Loop();

}
