RooDataSet* dataSet(0);
gStyle->SetOptFit(111111);
gSystem->Load("libRooFit");

using namespace RooFit;
using namespace RooStats;


void fitJpsi()
{
	
	TFile *f1 = TFile::Open("myMinBiasDimuon.root");
	// TFile *f1 = TFile::Open("doubleelectronElePtgt15GeV.root");
	// TFile *f1 = TFile::Open("doubleelectronElePtlt10GeV.root");
	// TFile *f1 = TFile::Open("output_MCElePtgt15GeV.root");
	// TFile *f1 = TFile::Open("output_MCElePtlt10GeV.root");
	cout<<"root file read"<<endl;
	TCanvas * c = new TCanvas("c","c",800,600); 
	c->SetTitle("");
	// TH1* hh = (TH1*)f->Get("myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5") ;

	// hh->Rebin(5);
	double JpsiMassmin=2.2, JpsiMassmax=3.6;

	RooRealVar x("x", "Mass (GeV/c^{2})", JpsiMassmin, JpsiMassmax);
	RooRealVar mean("Mean", "Mean" ,3.096916,2.6,3.4) ;
	


	RooRealVar sigma_bw0("sigma_bw0", "sigma_bw0" , 0.0516, 0.045,0.1) ; //0.2, 0.05,0.5
	RooRealVar sigma_cb0("sigma_cb0", "sigma_cb0" , 0.04, 0.02, 0.045) ;

	// RooRealVar scale_bw("scale_bw","scale_bw",1.0,-2.2,3.);
	// RooRealVar scale_cb("scale_cb","Sscale_cb",1.0,-2.2,3.);

	RooRealVar scale("scale","Sscale",1.0,-2.2,3.);

	RooProduct sigma_bw("sigma_bw", "sigma_bw0 * scale",RooArgList(sigma_bw0,scale));
	RooProduct sigma_cb("sigma_cb", "sigma_cb0 * scale",RooArgList(sigma_cb0,scale));





	RooRealVar n("n","", 5.6, 150.0); //0.0, 5.0
	RooRealVar alpha("alpha","", 1.437,0.5, 1.5);

	// RooRealVar mean_cb2("mean_cb2", "Mean2" ,3.1,3.0,3.3) ;
	// RooRealVar sigma_cb2("sigma_cb2", "Width2" , 0.4, 0.01,4) ;
	// RooRealVar n2("n2","", 0.0, 5.0);
	// RooRealVar alpha2("alpha2","", -1.5, 0.0);

	RooRealVar MyXfrac("MyXfrac","frac ",0.319,0.0,1.0) ;



	
	// // ele pt < 10 GeV
	// MyXfrac.setVal(2.97800e-01);
	// alpha.setVal(2.51682e-01);
	// n.setVal(2.32045e+00);
	// sigma_bw0.setVal(1.15649e-01);
	// sigma_cb0.setVal(4.30491e-02);
	// scale.setVal(1.0);
	// scale.setConstant();

	// MyXfrac.setConstant();
	// alpha.setConstant();
	// n.setConstant();
	// sigma_bw0.setConstant();
	// sigma_cb0.setConstant();


	// ele pt > 15 GeV
	// MyXfrac.setVal(1.12134e-01);
	// alpha.setVal(6.33645e-01);
	// n.setVal(1.14419e+00);
	// sigma_bw0.setVal(8.12625e-01);
	// sigma_cb0.setVal(8.69949e-02);
	// scale.setVal(1.0);
	// scale.setConstant();

	// MyXfrac.setConstant();
	// alpha.setConstant();
	// n.setConstant();
	// sigma_bw0.setConstant();
	// sigma_cb0.setConstant();



	////////////////////////////New Constants after changing quality cuts on the electrons




	// // ele pt < 10 GeV
	// MyXfrac.setVal(2.63854e-01);
	// alpha.setVal(3.46664e-01);
	// n.setVal(1.60465e+00);
	// sigma_bw0.setVal(1.32552e-01);
	// sigma_cb0.setVal(4.22383e-02);
	// scale.setVal(1.0);
	// scale.setConstant();

	// MyXfrac.setConstant();
	// alpha.setConstant();
	// n.setConstant();
	// sigma_bw0.setConstant();
	// sigma_cb0.setConstant();

	/*
	// ele pt > 15 GeV
	MyXfrac.setVal(1.24524e-01);
	alpha.setVal(5.15504e-01);
	n.setVal(1.80655e+00);
	sigma_bw0.setVal(1.29572e+00);
	sigma_cb0.setVal(8.59543e-02);
	// scale.setVal(1.0);
	// scale.setConstant();

	MyXfrac.setConstant();
	alpha.setConstant();
	n.setConstant();
	sigma_bw0.setConstant();
	sigma_cb0.setConstant();
	*/



	RooAbsPdf * pdfBW = new RooBreitWigner("pdfBW","pdfBW",x,mean,sigma_bw0);
	RooAbsPdf * pdfCB = new RooCBShape("pdfCB", "pdfCB", x, mean, sigma_cb0, alpha, n);
	// RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2", "pdfCB2", x, mean_cb2, sigma_cb2, alpha2, n2);


	

	RooRealVar c1("c1", "c1", -0.5 , -5.0, 10.0);
	RooRealVar c2("c2", "c2", .0, -.2, .2);
	RooRealVar c3("c3", "c3", .0, -.2, .2);
	RooAbsPdf *  BkgPdf = new RooChebychev("BkgPdf","BkgPdf",x,RooArgSet(c1,c2));
	RooRealVar nBkgPol("background", "background yield", 100, 0, 10000000);

	RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfBW,*pdfCB),RooArgList(MyXfrac)); 
	// RooAbsPdf * pdfMyX = new RooCBShape("pdfMyX", "pdfMyX", x, mean, sigma_cb0, alpha, n);
	// RooAbsPdf * pdfMyX = new RooBreitWigner("pdfMyX", "pdfMyX", x, mean, sigma_bw0);
	// RooAbsPdf * pdfMyX = new RooGaussian("pdfMyX", "pdfMyX", x, mean, sigma_bw0);



	RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 100,  -10.0, 1000000.0); 



	RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);


	RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPdf, nBkgPol);

	// RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
	RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
	


	// myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5->Rebin();
	// myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5->GetXaxis()->SetRange(0,250);
	// RooDataHist alldata("aadata", "alldata", x, myTrkatVtxEEOnlyMasstwoMVAeleidgt0dot5Jpsi);
	// RooDataHist alldata("aadata", "alldata", x, mumuMasswvertex);
	RooDataHist alldata("aadata", "alldata", x, mumuMass);



	// RooDataHist * alldata = &(RooDataSet::read("test.txt",variables,"Q"));

	cout<<"haha"<<endl;
	mytotalPdf.fitTo(alldata,Minos(kTRUE), Save(1));
	// mytotalPdf.fitTo(alldata,Save(1));


	gROOT->SetStyle("Plain");  
	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();
	RooPlot *frame = x.frame( (int)4.0/0.1 );   //30-12=18

	alldata.plotOn(frame, DataError(RooAbsData::SumW2) );
	mytotalPdf.plotOn(frame, Components(RooArgSet(*extendpdfBkgPol)),LineStyle(kDashed),LineColor(kBlue),Range(JpsiMassmin, JpsiMassmax) );
	// mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
	mytotalPdf.paramOn(frame);
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
	







 //  //RooGaussian gauss("gauss","gauss",x,mean,sigma);
 //  //RooVoigtian gauss("gauss","gauss", x, mean, width, sigma);
 //  RooBreitWigner gauss_bw("gauss_bw","gauss_bw",x,mean_bw,sigma_bw);
 //  RooCBShape cball("cball", "crystal ball", x, mean_cb, sigma_cb, alpha, n);
 //  RooDataHist data("data", "dataset with x", x, hh);
 //  //RooExponential expo("expo", "exponential PDF", x, lambda);
 //  RooAddPdf sum("sum", "gaussian crystal ball and exponential PDF", 
	// RooArgList(gauss_bw, cball, *BkgPdf), RooArgList(s_bw, s_cb, b));
 //  //RooAddPdf sum("sum", "gaussian crystal ball and exponential PDF", 
 //  //	RooArgList(gauss_bw, cball, expo), RooArgList(s_bw, s_cb, b));

 //  RooPlot * xFrame = x.frame(Title("J/#psi-peak")) ;
	

 //  sum.fitTo(data, RooFit::Extended());  
 //  data.plotOn(xFrame) ;
 //  sum.plotOn(xFrame) ;
 //  sum.plotOn(xFrame, 
 //  RooFit::Components(*BkgPdf), 
 //  RooFit::LineStyle(kDashed)) ;  
 //  sum.paramOn(xFrame,Layout(0.65), 
 //  Format("NEU", AutoPrecision(1)), 
	//       Parameters( RooArgList(s_bw, s_cb, b, mean_bw, mean_cb, sigma_bw, sigma_cb,alpha,c1 )));

	
 //  mean_bw.Print() ;
 //  mean_cb.Print() ;
 //  sigma_bw.Print();
 //  sigma_cb.Print();
 //  s_bw.Print();
 //  s_cb.Print();
 //  b.Print();
 //  xFrame->Draw();

 //  c->SaveAs("fitJpsi.gif");
 //  c->SaveAs("fitJpsi.pdf");


}
