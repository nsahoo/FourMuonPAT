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


void SidebandSubtructor()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);


	TFile * f=new TFile("Combined2011and2012Default.root");
	
	TCanvas* myc1=new TCanvas("myc1","myVtxProb",800,600);
	myVtxProbat18dot5GeV->SetTitle("");
	myVtxProbat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myVtxProbat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myVtxProbat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myVtxProbat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myVtxProbat18dot5GeV->GetXaxis()->SetTitle("4#mu Vtx-prob");
	myVtxProbat18dot5GeV->GetYaxis()->SetTitle("Events/0.05");
	myVtxProbat18dot5GeV->Rebin(50);
	myVtxProbat18dot5GeV->Sumw2();
	// myVtxProbat18dot5GeV->SetNormFactor(422);
	// myVtxProbat18dot5GeV->Draw();

	// myVtxProbatatSideband->SetNormFactor(288);
	// myVtxProbatatSideband->Rebin(50);
	// myVtxProbatatSideband->SetLineColor(2);
	// myVtxProbatatSideband->Draw("same");



	float nEntriesSignal, nEntriesSideband;
	float nSignalYield = 65.0;
	nEntriesSignal = myVtxProbat18dot5GeV->GetEntries();
	nEntriesSideband = myVtxProbatatSideband->GetEntries();
	float myScaleFactor = (nEntriesSignal - nSignalYield)/nEntriesSideband;
	cout<<"nEntriesSignal="<<nEntriesSignal<<endl;
	cout<<"nEntriesSideband="<<nEntriesSideband<<endl;
	// cout<<myScaleFactor<<endl;
	myVtxProbatatSideband->Rebin(50);
	myVtxProbatatSideband->Sumw2();
	// myVtxProbatatSideband->Scale(myScaleFactor);
	myVtxProbatatSideband->SetNormFactor(nEntriesSignal - nSignalYield);
	
	TH1F *h = (TH1F *) gDirectory->Get("myVtxProbat18dot5GeV");

	h->SetTitle("");
	h->GetXaxis()->SetTitleSize(0.06);
	h->GetYaxis()->SetTitleSize(0.06);
	h->GetXaxis()->SetTitleOffset(0.7);
	h->GetYaxis()->SetTitleOffset(0.9);
	h->GetXaxis()->SetTitle("4#mu Vtx-prob");
	h->GetYaxis()->SetTitle("Events/0.05");
	h->Add(myVtxProbatatSideband,-1);
	h->SetLineColor(2);
	h->Draw();
	// myVtxProbat18dot5GeV->Draw("same");
	
}
