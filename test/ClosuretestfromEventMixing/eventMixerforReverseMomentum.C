#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream> 
#include "TLorentzVector.h"
#include "TPoint.h"
// #include "TMath.h" 
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <TH1F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TF1.h>
// gStyle->SetOptFit(11111);


void eventMixerforReverseMomentum()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(10);
	gStyle->SetStatY(0.9);
	gStyle->SetStatX(0.9);
	// gStyle->SetStatStyle(1011);
	gStyle->SetStatTextColor(2);
	// gStyle->SetHistFillColor(kBlue);
	gStyle->SetOptFit(11111);

	TFile* myoutput = new TFile ("myoutputEventMixFromreversemomentum.root","recreate");

	TH1F* myMuMuPairsDihedralat18dot5GeV = new TH1F("myMuMuPairsDihedralat18dot5GeV","myMuMuPairsDihedralat18dot5GeV",20,0,3.142);
	TH1F* myMuMuPairsDihedralatSideband = new TH1F("myMuMuPairsDihedralatSideband","myMuMuPairsDihedralatSideband",20,0,3.142);
	TH1F* myMuMuPairsHelicityat18dot5GeV = new TH1F("myMuMuPairsHelicityat18dot5GeV","myMuMuPairsHelicityat18dot5GeV",22,-1.1,1.1);
	TH1F* myMuMuPairsHelicityatSideband = new TH1F("myMuMuPairsHelicityatSideband","myMuMuPairsHelicityatSideband",22,-1.1,1.1);
	TH1F* myMupmumu1Helicityat18dot5GeV = new TH1F("myMupmumu1Helicityat18dot5GeV","myMupmumu1Helicityat18dot5GeV",22,-1.1,1.1);
	TH1F* myMupmumu1HelicityatSideband = new TH1F("myMupmumu1HelicityatSideband","myMupmumu1HelicityatSideband",22,-1.1,1.1);
	TH1F* myMupmumu2Helicityat18dot5GeV = new TH1F("myMupmumu2Helicityat18dot5GeV","myMupmumu2Helicityat18dot5GeV",22,-1.1,1.1);
	TH1F* myMupmumu2HelicityatSideband = new TH1F("myMupmumu2HelicityatSideband","myMupmumu2HelicityatSideband",22,-1.1,1.1);
	
	TH1F* myEventMixingMassHistfinebin = new TH1F("myEventMixingMassHistfinebin","myEventMixingMassHistfinebin",500,0.0,50.0);
	TH1F* myEventMixingMassHist = new TH1F("myEventMixingMassHist","myEventMixingMassHist",250,0.0,50.0);
	TH1F* myEventMixingMassHist1 = new TH1F("myEventMixingMassHist1","myEventMixingMassHist1",90,12.0,30.0);
	TH1F* myEventMixingMassHist2 = new TH1F("myEventMixingMassHist2","myEventMixingMassHist2",55,14.0,25.0);

	TH1F* myFourMuonMassHist = new TH1F("myFourMuonMassHist","myFourMuonMassHist",500,0.0,50.0);

	TH1F* myFourMuonReversedV1PxHist = new TH1F("myFourMuonReversedV1PxHist","myFourMuonReversedV1PxHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1PyHist = new TH1F("myFourMuonReversedV1PyHist","myFourMuonReversedV1PyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1PzHist = new TH1F("myFourMuonReversedV1PzHist","myFourMuonReversedV1PzHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1PxPyHist = new TH1F("myFourMuonReversedV1PxPyHist","myFourMuonReversedV1PxPyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV2PxHist = new TH1F("myFourMuonReversedV2PxHist","myFourMuonReversedV2PxHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV2PyHist = new TH1F("myFourMuonReversedV2PyHist","myFourMuonReversedV2PyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV2PxPyHist = new TH1F("myFourMuonReversedV2PxPyHist","myFourMuonReversedV2PxPyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1V2PxPyHist = new TH1F("myFourMuonReversedV1V2PxPyHist","myFourMuonReversedV1V2PxPyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV11PxHist = new TH1F("myFourMuonReversedV11PxHist","myFourMuonReversedV11PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV11PyHist = new TH1F("myFourMuonReversedV11PyHist","myFourMuonReversedV11PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV12PxHist = new TH1F("myFourMuonReversedV12PxHist","myFourMuonReversedV12PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV12PyHist = new TH1F("myFourMuonReversedV12PyHist","myFourMuonReversedV12PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV21PxHist = new TH1F("myFourMuonReversedV21PxHist","myFourMuonReversedV21PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV21PyHist = new TH1F("myFourMuonReversedV21PyHist","myFourMuonReversedV21PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV22PxHist = new TH1F("myFourMuonReversedV22PxHist","myFourMuonReversedV22PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV22PyHist = new TH1F("myFourMuonReversedV22PyHist","myFourMuonReversedV22PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedEachMuonPxPyHist = new TH1F("myFourMuonReversedEachMuonPxPyHist","myFourMuonReversedEachMuonPxPyHist",500,0.0,50.0);

	TH1F* myDoubleMuonHist = new TH1F("myDoubleMuonHist","myDoubleMuonHist",250,0.0,50.0);

	std::vector<TLorentzVector> P4Vector1,P4Vector2, P4Vector11, P4Vector12, P4Vector21,P4Vector22;
	std::vector<float> mvector1,mvector2;


	std::ifstream infile("myoutfilereversemomentum.txt");
	float px1,py1,pz1,m1,px2,py2,pz2,m2, px11,py11,pz11,px12,py12,pz12,px21,py21,pz21,px22,py22,pz22;
	TLorentzVector p4,p4_1,p4_2;
	const double ele_mass = 0.000510998;
	const double muon_mass =  0.105658;


	while(infile)
	{
		infile>>px1>>py1>>pz1>>m1>>px2>>py2>>pz2>>m2>>px11>>py11>>pz11>>px12>>py12>>pz12>>px21>>py21>>pz21>>px22>>py22>>pz22;
		


		p4_1.SetXYZM(px1,py1,pz1,m1);
		p4_2.SetXYZM(px2,py2,pz2,m2);
		//
		// if( (p4_1+p4_2).M() > 13.0 && (p4_1+p4_2).M() < 25.0 )
		{
			P4Vector1.push_back(p4_1);
			P4Vector2.push_back(p4_2);

			mvector1.push_back(m1);
			mvector2.push_back(m2);

			p4.SetXYZM(px11,py11,pz11,muon_mass);
			P4Vector11.push_back(p4);

			p4.SetXYZM(px12,py12,pz12,muon_mass);
			P4Vector12.push_back(p4);

			p4.SetXYZM(px21,py21,pz21,ele_mass);
			P4Vector21.push_back(p4);

			p4.SetXYZM(px22,py22,pz22,ele_mass);
			P4Vector22.push_back(p4);

		}
		
	}
	cout<<P4Vector1.size()<<endl;
	cout<<P4Vector2.size()<<endl;
	//return;
	

	for(int i=0; i < P4Vector1.size(); i++)
	{
		// if( (P4Vector1[i]+P4Vector2[i]).M() < 13.0 && (P4Vector1[i]+P4Vector2[i]).M() > 25.0 ) continue;
		if(i%100==0) cout<<"i="<<i<<endl;
		cout<<"i="<<i<<endl;
		
		for(int j=0; j<P4Vector2.size(); j++)
		{
			TLorentzVector tmpp4, tmpp41,tmpp42;
			tmpp41=P4Vector11[i]+P4Vector12[i]; tmpp42=P4Vector21[j]+P4Vector22[j];

			float mydr=P4Vector1[i].Vect().DeltaR(  P4Vector2[i].Vect());
			float mydrx=P4Vector1[i].Vect().DeltaR(  P4Vector2[j].Vect());
			tmpp4 = tmpp41+tmpp42;
			
			if(i!=j)
			{
				if(1
					
					&& fabs(mydr)> 1.0*fabs(mydrx) 
					&& fabs(mvector2[i]-mvector2[j])<0.5*mvector2[i] 			   					   		
					)
				{
					

					myEventMixingMassHistfinebin->Fill(tmpp4.M());
					myEventMixingMassHist->Fill(tmpp4.M());
					myEventMixingMassHist1->Fill(tmpp4.M());
					myEventMixingMassHist2->Fill(tmpp4.M());
				}

				
			}
			if(i==j)
			{
				myFourMuonMassHist->Fill(tmpp4.M());
			}
			
		}

	}


	myEventMixingMassHistfinebin->Write();
	myEventMixingMassHist->Write();
	myEventMixingMassHist1->Write();
	myEventMixingMassHist2->Write();
	myFourMuonMassHist->Write();

	


	
	


	// Suleyman// canvas // 
	
	TCanvas* myc1=new TCanvas("myc1","myMyXPt",800,600);
	myEventMixingMassHistfinebin->Rebin(4);
	myEventMixingMassHistfinebin->SetTitle("");
	myEventMixingMassHistfinebin->GetXaxis()->SetTitleSize(0.06);
	myEventMixingMassHistfinebin->GetXaxis()->SetRange(25,125);
	myEventMixingMassHistfinebin->GetYaxis()->SetTitleSize(0.06);
	myEventMixingMassHistfinebin->GetXaxis()->SetTitleOffset(0.7);
	myEventMixingMassHistfinebin->GetYaxis()->SetTitleOffset(0.8);
	myEventMixingMassHistfinebin->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}e^{+}e^{-}) [GeV]");
	myEventMixingMassHistfinebin->GetYaxis()->SetTitle("Candidates/400 MeV");
	myEventMixingMassHistfinebin->Fit("pol8","","",13.0, 45.0); // 12-35	
	myc1->SaveAs("ReverseandEventMix.pdf");

	



	// TCanvas* myc3=new TCanvas("myc3","BkgModelandDefaultFourmuMass",800,600);
	// myFourMuonMassHist->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	// myFourMuonMassHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	// myFourMuonMassHist->SetLineColor(2);
	// myFourMuonMassHist->Draw("e1");

	// myFourMuonReversedEachMuonPxPyHist->SetNormFactor(4341);
	// myFourMuonReversedEachMuonPxPyHist->SetLineColor(4);
	// myFourMuonReversedEachMuonPxPyHist->Draw("e1same");
	
	// myc3->SaveAs("BkgModelandDefaultFourmuMass.pdf");







	 // TCanvas* myc2=new TCanvas("myc2","BkgModel",800,600);
	 // myFourMuonReversedEachMuonPxPyHist->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	 // myFourMuonReversedEachMuonPxPyHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	 // myFourMuonMassHist->Draw("e1");
	 // myFourMuonReversedEachMuonPxPyHist->Fit("pol8","","",12.0,35.0);
	// myc2->SaveAs("BkgModel.pdf");





	// TCanvas* myc2=new TCanvas("myc2","BkgModel",800,600);
	// myFourMuonReversedV1V2PxPyHist->Rebin(6);
	// myFourMuonReversedV1V2PxPyHist->SetTitle("");
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetTitleSize(0.06);
	// myFourMuonReversedV1V2PxPyHist->GetYaxis()->SetTitleSize(0.06);
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetTitleOffset(0.7);
	// myFourMuonReversedV1V2PxPyHist->GetYaxis()->SetTitleOffset(0.8);
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetTitle("m((#mu^{+}#mu^{-})_{1}(#mu^{+}#mu^{-})_{2}) [GeV]");
	// myFourMuonReversedV1V2PxPyHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	// myFourMuonReversedV1V2PxPyHist->Draw("e1");
	// myFourMuonReversedV1V2PxPyHist->Fit("pol5","","",13.0,25.0);
	// myc2->SaveAs("reversedv1v2pxpy.pdf");
	// myc2->SaveAs("reversedv1v2pxpy.gif");






}
