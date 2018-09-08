#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream> 
#include "TLorentzVector.h"
#include "TPoint.h"
// #include "TMath.h" 
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

#include <TH1F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TF1.h>
#include "TGraph.h"

#include "TAxis.h"
// gStyle->SetOptFit(11111);


void masspoints()
{
	gStyle->SetStatStyle(0000);
	gStyle->SetStatFormat(0000);
	gStyle->SetOptStat(10);
	gStyle->SetStatY(0.9);
	gStyle->SetStatX(0.9);
	// gStyle->SetStatStyle(1011);
	gStyle->SetStatTextColor(2);
	// gStyle->SetHistFillColor(kBlue);
	gStyle->SetOptFit(11111);


	TFile* myoutput = new TFile ("myoutput.root","recreate");

	TH1F * mySigma1 = new TH1F("mySigma1","mySigma1",60,0.0,60.0);
	mySigma1->GetXaxis()->SetTitle("mass [GeV]");
	mySigma1->GetYaxis()->SetTitle("CB Sigma 1 [GeV]");
	TH1F * mySigma2 = new TH1F("mySigma2","mySigma2",60,0.0,60.0);
	mySigma2->GetXaxis()->SetTitle("mass [GeV]");
	mySigma2->GetYaxis()->SetTitle("CB Sigma 2 [GeV]");
	TH1F * myAlpha1 = new TH1F("myAlpha1","myAlpha1",60,0.0,60.0);
	myAlpha1->GetXaxis()->SetTitle("mass [GeV]");
	myAlpha1->GetYaxis()->SetTitle("CB Alpha 1 [GeV]");
	TH1F * myAlpha2 = new TH1F("myAlpha2","myAlpha2",60,0.0,60.0);
	myAlpha2->GetXaxis()->SetTitle("mass [GeV]");
	myAlpha2->GetYaxis()->SetTitle("CB Alpha 2 [GeV]");
	TH1F * myn1 = new TH1F("myn1","myn1",60,0.0,60.0);
	myn1->GetXaxis()->SetTitle("mass [GeV]");
	myn1->GetYaxis()->SetTitle("CB n 1 [GeV]");
	TH1F * myn2 = new TH1F("myn2","myn2",60,0.0,60.0);
	myn2->GetXaxis()->SetTitle("mass [GeV]");
	myn2->GetYaxis()->SetTitle("CB n 2 [GeV]");

	// with floating parameters
	double mymeanAr[5] = {1.49951e+01,1.84859e+01,2.49840e+01,3.59621e+01,4.99372e+01};
	double mysigma1Ar[5] = {7.90862e-02,1.18533e-01,1.36811e-01,2.19147e-01,3.67275e-01};
	double mysigma2Ar[5] = {1.66641e-01,2.17124e-01,2.73989e-01,4.29389e-01,7.23758e-01};
	double myAlpha1Ar[5] = {9.34172e-01,1.40539e+00,1.23415e+00,1.95033e+00,2.17993e+00};
	double myAlpha2Ar[5] = {-2.48465e+00,-2.31294e+00,-2.07242e+00,-2.13790e+00,-2.29286e+00};
	double myn1Ar[5] = {2.95064e+00,1.49758e+00,1.22350e+00,4.92823e-01,3.14943e-01};
	double myn2Ar[5] = {1.01135e+00,1.13698e+00,1.65316e+00,1.16202e+00,3.74171e-01};

	// // fixt the alpha and n numbers to the default case, float sigma
	// double mymeanAr[6] = {1.09826e+01,1.49889e+01,1.84931e+01,2.49986e+01,3.60044e+01,5.00040e+01};
	// double mysigma1Ar[6] = {7.39797e-02,7.02152e-02,9.39269e-02,1.26210e-01,1.75493e-01,2.70797e-01};
	// double mysigma2Ar[6] = {1.21967e-01,1.40526e-01,1.78532e-01,2.47812e-01,3.62322e-01,5.52886e-01};


	for (int i = 0; i < 6; i++)
	{
		TAxis *xaxis = mySigma1->GetXaxis();
		Int_t binx = xaxis->FindBin( mymeanAr[i] );


		mySigma1->SetBinContent(binx, mysigma1Ar[i]);
		mySigma2->SetBinContent(binx, mysigma2Ar[i]);
		myAlpha1->SetBinContent(binx, myAlpha1Ar[i]);
		myAlpha2->SetBinContent(binx, myAlpha2Ar[i]);
		myn1->SetBinContent(binx, myn1Ar[i]);
		myn2->SetBinContent(binx, myn2Ar[i]);

	}

	

	// TCanvas *c1 = new TCanvas("c1","c1",800,600);
	// mySigma1->Fit("pol2","","",5,55);
	// mySigma2->Fit("pol2","","",5,55);
	// myAlpha1->Fit("pol2","","",5,55);
	// myAlpha2->Fit("pol2","","",5,55);
	// mySigma2->Fit("pol2","","",5,55);
	// mySigma2->Fit("pol2","","",5,55);



	




	myoutput->Write();

}
