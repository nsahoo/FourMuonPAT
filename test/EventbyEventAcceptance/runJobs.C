//#include "../myntupleAna.C"
//#include "myntupleAnaSPS.C"
//#include "myntupleAnaDPS.C"
//#include "myntupleAnaPtGun.C"
#include "../myntupleAnaDataEmbedding.C"

void runJobs()
{
  
  TChain * chain = new TChain("mkcands/X_data",""); 

///DPS MC
//chain->Add("/uscms/home/mhaytmyr/nobackup/ExoticQuarkoniumSearch/CMSSW_5_3_7_patch5/src/NtupleMaker/FourMuon/MC/DPSUpsilonUpsilon_FourMuon_ntuple1_MuIDBugFixed.root");
//chain->Add("/uscms/home/mhaytmyr/nobackup/ExoticQuarkoniumSearch/CMSSW_5_3_7_patch5/src/NtupleMaker/FourMuon/MC/DPSUpsilonUpsilon_FourMuon_ntuple2_MuIDBugFixed.root");

///SPS MC
//chain->Add("/uscms/home/mhaytmyr/nobackup/ExoticQuarkoniumSearch/CMSSW_5_3_7_patch5/src/NtupleMaker/FourMuon/MC/SPSUpsilonUpsilon_FourMuon_ntuple_MuIDBugFixed.root");


///Flat Eta_Pt Gun
//chain->Add("/uscms/home/mhaytmyr/nobackup/ExoticQuarkoniumSearch/CMSSW_5_3_7_patch5/src/NtupleMaker/FourMuon/MC/PtGunUpsilonpt_lt50_FourMuon_ntuple_MuIDBugFixed.root");


///Flat Pt Eta Gun Upsilon(2S)
//chain->Add("/uscms/home/mhaytmyr/nobackup/ExoticQuarkoniumSearch/CMSSW_5_3_7_patch5/src/NtupleMaker/FourMuon/MC/PtGunUpsilon2Spt_lt50_FourMuon_ntuple.root");

//Flat Pt Eta Gun Jpsi
//chain->Add("/uscms_data/d3/kdilsiz/UpsilonJpsi/CMSSW_5_3_7_patch5/src/Analyzer/FourMuonPAT/test/CONDOR/condorJPsi2/MCJPsi.root");

///Data Embedding 
//chain->Add("/uscms/home/mhaytmyr/work/CMSSW_5_3_7_patch5/test/NtupleMaker/MC/MCOutPut/PtGunFourMuonDataEmbedding_1.root");
chain->Add("/uscms/home/mhaytmyr/work/CMSSW_5_3_7_patch5/test/NtupleMaker/MC/MCOutPut/PtGunFourMuonDataEmbedding_PU1.root");

  myntuple _myntuple(chain);  
  //myntuple _myntuple;
  _myntuple.Loop();

}
