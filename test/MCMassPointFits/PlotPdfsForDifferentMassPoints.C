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

void PlotPdfsForDifferentMassPoints() 
{

	double xMassMin=12, xMassMax=55.0;

	double mybinwidth=0.1;


	// put all the pit values here

	const int n = 5;

	double mymeanAr[n] = {1.49951e+01,1.84859e+01,2.49840e+01,3.59621e+01,4.99372e+01};
	double mymeanErAr[n] = {3.25001e-03,3.08078e-03,4.45200e-03,6.70819e-03,1.27928e-02};

	// double mySignalYieldAr[n] = {2.40200e+03,3.97800e+03,3.89300e+03,3.02300e+03,1.94703e+03};
	double mySignalYieldAr[n] = {1000,1000,1000,1000,1000};

	double mysigma1Ar[n] = {7.90862e-02,1.18533e-01,1.36811e-01,2.19147e-01,3.67275e-01};
	double mysigma1ErAr[n] = {5.49394e-03,5.33805e-03,8.75156e-03,1.42098e-02,3.02451e-02};

	double mysigma2Ar[n] = {1.66641e-01,2.17124e-01,2.73989e-01,4.29389e-01,7.23758e-01};
	double mysigma2ErAr[n] = {6.92089e-03,7.99532e-03,8.25709e-03,1.95455e-02,5.40276e-02};

	double myAlpha1Ar[n] = {9.34172e-01,1.40539e+00,1.23415e+00,1.95033e+00,2.17993e+00};
	double myAlpha1ErAr[n] = {8.25862e-02,7.81915e-02,9.34830e-02,1.38425e-01,2.06325e-01};

	double myAlpha2Ar[n] = {-2.48465e+00,-2.31294e+00,-2.07242e+00,-2.13790e+00,-2.29286e+00};
	double myAlpha2ErAr[n] = {1.79855e-01,1.36255e-01,1.02753e-01,1.65817e-01,2.29828e-01};

	double myn1Ar[n] = {2.95064e+00,1.49758e+00,1.22350e+00,4.92823e-01,3.14943e-01};
	double myn1ErAr[n] = {4.78336e-01,1.53110e-01,1.42448e-01,1.38413e-01,1.94062e-01};
	
	double myn2Ar[n] = {1.01135e+00,1.13698e+00,1.65316e+00,1.16202e+00,3.74171e-01};
	double myn2ErAr[n] = {2.83406e-01,2.75035e-01,2.64880e-01,3.54971e-01,2.67849e-01};

	double myFracAr[n] = {4.60737e-01,5.11317e-01,3.94052e-01,4.78057e-01,5.81179e-01};
	double myFracErAr[n] = {5.54709e-02,5.01102e-02,4.37130e-02,5.87283e-02,8.96272e-02};




	gROOT->SetStyle("Plain");  
	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();


	for (int i = 0; i < n; ++i)
	{



		RooRealVar varMyXmass("varMyXmass", "m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",xMassMin,xMassMax);


		RooArgSet* observables = new RooArgSet(varMyXmass,"observables");


		RooRealVar   MyMean  ("MyMean"    ,"MyMean" , mymeanAr[i]);
		RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ",mySignalYieldAr[i]); 


		RooRealVar MyXfrac("MyXfrac","fraction of double gaussian1",myFracAr[i]) ;

		RooRealVar CBsigma1("CBsigma1","CBsigma1",mysigma1Ar[i]);
		RooRealVar CBalpha1("CBalpha1","CBalpha1",myAlpha1Ar[i]);
		RooRealVar CBn1("CBn1","CBn1",myn1Ar[i]);
		RooAbsPdf * pdfCB1 = new RooCBShape("pdfCB1","pdfCB1",varMyXmass,MyMean,CBsigma1,CBalpha1,CBn1);
		RooRealVar CBsigma2("CBsigma2","CBsigma2",mysigma2Ar[i]);
		RooRealVar CBalpha2("CBalpha2","CBalpha2",myAlpha2Ar[i]);
		RooRealVar CBn2("CBn2","CBn2",myn2Ar[i]);
		RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2","pdfCB2",varMyXmass,MyMean,CBsigma2,CBalpha2,CBn2);


		RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfCB2),RooArgList(MyXfrac)); 



		RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);


		RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX), RooArgList(nSigMyX) ) ;




		RooPlot *frame = varMyXmass.frame( /*(int)((xMassMax-xMassMin)/mybinwidth)*/ );




		mytotalPdf.plotOn(frame,LineColor(i+2));

		frame->SetTitle("");  
		frame->GetXaxis()->SetTitleSize(0.05);
		frame->GetXaxis()->SetLabelSize(0.035);
		frame->GetXaxis()->SetTitleOffset(0.9);
		frame->GetYaxis()->SetTitleSize(0.05);
		frame->GetYaxis()->SetTitleOffset(0.9);
		frame->SetMarkerColor(5);
		frame->SetFillColor(2);
		frame->SetLineColor(5);
		frame->SetMarkerSize(2.0);
		if(i == 0)	frame->Draw();
		else frame->Draw("same");

	}
	

	return;






}  


