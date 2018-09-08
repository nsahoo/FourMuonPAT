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

void ExoticmassFitUpsPull() 
{

	TFile *f1 = TFile::Open("/uscms_data/d3/sdurgut/RESEARCH/CMSSW_5_3_7_patch5/src/Analysis/FourMuonPAT/test/FourMuonAnyCHG/Fit/myoutput.root");
	

	//myARCDimuMassPullUpsi->Rebin();
	

	TH2F* my2DHist = new TH2F("my2DHist","my2DHist",10.0,18.0,19.0,100.0,-11360.0,-11280.0);

	double JpsiMassmin=-8.0, JpsiMassmax=18.0;  

	double mybinwidth=0.1;

	RooRealVar varMyXmass("varMyXmass", "m(#Upsilon(1S)#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);
	RooRealVar varMyXPt("varMyXPt", "Pt(X) [GeV]",0.0,100.0);
	RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_1 [GeV]",0.0,20.0);  //0-20
	RooRealVar varMymumu1Pt("varMymumu1Pt", "Pt(#mu^{+}#mu^{-})_1 [GeV]",0.0,100.0);
	//  RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10
	RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10

	RooRealVar varMymumu2Pt("varMymumu2Pt", "Pt(#mu^{+}#mu^{-})_2 [GeV]",0.0,100.0);

	RooRealVar varMymu11Pt("varMymu11Pt", "Pt(#mu)_11 [GeV]",2.,100.0);
	RooRealVar varMymu12Pt("varMymu12Pt", "Pt(#mu)_12 [GeV]",2.,100.0);
	RooRealVar varMymu21Pt("varMymu21Pt", "Pt(#mu)_21 [GeV]",2.,100.0);
	RooRealVar varMymu22Pt("varMymu22Pt", "Pt(#mu)_22 [GeV]",2.,100.0);
	


	//fixed shape from MC

	RooRealVar   MyMean1  ("MyMean1"    ,"MyMean1"  ,18.4532,15.0,22.0 );
	RooRealVar   MyMean2  ("MyMean2"    ,"MyMean2"  ,18.4532,15.0,22.0 );

	//free Gaus shape
	RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,-1.83796e-01,-1.0,1.0 );   
	RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  ,1.02644e+00, 0.5,1.5 ); 
	RooAbsPdf * pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, GausMean1 ,Gaussigma1 ) ;
	RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 100000,  -10.0, 1000000000.0);

	RooRealVar   GausMean2  ("GausMean2"    ,"GausMean2"  ,5.83575e+00,5.0,7.0 );   
	RooRealVar   Gaussigma2 ("Gaussigma2"    ,"Gaussigma2"  ,1.02644e+00, 0.5,2.5 ); 
	RooAbsPdf * pdfMyXGauss2 = new RooGaussian( "pdfMyXGauss2", "pdfMyXGauss2",  varMyXmass, GausMean2 ,Gaussigma2 ) ;

	RooRealVar   GausMean3  ("GausMean3"    ,"GausMean3"  ,12.5,11.0,14.0 );   
	RooRealVar   Gaussigma3 ("Gaussigma3"    ,"Gaussigma3"  ,1.02644e+00, 0.5,5.0 ); 
	RooAbsPdf * pdfMyXGauss3 = new RooGaussian( "pdfMyXGauss3", "pdfMyXGauss3",  varMyXmass, GausMean3 ,Gaussigma3 ) ;
 
	//  RooRealVar   Gauswidth1 ("Gauswidth1"    ,"Gauswidth1"  ,  2.56802,0.01,3.0 ); 
	//RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, MyMean1 ,Gauswidth1 ) ;
	RooRealVar BWMean1("BWMean1","BWMean1",5.82480e+00,5.0,7.0);
	RooRealVar BWWidth1("BWWidth1","BWWidth1",0.5,0.05,5.0);
	RooAbsPdf * pdfBW1 = new RooBreitWigner("pdfBW1","pdfBW1",varMyXmass,MyMean1,BWWidth1);

	RooRealVar BWMean2("BWMean2","BWMean2",12.0,11.0,13.0);
	RooRealVar BWWidth2("BWWidth2","BWWidth2", 1.5,1.0,3.0);
	RooAbsPdf * pdfBW2 = new RooBreitWigner("pdfBW2","pdfBW2",varMyXmass,MyMean1,BWWidth2);
	RooRealVar BWMean3("BWMean3","BWMean3",18.5628/*,15.0,22.0*/);
	RooRealVar BWWidth3("BWWidth3","BWWidth3",0.586284/*,0.01,3.0*/);
	RooAbsPdf * pdfBW3 = new RooBreitWigner("pdfBW3","pdfBW3",varMyXmass,BWMean3,BWWidth3);

	RooRealVar LandauMean1("LandauMean1","LandauMean1", 6.55,5.7,7.0);
	RooRealVar LandauSigma1("LandauSigma1","LandauSigma1",1.7,1.0,2.0);
	RooAbsPdf *pdfLandau1 = new RooLandau("pdfLandau1","pdfLandau1",varMyXmass,LandauMean1,LandauSigma1);

	RooRealVar LandauMean2("LandauMean2","LandauMean2",14.5, 10.0,15.0);
	RooRealVar LandauSigma2("LandauSigma2","LandauSigma2",1.1,0.0,2.0);
	RooAbsPdf *pdfLandau2 = new RooLandau("pdfLandau2","pdfLandau2",varMyXmass,LandauMean2,LandauSigma2);


	RooRealVar MyXfrac1("MyXfrac1","fraction1",0.0302285,0.0,1.0) ;
	RooRealVar MyXfrac2("MyXfrac2","fraction2", 0.714023,0.0,1.0);
	RooRealVar MyXfrac3("MyXfrac3","fraction3",1.0/*,0.0,1.0*/);


	RooRealVar CBMean1("CBMean1","CBMean1",5.82480e+00,4.5,6.5);
	RooRealVar CBsigma1("CBsigma1","CBsigma1",1.0,0.05,4.0);
	RooRealVar CBalpha1("CBalpha1","CBalpha1",2.13,1.0,10.0);
	RooRealVar CBn1("CBn1","CBn1",0.2,0.0,2.0);
	RooAbsPdf * pdfCB1 = new RooCBShape("pdfCB1","pdfCB1",varMyXmass,MyMean1,CBsigma1,CBalpha1,CBn1);

	RooRealVar CBMean2("CBMean2","CBMean2",12.0,11.0,13.0);
	RooRealVar CBsigma2("CBsigma2","CBsigma2",1.0,0.05,4.0);
	RooRealVar CBalpha2("CBalpha2","CBalpha2",2.13,2.1,2.2);
	RooRealVar CBn2("CBn2","CBn2",1.16,1.1,1.2);
	RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2","pdfCB2",varMyXmass,MyMean1,CBsigma2,CBalpha2,CBn2);

	//  RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfLandau1),RooArgList(MyXfrac1)); 
	RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfBW1),RooArgList(MyXfrac1));

	RooRealVar frac1("frac1","Fraction of X2",0.39,0.000,1.0);
	RooAbsPdf* pdfUps13SX = new RooAddPdf("pdfUpsnSX","...",RooArgList(*pdfLandau1, *pdfMyXGauss1),frac1);
	RooRealVar frac2("frac2","Fraction of X3",0.39,0.0000,1.0);
	RooAbsPdf* pdfUpsnSX = new RooAddPdf("pdfUps1SX","Sum of pdfUps1SGaussX1 and pdfUps1SGaussX2",RooArgList(*pdfUps13SX,*pdfLandau2),frac2);     

	//polynominal  
	//    GausEE_peak.setConstant(); 
	
	RooRealVar c1("c1", "c1",2.83467e-01 ,  -1.0, 1.0);
	RooRealVar c2("c2", "c2",4.40355e-02 ,  -1., 1.0);
	RooRealVar c3("c3", "c3", 1.06372e-01,  -1., 1.0);
	RooRealVar c4("c4", "c4", 3.59191e-02,  -1., 1.0);
	RooRealVar c5("c5", "c5", -5.12840e-02,  -1., 1.0);
	RooRealVar c6("c6", "c6", -2.13501e-02,  -1., 1.0);
	RooRealVar c7("c7", "c7", -5.54591e-02,  -15., 15.0);
	RooRealVar c8("c8", "c8", -5.54591e-02,  -15., 15.0);
	RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2));

	RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 100000,  0.0, 90000000000.0);
		
	RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfUpsnSX, nSigMyX);//single gausssian
	// RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);//fixed shape

	RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);

	// RooDataHist alldata("alldata","alldata",varMyXmass, myARCDimuMassPullUpsiScaled);
	RooDataHist alldata("alldata","alldata",varMyXmass, myARCDimuMassPullUpsi);
	

	//do s signal fit scan
	RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
	// RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;
	
	mytotalPdf.fitTo(alldata,Minos(kTRUE), Save(1));

	gROOT->SetStyle("Plain");
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(10);
	gStyle->SetStatY(0.9);
	gStyle->SetStatX(0.9);
	// gStyle->SetStatStyle(1011);
	gStyle->SetStatTextColor(2);
	gStyle->SetHistFillColor(kBlue);
	gStyle->SetOptFit(11111);

	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();
	RooPlot *frame = varMyXmass.frame( (int)((JpsiMassmax-JpsiMassmin)/mybinwidth) );   //30-12=18


	alldata.plotOn(frame, DataError(RooAbsData::SumW2) );
	mytotalPdf.plotOn(frame, Components(RooArgSet(*extendpdfBkgPol)),LineStyle(kDashed),LineColor(kBlue),Range(JpsiMassmin, JpsiMassmax) );
	//mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
	//mytotalPdf.paramOn(frame);
	mytotalPdf.plotOn(frame);
	
	frame->SetTitle("");  
	frame->GetXaxis()->SetTitleSize(0.05);
	frame->GetXaxis()->SetLabelSize(0.035);
	frame->GetXaxis()->SetTitleOffset(0.9);
	frame->GetYaxis()->SetTitleSize(0.05);
	frame->GetYaxis()->SetTitleOffset(1.0);
	frame->GetXaxis()->SetTitle("#Upsilon(1S) Pull ");
	frame->GetYaxis()->SetTitle("(Data-Fit)/Error");
	frame->SetMarkerColor(1);
	frame->SetMarkerSize(2.0);
	frame->SetMinimum(-500);
	// frame->SetMaximum(120);
	frame->Draw();
	// TLatex *t = new TLatex();
	TLatex *t = new TLatex();
	t->SetNDC();
	t->SetTextAlign(22);
	t->SetTextColor(2);
	t->SetTextFont(22);
	t->SetTextSizePixels(22);
	t->SetTextSize(0.045);
	t->DrawLatex(0.72,0.85,"#Upsilon(1S) #sigma = 1.00606");
	// t->DrawLatex(0.72,0.80,"2011 & 2012");
 	// t->DrawLatex(0.72,0.75,"DoubleMu");


	// TCanvas * cRes=new TCanvas("cRes","cRes",800,600);
	// cRes->cd();

 	/*RooHist * hresid = frame->residHist() ;
	if (!hresid) Error("hresid","hresid is nULL");
	hresid->SetMarkerStyle(8);
	hresid->SetMarkerSize(2.0);
	hresid->SetMarkerColor(2);
	hresid->SetLineColor(4);
	hresid->Draw("e1");*/


	// TCanvas * cPull=new TCanvas("cPull","cPull",800,600);
	// cPull->cd();

 	RooHist* hpull = frame->pullHist() ;
	if (!hpull) Error("hpull","hpull is nULL");
	hpull->SetMarkerStyle(8);
	hpull->SetMarkerSize(2.0);
	hpull->SetMarkerColor(2);
	hpull->SetLineColor(4);
	hpull->Draw("e1");


	







	return;


}  


