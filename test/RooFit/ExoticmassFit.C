//root -l /eos/uscms/store/user/yik/Reddy/psimumurootfile/PsiMassData.root
//.L Psi2SmassFit.C
//Psi2SmassFit(mymumu2012A)
//Psi2SmassFit(mymumu2012B)
//Psi2SmassFit(mymumu2012C)
//Psi2SmassFit(mymumu2012D)
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TGraph.h"


RooDataSet* dataSet(0);
// #include "sPlotMaker.hh"
gStyle->SetOptFit(111111);
gSystem->Load("libRooFit");

using namespace RooFit;
using namespace RooStats;

void ExoticmassFit() 
{


	TFile *f1 = TFile::Open("Combined10em10Vtxcl.root");
	TH2F* my2DHist = new TH2F("my2DHist","my2DHist",10.0,18.0,19.0,100.0,-11360.0,-11280.0);

	double JpsiMassmin=14.0, JpsiMassmax=25.0;
	double mybinwidth=0.2;


	RooRealVar varMyXmass("varMyXmass", "m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);
	RooRealVar varMyXmassErr("varMyXmassErr", "masserr(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",0.0, 0.5);
	RooRealVar varMyXPt("varMyXPt", "Pt(X) [GeV]",0.0,100.0);
	RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_1 [GeV]",0.0,20.0);
	RooRealVar varMymumu1Pt("varMymumu1Pt", "Pt(#mu^{+}#mu^{-})_1 [GeV]",0.0,100.0);
	RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0);
	RooRealVar varMymumu2Pt("varMymumu2Pt", "Pt(#mu^{+}#mu^{-})_2 [GeV]",0.0,100.0);
	RooRealVar varMymu11Pt("varMymu11Pt", "Pt(#mu)_11 [GeV]",2.,100.0);
	RooRealVar varMymu12Pt("varMymu12Pt", "Pt(#mu)_12 [GeV]",2.,100.0);
	RooRealVar varMymu21Pt("varMymu21Pt", "Pt(#mu)_21 [GeV]",2.,100.0);
	RooRealVar varMymu22Pt("varMymu22Pt", "Pt(#mu)_22 [GeV]",2.,100.0);
	
	RooArgSet variables;
	variables.add(varMyXmass);
	variables.add(varMyXmassErr);
	variables.add(varMyXPt);
	variables.add(varMymumu1mass);
	variables.add(varMymumu1Pt);
	variables.add(varMymumu2mass);
	variables.add(varMymumu2Pt);
	variables.add(varMymu11Pt);
	variables.add(varMymu12Pt);
	variables.add(varMymu21Pt);
	variables.add(varMymu22Pt);

	RooArgSet* observables = new RooArgSet(varMyXmass,"observables");



	RooRealVar   MyMean1  ("MyMean1"    ,"MyMean1"  ,18.4532,15.0,22.0 );
	RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 100,  -10.0, 100000000.0); 



	// RooRealVar   MyMean2  ("MyMean2"    ,"MyMean2"  ,18.4532,15.0,22.0 );
	// // free Gaus shape
	// RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,18.5,18.2,18.6 );   
	// RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  , 0.150, 0.01,0.5 ); 
	// RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, GausMean1 ,Gaussigma1 ) ;
	
	// // free Breit-Wigner shape
	// RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,18.485,18.2,18.6 );   
	// RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  , 0.000,0.5 ); 
	// RooAbsPdf* pdfMyXBreitWigner1 = new 	RooBreitWigner( "pdfMyXBreitWigner1", "pdfMyXBreitWigner1",  varMyXmass, GausMean1 ,Gaussigma1 ) ;
	// // RooRealVar   Gauswidth1 ("Gauswidth1"    ,"Gauswidth1"  ,  2.56802,0.01,3.0 ); 
	// // RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, MyMean1 ,Gauswidth1 ) ;
	// RooRealVar BWMean1("BWMean1","BWMean1",18.4344,15.0,22.0);
	// RooRealVar BWWidth1("BWWidth1","BWWidth1",0.260748,0.01,3.0);
	// RooAbsPdf * pdfBW1 = new RooBreitWigner("pdfBW1","pdfBW1",varMyXmass,MyMean1,BWWidth1);
	// RooRealVar BWMean2("BWMean2","BWMean2",18.5535);
	// RooRealVar BWWidth2("BWWidth2","BWWidth2", 0.291299);
	// RooAbsPdf * pdfBW2 = new RooBreitWigner("pdfBW2","pdfBW2",varMyXmass,MyMean1,BWWidth2);
	// RooRealVar BWMean3("BWMean3","BWMean3",18.5628);
	// RooRealVar BWWidth3("BWWidth3","BWWidth3",0.586284);
	// RooAbsPdf * pdfBW3 = new RooBreitWigner("pdfBW3","pdfBW3",varMyXmass,BWMean3,BWWidth3);

	// RooRealVar LandauSigma1("LandauSigma1","LandauSigma1",0.20,0.0,0.5);
	// RooAbsPdf *pdfLandau1 = new RooLandau("pdfLandau1","pdfLandau1",varMyXmass,MyMean1,LandauSigma1);



	RooRealVar MyXfrac1("MyXfrac1","fraction of double gaussian1",0.0302285,0.0,1.0) ;

	RooRealVar CBsigma1("CBsigma1","CBsigma1",0.1586284,0.1,0.3);
	RooRealVar CBalpha1("CBalpha1","CBalpha1",2.13,1.0,10.0);
	RooRealVar CBn1("CBn1","CBn1",0.2,0.0,2.0);
	RooAbsPdf * pdfCB1 = new RooCBShape("pdfCB1","pdfCB1",varMyXmass,MyMean1,CBsigma1,CBalpha1,CBn1);
	RooRealVar CBsigma2("CBsigma2","CBsigma2",0.1586284,0.12,0.17);
	RooRealVar CBalpha2("CBalpha2","CBalpha2",2.13,2.1,2.2);
	RooRealVar CBn2("CBn2","CBn2",1.16,1.1,1.2);
	RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2","pdfCB2",varMyXmass,MyMean1,CBsigma2,CBalpha2,CBn2);


	MyMean1.setVal( 1.85007e+01 );
	MyXfrac1.setVal( 3.49987e-01 );
	CBalpha1.setVal(5.76320e-01);
	CBn1.setVal( 2.52857e+00 );
	CBsigma1.setVal( 7.34724e-02 );
	CBalpha2.setVal(-2.03863e+00);
	CBn2.setVal( 1.85372e+00 );
	CBsigma2.setVal( 1.60791e-01 );


	MyXfrac1.setConstant();
	MyMean1.setConstant();
	CBalpha1.setConstant();
	CBn1.setConstant();
	CBsigma1.setConstant();
	CBalpha2.setConstant();
	CBn2.setConstant();
	CBsigma2.setConstant();



	RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfCB2),RooArgList(MyXfrac1)); 




	
	RooRealVar c1("c1", "c1",-7.37579e-02 ,  -2.0, 2.0);
	RooRealVar c2("c2", "c2",-2.68499e-01 ,  -2.0, 2.0);
	RooRealVar c3("c3", "c3", -5.54591e-02,  -15., 15.0);
	RooRealVar c4("c4", "c4", -5.54591e-02,  -15., 15.0);
	RooRealVar c5("c5", "c5", -5.54591e-02,  -15., 15.0);
	RooRealVar c6("c6", "c6", -5.54591e-02,  -15., 15.0);
	RooRealVar c7("c7", "c7", -5.54591e-02,  -15., 15.0);
	RooRealVar c8("c8", "c8", -5.54591e-02,  -15., 15.0);
	RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2,c3,c4/*,c5,c6,c7,c8*/));

	RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);
	
 
	RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);


	RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);

	// RooDataSet * alldata= &(RooDataSet::read("myfourmuonsignal.txt",variables,"Q"));
	// RooDataSet * alldata= &(RooDataSet::read("old.txt",variables,"Q"));

	RooDataSet * alldata= &(RooDataSet::read("fourmuonmass_HLTUpsilonMuonTrigger.txt",variables,"Q"));

	// myMuMuMuMumassV1mumubelowV1nolightmeson->Rebin();
	// RooDataHist *alldata =  new RooDataHist("alldata","alldata",varMyXmass, myMuMuMuMumassV1mumubelowV1nolightmeson);

	
	// do s signal fit scan
	RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
	
	
		
	// MyMean1.setVal( myMaxscanmean );MyMean1.setConstant();
	mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));

	gROOT->SetStyle("Plain");  
	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();
	RooPlot *frame = varMyXmass.frame( (int)((JpsiMassmax-JpsiMassmin)/mybinwidth) );   //30-12=18


	alldata.plotOn(frame, DataError(RooAbsData::SumW2) );
	mytotalPdf.plotOn(frame, Components(RooArgSet(*extendpdfBkgPol)),LineStyle(kDashed),LineColor(kBlue)/*,Precision(1e-8)*/,Range(JpsiMassmin, JpsiMassmax) );
	mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
	// mytotalPdf.paramOn(frame);
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
	// frame->SetMinimum(-10);
	// frame->SetMaximum(75);
	frame->Draw();
	
	



	return;


}  


