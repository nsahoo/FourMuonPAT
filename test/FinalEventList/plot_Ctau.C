void plot_Ctau()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);


	TFile * f50=new TFile("output.root");



	TCanvas* myc40=new TCanvas("myc40","myMu12Ctauat18dot5GeV",800,600);

	myMu12Ctauat18dot5GeV->SetTitle("");
	myMu12Ctauat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMu12Ctauat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMu12Ctauat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMu12Ctauat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMu12Ctauat18dot5GeV->GetXaxis()->SetTitle("#mu_{12} c#tau");
	myMu12Ctauat18dot5GeV->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu12Ctauat18dot5GeV->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc40->SaveAs("myMu12Ctauat18dot5GeV.pdf");

	TCanvas* myc41=new TCanvas("myc41","myMu12CtauatSideband",800,600);
	myMu12CtauatSideband->SetTitle("");
	myMu12CtauatSideband->GetXaxis()->SetTitleSize(0.06);
	myMu12CtauatSideband->GetYaxis()->SetTitleSize(0.06);
	myMu12CtauatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMu12CtauatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMu12CtauatSideband->GetXaxis()->SetTitle("#mu_{12} c#tau");
	myMu12CtauatSideband->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu12CtauatSideband->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc41->SaveAs("myMu12CtauatSideband.pdf");


	TCanvas* myc42=new TCanvas("myc42","myMu12CtauSidebandSubtracted",800,600);
	myMu12CtauatSideband->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu12Ctauat18dot5GeV");
	h->Add(myMu12CtauatSideband,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc42->SaveAs("myMu12CtauSidebandSubtracted.pdf");




	////////////////////////////////////////////////////

	TCanvas* myc43=new TCanvas("myc43","myMu34Ctauat18dot5GeV",800,600);

	myMu34Ctauat18dot5GeV->SetTitle("");
	myMu34Ctauat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMu34Ctauat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMu34Ctauat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMu34Ctauat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMu34Ctauat18dot5GeV->GetXaxis()->SetTitle("#mu_{34} c#tau");
	myMu34Ctauat18dot5GeV->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu34Ctauat18dot5GeV->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc43->SaveAs("myMu34Ctauat18dot5GeV.pdf");

	TCanvas* myc44=new TCanvas("myc44","myMu34CtauatSideband",800,600);
	myMu34CtauatSideband->SetTitle("");
	myMu34CtauatSideband->GetXaxis()->SetTitleSize(0.06);
	myMu34CtauatSideband->GetYaxis()->SetTitleSize(0.06);
	myMu34CtauatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMu34CtauatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMu34CtauatSideband->GetXaxis()->SetTitle("#mu_{34} c#tau");
	myMu34CtauatSideband->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu34CtauatSideband->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc44->SaveAs("myMu34CtauatSideband.pdf");


	TCanvas* myc45=new TCanvas("myc45","myMu34CtauSidebandSubtracted",800,600);
	myMu34CtauatSideband->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu34Ctauat18dot5GeV");
	h->Add(myMu34CtauatSideband,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc45->SaveAs("myMu34CtauSidebandSubtracted.pdf");





	////////////////////////////////////////////////////

	TCanvas* myc46=new TCanvas("myc46","myMu14Ctauat18dot5GeV",800,600);

	myMu14Ctauat18dot5GeV->SetTitle("");
	myMu14Ctauat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMu14Ctauat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMu14Ctauat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMu14Ctauat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMu14Ctauat18dot5GeV->GetXaxis()->SetTitle("#mu_{14} c#tau");
	myMu14Ctauat18dot5GeV->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu14Ctauat18dot5GeV->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc46->SaveAs("myMu14Ctauat18dot5GeV.pdf");

	TCanvas* myc47=new TCanvas("myc47","myMu14CtauatSideband",800,600);
	myMu14CtauatSideband->SetTitle("");
	myMu14CtauatSideband->GetXaxis()->SetTitleSize(0.06);
	myMu14CtauatSideband->GetYaxis()->SetTitleSize(0.06);
	myMu14CtauatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMu14CtauatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMu14CtauatSideband->GetXaxis()->SetTitle("#mu_{14} c#tau");
	myMu14CtauatSideband->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu14CtauatSideband->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc47->SaveAs("myMu14CtauatSideband.pdf");


	TCanvas* myc48=new TCanvas("myc48","myMu14CtauSidebandSubtracted",800,600);
	myMu14CtauatSideband->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu14Ctauat18dot5GeV");
	h->Add(myMu14CtauatSideband,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc48->SaveAs("myMu14CtauSidebandSubtracted.pdf");



	////////////////////////////////////////////////////

	TCanvas* myc49=new TCanvas("myc49","myMu23Ctauat18dot5GeV",800,600);

	myMu23Ctauat18dot5GeV->SetTitle("");
	myMu23Ctauat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMu23Ctauat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMu23Ctauat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMu23Ctauat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMu23Ctauat18dot5GeV->GetXaxis()->SetTitle("#mu_{23} c#tau");
	myMu23Ctauat18dot5GeV->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu23Ctauat18dot5GeV->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc49->SaveAs("myMu23Ctauat18dot5GeV.pdf");

	TCanvas* myc50=new TCanvas("myc50","myMu23CtauatSideband",800,600);
	myMu23CtauatSideband->SetTitle("");
	myMu23CtauatSideband->GetXaxis()->SetTitleSize(0.06);
	myMu23CtauatSideband->GetYaxis()->SetTitleSize(0.06);
	myMu23CtauatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMu23CtauatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMu23CtauatSideband->GetXaxis()->SetTitle("#mu_{23} c#tau");
	myMu23CtauatSideband->GetYaxis()->SetTitle("Candidates/5#mum");
	myMu23CtauatSideband->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc50->SaveAs("myMu23CtauatSideband.pdf");


	TCanvas* myc51=new TCanvas("myc51","myMu23CtauSidebandSubtracted",800,600);
	myMu23CtauatSideband->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu23Ctauat18dot5GeV");
	h->Add(myMu23CtauatSideband,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc51->SaveAs("myMu23CtauSidebandSubtracted.pdf");






	////////////////////////////////////////////////////

	TCanvas* myc52=new TCanvas("myc52","myFourMuonCtauat18dot5GeV",800,600);

	myFourMuonCtauat18dot5GeV->SetTitle("");
	myFourMuonCtauat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myFourMuonCtauat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myFourMuonCtauat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonCtauat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonCtauat18dot5GeV->GetXaxis()->SetTitle("4#mu c#tau");
	myFourMuonCtauat18dot5GeV->GetYaxis()->SetTitle("Candidates/5#mum");
	myFourMuonCtauat18dot5GeV->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc52->SaveAs("myFourMuonCtauat18dot5GeV.pdf");

	TCanvas* myc53=new TCanvas("myc53","myFourMuonCtauatSideband",800,600);
	myFourMuonCtauatSideband->SetTitle("");
	myFourMuonCtauatSideband->GetXaxis()->SetTitleSize(0.06);
	myFourMuonCtauatSideband->GetYaxis()->SetTitleSize(0.06);
	myFourMuonCtauatSideband->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonCtauatSideband->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonCtauatSideband->GetXaxis()->SetTitle("4#mu c#tau");
	myFourMuonCtauatSideband->GetYaxis()->SetTitle("Candidates/5#mum");
	myFourMuonCtauatSideband->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc53->SaveAs("myFourMuonCtauatSideband.pdf");


	TCanvas* myc54=new TCanvas("myc54","myFourMuonCtauSidebandSubtracted",800,600);
	myFourMuonCtauatSideband->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myFourMuonCtauat18dot5GeV");
	h->Add(myFourMuonCtauatSideband,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc54->SaveAs("myFourMuonCtauSidebandSubtracted.pdf");











	/*
	    TCanvas* myc42=new TCanvas("myc42","myMuMu1Ctauat18dot5GeV_myMuMu1CtauatSideband_overlap",800,600);
    // myV1VsMuMuMassBeforeVVmasshighpair->Rebin();
    // myMuMu1Ctauat18dot5GeV->GetXaxis()->SetRange(300,750);
    // myMuMuMuMumassV1mumubelowV1->GetYaxis()->SetRange(0,1000);
    myMuMu1Ctauat18dot5GeV->SetTitle("");
    myMuMu1Ctauat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
    myMuMu1Ctauat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
    myMuMu1Ctauat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
    myMuMu1Ctauat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
    myMuMu1Ctauat18dot5GeV->GetXaxis()->SetTitle("(#mu^{+}#mu^{-})_{1} c#tau");
    myMuMu1Ctauat18dot5GeV->GetYaxis()->SetTitle("Candidates/5#mum");
    // myMuMuMuMumassV1mumubelowV1->SetMaximum(40);
    myMuMu1Ctauat18dot5GeV->Draw("e1");

    myMuMu1CtauatSideband->SetNormFactor(283);
    // myFourMuRapidityatSideband->Rebin();
    // myMuMu1CtauatSideband->GetXaxis()->SetRange(300,750);
    myMuMu1CtauatSideband->SetLineColor(2);
    myMuMu1CtauatSideband->Draw("e1same");
    myc42->SaveAs("myMuMu1Ctauat18dot5GeV_myMuMu1CtauatSideband_overlap.pdf");





	*/






}
