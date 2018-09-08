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

 
void myntuple::Loop()
{  
	
	// ofstream myoutfilesignal4Cristina("myfourmuonsignal4Cristina.txt");
	// ofstream myoutfilesignal7cats("myfourmuonsignalGigi7cats.txt");

	// TString mysignaloutname=outputname+"myfourmuonsignal.txt";
	ofstream myoutfilesignal("myfourmuonsignal.txt");

	// TString mysignaloutCERN=outputname+"myfourmuonsignalCERN.txt";
	// ofstream myoutfilesignalCERN(mysignaloutCERN);

	// ofstream myoutfileEvtNum("myfourmuonEvtNum.txt");
	// TString myevtmixname=outputname+"myfourmuonevtmix.txt";
	ofstream myoutfileevtmix("myfourmuonevtmix.txt");
	// ofstream myoutfiledimu("mydimuon.txt");

	// ofstream myoutfileJYforKamuran("myJYforKamuran.txt");
	// ofstream myoutfileJYforMaksat("myJYforMaksat.txt");


	// TString mysignal1outname=outputname+"myfourmuonsignal1.txt";
	// ofstream myoutfilesignal1(mysignal1outname);
	// TString mysignal2outname=outputname+"myfourmuonsignal2.txt";
	// ofstream myoutfilesignal2(mysignal2outname);


	TFile* myhbk = new TFile ("myhbk_MuOnia.root","recreate");
	// TFile* myhbk = new TFile (outputname,"recreate");


	//for ARC comments
	// ofstream myARCoutNmuTCHG("myARCoutNmuTCHG.txt");
	// myARCoutNmuTCHG<<"runNum "<<"lumiNum "<<"evtNum "<<"myGoodSoftMu "<<"myTotalChg "<<endl;

	// ofstream myARCoutNTightMu("myARCoutNTightMu.txt");
	// myARCoutNTightMu<<"runNum "<<"lumiNum "<<"evtNum "<<"myGoodTightMu "<<endl;

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

	// TH2F* myARCMuMuHighmasserrRapidityVsmasserrEBE = new TH2F("myARCMuMuHighmasserrRapidityVsmasserrEBE","myARCMuMuHighmasserrRapidityVsmasserrEBE",500,0,0.5, 500, 0, 0.5);  
	// myARCMuMuHighmasserrRapidityVsmasserrEBE->GetXaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(Rapidity) GeV");
	// myARCMuMuHighmasserrRapidityVsmasserrEBE->GetYaxis()->SetTitle("#sigma_{m(#mu^{+}#mu^{-})}(EBE) GeV");  

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

	// TH2F* myARCY1s2tightmuMu1etaVsMu2eta = new TH2F("myARCY1s2tightmuMu1etaVsMu2eta","myARCY1s2tightmuMu1etaVsMu2eta",25 ,0,2.5, 25, 0, 2.5);  
 
	TH1F* myMuMuChg0ARCmasswith2tightmuEE = new TH1F("myMuMuChg0ARCmasswith2tightmuEE","myMuMuChg0ARCmasswith2tightmuEE",100000,0,500.0);  
	TH1F* myMuMuChg0ARCmasswith2tightmuEB = new TH1F("myMuMuChg0ARCmasswith2tightmuEB","myMuMuChg0ARCmasswith2tightmuEB",100000,0,500.0);  
	TH1F* myMuMuChg0ARCmasswith2tightmuBB = new TH1F("myMuMuChg0ARCmasswith2tightmuBB","myMuMuChg0ARCmasswith2tightmuBB",100000,0,500.0);  
 
	TH1F* myAnotherMuMuChg0ARCwithY1sonthismumumass = new TH1F("myAnotherMuMuChg0ARCwithY1sonthismumumass","myAnotherMuMuChg0ARCwithY1sonthismumumass",100000,0,500.0);  
	TH1F* myFourmuChg0ARCmass = new TH1F("myFourmuChg0ARCmass","myFourmuChg0ARCmass",5000,0,500.0);  
	TH1F* myFourmuChg0ARCmassWithanotherdimult9dot2 = new TH1F("myFourmuChg0ARCmassWithanotherdimult9dot2","myFourmuChg0ARCmassWithanotherdimult9dot2",5000,0,500.0);  

 
	// TH2F* myARCFourMuVsanotherdimuMass = new TH2F("myARCFourMuVsanotherdimuMass","myARCFourMuVsanotherdimuMass",5000,0,500.0, 50000, 0, 500.0);  
	TH1F* myFourmuChg0ARCmassandanotherdimultY1s = new TH1F("myFourmuChg0ARCmassandanotherdimultY1s","myFourmuChg0ARCmassandanotherdimultY1s",5000,0,500.0);  
	TH1F* myFourmuChg0ARCmassandanotherdimultY1sEBE = new TH1F("myFourmuChg0ARCmassandanotherdimultY1sEBE","myFourmuChg0ARCmassandanotherdimultY1sEBE",5000,0,500.0);  
	
	// TH2F* myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV = new TH2F("myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV","myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV",4000,0,400.0, 10000, 0, 100.0);  



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
	// TH2F* myV1VsMuMuMassBeforeVVmasshighpair = new TH2F("myV1VsMuMuMassBeforeVVmasshighpair","myV1VsMuMuMassBeforeVVmasshighpair",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassBeforeVVmasshighpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassBeforeVVmasshighpair->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");  
	// TH2F* myV1VsMuMuMassBeforeVVmasslowpair = new TH2F("myV1VsMuMuMassBeforeVVmasslowpair","myV1VsMuMuMassBeforeVVmasslowpair",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassBeforeVVmasslowpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassBeforeVVmasslowpair->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");
	// TH2F* myV1VsMuMuMassAfterVVmassanotherpair = new TH2F("myV1VsMuMuMassAfterVVmassanotherpair","myV1VsMuMuMassAfterVVmassanotherpair",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassAfterVVmassanotherpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassAfterVVmassanotherpair->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");  


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
 
	// TH2F* myDalitzmY1smupmasssqVsmmumumasssqat18GeV = new TH2F("myDalitzmY1smupmasssqVsmmumumasssqat18GeV","myDalitzmY1smupmasssqVsmmumumasssqat18GeV",4000,0,400.0, 10000, 0, 100.0);  
	// TH2F* myDalitzmY1smupmasssqVsmmumumasssqatSideband = new TH2F("myDalitzmY1smupmasssqVsmmumumasssqatSideband","myDalitzmY1smupmasssqVsmmumumasssqatSideband",4000,0,400.0, 10000, 0, 100.0);  




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


	// TH2F* myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV","myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");

	// TH2F* myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV","myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");


	// TH2F* myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV","myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");
	// TH2F* myV1VsMuMuMassAfterVVmassanotherpairatSideband = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairatSideband","myV1VsMuMuMassAfterVVmassanotherpairatSideband",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassAfterVVmassanotherpairatSideband->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassAfterVVmassanotherpairatSideband->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");


	// TH2F* myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull = new TH2F("myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull","myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull",5000,0,100.0, 5000, 0, 100.0);  
	// myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-})_{h} GeV");
	// myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->GetYaxis()->SetTitle("m(#mu^{+}#mu^{-})_{l} GeV");

	TH1F* myMuMu2Massat15dot7GeV = new TH1F("myMuMu2Massat15dot7GeV","myMuMu2Massat15dot7GeV",200,0,10.0);


	TH1F* myMu21Ptstartat18dot5GeV = new TH1F("myMu21Ptstartat18dot5GeV","myMu21Ptstartat18dot5GeV",50,0,50.0);
	TH1F* myMu21PtstartatSideband = new TH1F("myMu21PtstartatSideband","myMu21PtstartatSideband",50,0,50.0);
	TH1F* myMu22Ptstartat18dot5GeV = new TH1F("myMu22Ptstartat18dot5GeV","myMu22Ptstartat18dot5GeV",50,0,50.0);
	TH1F* myMu22PtstartatSideband = new TH1F("myMu22PtstartatSideband","myMu22PtstartatSideband",50,0,50.0);
 

	// TH2F* myMuMu1ptVsMuMu2ptat18dot5GeV = new TH2F("myMuMu1ptVsMuMu2ptat18dot5GeV","myMuMu1ptVsMuMu2ptat18dot5GeV",20,0,20.0, 20, 0, 20.0);  
	// myMuMu1ptVsMuMu2ptat18dot5GeV->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{high} GeV");
	// myMuMu1ptVsMuMu2ptat18dot5GeV->GetYaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{low} GeV");
	// TH2F* myMuMu1ptVsMuMu2ptatSideband = new TH2F("myMuMu1ptVsMuMu2ptatSideband","myMuMu1ptVsMuMu2ptatSideband",20,0,20.0, 20, 0, 20.0);  
	// myMuMu1ptVsMuMu2ptatSideband->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{high} GeV");
	// myMuMu1ptVsMuMu2ptatSideband->GetYaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{low} GeV");



	// TH2F* myMu1EtaVsPtat18dot5GeV = new TH2F("myMu1EtaVsPtat18dot5GeV","myMu1EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	// TH2F* myMu2EtaVsPtat18dot5GeV = new TH2F("myMu2EtaVsPtat18dot5GeV","myMu2EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	// TH2F* myMu3EtaVsPtat18dot5GeV = new TH2F("myMu3EtaVsPtat18dot5GeV","myMu3EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	// TH2F* myMu4EtaVsPtat18dot5GeV = new TH2F("myMu4EtaVsPtat18dot5GeV","myMu4EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
 
	// TH2F* myMu1EtaVsPtatSideband = new TH2F("myMu1EtaVsPtatSideband","myMu1EtaVsPtatSideband",60,-3,3, 300,0,30);
	// TH2F* myMu2EtaVsPtatSideband = new TH2F("myMu2EtaVsPtatSideband","myMu2EtaVsPtatSideband",60,-3,3, 300,0,30);
	// TH2F* myMu3EtaVsPtatSideband = new TH2F("myMu3EtaVsPtatSideband","myMu3EtaVsPtatSideband",60,-3,3, 300,0,30);
	// TH2F* myMu4EtaVsPtatSideband = new TH2F("myMu4EtaVsPtatSideband","myMu4EtaVsPtatSideband",60,-3,3, 300,0,30);

	
	// TH1F* myMu21PtstartatSideband = new TH1F("myMu21PtstartatSideband","myMu21PtstartatSideband",50,0,50.0);
	// TH1F* myMu22Ptstartat18dot5GeV = new TH1F("myMu22Ptstartat18dot5GeV","myMu22Ptstartat18dot5GeV",50,0,50.0);
	// TH1F* myMu22PtstartatSideband = new TH1F("myMu22PtstartatSideband","myMu22PtstartatSideband",50,0,50.0);
	

	// TH2F* myMuMu1ptVsMuMu2ptat18dot5GeV = new TH2F("myMuMu1ptVsMuMu2ptat18dot5GeV","myMuMu1ptVsMuMu2ptat18dot5GeV",20,0,20.0, 20, 0, 20.0);  
	// myMuMu1ptVsMuMu2ptat18dot5GeV->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{high} GeV");
	// myMuMu1ptVsMuMu2ptat18dot5GeV->GetYaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{low} GeV");
	// TH2F* myMuMu1ptVsMuMu2ptatSideband = new TH2F("myMuMu1ptVsMuMu2ptatSideband","myMuMu1ptVsMuMu2ptatSideband",20,0,20.0, 20, 0, 20.0);  
	// myMuMu1ptVsMuMu2ptatSideband->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{high} GeV");
	// myMuMu1ptVsMuMu2ptatSideband->GetYaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{low} GeV");



	// TH2F* myMu1EtaVsPtat18dot5GeV = new TH2F("myMu1EtaVsPtat18dot5GeV","myMu1EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	// TH2F* myMu2EtaVsPtat18dot5GeV = new TH2F("myMu2EtaVsPtat18dot5GeV","myMu2EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	// TH2F* myMu3EtaVsPtat18dot5GeV = new TH2F("myMu3EtaVsPtat18dot5GeV","myMu3EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	// TH2F* myMu4EtaVsPtat18dot5GeV = new TH2F("myMu4EtaVsPtat18dot5GeV","myMu4EtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
 
	// TH2F* myMu1EtaVsPtatSideband = new TH2F("myMu1EtaVsPtatSideband","myMu1EtaVsPtatSideband",60,-3,3, 300,0,30);
	// TH2F* myMu2EtaVsPtatSideband = new TH2F("myMu2EtaVsPtatSideband","myMu2EtaVsPtatSideband",60,-3,3, 300,0,30);
	// TH2F* myMu3EtaVsPtatSideband = new TH2F("myMu3EtaVsPtatSideband","myMu3EtaVsPtatSideband",60,-3,3, 300,0,30);
	// TH2F* myMu4EtaVsPtatSideband = new TH2F("myMu4EtaVsPtatSideband","myMu4EtaVsPtatSideband",60,-3,3, 300,0,30);
	

	TH1F* myVtxProbat18dot5GeV = new TH1F("myVtxProbat18dot5GeV","myVtxProbat18dot5GeV",1000,0.0,1.0);
	TH1F* myVtxProbatatSideband = new TH1F("myVtxProbatatSideband","myVtxProbatatSideband",1000,0.0,1.0);
	

	TH1F* myMuMumassinFourmuon = new TH1F("myMuMumassinFourmuon","myMuMumassinFourmuon",100000,0,500.0);  
	myMuMumassinFourmuon->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");



	TH1F* myFourMuGenMass = new TH1F("myFourMuGenMass","myFourMuGenMass",10000,0,1000.0);
	TH2F* myMu4EtaVsPtatGen = new TH2F("myMu4EtaVsPtatGen","myMu4EtaVsPtatGen",60,-3,3, 300,0,30);
  	TH2F* myMu4EtaVsPtatReco = new TH2F("myMu4EtaVsPtatReco","myMu4EtaVsPtatReco",60,-3,3, 300,0,30);
 


	
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
			// myARCoutNmuTCHG<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myGoodSoftMu<<" "<<myTotalChg<<endl;

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
					

		// collect gen mu information
		vector<TLorentzVector> genMup4vect;
		vector<bool> isAcceptedMuon;
		bool passedGenAcceptanceCut = true;

		if(MC_YmuPx->size() == 2 && MC_HmuPx->size()==2)
		{
			for(int i = 0; i<MC_YmuPx->size(); i++)
			{
				TLorentzVector Genmu;
				float raw_muPx = (*MC_YmuPx)[i];
				float raw_muPy = (*MC_YmuPy)[i];
				float raw_muPz = (*MC_YmuPz)[i];
				Genmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);
				genMup4vect.push_back( Genmu );


				if(
					(fabs(Genmu.Eta())<1.2 && Genmu.Pt()>3.8)
					|| (  Genmu.Eta()>1.2 && Genmu.Eta()<1.8 && Genmu.Pt() >= (-(2.0/0.6)*Genmu.Eta()+7.8)    )
					|| (  Genmu.Eta()>-1.8 && Genmu.Eta()<-1.2 && Genmu.Pt() >= ( (2.0/0.6)*Genmu.Eta()+7.8)    )
					|| (  fabs(Genmu.Eta())<2.3 && fabs(Genmu.Eta()) >1.8 && Genmu.Pt()>1.8 )

					)
					{
						isAcceptedMuon.push_back(true);
						myMu4EtaVsPtatGen->Fill( Genmu.Eta(), Genmu.Pt() );
					}
				else isAcceptedMuon.push_back(false);



			}

			for(int i = 0; i<MC_HmuPx->size(); i++)
			{
				TLorentzVector Genmu;
				float raw_muPx = (*MC_HmuPx)[i];
				float raw_muPy = (*MC_HmuPy)[i];
				float raw_muPz = (*MC_HmuPz)[i];
				Genmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, muon_mass);
				genMup4vect.push_back( Genmu );

				if(
					(fabs(Genmu.Eta())<1.2 && Genmu.Pt()>3.8)
					|| (  Genmu.Eta()>1.2 && Genmu.Eta()<1.8 && Genmu.Pt() >= (-(2.0/0.6)*Genmu.Eta()+7.8)    )
					|| (  Genmu.Eta()>-1.8 && Genmu.Eta()<-1.2 && Genmu.Pt() >= ( (2.0/0.6)*Genmu.Eta()+7.8)    )
					|| (  fabs(Genmu.Eta())<2.3 && fabs(Genmu.Eta()) >1.8 && Genmu.Pt()>1.8 )

					)
					{
						isAcceptedMuon.push_back(true);
						myMu4EtaVsPtatGen->Fill( Genmu.Eta(), Genmu.Pt() );
					}
				else isAcceptedMuon.push_back(false);



			}
			for (int i = 0; i < isAcceptedMuon.size(); i++)
			{
				passedGenAcceptanceCut =  passedGenAcceptanceCut*isAcceptedMuon[i];
			}


			// my gen four mu mass

			// cout<<genMup4vect.size()<<endl;

			float mygenfourmumass = (genMup4vect[0]+ genMup4vect[1] + genMup4vect[2] + genMup4vect[3] + genMup4vect[4]).M();


			// if(passedGenAcceptanceCut) myFourMuGenMass->Fill( mygenfourmumass );
			myFourMuGenMass->Fill( mygenfourmumass );


		}



		///////////////////////////////////// four muon signal /////////////////////////////////////////////
		///////////////////////////////////// four muon signal /////////////////////////////////////////////
		///////////////////////////////////// four muon signal /////////////////////////////////////////////
		///////////////////////////////////// four muon signal /////////////////////////////////////////////
		///////////////////////////////////// four muon signal /////////////////////////////////////////////

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
						// myoutfiledimu<<myMupMumMass[i][j]<<" "<<myMupMumMassErr[i][j]<<endl;
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


				&& (*MyFourMuonVtxCL)[myFourMuIdx]>=0.05
				// && (*MyFourMuonVtxCL)[myFourMuIdx]>=1e-30

				//MuOnia data
				// && ( TrigThreeMuonJpsi || TrigThreeMuonUpsi ) 
				&& TrigThreeMuonUpsi
						 

				//DoubleMu data
				
				// && !( TrigThreeMuonJpsi || TrigThreeMuonUpsi )
				// && TrigTripleMu5
				


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
							// myV1VsMuMuMassBeforeVVmasshighpair->Fill((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
							// check if muon pt is sorted.  Yeah, it is.
							// cout<<"rawMup4vect[0] pt="<<rawMup4vect[0].Pt()<<", (rawMup4vect[1]="<<rawMup4vect[1].Pt()<<", rawMup4vect[2].Pt()="<<rawMup4vect[2].Pt()<<", rawMup4vect[3].Pt()="<<rawMup4vect[3].Pt()<<endl;
							
						}
						if( mypidx==2 )
						{
							myMuMumassforV1lowpair->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );		      
							myMuMumassformumulowpair->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
							// myV1VsMuMuMassBeforeVVmasslowpair->Fill((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M(),  (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
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
							// myARCoutNTightMu<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myNumGoodTightMuon<<endl;
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
									// myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu11p11].Eta()),  fabs(rawMup4vect[mu11p12].Eta()) );
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
									// myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu12p11].Eta()),  fabs(rawMup4vect[mu12p12].Eta()) );
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
									// myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu21p11].Eta()),  fabs(rawMup4vect[mu21p12].Eta()) );
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
									// myARCY1s2tightmuMu1etaVsMu2eta->Fill( fabs(rawMup4vect[mu22p11].Eta()),  fabs(rawMup4vect[mu22p12].Eta()) );
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
											// myARCMuMuHighmasserrRapidityVsmasserrEBE->Fill( myY1sResthis, myMupMumMassErr[myi][myj] );
											myAnotherMuMuChg0ARCwithY1sonthismumumass->Fill( (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M() );
											myFourmuChg0ARCmass->Fill( myfourmuonmass );
											if( (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M()<9.2 )
											{
												myFourmuChg0ARCmassWithanotherdimult9dot2->Fill( myfourmuonmass );
											}

											// myARCFourMuVsanotherdimuMass->Fill( myfourmuonmass, (fitMup4vect[ muIdxanotherARCp11 ]+ fitMup4vect[ muIdxanotherARCp12 ]).M() );
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
							// if( myfourmuonmass>18.0 && myfourmuonmass<19.0)
							// {
							// 	myARCDalitzmY1smupmasssqVsmmumumasssqat18GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );
							// }
							NumDupARCEBE++;
						}
						//dealing ARC comments end		  

						//test for Kamuran JY, keep two combinations for test purpose
						// if( rawMup4vect[ muIdxp11 ].Pt()>3.5 && rawMup4vect[ muIdxp12 ].Pt()>3.5
						// 	&&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > 8.0 &&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<11.0
						// 	&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >2.5 && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<3.5
						// 	)
						// {
						// 	myoutfileJYforKamuran<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<(NumCanforKamuranCHK++)<<endl;
						// }
						// // end test for Kamuran JY
						// // test for Maksat YY, keep two combinations for test purpose
						// if( rawMup4vect[ muIdxp11 ].Pt()>3.5 && rawMup4vect[ muIdxp12 ].Pt()>3.5
						// 	&& rawMup4vect[ muIdxp21 ].Pt()>3.5 && rawMup4vect[ muIdxp22 ].Pt()>3.5
						// 	&& (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() > 8.0 &&  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<11.0
						// 	&& (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() > 8.0 && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<11.0
						// 	)
						// {
						// 	myoutfileJYforMaksat<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<" "<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<" "<<(NumCanforMaksatCHK++)<<endl;
						// }
						// end test for Kamuran JY

						bool mu11acc = false;
						bool mu12acc = false;
						bool mu21acc = false;
						bool mu22acc = false;

						if ( 
							(fabs(fitMup4vect[muIdxp11].Eta())<1.2 && fitMup4vect[muIdxp11].Pt()>3.8)
							|| (  fitMup4vect[muIdxp11].Eta()>1.2 && fitMup4vect[muIdxp11].Eta()<1.8 && fitMup4vect[muIdxp11].Pt() >= (-(2.0/0.6)*fitMup4vect[muIdxp11].Eta()+7.8)    )
							|| (  fitMup4vect[muIdxp11].Eta()>-1.8 && fitMup4vect[muIdxp11].Eta()<-1.2 && fitMup4vect[muIdxp11].Pt() >= ( (2.0/0.6)*fitMup4vect[muIdxp11].Eta()+7.8)    )
							|| (  fabs(fitMup4vect[muIdxp11].Eta())<2.3 && fabs(fitMup4vect[muIdxp11].Eta()) >1.8 && fitMup4vect[muIdxp11].Pt()>1.8 )
							) mu11acc = true;

						if ( 
							(fabs(fitMup4vect[muIdxp12].Eta())<1.2 && fitMup4vect[muIdxp12].Pt()>3.8)
							|| (  fitMup4vect[muIdxp12].Eta()>1.2 && fitMup4vect[muIdxp12].Eta()<1.8 && fitMup4vect[muIdxp12].Pt() >= (-(2.0/0.6)*fitMup4vect[muIdxp12].Eta()+7.8)    )
							|| (  fitMup4vect[muIdxp12].Eta()>-1.8 && fitMup4vect[muIdxp12].Eta()<-1.2 && fitMup4vect[muIdxp12].Pt() >= ( (2.0/0.6)*fitMup4vect[muIdxp12].Eta()+7.8)    )
							|| (  fabs(fitMup4vect[muIdxp12].Eta())<2.3 && fabs(fitMup4vect[muIdxp12].Eta()) >1.8 && fitMup4vect[muIdxp12].Pt()>1.8 )
							) mu12acc = true;

						if ( 
							(fabs(fitMup4vect[muIdxp21].Eta())<1.2 && fitMup4vect[muIdxp21].Pt()>3.8)
							|| (  fitMup4vect[muIdxp22].Eta()>1.2 && fitMup4vect[muIdxp21].Eta()<1.8 && fitMup4vect[muIdxp21].Pt() >= (-(2.0/0.6)*fitMup4vect[muIdxp21].Eta()+7.8)    )
							|| (  fitMup4vect[muIdxp21].Eta()>-1.8 && fitMup4vect[muIdxp21].Eta()<-1.2 && fitMup4vect[muIdxp21].Pt() >= ( (2.0/0.6)*fitMup4vect[muIdxp21].Eta()+7.8)    )
							|| (  fabs(fitMup4vect[muIdxp21].Eta())<2.3 && fabs(fitMup4vect[muIdxp21].Eta()) >1.8 && fitMup4vect[muIdxp21].Pt()>1.8 )
							) mu21acc = true;
						if ( 
							(fabs(fitMup4vect[muIdxp22].Eta())<1.2 && fitMup4vect[muIdxp22].Pt()>3.8)
							|| (  fitMup4vect[muIdxp22].Eta()>1.2 && fitMup4vect[muIdxp22].Eta()<1.8 && fitMup4vect[muIdxp22].Pt() >= (-(2.0/0.6)*fitMup4vect[muIdxp22].Eta()+7.8)    )
							|| (  fitMup4vect[muIdxp22].Eta()>-1.8 && fitMup4vect[muIdxp22].Eta()<-1.2 && fitMup4vect[muIdxp22].Pt() >= ( (2.0/0.6)*fitMup4vect[muIdxp22].Eta()+7.8)    )
							|| (  fabs(fitMup4vect[muIdxp22].Eta())<2.3 && fabs(fitMup4vect[muIdxp22].Eta()) >1.8 && fitMup4vect[muIdxp22].Pt()>1.8 )
							) mu22acc = true;
				
				
				


						// VV MASS CUT HERE //

						if(1
							&& myVVmasscut
							&& passedGenAcceptanceCut
							&& mu11acc && mu12acc && mu21acc && mu22acc
							)
						{
							if(NumDup<1) 
							{			
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

								

								// myoutfilesignalCERN<<runNum<<" "<<evtNum<<" "<<lumiNum<<" "<<myfourmuonmass<<endl;


								int theotherdimuidx=2; if(mypidx==2) {theotherdimuidx=1;}

								



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
									// myoutfilesignal1<<myfourmuonmass<<" "<<( myfourmuonmass-(fitMup4vect[ muIdxp11 ]+fitMup4vect[ muIdxp12 ]).M()+mymV)<<" "<<(*MyFourMuonMassErr)[myFourMuIdx]<<endl;
									myMuMumassinFourmuon->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()   );



									myMu4EtaVsPtatReco->Fill(fitMup4vect[0].Eta(),fitMup4vect[0].Pt());
									myMu4EtaVsPtatReco->Fill(fitMup4vect[1].Eta(),fitMup4vect[1].Pt());
									myMu4EtaVsPtatReco->Fill(fitMup4vect[2].Eta(),fitMup4vect[2].Pt());
									myMu4EtaVsPtatReco->Fill(fitMup4vect[3].Eta(),fitMup4vect[3].Pt());


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
										<<" "<<(*MyFourMuonVtxCL)[myFourMuIdx]
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


	


									if( myfourmuonmass>=18.0 && myfourmuonmass<=19.0)
									{


										myMuMu1Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );
										myMuMu2Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );

										myMu1Ptat18dot5GeV->Fill( rawMup4vect[0].Pt() );
										myMu2Ptat18dot5GeV->Fill( rawMup4vect[1].Pt() );
										myMu3Ptat18dot5GeV->Fill( rawMup4vect[2].Pt() );
										myMu4Ptat18dot5GeV->Fill( rawMup4vect[3].Pt() );
										myVtxProbat18dot5GeV->Fill( (*MyFourMuonVtxCL)[myFourMuIdx] );

									}
									if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0)    //background in signal area is 1/1.8 of sideband
										||
										(myfourmuonmass>=20.0 && myfourmuonmass<=21.0) 
										) 
									{

										myMuMu1MassatSideband->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );
										myMuMu2MassatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
										
										myMu1PtatSideband->Fill( rawMup4vect[0].Pt() );
										myMu2PtatSideband->Fill( rawMup4vect[1].Pt() );
										myMu3PtatSideband->Fill( rawMup4vect[2].Pt() );
										myMu4PtatSideband->Fill( rawMup4vect[3].Pt() );
										myVtxProbatatSideband->Fill( (*MyFourMuonVtxCL)[myFourMuIdx] );
	

									}
									
								}
								else
								{
									myMuMuMuMumassV1mumubelowV1withlightmeson->Fill( myfourmuonmass );
									// myoutfilesignal2<<myfourmuonmass<<" "<<(*MyFourMuonMassErr)[myFourMuIdx]<<endl;
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
										// myV1VsMuMuMassAfterVVmassanotherpairat15dot7GeVseagullandseagull->Fill( (fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() ); 
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
											
								// myV1VsMuMuMassAfterVVmassanotherpair->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() ); 
								

								if( myfourmuonmass>=18.0 && myfourmuonmass<=19.0)
								{
									
									//myoutfileEvtNum<<runNum<<" "<<lumiNum<<" "<<evtNum<<" "<<myfourmuonmass<<", "<<rawMup4vect[ muIdxp11 ].Pt()<<" "<<rawMup4vect[ muIdxp11 ].Eta()<<" "<<rawMup4vect[ muIdxp11 ].Phi()<<", "<<rawMup4vect[ muIdxp12 ].Pt()<<" "<<rawMup4vect[ muIdxp12 ].Eta()<<" "<<rawMup4vect[ muIdxp12 ].Phi()<<", "<<rawMup4vect[ muIdxp21 ].Pt()<<" "<<rawMup4vect[ muIdxp21 ].Eta()<<" "<<rawMup4vect[ muIdxp21 ].Phi()<<", "<<rawMup4vect[ muIdxp22 ].Pt()<<" "<<rawMup4vect[ muIdxp22 ].Eta()<<" "<<rawMup4vect[ muIdxp22 ].Phi()<<endl;

									// myDalitzmY1smupmasssqVsmmumumasssqat18GeV->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );


									myMu1Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] );
									myMu2Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] );
									myMu3Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] );
									myMu4Isoat18dot5GeV->Fill( (*muIsoratio)[ (*MyFourMuonMu4Idx)[myFourMuIdx]] );
									

									// myMuMu1Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );

									// myMuMu2Massat18dot5GeV->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );

									myFourMuPtat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
									myFourMuRapidityat18dot5GeV->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

									// myMu1EtaVsPtat18dot5GeV->Fill(  rawMup4vect[0].Eta(), rawMup4vect[0].Pt() ); 
									// myMu2EtaVsPtat18dot5GeV->Fill(  rawMup4vect[1].Eta(), rawMup4vect[1].Pt() ); 
									// myMu3EtaVsPtat18dot5GeV->Fill(  rawMup4vect[2].Eta(), rawMup4vect[2].Pt() ); 
									// myMu4EtaVsPtat18dot5GeV->Fill(  rawMup4vect[3].Eta(), rawMup4vect[3].Pt() );
									
									// myMuMu1ptVsMuMu2ptat18dot5GeV->Fill(  (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt(), (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
									
									// myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

									// if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 )
									// {
									// 	myV1VsMuMuMassAfterVVmassanotherpairat18dot5GeVmumu2massgt8GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
									// }
									
									// myMu1Ptat18dot5GeV->Fill( rawMup4vect[0].Pt() );
									// myMu2Ptat18dot5GeV->Fill( rawMup4vect[1].Pt() );
									// myMu3Ptat18dot5GeV->Fill( rawMup4vect[2].Pt() );
									// myMu4Ptat18dot5GeV->Fill( rawMup4vect[3].Pt() );

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

								if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0)    //background in signal area is 1/1.8 of sideband
									||
									(myfourmuonmass>=20.0 && myfourmuonmass<=21.0) 
									  ) 
								{

									// myDalitzmY1smupmasssqVsmmumumasssqatSideband->Fill(  (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ] + fitMup4vect[ muIdxp21 ]  ).M2(), (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M2()  );


									// myMuMu1MassatSideband->Fill( (fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() );

									// myMuMu2MassatSideband->Fill( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() );
									myFourMuPtatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );
									myFourMuRapidityatSideband->Fill( (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ] + rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Rapidity() );

									// myMu1EtaVsPtatSideband->Fill(  rawMup4vect[0].Eta(), rawMup4vect[0].Pt() ); 
									// myMu2EtaVsPtatSideband->Fill(  rawMup4vect[1].Eta(), rawMup4vect[1].Pt() ); 
									// myMu3EtaVsPtatSideband->Fill(  rawMup4vect[2].Eta(), rawMup4vect[2].Pt() ); 
									// myMu4EtaVsPtatSideband->Fill(  rawMup4vect[3].Eta(), rawMup4vect[3].Pt() );
									
									// myMuMu1ptVsMuMu2ptatSideband->Fill(  (rawMup4vect[ muIdxp11 ]+rawMup4vect[ muIdxp12 ]).Pt(), (rawMup4vect[ muIdxp21 ]+rawMup4vect[ muIdxp22 ]).Pt() );

									// myV1VsMuMuMassAfterVVmassanotherpairatSideband->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );

									// if ( (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() >= 8.0 )
									// {
									// 	myV1VsMuMuMassAfterVVmassanotherpairatSidebandmumu2massgt8GeV->Fill((fitMup4vect[ muanotherIdxp11 ]+ fitMup4vect[ muanotherIdxp12 ]).M(), (fitMup4vect[ muanotherIdxp21 ]+ fitMup4vect[ muanotherIdxp22 ]).M() );
									// }

									// myMu1PtatSideband->Fill( rawMup4vect[0].Pt() );
									// myMu2PtatSideband->Fill( rawMup4vect[1].Pt() );
									// myMu3PtatSideband->Fill( rawMup4vect[2].Pt() );
									// myMu4PtatSideband->Fill( rawMup4vect[3].Pt() );

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

	
 
}
