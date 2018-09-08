#define myntuple_cxx
#include "myntuple.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"
#include "TPoint.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define muon_mass  0.105658
#define jpsi_mass 3.0967

//order mode, 1--order by higer mass, m(11)>m(12), m(21)>m(22),  m(11)>m(21), 
#define myordermode 1


//11=Y(1S) mumu <Y(1S), 
#define mychannel 11

struct PairedMuonIdx {
  int p11;
  int p12;
  int p21;
  int p22;
};

void swap_two_paired_pair( PairedMuonIdx & myp1,  PairedMuonIdx & myp2 )
{
  int mytmp1, mytmp2;
  mytmp1=myp1.p11;  mytmp2=myp1.p12; 
  myp1.p11=myp2.p11;  myp1.p12=myp2.p12;
  myp2.p11=mytmp1;  myp2.p12=mytmp2;

  mytmp1=myp1.p21;  mytmp2=myp1.p22; 
  myp1.p21=myp2.p21;  myp1.p22=myp2.p22;
  myp2.p21=mytmp1;  myp2.p22=mytmp2;
}

void swap_one_paired_pair( PairedMuonIdx & myp )
{
  int mytmp1, mytmp2;
  mytmp1=myp.p11;  mytmp2=myp.p12; 
  myp.p11=myp.p21;  myp.p12=myp.p22;
  myp.p21=mytmp1;  myp.p22=mytmp2;
}

void swap_one_pair( PairedMuonIdx & myp, int whichpair )
{
  int mytmp;
  if( whichpair==1 ) {
    mytmp=myp.p11; 
    myp.p11=myp.p12; myp.p12=mytmp;
  }
  else if( whichpair==2 ) {
    mytmp=myp.p21; 
    myp.p21=myp.p22; myp.p22=mytmp;
  }//else

}

 
void myntuple::Loop()
{  
  ofstream myoutfilesignal("myfourmuonsignal.txt");
  ofstream myoutfileEvtNum("myfourmuonEvtNum.txt");
  ofstream myoutfileevtmix("myfourmuonevtmix.txt");

  TFile* myhbk = new TFile ("myhbk_MuOnia.root","recreate");

  TH1F* myMuMuonlymass = new TH1F("myMuMuonlymass","myMuMuonlymass",100000,0,500.0);  
  myMuMuonlymass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuOnlyIso = new TH1F("myMuMuOnlyIso","myMuMuOnlyIso",50,0,5.0);


  TH1F* myMuMumassforV1highpair = new TH1F("myMuMumassforV1highpair","myMuMumassforV1highpair",100000,0,500.0);  
  myMuMumassforV1highpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{hh} GeV");
  TH1F* myMuMumassforV1lowpair = new TH1F("myMuMumassforV1lowpair","myMuMumassforV1lowpair",100000,0,500.0);  
  myMuMumassforV1lowpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{lh} GeV");
  TH1F* myMuMumassformumulowpair = new TH1F("myMuMumassformumulowpair","myMuMumassformumulowpair",100000,0,500.0);  
  myMuMumassformumulowpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{ll} GeV");
  TH1F* myMuMumassformumuhighpair = new TH1F("myMuMumassformumuhighpair","myMuMumassformumuhighpair",100000,0,500.0);  
  myMuMumassformumuhighpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{hl} GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1 = new TH1F("myMuMuMuMumassV1mumubelowV1","myMuMuMuMumassV1mumubelowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuPPDeltapxpypz = new TH1F("myMuPPDeltapxpypz","myMuPPDeltapxpypz",10000,0,1000.0);
  myMuPPDeltapxpypz->GetXaxis()->SetTitle("|#Delta Px|+|#Delta Py|+|#Delta Pz| between #mu^{+}#mu^{+} [GeV]");
  TH1F* myMuMMDeltapxpypz = new TH1F("myMuMMDeltapxpypz","myMuMMDeltapxpypz",10000,0,1000.0);
  myMuMMDeltapxpypz->GetXaxis()->SetTitle("|#Delta Px|+|#Delta Py|+|#Delta Pz| between #mu^{-}#mu^{-} [GeV]");


  TH1F* myMuMuMuMumassV1mumubelowV1cowboyVscowboy = new TH1F("myMuMuMuMumassV1mumubelowV1cowboyVscowboy","myMuMuMuMumassV1mumubelowV1cowboyVscowboy",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1cowboyVscowboy->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1cowboyVsseagull = new TH1F("myMuMuMuMumassV1mumubelowV1cowboyVsseagull","myMuMuMuMumassV1mumubelowV1cowboyVsseagull",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1cowboyVsseagull->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1seagullVscowboy = new TH1F("myMuMuMuMumassV1mumubelowV1seagullVscowboy","myMuMuMuMumassV1mumubelowV1seagullVscowboy",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1seagullVscowboy->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1seagullVsseagull = new TH1F("myMuMuMuMumassV1mumubelowV1seagullVsseagull","myMuMuMuMumassV1mumubelowV1seagullVsseagull",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1seagullVsseagull->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
 

  TH1F* myMuMuMuMumassV1mumuWithVIso0dot1belowV1 = new TH1F("myMuMuMuMumassV1mumuWithVIso0dot1belowV1","myMuMuMuMumassV1mumuWithVIso0dot1belowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumuWithVIso0dot1belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumuWithVIso0dot2belowV1 = new TH1F("myMuMuMuMumassV1mumuWithVIso0dot2belowV1","myMuMuMuMumassV1mumuWithVIso0dot2belowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumuWithVIso0dot2belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumuWithVIso0dot5belowV1 = new TH1F("myMuMuMuMumassV1mumuWithVIso0dot5belowV1","myMuMuMuMumassV1mumuWithVIso0dot5belowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumuWithVIso0dot5belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");



  TH1F* myMuMuMuMumassV1highestmuWithVIso0dot1belowV1 = new TH1F("myMuMuMuMumassV1highestmuWithVIso0dot1belowV1","myMuMuMuMumassV1highestmuWithVIso0dot1belowV1",10000,0,1000.0);
  myMuMuMuMumassV1highestmuWithVIso0dot1belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1highestmuWithVIso0dot2belowV1 = new TH1F("myMuMuMuMumassV1highestmuWithVIso0dot2belowV1","myMuMuMuMumassV1highestmuWithVIso0dot2belowV1",10000,0,1000.0);
  myMuMuMuMumassV1highestmuWithVIso0dot2belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1highestmuWithVIso0dot5belowV1 = new TH1F("myMuMuMuMumassV1highestmuWithVIso0dot5belowV1","myMuMuMuMumassV1highestmuWithVIso0dot5belowV1",10000,0,1000.0);
  myMuMuMuMumassV1highestmuWithVIso0dot5belowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");







  TH1F* myMuMuMuMumassV1mumubelowV1LowSide = new TH1F("myMuMuMuMumassV1mumubelowV1LowSide","myMuMuMuMumassV1mumubelowV1LowSide",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1LowSide->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1HighSide = new TH1F("myMuMuMuMumassV1mumubelowV1HighSide","myMuMuMuMumassV1mumubelowV1HighSide",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1HighSide->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");

  TH1F* myMuMuMuMumassV1mumubelowV1LowSideShift = new TH1F("myMuMuMuMumassV1mumubelowV1LowSideShift","myMuMuMuMumassV1mumubelowV1LowSideShift",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1LowSideShift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  TH1F* myMuMuMuMumassV1mumubelowV1HighSideShift = new TH1F("myMuMuMuMumassV1mumubelowV1HighSideShift","myMuMuMuMumassV1mumubelowV1HighSideShift",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1HighSideShift->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");


  TH1F* myMuMuMuMumassDiffV1mumubelowV1 = new TH1F("myMuMuMuMumassDiffV1mumubelowV1","myMuMuMuMumassDiffV1mumubelowV1",10000,0,1000.0);
  TH2F* myV1VsMuMuMassBeforeVVmasshighpair = new TH2F("myV1VsMuMuMassBeforeVVmasshighpair","myV1VsMuMuMassBeforeVVmasshighpair",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassBeforeVVmasshighpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassBeforeVVmasshighpair->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");  
  TH2F* myV1VsMuMuMassBeforeVVmasslowpair = new TH2F("myV1VsMuMuMassBeforeVVmasslowpair","myV1VsMuMuMassBeforeVVmasslowpair",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassBeforeVVmasslowpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassBeforeVVmasslowpair->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");
  TH2F* myV1VsMuMuMassAfterVVmassanotherpair = new TH2F("myV1VsMuMuMassAfterVVmassanotherpair","myV1VsMuMuMassAfterVVmassanotherpair",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassAfterVVmassanotherpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassAfterVVmassanotherpair->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");  



  TH1F* myMuMu2Massat18dot5GeV = new TH1F("myMuMu2Massat18dot5GeV","myMuMu2Massat18dot5GeV",200,0,10.0);
  TH1F* myMuMu2MassatSideband = new TH1F("myMuMu2MassatSideband","myMuMu2MassatSideband",200,0,10.0);
  TH1F* myFourMuPtat18dot5GeV = new TH1F("myFourMuPtat18dot5GeV","myFourMuPtat18dot5GeV",50,0,50.0);
  TH1F* myFourMuPtatSideband = new TH1F("myFourMuPtatSideband","myFourMuPtatSideband",50,0,50.0);

  TH1F* myFourMuRapidityat18dot5GeV = new TH1F("myFourMuRapidityat18dot5GeV","myFourMuRapidityat18dot5GeV",32,-3.2,3.2);
  TH1F* myFourMuRapidityatSideband = new TH1F("myFourMuRapidityatSideband","myFourMuRapidityatSideband",32,-3.2,3.2);

  TH1F* myMu1Isoat18dot5GeV = new TH1F("myMu1Isoat18dot5GeV","myMu1Isoat18dot5GeV",50,0,5.0);
  TH1F* myMu2Isoat18dot5GeV = new TH1F("myMu2Isoat18dot5GeV","myMu2Isoat18dot5GeV",50,0,5.0);
  TH1F* myMu3Isoat18dot5GeV = new TH1F("myMu3Isoat18dot5GeV","myMu3Isoat18dot5GeV",50,0,5.0);
  TH1F* myMu4Isoat18dot5GeV = new TH1F("myMu4Isoat18dot5GeV","myMu4Isoat18dot5GeV",50,0,5.0);
 

  TH1F* myMu1Ptat18dot5GeV = new TH1F("myMu1Ptat18dot5GeV","myMu1Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu1PtatSideband = new TH1F("myMu1PtatSideband","myMu1PtatSideband",50,0,50.0);
  TH1F* myMu2Ptat18dot5GeV = new TH1F("myMu2Ptat18dot5GeV","myMu2Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu2PtatSideband = new TH1F("myMu2PtatSideband","myMu2PtatSideband",50,0,50.0);
  TH1F* myMu3Ptat18dot5GeV = new TH1F("myMu3Ptat18dot5GeV","myMu3Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu3PtatSideband = new TH1F("myMu3PtatSideband","myMu3PtatSideband",50,0,50.0);
  TH1F* myMu4Ptat18dot5GeV = new TH1F("myMu4Ptat18dot5GeV","myMu4Ptat18dot5GeV",50,0,50.0);
  TH1F* myMu4PtatSideband = new TH1F("myMu4PtatSideband","myMu4PtatSideband",50,0,50.0);
  TH1F* myMuMu1Ptat18dot5GeV = new TH1F("myMuMu1Ptat18dot5GeV","myMuMu1Ptat18dot5GeV",50,0,50.0);
  TH1F* myMuMu1PtatSideband = new TH1F("myMuMu1PtatSideband","myMuMu1PtatSideband",50,0,50.0);
  TH1F* myMuMu2Ptat18dot5GeV = new TH1F("myMuMu2Ptat18dot5GeV","myMuMu2Ptat18dot5GeV",50,0,50.0);
  TH1F* myMuMu2PtatSideband = new TH1F("myMuMu2PtatSideband","myMuMu2PtatSideband",50,0,50.0);
  TH1F* myFourMuFLSigat18dot5GeV = new TH1F("myFourMuFLSigat18dot5GeV","myFourMuFLSigat18dot5GeV",50,-25.0,25.0);
  TH1F* myFourMuFLSigatSideband = new TH1F("myFourMuFLSigatSideband","myFourMuFLSigatSideband",50,-25.0,25.0);  
  TH1F* myMuMu1Ctauat18dot5GeV = new TH1F("myMuMu1Ctauat18dot5GeV","myMuMu1Ctauat18dot5GeV",2000,-0.5,0.5);
  TH1F* myMuMu1CtauatSideband = new TH1F("myMuMu1CtauatSideband","myMuMu1CtauatSideband",2000,-0.5,0.5);
  TH1F* myMuMu2Ctauat18dot5GeV = new TH1F("myMuMu2Ctauat18dot5GeV","myMuMu2Ctauat18dot5GeV",2000,-0.5,0.5);
  TH1F* myMuMu2CtauatSideband = new TH1F("myMuMu2CtauatSideband","myMuMu2CtauatSideband",2000,-0.5,0.5);

  TH1F* myMuMuPairsDihedralat18dot5GeV = new TH1F("myMuMuPairsDihedralat18dot5GeV","myMuMuPairsDihedralat18dot5GeV",20,0,3.142);
  TH1F* myMuMuPairsDihedralatSideband = new TH1F("myMuMuPairsDihedralatSideband","myMuMuPairsDihedralatSideband",20,0,3.142);
  TH1F* myMuMuPairsHelicityat18dot5GeV = new TH1F("myMuMuPairsHelicityat18dot5GeV","myMuMuPairsHelicityat18dot5GeV",22,-1.1,1.1);
  TH1F* myMuMuPairsHelicityatSideband = new TH1F("myMuMuPairsHelicityatSideband","myMuMuPairsHelicityatSideband",22,-1.1,1.1);
  TH1F* myMupmumu1Helicityat18dot5GeV = new TH1F("myMupmumu1Helicityat18dot5GeV","myMupmumu1Helicityat18dot5GeV",22,-1.1,1.1);
  TH1F* myMupmumu1HelicityatSideband = new TH1F("myMupmumu1HelicityatSideband","myMupmumu1HelicityatSideband",22,-1.1,1.1);
  TH1F* myMupmumu2Helicityat18dot5GeV = new TH1F("myMupmumu2Helicityat18dot5GeV","myMupmumu2Helicityat18dot5GeV",22,-1.1,1.1);
  TH1F* myMupmumu2HelicityatSideband = new TH1F("myMupmumu2HelicityatSideband","myMupmumu2HelicityatSideband",22,-1.1,1.1);


  TH2F* myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV","myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");

 TH2F* myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV","myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");


  TH2F* myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV","myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");
 TH2F* myV1VsMuMuMassAfterVVmassanotherpairatSideband = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairatSideband","myV1VsMuMuMassAfterVVmassanotherpairatSideband",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassAfterVVmassanotherpairatSideband->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassAfterVVmassanotherpairatSideband->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");


  TH2F* myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull","myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull",5000,0,100.0, 5000, 0, 100.0);  
  myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
  myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");

  TH1F* myMuMu2Massat15dot7GeV = new TH1F("myMuMu2Massat15dot7GeV","myMuMu2Massat15dot7GeV",200,0,10.0);


 TH1F* myMu21Ptstartat18dot5GeV = new TH1F("myMu21Ptstartat18dot5GeV","myMu21Ptstartat18dot5GeV",50,0,50.0);
 TH1F* myMu21PtstartatSideband = new TH1F("myMu21PtstartatSideband","myMu21PtstartatSideband",50,0,50.0);
 TH1F* myMu22Ptstartat18dot5GeV = new TH1F("myMu22Ptstartat18dot5GeV","myMu22Ptstartat18dot5GeV",50,0,50.0);
 TH1F* myMu22PtstartatSideband = new TH1F("myMu22PtstartatSideband","myMu22PtstartatSideband",50,0,50.0);
 

  TH2F* myMuMu1ptVsMuMu2ptat18dot5GeV = new TH2F("myMuMu1ptVsMuMu2ptat18dot5GeV","myMuMu1ptVsMuMu2ptat18dot5GeV",20,0,20.0, 20, 0, 20.0);  
myMuMu1ptVsMuMu2ptat18dot5GeV->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{high} GeV");
myMuMu1ptVsMuMu2ptat18dot5GeV->GetYaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{low} GeV");
  TH2F* myMuMu1ptVsMuMu2ptatSideband = new TH2F("myMuMu1ptVsMuMu2ptatSideband","myMuMu1ptVsMuMu2ptatSideband",20,0,20.0, 20, 0, 20.0);  
  myMuMu1ptVsMuMu2ptatSideband->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{high} GeV");
  myMuMu1ptVsMuMu2ptatSideband->GetYaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{low} GeV");



  TH2F* myMu1EtaVsPtat18dot5GeV = new TH2F("myMu1EtaVsPtat18dot5GeV","myMu1EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
  TH2F* myMu2EtaVsPtat18dot5GeV = new TH2F("myMu2EtaVsPtat18dot5GeV","myMu2EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
  TH2F* myMu3EtaVsPtat18dot5GeV = new TH2F("myMu3EtaVsPtat18dot5GeV","myMu3EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
  TH2F* myMu4EtaVsPtat18dot5GeV = new TH2F("myMu4EtaVsPtat18dot5GeV","myMu4EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
 
  TH2F* myMu1EtaVsPtatSideband = new TH2F("myMu1EtaVsPtatSideband","myMu1EtaVsPtatSideband",60,-3,3, 300,0,30);
  TH2F* myMu2EtaVsPtatSideband = new TH2F("myMu2EtaVsPtatSideband","myMu2EtaVsPtatSideband",60,-3,3, 300,0,30);
  TH2F* myMu3EtaVsPtatSideband = new TH2F("myMu3EtaVsPtatSideband","myMu3EtaVsPtatSideband",60,-3,3, 300,0,30);
  TH2F* myMu4EtaVsPtatSideband = new TH2F("myMu4EtaVsPtatSideband","myMu4EtaVsPtatSideband",60,-3,3, 300,0,30);


  
  if (fChain == 0) return;
  
  Long64_t nentries = fChain->GetEntries();
  cout<<"Total entries="<<nentries<<endl;
  
  Long64_t nbytes = 0, nb = 0;
  //for (Long64_t jentry=0; jentry<2500;jentry++) {
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if(jentry%10000==0) cout<<"I am running "<<jentry<<"th entries out of "<<nentries<<" total entries"<<endl;

//    myoutfileEvtNum<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;

    bool TrigThreeMuon=false;
    bool TrigThreeMuonJpsi=false;
    bool TrigThreeMuonUpsi=false;

    bool TrigPsiprime=false;


    bool TrigTripleMu5=false;
    bool TrigDoubleMu5IsoMu5=false;
    bool TrigMu8=false;
    bool TrigDiMu7Upsi=false;
    bool TrigDiMu5Upsi=false;


    for(int i=0; i!=TrigRes->size(); ++i){ 
      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1 || TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1 )
	{
	  TrigThreeMuon=true;
	  //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
	}
      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
          TrigThreeMuonJpsi=true;
        }
      if(TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        { 
          TrigThreeMuonUpsi=true;
        }
      if( (TrigNames->at(i).find("HLT_Dimuon5_PsiPrime_")!=string::npos && TrigRes->at(i)==1)     
	  || (TrigNames->at(i).find("HLT_Dimuon7_PsiPrime_")!=string::npos && TrigRes->at(i)==1) 
	  )
        { 
         TrigPsiprime = true;
        }//if( (TrigNames->at(i).find("HLT_Dimuon5_PsiPrime_")!=string::npos && TrigRes->at(i)==1)  
      if( (TrigNames->at(i).find("HLT_TripleMu5_")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigTripleMu5 = true;
        }//if( (TrigNames->at(i).find("HLT_TripleMu5_")!=string::npos && TrigRes->at(i)==1) 
      if( (TrigNames->at(i).find("HLT_DoubleMu5_IsoMu5")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigDoubleMu5IsoMu5 = true;
        }//if( (TrigNames->at(i).find("HLT_DoubleMu5_IsoMu5")!=string::npos && TrigRes->at(i)==1) 
      if( (TrigNames->at(i).find("HLT_Mu8_v")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigMu8 = true;
        }//if( (TrigNames->at(i).find("HLT_Mu8_v")!=string::npos && TrigRes->at(i)==1)     
      if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigDiMu7Upsi = true;
        }//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)
     if( (TrigNames->at(i).find("HLT_Dimuon5_Upsilon_")!=string::npos && TrigRes->at(i)==1)     
	  )
        { 
	  TrigDiMu5Upsi = true;
	  //cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
        }//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)

    }


    for(int myi=0; myi<nmumuonly; myi++) {
      int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*mumuonlymu1Idx)[myi]] + (*muIsGoodLooseMuon)[ (*mumuonlymu2Idx)[myi]];
      int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*mumuonlymu1Idx)[myi]] + (*muIsGoodTightMuon)[ (*mumuonlymu2Idx)[myi]];
      TLorentzVector rawMu1p4vect, rawMu2p4vect;
      float raw_muPx = (*muPx)[ (*mumuonlymu1Idx)[myi] ];
      float raw_muPy = (*muPy)[ (*mumuonlymu1Idx)[myi] ];
      float raw_muPz = (*muPz)[ (*mumuonlymu1Idx)[myi] ];
      float raw_muM  =0.10565837; 
      rawMu1p4vect.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);    
      raw_muPx = (*muPx)[ (*mumuonlymu2Idx)[myi] ]; raw_muPy = (*muPy)[ (*mumuonlymu2Idx)[myi] ]; raw_muPz = (*muPz)[ (*mumuonlymu2Idx)[myi] ];
      rawMu2p4vect.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);    
 
      if(1
	 && (TrigThreeMuonJpsi || TrigThreeMuonUpsi)
	 && (*mumuonlyVtxCL)[myi]>0.005
	 && myNumGoodLooseMuon>=2
	 //&& myNumGoodTightMuon>=2
	 && fabs(rawMu1p4vect.Eta())<=2.4 && fabs(rawMu2p4vect.Eta())<=2.4
	 && rawMu1p4vect.Pt()>=2.0 && rawMu2p4vect.Pt()>=2.0
	 ) {
	myMuMuonlymass->Fill( (*mumuonlyMass)[myi] ); 
if(  (*mumuonlyMass)[myi]>9.2 &&  (*mumuonlyMass)[myi]<9.75 )
{
myMuMuOnlyIso->Fill( (*muIsoratio)[ (*mumuonlymu1Idx)[myi] ]   );
myMuMuOnlyIso->Fill( (*muIsoratio)[ (*mumuonlymu2Idx)[myi] ]   ); 
}

      } // if(1
    } // for(int myi=0; myi<nmumuonly; myi++) {
    
    //four muon signal
    for (int myFourMuIdx = 0; myFourMuIdx <nMyFourMuon; myFourMuIdx++) 
      {
	//assign the right information for the decay daughters
	TLorentzVector myFourMuonP4;
	myFourMuonP4.SetXYZM( (*MyFourMuonPx)[myFourMuIdx],(*MyFourMuonPy)[myFourMuIdx], (*MyFourMuonPz)[myFourMuIdx], (*MyFourMuonMass)[myFourMuIdx] );
	
	vector<int> fitMuCharge;
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu1Idx)[myFourMuIdx]] );
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu2Idx)[myFourMuIdx]] );
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu3Idx)[myFourMuIdx]] );
	fitMuCharge.push_back( (*muCharge)[(*MyFourMuonMu4Idx)[myFourMuIdx]] );

	vector<TLorentzVector> rawMup4vect, rawMuinFourMuFMp4vect;
	TLorentzVector Rawmu, RawmuinFourMuFM;
	float raw_muPx = (*muPx)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muPy = (*muPy)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muPz = (*muPz)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muM  =0.10565837; 
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);   
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMup4vect.push_back( Rawmu ); rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
	raw_muPx = (*muPx)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);  rawMup4vect.push_back( Rawmu );
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
	raw_muPx = (*muPx)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);  rawMup4vect.push_back( Rawmu );
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
	raw_muPx = (*muPx)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);  rawMup4vect.push_back( Rawmu );
	RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
	rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );

	vector<TLorentzVector> fitMup4vect;
	TLorentzVector Fitmu;
	//Muon From X Fit:        
	//Fit Muon 1
	float fit_muPx = (*MyFourMuonMu1Px)[myFourMuIdx];
	float fit_muPy = (*MyFourMuonMu1Py)[myFourMuIdx];
	float fit_muPz = (*MyFourMuonMu1Pz)[myFourMuIdx];
	float fit_muM  =0.10565837; 
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);    
	fitMup4vect.push_back( Fitmu );
	
	fit_muPx = (*MyFourMuonMu2Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu2Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu2Pz)[myFourMuIdx];
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back( Fitmu );
	fit_muPx = (*MyFourMuonMu3Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu3Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu3Pz)[myFourMuIdx];
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back( Fitmu );
	fit_muPx = (*MyFourMuonMu4Px)[myFourMuIdx]; fit_muPy = (*MyFourMuonMu4Py)[myFourMuIdx]; fit_muPz = (*MyFourMuonMu4Pz)[myFourMuIdx];
	Fitmu.SetXYZM( fit_muPx, fit_muPy,fit_muPz, fit_muM);  fitMup4vect.push_back( Fitmu );
	
	PairedMuonIdx myCombIdx[3];   
	//	double mymV[2]={9.46,3.0967};
	double mymV;   //3.096919 for jpsi, 3.686 for psi2s, 9.46 for Y(1s),10.02326,10.3552
	//code with simplest and safest way to make sure 
	if( mychannel==11) {  mymV=9.46; } 

 	myCombIdx[0].p11=0; myCombIdx[0].p12=1; myCombIdx[0].p21=2; myCombIdx[0].p22=3; 
	myCombIdx[1].p11=0; myCombIdx[1].p12=2; myCombIdx[1].p21=1; myCombIdx[1].p22=3; 
	myCombIdx[2].p11=0; myCombIdx[2].p12=3; myCombIdx[2].p21=1; myCombIdx[2].p22=2; 
	//find mu+mu+
// 	cout<<"before sort"<<endl;
// 	for(int i=0; i<3; i++) {
// 	  cout<<"i="<<i<<", p11,12,21,22 index and its charge="<<myCombIdx[i].p11<<"("<<fitMuCharge[ myCombIdx[i].p11 ]<<"),"<<myCombIdx[i].p12<<"("<<fitMuCharge[ myCombIdx[i].p12 ]<<"),"<<myCombIdx[i].p21<<"("<<fitMuCharge[ myCombIdx[i].p21 ]<<"),"<<myCombIdx[i].p22<<"("<<fitMuCharge[ myCombIdx[i].p22 ]<<"), p1 chg="<<(fitMuCharge[ myCombIdx[i].p11 ]+fitMuCharge[ myCombIdx[i].p12 ])<<", mass1,2="<<(fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<<","<<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()<<endl;	  
// 	}
	if( (fitMuCharge[ myCombIdx[1].p11 ]+fitMuCharge[ myCombIdx[1].p12 ])!=0 )  swap_two_paired_pair( myCombIdx[0],  myCombIdx[1] );
	if( (fitMuCharge[ myCombIdx[2].p11 ]+fitMuCharge[ myCombIdx[2].p12 ])!=0 )  swap_two_paired_pair( myCombIdx[0],  myCombIdx[2] );
	//now the  myCombIdx[0] is 2++ charged pair, but we want the first pair to be 2++
	if( (fitMuCharge[ myCombIdx[0].p11 ]+fitMuCharge[ myCombIdx[0].p12 ])!=2 )  swap_one_paired_pair( myCombIdx[0] );
	
	if(myordermode==1)  //sort to make m11>m12, m21>m22, m21>m11
	  {
	    for(int i=1; i<3; i++) {
	      if( (fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()  ) swap_one_paired_pair( myCombIdx[i] ); //for have first pair to have bigger mass
	    }	
	    //sort to have first pair to have bigger mass
	    if( ((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()) < ((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M() ) ) 
	      swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );	    
	  }
	else if(myordermode==2)
	  {
	    for(int i=1; i<3; i++) {
	      if( (fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()  ) swap_one_paired_pair( myCombIdx[i] ); //for have first pair to have bigger mass
	    }	
	//sort to make sure that |myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
	    if( fabs((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()-mymV )> fabs((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M()-mymV ) ) 
	      swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );
	  }	
        else if(myordermode==3)
          {
            for(int i=1; i<3; i++) {
              if( fabs((fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()-mymV) > fabs((fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()-mymV)  ) swap_one_paired_pair( myCombIdx[i] ); //for 
            }
        //sort to make sure that |myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
            if( fabs((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()-mymV )> fabs((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M()-mymV ) )
              swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );
          }


	//sort to make sure that the pi1 is always point to mu+
	//swap_one_pair( PairedMuonIdx & myp, int whichpair )
	//for(int myVi=0;myVi<2;myVi++) 
	  for(int i=1; i<3; i++) {
	    if( fitMuCharge[ myCombIdx[i].p11 ] !=1 ) swap_one_pair( myCombIdx[i], 1 );
	    if( fitMuCharge[ myCombIdx[i].p21 ] !=1 ) swap_one_pair( myCombIdx[i], 2 );
	  }
	//store information for sub-pair for each paied pair
	//the design is not so good, so we need more work here to match them
// 	cout<<" vtx prob, 01&23, 02&13, 03&12="<<(*MyJpsi1ChiProb_Mu12)[myFourMuIdx]<<","<<(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]<<",  "<<(*MyJpsi3ChiProb_Mu13)[myFourMuIdx]<<","<<(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]<<",  "<<(*MyJpsi5ChiProb_Mu14)[myFourMuIdx]<<","<<(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]<<endl;
// 	cout<<" ctau, 01&23, 02&13, 03&12="<<(*MyJpsi1CTau_Mu12)[myFourMuIdx]<<","<<(*MyJpsi2CTau_Mu34)[myFourMuIdx]<<",  "<<(*MyJpsi3CTau_Mu13)[myFourMuIdx]<<","<<(*MyJpsi4CTau_Mu24)[myFourMuIdx]<<",  "<<(*MyJpsi5CTau_Mu14)[myFourMuIdx]<<","<<(*MyJpsi6CTau_Mu23)[myFourMuIdx]<<endl;
// 	cout<<" ctauerr, 01&23, 02&13, 03&12="<<(*MyJpsi1CTauErr_Mu12)[myFourMuIdx]<<","<<(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]<<",  "<<(*MyJpsi3CTauErr_Mu13)[myFourMuIdx]<<","<<(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]<<",  "<<(*MyJpsi5CTauErr_Mu14)[myFourMuIdx]<<","<<(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]<<endl;

	float myMupMumVtxProb[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
	//myCombIdx[0], should be zero always 
	//
	myMupMumVtxProb[0][0]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[0][1]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumVtxProb[0][1]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[0][0]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumVtxProb[0][0]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[0][1]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumVtxProb[0][1]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[0][0]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumVtxProb[0][0]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[0][1]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumVtxProb[0][1]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[0][0]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	//
	//myCombIdx[1] 
	myMupMumVtxProb[1][0]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[1][1]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumVtxProb[1][1]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[1][0]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumVtxProb[1][0]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[1][1]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumVtxProb[1][1]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[1][0]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumVtxProb[1][0]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[1][1]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumVtxProb[1][1]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[1][0]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	//myCombIdx[2] 
	myMupMumVtxProb[2][0]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[2][1]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumVtxProb[2][1]=(*MyJpsi1ChiProb_Mu12)[myFourMuIdx];  myMupMumVtxProb[2][0]=(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumVtxProb[2][0]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[2][1]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumVtxProb[2][1]=(*MyJpsi3ChiProb_Mu13)[myFourMuIdx];  myMupMumVtxProb[2][0]=(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumVtxProb[2][0]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[2][1]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumVtxProb[2][1]=(*MyJpsi5ChiProb_Mu14)[myFourMuIdx];  myMupMumVtxProb[2][0]=(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]; }	
	//----------------------------------------------------------------------------------------------------------------------------

	
	float myMupMumCTau[3][2]; //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
	//myCombIdx[0], should be zero always 
	//
	myMupMumCTau[0][0]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[0][1]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumCTau[0][1]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[0][0]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTau[0][0]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[0][1]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTau[0][1]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[0][0]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTau[0][0]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[0][1]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTau[0][1]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[0][0]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	//
	//myCombIdx[1] 
	myMupMumCTau[1][0]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[1][1]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumCTau[1][1]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[1][0]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTau[1][0]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[1][1]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTau[1][1]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[1][0]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTau[1][0]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[1][1]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTau[1][1]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[1][0]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	//myCombIdx[2] 
	myMupMumCTau[2][0]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[2][1]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumCTau[2][1]=(*MyJpsi1CTau_Mu12)[myFourMuIdx];  myMupMumCTau[2][0]=(*MyJpsi2CTau_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTau[2][0]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[2][1]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTau[2][1]=(*MyJpsi3CTau_Mu13)[myFourMuIdx];  myMupMumCTau[2][0]=(*MyJpsi4CTau_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTau[2][0]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[2][1]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTau[2][1]=(*MyJpsi5CTau_Mu14)[myFourMuIdx];  myMupMumCTau[2][0]=(*MyJpsi6CTau_Mu23)[myFourMuIdx]; }	
	//----------------------------------------------------------------------------------------------------------------------------
	

	float myMupMumCTauErr[3][2];
	//myCombIdx[0], should be zero always 
	//
	myMupMumCTauErr[0][0]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[0][1]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
	  { myMupMumCTauErr[0][1]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[0][0]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTauErr[0][0]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[0][1]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTauErr[0][1]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[0][0]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMupMumCTauErr[0][0]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[0][1]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMupMumCTauErr[0][1]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[0][0]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	//
	//myCombIdx[1] 
	myMupMumCTauErr[1][0]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[1][1]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
	  { myMupMumCTauErr[1][1]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[1][0]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTauErr[1][0]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[1][1]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTauErr[1][1]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[1][0]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMupMumCTauErr[1][0]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[1][1]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMupMumCTauErr[1][1]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[1][0]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	//myCombIdx[2] 
	myMupMumCTauErr[2][0]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[2][1]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; 	
	if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
	  { myMupMumCTauErr[2][1]=(*MyJpsi1CTauErr_Mu12)[myFourMuIdx];  myMupMumCTauErr[2][0]=(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]; }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTauErr[2][0]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[2][1]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTauErr[2][1]=(*MyJpsi3CTauErr_Mu13)[myFourMuIdx];  myMupMumCTauErr[2][0]=(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]; }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMupMumCTauErr[2][0]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[2][1]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMupMumCTauErr[2][1]=(*MyJpsi5CTauErr_Mu14)[myFourMuIdx];  myMupMumCTauErr[2][0]=(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]; }	
	//----------------------------------------------------------------------------------------------------------------------------
	

	// added new by YIK
	//Two dimuon vertex distancexy
	float myMumu1Mumu2DisXY[3];
	//myCombIdx[0] 
	myMumu1Mumu2DisXY[0]=(*My1234JpsiDisXY)[myFourMuIdx]; 
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisXY[0]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	//
	//myCombIdx[1] 
	myMumu1Mumu2DisXY[1]=(*My1234JpsiDisXY)[myFourMuIdx]; 
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisXY[1]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	//myCombIdx[2] 
	myMumu1Mumu2DisXY[2]=(*My1234JpsiDisXY)[myFourMuIdx]; 
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1324JpsiDisXY)[myFourMuIdx];  }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisXY[2]=(*My1423JpsiDisXY)[myFourMuIdx];  }
	//----------------------------------------------------------------------------------------------------------------------------
// 	for(int i=0; i<3; i++) {
// 	  if(i==2 && myMumu1Mumu2DisXY[i]<0)
// 	    cout<<"i="<<i<<", myMumu1Mumu2DisXY="<<myMumu1Mumu2DisXY[i]<<",1234="<<(*My1234JpsiDisXY)[myFourMuIdx]<<",1324="<<(*My1324JpsiDisXY)[myFourMuIdx]<<",1423="<<(*My1423JpsiDisXY)[myFourMuIdx]<<endl;
// 	}
// 	//cout<<endl;
	//Two dimuon vertex distanceZ
	float myMumu1Mumu2DisZ[3];
	//myCombIdx[0] 
	myMumu1Mumu2DisZ[0]=(*My1234JpsiDisZ)[myFourMuIdx]; 
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	//
	if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
	  { myMumu1Mumu2DisZ[0]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	//
	//myCombIdx[1] 
	myMumu1Mumu2DisZ[1]=(*My1234JpsiDisZ)[myFourMuIdx]; 
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	//
	if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
	  { myMumu1Mumu2DisZ[1]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	//myCombIdx[2] 
	myMumu1Mumu2DisZ[2]=(*My1234JpsiDisZ)[myFourMuIdx]; 
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1324JpsiDisZ)[myFourMuIdx];  }
	//
	if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
	  { myMumu1Mumu2DisZ[2]=(*My1423JpsiDisZ)[myFourMuIdx];  }
	//----------------------------------------------------------------------------------------------------------------------------
// 	for(int i=0; i<3; i++) {
// 	  if(i==2 && myMumu1Mumu2DisZ[i]<0)
// 	    cout<<"same i="<<i<<", myMumu1Mumu2DisZ="<<myMumu1Mumu2DisZ[i]<<",1234="<<(*My1234JpsiDisZ)[myFourMuIdx]<<",1324="<<(*My1324JpsiDisZ)[myFourMuIdx]<<",1423="<<(*My1423JpsiDisZ)[myFourMuIdx]<<", vtx  prob="<<myMupMumVtxProb[i][0]<<endl;
// 	}
// 	//cout<<endl;
	//added new end



	//muon ID 
	int isTightMuon[4], isLooseMuon[4], myMuIso[4];
	isLooseMuon[0]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	isLooseMuon[2]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
	isTightMuon[0]=(*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isTightMuon[1]=(*muIsGoodTightMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	isTightMuon[2]=(*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isTightMuon[3]=(*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];

	//myMuIso[0]= (*muIsoratio)[ (*MyFourMuonMu1Idx)[myFourMuIdx]]; myMuIso[1]= (*muIsoratio)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	//myMuIso[2]= (*muIsoratio)[ (*MyFourMuonMu3Idx)[myFourMuIdx]]; myMuIso[3]= (*muIsoratio)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];

// //  	cout<<"after sort"<<endl;
//   	for(int i=0; i<3; i++) {
//   	  cout<<"i="<<i<<", p11,12,21,22 index and its charge="<<myCombIdx[i].p11<<"("<<fitMuCharge[ myCombIdx[i].p11 ]<<"),"<<myCombIdx[i].p12<<"("<<fitMuCharge[ myCombIdx[i].p12 ]<<"),"<<myCombIdx[i].p21<<"("<<fitMuCharge[ myCombIdx[i].p21 ]<<"),"<<myCombIdx[i].p22<<"("<<fitMuCharge[ myCombIdx[i].p22 ]<<"), p1 chg="<<(fitMuCharge[ myCombIdx[i].p11 ]+fitMuCharge[ myCombIdx[i].p12 ])<<", mass1,2="<<(fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<<","<<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()<<", vtx  prob="<<myMupMumVtxProb[i][0]<<", "<<myMupMumVtxProb[i][1]<<", ctau="<<myMupMumCTau[i][0]<<", "<<myMupMumCTau[i][1]<<", ctau err="<<myMupMumCTauErr[i][0]<<", "<<myMupMumCTauErr[i][1]<<",myMumu1Mumu2DisXY="<<myMumu1Mumu2DisXY[i]<<",1234="<<(*My1234JpsiDisXY)[myFourMuIdx]<<",1324="<<(*My1324JpsiDisXY)[myFourMuIdx]<<",1423="<<(*My1423JpsiDisXY)[myFourMuIdx]<<endl;
//   	}

	//	float myfourmuonmass=(*MyFourMuonMass)[myFourMuIdx];
	float myfourmuonmass= (fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).M();
	
	//int muonQual[] = {1,3,4,12};   
	// (N.B. "All" condition not saved => muQual  must have 1 for GlobalMu (1), TrackerMu(3). TMArbitrated(4), TMLastStationLoose (7)
       int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
       int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
       //int myGlobalMuNum=(int)(bool)( ((*muQual)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) ) + (int)(bool)( ((*muQual)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) ) + (int)(bool)( ((*muQual)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) ) + (int)(bool)( ((*muQual)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) );

	//bool matchUpsiTrig=(*muIsUpsTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] && (*muIsUpsTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] && (*muIsUpsTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] &&(*muIsUpsTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
	//bool matchJpsiTrig=(*muIsJpsiTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] && (*muIsJpsiTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] && (*muIsJpsiTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] &&(*muIsJpsiTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
		
	//int matchUpsiTrig=(int)(*muIsUpsTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] + (int) (*muIsUpsTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] + (int)(*muIsUpsTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] + (int)(*muIsUpsTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
	//int matchJpsiTrig=(int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] + (int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] + (int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] + (int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
	
	TLorentzVector myRaw4Mup4=rawMup4vect[0]+rawMup4vect[1]+rawMup4vect[2]+rawMup4vect[3];
	float myetacut=2.4;   //1.6, there is a bump at 31 GeV for Y(1S) mumu, default 2.4
	float minMuPt=2.0;  //2.0--default 1.5;2,5;3.0;3.5;  2.2
		
	if(1
	   && (*MyFourMuonVtxCL)[myFourMuIdx]>=0.05   //	   
	   //MuOnia data
	   	   
	   && ( TrigThreeMuonJpsi || TrigThreeMuonUpsi )    //for three muon trigger, default trigger, remove it for Higgs test
	   ////&& TrigThreeMuonUpsi

	   //DoubleMu data
	   /*
	   && !( TrigThreeMuonJpsi || TrigThreeMuonUpsi )
	   && TrigTripleMu5
	   */

	   //&& TrigThreeMuonUpsi
	   //&& TrigDiMu7Upsi
	   //&& TrigDiMu5Upsi
	   //&& (TrigTripleMu5 || TrigDoubleMu5IsoMu5)    //for double muon dataset
	   //&& TrigDoubleMu5IsoMu5
	   //&& TrigTripleMu5
	   //&& TrigMu8
	   //&& (matchUpsiTrig>=3 || matchJpsiTrig>=3)

	   && fabs(rawMup4vect[0].Eta())<=myetacut && fabs(rawMup4vect[1].Eta())<=myetacut
	   && fabs(rawMup4vect[2].Eta())<=myetacut && fabs(rawMup4vect[3].Eta())<=myetacut

	   /*
	   //test Stefan's suggestion for different eta, comment out for default
	   //in the transition region from barrel to forward
	   && 
	   !( (fabs(rawMup4vect[0].Eta()) >=1.0 &&  fabs(rawMup4vect[0].Eta())<=1.4)
	     || (fabs(rawMup4vect[1].Eta()) >=1.0 &&  fabs(rawMup4vect[1].Eta())<=1.4)
	     || (fabs(rawMup4vect[2].Eta()) >=1.0 &&  fabs(rawMup4vect[2].Eta())<=1.4)
	     || (fabs(rawMup4vect[3].Eta()) >=1.0 &&  fabs(rawMup4vect[3].Eta())<=1.4)
	     )
	   */

	   )
	  {	    
	    
	    int NumDup=0;   //we have two pairs, but only fill one time if at least one pair satisfy it
	    for(int mypidx=1; mypidx<3; mypidx++) //loop over the two combinations with zero chg
	      {
		int muIdxp11, muIdxp12, muIdxp21, muIdxp22;
		muIdxp11=myCombIdx[mypidx].p11; muIdxp12=myCombIdx[mypidx].p12; muIdxp21=myCombIdx[mypidx].p21; muIdxp22=myCombIdx[mypidx].p22;
		//this part is to investigate the another combination--to see if there are anything strange.
		int myanotherpidx; 
		if( mypidx==1 ) {myanotherpidx=2;}  if( mypidx==2 ) {myanotherpidx=1;} 
		int muanotherIdxp11, muanotherIdxp12, muanotherIdxp21, muanotherIdxp22;
		muanotherIdxp11=myCombIdx[myanotherpidx].p11; muanotherIdxp12=myCombIdx[myanotherpidx].p12; 
		muanotherIdxp21=myCombIdx[myanotherpidx].p21; muanotherIdxp22=myCombIdx[myanotherpidx].p22;
		//end this part is to investigate the another combination--to see if there are anything strange.
		
		//for this selected pair
		TLorentzVector mymumu1p4=rawMup4vect[ muIdxp11 ]+ rawMup4vect[ muIdxp12 ];
		TLorentzVector mymumu2p4=rawMup4vect[ muIdxp21 ]+ rawMup4vect[ muIdxp22 ];
		double myrap1=fabs(0.5*log( (mymumu1p4.E() + mymumu1p4.Pz())/(mymumu1p4.E() - mymumu1p4.Pz()) ) );
		double myrap2=fabs(0.5*log( (mymumu2p4.E() + mymumu2p4.Pz())/(mymumu2p4.E() - mymumu2p4.Pz()) ) );
		//obtained from data
		double myY1sResp1=0.0572+0.03602*myrap1;
		double myY2sResp1=0.05745+0.03926*myrap1;   
		double myJpsiResp1=0.01598+0.01562*myrap1;
		double myPsi2sResp1=0.01849+0.01906*myrap1;
		double myPhiResp1=0.006984+0.004505*myrap1+0.00426;  //0.00426 is its intrisince width
		double myOmegaResp1=0.006366+0.003277*myrap1+0.00849;  //+0.00849 is for its intrisic width
		
		double myY1sResp2=0.0572+0.03602*myrap2;
		double myY2sResp2=0.05745+0.03926*myrap2;   
		double myJpsiResp2=0.01598+0.01562*myrap2;
		double myPsi2sResp2=0.01849+0.01906*myrap2;
		double myPhiResp2=0.006984+0.004505*myrap2+0.00426;   //0.00426 is its intrisince width
		double myOmegaResp2=0.006366+0.003277*myrap2+0.00849;  //+0.00849 is for its intrisic width
		
		//mass resolution for another pair
		TLorentzVector myanothermumu1p4=rawMup4vect[ muanotherIdxp11 ]+ rawMup4vect[ muanotherIdxp12 ];
		TLorentzVector myanothermumu2p4=rawMup4vect[ muanotherIdxp21 ]+ rawMup4vect[ muanotherIdxp22 ];
		double myanotherrap1=fabs(0.5*log( (myanothermumu1p4.E() + myanothermumu1p4.Pz())/(myanothermumu1p4.E() - myanothermumu1p4.Pz()) ) );
		double myanotherrap2=fabs(0.5*log( (myanothermumu2p4.E() + myanothermumu2p4.Pz())/(myanothermumu2p4.E() - myanothermumu2p4.Pz()) ) );
		//obtained from data
		double myanotherY1sResp1=0.0572+0.03602*myanotherrap1;
		double myanotherY2sResp1=0.05745+0.03926*myanotherrap1;   
		double myanotherJpsiResp1=0.01598+0.01562*myanotherrap1;
		double myanotherPsi2sResp1=0.01849+0.01906*myanotherrap1;
		double myanotherPhiResp1=0.006984+0.004505*myanotherrap1+0.00426;  //0.00426 is its intrisince width
		double myanotherOmegaResp1=0.006366+0.003277*myanotherrap1+0.00849;  //+0.00849 is for its intrisic width
		
		double myanotherY1sResp2=0.0572+0.03602*myanotherrap2;
		double myanotherY2sResp2=0.05745+0.03926*myanotherrap2;   
		double myanotherJpsiResp2=0.01598+0.01562*myanotherrap2;
		double myanotherPsi2sResp2=0.01849+0.01906*myanotherrap2;
		double myanotherPhiResp2=0.006984+0.004505*myanotherrap2+0.00426;  //0.00426 is its intrisince width
		double myanotherOmegaResp2=0.006366+0.003277*myanotherrap2+0.00849;  //+0.00849 is for its intrisic width
		
		//cout<<"myY1sResp1="<<myY1sResp1<<", myY1sResp2="<<myY1sResp2<<", myanotherY1sResp1="<<myanotherY1sResp1<<", myanotherY1sResp2="<<myanotherY1sResp2<<endl;
		//cout<<"myY1sResp1="<<myJpsiResp1<<", myJpsiResp2="<<myJpsiResp2<<", myanotherJpsiResp1="<<myanotherJpsiResp1<<", myanotherJpsiResp2="<<myanotherJpsiResp2<<endl;
				
		if(1
		   && myMupMumVtxProb[mypidx][0]>=0.005 && myMupMumVtxProb[mypidx][1]>=0.005
		   && isLooseMuon[ muIdxp11 ] &&  isLooseMuon[ muIdxp12 ] //check tomorrow
		   && isLooseMuon[ muIdxp21 ] &&  isLooseMuon[ muIdxp22 ] //check tomorrow
		   && rawMup4vect[ muIdxp11 ].Pt()>=minMuPt && rawMup4vect[ muIdxp12 ].Pt()>=minMuPt
		   && rawMup4vect[ muIdxp21 ].Pt()>=minMuPt && rawMup4vect[ muIdxp22 ].Pt()>=minMuPt
		   		   
		   //&& (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt()>=3.0    //2.5
		   //&& (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt()>=0.0   //2.5
		   		   
		   //&& (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ] ).Pt()>=20.0

//simulate ATLAS trigger
//&& (rawMup4vect[ muIdxp11 ]).Pt()>=4.0
//&& (rawMup4vect[ muIdxp12 ]).Pt()>=4.0		   

		   //simulate doublemu5 trigger
		   //&& (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt()>=5.0
		   //simulate single mu trigger
		   //&& ( rawMup4vect[ muIdxp11 ].Pt()>=10.0 || rawMup4vect[ muIdxp12 ].Pt()>=10.0 || rawMup4vect[ muIdxp21 ].Pt()>=10.0 || rawMup4vect[ muIdxp22 ].Pt()>10.0 ) 
		   
		   ) {
		  if( mypidx==1 ) {
		    myMuMumassforV1highpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()  );
		    myMuMumassformumuhighpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
		    myV1VsMuMuMassBeforeVVmasshighpair->Fill((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
		    //check if muon pt is sorted.  Yeah, it is.
		    //cout<<"rawMup4vect[0] pt="<<rawMup4vect[0].Pt()<<", (rawMup4vect[1]="<<rawMup4vect[1].Pt()<<", rawMup4vect[2].Pt()="<<rawMup4vect[2].Pt()<<", rawMup4vect[3].Pt()="<<rawMup4vect[3].Pt()<<endl;
		    
		  }
		  if( mypidx==2 ) {
		    myMuMumassforV1lowpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );		      
		    myMuMumassformumulowpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
		    myV1VsMuMuMassBeforeVVmasslowpair->Fill((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
		  }
		  //apply mass cut 
		  float mynsigma=3.0;		  
		  bool myVVmasscut;
		  if( mychannel==11 ) {  //Y(1S) mumu
		    myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
                    //myVVmasscut= (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() < (mymV - mynsigma*myY1sResp1) 
                      //           && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > (mymV - 2*mynsigma*myY1sResp1)
                                  //to check background event to see if we can have a bck shape.
 		      && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myY1sResp2 )
		      //&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= 9.0  //4; 5, 7; 
		      && myNumGoodTightMuon>=2; //if one of the V is Upsilon
		  }

		  //define low/high Y(1S) sidebands
		  float lowsidel=8.6, lowsideh=9.2, highsidel=9.75, highsideh=9.85;
		  if(mychannel==11) {
		    if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >lowsidel 
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() <lowsideh
			 //&& myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
			 //&&(fitMup4vect[muIdxp21]+fitMup4vect[muIdxp22]).M()<=(mymV-mynsigma*myY1sResp2), assumed it is ordered 
			 ){
		      myMuMuMuMumassV1mumubelowV1LowSide->Fill( myfourmuonmass );
		      //shift the band to Y(1s)
		      TLorentzVector mylowsidedimuonp4=(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]);
		      TLorentzVector myYstardimuonp4=(fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]);		      
		      float mytmpmass=mylowsidedimuonp4.M(); mytmpmass=mytmpmass+ (9.46-(lowsidel+lowsideh)/2);
		      float mynewE=mylowsidedimuonp4.Vect().Mag2() + mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE );  mylowsidedimuonp4.SetE( mynewE  );
		      mytmpmass=myYstardimuonp4.M()+(9.46-mylowsidedimuonp4.M());
		      mynewE=myYstardimuonp4.Vect().Mag2()+ mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE ); myYstardimuonp4.SetE( mynewE  );
		      myMuMuMuMumassV1mumubelowV1LowSideShift->Fill( (mylowsidedimuonp4+myYstardimuonp4).M()  );		      
		    }//if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
		    if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > highsidel
			 && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() < highsideh
			 //&& myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
			 //&&(fitMup4vect[muIdxp21]+fitMup4vect[muIdxp22]).M()<=(mymV-mynsigma*myY1sResp2), assumed it is ordered 
			 ){		      
		      myMuMuMuMumassV1mumubelowV1HighSide->Fill( myfourmuonmass );
		      //shift the band to Y(1s)
		      TLorentzVector mylowsidedimuonp4=(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]);
		      TLorentzVector myYstardimuonp4=(fitMup4vect[ muIdxp21 ]+fitMup4vect[ muIdxp22 ]);		      
		      float mytmpmass=mylowsidedimuonp4.M(); mytmpmass=mytmpmass+ (9.46-(highsidel+highsideh)/2);
		      float mynewE=mylowsidedimuonp4.Vect().Mag2() + mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE );  mylowsidedimuonp4.SetE( mynewE  );
		      mytmpmass=myYstardimuonp4.M()+(9.46-mylowsidedimuonp4.M());
		      mynewE=myYstardimuonp4.Vect().Mag2()+ mytmpmass*mytmpmass; 
		      mynewE=sqrt(mynewE ); myYstardimuonp4.SetE( mynewE  );
		      myMuMuMuMumassV1mumubelowV1HighSideShift->Fill(  (mylowsidedimuonp4+myYstardimuonp4).M()  );
		    }//if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
		  }
		  

		  if(1
		     && myVVmasscut		     
		     ) 
		    {
		      if(NumDup<1) {			
			//dihedral angle
			TLorentzVector myfourmuonp4=fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3];
			TLorentzVector fitMu11bosstedp4, fitMu12bosstedp4, fitMu21bosstedp4, fitMu22bosstedp4;
			fitMu11bosstedp4=fitMup4vect[ muIdxp11 ]; fitMu12bosstedp4=fitMup4vect[ muIdxp12 ];
			fitMu21bosstedp4=fitMup4vect[ muIdxp21 ]; fitMu22bosstedp4=fitMup4vect[ muIdxp22 ];
			fitMu11bosstedp4.Boost( -myfourmuonp4.BoostVector() ); fitMu12bosstedp4.Boost( -myfourmuonp4.BoostVector() );
			fitMu21bosstedp4.Boost( -myfourmuonp4.BoostVector() ); fitMu22bosstedp4.Boost( -myfourmuonp4.BoostVector() );
			TVector3 OrthMupMum1=fitMu11bosstedp4.Vect().Cross( fitMu12bosstedp4.Vect()  );
			TVector3 OrthMupMum2=fitMu21bosstedp4.Vect().Cross( fitMu22bosstedp4.Vect()  );
			float myDihedral=  TMath::ACos(OrthMupMum1.Unit().Dot(OrthMupMum2.Unit() ) );
			//cout<<"myDihedral="<<myDihedral<<endl;
			//helicity angle of two mumu pairs			  
			TLorentzVector mymupmum1p4=fitMu11bosstedp4+ fitMu12bosstedp4;
			TLorentzVector mymupmum1p4boosted=fitMu11bosstedp4+ fitMu12bosstedp4;
			//mymupmum1p4boosted.Boost( -myfourmuonp4.BoostVector() );
			float mymupmum1CosHelicity= cos( mymupmum1p4boosted.Vect().Angle( myfourmuonp4.Vect() ) );
			//cout<<"mymupmum1CosHelicity="<<mymupmum1CosHelicity<<endl;
			//helicity of mu+mu- for each pair
			TLorentzVector mymupmum2p4=fitMu21bosstedp4+fitMu22bosstedp4;
			//mymupmum2p4.Boost( -myfourmuonp4.BoostVector() );
			TLorentzVector mymupmum1mupboosted; 
			mymupmum1mupboosted=fitMu11bosstedp4; 
			TLorentzVector mymupmum2mupboosted; 
			mymupmum2mupboosted=fitMu21bosstedp4; 
			mymupmum1mupboosted.Boost( -mymupmum1p4.BoostVector() );
			mymupmum2mupboosted.Boost( -mymupmum2p4.BoostVector() );
			float mymupmum1mupCosHelicity= cos( mymupmum1mupboosted.Vect().Angle( mymupmum1p4.Vect() ) );
			float mymupmum2mupCosHelicity= cos( mymupmum2mupboosted.Vect().Angle( mymupmum2p4.Vect() ) );
			
//    myoutfileEvtNum<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;

			myoutfileevtmix<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Px()<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Py()<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Pz()<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Px()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Py()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Pz()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<fitMup4vect[ muIdxp11 ].Px()<<" "<<fitMup4vect[ muIdxp11 ].Py()<<" "<<fitMup4vect[ muIdxp11 ].Pz()<<" "<<fitMup4vect[ muIdxp12 ].Px()<<" "<<fitMup4vect[ muIdxp12 ].Py()<<" "<<fitMup4vect[ muIdxp12 ].Pz()<<" "<<fitMup4vect[ muIdxp21 ].Px()<<" "<<fitMup4vect[ muIdxp21 ].Py()<<" "<<fitMup4vect[ muIdxp21 ].Pz()<<" "<<fitMup4vect[ muIdxp22 ].Px()<<" "<<fitMup4vect[ muIdxp22 ].Py()<<" "<<fitMup4vect[ muIdxp22 ].Pz()<<" "<<endl;

			myoutfilesignal<<myfourmuonmass<<" "<<(rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt()<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<(rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt()<<" "<<rawMup4vect[ muIdxp11 ].Pt()<<" "<<rawMup4vect[ muIdxp12 ].Pt()<<" "<<rawMup4vect[ muIdxp21 ].Pt()<<" "<<rawMup4vect[ muIdxp22 ].Pt()<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ] ).M()<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp22 ] ).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ] + fitMup4vect[ muIdxp11 ] ).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ] + fitMup4vect[ muIdxp12 ] ).M()<<" "<<(*MyFourMuonVtxCL)[myFourMuIdx]<<" "<<myMumu1Mumu2DisXY[mypidx]<<" "<<myMumu1Mumu2DisZ[mypidx]<<" "<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;
			
			myMuMuMuMumassV1mumubelowV1->Fill( myfourmuonmass );
			float mytmpdp=fabs((*muPx)[ myCombIdx[0].p11 ]-(*muPx)[ myCombIdx[0].p12 ])+fabs((*muPy)[ myCombIdx[0].p11 ]-(*muPy)[ myCombIdx[0].p12 ])+fabs((*muPz)[ myCombIdx[0].p11 ]-(*muPz)[ myCombIdx[0].p12 ]);
			//cout<<"hello="<<(*muPx)[ myCombIdx[0].p11 ]<<","<<(*muPx)[ myCombIdx[0].p12 ]<<","<<mytmpdp<<endl;
			myMuPPDeltapxpypz->Fill( mytmpdp );
			mytmpdp=fabs((*muPx)[ myCombIdx[0].p21 ]-(*muPx)[ myCombIdx[0].p22 ])+fabs((*muPy)[ myCombIdx[0].p21 ]-(*muPy)[ myCombIdx[0].p22 ])+fabs((*muPz)[ myCombIdx[0].p21 ]-(*muPz)[ myCombIdx[0].p22 ]);
			myMuMMDeltapxpypz->Fill( mytmpdp );
			float deltaPhi1=rawMup4vect[ muIdxp12 ].Phi()-rawMup4vect[ muIdxp11 ].Phi();
			float deltaPhi2=rawMup4vect[ muIdxp22 ].Phi()-rawMup4vect[ muIdxp21 ].Phi();
			if(deltaPhi1 > TMath::Pi()) deltaPhi1 -= 2.*TMath::Pi();
			else if(deltaPhi1 < -TMath::Pi()) deltaPhi1 += 2.*TMath::Pi();
			if(deltaPhi2 > TMath::Pi()) deltaPhi2 -= 2.*TMath::Pi();
			else if(deltaPhi2 < -TMath::Pi()) deltaPhi2 += 2.*TMath::Pi();

			if( deltaPhi1<0 && deltaPhi2<0 ) myMuMuMuMumassV1mumubelowV1cowboyVscowboy->Fill( myfourmuonmass );
			if( deltaPhi1<0 && deltaPhi2>0 ) myMuMuMuMumassV1mumubelowV1cowboyVsseagull->Fill( myfourmuonmass );
			if( deltaPhi1>0 && deltaPhi2<0 ) myMuMuMuMumassV1mumubelowV1seagullVscowboy->Fill( myfourmuonmass );
			if( deltaPhi1>0 && deltaPhi2>0 ) {
			  myMuMuMuMumassV1mumubelowV1seagullVsseagull->Fill( myfourmuonmass );
			  if(myfourmuonmass>15.2 && myfourmuonmass<16.2) {
			    myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->Fill( (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() ); 
			    myMuMu2Massat15dot7GeV->Fill(  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
			    //myoutfileEvtNum<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;
			  }
			}
			//cout<< deltaPhi1<<","<<deltaPhi2<<endl; 
			
			
			if( 
			   (*muIsoratio)[ muIdxp11 ]<0.1 && (*muIsoratio)[ muIdxp12 ]<0.1
			   )
			  {
			    myMuMuMuMumassV1mumuWithVIso0dot1belowV1->Fill( myfourmuonmass );
			  }

			if( 
			   (*muIsoratio)[ muIdxp11 ]<0.2 && (*muIsoratio)[ muIdxp12 ]<0.2
			   )
			  {
			    myMuMuMuMumassV1mumuWithVIso0dot2belowV1->Fill( myfourmuonmass );
			  }
			if( 
			   (*muIsoratio)[ muIdxp11 ]<0.5 && (*muIsoratio)[ muIdxp12 ]<0.5
			   )
			  {
			    myMuMuMuMumassV1mumuWithVIso0dot5belowV1->Fill( myfourmuonmass );
			  }

			if( 
			   (*muIsoratio)[  (*MyFourMuonMu1Idx)[myFourMuIdx] ]<0.1 
			   )
			  {
			    myMuMuMuMumassV1highestmuWithVIso0dot1belowV1->Fill( myfourmuonmass );
			  }
			if( 
			   (*muIsoratio)[  (*MyFourMuonMu1Idx)[myFourMuIdx] ]<0.2 
			   )
			  {
			    myMuMuMuMumassV1highestmuWithVIso0dot2belowV1->Fill( myfourmuonmass );
			  }
			if( 
			   (*muIsoratio)[  (*MyFourMuonMu1Idx)[myFourMuIdx] ]<0.5 
			   )
			  {
			    myMuMuMuMumassV1highestmuWithVIso0dot5belowV1->Fill( myfourmuonmass );
			  }



			myMuMuMuMumassDiffV1mumubelowV1->Fill( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV  );
						
			myV1VsMuMuMassAfterVVmassanotherpair->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() ); 
			

			if( myfourmuonmass>=18.0 && myfourmuonmass<=19.0 ) {
			  
			  myoutfileEvtNum<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myfourmuonmass<<", "<<rawMup4vect[ muIdxp11 ].Pt()<<" "<<rawMup4vect[ muIdxp11 ].Eta()<<" "<<rawMup4vect[ muIdxp11 ].Phi()<<", "<<rawMup4vect[ muIdxp12 ].Pt()<<" "<<rawMup4vect[ muIdxp12 ].Eta()<<" "<<rawMup4vect[ muIdxp12 ].Phi()<<", "<<rawMup4vect[ muIdxp21 ].Pt()<<" "<<rawMup4vect[ muIdxp21 ].Eta()<<" "<<rawMup4vect[ muIdxp21 ].Phi()<<", "<<rawMup4vect[ muIdxp22 ].Pt()<<" "<<rawMup4vect[ muIdxp22 ].Eta()<<" "<<rawMup4vect[ muIdxp22 ].Phi()<<endl;
			  

			  myMu1Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] );
			  myMu2Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] );
			  myMu3Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] );
			  myMu4Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu4Idx)[myFourMuIdx]] );
			  


			  myMuMu2Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
			  myFourMuPtat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
			  myFourMuRapidityat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

			  myMu1EtaVsPtat18dot5GeV->Fill(  rawMup4vect[0].Eta(), rawMup4vect[0].Pt() ); 
			  myMu2EtaVsPtat18dot5GeV->Fill(  rawMup4vect[1].Eta(), rawMup4vect[1].Pt() ); 
			  myMu3EtaVsPtat18dot5GeV->Fill(  rawMup4vect[2].Eta(), rawMup4vect[2].Pt() ); 
			  myMu4EtaVsPtat18dot5GeV->Fill(  rawMup4vect[3].Eta(), rawMup4vect[3].Pt() );
			  
			  myMuMu1ptVsMuMu2ptat18dot5GeV->Fill(  (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt(), (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
			  
			  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

			  if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 ) {
			    myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
			  }
			  
			  myMu1Ptat18dot5GeV->Fill( rawMup4vect[0].Pt() );
			  myMu2Ptat18dot5GeV->Fill( rawMup4vect[1].Pt() );
			  myMu3Ptat18dot5GeV->Fill( rawMup4vect[2].Pt() );
			  myMu4Ptat18dot5GeV->Fill( rawMup4vect[3].Pt() );

 			  myMu21Ptstartat18dot5GeV->Fill( rawMuinFourMuFMp4vect[muIdxp21].Pt() ); 
 			  myMu22Ptstartat18dot5GeV->Fill( rawMuinFourMuFMp4vect[muIdxp22].Pt() ); 

			  myMuMu1Ptat18dot5GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Pt() );
			  myMuMu2Ptat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Pt() );
			  myMuMuPairsDihedralat18dot5GeV->Fill( myDihedral );
			  myMuMuPairsHelicityat18dot5GeV->Fill( mymupmum1CosHelicity );
			  myMupmumu1Helicityat18dot5GeV->Fill( mymupmum1mupCosHelicity );
			  myMupmumu2Helicityat18dot5GeV->Fill( mymupmum2mupCosHelicity );
			  myFourMuFLSigat18dot5GeV->Fill( (*MyFourMuonFLSig)[myFourMuIdx] );
			  myMuMu1Ctauat18dot5GeV->Fill( myMupMumCTau[mypidx][0] );    //there is a problem here, could be mixed between 1 &2, 1&2 did not swith when we change it 
			  myMuMu2Ctauat18dot5GeV->Fill( myMupMumCTau[mypidx][1] );    //there is a problem here, could be mixed between 1 &2, should be ok if put 1&2 together
			}
			if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0)   //background in signal area is 1/1.8 of sideband
			    ||
			    (myfourmuonmass>=20.0 && myfourmuonmass<=21.0)
			    ) {
			  myMuMu2MassatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
			  myFourMuPtatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
			  myFourMuRapidityatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

			  myMu1EtaVsPtatSideband->Fill(  rawMup4vect[0].Eta(), rawMup4vect[0].Pt() ); 
			  myMu2EtaVsPtatSideband->Fill(  rawMup4vect[1].Eta(), rawMup4vect[1].Pt() ); 
			  myMu3EtaVsPtatSideband->Fill(  rawMup4vect[2].Eta(), rawMup4vect[2].Pt() ); 
			  myMu4EtaVsPtatSideband->Fill(  rawMup4vect[3].Eta(), rawMup4vect[3].Pt() );
			  
			  myMuMu1ptVsMuMu2ptatSideband->Fill(  (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt(), (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );

			  myV1VsMuMuMassAfterVVmassanotherpairatSideband->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

			  if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 ) {
			    myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
			  }

			  myMu1PtatSideband->Fill( rawMup4vect[0].Pt() );
			  myMu2PtatSideband->Fill( rawMup4vect[1].Pt() );
			  myMu3PtatSideband->Fill( rawMup4vect[2].Pt() );
			  myMu4PtatSideband->Fill( rawMup4vect[3].Pt() );

 			  myMu21PtstartatSideband->Fill( rawMuinFourMuFMp4vect[ muIdxp21 ].Pt() ); 
 			  myMu22PtstartatSideband->Fill( rawMuinFourMuFMp4vect[ muIdxp22].Pt() ); 

			  myMuMu1PtatSideband->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Pt() );
			  myMuMu2PtatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Pt() );
			  myMuMuPairsDihedralatSideband->Fill( myDihedral );
			  myMuMuPairsHelicityatSideband->Fill( mymupmum1CosHelicity );
			  myMupmumu1HelicityatSideband->Fill( mymupmum1mupCosHelicity );
			  myMupmumu2HelicityatSideband->Fill( mymupmum2mupCosHelicity );
			  myFourMuFLSigatSideband->Fill(  (*MyFourMuonFLSig)[myFourMuIdx] );
			  myMuMu1CtauatSideband->Fill( myMupMumCTau[mypidx][0] );    //there is a problem here, could be mixed between 1 &2
			  myMuMu2CtauatSideband->Fill( myMupMumCTau[mypidx][1] );    //there is a problem here, could be mixed between 1 &2
			}//if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0) 
			
			//to remove duplicate
			NumDup++;
		      }//if(NumDup<1) {
		    }//if(fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )< 3.0*myY1sResp1
		  
		}//if(1
	      }//for(mycombi=1; myCombi<3; myCombi++)
	    //}//for(int myVi=0;myVi<1;myVi++)	    
	  }//if(1			
		
      }//for (int myFourMuIdx = 0; myFourMuIdx <nJ; myFourMuIdx++)
    
       
  }//for (Long64_t jentry=0;

  myMuMu2Massat15dot7GeV->Write();
  myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->Write();
  
  myMuMuMuMumassV1mumubelowV1cowboyVscowboy->Write();
  myMuMuMuMumassV1mumubelowV1cowboyVsseagull->Write();
  myMuMuMuMumassV1mumubelowV1seagullVscowboy->Write();
  myMuMuMuMumassV1mumubelowV1seagullVsseagull->Write();
  
  myMuPPDeltapxpypz->Write();
  myMuMMDeltapxpypz->Write();
  
  myMuMuOnlyIso->Write();
  myMu1Isoat18dot5GeV->Write();
  myMu2Isoat18dot5GeV->Write();
  myMu3Isoat18dot5GeV->Write();
  myMu4Isoat18dot5GeV->Write();
  
  
  myMuMuMuMumassV1mumubelowV1LowSideShift->Write();
  myMuMuMuMumassV1mumubelowV1HighSideShift->Write();
  
  myMuMuMuMumassV1mumubelowV1LowSide->Write();
  myMuMuMuMumassV1mumubelowV1HighSide->Write();
  
  myMuMuMuMumassV1mumuWithVIso0dot1belowV1->Write();  
  myMuMuMuMumassV1mumuWithVIso0dot2belowV1->Write();  
  myMuMuMuMumassV1mumuWithVIso0dot5belowV1->Write();  

  myMuMuMuMumassV1highestmuWithVIso0dot1belowV1->Write(); 
  myMuMuMuMumassV1highestmuWithVIso0dot2belowV1->Write(); 
  myMuMuMuMumassV1highestmuWithVIso0dot5belowV1->Write(); 
  

  myMuMuMuMumassV1mumubelowV1->Write();
  myMuMuMuMumassDiffV1mumubelowV1->Write();
  myMuMumassforV1highpair->Write();
  myMuMumassforV1lowpair->Write();
  myMuMumassformumulowpair->Write();
  myMuMumassformumuhighpair->Write();
  
  myMuMuonlymass->Write();
  
  myV1VsMuMuMassBeforeVVmasshighpair->Write();
  myV1VsMuMuMassBeforeVVmasslowpair->Write();
  myV1VsMuMuMassAfterVVmassanotherpair->Write();
  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->Write();
  myV1VsMuMuMassAfterVVmassanotherpairatSideband->Write();
  myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->Write();
  myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->Write();
  
  myMu1EtaVsPtat18dot5GeV->Write();
  myMu2EtaVsPtat18dot5GeV->Write();
  myMu3EtaVsPtat18dot5GeV->Write();
  myMu4EtaVsPtat18dot5GeV->Write();
  myMu1EtaVsPtatSideband->Write();
  myMu2EtaVsPtatSideband->Write();
  myMu3EtaVsPtatSideband->Write();
  myMu4EtaVsPtatSideband->Write();
  myMuMu1ptVsMuMu2ptat18dot5GeV->Write();
  myMuMu1ptVsMuMu2ptatSideband->Write();
  

  myMuMu2Massat18dot5GeV->Write();
  myMuMu2MassatSideband->Write();
  myFourMuPtatSideband->Write();
  myFourMuPtat18dot5GeV->Write();
  myFourMuRapidityat18dot5GeV->Write();
  myFourMuRapidityatSideband->Write();

  myMu1Ptat18dot5GeV->Write();
  myMu1PtatSideband->Write();
  myMu2Ptat18dot5GeV->Write();
  myMu2PtatSideband->Write();
  myMu3Ptat18dot5GeV->Write();
  myMu3PtatSideband->Write();
  myMu4Ptat18dot5GeV->Write();
  myMu4PtatSideband->Write();

  myMu21Ptstartat18dot5GeV->Write();
  myMu21PtstartatSideband->Write();
  myMu22Ptstartat18dot5GeV->Write();
  myMu22PtstartatSideband->Write();

  myMuMu1Ptat18dot5GeV->Write();
  myMuMu1PtatSideband->Write();
  myMuMu2Ptat18dot5GeV->Write();
  myMuMu2PtatSideband->Write();
  myMuMuPairsDihedralat18dot5GeV->Write();
  myMuMuPairsDihedralatSideband->Write();
			    
  myMuMuPairsHelicityat18dot5GeV->Write();
  myMuMuPairsHelicityatSideband->Write();
  myMupmumu1Helicityat18dot5GeV->Write();
  myMupmumu1HelicityatSideband->Write();
  myMupmumu2Helicityat18dot5GeV->Write();
  myMupmumu2HelicityatSideband->Write();
  myFourMuFLSigat18dot5GeV->Write();
  myFourMuFLSigatSideband->Write();
  myMuMu1Ctauat18dot5GeV->Write();
  myMuMu1CtauatSideband->Write();
  myMuMu2Ctauat18dot5GeV->Write();
  myMuMu2CtauatSideband->Write();


 
}
