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


void yieldChangeVsVertex()
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

	TH1F * myYield = new TH1F("myYield","myYield",110,-0.05,1.05);
	myYield->GetXaxis()->SetTitle("Vtx CL");
	myYield->GetYaxis()->SetTitle("Signal Yield");
	TH1F * myLocalSig = new TH1F("myLocalSig","myLocalSig",110,-0.05,1.05);
	myLocalSig->GetXaxis()->SetTitle("Vtx CL");
	myLocalSig->GetYaxis()->SetTitle("Local #sigma");


	// fix the alpha and n numbers to the default case, float sigma
	double myVtxAr[7] = {10e-30,0.05,0.1,0.2,0.3,0.5,0.7};
	double myYieldAr[7] = {137,65,51,39,31,27,22};
	double myLocalSigAr[7] = {5.40,4.7,4.01,3.56,3.10,3.13,3.33};


	for (int i = 0; i < 7; i++)
	{
		TAxis *xaxis = myYield->GetXaxis();
		Int_t binx = xaxis->FindBin( myVtxAr[i] );

		myYield->SetBinContent(binx, myYieldAr[i]);
		myLocalSig->SetBinContent(binx, myLocalSigAr[i]);
	}

	

	// myYield->Draw();
	myLocalSig->Draw();



	




	myoutput->Write();

}
