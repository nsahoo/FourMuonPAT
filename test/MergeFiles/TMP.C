{
  TChain* chain = new TChain("mkcands/X_data");

  chain->Add("/eos/uscms/store/user/lpcbphy/Suleyman/FourMuonNtpl/Muonia/merged/MergedMuonia2012D_9.root");

 TFile *f2 = new TFile("/eos/uscms/store/user/lpcbphy/Suleyman/FourMuonNtpl/Muonia/merged/MergedMuonia2012D_9.root","recreate");  
 TTree *T2 = chain->CopyTree("MyFourMuonVtxCL>0.0001");
 
 T2->Write();
 
}
