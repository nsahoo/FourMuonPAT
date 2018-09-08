{
  TChain* chain = new TChain("mkcands/X_data");

  chain->Add("/eos/uscms/store/user/sdurgut/TrigMatch/Merged/Muonia2012B_1.root");

 TFile *f2 = new TFile("/eos/uscms/store/user/sdurgut/TrigMatch/Reduced/Muonia2012B_1.root","recreate");  
 TTree *T2 = chain->CopyTree("MyFourMuonVtxCL>0.01 && MyFourMuonChg==0");
 
 T2->Write();

}
