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
	
	f1->cd();

	TCanvas* myc1=new TCanvas("myc1","myMuPtData",800,600);
	// myGenMu1PtHist->GetXaxis()->SetRange(0.0,10.0);
	// myMuMuMuMumassV1mumubelowV1->GetYaxis()->SetRange(0,1000);
	myMu1Ptat18dot5GeV->SetTitle("");
	myMu1Ptat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMu1Ptat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMu1Ptat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMu1Ptat18dot5GeV->GetYaxis()->SetTitleOffset(0.9);
	myMu1Ptat18dot5GeV->GetXaxis()->SetTitle("#mu p_{T}");
	myMu1Ptat18dot5GeV->GetYaxis()->SetTitle("Candidates/100 MeV");
	myMu1Ptat18dot5GeV->SetMaximum(250);
	myMu1Ptat18dot5GeV->Draw();

	myMu2Ptat18dot5GeV->SetLineColor(2);
	myMu2Ptat18dot5GeV->Draw("same");

	myMu3Ptat18dot5GeV->SetLineColor(3);
	myMu3Ptat18dot5GeV->Draw("same");

	myMu4Ptat18dot5GeV->SetLineColor(4);
	myMu4Ptat18dot5GeV->Draw("same");
							  
	
	TLegend* leg1 = new TLegend(0.60,0.65,0.90,0.90,NULL,"brNDC");
	leg1->SetFillColor(0);
	leg1->SetHeader("#mu p_{T} Dist. from Data");
	leg1->AddEntry("Mu1PtHist","#mu_{1} p_{T}","l");
	leg1->AddEntry("Mu2PtHist","#mu_{2} p_{T}","l");
	leg1->AddEntry("Mu3PtHist","#mu_{3} p_{T}","l");
	leg1->AddEntry("Mu4PtHist","#mu_{4} p_{T}","l");
	leg1->Draw();
	myc1->SaveAs("MuPtFromData.pdf");
	myc1->SaveAs("MuPtFromData.gif");


	f2->cd();




	TCanvas* myc2=new TCanvas("myc2","myMuPtHiggs",800,600);
	// myGenMu1PtHist->GetXaxis()->SetRange(0.0,10.0);
	// myMuMuMuMumassV1mumubelowV1->GetYaxis()->SetRange(0,1000);
	myMu1Ptat18dot5GeV->SetTitle("");
	myMu1Ptat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMu1Ptat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMu1Ptat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMu1Ptat18dot5GeV->GetYaxis()->SetTitleOffset(0.9);
	myMu1Ptat18dot5GeV->GetXaxis()->SetTitle("#mu p_{T}");
	myMu1Ptat18dot5GeV->GetYaxis()->SetTitle("Candidates/100 MeV");
	myMu1Ptat18dot5GeV->SetMaximum(900);
	myMu1Ptat18dot5GeV->Draw();

	myMu2Ptat18dot5GeV->SetLineColor(2);
	myMu2Ptat18dot5GeV->Draw("same");

	myMu3Ptat18dot5GeV->SetLineColor(3);
	myMu3Ptat18dot5GeV->Draw("same");

	myMu4Ptat18dot5GeV->SetLineColor(4);
	myMu4Ptat18dot5GeV->Draw("same");
							  
	
	TLegend* leg2 = new TLegend(0.60,0.65,0.90,0.90,NULL,"brNDC");
	leg2->SetFillColor(0);
	leg2->SetHeader("#mu p_{T} Dist. H_{0} MC");
	leg2->AddEntry("Mu1PtHist","#mu_{1} p_{T}","l");
	leg2->AddEntry("Mu2PtHist","#mu_{2} p_{T}","l");
	leg2->AddEntry("Mu3PtHist","#mu_{3} p_{T}","l");
	leg2->AddEntry("Mu4PtHist","#mu_{4} p_{T}","l");
	leg2->Draw();
	myc2->SaveAs("MuPtFromHiggs.pdf");
	myc2->SaveAs("MuPtFromHiggs.gif");






















	// f1->cd();
	// TCanvas* myc11=new TCanvas("myc11","myMu21Pt_Signal_Sideband_HiggsMC_Overlap",800,600);
	// // myV1VsMuMuMassBeforeVVmasshighpair->Rebin();
	// myMu21Ptstartat18dot5GeV->GetXaxis()->SetRange(0.0,10.0);
	// // myMuMuMuMumassV1mumubelowV1->GetYaxis()->SetRange(0,1000);
	// myMu21Ptstartat18dot5GeV->SetTitle("");
	// myMu21Ptstartat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	// myMu21Ptstartat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	// myMu21Ptstartat18dot5GeV->GetXaxis()->SetTitleOffset(0.6);
	// myMu21Ptstartat18dot5GeV->GetYaxis()->SetTitleOffset(0.8);
	// myMu21Ptstartat18dot5GeV->GetXaxis()->SetTitle("(#mu)_{21} p_T");
	// myMu21Ptstartat18dot5GeV->GetYaxis()->SetTitle("Candidates/1 GeV");
	// // myMu21Ptstartat18dot5GeV->SetNormFactor(383);
	// // myMuMuMuMumassV1mumubelowV1->SetMaximum(40);
	// myMu21Ptstartat18dot5GeV->Draw("e1");

	// myMu21PtstartatSideband->SetNormFactor(283);
	// // myMu21PtstartatSideband->Rebin();
	// myMu21PtstartatSideband->GetXaxis()->SetRange(0.0,10.0);
	// myMu21PtstartatSideband->SetLineColor(2);
	// myMu21PtstartatSideband->Draw("e1same");

	// f2->cd();
	// histHiggs21->GetXaxis()->SetRange(0.0,10.0);
	// histHiggs21->SetNormFactor(383);
	// histHiggs21->SetLineColor(3);
	// histHiggs21->Draw("e1same");

	// f3->cd();
	// histChib21->GetXaxis()->SetRange(0.0,10.0);
	// histChib21->SetNormFactor(383);
	// histChib21->SetLineColor(4);
	// histChib21->Draw("e1same");

	// TLegend* leg1 = new TLegend(0.60,0.65,0.90,0.90,NULL,"brNDC");
	// leg1->SetFillColor(0);
	// f1->cd();
	// leg1->AddEntry("myMu21Ptstartat18dot5GeV","(#mu)_{21} p_T at Sig. Reg. in Data","lep");
	// leg1->AddEntry("myMu21PtstartatSideband","(#mu)_{21} p_T at Sband Reg. in Data","lep");
	// f2->cd();
	// leg1->AddEntry("histHiggs21","(#mu)_{21} p_T from H_{0} MC","lep");
	// f3->cd();
	// leg1->AddEntry("histChib21","(#mu)_{21} p_T from #Chi_{b0} MC","lep");
	// leg1->Draw();




	// myc11->SaveAs("myMu21Pt_Signal_Sideband_HiggsMC_Overlap.pdf");





	// f1->cd();
	// TCanvas* myc12=new TCanvas("myc12","myMu22Pt_Signal_Sideband_HiggsMC_Overlap",800,600);
	// // myV1VsMuMuMassBeforeVVmasshighpair->Rebin();
	// myMu22Ptstartat18dot5GeV->GetXaxis()->SetRange(0.0,10.0);
	// // myMuMuMuMumassV1mumubelowV1->GetYaxis()->SetRange(0,1000);
	// myMu22Ptstartat18dot5GeV->SetTitle("");
	// myMu22Ptstartat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	// myMu22Ptstartat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	// myMu22Ptstartat18dot5GeV->GetXaxis()->SetTitleOffset(0.6);
	// myMu22Ptstartat18dot5GeV->GetYaxis()->SetTitleOffset(0.8);
	// myMu22Ptstartat18dot5GeV->GetXaxis()->SetTitle("(#mu)_{22} p_T");
	// myMu22Ptstartat18dot5GeV->GetYaxis()->SetTitle("Candidates/1 GeV");
	// // myMu22Ptstartat18dot5GeV->SetNormFactor(383);
	// // myMuMuMuMumassV1mumubelowV1->SetMaximum(40);
	// myMu22Ptstartat18dot5GeV->Draw("e1");

	// myMu22PtstartatSideband->SetNormFactor(283);
	// // myMu22PtstartatSideband->Rebin();
	// myMu22PtstartatSideband->GetXaxis()->SetRange(0.0,10.0);
	// myMu22PtstartatSideband->SetLineColor(2);
	// myMu22PtstartatSideband->Draw("e1same");

	// f2->cd();
	// histHiggs22->GetXaxis()->SetRange(0.0,10.0);
	// histHiggs22->SetNormFactor(383);
	// histHiggs22->SetLineColor(3);
	// histHiggs22->Draw("e1same");

	// f3->cd();
	// histChib22->GetXaxis()->SetRange(0.0,10.0);
	// histChib22->SetNormFactor(383);
	// histChib22->SetLineColor(4);
	// histChib22->Draw("e1same");

	// TLegend* leg2 = new TLegend(0.60,0.65,0.90,0.90,NULL,"brNDC");
	// leg2->SetFillColor(0);
	// f1->cd();
	// leg2->AddEntry("myMu22Ptstartat18dot5GeV","(#mu)_{22} p_T at Sig. Reg. in Data","lep");
	// leg2->AddEntry("myMu22PtstartatSideband","(#mu)_{22} p_T at Sband Reg. in Data","lep");
	// f2->cd();
	// leg2->AddEntry("histHiggs22","(#mu)_{22} p_T from H_{0} MC","lep");
	// f3->cd();
	// leg2->AddEntry("histChib22","(#mu)_{22} p_T from #Chi_{b0} MC","lep");
	// leg2->Draw();




	// myc12->SaveAs("myMu22Pt_Signal_Sideband_HiggsMC_Overlap.pdf");






	

}
