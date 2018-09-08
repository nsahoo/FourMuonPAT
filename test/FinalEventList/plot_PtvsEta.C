void plot_PtvsEta()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(0);


	TFile * f50=new TFile("output.root");

/*
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

*/


	TCanvas* myc56=new TCanvas("myc56","myFourMuonMomentumat18dot5GeV",800,600);
	myFourMuonMomentumat18dot5GeV->Rebin(50);
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonMomentumat18dot5GeV->SetTitle("");
	myFourMuonMomentumat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myFourMuonMomentumat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} P");
	myFourMuonMomentumat18dot5GeV->GetYaxis()->SetTitle("Candidates/5 GeV");
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
	myFourMuonMomentumatSideband->Rebin(50);
	myFourMuonMomentumatSideband->GetYaxis()->SetRange(0,150);
	myFourMuonMomentumatSideband->SetTitle("");
	myFourMuonMomentumatSideband->GetXaxis()->SetTitleSize(0.06);
	myFourMuonMomentumatSideband->GetYaxis()->SetTitleSize(0.06);
	myFourMuonMomentumatSideband->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumatSideband->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonMomentumatSideband->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} P");
	myFourMuonMomentumatSideband->GetYaxis()->SetTitle("Candidates/5 GeV");
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



	TCanvas* myc58=new TCanvas("myc58","myFourMuonMomentumatSidebandSubtracted",800,600);
	// nEntriesSignal = myFourMuonMomentumat18dot5GeV->GetEntries();
	// nEntriesSideband = myFourMuonMomentumatSideband->GetEntries();
	// myFourMuonMomentumat18dot5GeV->SetNormFactor(nEntriesSignal);
	myFourMuonMomentumat18dot5GeV->Rebin(4);
	myFourMuonMomentumatSideband->Rebin(4);
	// myFourMuonMomentumatSideband->SetNormFactor(nEntriesSignal);
	// myFourMuonMomentumat18dot5GeV->Sumw2();
	myFourMuonMomentumatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myFourMuonMomentumat18dot5GeV");
	h->Add(myFourMuonMomentumatSideband,-1);
	h->GetYaxis()->SetTitle("Candidates/20 GeV");
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc58->SaveAs("myFourMuonMomentumatSidebandSubtracted.pdf");
	myc58->SaveAs("myFourMuonMomentumatSidebandSubtracted.gif");







	TCanvas* myc59=new TCanvas("myc59","myUpsilonEtaat18dot5GeV",800,600);
	myUpsilonEtaat18dot5GeV->Rebin(5);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myUpsilonEtaat18dot5GeV->SetTitle("");
	myUpsilonEtaat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myUpsilonEtaat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myUpsilonEtaat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myUpsilonEtaat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myUpsilonEtaat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S) #eta");
	myUpsilonEtaat18dot5GeV->GetYaxis()->SetTitle("Candidates/0.5");
	myUpsilonEtaat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc59->SaveAs("myUpsilonEtaat18dot5GeV.pdf");
	myc59->SaveAs("myUpsilonEtaat18dot5GeV.gif");


	TCanvas* myc60=new TCanvas("myc60","myUpsilonEtaatSideband",800,600);
	myUpsilonEtaatSideband->Rebin(5);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myUpsilonEtaatSideband->SetTitle("");
	myUpsilonEtaatSideband->GetXaxis()->SetTitleSize(0.06);
	myUpsilonEtaatSideband->GetYaxis()->SetTitleSize(0.06);
	myUpsilonEtaatSideband->GetXaxis()->SetTitleOffset(0.7);
	myUpsilonEtaatSideband->GetYaxis()->SetTitleOffset(0.7);
	myUpsilonEtaatSideband->GetXaxis()->SetTitle("#Upsilon(1S) #eta");
	myUpsilonEtaatSideband->GetYaxis()->SetTitle("Candidates/0.5");
	myUpsilonEtaatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc60->SaveAs("myUpsilonEtaatSideband.pdf");
	myc60->SaveAs("myUpsilonEtaatSideband.gif");



	TCanvas* myc1=new TCanvas("myc1","myUpsilonEtaSidebandSubtracted",800,600);
	myUpsilonEtaatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myUpsilonEtaat18dot5GeV");
	h->Add(myUpsilonEtaatSideband,-1);
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc1->SaveAs("myUpsilonEtaSidebandSubtracted.pdf");
	myc1->SaveAs("myUpsilonEtaSidebandSubtracted.gif");







	TCanvas* myc61=new TCanvas("myc61","myUpsilonPtat18dot5GeV",800,600);
	myUpsilonPtat18dot5GeV->Rebin(50);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myUpsilonPtat18dot5GeV->SetTitle("");
	myUpsilonPtat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myUpsilonPtat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myUpsilonPtat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myUpsilonPtat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myUpsilonPtat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S) p_{T}");
	myUpsilonPtat18dot5GeV->GetYaxis()->SetTitle("Candidates/5 GeV");
	myUpsilonPtat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc61->SaveAs("myUpsilonPtat18dot5GeV.pdf");
	myc61->SaveAs("myUpsilonPtat18dot5GeV.gif");

	TCanvas* myc62=new TCanvas("myc62","myUpsilonPtatSideband",800,600);
	myUpsilonPtatSideband->Rebin(50);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myUpsilonPtatSideband->SetTitle("");
	myUpsilonPtatSideband->GetXaxis()->SetTitleSize(0.06);
	myUpsilonPtatSideband->GetYaxis()->SetTitleSize(0.06);
	myUpsilonPtatSideband->GetXaxis()->SetTitleOffset(0.7);
	myUpsilonPtatSideband->GetYaxis()->SetTitleOffset(0.7);
	myUpsilonPtatSideband->GetXaxis()->SetTitle("#Upsilon(1S) p_{T}");
	myUpsilonPtatSideband->GetYaxis()->SetTitle("Candidates/5 GeV");
	myUpsilonPtatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc62->SaveAs("myUpsilonPtatSideband.pdf");
	myc62->SaveAs("myUpsilonPtatSideband.gif");





	TCanvas* myc2=new TCanvas("myc2","myUpsilonPtSidebandSubtracted",800,600);
	//myUpsilonPtat18dot5GeV->Rebin(4);
	//myUpsilonPtatSideband->Rebin(4);
	myUpsilonPtatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myUpsilonPtat18dot5GeV");
	h->Add(myUpsilonPtatSideband,-1);
	//h->GetYaxis()->SetTitle("Candidates/20 GeV");
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc2->SaveAs("myUpsilonPtSidebandSubtracted.pdf");
	myc2->SaveAs("myUpsilonPtSidebandSubtracted.gif");







	////////////////////////////////////////



	TCanvas* myc63=new TCanvas("myc63","myMuMuEtaat18dot5GeV",800,600);
	myMuMuEtaat18dot5GeV->Rebin(5);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myMuMuEtaat18dot5GeV->SetTitle("");
	myMuMuEtaat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMuMuEtaat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMuMuEtaat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMuMuEtaat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMuMuEtaat18dot5GeV->GetXaxis()->SetTitle("#mu^{+}#mu^{-} #eta");
	myMuMuEtaat18dot5GeV->GetYaxis()->SetTitle("Candidates/0.5");
	myMuMuEtaat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc63->SaveAs("myMuMuEtaat18dot5GeV.pdf");
	myc63->SaveAs("myMuMuEtaat18dot5GeV.gif");


	TCanvas* myc64=new TCanvas("myc64","myMuMuEtaatSideband",800,600);
	myMuMuEtaatSideband->Rebin(5);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myMuMuEtaatSideband->SetTitle("");
	myMuMuEtaatSideband->GetXaxis()->SetTitleSize(0.06);
	myMuMuEtaatSideband->GetYaxis()->SetTitleSize(0.06);
	myMuMuEtaatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMuMuEtaatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMuMuEtaatSideband->GetXaxis()->SetTitle("#mu^{+}#mu^{-} #eta");
	myMuMuEtaatSideband->GetYaxis()->SetTitle("Candidates/0.5");
	myMuMuEtaatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc64->SaveAs("myMuMuEtaatSideband.pdf");
	myc64->SaveAs("myMuMuEtaatSideband.gif");



	TCanvas* myc3=new TCanvas("myc3","myMuMuEtaSidebandSubtracted",800,600);
	myMuMuEtaatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myMuMuEtaat18dot5GeV");
	h->Add(myMuMuEtaatSideband,-1);
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc3->SaveAs("myMuMuEtaSidebandSubtracted.pdf");
	myc3->SaveAs("myMuMuEtaSidebandSubtracted.gif");






	TCanvas* myc65=new TCanvas("myc65","myMuMuPtat18dot5GeV",800,600);
	myMuMuPtat18dot5GeV->Rebin(50);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myMuMuPtat18dot5GeV->SetTitle("");
	myMuMuPtat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myMuMuPtat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myMuMuPtat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myMuMuPtat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myMuMuPtat18dot5GeV->GetXaxis()->SetTitle("#mu^{+}#mu^{-} p_{T}");
	myMuMuPtat18dot5GeV->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMuMuPtat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc65->SaveAs("myMuMuPtat18dot5GeV.pdf");
	myc65->SaveAs("myMuMuPtat18dot5GeV.gif");

	TCanvas* myc66=new TCanvas("myc66","myMuMuPtatSideband",800,600);
	myMuMuPtatSideband->Rebin(50);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myMuMuPtatSideband->SetTitle("");
	myMuMuPtatSideband->GetXaxis()->SetTitleSize(0.06);
	myMuMuPtatSideband->GetYaxis()->SetTitleSize(0.06);
	myMuMuPtatSideband->GetXaxis()->SetTitleOffset(0.7);
	myMuMuPtatSideband->GetYaxis()->SetTitleOffset(0.7);
	myMuMuPtatSideband->GetXaxis()->SetTitle("#mu^{+}#mu^{-} p_{T}");
	myMuMuPtatSideband->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMuMuPtatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc66->SaveAs("myMuMuPtatSideband.pdf");
	myc66->SaveAs("myMuMuPtatSideband.gif");




	TCanvas* myc4=new TCanvas("myc4","myMuMuPtSidebandSubtracted",800,600);
	//myMuMuPtat18dot5GeV->Rebin(4);
	//myMuMuPtatSideband->Rebin(4);
	myMuMuPtatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myMuMuPtat18dot5GeV");
	h->Add(myMuMuPtatSideband,-1);
	//h->GetYaxis()->SetTitle("Candidates/20 GeV");
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc4->SaveAs("myMuMuPtSidebandSubtracted.pdf");
	myc4->SaveAs("myMuMuPtSidebandSubtracted.gif");




//////////////////////////////////////////////////
	///////////////////////////////////////////////
	/////////////////////////////////////////////////


	////////////////////////////////////////



	TCanvas* myc5=new TCanvas("myc5","myFourMuonEtaat18dot5GeV",800,600);
	myFourMuonEtaat18dot5GeV->Rebin(5);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonEtaat18dot5GeV->SetTitle("");
	myFourMuonEtaat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myFourMuonEtaat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myFourMuonEtaat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonEtaat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonEtaat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} #eta");
	myFourMuonEtaat18dot5GeV->GetYaxis()->SetTitle("Candidates/0.5");
	myFourMuonEtaat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc5->SaveAs("myFourMuonEtaat18dot5GeV.pdf");
	myc5->SaveAs("myFourMuonEtaat18dot5GeV.gif");


	TCanvas* myc6=new TCanvas("myc6","myFourMuonEtaatSideband",800,600);
	myFourMuonEtaatSideband->Rebin(5);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonEtaatSideband->SetTitle("");
	myFourMuonEtaatSideband->GetXaxis()->SetTitleSize(0.06);
	myFourMuonEtaatSideband->GetYaxis()->SetTitleSize(0.06);
	myFourMuonEtaatSideband->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonEtaatSideband->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonEtaatSideband->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} #eta");
	myFourMuonEtaatSideband->GetYaxis()->SetTitle("Candidates/0.5");
	myFourMuonEtaatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc6->SaveAs("myFourMuonEtaatSideband.pdf");
	myc6->SaveAs("myFourMuonEtaatSideband.gif");



	TCanvas* myc7=new TCanvas("myc7","myFourMuonEtaSidebandSubtracted",800,600);
	myFourMuonEtaatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myFourMuonEtaat18dot5GeV");
	h->Add(myFourMuonEtaatSideband,-1);
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc7->SaveAs("myFourMuonEtaSidebandSubtracted.pdf");
	myc7->SaveAs("myFourMuonEtaSidebandSubtracted.gif");






	TCanvas* myc8=new TCanvas("myc8","myFourMuonPtat18dot5GeV",800,600);
	myFourMuonPtat18dot5GeV->Rebin(50);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonPtat18dot5GeV->SetTitle("");
	myFourMuonPtat18dot5GeV->GetXaxis()->SetTitleSize(0.06);
	myFourMuonPtat18dot5GeV->GetYaxis()->SetTitleSize(0.06);
	myFourMuonPtat18dot5GeV->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonPtat18dot5GeV->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonPtat18dot5GeV->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} p_{T}");
	myFourMuonPtat18dot5GeV->GetYaxis()->SetTitle("Candidates/5 GeV");
	myFourMuonPtat18dot5GeV->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");

	myc8->SaveAs("myFourMuonPtat18dot5GeV.pdf");
	myc8->SaveAs("myFourMuonPtat18dot5GeV.gif");

	TCanvas* myc9=new TCanvas("myc9","myFourMuonPtatSideband",800,600);
	myFourMuonPtatSideband->Rebin(50);
	// myUpsilonEtaat18dot5GeV->GetYaxis()->SetRange(0,150);
	myFourMuonPtatSideband->SetTitle("");
	myFourMuonPtatSideband->GetXaxis()->SetTitleSize(0.06);
	myFourMuonPtatSideband->GetYaxis()->SetTitleSize(0.06);
	myFourMuonPtatSideband->GetXaxis()->SetTitleOffset(0.7);
	myFourMuonPtatSideband->GetYaxis()->SetTitleOffset(0.7);
	myFourMuonPtatSideband->GetXaxis()->SetTitle("#Upsilon(1S)#mu^{+}#mu^{-} p_{T}");
	myFourMuonPtatSideband->GetYaxis()->SetTitle("Candidates/5 GeV");
	myFourMuonPtatSideband->Draw("e1");

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");

	myc9->SaveAs("myFourMuonPtatSideband.pdf");
	myc9->SaveAs("myFourMuonPtatSideband.gif");




	TCanvas* myc10=new TCanvas("myc10","myFourMuonPtSidebandSubtracted",800,600);
	//myFourMuonPtat18dot5GeV->Rebin(4);
	//myFourMuonPtatSideband->Rebin(4);
	myFourMuonPtatSideband->Sumw2();


	TH1F *h = (TH1F *) gDirectory->Get("myFourMuonPtat18dot5GeV");
	h->Add(myFourMuonPtatSideband,-1);
	//h->GetYaxis()->SetTitle("Candidates/20 GeV");
	h->Draw();

	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");

	myc10->SaveAs("myFourMuonPtSidebandSubtracted.pdf");
	myc10->SaveAs("myFourMuonPtSidebandSubtracted.gif");


	


	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////



	TCanvas* myc11=new TCanvas("myc11","myMu1PtSignalRegion",800,600);
	myMu1PtSignalRegion->Rebin(50);
	myMu1PtSignalRegion->SetTitle("");
	myMu1PtSignalRegion->GetXaxis()->SetTitleSize(0.06);
	myMu1PtSignalRegion->GetYaxis()->SetTitleSize(0.06);
	myMu1PtSignalRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu1PtSignalRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu1PtSignalRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu1PtSignalRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc11->SaveAs("myMu1PtSignalRegion.pdf");
	myc11->SaveAs("myMu1PtSignalRegion.gif");

	TCanvas* myc12=new TCanvas("myc12","myMu1PtSidebandRegion",800,600);
	myMu1PtSidebandRegion->Rebin(50);
	myMu1PtSidebandRegion->SetTitle("");
	myMu1PtSidebandRegion->GetXaxis()->SetTitleSize(0.06);
	myMu1PtSidebandRegion->GetYaxis()->SetTitleSize(0.06);
	myMu1PtSidebandRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu1PtSidebandRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu1PtSidebandRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu1PtSidebandRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc12->SaveAs("myMu1PtSidebandRegion.pdf");
	myc12->SaveAs("myMu1PtSidebandRegion.gif");


	TCanvas* myc13=new TCanvas("myc13","myMu1PtSidebandSubtracted",800,600);
	myMu1PtSidebandRegion->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu1PtSignalRegion");
	h->Add(myMu1PtSidebandRegion,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc13->SaveAs("myMu1PtSidebandSubtracted.pdf");
	myc13->SaveAs("myMu1PtSidebandSubtracted.gif");

	





	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////



	TCanvas* myc14=new TCanvas("myc14","myMu2PtSignalRegion",800,600);
	myMu2PtSignalRegion->Rebin(50);
	myMu2PtSignalRegion->SetTitle("");
	myMu2PtSignalRegion->GetXaxis()->SetTitleSize(0.06);
	myMu2PtSignalRegion->GetYaxis()->SetTitleSize(0.06);
	myMu2PtSignalRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu2PtSignalRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu2PtSignalRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu2PtSignalRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc14->SaveAs("myMu2PtSignalRegion.pdf");
	myc14->SaveAs("myMu2PtSignalRegion.gif");

	TCanvas* myc15=new TCanvas("myc15","myMu2PtSidebandRegion",800,600);
	myMu2PtSidebandRegion->Rebin(50);
	myMu2PtSidebandRegion->SetTitle("");
	myMu2PtSidebandRegion->GetXaxis()->SetTitleSize(0.06);
	myMu2PtSidebandRegion->GetYaxis()->SetTitleSize(0.06);
	myMu2PtSidebandRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu2PtSidebandRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu2PtSidebandRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu2PtSidebandRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc15->SaveAs("myMu2PtSidebandRegion.pdf");
	myc15->SaveAs("myMu2PtSidebandRegion.gif");


	TCanvas* myc16=new TCanvas("myc16","myMu2PtSidebandSubtracted",800,600);
	myMu2PtSidebandRegion->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu2PtSignalRegion");
	h->Add(myMu2PtSidebandRegion,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc16->SaveAs("myMu2PtSidebandSubtracted.pdf");
	myc16->SaveAs("myMu2PtSidebandSubtracted.gif");

	


	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////



	TCanvas* myc17=new TCanvas("myc17","myMu3PtSignalRegion",800,600);
	myMu3PtSignalRegion->Rebin(50);
	myMu3PtSignalRegion->SetTitle("");
	myMu3PtSignalRegion->GetXaxis()->SetTitleSize(0.06);
	myMu3PtSignalRegion->GetYaxis()->SetTitleSize(0.06);
	myMu3PtSignalRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu3PtSignalRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu3PtSignalRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu3PtSignalRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc17->SaveAs("myMu3PtSignalRegion.pdf");
	myc17->SaveAs("myMu3PtSignalRegion.gif");

	TCanvas* myc18=new TCanvas("myc18","myMu3PtSidebandRegion",800,600);
	myMu3PtSidebandRegion->Rebin(50);
	myMu3PtSidebandRegion->SetTitle("");
	myMu3PtSidebandRegion->GetXaxis()->SetTitleSize(0.06);
	myMu3PtSidebandRegion->GetYaxis()->SetTitleSize(0.06);
	myMu3PtSidebandRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu3PtSidebandRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu3PtSidebandRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu3PtSidebandRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc18->SaveAs("myMu3PtSidebandRegion.pdf");
	myc18->SaveAs("myMu3PtSidebandRegion.gif");


	TCanvas* myc19=new TCanvas("myc19","myMu3PtSidebandSubtracted",800,600);
	myMu3PtSidebandRegion->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu3PtSignalRegion");
	h->Add(myMu3PtSidebandRegion,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc19->SaveAs("myMu3PtSidebandSubtracted.pdf");
	myc19->SaveAs("myMu3PtSidebandSubtracted.gif");



	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////
	/////////////////////////////////////////////////////



	TCanvas* myc20=new TCanvas("myc20","myMu4PtSignalRegion",800,600);
	myMu4PtSignalRegion->Rebin(50);
	myMu4PtSignalRegion->SetTitle("");
	myMu4PtSignalRegion->GetXaxis()->SetTitleSize(0.06);
	myMu4PtSignalRegion->GetYaxis()->SetTitleSize(0.06);
	myMu4PtSignalRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu4PtSignalRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu4PtSignalRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu4PtSignalRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Signal Region");
	myc20->SaveAs("myMu4PtSignalRegion.pdf");
	myc20->SaveAs("myMu4PtSignalRegion.gif");

	TCanvas* myc21=new TCanvas("myc21","myMu4PtSidebandRegion",800,600);
	myMu4PtSidebandRegion->Rebin(50);
	myMu4PtSidebandRegion->SetTitle("");
	myMu4PtSidebandRegion->GetXaxis()->SetTitleSize(0.06);
	myMu4PtSidebandRegion->GetYaxis()->SetTitleSize(0.06);
	myMu4PtSidebandRegion->GetXaxis()->SetTitleOffset(0.7);
	myMu4PtSidebandRegion->GetYaxis()->SetTitleOffset(0.7);
	myMu4PtSidebandRegion->GetYaxis()->SetTitle("Candidates/5 GeV");
	myMu4PtSidebandRegion->Draw("e1");
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Region");
	myc21->SaveAs("myMu4PtSidebandRegion.pdf");
	myc21->SaveAs("myMu4PtSidebandRegion.gif");


	TCanvas* myc22=new TCanvas("myc22","myMu4PtSidebandSubtracted",800,600);
	myMu4PtSidebandRegion->Sumw2();
	TH1F *h = (TH1F *) gDirectory->Get("myMu4PtSignalRegion");
	h->Add(myMu4PtSidebandRegion,-1);
	h->Draw();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(6);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.70,0.80,"Sideband Subtraction");
	myc22->SaveAs("myMu4PtSidebandSubtracted.pdf");
	myc22->SaveAs("myMu4PtSidebandSubtracted.gif");




}
