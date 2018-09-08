void plot_PtvsEta()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);


	TFile * f50=new TFile("EtavsPt.root");


	TCanvas* myc50=new TCanvas("myc50","myMuMuEtaVsPtat18dot5GeV",800,600);
	// myV1VsMuMuMassBeforeVVmasshighpair-->Rebin();
	// myMuMuMuMumassV1mumubelowV1HighSideShift->GetXaxis()->SetRange(100,1000);
	myMuMuEtaVsPtat18dot5GeV->GetYaxis()->SetRange(0,150);
	myMuMuEtaVsPtat18dot5GeV->SetTitle("");
	myMuMuEtaVsPtat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMuMuEtaVsPtat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMuMuEtaVsPtat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMuMuEtaVsPtat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMuMuEtaVsPtat18dot5GeV->GetXaxis()->SetTitle("#mu^{+}#mu^{-} #eta");
	myMuMuEtaVsPtat18dot5GeV->GetYaxis()->SetTitle("#mu^{+}#mu^{-} p_{T}");
	// myMuMuMuMumassV1mumubelowV1->SetMaximum(40);
	myMuMuEtaVsPtat18dot5GeV->Draw("colz");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.50,0.20,"Signal Region");



	myc50->SaveAs("myMuMuEtaVsPtat18dot5GeV.pdf");
	myc50->SaveAs("myMuMuEtaVsPtat18dot5GeV.gif");
	
	TCanvas* myc51=new TCanvas("myc51","myMuMuEtaVsPtatSideband",800,600);
	// myV1VsMuMuMassBeforeVVmasshighpair-->Rebin();
	// myMuMuMuMumassV1mumubelowV1HighSideShift->GetXaxis()->SetRange(100,1000);
	myMuMuEtaVsPtatSideband->GetYaxis()->SetRange(0,150);
	myMuMuEtaVsPtatSideband->SetTitle("");
	myMuMuEtaVsPtatSideband->GetXaxis()->SetTitleSize(0.06);
	myMuMuEtaVsPtatSideband->GetYaxis()->SetTitleSize(0.06);
	myMuMuEtaVsPtatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMuMuEtaVsPtatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMuMuEtaVsPtatSideband->GetXaxis()->SetTitle("#mu^{+}#mu^{-} #eta");
	myMuMuEtaVsPtatSideband->GetYaxis()->SetTitle("#mu^{+}#mu^{-} p_{T}");
	// myMuMuMuMumassV1mumubelowV1->SetMaximum(40);
	myMuMuEtaVsPtatSideband->Draw("colz");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.50,0.20,"Sideband Region");



	myc51->SaveAs("myMuMuEtaVsPtatSideband.pdf");
	myc51->SaveAs("myMuMuEtaVsPtatSideband.gif");
	
	



	TCanvas* myc52=new TCanvas("myc52","myUpsilonEtaVsPtat18dot5GeV",800,600);
	myUpsilonEtaVsPtat18dot5GeV->GetYaxis()->SetRange(0,150);
	myUpsilonEtaVsPtat18dot5GeV->SetTitle("");
	myUpsilonEtaVsPtat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myUpsilonEtaVsPtat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myUpsilonEtaVsPtat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myUpsilonEtaVsPtat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myUpsilonEtaVsPtat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S) #eta");
	myUpsilonEtaVsPtat18dot5GeV->GetYaxis()->SetTitle("#Upsilon(1S) p_{T}");

	myUpsilonEtaVsPtat18dot5GeV->Draw("colz");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.50,0.20,"Signal Region");


	myc52->SaveAs("myUpsilonEtaVsPtat18dot5GeV.pdf");
	myc52->SaveAs("myUpsilonEtaVsPtat18dot5GeV.gif");
	
	



	TCanvas* myc53=new TCanvas("myc53","myUpsilonEtaVsPtatSideband",800,600);
	myUpsilonEtaVsPtatSideband->GetYaxis()->SetRange(0,150);
	myUpsilonEtaVsPtatSideband->SetTitle("");
	myUpsilonEtaVsPtatSideband->GetXaxis()->SetTitleSize(0.06);
	myUpsilonEtaVsPtatSideband->GetYaxis()->SetTitleSize(0.06);
	myUpsilonEtaVsPtatSideband->GetXaxis()->SetTitleOffset(0.7);
	myUpsilonEtaVsPtatSideband->GetYaxis()->SetTitleOffset(0.7);
	myUpsilonEtaVsPtatSideband->GetXaxis()->SetTitle("#Upsilon(1S) #eta");
	myUpsilonEtaVsPtatSideband->GetYaxis()->SetTitle("#Upsilon(1S) p_{T}");
	myUpsilonEtaVsPtatSideband->Draw("colz");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.50,0.20,"Sideband Region");


	myc53->SaveAs("myUpsilonEtaVsPtatSideband.pdf");
	myc53->SaveAs("myUpsilonEtaVsPtatSideband.gif");
	
	


	TCanvas* myc54=new TCanvas("myc54","myFourMuonEtaVsPtat18dot5GeV",800,600);
	myFourMuonEtaVsPtat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonEtaVsPtat18dot5GeV->SetTitle("");
	myFourMuonEtaVsPtat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myFourMuonEtaVsPtat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myFourMuonEtaVsPtat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonEtaVsPtat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonEtaVsPtat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} #eta");
	myFourMuonEtaVsPtat18dot5GeV->GetYaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} p_{T}");
	myFourMuonEtaVsPtat18dot5GeV->Draw("colz");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.50,0.20,"Signal Region");


	myc54->SaveAs("myFourMuonEtaVsPtat18dot5GeV.pdf");
	myc54->SaveAs("myFourMuonEtaVsPtat18dot5GeV.gif");
	


	TCanvas* myc55=new TCanvas("myc55","myFourMuonEtaVsPtatSideband",800,600);
	myFourMuonEtaVsPtatSideband->GetYaxis()->SetRange(0,150);
	myFourMuonEtaVsPtatSideband->SetTitle("");
	myFourMuonEtaVsPtatSideband->GetXaxis()->SetTitleSize(0.06);
	myFourMuonEtaVsPtatSideband->GetYaxis()->SetTitleSize(0.06);
	myFourMuonEtaVsPtatSideband->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonEtaVsPtatSideband->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonEtaVsPtatSideband->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} #eta");
	myFourMuonEtaVsPtatSideband->GetYaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} p_{T}");
	myFourMuonEtaVsPtatSideband->Draw("colz");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.50,0.20,"Sideband Region");

	myc55->SaveAs("myFourMuonEtaVsPtatSideband.pdf");
	myc55->SaveAs("myFourMuonEtaVsPtatSideband.gif");




	TCanvas* myc56=new TCanvas("myc56","myFourMuonMomentumat18dot5GeV",800,600);
	myFourMuonMomentumat18dot5GeV->Rebin(5);
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonMomentumat18dot5GeV->SetTitle("");
	myFourMuonMomentumat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myFourMuonMomentumat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} P");
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	myFourMuonMomentumat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc56->SaveAs("myFourMuonMomentumat18dot5GeV.pdf");
	myc56->SaveAs("myFourMuonMomentumat18dot5GeV.gif");


	

	TCanvas* myc57=new TCanvas("myc57","myFourMuonMomentumatSideband",800,600);
	myFourMuonMomentumatSideband->Rebin(5);
	myFourMuonMomentumatSideband->GetYaxis()->SetRange(0,150);
	myFourMuonMomentumatSideband->SetTitle("");
	myFourMuonMomentumatSideband->GetXaxis()->SetTitleSize(0.06);
	myFourMuonMomentumatSideband->GetYaxis()->SetTitleSize(0.06);
	myFourMuonMomentumatSideband->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumatSideband->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumatSideband->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} P");
	myFourMuonMomentumatSideband->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	myFourMuonMomentumatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc57->SaveAs("myFourMuonMomentumatSideband.pdf");
	myc57->SaveAs("myFourMuonMomentumatSideband.gif");



	TCanvas* myc57=new TCanvas("myc57","myFourMuonMomentumatSidebandSubtracted",800,600);
	nEntriesSignal = myFourMuonMomentumat18dot5GeV->GetEntries();
	nEntriesSideband = myFourMuonMomentumatSideband->GetEntries();
	// myFourMuonMomentumat18dot5GeV->SetNormFactor(nEntriesSignal);
	myFourMuonMomentumatSideband->SetNormFactor(nEntriesSignal);
	// myFourMuonMomentumat18dot5GeV->Sumw2();
	myFourMuonMomentumatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myFourMuonMomentumat18dot5GeV");
	h->Add(myFourMuonMomentumatSideband,-1);
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc57->SaveAs("myFourMuonMomentumatSidebandSubtracted.pdf");
	myc57->SaveAs("myFourMuonMomentumatSidebandSubtracted.gif");








	




}
