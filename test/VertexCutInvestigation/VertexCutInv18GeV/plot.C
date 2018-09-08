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
	gStyle->SetOptFit(00000);


	TFile * f1=new TFile("myMuMuAfterNoVertexCut.root");
	TCanvas* myc1=new TCanvas("myc1","Combined_11_Default",800,600);
	// myMuMumassforV1highpair->Rebin();
	myMuMumassforV1highpair->GetXaxis()->SetRange(400,800);
	myMuMumassforV1highpair->SetTitle("");
	myMuMumassforV1highpair->GetXaxis()->SetTitleSize(0.06);
	myMuMumassforV1highpair->GetYaxis()->SetTitleSize(0.06);
	myMuMumassforV1highpair->GetXaxis()->SetTitleOffset(0.7);
	myMuMumassforV1highpair->GetYaxis()->SetTitleOffset(0.8);
	myMuMumassforV1highpair->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}) [GeV]");
	myMuMumassforV1highpair->GetYaxis()->SetTitle("Candidates/5 MeV");
	// myMuMumassforV1highpair->SetMaximum(135);
	myMuMumassforV1highpair->Draw("e1");

	myc1->SaveAs("MuMuMasswithNo4MuVtxCut.pdf");
	myc1->SaveAs("MuMuMasswithNo4MuVtxCut.gif");

	///////////////////////////////////////////////


}
