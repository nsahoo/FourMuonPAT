RooDataSet* dataSet(0);
gStyle->SetOptFit(111111);
gSystem->Load("libRooFit");

using namespace RooFit;
using namespace RooStats;


void fitJpsi()
{
	
	TFile *f1 = TFile::Open("myMuMuAfterwithVertexCut.root");

	cout<<"root file read"<<endl;
	TCanvas * c = new TCanvas("c","c",800,600); 
	c->SetTitle("");
	// TH1* hh = (TH1*)f->Get("myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5") ;

	// hh->Rebin(5);
	double JpsiMassmin=2.0, JpsiMassmax=4.0;

	RooRealVar x("x", "Mass (GeV/c^{2})", JpsiMassmin, JpsiMassmax);
	RooRealVar mean("Mean", "Mean" ,3.096916,2.6,3.4) ;
	


	RooRealVar sigma_bw("sigma_bw", "sigma_bw" , 2.01029e-01 /*, 0.05,10.0*/) ; //0.2, 0.05,0.5
	RooRealVar sigma_cb("sigma_cb", "sigma_cb" ,3.30938e-02/*, 0.01,4*/) ;

	// RooRealVar scale_bw("scale_bw","scale_bw",1.0,-2.2,3.);
	// RooRealVar scale_cb("scale_cb","Sscale_cb",1.0,-2.2,3.);

	// RooRealVar scale("scale","Sscale",1.0,-2.2,3.);

	// RooProduct sigma_bw("sigma_bw", "sigma_bw0 * scale",RooArgList(sigma_bw0,scale));
	// RooProduct sigma_cb("sigma_cb", "sigma_cb0 * scale",RooArgList(sigma_cb0,scale));





	RooRealVar n("n","",1.37014e+00/*, 0.0, 10.0*/); //0.0, 5.0
	RooRealVar alpha("alpha","",7.44802e-01/*, 0, 1.5*/);

	// RooRealVar mean_cb2("mean_cb2", "Mean2" ,3.1,3.0,3.3) ;
	// RooRealVar sigma_cb2("sigma_cb2", "Width2" , 0.4, 0.01,4) ;
	// RooRealVar n2("n2","", 0.0, 5.0);
	// RooRealVar alpha2("alpha2","", -1.5, 0.0);

	RooRealVar MyXfrac("MyXfrac","frac ",5.10646e-01/*,0.0,1.0*/) ;





	RooAbsPdf * pdfBW = new RooBreitWigner("pdfBW","pdfBW",x,mean,sigma_bw);
	RooAbsPdf * pdfCB = new RooCBShape("pdfCB", "pdfCB", x, mean, sigma_cb, alpha, n);
	// RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2", "pdfCB2", x, mean_cb2, sigma_cb2, alpha2, n2);


	

	RooRealVar c1("c1", "c1", -1.99820e-01/* , -1.0, 1.0*/);
	RooRealVar c2("c2", "c2", 4.74836e-02/*, -10.0, 10.0*/);
	RooRealVar c3("c3", "c3", 0.0, -10.0, 10.0);
	RooAbsPdf *  BkgPdf = new RooChebychev("BkgPdf","BkgPdf",x,RooArgSet(c1,c2));
	RooRealVar nBkgPol("background", "background yield", 100000, 0, 10000000);

	RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfBW,*pdfCB),RooArgList(MyXfrac)); 
	RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 10000,  -10.0, 1000000.0); 



	RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);


	RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPdf, nBkgPol);

	RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
	// RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX/*,*extendpdfBkgPol*/), RooArgList(nSigMyX/*,nBkgPol*/) ) ;
	


	// myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5->Rebin();
	// myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5->GetXaxis()->SetRange(0,250);
	RooDataHist alldata("aadata", "alldata", x, myMuMumassforV1highpair);

	// RooDataHist * alldata = &(RooDataSet::read("test.txt",variables,"Q"));

	cout<<"haha"<<endl;
	mytotalPdf.fitTo(alldata,Minos(kTRUE), Save(1));

	gROOT->SetStyle("Plain");  
	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();
	RooPlot *frame = x.frame( (int)4.0/0.1 );   //30-12=18

	alldata.plotOn(frame, DataError(RooAbsData::SumW2) );
  	mytotalPdf.plotOn(frame, Components(RooArgSet(*extendpdfBkgPol)),LineStyle(kDashed),LineColor(kBlue)/*,Precision(1e-8)*/,Range(JpsiMassmin, JpsiMassmax) );
  	mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
	mytotalPdf.plotOn(frame);
	
	frame->SetTitle("");  
	frame->GetXaxis()->SetTitleSize(0.05);
	frame->GetXaxis()->SetLabelSize(0.035);
	frame->GetXaxis()->SetTitleOffset(0.9);
	// frame->GetYaxis()->SetTitle("pull");
	frame->GetYaxis()->SetTitleSize(0.05);
	frame->GetYaxis()->SetTitleOffset(0.9);
	frame->SetMarkerColor(1);
	frame->SetMarkerSize(2.0);
	frame->SetMinimum(-10);
	// frame->SetMaximum(75);
	frame->Draw();


	RooHist* hpull = frame->pullHist() ;
	if (!hpull) Error("hpull","hpull is nULL");
	hpull->SetMarkerStyle(8);
	hpull->SetMarkerSize(2.0);
	hpull->SetMarkerColor(2);
	hpull->Draw("e1");
	

}
