#include "TF1"
#include <TH2.h>
#include <iostream>
void plotReverseMomentumandEvtMix()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);
	gStyle->SetHistFillColor(kBlue);
	gStyle->SetOptFit(11111);


	TFile * f1=new TFile("myoutputreverseMomentum.root");
	TFile * f2=new TFile("myoutputEventMixFromreversemomentum.root");

	TH1F* myBinErrorforRevMom = new TH1F("myBinErrorforRevMom","myBinErrorforRevMom",125,0.0,50.0);
	
	f1->cd();
	TCanvas* myc1=new TCanvas("myc1","mymumueeMass",800,600);
	myFourMuonReversedEachMuonPxPyHist->Rebin(4);
	myFourMuonReversedEachMuonPxPyHist->GetXaxis()->SetRange(32,125);
	myFourMuonReversedEachMuonPxPyHist->SetTitle("");
	myFourMuonReversedEachMuonPxPyHist->GetXaxis()->SetTitleSize(0.06);
	myFourMuonReversedEachMuonPxPyHist->GetYaxis()->SetTitleSize(0.06);
	myFourMuonReversedEachMuonPxPyHist->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonReversedEachMuonPxPyHist->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonReversedEachMuonPxPyHist->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	myFourMuonReversedEachMuonPxPyHist->GetYaxis()->SetTitle("Candidates/400 MeV");
	// myFourMuonMassHist->SetMaximum(135);
	// myFourMuonMassHist->SetNormFactor(850000);
	// myFourMuonReversedEachMuonPxPyHist->Draw("e1");

	TH1F * hrevmom = myFourMuonReversedEachMuonPxPyHist->Clone();
	TH1F * hrevmom1 = myFourMuonReversedEachMuonPxPyHist->Clone();

	f2->cd();
	myEventMixingMassHistfinebin->Rebin(4);
	myEventMixingMassHistfinebin->SetLineColor(2);
	myEventMixingMassHistfinebin->SetNormFactor(11980);
	// myEventMixingMassHistfinebin->SetNormFactor(13356);
	// myEventMixingMassHistfinebin->Draw("same");

	TH1F * hrevmomandEvtMix = myEventMixingMassHistfinebin->Clone();
	// hrevmomandEvtMix->Draw();
	// myEventMixingMassHistfinebin->Draw();
	

	double nrevmom = hrevmom->GetEntries();
	double nevtmix = hrevmomandEvtMix->GetEntries();
	cout<<nrevmom<<" "<<nevtmix<<endl;
	double myscalefactor = nrevmom/nevtmix;
	cout<<myscalefactor<<endl;

	for (int i = 1; i < hrevmom->GetNbinsX(); ++i)
	{
		myBinErrorforRevMom->SetBinContent(i, hrevmom->GetBinError(i) );
		 // cout<<i<<" "<<hrevmom->GetBinContent(i)<<endl;
		 // cout<<i<<" "<<hrevmom->GetBinError(i)<<endl;
	
	}

	// myBinErrorforRevMom->Draw();
	hrevmom->Add(hrevmomandEvtMix, -1);
	hrevmom->Divide(myBinErrorforRevMom);
	hrevmom->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	hrevmom->GetYaxis()->SetTitle("pull");

	// TCanvas *c2 = new TCanvas("c2","Image example",200,10,700,700);

	hrevmom->Draw();

	TLine *line = new TLine(12.5,0.0,50.0,0.0);
	line->SetLineColor(kRed);
	line->Draw();

	double npulltotal = 0.0;
	for (int i = 32; i < hrevmom->GetNbinsX(); ++i)
	{
		npulltotal = npulltotal + hrevmom->GetBinContent(i);
		cout<<"i="<<i<<" bin Content = "<<hrevmom->GetBinContent(i)<<endl;
	}
	

	cout<<"npulltotal="<<npulltotal<<endl;

	
}
