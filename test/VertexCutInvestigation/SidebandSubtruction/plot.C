#include "TF1"
#include <iostream>
void plot()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(10);
	gStyle->SetStatY(0.9);
	gStyle->SetStatX(0.9);
	// gStyle->SetStatStyle(1011);
	gStyle->SetStatTextColor(2);
	gStyle->SetHistFillColor(kBlue);
	// gStyle->SetOptFit(11111);
	// gStyle->SetOptFit(00000);


	TFile * f1=new TFile("combineddefaultandptdistributions.root");
	TCanvas* myc1=new TCanvas("myc1","Combined_11_Default",800,600);
	// myMuMumassforV1highpair->Rebin();
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

	h->Add(myMuMu2MassatSideband,-1);
	// myMuMu2MassatSideband->Draw();
	h->Draw();

}
