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

//#define muon_mass  0.105658
#define muon_mass 0.10565837
#define jpsi_mass 3.0967


//float raw_muM  =0.10565837; 

//order mode, 1--order by higer mass, m(11)>m(12), m(21)>m(22),  m(11)>m(21), 
#define myordermode 1


//11=Y(1S) mumu <Y(1S), 
#define mychannel 11

struct PairedMuonIdx
{
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
	if( whichpair==1 )
	{
		mytmp=myp.p11; 
		myp.p11=myp.p12; myp.p12=mytmp;
	}
	else if( whichpair==2 )
	{
		mytmp=myp.p21; 
		myp.p21=myp.p22; myp.p22=mytmp;
	}//else

}

 
void myntuple::Loop(TString outputname)
{  
	
	ofstream myoutfilesignal4Cristina("myfourmuonsignal4Cristina.txt");
	ofstream myoutfilesignal7cats("myfourmuonsignalGigi7cats.txt");

	TString mysignaloutname=outputname+"myfourmuonsignal.txt";
	ofstream myoutfilesignal(mysignaloutname);

	TString mysignaloutCERN=outputname+"myfourmuonsignalCERN.txt";
	ofstream myoutfilesignalCERN(mysignaloutCERN);

	TString mysignaloutCERNsevtnumberscheck=outputname+"myfourmuonsignalCERNsevtnumberscheck.txt";
	ofstream myoutfilesignalCERNsevtnumberscheck(mysignaloutCERNsevtnumberscheck);

	TString mysignaloutFNALsevtnumberscheck=outputname+"myfourmuonsignalFNALsevtnumberscheck.txt";
	ofstream myoutfilesignalFNALsevtnumberscheck(mysignaloutFNALsevtnumberscheck);


	ofstream myoutfileEvtNum("myfourmuonEvtNum.txt");
	ofstream myoutfileevtmix("myfourmuonevtmix.txt");
	ofstream myoutfiledimu("mydimuon.txt");

	ofstream myoutfileJYforKamuran("myJYforKamuran.txt");
	ofstream myoutfileJYforMaksat("myJYforMaksat.txt");


	TString mysignal1outname=outputname+"myfourmuonsignal1.txt";
	ofstream myoutfilesignal1(mysignal1outname);
	TString mysignal2outname=outputname+"myfourmuonsignal2.txt";
	ofstream myoutfilesignal2(mysignal2outname);


	// TFile* myhbk = new TFile ("myhbk_MuOnia.root","recreate");
	TFile* myhbk = new TFile (outputname,"recreate");


	//for ARC comments
	ofstream myARCoutNmuTCHG("myARCoutNmuTCHG.txt");
	myARCoutNmuTCHG<<"runNum "<<"lumiNum "<<"evtNum "<<"myGoodSoftMu "<<"myTotalChg "<<endl;

	ofstream myARCoutNTightMu("myARCoutNTightMu.txt");
	myARCoutNTightMu<<"runNum "<<"lumiNum "<<"evtNum "<<"myGoodTightMu "<<endl;

	TH1F* myARCDimuMassPullUpsi=new TH1F("myARCDimuMassPullUpsi","myARCDimuMassPullUpsi",1000,-5,5.0);
	TH1F* myARCDimuMassPullJpsi=new TH1F("myARCDimuMassPullJpsi","myARCDimuMassPullJpsi",1000,-5,5.0);

	TH1F* myARCDimuMassPullUpsiScaled=new TH1F("myARCDimuMassPullUpsiScaled","myARCDimuMassPullUpsiScaled",1000,-5,5.0);
	TH1F* myARCDimuMassPullJpsiScaled=new TH1F("myARCDimuMassPullJpsiScaled","myARCDimuMassPullJpsiScaled",1000,-5,5.0);


	TH1F* myARCDimuMass=new TH1F("myARCDimuMass","myARCDimuMass",100000,0,500.0);


	TH1F* myMuMuChg0ARCmass = new TH1F("myMuMuChg0ARCmass","myMuMuChg0ARCmass",100000,0,500.0);  
	myMuMuChg0ARCmass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
	TH1F* myMuMuChgp2ARCmass = new TH1F("myMuMuChgp2ARCmass","myMuMuChgp2ARCmass",100000,0,500.0);  
	myMuMuChgp2ARCmass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");  
	TH1F* myMuMuChgm2ARCmass = new TH1F("myMuMuChgm2ARCmass","myMuMuChgm2ARCmass",100000,0,500.0);  
	myMuMuChgm2ARCmass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
	
	TH1F* myARCMuMuHighmasserr = new TH1F("myARCMuMuHighmasserr","myARCMuMuHighmasserr",500,0,0.5);  
	myARCMuMuHighmasserr->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(Rapidity) GeV");
	TH1F* myARCMuMuHighmasserrEBE = new TH1F("myARCMuMuHighmasserrEBE","myARCMuMuHighmasserrEBE",500,0,0.5);  
	myARCMuMuHighmasserrEBE->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(EBE) GeV");

	TH2F* myARCMuMuHighmasserrRapidityVsmasserrEBE = new TH2F("myARCMuMuHighmasserrRapidityVsmasserrEBE","myARCMuMuHighmasserrRapidityVsmasserrEBE",500,0,0.5, 500, 0, 0.5);  
	myARCMuMuHighmasserrRapidityVsmasserrEBE->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(Rapidity) GeV");
	myARCMuMuHighmasserrRapidityVsmasserrEBE->GetYaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(EBE) GeV");  

	TH1F* myMuMu01Chgp2ARCmassafterselection = new TH1F("myMuMu01Chgp2ARCmassafterselection","myMuMu01Chgp2ARCmassafterselection",100000,0,500.0);  
	myMuMu01Chgp2ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
	TH1F* myMuMu02Chgm2ARCmassafterselection = new TH1F("myMuMu02Chgm2ARCmassafterselection","myMuMu02Chgm2ARCmassafterselection",100000,0,500.0);  
	myMuMu02Chgm2ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");


	TH1F* myMuMu11Chg0ARCmassafterselection = new TH1F("myMuMu11Chg0ARCmassafterselection","myMuMu11Chg0ARCmassafterselection",100000,0,500.0);  
	myMuMu11Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
	TH1F* myMuMu12Chg0ARCmassafterselection = new TH1F("myMuMu12Chg0ARCmassafterselection","myMuMu12Chg0ARCmassafterselection",100000,0,500.0);  
	myMuMu12Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
	TH1F* myMuMu21Chg0ARCmassafterselection = new TH1F("myMuMu21Chg0ARCmassafterselection","myMuMu21Chg0ARCmassafterselection",100000,0,500.0);  
	myMuMu21Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");
	TH1F* myMuMu22Chg0ARCmassafterselection = new TH1F("myMuMu22Chg0ARCmassafterselection","myMuMu22Chg0ARCmassafterselection",100000,0,500.0);  
	myMuMu22Chg0ARCmassafterselection->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");

	TH1F* myMuMuwith2tightmuChg0ARCmassafterselection = new TH1F("myMuMuwith2tightmuChg0ARCmassafterselection","myMuMuwith2tightmuChg0ARCmassafterselection",100000,0,500.0);  

	TH1F* myNY1swith2tightmusARCafterselection = new TH1F("myNY1swith2tightmusARCafterselection","myNY1swith2tightmusARCafterselection",11,-0.5,10.5);  

	TH2F* myARCY1s2tightmuMu1etaVsMu2eta = new TH2F("myARCY1s2tightmuMu1etaVsMu2eta","myARCY1s2tightmuMu1etaVsMu2eta",25 ,0,2.5, 25, 0, 2.5);  
 
	TH1F* myMuMuChg0ARCmasswith2tightmuEE = new TH1F("myMuMuChg0ARCmasswith2tightmuEE","myMuMuChg0ARCmasswith2tightmuEE",100000,0,500.0);  
	TH1F* myMuMuChg0ARCmasswith2tightmuEB = new TH1F("myMuMuChg0ARCmasswith2tightmuEB","myMuMuChg0ARCmasswith2tightmuEB",100000,0,500.0);  
	TH1F* myMuMuChg0ARCmasswith2tightmuBB = new TH1F("myMuMuChg0ARCmasswith2tightmuBB","myMuMuChg0ARCmasswith2tightmuBB",100000,0,500.0);  
 
	TH1F* myAnotherMuMuChg0ARCwithY1sonthismumumass = new TH1F("myAnotherMuMuChg0ARCwithY1sonthismumumass","myAnotherMuMuChg0ARCwithY1sonthismumumass",100000,0,500.0);  
	TH1F* myFourmuChg0ARCmass = new TH1F("myFourmuChg0ARCmass","myFourmuChg0ARCmass",5000,0,500.0);  
	TH1F* myFourmuChg0ARCmassWithanotherdimult9dot2 = new TH1F("myFourmuChg0ARCmassWithanotherdimult9dot2","myFourmuChg0ARCmassWithanotherdimult9dot2",5000,0,500.0);  

 
	TH2F* myARCFourMuVsanotherdimuMass = new TH2F("myARCFourMuVsanotherdimuMass","myARCFourMuVsanotherdimuMass",5000,0,500.0, 50000, 0, 500.0);  
	TH1F* myFourmuChg0ARCmassandanotherdimultY1s = new TH1F("myFourmuChg0ARCmassandanotherdimultY1s","myFourmuChg0ARCmassandanotherdimultY1s",5000,0,500.0);  
	TH1F* myFourmuChg0ARCmassandanotherdimultY1sEBE = new TH1F("myFourmuChg0ARCmassandanotherdimultY1sEBE","myFourmuChg0ARCmassandanotherdimultY1sEBE",5000,0,500.0);  
	
	TH2F* myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV = new TH2F("myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV","myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV",4000,0,400.0, 10000, 0, 100.0);  



	//end ARC


	//  TH1F* myMuMuMuMumassJUforKamuran = new TH1F("myMuMuMuMumassJUforKamuran","myMuMuMuMumassJUforKamuran",10000,0,1000.0);
	// myMuMuMuMumassJUforKamuran->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");


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

	TH1F* myMuMuMuMumMaxDeltaEta =new TH1F("myMuMuMuMumMaxDeltaEta","myMuMuMuMumMaxDeltaEta",50,0,5);


	TH1F* myMuMuMuMumassV1mumubelowV1nolightmeson = new TH1F("myMuMuMuMumassV1mumubelowV1nolightmeson","myMuMuMuMumassV1mumubelowV1nolightmeson",10000,0,1000.0);
	myMuMuMuMumassV1mumubelowV1nolightmeson->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
	TH1F* myMuMuMuMumassV1mumubelowV1withlightmeson = new TH1F("myMuMuMuMumassV1mumubelowV1withlightmeson","myMuMuMuMumassV1mumubelowV1withlightmeson",10000,0,1000.0);
	myMuMuMuMumassV1mumubelowV1withlightmeson->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");



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

	TH1F* myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination = new TH1F("myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination","myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination",10000,0,1000.0);

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


	TH1F* myMuMu1Massat18dot5GeV = new TH1F("myMuMu1Massat18dot5GeV","myMuMu1Massat18dot5GeV",400,0,20.0);
	TH1F* myMuMu1MassatSideband = new TH1F("myMuMu1MassatSideband","myMuMu1MassatSideband",400,0,20.0);


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
 
	TH2F* myDalitzmY1smupmasssqVsmmumumasssqat18GeV = new TH2F("myDalitzmY1smupmasssqVsmmumumasssqat18GeV","myDalitzmY1smupmasssqVsmmumumasssqat18GeV",4000,0,400.0, 10000, 0, 100.0);  
	TH2F* myDalitzmY1smupmasssqVsmmumumasssqatSideband = new TH2F("myDalitzmY1smupmasssqVsmmumumasssqatSideband","myDalitzmY1smupmasssqVsmmumumasssqatSideband",4000,0,400.0, 10000, 0, 100.0);  




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

	TH1F* my4MuCtauat18dot5GeV = new TH1F("my4MuCtauat18dot5GeV","my4MuCtauat18dot5GeV",2000,-0.5,0.5);
	TH1F* my4MuCtauatSideband = new TH1F("my4MuCtauatSideband","my4MuCtauatSideband",2000,-0.5,0.5);



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

	/*
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
	*/

	
	int CernUniqEvtNumArray[245] = {100017905, 100367214, 100622219, 100739298, 100858235, 100925925, 101449441, 101659205, 102071856, 102072100, 102136508, 102319816, 102934117, 102966181, 102986751, 103007546, 103037117, 103365346, 104134151, 104610779, 104692361, 104762642, 105287442, 105874406, 106089015, 106097061, 106097407, 106104896, 106918038, 106925581, 106953044, 107548231, 107940362, 107940369, 108887106, 108890015, 109302264, 109443222, 109811647, 109866447, 110343840, 111042758, 111094913, 111805004, 111845613, 112410073, 112553091, 112855519, 113256974, 113387214, 113512867, 113567723, 113578042, 113633242, 113761961, 114105744, 114381722, 114425467, 114697266, 115004725, 115008787, 115061004, 115231252, 116136662, 116272238, 116473032, 116589276, 118178960, 118444840, 118470423, 119204105, 119329493, 119356041, 119427218, 120134101, 120372299, 120420453, 12105119, 121188180, 121550927, 123026524, 123558766, 123873865, 123929517, 124354333, 124549629, 124881878, 125892333, 125987499, 126571483, 126592349, 126718968, 126775188, 128167487, 129292357, 129302087, 129352107, 129680711, 129846154, 130116681, 130176989, 130672128, 131200080, 131560387, 131670851, 132003419, 132247348, 132310728, 132959003, 133045155, 133178441, 134516613, 135415278, 135462890, 135523830, 136102075, 136331280, 136874865, 136921840, 137520265, 138371241, 139206018, 140446879, 140559136, 140974850, 141324843, 141331952, 141652431, 141911145, 143814468, 144197491, 144735189, 144807935, 144940725, 145356790, 145568654, 145780955, 147189064, 147448117, 147519230, 148001574, 148116936, 148245470, 148450987, 149970298, 150279353, 1528491, 152947032, 156085185, 157514200, 158471962, 159055925, 161840378, 162108108, 162386533, 16391784, 164350965, 166956011, 167207504, 170317127, 171784036, 175773604, 176763262, 177815063, 17821958, 181504902, 184269613, 189647865, 19018919, 192465437, 198448640, 200533961, 203179635, 203441901, 203529193, 211322935, 213929202, 220371838, 22159302, 225737895, 231359305, 241677713, 24408112, 260875395, 268890748, 271180843, 275542638, 291329694, 295111156, 310269260, 312264822, 323966482, 33241462, 340672759, 344784226, 372374940, 375190616, 397466218, 398663265, 412443447, 413458439, 420045446, 427927089, 437395229, 438103640, 443069909, 446988787, 460561251, 46846021, 484531197, 486267004, 490678769, 504939147, 527256423, 540789856, 566804435, 571583775, 580119686, 590045241, 636076770, 644823893, 645185551, 67929313, 694804754, 699997296, 718063854, 719802961, 721243339, 727568647, 74959569, 756327740, 762819274, 770837496, 783048668, 828915927, 85380555, 861285562, 862440972, 90472200, 905229273, 95901729, 97280235, 977930744, 99485880, 994959379};
	int FnalUniqEvtNumArray[1167] = {1000179055, 1003672146, 1005413323, 1006222193, 100753060, 100823386, 1008582355, 1009259257, 101063577, 1013249394, 1016592054, 1019511424, 1020718567, 1020721009, 1021365085, 1022207757, 1023198166, 102386461, 1029341179, 102994515, 1030075462, 1030371173, 1030551430, 103112265, 1033653463, 1034507396, 1034994566, 103702048, 1037673131, 1041341515, 1041463157, 1042400533, 104337391, 1046107792, 1046138046, 104664936, 1047626429, 1050875573, 1051680790, 1052874423, 105352949, 105510651, 1056112981, 1058744066, 106075278, 1060890154, 1060970616, 1060974078, 1061048966, 106364158, 1064819826, 1065079684, 1066054895, 106763899, 1068987418, 1069180381, 1069255817, 1069348547, 1069530446, 107111958, 1072253734, 107282381, 1072875328, 107302220, 107399184, 1075482310, 1076753520, 1079403628, 1079403690, 1081354273, 108148666, 1083791132, 1088871064, 1088900151, 1089736392, 1093022643, 1093189071, 109361761, 109424462, 1094432222, 1094655336, 1097378489, 1098116478, 1098664475, 1099885772, 1103438403, 110429121, 1108367812, 1110003806, 1110427586, 1110949131, 1111348251, 1113115849, 111433644, 111445048, 1114656075, 111582034, 11166435, 1117399672, 1118050045, 1118456133, 111871337, 1119285319, 1120324106, 1124100735, 1124694310, 112501837, 1125530915, 1126683289, 112788955, 1128555190, 1131888616, 1132569748, 1133872149, 1135128674, 1135677230, 1135780423, 1136332428, 1137514163, 1137619613, 1140455481, 1141057443, 1143817222, 1144254677, 1146972666, 1150047258, 1150087874, 1150610049, 115268482, 11535392, 115922560, 11602414, 1161366623, 1161981597, 1162722386, 116303581, 1164730320, 11650275, 1165394888, 1165892761, 116617744, 116768984, 1167963114, 1168003437, 116878677, 1170321326, 1171005312, 1173251754, 117327424, 1174820356, 117561404, 1181789608, 1181814940, 1184704232, 118496854, 1190202145, 1191214409, 11913623, 1192041054, 1193294931, 1193560418, 119418137, 1194272187, 119492840, 119563149, 1196784071, 1200706130, 1201341011, 1201822015, 120246367, 1203722998, 1204204531, 120574874, 1211881805, 1215509278, 121780725, 121842475, 1229908294, 123004806, 1230265248, 1233360256, 123436696, 1235587662, 1238738653, 1239295174, 12411683, 1241515086, 124184397, 1243543332, 1245018082, 1245496290, 1248818783, 1252245369, 125457565, 1256457912, 125681357, 1257008335, 1258923338, 125951043, 1259874998, 126044622, 1261021696, 126114798, 1264675165, 1265714837, 1265923493, 1267189681, 127114327, 1271476218, 1272804706, 1273867260, 1276210228, 1281674879, 1284262488, 1290029487, 129102879, 1293020871, 1293521071, 129359603, 129390532, 1296807111, 1298461545, 130043132, 1301166818, 1301769897, 130471571, 1306721288, 1309743798, 1312000805, 1315603870, 131599302, 1316708518, 131950262, 1320034194, 13210422, 1321653317, 1322265200, 1322473486, 1323107288, 1327800243, 1329590036, 1330451559, 1331044204, 1331784410, 1343425452, 134408796, 1345166134, 134550618, 1347911758, 135233735, 1354628900, 1355238302, 135671959, 135738225, 1358330814, 1361020750, 13623355, 1363312805, 136540390, 136848230, 1368748657, 137079141, 1374912595, 1375202651, 137749014, 1378641503, 1379273507, 1383712415, 138396930, 13880799, 138935645, 139073820, 139099935, 1392060183, 139272898, 139299994, 1393034197, 1398071711, 1399964467, 1402093443, 140306686, 140752340, 140943840, 1409748505, 1412772574, 1413248432, 1413319524, 1415023086, 1416524311, 1419111450, 1424562097, 142473055, 143581879, 1438144683, 1440982603, 1441595054, 144681416, 1447351890, 14474924, 1447948566, 1448079355, 144809114, 1449407252, 1453567906, 14538427, 1455686542, 145570411, 1457809558, 145968392, 1465024981, 146508283, 1466722329, 146762120, 1471890644, 1474172773, 1475192303, 1476320413, 1480015743, 1481169364, 1482454706, 148258505, 148559071, 148768506, 149292997, 1496248609, 1499260913, 150012701, 1501199860, 150188195, 1502062808, 1502793532, 150526854, 150767623, 151605138, 1519162249, 1528319603, 1529470329, 1530698830, 154629017, 1546322940, 154982305, 155346854, 1560627357, 1560851859, 1561524861, 156504753, 15723370, 1576611962, 1584719623, 158485578, 1586035589, 158804007, 158924578, 1590559256, 1597529380, 1603196092, 161027548, 1613353675, 161362528, 161695414, 1618403785, 1621081087, 1623865338, 1628219122, 162861731, 1638447680, 1641817833, 164304306, 1643509658, 164548634, 164887453, 1649400689, 1649544578, 165231465, 165336633, 165473748, 166217726, 166526102, 167578917, 167740731, 169254774, 169829013, 170429123, 170479395, 170641128, 170747901, 170788313, 171052694, 171241949, 1717840368, 172415146, 172484786, 17287494, 173082529, 1734076, 173506468, 17408995, 174179055, 174181715, 1757736045, 1758920302, 176559336, 1768200231, 1768340972, 177379392, 1774956782, 1778150632, 178412524, 179249967, 179704028, 179787254, 181295211, 181745528, 181747448, 18188768, 182264872, 184199618, 1842696139, 184962438, 185077779, 1852455631, 185272385, 1856336944, 1859095964, 186126252, 1870217318, 1875098942, 187568311, 1896478656, 190710540, 191672324, 1924654378, 192680106, 19326052, 193927000, 194068992, 194709963, 196041119, 196559460, 19785281, 1984486403, 198612150, 1990953126, 1992177343, 200103546, 200505713, 200510757, 20117450, 202274367, 202579921, 2034419014, 2035291931, 203902973, 2046298281, 204862106, 2055466732, 205655600, 206741871, 20686253, 2072881002, 2081325341, 209987451, 210076086, 2113229357, 211840315, 21186679, 21240347, 212474698, 212727168, 21279532, 2128633394, 212884003, 213314878, 214357815, 215777903, 218035389, 218060753, 218720005, 22022996, 220302464, 220889982, 222007479, 222809304, 224967435, 226279446, 227101959, 227697744, 228001746, 228115835, 228761062, 22887273, 228898694, 230731271, 230866609, 230923729, 231085947, 232571983, 234813534, 236049346, 236935976, 237244748, 237636042, 23965082, 239741270, 242727045, 243474657, 244083172, 244668690, 24475077, 24650703, 248217023, 252278606, 252951091, 254044555, 254534995, 257364141, 257925529, 258050941, 258395488, 26020614, 260995883, 261007401, 261795478, 262108720, 262456100, 263291380, 264935400, 26505042, 265314214, 265772330, 267901165, 268302917, 269380612, 269398349, 269860272, 270009623, 270288379, 270637796, 272700425, 273043015, 273389396, 275359848, 280385894, 280908583, 280945319, 28140040, 28421079, 284823805, 285209027, 285212828, 285438306, 286031353, 286247961, 287550245, 287717011, 287878443, 289323323, 290144351, 290359780, 291044413, 29107696, 29117088, 292152275, 292286250, 292765413, 29379134, 294960997, 296519241, 298339050, 298670226, 298754366, 301490051, 302960495, 30500356, 307148413, 309467488, 309519477, 309891340, 310046655, 311695811, 313260962, 314201809, 31499622, 31499714, 315137968, 316705903, 316749052, 31705271, 317066447, 317220197, 317937110, 319048392, 319993316, 320761181, 321408474, 321449232, 3216026, 32197000, 322728752, 325028151, 325104299, 325532634, 326788952, 327655545, 330755298, 330887455, 331265059, 331568194, 333580048, 333888191, 335230469, 336439513, 33674311, 33746130, 33811083, 338128277, 33826518, 338805615, 339467971, 340071223, 34048105, 340846705, 342593866, 344094940, 344876568, 345240628, 347026594, 347270464, 348006474, 348694049, 348932253, 349940233, 351162438, 351185338, 351662275, 35279390, 353337819, 353375163, 354355246, 354977478, 355098380, 356798146, 357608559, 357793941, 359776603, 360590452, 36123576, 363285778, 36402878, 36421310, 365330552, 368206056, 368293924, 368531341, 370884964, 371027033, 371031588, 372750685, 372964130, 376937762, 37731387, 377369677, 381647005, 382339379, 383391181, 385465209, 385554972, 38597051, 385973268, 386209735, 386424792, 386457709, 387480716, 388059326, 388650341, 388915650, 390216273, 390532738, 39120102, 391386984, 391763512, 392078107, 392990385, 394202859, 394842294, 39544443, 395801528, 39597114, 396073980, 39697846, 39921077, 399759355, 400163166, 400910127, 40116379, 402781911, 403048535, 403565200, 403703762, 40467697, 406187962, 406677332, 408240349, 41046368, 41096330, 411951560, 412050679, 412540247, 413750545, 414612553, 415966315, 416280887, 416753739, 41932281, 420340654, 421890069, 422375372, 423302515, 426067522, 42648410, 426728442, 427412705, 428157663, 428513672, 428554463, 431103811, 43146985, 432222008, 43225223, 434774432, 436160779, 438489613, 438641942, 438992328, 442663685, 442749714, 443226553, 443630475, 443665322, 443724131, 444667331, 444868717, 446740031, 446853878, 447287086, 448051557, 452637798, 453872909, 454909243, 45703666, 458226460, 459927954, 460387564, 461442074, 461938070, 462611880, 462652606, 466613420, 466627819, 467324228, 468334139, 469361711, 469488108, 469592213, 469977476, 47052775, 47194309, 472704188, 475832572, 476271045, 478764946, 479080347, 483274845, 483354464, 483565140, 483868068, 484451264, 484791726, 486234471, 487328815, 487492111, 487693981, 490711139, 490771726, 493220123, 493512957, 495323217, 495637473, 496527809, 496816997, 497369718, 497496502, 498426766, 499693218, 500381664, 500482518, 501769227, 502107461, 503537362, 50362806, 504299033, 50476769, 505728524, 506260442, 50657734, 507573183, 509572286, 510342069, 51117557, 513143593, 514455193, 514760764, 515648958, 515815919, 516079519, 516636285, 516716893, 517026084, 519697454, 520089353, 524911837, 524940570, 52533897, 527821036, 52932366, 530326385, 530815725, 530893189, 531275221, 53129882, 533243487, 533462617, 534177253, 53855404, 539615876, 540202001, 540328240, 541080678, 541734926, 543984574, 546087298, 54781499, 548435499, 549935905, 550194422, 55296591, 554180995, 554859619, 555075741, 556715876, 557595582, 557882739, 557892647, 558592559, 558709550, 560783772, 560875562, 561201504, 561580220, 564741843, 565250293, 568919344, 56925749, 570287459, 572472907, 573078539, 573392656, 574453227, 57518635, 576478595, 577123466, 577209597, 577646853, 578750520, 578992571, 57899340, 579064096, 579078231, 579313133, 580055464, 580524435, 58107837, 581187263, 581267665, 582780869, 587780549, 590208060, 591633800, 592387976, 594182882, 594526920, 597192827, 598929794, 599091069, 599454760, 600086778, 60010502, 601642942, 60177581, 603199402, 603258176, 603289923, 60655519, 607437616, 608262532, 610249605, 61038749, 612903013, 61367909, 61498021, 615884836, 616067146, 61625705, 616379656, 617205847, 618071894, 618214246, 618332692, 619090144, 623188466, 623482351, 625072539, 625410814, 625589457, 628206459, 6286035, 629349384, 630710286, 63140088, 631761082, 633310699, 633374237, 634632248, 635597394, 639421817, 63959600, 640535772, 641740037, 642672808, 643590857, 644128337, 646516405, 647469193, 647676783, 647944867, 648139412, 648166114, 649557959, 650130965, 651520741, 653280625, 6555828, 658523469, 66027923, 666992469, 667691489, 66915340, 672848450, 67393576, 674041497, 67423554, 674827418, 67600850, 676619519, 677922773, 67973162, 68177109, 683081442, 68579505, 686032988, 686295848, 686356530, 686616056, 686618038, 6901271, 692881014, 694655481, 695373892, 69629508, 69715672, 698085203, 698266240, 699005527, 69955405, 70027668, 702957710, 70322363, 704635551, 706957359, 70835227, 708906289, 7094904, 710430786, 71049301, 710753512, 71418453, 714605196, 715549694, 716715540, 71839721, 71943497, 71980792, 724346211, 726046270, 728248891, 729407472, 732428682, 733329292, 73662738, 738180803, 74074375, 742000913, 742878880, 743476514, 74396740, 744162938, 74444811, 747482632, 74779422, 750012587, 750695494, 751799125, 753306025, 754079582, 756135608, 758831660, 759895285, 76090946, 76218707, 76228785, 763973828, 76429148, 766743937, 768155188, 769441052, 77189930, 773536576, 77539911, 77735487, 77790036, 778531501, 779843892, 78101628, 78446624, 787270649, 792110028, 792590420, 79446592, 796126041, 798353999, 79892550, 799756035, 801067291, 801754157, 804533845, 804781202, 805057569, 805988527, 80726970, 8077660, 813918575, 81668095, 817469514, 819307911, 82159241, 82175962, 822609448, 823835031, 82534663, 826740968, 82685494, 83199382, 834187976, 83752647, 83765370, 84116736, 843598006, 844512946, 846704480, 853312709, 855190212, 85727635, 860769816, 861015231, 861542314, 864633902, 8652952, 866027587, 86668124, 86858630, 873440506, 875953736, 8766057, 877481394, 87985759, 880730866, 881233478, 882518283, 882762080, 88302262, 88364226, 885963357, 88747827, 888031424, 889595647, 8917219, 893217710, 893747213, 89550038, 89765412, 897693945, 903777118, 904398521, 90496304, 911752796, 912673468, 912952998, 913502208, 91390107, 916550673, 921555041, 92295064, 924254603, 924332394, 926884910, 92781695, 928601522, 9291797, 929433032, 930740213, 931251157, 931701325, 935804702, 937777556, 938589842, 940436470, 941481524, 944236641, 944241352, 945760307, 94855927, 950410676, 952411857, 95531271, 957043270, 95794477, 958344467, 958783952, 963045189, 96606128, 966124848, 968342033, 97079779, 972472977, 972740781, 97303271, 975460902, 975755178, 978901, 981389671, 982234354, 982553494, 983016128, 98975187, 9947466, 99588528, 99671626};

	
	
	if (fChain == 0) return;
	
	Long64_t nentries = fChain->GetEntries();
	cout<<"Total entries="<<nentries<<endl;
	
	Long64_t nbytes = 0, nb = 0;
	//for (Long64_t jentry=0; jentry<2500;jentry++) {
	for (Long64_t jentry=0; jentry<nentries;jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		if(jentry%10000==0) cout<<"I am running "<<jentry<<"th entries out of "<<nentries<<" total entries"<<endl;

		//  myoutfileEvtNum<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;

		bool TrigThreeMuon=false;
		bool TrigThreeMuonJpsi=false;
		bool TrigThreeMuonUpsi=false;

		bool TrigPsiprime=false;


		bool TrigTripleMu5=false;
		bool TrigDoubleMu5IsoMu5=false;
		bool TrigMu8=false;
		bool TrigDiMu7Upsi=false;
		bool TrigDiMu5Upsi=false;


		for(int i=0; i!=TrigRes->size(); ++i)
		{ 
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
			if( (TrigNames->at(i).find("HLT_TripleMu5_")!=string::npos && TrigRes->at(i)==1) )
			{
				TrigTripleMu5 = true;
			}//if( (TrigNames->at(i).find("HLT_TripleMu5_")!=string::npos && TrigRes->at(i)==1) 
			if( (TrigNames->at(i).find("HLT_DoubleMu5_IsoMu5")!=string::npos && TrigRes->at(i)==1) )
			{ 
				TrigDoubleMu5IsoMu5 = true;
			}//if( (TrigNames->at(i).find("HLT_DoubleMu5_IsoMu5")!=string::npos && TrigRes->at(i)==1) 
			if( (TrigNames->at(i).find("HLT_Mu8_v")!=string::npos && TrigRes->at(i)==1) )
			{
				TrigMu8 = true;
			}//if( (TrigNames->at(i).find("HLT_Mu8_v")!=string::npos && TrigRes->at(i)==1)     
			if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1) )
			{ 
				TrigDiMu7Upsi = true;
			}//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)
			if( (TrigNames->at(i).find("HLT_Dimuon5_Upsilon_")!=string::npos && TrigRes->at(i)==1) )
			{ 
				TrigDiMu5Upsi = true;
				//cout<<TrigNames->at(i)<<", result="<<TrigRes->at(i)<<endl;
			}//if( (TrigNames->at(i).find("HLT_Dimuon7_Upsilon_")!=string::npos && TrigRes->at(i)==1)

		}


		//ARC suggestion
		int myGoodSoftMu=0;
		int myTotalChg=0;
		int mySoftMuIdx[100];  //assume maximum good muon is 100
		if(TrigThreeMuonUpsi)
		{
			for(int mymui=0; mymui<nMu; mymui++)
			{
				TLorentzVector mymup4;
				mymup4.SetXYZM( (*muPx)[mymui], (*muPy)[mymui], (*muPz)[mymui], muon_mass); 
				// cout<<"(*muPx)[mymui]="<<(*muPx)[mymui]<<","<<mymup4.Px()<<endl;
				if( (*muIsGoodLooseMuon)[mymui]>0  
					&& mymup4.Pt()>=2.0 && fabs( mymup4.Eta() ) <=2.4
					) 
					{
						myTotalChg+=(*muCharge)[mymui];
						mySoftMuIdx[myGoodSoftMu]=mymui;
						myGoodSoftMu++;
					}
			}
		}
		if(myGoodSoftMu>=4)
		{  
			//cout<<runNum<<" "<<evtNum<<" "<<lumiNum<<" "<<myGoodSoftMu<<" "<<myTotalChg<<endl;
			myARCoutNmuTCHG<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myGoodSoftMu<<" "<<myTotalChg<<endl;

			for(int myi=0; myi<myGoodSoftMu; myi++)
			{ 
				for(int myj=myi+1; myj<myGoodSoftMu; myj++) 
				{
					TLorentzVector mymuip4,mymujp4;
					mymuip4.SetXYZM( (*muPx)[ mySoftMuIdx[myi] ], (*muPy)[ mySoftMuIdx[myi] ], (*muPz)[ mySoftMuIdx[myi] ], muon_mass); 
					mymujp4.SetXYZM( (*muPx)[ mySoftMuIdx[myj] ], (*muPy)[ mySoftMuIdx[myj] ], (*muPz)[ mySoftMuIdx[myj] ], muon_mass); 
					if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]==0 )	      
					{
						myMuMuChg0ARCmass->Fill( (mymuip4+mymujp4).M() );
					}
					if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]==2 )	      
					{
						myMuMuChgp2ARCmass->Fill( (mymuip4+mymujp4).M() );
					}
					if(  (*muCharge)[ mySoftMuIdx[myi] ]+(*muCharge)[ mySoftMuIdx[myj] ]== -2 )	      
					{
						myMuMuChgm2ARCmass->Fill( (mymuip4+mymujp4).M() );
					}
				}

			}
		} // if(myGoodSoftMu>=4)

		//ARC suggestion
		
		for(int myi=0; myi<nmumuonly; myi++)
		{
			int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*mumuonlymu1Idx)[myi]] + (*muIsGoodLooseMuon)[ (*mumuonlymu2Idx)[myi]];
			int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*mumuonlymu1Idx)[myi]] + (*muIsGoodTightMuon)[ (*mumuonlymu2Idx)[myi]];
			TLorentzVector rawMu1p4vect, rawMu2p4vect;
			float raw_muPx = (*muPx)[ (*mumuonlymu1Idx)[myi] ];
			float raw_muPy = (*muPy)[ (*mumuonlymu1Idx)[myi] ];
			float raw_muPz = (*muPz)[ (*mumuonlymu1Idx)[myi] ];
			
			rawMu1p4vect.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);    
			raw_muPx = (*muPx)[ (*mumuonlymu2Idx)[myi] ]; raw_muPy = (*muPy)[ (*mumuonlymu2Idx)[myi] ]; raw_muPz = (*muPz)[ (*mumuonlymu2Idx)[myi] ];
			rawMu2p4vect.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);    
			
			if(1
				//	 && (TrigThreeMuonJpsi || TrigThreeMuonUpsi)
				&& (TrigThreeMuonUpsi)
				&& (*mumuonlyVtxCL)[myi]>0.005
				&& myNumGoodLooseMuon>=2
				//&& myNumGoodTightMuon>=2
				&& fabs(rawMu1p4vect.Eta())<=2.4 && fabs(rawMu2p4vect.Eta())<=2.4
				&& rawMu1p4vect.Pt()>=2.0 && rawMu2p4vect.Pt()>=2.0
				&& ( (*muCharge)[ (*mumuonlymu1Idx)[myi] ] + (*muCharge)[ (*mumuonlymu2Idx)[myi] ] ) ==0
				)
			{


				myMuMuonlymass->Fill( (*mumuonlyMass)[myi] ); 



				if(  (*mumuonlyMass)[myi]>9.2 &&  (*mumuonlyMass)[myi]<9.75 )
				{
					myMuMuOnlyIso->Fill( (*muIsoratio)[ (*mumuonlymu1Idx)[myi] ]   );
					myMuMuOnlyIso->Fill( (*muIsoratio)[ (*mumuonlymu2Idx)[myi] ]   ); 
				}
				
			}
		} // for(int myi=0; myi<nmumuonly; myi++)
					





		/////////////////////////////////////four muon signal/////////////////////////////////////////////
		/////////////////////////////////////four muon signal/////////////////////////////////////////////
		/////////////////////////////////////four muon signal/////////////////////////////////////////////
		/////////////////////////////////////four muon signal/////////////////////////////////////////////
		/////////////////////////////////////four muon signal/////////////////////////////////////////////

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
			//	float raw_muM  =0.10565837; 
			Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);   
			RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
			rawMup4vect.push_back( Rawmu ); rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
			raw_muPx = (*muPx)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];
			Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);  rawMup4vect.push_back( Rawmu );
			RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
			rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
			raw_muPx = (*muPx)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];
			Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);  rawMup4vect.push_back( Rawmu );
			RawmuinFourMuFM=Rawmu; RawmuinFourMuFM.Boost( -myFourMuonP4.BoostVector() );
			rawMuinFourMuFMp4vect.push_back( RawmuinFourMuFM );
			raw_muPx = (*muPx)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];
			Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);  rawMup4vect.push_back( Rawmu );
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
				for(int i=1; i<3; i++)
				{
					if( (fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()  ) swap_one_paired_pair( myCombIdx[i] ); //for have first pair to have bigger mass
				}	
				//sort to have first pair to have bigger mass
				if( ((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()) < ((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M() ) ) 
					swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );	    
			}
			else if(myordermode==2)
			{
				for(int i=1; i<3; i++)
				{
					if( (fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()<(fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()  ) swap_one_paired_pair( myCombIdx[i] ); //for have first pair to have bigger mass
				}	
				//sort to make sure that |myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
				if( fabs((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()-mymV )> fabs((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M()-mymV ) ) 
					swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );
			}	
			else if(myordermode==3)
			{
				for(int i=1; i<3; i++)
				{
					if( fabs((fitMup4vect[ myCombIdx[i].p11 ]+ fitMup4vect[ myCombIdx[i].p12 ]).M()-mymV) > fabs((fitMup4vect[ myCombIdx[i].p21 ]+ fitMup4vect[ myCombIdx[i].p22 ]).M()-mymV)  ) swap_one_paired_pair( myCombIdx[i] ); //for 
				}
				//sort to make sure that |myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
				if( fabs((fitMup4vect[ myCombIdx[1].p11 ]+ fitMup4vect[ myCombIdx[1].p12 ]).M()-mymV )> fabs((fitMup4vect[ myCombIdx[2].p11 ]+ fitMup4vect[ myCombIdx[2].p12 ]).M()-mymV ) )
					swap_two_paired_pair( myCombIdx[1],  myCombIdx[2] );
			}


			//sort to make sure that the pi1 is always point to mu+
			//swap_one_pair( PairedMuonIdx & myp, int whichpair )
			//for(int myVi=0;myVi<2;myVi++) 
			for(int i=1; i<3; i++)
			{
				if( fitMuCharge[ myCombIdx[i].p11 ] !=1 ) swap_one_pair( myCombIdx[i], 1 );
				if( fitMuCharge[ myCombIdx[i].p21 ] !=1 ) swap_one_pair( myCombIdx[i], 2 );
			}
			// store information for sub-pair for each paied pair
			// the design is not so good, so we need more work here to match them
			// cout<<" vtx prob, 01&23, 02&13, 03&12="<<(*MyJpsi1ChiProb_Mu12)[myFourMuIdx]<<","<<(*MyJpsi2ChiProb_Mu34)[myFourMuIdx]<<",  "<<(*MyJpsi3ChiProb_Mu13)[myFourMuIdx]<<","<<(*MyJpsi4ChiProb_Mu24)[myFourMuIdx]<<",  "<<(*MyJpsi5ChiProb_Mu14)[myFourMuIdx]<<","<<(*MyJpsi6ChiProb_Mu23)[myFourMuIdx]<<endl;
			// cout<<" ctau, 01&23, 02&13, 03&12="<<(*MyJpsi1CTau_Mu12)[myFourMuIdx]<<","<<(*MyJpsi2CTau_Mu34)[myFourMuIdx]<<",  "<<(*MyJpsi3CTau_Mu13)[myFourMuIdx]<<","<<(*MyJpsi4CTau_Mu24)[myFourMuIdx]<<",  "<<(*MyJpsi5CTau_Mu14)[myFourMuIdx]<<","<<(*MyJpsi6CTau_Mu23)[myFourMuIdx]<<endl;
			// cout<<" ctauerr, 01&23, 02&13, 03&12="<<(*MyJpsi1CTauErr_Mu12)[myFourMuIdx]<<","<<(*MyJpsi2CTauErr_Mu34)[myFourMuIdx]<<",  "<<(*MyJpsi3CTauErr_Mu13)[myFourMuIdx]<<","<<(*MyJpsi4CTauErr_Mu24)[myFourMuIdx]<<",  "<<(*MyJpsi5CTauErr_Mu14)[myFourMuIdx]<<","<<(*MyJpsi6CTauErr_Mu23)[myFourMuIdx]<<endl;

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


			//dimuon mass from the fit
			float myMupMumMass[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
			//myCombIdx[0], should be zero always 
			//
			myMupMumMass[0][0]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[0][1]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; 	
			if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
			{ myMupMumMass[0][1]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[0][0]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; }
			//
			if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
			{ myMupMumMass[0][0]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[0][1]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
			if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
			{ myMupMumMass[0][1]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[0][0]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
			//
			if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
			{ myMupMumMass[0][0]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[0][1]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
			if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
			{ myMupMumMass[0][1]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[0][0]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
			//
			//myCombIdx[1] 
			myMupMumMass[1][0]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[1][1]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; 	
			if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
			{ myMupMumMass[1][1]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[1][0]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; }
			//
			if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
			{ myMupMumMass[1][0]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[1][1]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
			if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
			{ myMupMumMass[1][1]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[1][0]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
			//
			if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
			{ myMupMumMass[1][0]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[1][1]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
			if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
			{ myMupMumMass[1][1]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[1][0]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
			//myCombIdx[2] 
			myMupMumMass[2][0]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[2][1]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; 	
			if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
			{ myMupMumMass[2][1]=(*MyJpsi1Mass_Mu12)[myFourMuIdx];  myMupMumMass[2][0]=(*MyJpsi2Mass_Mu34)[myFourMuIdx]; }
			//
			if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
			{ myMupMumMass[2][0]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[2][1]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
			if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
			{ myMupMumMass[2][1]=(*MyJpsi3Mass_Mu13)[myFourMuIdx];  myMupMumMass[2][0]=(*MyJpsi4Mass_Mu24)[myFourMuIdx]; }
			//
			if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
			{ myMupMumMass[2][0]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[2][1]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
			if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
			{ myMupMumMass[2][1]=(*MyJpsi5Mass_Mu14)[myFourMuIdx];  myMupMumMass[2][0]=(*MyJpsi6Mass_Mu23)[myFourMuIdx]; }	
			//----------------------------------------------------------------------------------------------------------------------------

			//dimuon mass error
			float myMupMumMassErr[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
			//myCombIdx[0], should be zero always 
			//
			myMupMumMassErr[0][0]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[0][1]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; 	
			if(  (myCombIdx[0].p11==2 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==2) )
			{ myMupMumMassErr[0][1]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[0][0]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; }
			//
			if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==0) ) 
			{ myMupMumMassErr[0][0]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[0][1]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
			if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==1) ) 
			{ myMupMumMassErr[0][1]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[0][0]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
			//
			if( (myCombIdx[0].p11==0 && myCombIdx[0].p12==3) ||  (myCombIdx[0].p11==3 && myCombIdx[0].p12==0) ) 
			{ myMupMumMassErr[0][0]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[0][1]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
			if( (myCombIdx[0].p11==1 && myCombIdx[0].p12==2) ||  (myCombIdx[0].p11==2 && myCombIdx[0].p12==1) ) 
			{ myMupMumMassErr[0][1]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[0][0]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
			//
			//myCombIdx[1] 
			myMupMumMassErr[1][0]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[1][1]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; 	
			if(  (myCombIdx[1].p11==2 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==2) )
			{ myMupMumMassErr[1][1]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[1][0]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; }
			//
			if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==0) ) 
			{ myMupMumMassErr[1][0]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[1][1]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
			if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==1) ) 
			{ myMupMumMassErr[1][1]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[1][0]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
			//
			if( (myCombIdx[1].p11==0 && myCombIdx[1].p12==3) ||  (myCombIdx[1].p11==3 && myCombIdx[1].p12==0) ) 
			{ myMupMumMassErr[1][0]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[1][1]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
			if( (myCombIdx[1].p11==1 && myCombIdx[1].p12==2) ||  (myCombIdx[1].p11==2 && myCombIdx[1].p12==1) ) 
			{ myMupMumMassErr[1][1]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[1][0]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
			//myCombIdx[2] 
			myMupMumMassErr[2][0]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[2][1]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; 	
			if(  (myCombIdx[2].p11==2 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==2) )
			{ myMupMumMassErr[2][1]=(*MyJpsi1MassErr_Mu12)[myFourMuIdx];  myMupMumMassErr[2][0]=(*MyJpsi2MassErr_Mu34)[myFourMuIdx]; }
			//
			if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==0) ) 
			{ myMupMumMassErr[2][0]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[2][1]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
			if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==1) ) 
			{ myMupMumMassErr[2][1]=(*MyJpsi3MassErr_Mu13)[myFourMuIdx];  myMupMumMassErr[2][0]=(*MyJpsi4MassErr_Mu24)[myFourMuIdx]; }
			//
			if( (myCombIdx[2].p11==0 && myCombIdx[2].p12==3) ||  (myCombIdx[2].p11==3 && myCombIdx[2].p12==0) ) 
			{ myMupMumMassErr[2][0]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[2][1]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
			if( (myCombIdx[2].p11==1 && myCombIdx[2].p12==2) ||  (myCombIdx[2].p11==2 && myCombIdx[2].p12==1) ) 
			{ myMupMumMassErr[2][1]=(*MyJpsi5MassErr_Mu14)[myFourMuIdx];  myMupMumMassErr[2][0]=(*MyJpsi6MassErr_Mu23)[myFourMuIdx]; }	
			//----------------------------------------------------------------------------------------------------------------------------

			//added by yik to check EBE fro ARC
			for(int i=1; i<3; i++)
			{
				for (int j=0;j<2;j++)
				{
					int mymuidx1,mymuidx2;
					if(j==0) {mymuidx1=myCombIdx[i].p11; mymuidx2=myCombIdx[i].p12; }
					if(j==1) {mymuidx1=myCombIdx[i].p21; mymuidx2=myCombIdx[i].p22; }
					// muIdxp11=myCombIdx[mypidx].p11; muIdxp12=myCombIdx[mypidx].p12; muIdxp21=myCombIdx[mypidx].p21; muIdxp22=myCombIdx[mypidx].p22;

					if(myMupMumVtxProb[i][j]>0.005   //impl the total chg==0 for this cut because it will be negative otherwise
						// && (*muIsGoodLooseMuon)[mymuidx1] && (*muIsGoodLooseMuon)[mymuidx2]
						&& (*muIsGoodTightMuon)[mymuidx1] && (*muIsGoodTightMuon)[mymuidx2]
						&& rawMup4vect[mymuidx1].Pt()>=2.0 && rawMup4vect[mymuidx2].Pt()>=2.0
						&& rawMup4vect[mymuidx1].Eta()<=2.4 && rawMup4vect[mymuidx2].Eta()<=2.4
						) 
					{
						// cout<<"(i,j)=("<<i<<","<<j<<"),"<<myMupMumMass[i][j]<<","<<myMupMumMassErr[i][j]<<endl;
						myARCDimuMass->Fill( myMupMumMass[i][j] );
						myARCDimuMassPullUpsi->Fill( (myMupMumMass[i][j]-9.46)/myMupMumMassErr[i][j] );
						myARCDimuMassPullJpsi->Fill( (myMupMumMass[i][j]-3.096919)/myMupMumMassErr[i][j] );

						myARCDimuMassPullUpsiScaled->Fill( (myMupMumMass[i][j]-9.46)/(myMupMumMassErr[i][j]*1.0576) );
						myARCDimuMassPullJpsiScaled->Fill( (myMupMumMass[i][j]-3.096919)/(myMupMumMassErr[i][j]*1.125) );
						myoutfiledimu<<myMupMumMass[i][j]<<" "<<myMupMumMassErr[i][j]<<endl;
					}
				}
			}
			//end added by yik to check EBE fro ARC

			//muon ID 
			int isTightMuon[4], isLooseMuon[4], myMuIso[4];
			//default muonID old soft muonID w/ TMOneStationLoose	
			/*	
			isLooseMuon[0]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isLooseMuon[2]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			*/

			// modified muonID new soft muonID w/ TMOneStationLoose
			/*
			isLooseMuon[0]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isLooseMuon[2]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			*/
			/*
			//test old soft muonID w/ TMOneStationTight
			isLooseMuon[0]=(*muIsGoodLooseMuonNew)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodLooseMuonNew)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isLooseMuon[2]=(*muIsGoodLooseMuonNew)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodLooseMuonNew)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			*/

				
			//new default muon id					
			//test new soft muonID 
			isLooseMuon[0]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isLooseMuon[2]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			
		
			/*	
			//test modified new soft muonID || old soft muonID w/ TMOneStationLoose
			isLooseMuon[0]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] ||  (*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   
			isLooseMuon[1]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] ||  (*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isLooseMuon[2]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] ||  (*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   
			isLooseMuon[3]=(*muIsGoodSoftMuonNewIlseMod)[ (*MyFourMuonMu4Idx)[myFourMuIdx]] ||  (*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			*/

			/*	
			//test new soft muonID && old soft muonID w/ TMOneStationTight
			isLooseMuon[0]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] &&  (*muIsGoodLooseMuonNew)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   
			isLooseMuon[1]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] &&  (*muIsGoodLooseMuonNew)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isLooseMuon[2]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] &&  (*muIsGoodLooseMuonNew)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   
			isLooseMuon[3]=(*muIsGoodSoftMuonNewIlse)[ (*MyFourMuonMu4Idx)[myFourMuIdx]] &&  (*muIsGoodLooseMuonNew)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			*/



			/*
			//test Bsmumu MVA soft muonID
			isLooseMuon[0]=(*muMVAMuonID)[ (*MyFourMuonMu1Idx)[myFourMuIdx]]>0;   isLooseMuon[1]=(*muMVAMuonID)[ (*MyFourMuonMu2Idx)[myFourMuIdx]]>0;
			isLooseMuon[2]=(*muMVAMuonID)[ (*MyFourMuonMu3Idx)[myFourMuIdx]]>0;   isLooseMuon[3]=(*muMVAMuonID)[ (*MyFourMuonMu4Idx)[myFourMuIdx]]>0;
			*/

			isTightMuon[0]=(*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isTightMuon[1]=(*muIsGoodTightMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			isTightMuon[2]=(*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isTightMuon[3]=(*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];


			// myMuIso[0]= (*muIsoratio)[ (*MyFourMuonMu1Idx)[myFourMuIdx]]; myMuIso[1]= (*muIsoratio)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
			// myMuIso[2]= (*muIsoratio)[ (*MyFourMuonMu3Idx)[myFourMuIdx]]; myMuIso[3]= (*muIsoratio)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];


			//	float myfourmuonmass=(*MyFourMuonMass)[myFourMuIdx];
			float myfourmuonmass= (fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).M();
			
			//int muonQual[] = {1,3,4,12};   
			// (N.B. "All" condition not saved => muQual  must have 1 for GlobalMu (1), TrackerMu(3). TMArbitrated(4), TMLastStationLoose (7)
			//int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			int myNumGoodLooseMuon=isLooseMuon[0]+isLooseMuon[1]+isLooseMuon[2]+isLooseMuon[3];
			
			int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
			//int myGlobalMuNum=(int)(bool)( ((*muQual)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) ) + (int)(bool)( ((*muQual)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) ) + (int)(bool)( ((*muQual)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) ) + (int)(bool)( ((*muQual)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]) & (1 << muonQual[0] ) );
			
			//bool matchUpsiTrig=(*muIsUpsTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] && (*muIsUpsTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] && (*muIsUpsTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] &&(*muIsUpsTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
			//bool matchJpsiTrig=(*muIsJpsiTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] && (*muIsJpsiTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] && (*muIsJpsiTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] &&(*muIsJpsiTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
			
			//int matchUpsiTrig=(int)(*muIsUpsTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] + (int) (*muIsUpsTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] + (int)(*muIsUpsTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] + (int)(*muIsUpsTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
			//int matchJpsiTrig=(int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ] + (int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ] + (int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ] + (int)(*muIsJpsiTrigMatch)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ] ;
			
			TLorentzVector myRaw4Mup4=rawMup4vect[0]+rawMup4vect[1]+rawMup4vect[2]+rawMup4vect[3];
			float myetacut=2.4;   //1.6, there is a bump at 31 GeV for Y(1S) mumu, default 2.4
			float minMuPt=2.0;  //2.0--default 1.5;2,5;3.0;3.5;  2.2

			float myEBEscale=1.105;
			//float myEBEscale=1.2;
			


			if(1
				&& myNumGoodLooseMuon>=4


				&&
				( (*MyFourMuonOverlap12)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap13)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap14)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap23)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap24)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap34)[myFourMuIdx]<1
				)
			 

				/*	   	   
				&& (*muShits)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ]>=5
				&& (*muShits)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]>=5
				&& (*muShits)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]>=5
				&& (*muShits)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]>=5
				*/


				/*	   
				&&  
				(   ((*MyFourMuonSharedSeg12)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg13)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg14)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg23)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg24)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg34)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
				)
				*/ 


				/*
				&&  
				(   ((*MyFourMuonSharedSeg12)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg13)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg14)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg23)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg24)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
				&&  ((*MyFourMuonSharedSeg34)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
				)
				*/

				/*
				&& 
				(!( (*MyFourMuonOverlap12)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap13)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap14)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap23)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap24)[myFourMuIdx]<1
				&& (*MyFourMuonOverlap34)[myFourMuIdx]<1
				)
				||
					!( ((*MyFourMuonSharedSeg12)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ]))<0.5
					&&  ((*MyFourMuonSharedSeg13)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<0.5
					&&  ((*MyFourMuonSharedSeg14)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
					&&  ((*MyFourMuonSharedSeg23)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<0.5
					&&  ((*MyFourMuonSharedSeg24)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
					&&  ((*MyFourMuonSharedSeg34)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<0.5
					)
				)
				*/


				&& (*MyFourMuonVtxCL)[myFourMuIdx]>=0.05   //	   
				
				//MuOnia data
				&& ( TrigThreeMuonJpsi || TrigThreeMuonUpsi )    //for three muon trigger, default trigger, remove it for Higgs test
				// && TrigThreeMuonUpsi
						 

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

				&& (fitMuCharge[0]+fitMuCharge[1]+fitMuCharge[2]+fitMuCharge[3])==0

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
				// cout<<(*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ]<<","<<(*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ]<<","<<(*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]<<","<<(*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]<<",share between 12,13,14,23,24,34="<<((*MyFourMuonSharedSeg12)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ]))<<","<< ((*MyFourMuonSharedSeg13)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg14)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg23)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg24)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg34)[myFourMuIdx]/std::min<double>( (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<<",shared if choose max="<<((*MyFourMuonSharedSeg12)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ]))<<","<< ((*MyFourMuonSharedSeg13)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg14)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu1Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg23)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg24)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu2Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<<","<<((*MyFourMuonSharedSeg34)[myFourMuIdx]/std::max<double>( (*munMatchedSeg)[(*MyFourMuonMu3Idx)[myFourMuIdx] ], (*munMatchedSeg)[(*MyFourMuonMu4Idx)[myFourMuIdx] ]))<<endl;
				int NumCanforKamuranCHK=0;
				int NumCanforMaksatCHK=0;

				int NumDupARC=0; 
				int NumDupARCEBE=0;
				int NumDup=0;   //we have two pairs, but only fill one time if at least one pair satisfy it
				for(int mypidx=1; mypidx<3; mypidx++) //loop over the two combinations with zero chg
				//for(int mypidx=2; mypidx>0; mypidx--) //loop over the two combinations with zero chg, low mass combination first
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
									 
						// && (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt()>=3.0    //2.5
						// && (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt()>=0.0   //2.5
						// && (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ] ).Pt()>=20.0

						// && rawMup4vect[ 2 ].Pt()>3.0 //simulate atlas three-mu trigger
						 
						// simulate ATLAS trigger
						// && (rawMup4vect[ muIdxp11 ]).Pt()>=4.0
						// && (rawMup4vect[ muIdxp12 ]).Pt()>=4.0		   

						// simulate doublemu5 trigger
						// && (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt()>=5.0
						// simulate single mu trigger
						// && ( rawMup4vect[ muIdxp11 ].Pt()>=10.0 || rawMup4vect[ muIdxp12 ].Pt()>=10.0 || rawMup4vect[ muIdxp21 ].Pt()>=10.0 || rawMup4vect[ muIdxp22 ].Pt()>10.0 ) 
						 
						)
					{
						if( mypidx==1 )
						{
							myMuMumassforV1highpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()  );
							myMuMumassformumuhighpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
							myV1VsMuMuMassBeforeVVmasshighpair->Fill((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
							// check if muon pt is sorted.  Yeah, it is.
							// cout<<"rawMup4vect[0] pt="<<rawMup4vect[0].Pt()<<", (rawMup4vect[1]="<<rawMup4vect[1].Pt()<<", rawMup4vect[2].Pt()="<<rawMup4vect[2].Pt()<<", rawMup4vect[3].Pt()="<<rawMup4vect[3].Pt()<<endl;
							
						}
						if( mypidx==2 )
						{
							myMuMumassforV1lowpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );		      
							myMuMumassformumulowpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
							myV1VsMuMuMassBeforeVVmasslowpair->Fill((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
						}
						//apply mass cut 
						float mynsigma=3.0;
						bool myVVmasscut;
						if( mychannel==11 )
						{  //Y(1S) mumu
							/*
							//old cut
							myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
							// myVVmasscut= (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() < (mymV - mynsigma*myY1sResp1) 
							// && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > (mymV - 2*mynsigma*myY1sResp1)
							// to check background event to see if we can have a bck shape.
							&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myY1sResp2 )
							// && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= 9.0  //4; 5, 7; 
							&& myNumGoodTightMuon>=2; //if one of the V is Upsilon
							*/
					
							// used EBE error
							myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myEBEscale*myMupMumMassErr[mypidx][0]  
							// myVVmasscut= (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() < (mymV - mynsigma*myY1sResp1) 
							// && (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > (mymV - 2*mynsigma*myY1sResp1)
							// to check background event to see if we can have a bck shape.
							&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myEBEscale*myMupMumMassErr[mypidx][1] )
							// && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= 9.0  //4; 5, 7; 
							&& myNumGoodTightMuon>=2; //if one of the V is Upsilon
					
						}

						// define low/high Y(1S) sidebands
						float lowsidel=8.6, lowsideh=9.2, highsidel=9.75, highsideh=9.85;
						if(mychannel==11)
						{
							if(  myNumGoodTightMuon>=2  //if one of the V is Upsilon
								&& (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() >lowsidel 
								&& (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() <lowsideh
								// && myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
								// &&(fitMup4vect[muIdxp21]+fitMup4vect[muIdxp22]).M()<=(mymV-mynsigma*myY1sResp2), assumed it is ordered 
								)
							{
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
								// && myVVmasscut= fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
								// &&(fitMup4vect[muIdxp21]+fitMup4vect[muIdxp22]).M()<=(mymV-mynsigma*myY1sResp2), assumed it is ordered 
								)
							{
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
				

						// dealing ARC comments		 
						if( mypidx==1 
						// && TrigThreeMuonUpsi
						&& myNumGoodTightMuon>=2
						)
						{
							myARCoutNTightMu<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myNumGoodTightMuon<<endl;
							int mu01p11=myCombIdx[0].p11,mu01p12=myCombIdx[0].p12,mu11p11=myCombIdx[1].p11,mu11p12=myCombIdx[1].p12,  mu21p11=myCombIdx[2].p11,mu21p12=myCombIdx[2].p12;
							int mu02p11=myCombIdx[0].p21,mu02p12=myCombIdx[0].p22,mu12p11=myCombIdx[1].p21,mu12p12=myCombIdx[1].p22,  mu22p11=myCombIdx[2].p21,mu22p12=myCombIdx[2].p22;
							myMuMu01Chgp2ARCmassafterselection->Fill( (fitMup4vect[ mu01p11 ]+fitMup4vect[ mu01p12 ]).M() );
							myMuMu02Chgm2ARCmassafterselection->Fill( (fitMup4vect[ mu02p11 ]+fitMup4vect[ mu02p12 ]).M() );
							myMuMu11Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
							myMuMu12Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
							myMuMu21Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
							myMuMu22Chg0ARCmassafterselection->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
							//cout<<myNumGoodTightMuon<<endl;
							int nY1Comination2Tightmu=0;
							if(isTightMuon[mu11p11]>0 && isTightMuon[mu11p12]>0)
							{
								if( fabs(rawMup4vect[mu11p11].Eta()) > 1.0 && fabs(rawMup4vect[mu11p12].Eta()) >1.0 )			   
								{
									//cout<<", ee m="<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() ); 
								}
								else if( fabs(rawMup4vect[mu11p11].Eta()) > 1.0 || fabs(rawMup4vect[mu11p12].Eta()) >1.0 ) 
								{
								//cout<<", eb m="<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;
								myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
								}
								else 
								{
									//cout<<", bb m="<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
								}
								// cout<<"11,"<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<endl;	
								if( fabs((fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()-9.46)<0.25 ) 
								{
									nY1Comination2Tightmu++;
									myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu11p11].Eta()),  fabs(rawMup4vect[mu11p12].Eta()) );
									//cout<<fabs(rawMup4vect[mu11p11].Eta())<<","<<fabs(rawMup4vect[mu11p12].Eta())<<endl;
								}
								myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M() );
							}
							
							if(isTightMuon[mu12p11]>0 && isTightMuon[mu12p12]>0)
							{
								if( fabs(rawMup4vect[mu12p11].Eta()) > 1.0 && fabs(rawMup4vect[mu12p12].Eta()) >1.0 )			   
								{
									//cout<<", ee m="<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() ); 
								}
								else if( fabs(rawMup4vect[mu12p11].Eta()) > 1.0 || fabs(rawMup4vect[mu12p12].Eta()) >1.0 ) 
								{
									//cout<<", eb m="<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
								}
								else 
								{
									//cout<<", bb m="<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
								}	

								if( fabs((fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()-9.46)<0.25 ) 
								{
									nY1Comination2Tightmu++;
									myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu12p11].Eta()),  fabs(rawMup4vect[mu12p12].Eta()) );
								}
								myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M() );
								//cout<<"12,"<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<endl;			
							}

							if(isTightMuon[mu21p11]>0 && isTightMuon[mu21p12]>0)
							{
								if( fabs(rawMup4vect[mu21p11].Eta()) > 1.0 && fabs(rawMup4vect[mu21p12].Eta()) >1.0 )			   
								{
									//cout<<", ee m="<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() ); 
								}
								else if( fabs(rawMup4vect[mu21p11].Eta()) > 1.0 || fabs(rawMup4vect[mu21p12].Eta()) >1.0 ) 
								{
									//cout<<", eb m="<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
								}
								else 
								{
									//cout<<", bb m="<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
								}

								if( fabs((fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()-9.46)<0.25 ) 
								{
									nY1Comination2Tightmu++;
									myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu21p11].Eta()),  fabs(rawMup4vect[mu21p12].Eta()) );
								}
								myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M() );
								//cout<<"21,"<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<endl;			
							}
							if(isTightMuon[mu22p11]>0 && isTightMuon[mu22p12]>0)
							{
								if( fabs(rawMup4vect[mu22p11].Eta()) > 1.0 && fabs(rawMup4vect[mu22p12].Eta()) >1.0 )			   
								{
									//cout<<", ee m="<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEE->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() ); 
								}
								else if( fabs(rawMup4vect[mu22p11].Eta()) > 1.0 || fabs(rawMup4vect[mu22p12].Eta()) >1.0 ) 
								{
									//cout<<", eb m="<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuEB->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
								} 
								else 
								{
									//cout<<", bb m="<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
									myMuMuChg0ARCmasswith2tightmuBB->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
								} 
				
								if( fabs((fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()-9.46)<0.25 ) 
								{
									nY1Comination2Tightmu++;
									myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu22p11].Eta()),  fabs(rawMup4vect[mu22p12].Eta()) );
								}
								myMuMuwith2tightmuChg0ARCmassafterselection->Fill( (fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M() );
								//cout<<"22,"<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;			
							}
							
							//cout<<"nY1Comination2Tightmu="<<nY1Comination2Tightmu<<endl;
					
							myNY1swith2tightmusARCafterselection->Fill( nY1Comination2Tightmu );

							//cout<<(fitMuCharge[mu01p11]+fitMuCharge[mu01p12])<<","<<(fitMuCharge[mu02p11]+fitMuCharge[mu02p12])<<endl;
							//cout<<(fitMup4vect[ mu01p11 ]+fitMup4vect[ mu01p12 ]).M()<<","<<(fitMup4vect[ mu02p11 ]+fitMup4vect[ mu02p12 ]).M()<<","<<(fitMup4vect[ mu11p11 ]+fitMup4vect[ mu11p12 ]).M()<<","<<(fitMup4vect[ mu12p11 ]+fitMup4vect[ mu12p12 ]).M()<<","<<(fitMup4vect[ mu21p11 ]+fitMup4vect[ mu21p12 ]).M()<<","<<(fitMup4vect[ mu22p11 ]+fitMup4vect[ mu22p12 ]).M()<<endl;
							//cout<<myMupMumMass[0][0]<<","<<myMupMumMass[0][1]<<","<<myMupMumMass[1][0]<<","<<myMupMumMass[1][1]<<","<<myMupMumMass[2][0]<<","<<myMupMumMass[2][1]<<endl;
							for(int myi=1; myi<3; myi++)
							{
								for (int myj=0;myj<2; myj++)
								{
									int myjanother=1; if(myj==1) { myjanother=0; }
									int muIdxthisARCp11, muIdxthisARCp12, muIdxanotherARCp11, muIdxanotherARCp12;
									if(myj==0)
									{
										muIdxthisARCp11=myCombIdx[myi].p11; muIdxthisARCp12=myCombIdx[myi].p12; 
										muIdxanotherARCp11=myCombIdx[myi].p21; muIdxanotherARCp12=myCombIdx[myi].p22;
									}
									if(myj==1)
									{
										muIdxthisARCp11=myCombIdx[myi].p21; muIdxthisARCp12=myCombIdx[myi].p22; 
										muIdxanotherARCp11=myCombIdx[myi].p11; muIdxanotherARCp12=myCombIdx[myi].p12;
									}
									TLorentzVector mymumuthisp4=rawMup4vect[ muIdxthisARCp11 ]+ rawMup4vect[ muIdxthisARCp12 ];
									TLorentzVector mymumuanotherp4=rawMup4vect[ muIdxanotherARCp11 ]+ rawMup4vect[ muIdxanotherARCp12 ];
									double myrapthis=fabs(0.5*log( (mymumuthisp4.E() + mymumuthisp4.Pz())/(mymumuthisp4.E() - mymumuthisp4.Pz()) ) );
									double myrapanother=fabs(0.5*log( (mymumuanotherp4.E() + mymumuanotherp4.Pz())/(mymumuanotherp4.E() - mymumuanotherp4.Pz()) ) );
									//obtained from data
									double myY1sResthis=0.0572+0.03602*myrapthis;
									double myY1sRespanother=0.0572+0.03602*myrapanother; 
				
									if( fabs((fitMup4vect[ muIdxthisARCp11 ]+ fitMup4vect[ muIdxthisARCp12 ]).M()-9.46)<0.25 )
									{
											myARCMuMuHighmasserr->Fill( myY1sResthis ); 
											myARCMuMuHighmasserrEBE->Fill( myMupMumMassErr[myi][myj] );
											myARCMuMuHighmasserrRapidityVsmasserrEBE->Fill( myY1sResthis, myMupMumMassErr[myi][myj] );
											myAnotherMuMuChg0ARCwithY1sonthismumumass->Fill( (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M() );
											myFourmuChg0ARCmass->Fill( myfourmuonmass );
											if( (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M()<9.2 )
											{
												myFourmuChg0ARCmassWithanotherdimult9dot2->Fill( myfourmuonmass );
											}

											myARCFourMuVsanotherdimuMass->Fill( myfourmuonmass, (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M() );
											// cout<<"myi="<<myi<<",myj="<<myj<<",old this dimu mass & err=("<<(fitMup4vect[ muIdxthisARCp11 ]+ fitMup4vect[ muIdxthisARCp12 ]).M()<<","<<myY1sResthis<<"), new this dimu mass & err=("<<myMupMumMass[myi][myj]<<", "<<myMupMumMassErr[myi][myj]<<")"<<"old another dimu mass & err=("<<(fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M()<<","<<myY1sRespanother<<"), new another dimu mass & err=("<<myMupMumMass[myi][myjanother]<<", "<<myMupMumMassErr[myi][myjanother]<<")"<<endl;			   
									}
									// if( fabs(myMupMumMass[myi][myj]-9.46)<0.25 )
								}
								// for (int myj=0;myj<2; myj++) {
							}
							// for(int myi=1; myi<3; myi++) {
						}
						// if( mypidx==1 

						//cout<<"myY1sResp1, myMupMumMassErr[mypidx][0]="<<myY1sResp1<<","<<myMupMumMassErr[mypidx][0]<<",myY1sResp2,myMupMumMassErr[mypidx][1] )="<<myY1sResp2<<","<<myMupMumMassErr[mypidx][1]<<endl;

						//ARC requested final result
						//with old mass resolution
						

						if(1
							// &&TrigThreeMuonUpsi
							&& fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
							&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myY1sResp2 )
							&& myNumGoodTightMuon>=2 //if one of the V is Upsilon	
							&& NumDupARC<1
						)
						{
							myFourmuChg0ARCmassandanotherdimultY1s->Fill( myfourmuonmass ); 
							NumDupARC++;
						}
						// with EBE
						if(1
							//&&TrigThreeMuonUpsi
							&& fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myMupMumMassErr[mypidx][0]
							&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma* myMupMumMassErr[mypidx][1] )
							&& myNumGoodTightMuon>=2 //if one of the V is Upsilon	
							&& NumDupARCEBE<1
							) 
						{
							myFourmuChg0ARCmassandanotherdimultY1sEBE->Fill( myfourmuonmass ); 
							if( myfourmuonmass>18.0 && myfourmuonmass<19.0)
							{
								myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );
							}
							NumDupARCEBE++;
						}
						//dealing ARC comments end		  

						//test for Kamuran JY, keep two combinations for test purpose
						if( rawMup4vect[ muIdxp11 ].Pt()>3.5 && rawMup4vect[ muIdxp12 ].Pt()>3.5
							&&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > 8.0 &&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<11.0
							&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >2.5 && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<3.5
							)
						{
							myoutfileJYforKamuran<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<(NumCanforKamuranCHK++)<<endl;
						}
						// end test for Kamuran JY
						// test for Maksat YY, keep two combinations for test purpose
						if( rawMup4vect[ muIdxp11 ].Pt()>3.5 && rawMup4vect[ muIdxp12 ].Pt()>3.5
							&& rawMup4vect[ muIdxp21 ].Pt()>3.5 && rawMup4vect[ muIdxp22 ].Pt()>3.5
							&& (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > 8.0 &&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<11.0
							&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() > 8.0 && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<11.0
							)
						{
							myoutfileJYforMaksat<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<(NumCanforMaksatCHK++)<<endl;
						}
						// end test for Kamuran JY
				


						// VV MASS CUT HERE //

						if(1
							&& myVVmasscut		     
							) 
						{
							if(NumDup<1) 
							{

								for (int i = 0; i < 245; i++)
								{
										if (evtNum == CernUniqEvtNumArray[i])
										{
											myoutfilesignalCERNsevtnumberscheck<<myfourmuonmass<<" "<<runNum<<" "<<lumiNum<<" "<<evtNum<<endl;
										}
								}


								// dihedral angle
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
				
								// myoutfileEvtNum<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;

								myoutfileevtmix<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Px()
									<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Py()
									<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Pz()
									<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Px()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Py()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Pz()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()
									<<" "<<fitMup4vect[ muIdxp11 ].Px()<<" "<<fitMup4vect[ muIdxp11 ].Py()
									<<" "<<fitMup4vect[ muIdxp11 ].Pz()<<" "<<fitMup4vect[ muIdxp12 ].Px()
									<<" "<<fitMup4vect[ muIdxp12 ].Py()<<" "<<fitMup4vect[ muIdxp12 ].Pz()
									<<" "<<fitMup4vect[ muIdxp21 ].Px()<<" "<<fitMup4vect[ muIdxp21 ].Py()
									<<" "<<fitMup4vect[ muIdxp21 ].Pz()<<" "<<fitMup4vect[ muIdxp22 ].Px()
									<<" "<<fitMup4vect[ muIdxp22 ].Py()<<" "<<fitMup4vect[ muIdxp22 ].Pz()
									<<" "<<endl;

								

								myoutfilesignal<<myfourmuonmass<<" "<<(*MyFourMuonMassErr)[myFourMuIdx]
									<<" "<<(rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt()
									<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()
									<<" "<<(rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()
									<<" "<<(rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt()
									<<" "<<rawMup4vect[ muIdxp11 ].Pt()<<" "<<rawMup4vect[ muIdxp12 ].Pt()
									<<" "<<rawMup4vect[ muIdxp21 ].Pt()<<" "<<rawMup4vect[ muIdxp22 ].Pt()
									<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ] ).M()
									<<" "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp22 ] ).M()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ] + fitMup4vect[ muIdxp11 ] ).M()
									<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ] + fitMup4vect[ muIdxp12 ] ).M()
									<<" "<<(*MyFourMuonVtxCL)[myFourMuIdx]<<" "<<myMumu1Mumu2DisXY[mypidx]
									<<" "<<myMumu1Mumu2DisZ[mypidx]
									<<" "<<fabs( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).Rapidity()-(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).Rapidity() ) 
									<<" "<<fabs( (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).Rapidity()-(fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22]).Rapidity() ) 
									<<" "<<(*MyFourMuonCTau)[ myFourMuIdx ]<<" "<<runNum<<" "<<evtNum<<" "<<lumiNum
									<<endl;

								myoutfilesignalCERN<<runNum<<" "<<evtNum<<" "<<lumiNum<<" "<<myfourmuonmass<<endl;


								int theotherdimuidx=2; if(mypidx==2) {theotherdimuidx=1;}

								myoutfilesignal7cats<<myfourmuonmass
									<<" "<< (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<myMupMumMassErr[mypidx][0]<<" "<<myY1sResp1
									<<" "<< (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<myMupMumMassErr[mypidx][1]<<" "<<myY1sResp2
									<<" "<<(fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()<<" "<<myMupMumMassErr[theotherdimuidx][0]
									<<" "<<(fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()<<" "<<myMupMumMassErr[theotherdimuidx][1]
									<<endl;
				

								/*
								myoutfilesignal4Cristina<<runNum<<" "<<lumiNum<<" "<<evtNum
									<<" "<<rawMup4vect[ muIdxp11 ].Px()<<" "<<rawMup4vect[ muIdxp11].Py()<<" "<<rawMup4vect[ muIdxp11 ].Pz()
									<<" "<<rawMup4vect[ muIdxp12 ].Px()<<" "<<rawMup4vect[ muIdxp12].Py()<<" "<<rawMup4vect[ muIdxp12 ].Pz()
									<<" "<<rawMup4vect[ muIdxp21 ].Px()<<" "<<rawMup4vect[ muIdxp21].Py()<<" "<<rawMup4vect[ muIdxp21 ].Pz()
									<<" "<<rawMup4vect[ muIdxp22 ].Px()<<" "<<rawMup4vect[ muIdxp22].Py()<<" "<<rawMup4vect[ muIdxp22 ].Pz()
									<<" "<<myfourmuonmass<<" "<<endl;
								*/

								myoutfilesignal4Cristina<<"runlumevt "<<runNum<<" "<<lumiNum<<" "<<evtNum
									<<" mu1234ptphieta "<<rawMup4vect[ muIdxp11 ].Pt()<<" "<<rawMup4vect[ muIdxp11].Phi()<<" "<<rawMup4vect[ muIdxp11 ].Eta()
									<<" "<<rawMup4vect[ muIdxp12 ].Pt()<<" "<<rawMup4vect[ muIdxp12].Phi()<<" "<<rawMup4vect[ muIdxp12 ].Eta()
									<<" "<<rawMup4vect[ muIdxp21 ].Pt()<<" "<<rawMup4vect[ muIdxp21].Phi()<<" "<<rawMup4vect[ muIdxp21 ].Eta()
									<<" "<<rawMup4vect[ muIdxp22 ].Pt()<<" "<<rawMup4vect[ muIdxp22].Phi()<<" "<<rawMup4vect[ muIdxp22 ].Eta()
									<<" 4mumass "<<myfourmuonmass<<" 4muvtxprob "<<(*MyFourMuonVtxCL)[myFourMuIdx] 
									<<" vtx1prob "<<myMupMumVtxProb[mypidx][0]<<" vtx2prob "<<myMupMumVtxProb[mypidx][1]
									<<" dimu12mass "<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()
									<<" dimu12massErrEBE "<<myMupMumMassErr[mypidx][0]<<" "<<myMupMumMassErr[mypidx][1]<<" dimumassErronRapidity12 "<<myY1sResp1<<" "<<myY1sResp2
									<<" "<<endl;


								float myexclnsigma=2.0;

								// Light meson study
								if( fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-3.096919)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
								&& fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-3.096919)>  myMupMumMassErr[myanotherpidx][1]*myexclnsigma
								//&& fabs( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-3.096919)> myMupMumMassErr[mypidx][1]*myexclnsigma
								&& fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][0]*myexclnsigma
								&& fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-1.01946)> myMupMumMassErr[myanotherpidx][1]*myexclnsigma
								//&& fabs( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-1.01946)> myMupMumMassErr[mypidx][1]*myexclnsigma
								&& fabs((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][0]*myexclnsigma
								&& fabs((fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M()-0.78265)>myMupMumMassErr[myanotherpidx][1]*myexclnsigma
								//&& fabs( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()-0.78265)> myMupMumMassErr[mypidx][1]*myexclnsigma
								)
								{
									myMuMuMuMumassV1mumubelowV1nolightmeson->Fill( myfourmuonmass );
									myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination->Fill(  myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV );
									myoutfilesignal1<<myfourmuonmass<<" "<<( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV)<<" "<<(*MyFourMuonMassErr)[myFourMuIdx]<<endl;
								}
								else
								{
									myMuMuMuMumassV1mumubelowV1withlightmeson->Fill( myfourmuonmass );
									myoutfilesignal2<<myfourmuonmass<<" "<<(*MyFourMuonMassErr)[myFourMuIdx]<<endl;
								}


								// Fill default 4-muon mass
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								myMuMuMuMumassV1mumubelowV1->Fill( myfourmuonmass );
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
								//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


								//dr means deltaeta
								float dr12,dr13,dr14,dr23,dr24,dr34, mymaxdeta;
								dr12=fabs(rawMup4vect[0].Eta()-rawMup4vect[1].Eta());
								dr13=fabs(rawMup4vect[0].Eta()-rawMup4vect[2].Eta()); 
								dr14=fabs(rawMup4vect[0].Eta()-rawMup4vect[3].Eta()); 
								dr23=fabs(rawMup4vect[1].Eta()-rawMup4vect[2].Eta()); 
								dr24=fabs(rawMup4vect[1].Eta()-rawMup4vect[3].Eta()); 
								dr34=fabs(rawMup4vect[2].Eta()-rawMup4vect[3].Eta()); 

								mymaxdeta=std::max(dr12,dr13); mymaxdeta=std::max(mymaxdeta,dr14 ); mymaxdeta=std::max(mymaxdeta,dr23 );
								mymaxdeta=std::max(mymaxdeta,dr24 ); mymaxdeta=std::max(mymaxdeta,dr34 );

								myMuMuMuMumMaxDeltaEta->Fill(mymaxdeta); 

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
								if( deltaPhi1>0 && deltaPhi2>0 )
								{
									myMuMuMuMumassV1mumubelowV1seagullVsseagull->Fill( myfourmuonmass );
									if(myfourmuonmass>15.2 && myfourmuonmass<16.2)
									{
										myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->Fill( (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() ); 
										myMuMu2Massat15dot7GeV->Fill(  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
										// myoutfileEvtNum<<runNum<<" "<<evtNum<<" "<<lumiNum<<endl;
									}
								}
								// cout<< deltaPhi1<<","<<deltaPhi2<<endl; 
				
								
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
								

								if( myfourmuonmass>=18.0 && myfourmuonmass<=19.0 )
								{
									
									//myoutfileEvtNum<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myfourmuonmass<<", "<<rawMup4vect[ muIdxp11 ].Pt()<<" "<<rawMup4vect[ muIdxp11 ].Eta()<<" "<<rawMup4vect[ muIdxp11 ].Phi()<<", "<<rawMup4vect[ muIdxp12 ].Pt()<<" "<<rawMup4vect[ muIdxp12 ].Eta()<<" "<<rawMup4vect[ muIdxp12 ].Phi()<<", "<<rawMup4vect[ muIdxp21 ].Pt()<<" "<<rawMup4vect[ muIdxp21 ].Eta()<<" "<<rawMup4vect[ muIdxp21 ].Phi()<<", "<<rawMup4vect[ muIdxp22 ].Pt()<<" "<<rawMup4vect[ muIdxp22 ].Eta()<<" "<<rawMup4vect[ muIdxp22 ].Phi()<<endl;

									myDalitzmY1smupmasssqVsmmumumasssqat18GeV->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );


									myMu1Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] );
									myMu2Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] );
									myMu3Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] );
									myMu4Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu4Idx)[myFourMuIdx]] );
									

									myMuMu1Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );

									myMuMu2Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );

									myFourMuPtat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
									myFourMuRapidityat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

									myMu1EtaVsPtat18dot5GeV->Fill(  rawMup4vect[0].Eta(), rawMup4vect[0].Pt() ); 
									myMu2EtaVsPtat18dot5GeV->Fill(  rawMup4vect[1].Eta(), rawMup4vect[1].Pt() ); 
									myMu3EtaVsPtat18dot5GeV->Fill(  rawMup4vect[2].Eta(), rawMup4vect[2].Pt() ); 
									myMu4EtaVsPtat18dot5GeV->Fill(  rawMup4vect[3].Eta(), rawMup4vect[3].Pt() );
									
									myMuMu1ptVsMuMu2ptat18dot5GeV->Fill(  (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt(), (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
									
									myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

									if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 )
									{
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

									my4MuCtauat18dot5GeV->Fill(  (*MyFourMuonCTau)[ myFourMuIdx ] );

									myMuMu1Ctauat18dot5GeV->Fill( myMupMumCTau[mypidx][0] );    //there is a problem here, could be mixed between 1 &2, 1&2 did not swith when we change it 
									myMuMu2Ctauat18dot5GeV->Fill( myMupMumCTau[mypidx][1] );    //there is a problem here, could be mixed between 1 &2, should be ok if put 1&2 together
								}

								if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0)   //background in signal area is 1/1.8 of sideband
									||
									(myfourmuonmass>=20.0 && myfourmuonmass<=21.0)
									)
								{

									myDalitzmY1smupmasssqVsmmumumasssqatSideband->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );


									myMuMu1MassatSideband->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );

									myMuMu2MassatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
									myFourMuPtatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
									myFourMuRapidityatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

									myMu1EtaVsPtatSideband->Fill(  rawMup4vect[0].Eta(), rawMup4vect[0].Pt() ); 
									myMu2EtaVsPtatSideband->Fill(  rawMup4vect[1].Eta(), rawMup4vect[1].Pt() ); 
									myMu3EtaVsPtatSideband->Fill(  rawMup4vect[2].Eta(), rawMup4vect[2].Pt() ); 
									myMu4EtaVsPtatSideband->Fill(  rawMup4vect[3].Eta(), rawMup4vect[3].Pt() );
									
									myMuMu1ptVsMuMu2ptatSideband->Fill(  (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt(), (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );

									myV1VsMuMuMassAfterVVmassanotherpairatSideband->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

									if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 )
									{
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
									my4MuCtauatSideband->Fill(  (*MyFourMuonCTau)[ myFourMuIdx ] );

									myMuMu1CtauatSideband->Fill( myMupMumCTau[mypidx][0] );    //there is a problem here, could be mixed between 1 &2
									myMuMu2CtauatSideband->Fill( myMupMumCTau[mypidx][1] );    //there is a problem here, could be mixed between 1 &2
								}
								// if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0) 
					
								// to remove duplicate
								NumDup++;
							}
							// if(NumDup<1)
						}
						// if(fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )< 3.0*myY1sResp1
						
					}
					// if(1
				}
				// for(mycombi=1; myCombi<3; myCombi++)

			}//if(1			
				
		}//for (int myFourMuIdx = 0; myFourMuIdx <nJ; myFourMuIdx++)


	}//for (Long64_t jentry=0;


	myhbk->Write();
	
	// myARCDimuMassPullUpsi->Write();
	// myARCDimuMassPullJpsi->Write();

	// myARCDimuMassPullUpsiScaled->Write();
	// myARCDimuMassPullJpsiScaled->Write();

	// myARCDimuMass->Write();
	// myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV->Write();

	// myMuMuChg0ARCmass->Write();
	// myMuMuChgp2ARCmass->Write();
	// myMuMuChgm2ARCmass->Write();
	// myARCMuMuHighmasserr->Write();
	// myARCMuMuHighmasserrEBE->Write();
	// myARCMuMuHighmasserrRapidityVsmasserrEBE->Write();
	// myMuMu11Chg0ARCmassafterselection->Write();
	// myMuMu12Chg0ARCmassafterselection->Write();
	// myMuMu21Chg0ARCmassafterselection->Write();
	// myMuMu22Chg0ARCmassafterselection->Write();
	// myMuMu01Chgp2ARCmassafterselection->Write();
	// myMuMu02Chgm2ARCmassafterselection->Write();
	// myMuMuwith2tightmuChg0ARCmassafterselection->Write();
	// myNY1swith2tightmusARCafterselection->Write();
	// myARCY1s2tightmuMu1etaVsMu2eta->Write();
	// myMuMuChg0ARCmasswith2tightmuEE->Write();
	// myMuMuChg0ARCmasswith2tightmuEB->Write();
	// myMuMuChg0ARCmasswith2tightmuBB->Write();
	// myAnotherMuMuChg0ARCwithY1sonthismumumass->Write();
	// myFourmuChg0ARCmass->Write();
	// myFourmuChg0ARCmassWithanotherdimult9dot2->Write();
	// myARCFourMuVsanotherdimuMass->Write();
	// myFourmuChg0ARCmassandanotherdimultY1s->Write();
	// myFourmuChg0ARCmassandanotherdimultY1sEBE->Write();


	// myDalitzmY1smupmasssqVsmmumumasssqat18GeV->Write();
	// myDalitzmY1smupmasssqVsmmumumasssqatSideband->Write();

	// myMuMuMuMumassV1mumubelowV1withlightmeson->Write();
	// myMuMuMuMumassV1mumubelowV1nolightmeson->Write(); 
	// myMuMuMuMumassDiffV1mumubelowV1nolightmesoninaonthercombination->Write();

	//   myMuMu2Massat15dot7GeV->Write();
	//   myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->Write();
		
	//   myMuMuMuMumassV1mumubelowV1cowboyVscowboy->Write();
	//   myMuMuMuMumassV1mumubelowV1cowboyVsseagull->Write();
	//   myMuMuMuMumassV1mumubelowV1seagullVscowboy->Write();
	//   myMuMuMuMumassV1mumubelowV1seagullVsseagull->Write();
		
	//   myMuPPDeltapxpypz->Write();
	//   myMuMMDeltapxpypz->Write();
		
	//   myMuMuOnlyIso->Write();
	//   myMu1Isoat18dot5GeV->Write();
	//   myMu2Isoat18dot5GeV->Write();
	//   myMu3Isoat18dot5GeV->Write();
	//   myMu4Isoat18dot5GeV->Write();
		
		
	//   myMuMuMuMumassV1mumubelowV1LowSideShift->Write();
	//   myMuMuMuMumassV1mumubelowV1HighSideShift->Write();
		
	//   myMuMuMuMumassV1mumubelowV1LowSide->Write();
	//   myMuMuMuMumassV1mumubelowV1HighSide->Write();
		
	//   myMuMuMuMumassV1mumuWithVIso0dot1belowV1->Write();  
	//   myMuMuMuMumassV1mumuWithVIso0dot2belowV1->Write();  
	//   myMuMuMuMumassV1mumuWithVIso0dot5belowV1->Write();  

	//   myMuMuMuMumassV1highestmuWithVIso0dot1belowV1->Write(); 
	//   myMuMuMuMumassV1highestmuWithVIso0dot2belowV1->Write(); 
	//   myMuMuMuMumassV1highestmuWithVIso0dot5belowV1->Write(); 
		
	// 	 myMuMuMuMumMaxDeltaEta->Write();
	//   myMuMuMuMumassV1mumubelowV1->Write();
	//   myMuMuMuMumassDiffV1mumubelowV1->Write();
	//   myMuMumassforV1highpair->Write();
	//   myMuMumassforV1lowpair->Write();
	//   myMuMumassformumulowpair->Write();
	//   myMuMumassformumuhighpair->Write();
		
	//   myMuMuonlymass->Write();
		
	//   myV1VsMuMuMassBeforeVVmasshighpair->Write();
	//   myV1VsMuMuMassBeforeVVmasslowpair->Write();
	//   myV1VsMuMuMassAfterVVmassanotherpair->Write();
	//   myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->Write();
	//   myV1VsMuMuMassAfterVVmassanotherpairatSideband->Write();
	//   myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->Write();
	//   myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->Write();
		
	//   myMu1EtaVsPtat18dot5GeV->Write();
	//   myMu2EtaVsPtat18dot5GeV->Write();
	//   myMu3EtaVsPtat18dot5GeV->Write();
	//   myMu4EtaVsPtat18dot5GeV->Write();
	//   myMu1EtaVsPtatSideband->Write();
	//   myMu2EtaVsPtatSideband->Write();
	//   myMu3EtaVsPtatSideband->Write();
	//   myMu4EtaVsPtatSideband->Write();
	//   myMuMu1ptVsMuMu2ptat18dot5GeV->Write();
	//   myMuMu1ptVsMuMu2ptatSideband->Write();
		
	//   myMuMu1Massat18dot5GeV->Write();
	//   myMuMu1MassatSideband->Write();

	//   myMuMu2Massat18dot5GeV->Write();
	//   myMuMu2MassatSideband->Write();
	//   myFourMuPtatSideband->Write();
	//   myFourMuPtat18dot5GeV->Write();
	//   myFourMuRapidityat18dot5GeV->Write();
	//   myFourMuRapidityatSideband->Write();

	//   myMu1Ptat18dot5GeV->Write();
	//   myMu1PtatSideband->Write();
	//   myMu2Ptat18dot5GeV->Write();
	//   myMu2PtatSideband->Write();
	//   myMu3Ptat18dot5GeV->Write();
	//   myMu3PtatSideband->Write();
	//   myMu4Ptat18dot5GeV->Write();
	//   myMu4PtatSideband->Write();

	//   myMu21Ptstartat18dot5GeV->Write();
	//   myMu21PtstartatSideband->Write();
	//   myMu22Ptstartat18dot5GeV->Write();
	//   myMu22PtstartatSideband->Write();

	//   myMuMu1Ptat18dot5GeV->Write();
	//   myMuMu1PtatSideband->Write();
	//   myMuMu2Ptat18dot5GeV->Write();
	//   myMuMu2PtatSideband->Write();
	//   myMuMuPairsDihedralat18dot5GeV->Write();
	//   myMuMuPairsDihedralatSideband->Write();
						
	//   myMuMuPairsHelicityat18dot5GeV->Write();
	//   myMuMuPairsHelicityatSideband->Write();
	//   myMupmumu1Helicityat18dot5GeV->Write();
	//   myMupmumu1HelicityatSideband->Write();
	//   myMupmumu2Helicityat18dot5GeV->Write();
	//   myMupmumu2HelicityatSideband->Write();
	//   myFourMuFLSigat18dot5GeV->Write();
	//   myFourMuFLSigatSideband->Write();
	//   myMuMu1Ctauat18dot5GeV->Write();
	//   myMuMu1CtauatSideband->Write();
	//   myMuMu2Ctauat18dot5GeV->Write();
	//   myMuMu2CtauatSideband->Write();
	//   my4MuCtauatSideband->Write();
	//   my4MuCtauat18dot5GeV->Write();

 
}
