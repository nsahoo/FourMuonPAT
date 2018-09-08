#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"
#include "TPoint.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void addhistos()
{
	
	TFile * f=new TFile("Combined2011and2012NoVertexCut.root");
	TH1F * h_forV1highpair = (TH1F*) f->Get("myMuMumassforV1highpair");
	TH1F * h_forV1lowpair = (TH1F*) f->Get("myMuMumassforV1lowpair");
	TH1F * h_formumuhighpair = (TH1F*) f->Get("myMuMumassformumuhighpair");
	TH1F * h_formumulowpair = (TH1F*) f->Get("myMuMumassforV1lowpair");

	TH1F h_sum = (*h_forV1highpair)+(*h_forV1lowpair)+(*h_formumuhighpair)+(*h_formumulowpair);
	TFile* myhbk = new TFile ("myMuMuAfterNoVertexCut.root","recreate");
	h_sum.Write();
	// myhbk->Write();
	
}