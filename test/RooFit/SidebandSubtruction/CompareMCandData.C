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


void CompareMCandData()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);

	const Int_t NBINS = 6;
	Double_t edges[NBINS + 1] = {0.05, 0.1, 0.2, 0.4, 0.6, 0.8,1.0};
	TH1F * hdata=new TH1F("hdata","hdata",NBINS,edges);
	TH1F * hMC=new TH1F("hMC","hMC",NBINS,edges);
	
	TCanvas* myc1=new TCanvas("myc1","myVtxProb",800,600);
	// myc1->SetGrid();
	double dataAr[6] = {17.4,15.3,18.1,0.0,8.0,14.7};
	double dataArEr[6] = {6.6,6.9,7.6,10.0,5.6,6.5};
	double MCAr[6] = {715,1431,2854,3042,3416,3981};
	double MCArEr[6] = {27,38,53,55,58,63};


	for (int i = 0; i < 6; ++i)
	{
		hdata->SetBinContent(i+1,dataAr[i]);
		hdata->SetBinError(i+1,dataArEr[i]);
		hMC->SetBinContent(i+1,MCAr[i]);
		hMC->SetBinError(i+1,MCArEr[i]);
	}

	float nEntriesData, nEntriesMC;
	nEntriesData = hdata->GetEntries();
	nEntriesMC = hMC->GetEntries();
	cout<<"nEntriesData="<<nEntriesData<<endl;
	cout<<"nEntriesMC="<<nEntriesMC<<endl;
	// hdata->SumW2();
	hdata->SetTitle("");
	hdata->GetXaxis()->SetTitleSize(0.06);
	hdata->GetYaxis()->SetTitleSize(0.06);
	hdata->GetXaxis()->SetTitleOffset(0.7);
	hdata->GetYaxis()->SetTitleOffset(0.7);
	hdata->GetXaxis()->SetTitle("4#mu Vtx-prob");
	hdata->GetYaxis()->SetTitle("Events(Normalized)");
	hdata->DrawNormalized("e1");
	hMC->SetLineColor(2);
	// hMC->Sumw2();
	hMC->DrawNormalized("samee1");


	// TLine *line1 = new TLine(0.05,(myMaxNLL+1),0.05,(myMaxNLL+1));
	// line1->SetLineColor(kRed);
	// line1->Draw();


	// myVtxProbat18dot5GeV->SetTitle("");
	// myVtxProbat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	// myVtxProbat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	// myVtxProbat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	// myVtxProbat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	// myVtxProbat18dot5GeV->GetXaxis()->SetTitle("4#mu Vtx-prob");
	// myVtxProbat18dot5GeV->GetYaxis()->SetTitle("Events/0.05");
	// myVtxProbat18dot5GeV->Rebin(50);
	// myVtxProbat18dot5GeV->Sumw2();
	// // myVtxProbat18dot5GeV->SetNormFactor(422);
	// // myVtxProbat18dot5GeV->Draw();

	// // myVtxProbatatSideband->SetNormFactor(288);
	// // myVtxProbatatSideband->Rebin(50);
	// // myVtxProbatatSideband->SetLineColor(2);
	// // myVtxProbatatSideband->Draw("same");



	// float nEntriesSignal, nEntriesSideband;
	// float nSignalYield = 65.0;
	// nEntriesSignal = myVtxProbat18dot5GeV->GetEntries();
	// nEntriesSideband = myVtxProbatatSideband->GetEntries();
	// float myScaleFactor = (nEntriesSignal - nSignalYield)/nEntriesSideband;
	// cout<<"nEntriesSignal="<<nEntriesSignal<<endl;
	// cout<<"nEntriesSideband="<<nEntriesSideband<<endl;
	// // cout<<myScaleFactor<<endl;
	// myVtxProbatatSideband->Rebin(50);
	// myVtxProbatatSideband->Sumw2();
	// // myVtxProbatatSideband->Scale(myScaleFactor);
	// myVtxProbatatSideband->SetNormFactor(nEntriesSignal - nSignalYield);
	
	// TH1F *h = (TH1F *) gDirectory->Get("myVtxProbat18dot5GeV");

	// h->SetTitle("");
	// h->GetXaxis()->SetTitleSize(0.06);
	// h->GetYaxis()->SetTitleSize(0.06);
	// h->GetXaxis()->SetTitleOffset(0.7);
	// h->GetYaxis()->SetTitleOffset(0.9);
	// h->GetXaxis()->SetTitle("4#mu Vtx-prob");
	// h->GetYaxis()->SetTitle("Events/0.05");
	// h->Add(myVtxProbatatSideband,-1);
	// h->SetLineColor(2);
	// h->Draw();
	// // myVtxProbat18dot5GeV->Draw("same");
	
}
