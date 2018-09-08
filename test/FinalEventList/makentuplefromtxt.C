

void makentuplefromtxt()
{

  TFile * t=new TFile("finalselectionntuple.root","recreate");
  TTree *mytree = new TTree("mytree", "mytree");
  mytree->ReadFile("myFinalfourmuonsignal.txt", "fourmuonmass:fourmuonmassErr:mupmumhighmass:mupmumhighmassErr:mupmumhighmassFit:mupmumlowmassFit:mupmummasswrong1:mupmummasswrong2:fourmuonvtxprob:rawfourmuonpt:mupmummupmass:mupmummummass:runnum:evtnum:luminum:dupnum:mupmumhighmassFitN:mupmumlowmassFitN:fitmu11px:fitmu11py:fitmu11pz:fitmu12px:fitmu12py:fitmu12pz:fitmu21px:fitmu21py:fitmu21pz:rawmu11px:rawmu11py:rawmu11pz:rawmu12px:rawmu12py:rawmu12pz:rawmu21px:rawmu21py:rawmu21pz:rawmu22px:rawmu22py:rawmu22pz:fitmu22px:fitmu22py:fitmu22pz:mypidx:mu12ctau:mu34ctau:mu14ctau:mu23ctau:fourmuctau");

  mytree->Write();






/*
  TH1F * mymassY1s= new TH1F("mymassY1s","mymassY1s",2500,0,25);
  mytree->Project("mymassY1s","Y1s");
  mymassY1s->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{1} [GeV], #Upsilon(1S) candidate");
  mymassY1s->GetYaxis()->SetTitle("Candidates/10 MeV");

  TH1F * mymasssecondpair= new TH1F("mymasssecondpair","mymasssecondpair",2500,0,25);
  mytree->Project("mymasssecondpair","mmumu");
  mymasssecondpair ->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{2} [GeV], second pair");
  mymasssecondpair->GetYaxis()->SetTitle("Candidates/10 MeV");



  TH1F * mymassmumuanother1= new TH1F("mymassmumuanother1","mymassmumuanother1",2500,0,25);
  mytree->Project("mymassmumuanother1","mmumuanother1");
  mymassmumuanother1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{3} [GeV], one muon from #Upsilon(1S), one muon from second pair");
  mymassmumuanother1->GetYaxis()->SetTitle("Candidates/10 MeV");

  TH1F * mymassmumuanother2= new TH1F("mymassmumuanother2","mymassmumuanother2",2500,0,25);
  mytree->Project("mymassmumuanother2","mmumuanother2");
  mymassmumuanother2->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{4} [GeV], one muon from #Upsilon(1S), one muon from second pair");
  mymassmumuanother2->GetYaxis()->SetTitle("Candidates/10 MeV");
*/




}
