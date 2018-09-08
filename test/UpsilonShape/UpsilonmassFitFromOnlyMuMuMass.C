#include <stdio.h>
#include <string.h>
#include <sstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TGraph.h"


RooDataSet* dataSet(0);
gStyle->SetOptFit(111111);
gSystem->Load("libRooFit");

using namespace RooFit;
using namespace RooStats;

void UpsilonmassFitFromOnlyMuMuMass() 
{
	double UpsMin = 9.0, UpsMax = 10.0;

	RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_{1} [GeV]",UpsMin,UpsMax);

	RooArgSet variables;
	variables.add(varMymumu1mass);


	RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 1000,  0.0, 10000000.0); 

	// Upsilon Shape
	RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,9.46,9.30,9.60 );
	RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  , 0.200, 0.01,0.5 );
	RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMymumu1mass, GausMean1 ,Gaussigma1 ) ;

	RooRealVar   Gaussigma2 ("Gaussigma2"    ,"Gaussigma2"  , 0.150, 0.01,0.5 );
	RooAbsPdf* pdfMyXGauss2 = new RooGaussian( "pdfMyXGauss2", "pdfMyXGauss2",  varMymumu1mass, GausMean1 ,Gaussigma2 ) ;

	RooRealVar MyXfrac1("MyXfrac1","fraction of double gaussian1",0.0302285,0.0,1.0) ;

	RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfMyXGauss1,*pdfMyXGauss2),RooArgList(MyXfrac1)); 



	
	RooRealVar c1("c1", "c1",-7.37579e-02 ,  -5.0, 5.0);
	RooRealVar c2("c2", "c2",-2.68499e-01 ,  -5.0, 5.0);
	RooRealVar c3("c3", "c3", -5.54591e-02,  -15., 15.0);
	RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMymumu1mass,RooArgSet(c1,c2,c3));

	RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 100000,  0.0, 9000000.0);
	
 
	RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXGauss1, nSigMyX);


	RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);


	RooDataSet * alldata= &(RooDataSet::read("mymumu21.txt",variables,"Q"));

	
	// do s signal fit scan
	RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
	
	
		
	// MyMean1.setVal( myMaxscanmean );MyMean1.setConstant();
	mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));

	gROOT->SetStyle("Plain");  
	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();
	RooPlot *frame = varMymumu1mass.frame( 50 );   //30-12=18


	alldata->plotOn(frame, DataError(RooAbsData::SumW2) );
	mytotalPdf.plotOn(frame, Components(RooArgSet(*extendpdfBkgPol)),LineStyle(kDashed),LineColor(kBlue)/*,Precision(1e-8)*/,Range(UpsMin,UpsMax) );
	// mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX,)) );
	mytotalPdf.paramOn(frame);
	mytotalPdf.plotOn(frame);
	frame->SetTitle("");  
	frame->GetXaxis()->SetTitleSize(0.05);
	frame->GetXaxis()->SetLabelSize(0.035);
	frame->GetXaxis()->SetTitleOffset(0.9);
	frame->GetYaxis()->SetTitleSize(0.05);
	frame->GetYaxis()->SetTitleOffset(0.9);
	frame->SetMarkerColor(1);
	frame->SetMarkerSize(2.0);
	frame->Draw();

	varMymumu1mass.setRange("selection", UpsMin, UpsMax);
	RooAbsReal* mybckinwholerange=extendpdfBkgPol->createIntegral(RooArgSet(varMymumu1mass),"selection");
	RooAbsReal* mySiginwholerange=extendpdfSigMyX->createIntegral(RooArgSet(varMymumu1mass),"selection");

	double lowerbound = 9.4456-3*0.079;
	double higherbound = 9.4456+3*0.079;
	varMymumu1mass.setRange("selection1",lowerbound,higherbound);
	RooAbsReal* mybckin3sigmarange=extendpdfBkgPol->createIntegral(RooArgSet(varMymumu1mass),"selection1");
	RooAbsReal* mySigin3sigmarange=extendpdfSigMyX->createIntegral(RooArgSet(varMymumu1mass),"selection1");
	double mybckratio=(double)mybckin3sigmarange->getVal()/(double)mybckinwholerange->getVal();
	double mySigratio=(double)mySigin3sigmarange->getVal()/(double)mySiginwholerange->getVal();
	 
	cout<<"# Background under 3 sigma Y(1S)="<<mybckratio*nBkgPol.getVal()/*<<", and the ratio="<<mybckratio*/<<endl;
	cout<<"# Yield is 3 sigma Y(1S)="<<mySigratio*nSigMyX.getVal()/*<<", and the ratio="<<mySigratio*/<<endl;
	 
	TLine *line1 = new TLine(lowerbound,0,lowerbound,60);
	line1->SetLineColor(kRed);
	line1->Draw();

	TLine *line2 = new TLine(higherbound,0,higherbound,60);
	line2->SetLineColor(kRed);
	line2->Draw();





	return;


}  


