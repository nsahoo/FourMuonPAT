#define myntuple_cxx
#include "myntuple.h"
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "DataFormats/Math/interface/deltaR.h"
#include "TLorentzVector.h"
#include "TPoint.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#define muon_mass  0.105658
#define jpsi_mass 3.0967


void myntuple::Loop()
{
   std::cout.precision(50);
 
  ofstream eventEfficiency("EventByEventEfficiency_BugFixed.txt");
  TFile* myhbk = new TFile ("PtGunDataEmbedding.root","recreate");

  TH1F* myMuMuMuMumassSignal = new TH1F("myMuMuMuMumassSignal","myMuMuMuMumassSignal",20000,0,200.0);
  TH1F* myMuPMuMmassGen1 = new TH1F("myMuPMuMmassGen1","myMuPMuMmassGen1",20000,0.0,200.0);
  TH1F* myMuPMuMmassGen2 = new TH1F("myMuPMuMmassGen2","myMuPMuMmassGen2",20000,0.0,200.0);

  TH1F* myMuPMuMmassReco1 = new TH1F("myMuPMuMmassReco1","myMuPMuMmassReco1",20000,0.0,200.0);
  TH1F* myMuPMuMmassReco2 = new TH1F("myMuPMuMmassReco2","myMuPMuMmassReco2",20000,0.0,200.0);
  TH1F* myMuPMuMmassOnly = new TH1F("myMuPMuMmassOnly","myMuPMuMmassOnly",20000,0.0,200.0);
  TH1F* myMuPMuMRecoPt1 = new TH1F("myMuPMuMRecoPt1","",500,0.0,100.0);
  TH1F* myMuPMuMRecoPt2 = new TH1F("myMuPMuMRecoPt2","",500,0.0,100.0);
  TH1F* myMuPMuMRecoPhi1 = new TH1F("myMuPMuMRecoPhi1","",64,-3.2,3.2);
  TH1F* myMuPMuMRecoPhi2 = new TH1F("myMuPMuMRecoPhi2","",64,-3.2,3.2);
  TH1F* myMuPMuMRecoCosHelicity = new TH1F("myMuPMuMRecoCosHelicity","",100,-1.1,1.1);
  TH1F* myMuPMuMRecoDihedral = new TH1F("myMuPMuMRecoDihedral","",100,0,3.14);
  TH1F* myMuPMuMRecoDeltaY = new TH1F("myMuPMuMRecoDeltaY","", 100,0.,5.);
  TH1F* myMuMu1VsMuMu2RecoPhi = new TH1F("myMuMu1VsMuMu2RecoPhi","",100,0,3.14);
  TH1F* myMuPMuPRecoDeltaPhi = new TH1F("myMuPMuPRecoDeltaPhi","",100,0,3.14);
  TH1F* myMuMMuMRecoDeltaPhi = new TH1F("myMuMMuMRecoDeltaPhi","", 100,0.0,3.14);

  TH1F* myMuMuMuMuRecoEta = new TH1F("myMuMuMuMuRecoEta","",80,-4,4);
  TH1F* myNumGenUpsilonUpsilon = new TH1F("myNumGenUpsilonUpsilon","",10,0,10);
  TH1F* myNumRecoUpsilon = new TH1F("myNumRecoUpsilon","",1000,5,15);

  ///////////// End Upsilon Acceptance graph /////
  float etaMin=-2.6, etaMax=2.6, binEta=104, pTMin=0, pTMax=15, binpT=150;
  float upsEtaMin =0, upsEtaMax=2.4, upsEtabin=24, upsPtMin=0, upsPtMax=25, upsPtbin=50;

  TH2F* my2DMuPtVsEtaReco = new TH2F("my2DMuPtVsEtaReco","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPtVsEtaGen = new TH2F("my2DMuPtVsEtaGen","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPVsEtaReco = new TH2F("my2DMuPVsEtaReco","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPVsEtaGen = new TH2F("my2DMuPVsEtaGen","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);

  TH2F* my2DMuPtVsEtaRecoMatched = new TH2F("my2DMuPtVsEtaRecoMatched","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPtVsEtaEff = new TH2F("my2DMuPtVsEtaEff","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPVsEtaEff = new TH2F("my2DMuPVsEtaEff","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPtVsEtaPurity = new TH2F("my2DMuPtVsEtaPurity","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPVsEtaPurity = new TH2F("my2DMuPVsEtaPurity","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* myMuPMuMRecoPtVsEtaTotal = new TH2F("myMuPMuMRecoPtVsEtaTotal","",upsEtabin,upsEtaMin,upsEtaMax,upsPtbin,upsPtMin,upsPtMax);

  TH2F* myMuPMuMRecoEtaVsPtTotal = new TH2F("myMuPMuMRecoEtaVsPtTotal","",upsPtbin/2.,upsPtMin,upsPtMax,upsEtabin/2.,upsEtaMin,2.5);

  TH2F* myMuPMuMRecoPtVsEta2 = new TH2F("myMuPMuMRecoPtVsEta2","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* myMuPMuMRecoPtVsEta1 = new TH2F("myMuPMuMRecoPtVsEta1","",binEta,etaMin,etaMax,binpT,pTMin,pTMax);
  TH2F* my2DMuPMuMPtVsEtaGen = new TH2F("my2DMuPMuMPtVsEtaGen","",upsEtabin,upsEtaMin,upsEtaMax,upsPtbin,upsPtMin,upsPtMax);

  TH2F* my2DMuPMuMEtaVsPtGen = new TH2F("my2DMuPMuMEtaVsPtGen","",upsPtbin/2.,upsPtMin,upsPtMax,upsEtabin/2.,upsEtaMin,2.5);
  
  TH2F* my2DMuPMuMPtVsEta1PCosSquareGen = new TH2F("my2DMuPMuMPtVsEta1PCosSquareGen","",upsEtabin,upsEtaMin,upsEtaMax,upsPtbin,upsPtMin,upsPtMax);
  TH2F* my2DMuPMuMPtVsEta1MCosSquareGen = new TH2F("my2DMuPMuMPtVsEta1MCosSquareGen","",upsEtabin,upsEtaMin,upsEtaMax,upsPtbin,upsPtMin,upsPtMax);
  TH2F* my2DMuPMuMPtVsEta1PCosSquareReco = new TH2F("my2DMuPMuMPtVsEta1PCosSquareReco","",upsEtabin,upsEtaMin,upsEtaMax,upsPtbin,upsPtMin,upsPtMax);
  TH2F* my2DMuPMuMPtVsEta1MCosSquareReco = new TH2F("my2DMuPMuMPtVsEta1MCosSquareReco","",upsEtabin,upsEtaMin,upsEtaMax,upsPtbin,upsPtMin,upsPtMax);


  TH1F* myMuEtaEff = new TH1F("myMuEtaEff","",binEta,etaMin,etaMax);
  TH1F* myMuPtEff = new TH1F("myMuPtEff","",binpT,pTMin,pTMax);

  TH1F* myMuGenEta = new TH1F("myMuGenEta","",binEta,etaMin,etaMax);
  TH1F* myMuRecoEta = new TH1F("myMuRecoEta","",binEta,etaMin,etaMax);
  TH1F* myMuRecoMatchedEta = new TH1F("myMuRecoMatchedEta","",binEta,etaMin,etaMax);
  
  TH1F* myMuGenPt = new TH1F("myMuGenPt","",binpT,pTMin,pTMax);
  TH1F* myMuRecoPt = new TH1F("myMuRecoPt","",binpT,pTMin,pTMax);
  TH1F* myMuRecoMatchedPt = new TH1F("myMuRecoMatchedPt","",binpT,pTMin,pTMax);

  TH1F* myMuPMuMGenPt1 = new TH1F("myMuPMuMGenPt1","",500,0.0,100.0);
  TH1F* myMuPMuMGenPt2 = new TH1F("myMuPMuMGenPt2","",500,0.0,100.0);
  TH1F* myMuPMuMGenPhi1 = new TH1F("myMuPMuMGenPhi1","",64,-3.2,3.2);
  TH1F* myMuPMuMGenPhi2 = new TH1F("myMuPMuMGenPhi2","",64,-3.2,3.2);
  TH1F* myMuPMuMGenEta2 = new TH1F("myMuPMuMGenEta2","",80,-4,4);
  TH1F* myMuPMuMGenEta1 = new TH1F("myMuPMuMGenEta1","",80,-4,4);

  
  ///// Getting Run and Event Numbers From List
  //ifstream fp("/uscms/home/mhaytmyr/work/CMSSW_5_3_7_patch5/test/NtupleAnalyzer/FourMuonAnalyzer/MCAnalyzer/DataEmbedding_5/EventAndRunNumbers.txt",ios::in);
  ifstream fp("/uscms/home/mhaytmyr/work/CMSSW_5_3_7_patch5/test/NtupleAnalyzer/FourMuonAnalyzer/MCAnalyzer/DataEmbedding_SPS4/EventAndRunNumbers.txt",ios::in);

  //ifstream fp("/uscms/home/mhaytmyr/work/CMSSW_5_3_7_patch5/test/NtupleAnalyzer/FourMuonAnalyzer/MCAnalyzer/DataEmbedding_DPS8/EventAndRunNumbers.txt",ios::in);
  //ifstream fp("/uscms/home/mhaytmyr/work/CMSSW_5_3_7_patch5/test/NtupleAnalyzer/FourMuonAnalyzer/MCAnalyzer/DataEmbedding_5/EventAndRunNumbers.txt",ios::in);


  if(!fp) { cerr << "Bad" << endl; return; }


  //////Checking Event Number And Run Number
  //Float_t EvtNum, RunNum;
  long int EvtNum, RunNum;

  while(kTRUE){

  fp>>EvtNum>>RunNum;

  if(fp.eof()) break;


  int totPassed = 0;

  if(fChain == 0) return;
    Long64_t nentries = fChain->GetEntries();
  //cout<<"Total entries="<<nentries<<endl;
 
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
	
    bool foundEvent = false;	
    if(runNum == RunNum && evtNum>=EvtNum && evtNum<=EvtNum+1000) {

	//std::cout<<evtNum<<" ; "<<runNum<<std::endl;
	foundEvent = true;}

    //if(foundEvent) std::cout<<"I found event "<<EvtNum<<std::endl;
    Long64_t ientry = LoadTree(jentry);

    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if(jentry%10000==0) cout<<"I am running "<<jentry<<"th entries out of "<<nentries<<" total entries"<<endl;

    bool TrigThreeMuon=false;
    bool TrigThreeMuonJpsi=false;
    bool TrigThreeMuonUpsi=false;


    for(int i=0; i!=TrigRes->size(); ++i){ 
//      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1) 
//      if(TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1 || TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1 )
	{
	  TrigThreeMuon=true;
	}

      if(TrigNames->at(i).find("HLT_Dimuon0_Jpsi_Muon_")!=string::npos && TrigRes->at(i)==1)
        {
          TrigThreeMuonJpsi=true;
        }

      if(TrigNames->at(i).find("HLT_Dimuon0_Upsilon_Muon_")!=string::npos && TrigRes->at(i)==1)
        { 
          TrigThreeMuonUpsi=true;
        }

    }


 
    	//////////////four muon signal//////////////    	
    	for (int myFourMuIdx = 0; myFourMuIdx <nMyFourMuon; myFourMuIdx++){

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



       int myNumGoodLooseMuon= (*muIsGoodLooseMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodLooseMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];

       int myNumGoodTightMuon= (*muIsGoodTightMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodTightMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];

       int myNumGoodSoftMuon= (*muIsGoodSoftMuon)[ (*MyFourMuonMu1Idx)[myFourMuIdx]] + (*muIsGoodSoftMuon)[(*MyFourMuonMu2Idx)[myFourMuIdx]] + (*muIsGoodSoftMuon)[ (*MyFourMuonMu3Idx)[myFourMuIdx]] + (*muIsGoodSoftMuon)[ (*MyFourMuonMu4Idx)[myFourMuIdx]];


	float mymumumassmin=8.5;
        float mymumumassmax=11;

	if(1
	   && (*MyFourMuonVtxCL)[myFourMuIdx]>=0.05	   
	   && TrigThreeMuonUpsi
	   && fitMup4vect[3].Pt()>3.5
	   && fabs(fitMup4vect[0].Eta())<=2.4 && fabs(fitMup4vect[1].Eta())<=2.4
	   && fabs(fitMup4vect[1].Eta())<=2.4 && fabs(fitMup4vect[3].Eta())<=2.4
           && myNumGoodSoftMuon>=4
	   ){ 	    

	float myvrtxprob=0.005;

	//for upsilon+upsilon
        float upsups12label=0;
        float upsups13label=0;
        float upsups14label=0;

        if( (fitMuCharge[0] + fitMuCharge[1] ) == 0 ) {
        upsups12label=sqrt(  pow((fitMup4vect[0]+fitMup4vect[1]).M()-9.4603,2) + pow((fitMup4vect[2]+fitMup4vect[3]).M()-9.4603,2)  );
        }
        if( (fitMuCharge[0] + fitMuCharge[2] ) == 0 ) {
        upsups13label=sqrt(  pow((fitMup4vect[0]+fitMup4vect[2]).M()-9.4603,2) + pow((fitMup4vect[1]+fitMup4vect[3]).M()-9.4603,2)  );
        }
        if( (fitMuCharge[0] + fitMuCharge[3] ) == 0 ) {
       upsups14label=sqrt(  pow((fitMup4vect[0]+fitMup4vect[3]).M()-9.4603,2) + pow((fitMup4vect[1]+fitMup4vect[2]).M()-9.4603,2)  );
        }

        float myavgups=(upsups12label+upsups13label+upsups14label)/2.0;
        if( upsups12label>0 )upsups12label=(int)((upsups12label+myavgups)/myavgups);
        if( upsups13label>0 )upsups13label=(int)((upsups13label+myavgups)/myavgups);
        if( upsups14label>0 )upsups14label=(int)((upsups14label+myavgups)/myavgups);


	if((fitMuCharge[0] + fitMuCharge[1] ) == 0
        && (*MyJpsi1ChiProb_Mu12)[myFourMuIdx]>myvrtxprob && (*MyJpsi2ChiProb_Mu34)[myFourMuIdx]>myvrtxprob
	&& (*My1234MuonTrigMatch)[myFourMuIdx]
	&& (fitMup4vect[0]+fitMup4vect[1]).M()>mymumumassmin && (fitMup4vect[0]+fitMup4vect[1]).M()<mymumumassmax
        && (fitMup4vect[2]+fitMup4vect[3]).M()>mymumumassmin && (fitMup4vect[2]+fitMup4vect[3]).M()<mymumumassmax
	&& upsups12label == 1 
	){
	
	myMuPMuMmassReco1->Fill((fitMup4vect[0]+fitMup4vect[1]).M());
	myMuPMuMmassReco2->Fill((fitMup4vect[2]+fitMup4vect[3]).M());

	myMuPMuMRecoPtVsEta1->Fill((fitMup4vect[0]+fitMup4vect[1]).Rapidity(),(fitMup4vect[0]+fitMup4vect[1]).Pt());
 	myMuPMuMRecoPtVsEta2->Fill((fitMup4vect[2]+fitMup4vect[3]).Rapidity(),(fitMup4vect[2]+fitMup4vect[3]).Pt());

	myMuMu1VsMuMu2RecoPhi->Fill(fabs ((fitMup4vect[0]+fitMup4vect[1]).DeltaPhi(fitMup4vect[2]+fitMup4vect[3])));

        myMuPMuMRecoPt1->Fill((fitMup4vect[0]+fitMup4vect[1]).Pt());
        myMuPMuMRecoPt2->Fill((fitMup4vect[2]+fitMup4vect[3]).Pt());

        myMuMuMuMuRecoEta->Fill((fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).Rapidity());

	if(foundEvent) totPassed++;

	}////if charge(mu1+mu2) = 0

	if((fitMuCharge[0] + fitMuCharge[2] ) == 0
	&& (*MyJpsi3ChiProb_Mu13)[myFourMuIdx]>myvrtxprob && (*MyJpsi4ChiProb_Mu24)[myFourMuIdx]>myvrtxprob
	&& (*My1324MuonTrigMatch)[myFourMuIdx]
	&& (fitMup4vect[0]+fitMup4vect[2]).M()>mymumumassmin && (fitMup4vect[0]+fitMup4vect[2]).M()<mymumumassmax
        && (fitMup4vect[1]+fitMup4vect[3]).M()>mymumumassmin && (fitMup4vect[1]+fitMup4vect[3]).M()<mymumumassmax
	&& upsups13label == 1 
	){
	  

	myMuPMuMmassReco1->Fill((fitMup4vect[0]+fitMup4vect[2]).M());
        myMuPMuMmassReco2->Fill((fitMup4vect[1]+fitMup4vect[3]).M());

        myMuPMuMRecoPtVsEta1->Fill((fitMup4vect[0]+fitMup4vect[2]).Rapidity(),(fitMup4vect[0]+fitMup4vect[2]).Pt());
        myMuPMuMRecoPtVsEta2->Fill((fitMup4vect[1]+fitMup4vect[3]).Rapidity(),(fitMup4vect[1]+fitMup4vect[3]).Pt());

        myMuMu1VsMuMu2RecoPhi->Fill(fabs ((fitMup4vect[0]+fitMup4vect[2]).DeltaPhi(fitMup4vect[1]+fitMup4vect[3])));

        myMuPMuMRecoPt1->Fill((fitMup4vect[0]+fitMup4vect[2]).Pt());
        myMuPMuMRecoPt2->Fill((fitMup4vect[1]+fitMup4vect[3]).Pt());

        myMuMuMuMuRecoEta->Fill((fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).Rapidity());

	if(foundEvent) totPassed++;

	}/// charge(mu1+mu3) = 0

	if((fitMuCharge[0] + fitMuCharge[3] ) == 0
	   && (*MyJpsi5ChiProb_Mu14)[myFourMuIdx]>myvrtxprob && (*MyJpsi6ChiProb_Mu23)[myFourMuIdx]>myvrtxprob
	   && (*My1423MuonTrigMatch)[myFourMuIdx]
	   && (fitMup4vect[0]+fitMup4vect[3]).M()>mymumumassmin && (fitMup4vect[0]+fitMup4vect[3]).M()<mymumumassmax
           && (fitMup4vect[1]+fitMup4vect[2]).M()>mymumumassmin && (fitMup4vect[1]+fitMup4vect[2]).M()<mymumumassmax
	   && upsups14label == 1
	){


	myMuPMuMmassReco1->Fill((fitMup4vect[0]+fitMup4vect[3]).M());
        myMuPMuMmassReco2->Fill((fitMup4vect[1]+fitMup4vect[2]).M());

        myMuPMuMRecoPtVsEta1->Fill((fitMup4vect[0]+fitMup4vect[3]).Rapidity(),(fitMup4vect[0]+fitMup4vect[3]).Pt());
        myMuPMuMRecoPtVsEta2->Fill((fitMup4vect[2]+fitMup4vect[1]).Rapidity(),(fitMup4vect[2]+fitMup4vect[1]).Pt());

        myMuMu1VsMuMu2RecoPhi->Fill(fabs((fitMup4vect[0]+fitMup4vect[3]).DeltaPhi(fitMup4vect[2]+fitMup4vect[1])));

        myMuPMuMRecoPt1->Fill((fitMup4vect[0]+fitMup4vect[3]).Pt());
        myMuPMuMRecoPt2->Fill((fitMup4vect[2]+fitMup4vect[1]).Pt());

        myMuMuMuMuRecoEta->Fill((fitMup4vect[0]+fitMup4vect[1]+fitMup4vect[2]+fitMup4vect[3]).Rapidity());

	if(foundEvent) totPassed++;

		} ///charge(mu1+mu4) = 0 
	    
	  }//if Four muon selections Pass
	
      }//for (int myFourMuIdx = 0; myFourMuIdx <nJ; myFourMuIdx++)

   }//for (Long64_t jentry=0; 

	//myEventByEventEfficiency->Fill(EvtNum,RunNum,totPassed);
	std::cout<<EvtNum<<" "<<RunNum<<" "<<totPassed<<std::endl;    
	eventEfficiency<<EvtNum<<" "<<RunNum<<" "<<totPassed<<std::endl;    
}//end while loop

   myhbk->cd();



   my2DMuPtVsEtaReco->SetStats(00000);
   my2DMuPtVsEtaReco->GetYaxis()->SetTitle("p^{#mu}_{T} GeV/c");
   my2DMuPtVsEtaReco->GetXaxis()->SetTitle("#eta^{#mu}");
   my2DMuPtVsEtaGen->SetStats(00000);
   my2DMuPtVsEtaGen->GetYaxis()->SetTitle("p^{#mu}_{T} GeV/c");
   my2DMuPtVsEtaGen->GetXaxis()->SetTitle("#eta^{#mu}");

   my2DMuPVsEtaReco->SetStats(00000);
   my2DMuPVsEtaReco->GetYaxis()->SetTitle("p^{#mu} GeV/c");
   my2DMuPVsEtaReco->GetXaxis()->SetTitle("#eta^{#mu}");
   my2DMuPVsEtaGen->SetStats(00000);
   my2DMuPVsEtaGen->GetYaxis()->SetTitle("p^{#mu} GeV/c");
   my2DMuPVsEtaGen->GetXaxis()->SetTitle("#eta^{#mu}");

   myMuPMuMRecoPtVsEta2->SetStats(00000);
   myMuPMuMRecoPtVsEta2->GetYaxis()->SetTitle("#Upsilon(1S) p_{T} GeV/c");
   myMuPMuMRecoPtVsEta2->GetXaxis()->SetTitle("#Upsilon(1S) y");

   myMuPMuMRecoPtVsEta1->SetStats(00000);
   myMuPMuMRecoPtVsEta1->GetYaxis()->SetTitle("#Upsilon(1S) p_{T} GeV/c");
   myMuPMuMRecoPtVsEta1->GetXaxis()->SetTitle("#Upsilon(1S) y");

   my2DMuPtVsEtaRecoMatched->SetStats(00000);
   my2DMuPtVsEtaRecoMatched->GetYaxis()->SetTitle("p^{#mu}_{T} GeV/c");
   my2DMuPtVsEtaRecoMatched->GetXaxis()->SetTitle("#eta^{#mu}");

   myMuPMuMRecoPtVsEtaTotal->SetStats(00000);
   myMuPMuMRecoPtVsEtaTotal->GetYaxis()->SetTitle("p^{#Upsilon}_{T} GeV/c");
   myMuPMuMRecoPtVsEtaTotal->GetXaxis()->SetTitle("Reconstructed #Upsilon y");

   myMuPMuMRecoEtaVsPtTotal->SetStats(00000);
   myMuPMuMRecoEtaVsPtTotal->GetXaxis()->SetTitle("p^{#Upsilon}_{T} GeV/c");
   myMuPMuMRecoEtaVsPtTotal->GetYaxis()->SetTitle("Reconstructed #Upsilon y");  

   my2DMuPMuMPtVsEtaGen->SetStats(00000);
   my2DMuPMuMPtVsEtaGen->GetYaxis()->SetTitle("p^{#Upsilon}_{T} GeV/c");
   my2DMuPMuMPtVsEtaGen->GetXaxis()->SetTitle("Generated #Upsilon y");

   my2DMuPtVsEtaEff->SetStats(00000);
   my2DMuPtVsEtaEff->GetYaxis()->SetTitle("p^{#mu}_{T} GeV/c");
   my2DMuPtVsEtaEff->GetXaxis()->SetTitle("#eta^{#mu}");

   my2DMuPVsEtaEff->SetStats(00000);
   my2DMuPVsEtaEff->GetYaxis()->SetTitle("p^{#mu} GeV/c");
   my2DMuPVsEtaEff->GetXaxis()->SetTitle("#eta^{#mu}");

   my2DMuPtVsEtaPurity->SetStats(00000);
   my2DMuPtVsEtaPurity->GetYaxis()->SetTitle("p^{#mu}_{T} GeV/c");
   my2DMuPtVsEtaPurity->GetXaxis()->SetTitle("#eta^{#mu}");
  
   my2DMuPVsEtaPurity->SetStats(00000);
   my2DMuPVsEtaPurity->GetYaxis()->SetTitle("p^{#mu} GeV/c");
   my2DMuPVsEtaPurity->GetXaxis()->SetTitle("#eta^{#mu}");

   myMuRecoMatchedPt->SetStats(00000);
   myMuRecoMatchedPt->GetXaxis()->SetTitle("p^{#mu}_{T} GeV/c");

   myMuRecoMatchedEta->SetStats(00000);
   myMuRecoMatchedEta->GetXaxis()->SetTitle("#eta^{#mu}");

   my2DMuPtVsEtaRecoMatched->Divide(my2DMuPtVsEtaGen);
   myNumGenUpsilonUpsilon->Write();
   myNumRecoUpsilon->Write();

   myMuPMuMRecoPt2->Write();
   myMuPMuMRecoPt1->Write();
   myMuPMuMRecoPtVsEta2->Write(); 
   myMuPMuMRecoPtVsEta1->Write();
   myMuPMuMmassReco2->Write(); 
   myMuPMuMmassReco1->Write(); 
   myMuPMuMmassOnly->Write();
   myMuMuMuMumassSignal->Write(); 
   myMuMuMuMuRecoEta->Write();
   myMuPMuMRecoCosHelicity->Write(); 
   myMuPMuMRecoDihedral->Write();
   myMuMu1VsMuMu2RecoPhi->Write();
   myMuPMuPRecoDeltaPhi->Write(); 
   myMuMMuMRecoDeltaPhi->Write(); 
   myMuRecoMatchedEta->Write();
   myMuRecoMatchedPt->Write();
   my2DMuPtVsEtaRecoMatched->Write();



}
