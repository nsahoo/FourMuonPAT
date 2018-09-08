#include "Basics.h"
#include "TLorentzVector.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

#ifndef M_PI
#define M_PI       3.14159265358979323846264338328      // Pi 
#endif


    //gSystem->Load("libPhysics.so");
void UpsilonSPSDecayer(){

    std::cout.precision(10);

    //ofstream outfile("OveralEffMap_SPSModel.txt");
    //ofstream outfile("OveralEffMap_DPSModel.txt");
    //ofstream outfile("OveralEffMap_BugFixed.txt");

    //ofstream outAcceptance("AcceptanceMap_SPSModel.txt");
    //ofstream outAcceptance("AcceptanceMap_DPSModel.txt");
    ofstream outfile("AcceptanceMapSPS_YRap2p0.txt");

    Float_t Ups1Px, Ups1Py, Ups1Pz, Ups2Px, Ups2Py, Ups2Pz, Ups1Mass, Ups2Mass, defaultEff, FouMuvrtx, evtByEvtEff, label;
    long int nEvt,evtNumAcc,runNumAcc, evtNumEff, runNumEff, effEvent, effRun;
    double totalEff;

    TFile* myhbk = new TFile ("SPSAcceptanceDef.root","recreate");
    TH2F* myTotAccVsSingleAcc = new TH2F("myTotAccVsSingleAcc","",50,0,1,50,0,1);

    TH1F* myTransversePol1 = new TH1F("myTransversePol1","",200,-1.0,1.0);
    TH1F* myLongtPol1 = new TH1F("myLongtPol1","",200,-1.0,1.0);
    TH1F* myTransversePol2 = new TH1F("myTransversePol2","",200,-1.0,1.0);
    TH1F* myLongtPol2 = new TH1F("myLongtPol2","",200,-1.0,1.0);
    TH1F* myIsoTropic = new TH1F("myIsoTropic","",200,-1.0,1.0);

    TH1F* myMu1RecoEta = new TH1F("myMu1RecoEta","",100,-5.0,5.0);
    TH1F* myMu2RecoEta = new TH1F("myMu2RecoEta","",100,-5.0,5.0);
    TH1F* myUpsilonGunEff = new TH1F("myUpsilonGunEff","",100,0.0,1.0);
    TH1F* myMu1RecoPt = new TH1F("myMu1RecoPt","",500,-50.0,50.0);
    TH1F* myMu2RecoPt = new TH1F("myMu2RecoPt","",500,-50.0,50.0);
    TH1F* myMu3RecoPt = new TH1F("myMu3RecoPt","",500,-50.0,50.0);
    TH1F* myMu4RecoPt = new TH1F("myMu4RecoPt","",500,-50.0,50.0);
    TH1F* myEvtByEvtAcc_PercentErr = new TH1F("myEvtByEvtAcc_PercentErr","",500,0.0,0.1);
    TH1F* myEvtByEvtEff_PercentErr = new TH1F("myEvtByEvtEff_PercentErr","",300,0.0,0.3);
    TH1F* myEvtByEvtTot_PercentErr = new TH1F("myEvtByEvtTot_PercentErr","",500,0.0,1);
    TH1F* myEvtByEvtAcceptance = new TH1F("myEvtByEvtAcceptance","",100,0.0,1);
    TH1F* myOverallEvtByEvtEff = new TH1F("myOverallEvtByEvtEff","",100,0.0,1);
    TH1F* myEvtByEvtEfficiency = new TH1F("myEvtByEvtEfficiency","",100,0.0,1);
 
    TH2F* myUps1AccPtVsEta = new TH2F("myUps1AccPtVsEta","",24,0,2.4,50,0,10);
    TH2F* myUps2AccPtVsEta = new TH2F("myUps2AccPtVsEta","",24,0,2.4,50,0,10);


    TH1F* myAngleMu1VsMu2 = new TH1F("myAngleMu1VsMu2","",100,-2*3.14,2*3.14);
    TH1F* myAngleMu3VsMu4 = new TH1F("myAngleMu3VsMu4","",100,-2*3.14,2*3.14);


    vector<double> mProd;

    /// Define Upsilon Mass
    mProd.push_back(9.46030);
    ///x-check with Jpsi Mass
    //mProd.push_back(3.096);

    /// Define Muon Masses
    mProd.push_back(0.1056583);
    mProd.push_back(0.1056583);

    // Masses.
    double m0   = mProd[0];
    double m1   = mProd[1];
    double m2   = mProd[2];

    // Energies and absolute momentum in the rest frame.
    double e1   = 0.5 * (m0*m0 + m1*m1 - m2*m2) / m0;
    double e2   = 0.5 * (m0*m0 + m2*m2 - m1*m1) / m0; 
    double pAbs = 0.5 * sqrt( (m0 - m1 - m2) * (m0 + m1 + m2)
      * (m0 + m1 - m2) * (m0 - m1 + m2) ) / m0;


    ///Signal MC Model
    //ifstream fp("../ReRecoUpsilon/NtupleOut/myFourMuon_SPSClosureTest_ForAcceptance.txt",ios::in);
    //ifstream fp("../ReRecoUpsilon/NtupleOut/myFourMuon_DPSClosureTest_ForAcceptance.txt",ios::in);

    //ifstream fp("../ReRecoUpsilon/NtupleOut/myFourMuon_SPSGenEvents_ForAcceptance.txt",ios::in);
    //ifstream fp("../ReRecoUpsilon/NtupleOut/myFourMuon_DPSGenEvents_ForAcceptance.txt",ios::in);

    //Increased statistics after ARC meeting
    ifstream fp("../ReRecoUpsilon/NtupleOut/myFourMuon_SPSGenEvents_ForAcceptance_YRap2p0.txt",ios::in);
    //Reduced File

    //Define variables once
    double nGenerated, nPassed, nUps1Pass, nUps2Pass;
    double rndm, rndm2, rndm3, rndm4;
    double cosTheta1, sinTheta1, phi1, pX1, pY1, pZ1;
    double cosTheta2, sinTheta2, phi2, pX2, pY2, pZ2;
    vector<TLorentzVector>  pProd;
    TLorentzVector mu1, mu2, Upsilon1, mu3, mu4, Upsilon2;


    if(!fp) { cerr << "Bad" << endl; return; }

    double IsotropicTotalAcc = 0, IsotropicSingleAcc = 0, PolarizationTotalAcc = 0, PolarizationSingleAcc = 0;
    double lambdaUps1 = -1;
    double lambdaUps2 = -1.; 
    //-1 for 100% Transverse and +1 for 100% Longitude Polarization

    while(kTRUE) {
	//For gen events use following
	fp>>Ups1Mass>>Ups2Mass>>Ups1Px>>Ups1Py>>Ups1Pz>>Ups2Px>>Ups2Py>>Ups2Pz>>defaultEff>>evtNumAcc>>runNumAcc>>label;
	//fp>>Ups1Mass>>Ups2Mass>>Ups1Px>>Ups1Py>>Ups1Pz>>Ups2Px>>Ups2Py>>Ups2Pz>>defaultEff>>evtNumAcc>>runNumAcc>>label>>FouMuvrtx;

	if (fp.eof()) break;


	//myUpsilonGunEff->Fill(1./defaultEff);

	TRandom *eventGenerator = new TRandom1();
	eventGenerator->SetSeed();
	TRandom *eventGenerator2 = new TRandom2();
	eventGenerator2->SetSeed();
	TRandom *eventGenerator3 = new TRandom3();
	eventGenerator3->SetSeed();
	TRandom *eventGenerator4 = new TRandom3();
	eventGenerator4->SetSeed();

        //TLorentzVector mu1, mu2, Upsilon1, mu3, mu4, Upsilon2;
        Upsilon1.SetXYZM(Ups1Px, Ups1Py, Ups1Pz , m0);
        Upsilon2.SetXYZM(Ups2Px, Ups2Py, Ups2Pz , m0);


	cout<<"Read Event="<<Upsilon1.Rapidity()<<" ; "<<Upsilon1.Pt()<<" ; "<<evtNumAcc<<endl;

	nGenerated = 10000; nPassed = 0; nUps1Pass =0; nUps2Pass=0;
	//double nUps1Ups2Polarization = 0, nUps1Ups2PolarizationPassed=0;

	// Wrong Way
	//double nUps1Polarization = 0, nUps1PolarizationPassed=0;
	//double nUps2Polarization = 0, nUps2PolarizationPassed=0;


        ///Start repeadet decay 
        for(int i=0; i<nGenerated; i++){

	rndm = eventGenerator->Uniform();
	rndm2 = eventGenerator2->Rndm();
	rndm3 = eventGenerator3->Uniform();
	rndm4 = eventGenerator4->Rndm();

        // Pick isotropic angles to give three-momentum for mu1 and mu2
        //double cosTheta1 = 2. * rndm - 1.;
        cosTheta1 = 2*rndm-1;
	sinTheta1 = sqrt(1. - cosTheta1*cosTheta1);
        phi1      = 2. * M_PI *rndm3;
        pX1       = pAbs * sinTheta1 * cos(phi1);
        pY1       = pAbs * sinTheta1 * sin(phi1);
        pZ1       = pAbs * cosTheta1;
	//std::cout<<"Theta1 = "<<cosTheta1<<" ; Phi1 ="<<cos(phi1)<<std::endl;

	// Pick isotropic angles to give three-momentum for mu3 and mu4
        //double cosTheta2 = 2. * rndm2 - 1.;
        cosTheta2 = 2*rndm3-1;
        sinTheta2 = sqrt(1. - cosTheta2*cosTheta2);
        phi2      = 2. * M_PI * rndm;
        pX2       = pAbs * sinTheta2 * cos(phi2);
        pY2       = pAbs * sinTheta2 * sin(phi2);
        pZ2       = pAbs * cosTheta2;

	//std::cout<<"Theta2 = "<<cosTheta2<<" ; Phi2 ="<<cos(phi2)<<std::endl;
	//std::cout<<"Px = "<<pX<<"; Py = "<<pY<<" ; Pz = "<<pZ<<std::endl; 

	mu1.SetPxPyPzE(pX1,pY1,pZ1,e1);
	mu2.SetPxPyPzE(-pX1,-pY1,-pZ1,e2);

	mu3.SetPxPyPzE(pX2,pY2,pZ2,e1);
        mu4.SetPxPyPzE(-pX2,-pY2,-pZ2,e2);
        // Fill four-momenta in mother rest frame and then boost to lab frame.
        pProd.push_back( mu1 );
        pProd.push_back( mu2 );
        pProd.push_back( mu3 );
        pProd.push_back( mu4 );

        pProd[0].Boost( Upsilon1.BoostVector());
        pProd[1].Boost( Upsilon1.BoostVector());

        pProd[2].Boost( Upsilon2.BoostVector());
        pProd[3].Boost( Upsilon2.BoostVector());


	//Calculate Polarization Angle
        //double thetaStar1 = cos(mu1.Angle(Upsilon1.Vect()));
        //double thetaStar2 = cos(mu2.Angle(Upsilon1.Vect()));

        //double thetaStar3 = cos(mu3.Angle(Upsilon2.Vect()));
        //double thetaStar4 = cos(mu4.Angle(Upsilon2.Vect()));

        //myAngleMu1VsMu2->Fill(thetaStar1,thetaStar2);
        //myAngleMu3VsMu4->Fill(thetaStar3,thetaStar4);

        //double Ups1Polarization = 1+lambdaUps1*thetaStar1*thetaStar1;
        //double Ups2Polarization = 1+lambdaUps2*thetaStar3*thetaStar3;

	/*
        myTransversePol1->Fill(thetaStar1,Ups1Polarization);
        myLongtPol1->Fill(thetaStar1,Ups1Polarization);
        myTransversePol2->Fill(thetaStar3,Ups2Polarization);
        myLongtPol2->Fill(thetaStar3,Ups2Polarization);
        myIsoTropic->Fill(thetaStar1,1);
	*/

        //Summing Transverse and Longitude Polarizatio
	//nUps1Ups2Polarization += Ups1Polarization*Ups2Polarization;

	//Alternative Way
	//nUps1Polarization += Ups1Polarization; 
	//nUps2Polarization += Ups2Polarization;
	

	int Ups1Pass = 0, Ups2Pass =0;
	//Look for Ups1 first
	if(1
	//Upsilon
        && pProd[0].Pt()>3.5 && fabs(pProd[0].Eta())<=2.4
        && pProd[1].Pt()>3.5 && fabs(pProd[1].Eta())<=2.4
	//Jpsi
	/*&& ((fabs(pProd[0].Eta())<0.8 && pProd[0].Pt()>3.5) 
	|| (fabs(pProd[0].Eta())>0.8 && fabs(pProd[0].Eta())<1.6 && pProd[0].Pt()>(-2*fabs(pProd[0].Eta())+5.2)) 
	|| (fabs(pProd[0].Eta())>1.6 && fabs(pProd[0].Eta())<2.2 && pProd[0].Pt()>2.0))
	&& ((fabs(pProd[1].Eta())<0.8 && pProd[1].Pt()>3.5)
        || (fabs(pProd[1].Eta())>0.8 && fabs(pProd[1].Eta())<1.6 && pProd[1].Pt()>(-2*fabs(pProd[1].Eta())+5.2)) 
        || (fabs(pProd[1].Eta())>1.6 && fabs(pProd[1].Eta())<2.2 && pProd[1].Pt()>2.0))
	*/
	){
		Ups1Pass = 1;
		//nUps1PolarizationPassed += Ups1Polarization;
		nUps1Pass++;
	}
	
	if(1
	&& pProd[2].Pt()>3.5 && fabs(pProd[2].Eta())<=2.4
        && pProd[3].Pt()>3.5 && fabs(pProd[3].Eta())<=2.4
	/*
	&& ((fabs(pProd[2].Eta())<0.8 && pProd[2].Pt()>3.5)
        || (fabs(pProd[2].Eta())>0.8 && fabs(pProd[2].Eta())<1.6 && pProd[2].Pt()>(-2*fabs(pProd[2].Eta())+5.2)) 
        || (fabs(pProd[2].Eta())>1.6 && fabs(pProd[2].Eta())<2.2 && pProd[2].Pt()>2.0))
        && ((fabs(pProd[3].Eta())<0.8 && pProd[3].Pt()>3.5)
        || (fabs(pProd[3].Eta())>0.8 && fabs(pProd[3].Eta())<1.6 && pProd[3].Pt()>(-2*fabs(pProd[3].Eta())+5.2))
        || (fabs(pProd[3].Eta())>1.6 && fabs(pProd[3].Eta())<2.2 && pProd[3].Pt()>2.0))
	*/
	){
		Ups2Pass = 1;
		//nUps2PolarizationPassed += Ups2Polarization;
		nUps2Pass++;
	}

	if(Ups1Pass && Ups2Pass)
	{
		nPassed++;
		//nUps1Ups2PolarizationPassed += Ups1Polarization*Ups2Polarization;
	} 

	
	/*
	myMu1RecoEta->Fill(pProd[0].Eta());
	myMu2RecoEta->Fill(pProd[2].Eta());

	myMu1RecoPt->Fill(pProd[1].Px());
	myMu2RecoPt->Fill(pProd[1].Py());
	myMu3RecoPt->Fill(pProd[1].Pz());
	myMu4RecoPt->Fill(mu4.Py());
	*/

	//earse vector
	pProd.erase(pProd.begin(),pProd.end());

	}//End loop for each event



	/*
	//Default
	cout<<"Default "<<endl;
	cout<<"Isotropic Decay = "<<nPassed/nGenerated
	<<"; Transverse Polarization = "<<nTransversePolPassed/nTransversePol
	<<" ; Longitudinal Polazization = "<<nLongitudePolPassed/nLongitudePol<<endl;
	
	cout<<"Single Upsilon "<<endl;
	cout<<"Isotropic Decay = "<<nUps1Pass/nGenerated*nUps2Pass/nGenerated
	<<"; Transverse Polarization="<<nUps1PolarizationPassed/nUps1Polarization*nUps2PolarizationPassed/nUps2Polarization
	<<"; Longitudinal Polarization="<<nUps1LongitudePolPassed/nUps1LongitudePol*nUps2LongitudePolPassed/nUps2LongitudePol<<endl;

	cout<<"**********************"<<endl;
	*/

	myUps1AccPtVsEta->Fill(fabs(Upsilon1.Rapidity()),Upsilon1.Pt(),nPassed/nGenerated);
	myUps2AccPtVsEta->Fill(fabs(Upsilon2.Rapidity()),Upsilon2.Pt(),nPassed/nGenerated);

	//Adding follwoing line, because closure test was not closed
	outfile<<evtNumAcc<<" "<<runNumAcc<<" "<<(double)nPassed/nGenerated<<" "<<nUps1Pass/nGenerated*nUps2Pass/nGenerated<<std::endl;

	//Following format is for acceptance definition
	/*
	outfile<<Upsilon1.Rapidity()<<" "<<Upsilon1.P()<<" "<<Upsilon1.Pt()<<
                " "<<Upsilon2.Rapidity()<<" "<<Upsilon2.P()<<" "<<Upsilon2.Pt()<<
                " "<<nPassed/nGenerated<<" "<<nUps1Pass/nGenerated<<" "<<nUps2Pass/nGenerated<<endl;
	*/

	myEvtByEvtAcceptance->Fill((double)nPassed/nGenerated);
	myTotAccVsSingleAcc->Fill(nUps1Pass/nGenerated*nUps2Pass/nGenerated,nPassed/nGenerated);

	}//End txt file for events
	
	fp.close();

	cout<<"***************************"<<endl;
	cout<<"Total Eff = "<<IsotropicTotalAcc<<"; Polarization = "<<PolarizationTotalAcc<<endl;
	cout<<"Single EFf = "<<IsotropicSingleAcc<<"; Polarization = "<<PolarizationSingleAcc<<endl;
	//cout<<"******Relative Change*********"<<endl;
	//cout<<"For Combined Eff = "<<(-IsotropicTotalAcc+PolarizationTotalAcc)/IsotropicTotalAcc<<endl;
	//cout<<"For Separate Eff = "<<(-IsotropicSingleAcc+PolarizationSingleAcc)/IsotropicSingleAcc<<endl;


	myEvtByEvtEfficiency->GetXaxis()->SetTitle("Event By Event Efficiency #epsilon_{i}");
	myEvtByEvtEfficiency->GetYaxis()->SetTitle("Arbitrary Units");
	myEvtByEvtEfficiency->GetXaxis()->SetTitleSize(0.045);
	myEvtByEvtEfficiency->GetXaxis()->SetTitleOffset(1.);
	myEvtByEvtEfficiency->GetYaxis()->SetTitleOffset(0.8);
	myEvtByEvtEfficiency->GetYaxis()->SetTitleSize(0.045);
	myEvtByEvtEfficiency->SetMarkerStyle(20);
	//myEvtByEvtEfficiency->Draw("EP");

	myOverallEvtByEvtEff->GetXaxis()->SetTitle("Acceptance x Efficiency #epsilon_{i}*a_{i}");
        myOverallEvtByEvtEff->GetYaxis()->SetTitle("Arbitrary Units");
        myOverallEvtByEvtEff->GetXaxis()->SetTitleSize(0.045);
        myOverallEvtByEvtEff->GetXaxis()->SetTitleOffset(1.);
        myOverallEvtByEvtEff->GetYaxis()->SetTitleOffset(0.8);
        myOverallEvtByEvtEff->GetYaxis()->SetTitleSize(0.045);
        myOverallEvtByEvtEff->SetMarkerStyle(20);

	myEvtByEvtAcc_PercentErr->GetXaxis()->SetTitle("Statistical Uncertainty of Acceptance (%)");	
	myEvtByEvtAcc_PercentErr->GetYaxis()->SetTitle("Arbitrary Units");
	myEvtByEvtAcc_PercentErr->GetXaxis()->SetTitleSize(0.045);
        myEvtByEvtAcc_PercentErr->GetXaxis()->SetTitleOffset(1.);
        myEvtByEvtAcc_PercentErr->GetYaxis()->SetTitleOffset(0.8);
        myEvtByEvtAcc_PercentErr->GetYaxis()->SetTitleSize(0.045);
        myEvtByEvtAcc_PercentErr->SetMarkerStyle(20);

	myEvtByEvtEff_PercentErr->GetXaxis()->SetTitle("Statistical Uncertainty of Efficiency (%)");              
        myEvtByEvtEff_PercentErr->GetYaxis()->SetTitle("Arbitrary Units");
        myEvtByEvtEff_PercentErr->GetXaxis()->SetTitleSize(0.045);
        myEvtByEvtEff_PercentErr->GetXaxis()->SetTitleOffset(1.);
        myEvtByEvtEff_PercentErr->GetYaxis()->SetTitleOffset(0.8);
        myEvtByEvtEff_PercentErr->GetYaxis()->SetTitleSize(0.045);
        myEvtByEvtEff_PercentErr->SetMarkerStyle(20);

	myEvtByEvtAcceptance->GetXaxis()->SetTitle("Acceptance a_{i}");
        myEvtByEvtAcceptance->GetYaxis()->SetTitle("Arbitrary Units");
        myEvtByEvtAcceptance->GetXaxis()->SetTitleSize(0.045);
        myEvtByEvtAcceptance->GetXaxis()->SetTitleOffset(1.);
        myEvtByEvtAcceptance->GetYaxis()->SetTitleOffset(0.8);
        myEvtByEvtAcceptance->GetYaxis()->SetTitleSize(0.045);
        myEvtByEvtAcceptance->SetMarkerStyle(20);
	
	myhbk->cd();

	myTotAccVsSingleAcc->Write();
	myEvtByEvtAcc_PercentErr->Write();
	myEvtByEvtEff_PercentErr->Write();
	myEvtByEvtTot_PercentErr->Write();
	myUps1AccPtVsEta->Write();
	myUps2AccPtVsEta->Write();
	myMu1RecoPt->Write();
	myMu2RecoPt->Write();
	myMu3RecoPt->Write();
	myMu4RecoPt->Write();
	myMu1RecoEta->Write();
	myMu2RecoEta->Write();

	myTransversePol1->Write();
        myLongtPol1->Write();
        myTransversePol2->Write();
        myLongtPol2->Write();
        myIsoTropic->Write();
	myAngleMu1VsMu2->Write();
	myAngleMu3VsMu4->Write();
	myUpsilonGunEff->Write();
	myEvtByEvtAcceptance->Write();
	myEvtByEvtEfficiency->Write();
	myOverallEvtByEvtEff->Write();
	myhbk->Close();


}

