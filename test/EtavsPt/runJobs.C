#include "myntupleAna.C"

void runJobs()
{
  
//  TChain * chain = new TChain("mkcands/X_data",""); 
  TChain * chain = new TChain("mytree","");


// chain->Add("/eos/uscms/store/user/lpcbphy/myfourmuonNtpl/muonia/reduced/ReducedAnyCHGMuonia2012C_0.root");
chain->Add("finalselectionntuple.root");


  myntuple _myntuple(chain);  
  //myntuple _myntuple;
  _myntuple.Loop();

}
