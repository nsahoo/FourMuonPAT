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
//order mode, 2--order by higher mass for each combination,  (m(11)-mymV)<(m(21)-mymV), 
//order ==3 for by mV mass, (m(11)-mV)<(m(12)-mV), (m(21)-mV)<(m(22)-mV),  (m(11)-mymV)< (m(21)-mymV),
#define myordermode 1


//11=Y(1S) mumu <Y(1S), 12=Y(1S)+X, 13=Y(1s)+Jpsi, 14=Y(1s)+Y(1S), 15=Y(1S) mumu mass no limit
//21=Jpsi+Jpsi, 22=Jpsi+ phi, 23=Jpsi+ omega, 24=Jpsi+ Gammastar, 25=Jpsi+Jpsi*
//31=Psi2s+Jpsi,
//41=Y(2S) Y(1S)*, 42=Y(2S)+X
//51=X+Jpsi, m(X)>m(Jpsi); 52=X+Jpsi, m(X)>m(Jpsi) && m(X)< 9 
//91=ZZ* to test Higgs, remove trigger requirement for this test
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
  //	if( matchUpsiTrig ) cout<<"*muIsUpsTrigMatch 1="<<matchUpsiTrig<<endl; 
  //	if( matchJpsiTrig ) cout<<"*muIsJpsTrigMatch 1="<<matchJpsiTrig<<endl; 

  //ofstream myoutfilesignal("myfourmuonsignal.txt");
  //ofstream myoutfileAll("myfourmuonAll.txt");
  //ofstream myoutfileEvtNum("myfourmuonEvtNum.txt");
  //ofstream myoutfileevtmix("myfourmuonevtmix.txt");

  TFile* myhbk = new TFile ("myhbk_MuOnia.root","recreate");

  TH1F* myMuMuonlymass = new TH1F("myMuMuonlymass","myMuMuonlymass",100000,0,500.0);  
  myMuMuonlymass->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) GeV");


 TH1F* myMuMuMuMumassV1mumubelowV1 = new TH1F("myMuMuMuMumassV1mumubelowV1","myMuMuMuMumassV1mumubelowV1",10000,0,1000.0);
  myMuMuMuMumassV1mumubelowV1->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");




  
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

  
    bool TrigThreeMuonJpsi=false;
    bool TrigThreeMuonUpsi=false;


    for(int i=0; i!=TrigRes->size(); ++i){ 
 
      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
          TrigThreeMuonJpsi=true;
        }

      if(TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        { 
          TrigThreeMuonUpsi=true;
        }

  
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

	vector<TLorentzVector> rawMup4vect;
	TLorentzVector Rawmu;
	float raw_muPx = (*muPx)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muPy = (*muPy)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muPz = (*muPz)[ (*MyFourMuonMu1Idx)[myFourMuIdx] ];
	float raw_muM  =0.10565837; 
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);    
	rawMup4vect.push_back( Rawmu );
	raw_muPx = (*muPx)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu2Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);  rawMup4vect.push_back( Rawmu );
	raw_muPx = (*muPx)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu3Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);  rawMup4vect.push_back( Rawmu );
	raw_muPx = (*muPx)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ]; raw_muPy = (*muPy)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];raw_muPz = (*muPz)[ (*MyFourMuonMu4Idx)[myFourMuIdx] ];
	Rawmu.SetXYZM( raw_muPx, raw_muPy,raw_muPz, raw_muM);  rawMup4vect.push_back( Rawmu );

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

	//myCombId[i][j],  i=0->Y(1S) mu+mu-;  i=1->J/psi mu+mu-; 
	//change the order to make myCombIdx[i][0] to store mu+mu+ and mu-mu- pair
	//myCombIdx[i][1] & myCombIdx[i][2] to store two pairs to satisfy the following condition:
	//|myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][1]-pair2- m(V)| ,  V=Y(1S), J/psi, 
	//|myCombIdx[i][1]-pair1 mass - m(V)| < |myCombIdx[i][2]-pair1- m(V)| ,  V=Y(1S), J/psi
	
	PairedMuonIdx myCombIdx[3];   
	//	double mymV[2]={9.46,3.0967};
	double mymV=9.46;   //3.096919 for jpsi, 3.686 for psi2s, 9.46 for Y(1s),10.02326,10.3552

	myCombIdx[0].p11=0; myCombIdx[0].p12=1; myCombIdx[0].p21=2; myCombIdx[0].p22=3; 
	myCombIdx[1].p11=0; myCombIdx[1].p12=2; myCombIdx[1].p21=1; myCombIdx[1].p22=3; 
	myCombIdx[2].p11=0; myCombIdx[2].p12=3; myCombIdx[2].p21=1; myCombIdx[2].p22=2; 
	
	for(int i=0; i<3; i++) {
	  if( (fitMuCharge[ myCombIdx[i].p11 ]+ fitMuCharge[ myCombIdx[i].p12 ])!=0  ) swap_one_paired_pair( myCombIdx[i] ); 
	}


	float myMupMumVtxProb[3][2];   //[2]-> V=Y1s, J/psi; 3-> 3 combinations; 2->pair 1 & pair 2
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



	//
	//muon ID 
	int isTightMuon[4], isLooseMuon[4], myMuIso[4];
	isLooseMuon[0]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isLooseMuon[1]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	isLooseMuon[2]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isLooseMuon[3]=(*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
	isTightMuon[0]=(*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]];   isTightMuon[1]=(*muIsGoodTightMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]];
	isTightMuon[2]=(*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]];   isTightMuon[3]=(*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];

	//	float myfourmuonmass=(*MyFourMuonMass)[myFourMuIdx];
	float myfourmuonmass= (fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).M();
	

	// (N.B. "All" condition not saved => muQual  must have 1 for GlobalMu (1), TrackerMu(3). TMArbitrated(4), TMLastStationLoose (7)
       int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];
       int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];


	
	TLorentzVector myRaw4Mup4=rawMup4vect[0]+rawMup4vect[1]+rawMup4vect[2]+rawMup4vect[3];

	float myetacut=2.4;   //1.6, there is a bump at 31 GeV for Y(1S) mumu, default 2.4
	float minMuPt=2.0;  //2.0--default 1.5;2,5;3.0;3.5;  2.2
		
	if(1
	   
	   && (*MyFourMuonVtxCL)[myFourMuIdx]>=0.05   //	   
	   && ( TrigThreeMuonJpsi || TrigThreeMuonUpsi )    //for three muon trigger, default trigger, remove it for Higgs test
	   && fabs(rawMup4vect[0].Eta())<=myetacut && fabs(rawMup4vect[1].Eta())<=myetacut
	   && fabs(rawMup4vect[2].Eta())<=myetacut && fabs(rawMup4vect[3].Eta())<=myetacut
	   && fabs( fitMuCharge[0]+fitMuCharge[1]+ fitMuCharge[2]+fitMuCharge[3] )==2
	   )
	  {	    
	    
	    int NumDup=0;   //we have two pairs, but only fill one time if at least one pair satisfy it
	    for(int mypidx=0; mypidx<3; mypidx++) //loop over the two combinations with zero ch
	      {
		int muIdxp11, muIdxp12, muIdxp21, muIdxp22;
		muIdxp11=myCombIdx[mypidx].p11; muIdxp12=myCombIdx[mypidx].p12; muIdxp21=myCombIdx[mypidx].p21; muIdxp22=myCombIdx[mypidx].p22;

	
		//for this selected pair
		TLorentzVector mymumu1p4=rawMup4vect[ muIdxp11 ]+ rawMup4vect[ muIdxp12 ];
		TLorentzVector mymumu2p4=rawMup4vect[ muIdxp21 ]+ rawMup4vect[ muIdxp22 ];
		double myrap1=fabs(0.5*log( (mymumu1p4.E() + mymumu1p4.Pz())/(mymumu1p4.E() - mymumu1p4.Pz()) ) );
		double myrap2=fabs(0.5*log( (mymumu2p4.E() + mymumu2p4.Pz())/(mymumu2p4.E() - mymumu2p4.Pz()) ) );
		double myY1sResp1=0.0572+0.03602*myrap1;		
		double myY1sResp2=0.0572+0.03602*myrap2;
						
		if(1
		   
		   && myMupMumVtxProb[mypidx][0]>=0.005 && myMupMumVtxProb[mypidx][1]>=0.005
		   && isLooseMuon[ muIdxp11 ] &&  isLooseMuon[ muIdxp12 ] //check tomorrow
		   && isLooseMuon[ muIdxp21 ] &&  isLooseMuon[ muIdxp22 ] //check tomorrow
		   && rawMup4vect[ muIdxp11 ].Pt()>=minMuPt && rawMup4vect[ muIdxp12 ].Pt()>=minMuPt
		   && rawMup4vect[ muIdxp21 ].Pt()>=minMuPt && rawMup4vect[ muIdxp22 ].Pt()>=minMuPt
		   
		   ) {
		  
		  cout<<"mypidx="<<mypidx<<", mumu1 mass="<<(fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M()<<", mumu2 mass="<<(fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M()<<","<<fitMuCharge[ muIdxp11 ]<<","<<fitMuCharge[ muIdxp12 ]<<","<<fitMuCharge[ muIdxp21 ]<<","<<fitMuCharge[ muIdxp22 ]<<","<<(fitMuCharge[0]+fitMuCharge[1]+fitMuCharge[2]+fitMuCharge[3]) <<","<<myMupMumVtxProb[mypidx][0]<<","<<myMupMumVtxProb[mypidx][1]<<endl;	
		  //apply mass cut 
		  float mynsigma=3.0;		  		  

		  if(1		     
		     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ changed by suleyman~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

			 // &&  fabs((fitMup4vect[ muIdxp11 ]+ fitMup4vect[ muIdxp12 ]).M() -mymV )<= mynsigma*myY1sResp1 
		     // && (fitMup4vect[ muIdxp21 ]+ fitMup4vect[ muIdxp22 ]).M() <= ( mymV-mynsigma*myY1sResp2 )
		     
		     // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~change end suleyman~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
			 && myNumGoodTightMuon>=2 //if one of the V is Upsilon
		     
		     ) 
		    {
		      if(NumDup<1) {			
 			myMuMuMuMumassV1mumubelowV1->Fill( myfourmuonmass );
			  						
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
  

  myMuMuMuMumassV1mumubelowV1->Write();
myMuMuonlymass->Write();

  


 
}
