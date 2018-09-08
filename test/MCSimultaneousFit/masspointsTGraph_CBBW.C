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


void masspointsTGraph_CBBW()
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

	// fixt the alpha and n numbers to the default case, float sigma
	double mymeanAr[n] = {1.49816e+01,1.84755e+01,2.49713e+01,3.59548e+01,4.99394e+01};
	double mymeanErAr[n] = {3.41176e-03,3.13022e-03,4.26473e-03,6.68985e-03,1.27886e-02};

	double myBWWidthAr[n] = {1.77755e-01,2.03817e-01,3.04906e-01,4.18386e-01,6.94440e-01};
	double myBWWidthErAr[n] = {2.16355e-02,1.93643e-02,2.80390e-02,3.69961e-02,7.40966e-02};

	double myCBSigmaAr[n] = {1.40966e-01,1.82132e-01,2.42269e-01,3.53433e-01,5.05807e-01};
	double myCBSigmaErAr[n] = {4.10773e-03,4.73724e-03,7.86737e-03,1.24573e-02,2.83749e-02};

	double myFracAr[n] = {7.65194e-01,7.03310e-01,6.69178e-01,6.15035e-01,5.52201e-01};
	double myFracErAr[n] = {4.37554e-02,3.22455e-02,3.42161e-02,4.19717e-02,5.55679e-02};

	double mynAr[n] = {2.91768e+00,1.32828e+00,1.08937e+00,6.55158e-01,7.50737e-01};
	double mynErAr[n] = {7.42380e-01,1.86733e-01,1.55926e-01,1.82722e-01,2.47202e-01};

	double myAplhaAr[n] = {1.76902e+00,1.95033e+00,1.90812e+00,2.05463e+00,1.83777e+00};
	double myAplhaErAr[n] = {1.11382e-01,8.71152e-02,1.01770e-01,1.20333e-01,1.76184e-01};


	gr = new TGraphErrors(n,mymeanAr,myBWWidthAr,mymeanErAr,myBWWidthErAr);
	// gr = new TGraphErrors(n,mymeanAr,myCBSigmaAr,mymeanErAr,myCBSigmaErAr);
	// gr = new TGraphErrors(n,mymeanAr,myFracAr,mymeanErAr,myFracErAr);
	// gr = new TGraphErrors(n,mymeanAr,mynAr,mymeanErAr,mynErAr);
	// gr = new TGraphErrors(n,mymeanAr,myAplhaAr,mymeanErAr,myAplhaErAr);

	gr->SetTitle("");
	gr->SetMarkerColor(2);
	gr->SetMarkerStyle(21);
	gr->Draw("AP");
	gr->GetXaxis()->SetTitle("mass [GeV]");
	gr->GetYaxis()->SetTitle("BW Width [GeV]");
	// gr->GetYaxis()->SetTitle("CB Sigma [GeV]");
	// gr->GetYaxis()->SetTitle("Fraction");
	// gr->GetYaxis()->SetTitle("CB n");
	// gr->GetYaxis()->SetTitle("CB Alpha");
	// gr->SetMinimum(0);
   
	gr->Fit("pol2","","",5,55);

	TF1 *f = new TF1("f","-9.08052e-02+1.50605e-02*x+2.73447e-06*pow(x,2)",5.0,55.0); // BW Width
	// TF1 *f = new TF1("f","9.51596e-01-5.30569e-02*x+8.37061e-04*pow(x,2)",5.0,55.0); // CB Alpha
	// TF1 *f = new TF1("f","-8.08821e-02+1.59177e-02*x",5.0,55.0); // CB Sigma
	// TF1 *f = new TF1("f","1.12414e+01-2.12358e-01*x",5.0,55.0); // CB n
	// TF1 *f = new TF1("f","7.37172e-01",5.0,55.0); // Fraction
	f->SetLineColor(4);
	f->Draw("same");
	// Fraction
	// TLine *line = new TLine(5.0,2.60789e-01,55.0,2.60789e-01);
	// line->SetLineColor(kBlue);
	// line->Draw("same");
  


	return c1;



}
