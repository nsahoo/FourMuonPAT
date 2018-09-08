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


void plotMass()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);


	TFile * f1=new TFile("combineddefaultandptdistributions.root");
	TFile * f2=new TFile("higgsMCdefaultandptdistributions.root");
	


	f2->cd();
	TCanvas* myc1=new TCanvas("myc1","myMu1Pt",800,600);
	myMuMu2Massat18dot5GeV->SetTitle("");
	myMuMu2Massat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMuMu2Massat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMuMu2Massat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMuMu2Massat18dot5GeV->GetYaxis()->SetTitleOffset(0.9);
	myMuMu2Massat18dot5GeV->GetXaxis()->SetTitle("#mu p_{T}");
	myMuMu2Massat18dot5GeV->GetYaxis()->SetTitle("Candidates/100 MeV");
	// myMu4Ptat18dot5GeV->SetMaximum(250);
	// myMuMu2Massat18dot5GeV->SetNormFactor(65);
	myMuMu2Massat18dot5GeV->Draw();
	f1->cd();

	float nEntriesSignal, nEntriesSideband;
	float nSignalYield = 65.0;
	nEntriesSignal = myMuMu2Massat18dot5GeV->GetEntries();
	nEntriesSideband = myMuMu2MassatSideband->GetEntries();
	float myScaleFactor = (nEntriesSignal - nSignalYield)/nEntriesSideband;
	cout<<"nEntriesSignal="<<nEntriesSignal<<endl;
	cout<<"nEntriesSideband="<<nEntriesSideband<<endl;
	cout<<myScaleFactor<<endl;
	myMuMu2MassatSideband->Scale(myScaleFactor);
	TH1F *h = (TH1F *) gDirectory->Get("myMuMu2Massat18dot5GeV");

	h->SetTitle("");
	h->GetXaxis()->SetTitleSize(0.06);
	h->GetYaxis()->SetTitleSize(0.06);
	h->GetXaxis()->SetTitleOffset(0.7);
	h->GetYaxis()->SetTitleOffset(0.9);
	h->GetXaxis()->SetTitle("m(#mu#mu)_{2}");
	h->GetYaxis()->SetTitle("Candidates/50 MeV");
	h->Add(myMuMu2MassatSideband,-1);
	h->SetLineColor(2);
	h->Draw();
	f2->cd();
	myMuMu2Massat18dot5GeV->Draw("same");
	
}
