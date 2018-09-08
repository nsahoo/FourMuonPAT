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


void masspointsTGraph()
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



	c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
	// c1->SetFillColor(42);
	c1->SetGrid();
	c1->GetFrame()->SetFillColor(21);
	c1->GetFrame()->SetBorderSize(12);
	const int n = 5;


	
	// with floating parameters
	double mymeanAr[n] = {1.49951e+01,1.84859e+01,2.49840e+01,3.59621e+01,4.99372e+01};
	double mymeanErAr[n] = {3.25001e-03,3.08078e-03,4.45200e-03,6.70819e-03,1.27928e-02};

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


	// gr = new TGraphErrors(n,mymeanAr,mysigma1Ar,mymeanErAr,mysigma1ErAr);
	// gr = new TGraphErrors(n,mymeanAr,mysigma2Ar,mymeanErAr,mysigma2ErAr);
	// gr = new TGraphErrors(n,mymeanAr,myAlpha1Ar,mymeanErAr,myAlpha1ErAr);
	// gr = new TGraphErrors(n,mymeanAr,myAlpha2Ar,mymeanErAr,myAlpha2ErAr);
	// gr = new TGraphErrors(n,mymeanAr,myn1Ar,mymeanErAr,myn1ErAr);
	// gr = new TGraphErrors(n,mymeanAr,myn2Ar,mymeanErAr,myn2ErAr);
	gr = new TGraphErrors(n,mymeanAr,myFracAr,mymeanErAr,myFracErAr);
   	gr->SetTitle("");
   	gr->SetMarkerColor(2);
   	gr->SetMarkerStyle(21);
   	gr->Draw("AP");
   	gr->GetXaxis()->SetTitle("mass [GeV]");
   	// gr->GetYaxis()->SetTitle("CB Sigma 1 [GeV]");
   	// gr->GetYaxis()->SetTitle("CB Sigma 2 [GeV]");
   	// gr->GetYaxis()->SetTitle("CB Alpha 1");
   	// gr->GetYaxis()->SetTitle("CB Alpha 2");
   	// gr->GetYaxis()->SetTitle("CB n 1");
   	// gr->GetYaxis()->SetTitle("CB n 2");
   	gr->GetYaxis()->SetTitle("Fraction");
   	gr->Fit("pol0","","",5,55);


   	// TF1 *f = new TF1("f","7.12433e-01+2.66384e-02*x",5.0,55.0); // Alpha1
   	// TF1 *f = new TF1("f","-2.13556e+00",5.0,55.0); // Alpha2
	// TF1 *f = new TF1("f","-4.35169e-02+8.64066e-03*x-3.50868e-05*pow(x,2)",5.0,55.0); // Sigma1
	// TF1 *f = new TF1("f","3.32583e-02+7.22298e-03*x+1.03478e-04*pow(x,2)",5.0,55.0); // Sigma2
	TF1 *f = new TF1("f","4.58737e-01",5.0,55.0); // Fraction
	// TF1 *f = new TF1("f","3.61764e+00-1.24494e-01*x+1.18504e-03*pow(x,2)",5.0,55.0); // n1
	// TF1 *f = new TF1("f","1.38336e+00",5.0,55.0); // n2
	
	f->SetLineColor(4);
	f->Draw("same");







   	return c1;
	

	

	




}
