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


void plotMC()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);


	TFile * f1=new TFile("combineddefaultandptdistributions.root");
	TFile * f2=new TFile("higgsMCdefaultandptdistributions.root");
	


	f2->cd();
	TCanvas* myc1=new TCanvas("myc1","myMu1Pt",800,600);
	// myMu1Ptat18dot5GeV->SetTitle("");
	// myMu1Ptat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	// myMu1Ptat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	// myMu1Ptat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	// myMu1Ptat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	// myMu1Ptat18dot5GeV->GetXaxis()->SetTitle("#mu_{4} p_{T} [GeV]");
	// myMu1Ptat18dot5GeV->GetYaxis()->SetTitle("Candidates/1 GeV");
	// // myMu1Ptat18dot5GeV->SetMaximum(250);
	myMu1Ptat18dot5GeV->SetNormFactor(65);
	myMu1Ptat18dot5GeV->Draw();
	f1->cd();

	float nEntriesSignal, nEntriesSideband;
	float nSignalYield = 65.0;
	nEntriesSignal = myMu1Ptat18dot5GeV->GetEntries();
	nEntriesSideband = myMu1PtatSideband->GetEntries();
	float myScaleFactor = (nEntriesSignal - nSignalYield)/nEntriesSideband;
	cout<<"nEntriesSignal="<<nEntriesSignal<<endl;
	cout<<"nEntriesSideband="<<nEntriesSideband<<endl;
	cout<<myScaleFactor<<endl;
	myMu1PtatSideband->Scale(myScaleFactor);
	TH1F *h = (TH1F *) gDirectory->Get("myMu1Ptat18dot5GeV");

	h->SetTitle("");
	h->GetXaxis()->SetTitleSize(0.06);
	h->GetYaxis()->SetTitleSize(0.06);
	h->GetXaxis()->SetTitleOffset(0.7);
	h->GetYaxis()->SetTitleOffset(0.7);
	h->GetXaxis()->SetTitle("#mu_{1} p_{T} [GeV]");
	h->GetYaxis()->SetTitle("Candidates/1 GeV");
	h->Add(myMu1PtatSideband,-1);
	h->SetLineColor(2);
	h->Draw();
	f2->cd();
	myMu1Ptat18dot5GeV->Draw("same");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->SetTextColor(2);
	t->DrawLatex(0.70,0.85,"Sideband Subtructed Data");
	t->SetTextColor(4);
	t->DrawLatex(0.70,0.80,"MC");

}
