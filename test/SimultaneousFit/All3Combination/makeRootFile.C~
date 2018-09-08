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
#include <vector>

#include <TH1F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TF1.h>
// gStyle->SetOptFit(11111);

void makeRootFile()
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

	TFile* myoutput = new TFile ("fourmuonmassNolightmeson.root","recreate");

	TH1F* my2Mu2EleMassHist = new TH1F("my2Mu2EleMassHist","my2Mu2EleMassHist",500,0.0,50.0);
	TH1F* myFourMuonMassHist = new TH1F("myFourMuonMassHist","myFourMuonMassHist",500,0.0,50.0);

	std::vector<float> massVector;

	// std::ifstream infile("2mu2elemass.txt");
	std::ifstream infile("7and8TeVcombinedMuOniaDoubleMunolightmesoninunselectedpair.txt");
	float mass,var1,var2;
	

	while(infile)
	{
		infile>>mass>>var1>>var2;
		massVector.push_back(mass);
	}


	for(int i=0; i < massVector.size(); i++)
	{
		myFourMuonMassHist->Fill( massVector[i] );
	}

		
	myoutput->Write();
}