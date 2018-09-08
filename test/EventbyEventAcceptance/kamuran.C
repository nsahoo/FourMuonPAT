#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <TGraph.h>

#include "TFile.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TMath.h"

void kamuran()
{
/*float ptbin[]={0,5,10,15,20,25,30,35};
float effbin[]={0.24,0.24,0.29,0.36,0.39,0.43,0.47};
int nptbins=7;
int neffbins=6;
float Nbin[]={59,154,110,72,26,17,20};
int nNbins=6;
*/

/*
//Four Pt with 10 bins
float ptbin[]={0,10,20,30,40,50,60};
float effbin[]={0.24,0.32,0.37,0.44,0.45,0.60};
float Nbin[]={213,182,53,35,35,25};
int nptbins = 6;
int neffbins =5;
int nNbins = 5;
///End for Four muon  Pt
*/

/*
//Four muon Mass
float ptbin[]={10,20,30,40,50,60};
float effbin[]={0.24,0.3,0.33,0.39,0.34};
float Nbin[]={186,138,68,31,18};
int nptbins = 5;
int neffbins =4;
int nNbins = 4;
*/
//End for four muon Mass

//Lowest muon Pt/////
float ptbin[]={3,3.5,4,4.5,5,5.5};
float effbin[]={0.012,0.25,0.39,0.6,0.6};
float Nbin[]={2,345,100,9,10};
int nptbins = 5;
int neffbins= 4;
int nNbins = 4;
////////////////////

/*
//Lowest muon Pt/////
float ptbin[]={0,3,6,9,12};
float effbin[]={0.22,0.31,0.55,0.53,0.59 };
float Nbin[]={182,247,26,3};
*/
/*
//Pile Up
float ptbin[]={0,5,10,15,20,25,30};
float effbin[]={0.35,0.29,0.30,0.29,0.30,0.21};
float Nbin[]={13,108,171,109,43,14};
int nptbins = 6;
int neffbins =5; 
int nNbins = 5;
///End for PileUp
*/




	TH1F *hist = new TH1F("hist", "",nptbins,ptbin);
//	TH2F *hist = new TH2F("hist", "", nptbins,ptbin,neffbins,effbin);

for(int i=1; i<=nptbins; ++i){


//double error= effbin[i-1]*(1/sqrt(89));
hist->SetBinContent(i,effbin[i-1]);
//hist->SetBinError(i,effbin[i-1]*(1/sqrt(Nbin[i-1])));
hist->SetBinError(i,(sqrt(effbin[i-1]*(1-effbin[i-1])/Nbin[i-1])));
/*
for(int j=0; j<neffbins; ++j){
	hist->GetXaxis()->SetBinContent(i,ptbin[i]);
	hits->GetYaxis()->SetBinContent(j,effbin[j]);

	  }
*/
	}
//hist->SetMarkerColor(kBlue);
//hist->SetMarkerStyle(1);

//hist->GetXaxis()->SetTitle("Four muon p_{T} (#mu^{+}#mu^{-}#mu^{+}#mu^{-})");
//hist->GetXaxis()->SetTitle("Four muon Mass (#mu^{+}#mu^{-}#mu^{+}#mu^{-})");
hist->GetXaxis()->SetTitle("Lowest muon p_{T}");
//hist->GetXaxis()->SetTitle("Number of PrmVrtx");
hist->GetYaxis()->SetTitle("Avarage Efficiency");
hist->Draw("pe");
}

