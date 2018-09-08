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


void reversemomentum()
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

	ofstream myoutfilereversemomentum("myoutfilereversemomentum.txt");
	TFile* myoutput = new TFile ("myoutputreverseMomentum.root","recreate");

	TH1F* myMuMuPairsDihedralat18dot5GeV = new TH1F("myMuMuPairsDihedralat18dot5GeV","myMuMuPairsDihedralat18dot5GeV",20,0,3.142);
	TH1F* myMuMuPairsDihedralatSideband = new TH1F("myMuMuPairsDihedralatSideband","myMuMuPairsDihedralatSideband",20,0,3.142);
	TH1F* myMuMuPairsHelicityat18dot5GeV = new TH1F("myMuMuPairsHelicityat18dot5GeV","myMuMuPairsHelicityat18dot5GeV",22,-1.1,1.1);
	TH1F* myMuMuPairsHelicityatSideband = new TH1F("myMuMuPairsHelicityatSideband","myMuMuPairsHelicityatSideband",22,-1.1,1.1);
	TH1F* myMupmumu1Helicityat18dot5GeV = new TH1F("myMupmumu1Helicityat18dot5GeV","myMupmumu1Helicityat18dot5GeV",22,-1.1,1.1);
	TH1F* myMupmumu1HelicityatSideband = new TH1F("myMupmumu1HelicityatSideband","myMupmumu1HelicityatSideband",22,-1.1,1.1);
	TH1F* myMupmumu2Helicityat18dot5GeV = new TH1F("myMupmumu2Helicityat18dot5GeV","myMupmumu2Helicityat18dot5GeV",22,-1.1,1.1);
	TH1F* myMupmumu2HelicityatSideband = new TH1F("myMupmumu2HelicityatSideband","myMupmumu2HelicityatSideband",22,-1.1,1.1);
	
	TH1F* myEventMixingMassHistfinebin = new TH1F("myEventMixingMassHistfinebin","myEventMixingMassHistfinebin",500,0.0,50.0);
	TH1F* myEventMixingMassHist = new TH1F("myEventMixingMassHist","myEventMixingMassHist",250,0.0,50.0);
	TH1F* myEventMixingMassHist1 = new TH1F("myEventMixingMassHist1","myEventMixingMassHist1",90,12.0,30.0);
	TH1F* myEventMixingMassHist2 = new TH1F("myEventMixingMassHist2","myEventMixingMassHist2",55,14.0,25.0);

	TH1F* myFourMuonMassHist = new TH1F("myFourMuonMassHist","myFourMuonMassHist",500,0.0,50.0);

	TH1F* myFourMuonReversedV1PxHist = new TH1F("myFourMuonReversedV1PxHist","myFourMuonReversedV1PxHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1PyHist = new TH1F("myFourMuonReversedV1PyHist","myFourMuonReversedV1PyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1PzHist = new TH1F("myFourMuonReversedV1PzHist","myFourMuonReversedV1PzHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1PxPyHist = new TH1F("myFourMuonReversedV1PxPyHist","myFourMuonReversedV1PxPyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV2PxHist = new TH1F("myFourMuonReversedV2PxHist","myFourMuonReversedV2PxHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV2PyHist = new TH1F("myFourMuonReversedV2PyHist","myFourMuonReversedV2PyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV2PxPyHist = new TH1F("myFourMuonReversedV2PxPyHist","myFourMuonReversedV2PxPyHist",500,0.0,50.0);
	TH1F* myFourMuonReversedV1V2PxPyHist = new TH1F("myFourMuonReversedV1V2PxPyHist","myFourMuonReversedV1V2PxPyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedIndividualParPxHist = new TH1F("myFourMuonReversedIndividualParPxHist","myFourMuonReversedIndividualParPxHist",500,0.0,50.0);
	

	TH1F * myFourMuonReversedV11PxHist = new TH1F("myFourMuonReversedV11PxHist","myFourMuonReversedV11PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV11PyHist = new TH1F("myFourMuonReversedV11PyHist","myFourMuonReversedV11PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV12PxHist = new TH1F("myFourMuonReversedV12PxHist","myFourMuonReversedV12PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV12PyHist = new TH1F("myFourMuonReversedV12PyHist","myFourMuonReversedV12PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV21PxHist = new TH1F("myFourMuonReversedV21PxHist","myFourMuonReversedV21PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV21PyHist = new TH1F("myFourMuonReversedV21PyHist","myFourMuonReversedV21PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedV22PxHist = new TH1F("myFourMuonReversedV22PxHist","myFourMuonReversedV22PxHist",500,0.0,50.0);
	TH1F * myFourMuonReversedV22PyHist = new TH1F("myFourMuonReversedV22PyHist","myFourMuonReversedV22PyHist",500,0.0,50.0);

	TH1F * myFourMuonReversedEachMuonPxPyHist = new TH1F("myFourMuonReversedEachMuonPxPyHist","myFourMuonReversedEachMuonPxPyHist",500,0.0,50.0);

	TH1F* myDoubleMuonHist = new TH1F("myDoubleMuonHist","myDoubleMuonHist",250,0.0,50.0);

	std::vector<TLorentzVector> P4Vector1,P4Vector2, P4Vector11, P4Vector12, P4Vector21,P4Vector22;
	std::vector<float> mvector1,mvector2;

	cout<<"##########################################################"<<endl;

	std::ifstream infile("myfourmuonevtmixNolm.txt");
	float px1,py1,pz1,m1,px2,py2,pz2,m2, px11,py11,pz11,px12,py12,pz12,px21,py21,pz21,px22,py22,pz22;
	TLorentzVector p4,p4_1,p4_2;
	
	const double ele_mass = 0.000510998;
	const double muon_mass =  0.105658;

	while(infile)
	{
		infile>>px1>>py1>>pz1>>m1>>px2>>py2>>pz2>>m2>>px11>>py11>>pz11>>px12>>py12>>pz12>>px21>>py21>>pz21>>px22>>py22>>pz22;
		


		p4_1.SetXYZM(px1,py1,pz1,m1);
		p4_2.SetXYZM(px2,py2,pz2,m2);
		//
		// if( (p4_1+p4_2).M() > 13.0 && (p4_1+p4_2).M() < 25.0 )
		{
			P4Vector1.push_back(p4_1);
			P4Vector2.push_back(p4_2);

			mvector1.push_back(m1);
			mvector2.push_back(m2);

			p4.SetXYZM(px11,py11,pz11,muon_mass);
			P4Vector11.push_back(p4);

			p4.SetXYZM(px12,py12,pz12,muon_mass);
			P4Vector12.push_back(p4);

			p4.SetXYZM(px21,py21,pz21,ele_mass);
			P4Vector21.push_back(p4);

			p4.SetXYZM(px22,py22,pz22,ele_mass);
			P4Vector22.push_back(p4);
		}
		




		// p4.SetXYZM(px1,py1,pz1,m1);
		// P4Vector1.push_back(p4);

		// p4.SetXYZM(px2,py2,pz2,m2);
		// P4Vector2.push_back(p4);

		// mvector1.push_back(m1);
		// mvector2.push_back(m2);

		// p4.SetXYZM(px11,py11,pz11,mymumass);
		// P4Vector11.push_back(p4);

		// p4.SetXYZM(px12,py12,pz12,mymumass);
		// P4Vector12.push_back(p4);

		// p4.SetXYZM(px21,py21,pz21,mymumass);
		// P4Vector21.push_back(p4);

		// p4.SetXYZM(px22,py22,pz22,mymumass);
		// P4Vector22.push_back(p4);
		
	}
	cout<<P4Vector1.size()<<endl;
	//return;
	

	for(int i=0; i < P4Vector1.size(); i++)
	{
		// if( (P4Vector1[i]+P4Vector2[i]).M() < 13.0 && (P4Vector1[i]+P4Vector2[i]).M() > 25.0 ) continue;
		if(i%100==0) cout<<"i="<<i<<endl;
		cout<<"i="<<i<<endl;
		TLorentzVector p4tmp11, p4tmp12;
		p4tmp11=P4Vector11[i]; p4tmp12=P4Vector12[i];
		for(int j=0; j<P4Vector2.size(); j++)
		{
			TLorentzVector p4tmp21, p4tmp22;
			p4tmp21=P4Vector21[j]; p4tmp22=P4Vector22[j];

			TLorentzVector tmpp4, tmpp41,tmpp42;
			tmpp41=P4Vector1[i]; tmpp42=P4Vector2[j];

			float mydr=P4Vector1[i].Vect().DeltaR(  P4Vector2[i].Vect());
			float mydrx=P4Vector1[i].Vect().DeltaR(  P4Vector2[j].Vect());
			tmpp4 = tmpp41+tmpp42;
			
			if(i!=j)
			{
				if(1
				
					&& fabs(mydr)> 1.0*fabs(mydrx) 
					&& fabs(mvector2[i]-mvector2[j])<0.5*mvector2[i] 			   					   		
					)
				{
					// calculate angles with evt-mixing
					// dihedral angle
					TLorentzVector myfourmuonp4=p4tmp11+p4tmp12+p4tmp21+p4tmp22;
					float myfourmuonmass = myfourmuonp4.M();

					TLorentzVector fitMu11bosstedp4, fitMu12bosstedp4, fitMu21bosstedp4, fitMu22bosstedp4;
					fitMu11bosstedp4 = p4tmp11; fitMu12bosstedp4 = p4tmp12;
					fitMu21bosstedp4 = p4tmp21; fitMu22bosstedp4 = p4tmp22;
					fitMu11bosstedp4.Boost( -myfourmuonp4.BoostVector() ); fitMu12bosstedp4.Boost( -myfourmuonp4.BoostVector() );
					fitMu21bosstedp4.Boost( -myfourmuonp4.BoostVector() ); fitMu22bosstedp4.Boost( -myfourmuonp4.BoostVector() );
					TVector3 OrthMupMum1 =  fitMu11bosstedp4.Vect().Cross( fitMu12bosstedp4.Vect()  );
					TVector3 OrthMupMum2=fitMu21bosstedp4.Vect().Cross( fitMu22bosstedp4.Vect()  );
					float myDihedral=  TMath::ACos(OrthMupMum1.Unit().Dot(OrthMupMum2.Unit() ) );
					//cout<<"myDihedral="<<myDihedral<<endl;
					//helicity angle of two mumu pairs			  
					TLorentzVector mymupmum1p4=fitMu11bosstedp4+ fitMu12bosstedp4;
					TLorentzVector mymupmum1p4boosted=fitMu11bosstedp4+ fitMu12bosstedp4;
					//mymupmum1p4boosted.Boost( -myfourmuonp4.BoostVector() );
					float mymupmum1CosHelicity= cos( mymupmum1p4boosted.Vect().Angle( myfourmuonp4.Vect() ) );
					//cout<<"mymupmum1CosHelicity="<<mymupmum1CosHelicity<<endl;
					//helicity of mu+mu- for each pair
					TLorentzVector mymupmum2p4=fitMu21bosstedp4+fitMu22bosstedp4;
					//mymupmum2p4.Boost( -myfourmuonp4.BoostVector() );
					TLorentzVector mymupmum1mupboosted; 
					mymupmum1mupboosted=fitMu11bosstedp4; 
					TLorentzVector mymupmum2mupboosted; 
					mymupmum2mupboosted=fitMu21bosstedp4; 
					mymupmum1mupboosted.Boost( -mymupmum1p4.BoostVector() );
					mymupmum2mupboosted.Boost( -mymupmum2p4.BoostVector() );
					float mymupmum1mupCosHelicity= cos( mymupmum1mupboosted.Vect().Angle( mymupmum1p4.Vect() ) );
					float mymupmum2mupCosHelicity= cos( mymupmum2mupboosted.Vect().Angle( mymupmum2p4.Vect() ) );

					if( myfourmuonmass>=18.0 && myfourmuonmass<=19.0 )
					{
						myMuMuPairsDihedralat18dot5GeV->Fill( myDihedral );
						myMuMuPairsHelicityat18dot5GeV->Fill( mymupmum1CosHelicity );
						myMupmumu1Helicityat18dot5GeV->Fill( mymupmum1mupCosHelicity );
						myMupmumu2Helicityat18dot5GeV->Fill( mymupmum2mupCosHelicity );
					}
					if( (myfourmuonmass>=16.0 && myfourmuonmass<=17.0)   //background in signal area is 1/1.8 of sideband
						||
						(myfourmuonmass>=20.0 && myfourmuonmass<=21.0)
						)
					{
						myMuMuPairsDihedralatSideband->Fill( myDihedral );
						myMuMuPairsHelicityatSideband->Fill( mymupmum1CosHelicity );
						myMupmumu1HelicityatSideband->Fill( mymupmum1mupCosHelicity );
						myMupmumu2HelicityatSideband->Fill( mymupmum2mupCosHelicity );
					}

					//calculate angles with evt-mixing

					myEventMixingMassHistfinebin->Fill(tmpp4.M());
					myEventMixingMassHist->Fill(tmpp4.M());
					myEventMixingMassHist1->Fill(tmpp4.M());
					myEventMixingMassHist2->Fill(tmpp4.M());

				}
			}
			if(i==j
				// && mvector2[i]>5.5 && mvector2[j]>5.5
				)
			{
				myFourMuonMassHist->Fill(tmpp4.M());


				// Changed by Suleyman

				// infile>>px1>>py1>>pz1>>m1>>px2>>py2>>pz2>>m2>>px11>>py11>>pz11>>px12>>py12>>pz12>>px21>>py21>>pz21>>px22>>py22>>pz22;
		
				////////////~~~~~~~~~~~~reverse V1 px py 
				TLorentzVector tempV1p4;

				tempV1p4 = P4Vector1[i];
				float tempV1px = tempV1p4.Px();
				float tempV1py = tempV1p4.Py();
				float tempV1pz = tempV1p4.Pz();


				// reverse px of v1
				tempV1p4.SetPx(-tempV1px);
				myFourMuonReversedV1PxHist->Fill( (tempV1p4+P4Vector2[i]).M() );
				myFourMuonReversedV1PxPyHist->Fill( (tempV1p4+P4Vector2[i]).M() );
				myFourMuonReversedV1V2PxPyHist->Fill( (tempV1p4+P4Vector2[i]).M() );
				

				// reverse py of v1
				tempV1p4 = P4Vector1[i];
				tempV1p4.SetPy(-tempV1py);
				myFourMuonReversedV1PyHist->Fill( (tempV1p4+P4Vector2[i]).M() );
				myFourMuonReversedV1PxPyHist->Fill( (tempV1p4+P4Vector2[i]).M() );
				myFourMuonReversedV1V2PxPyHist->Fill( (tempV1p4+P4Vector2[i]).M() );
				// myoutfilereversemomentum<<tempV1p4.Px()<<" "<<tempV1p4.Py()<<" "<<tempV1p4.Pz()
				// 	<<" "<<tempV1p4.M()<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()<<endl;

				// reverse pz of v1
				tempV1p4 = P4Vector1[i];
				tempV1p4.SetPz(-tempV1pz);
				myFourMuonReversedV1PzHist->Fill( (tempV1p4+P4Vector2[i]).M() );


				//////////// reverse V2 px py 
				TLorentzVector tempV2p4;

				tempV2p4 = P4Vector2[i];
				float tempV2px = tempV2p4.Px();
				float tempV2py = tempV2p4.Py();
				float tempV2pz = tempV2p4.Pz();
				// reverse px of v2
				tempV2p4.SetPx(-tempV2px);
				myFourMuonReversedV2PxHist->Fill( (tempV2p4+P4Vector1[i]).M() );
				myFourMuonReversedV2PxPyHist->Fill( (tempV2p4+P4Vector1[i]).M() );
				myFourMuonReversedV1V2PxPyHist->Fill( (tempV2p4+P4Vector1[i]).M() );
				

				// reverse py of v2
				tempV2p4 = P4Vector2[i];
				tempV2p4.SetPy(-tempV2py);
				myFourMuonReversedV2PyHist->Fill( (tempV2p4+P4Vector1[i]).M() );
				myFourMuonReversedV2PxPyHist->Fill( (tempV2p4+P4Vector1[i]).M() );
				myFourMuonReversedV1V2PxPyHist->Fill( (tempV2p4+P4Vector1[i]).M() );









				// reverse each muon's px and py one by one
				// 11 case
				TLorentzVector tempV11p4, tempV12p4, tempV21p4, tempV22p4;
				//reverse px
				// tempV11p4 = P4Vector11[i];
				// float tempV11px = tempV11p4.Px();
				// tempV11p4.SetPx(-tempV11px);
				// myFourMuonReversedIndividualParPxHist->Fill((tempV11p4 + P4Vector12[i]+P4Vector21[i]+P4Vector22[i]).M());
				// myFourMuonReversedV11PxHist->Fill((tempV11p4 + P4Vector12[i]+P4Vector21[i]+P4Vector22[i]).M());
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV11p4 + P4Vector12[i]+P4Vector21[i]+P4Vector22[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<tempV11p4.Px()<<" "<<tempV11p4.Py()<<" "<<tempV11p4.Pz()
				// 	<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
				// 	<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
				// 	<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
				// 	<<endl;
				//reverse py
				// tempV11p4 = P4Vector11[i];
				// float tempV11py = tempV11p4.Py();
				// tempV11p4.SetPy(-tempV11py);
				// myFourMuonReversedV11PyHist->Fill( (tempV11p4 + P4Vector12[i]+P4Vector21[i]+P4Vector22[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV11p4 + P4Vector12[i]+P4Vector21[i]+P4Vector22[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<tempV11p4.Px()<<" "<<tempV11p4.Py()<<" "<<tempV11p4.Pz()
				// 	<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
				// 	<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
				// 	<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
				// 	<<endl;

				tempV11p4 = P4Vector11[i];
				float tempV11px = tempV11p4.Px();
				tempV11p4.SetPx(-tempV11px);
				float tempV11py = tempV11p4.Py();
				tempV11p4.SetPy(-tempV11py);
				myFourMuonReversedEachMuonPxPyHist->Fill((tempV11p4 + P4Vector12[i]+P4Vector21[i]+P4Vector22[i]).M());
				myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
					<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
					<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
					<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
					<<" "<<tempV11p4.Px()<<" "<<tempV11p4.Py()<<" "<<tempV11p4.Pz()
					<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
					<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
					<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
					<<endl;

				//12 case
				//reverse px
				// tempV12p4 = P4Vector12[i];
				// float tempV12px = tempV12p4.Px();
				// tempV12p4.SetPx(-tempV12px);
				// myFourMuonReversedIndividualParPxHist->Fill( (tempV12p4 + P4Vector11[i]+P4Vector21[i]+P4Vector22[i]).M() );
				// myFourMuonReversedV12PxHist->Fill( (tempV12p4 + P4Vector11[i]+P4Vector21[i]+P4Vector22[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV12p4 + P4Vector11[i]+P4Vector21[i]+P4Vector22[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
				// 	<<" "<<tempV12p4.Px()<<" "<<tempV12p4.Py()<<" "<<tempV12p4.Pz()
				// 	<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
				// 	<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
				// 	<<endl;

				// //reverse py
				// tempV12p4 = P4Vector12[i];
				// float tempV12py = tempV12p4.Py();
				// tempV12p4.SetPy(-tempV12py);
				// myFourMuonReversedV12PyHist->Fill( (tempV12p4 + P4Vector11[i]+P4Vector21[i]+P4Vector22[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV12p4 + P4Vector11[i]+P4Vector21[i]+P4Vector22[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
				// 	<<" "<<tempV12p4.Px()<<" "<<tempV12p4.Py()<<" "<<tempV12p4.Pz()
				// 	<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
				// 	<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
				// 	<<endl;


				tempV12p4 = P4Vector12[i];
				float tempV12px = tempV12p4.Px();
				tempV12p4.SetPx(-tempV12px);
				float tempV12py = tempV12p4.Py();
				tempV12p4.SetPy(-tempV12py);
				myFourMuonReversedEachMuonPxPyHist->Fill((tempV12p4 + P4Vector11[i]+P4Vector21[i]+P4Vector22[i]).M());
				myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
					<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
					<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
					<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
					<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
					<<" "<<tempV12p4.Px()<<" "<<tempV12p4.Py()<<" "<<tempV12p4.Pz()
					<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
					<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
					<<endl;

					
				//21 Case
				//reverse px
				// tempV21p4 = P4Vector21[i];
				// float tempV21px = tempV21p4.Px();
				// tempV21p4.SetPx(-tempV21px);
				// myFourMuonReversedIndividualParPxHist->Fill( (tempV21p4 + P4Vector11[i]+P4Vector12[i]+P4Vector22[i]).M() );
				// myFourMuonReversedV21PxHist->Fill( (tempV21p4 + P4Vector11[i]+P4Vector12[i]+P4Vector22[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV21p4 + P4Vector11[i]+P4Vector12[i]+P4Vector22[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
				// 	<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
				// 	<<" "<<tempV21p4.Px()<<" "<<tempV21p4.Py()<<" "<<tempV21p4.Pz()
				// 	<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
				// 	<<endl;

				// //reverse py
				// tempV21p4 = P4Vector21[i];
				// float tempV21py = tempV21p4.Py();
				// tempV21p4.SetPy(-tempV21py);
				// myFourMuonReversedV21PyHist->Fill( (tempV21p4 + P4Vector11[i]+P4Vector12[i]+P4Vector22[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV21p4 + P4Vector11[i]+P4Vector12[i]+P4Vector22[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
				// 	<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
				// 	<<" "<<tempV21p4.Px()<<" "<<tempV21p4.Py()<<" "<<tempV21p4.Pz()
				// 	<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
				// 	<<endl;


				tempV21p4 = P4Vector21[i];
				float tempV21px = tempV21p4.Px();
				tempV21p4.SetPx(-tempV21px);
				float tempV21py = tempV21p4.Py();
				myFourMuonReversedEachMuonPxPyHist->Fill((tempV21p4 + P4Vector11[i]+P4Vector12[i]+P4Vector22[i]).M());
				myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
					<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
					<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
					<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
					<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
					<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
					<<" "<<tempV21p4.Px()<<" "<<tempV21p4.Py()<<" "<<tempV21p4.Pz()
					<<" "<<P4Vector22[i].Px()<<" "<<P4Vector22[i].Py()<<" "<<P4Vector22[i].Pz()
					<<endl;



				//22 Case
				//reverse px
				// tempV22p4 = P4Vector22[i];
				// float tempV22px = tempV22p4.Px();
				// tempV22p4.SetPx(-tempV22px);
				// myFourMuonReversedIndividualParPxHist->Fill( (tempV22p4 + P4Vector11[i]+P4Vector12[i]+P4Vector21[i]).M() );
				// myFourMuonReversedV22PxHist->Fill( (tempV22p4 + P4Vector11[i]+P4Vector12[i]+P4Vector21[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV22p4 + P4Vector11[i]+P4Vector12[i]+P4Vector21[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
				// 	<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
				// 	<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
				// 	<<" "<<tempV22p4.Px()<<" "<<tempV22p4.Py()<<" "<<tempV22p4.Pz()
				// 	<<endl;

				// //reverse py
				// tempV22p4 = P4Vector22[i];
				// float tempV22py = tempV22p4.Py();
				// tempV22p4.SetPy(-tempV22py);
				// myFourMuonReversedV22PyHist->Fill( (tempV22p4 + P4Vector11[i]+P4Vector12[i]+P4Vector21[i]).M() );
				// myFourMuonReversedEachMuonPxPyHist->Fill((tempV22p4 + P4Vector11[i]+P4Vector12[i]+P4Vector21[i]).M());
				// myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
				// 	<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
				// 	<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
				// 	<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
				// 	<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
				// 	<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
				// 	<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
				// 	<<" "<<tempV22p4.Px()<<" "<<tempV22p4.Py()<<" "<<tempV22p4.Pz()
				// 	<<endl;

				tempV22p4 = P4Vector22[i];
				float tempV22px = tempV22p4.Px();
				tempV22p4.SetPx(-tempV22px);
				float tempV22py = tempV22p4.Py();
				tempV22p4.SetPy(-tempV22py);
				myFourMuonReversedEachMuonPxPyHist->Fill((tempV22p4 + P4Vector11[i]+P4Vector12[i]+P4Vector21[i]).M());
				myoutfilereversemomentum<<P4Vector1[i].Px()<<" "<<P4Vector1[i].Py()
					<<" "<<P4Vector1[i].Pz()<<" "<<P4Vector1[i].M()
					<<" "<<P4Vector2[i].Px()<<" "<<P4Vector2[i].Py()
					<<" "<<P4Vector2[i].Pz()<<" "<<P4Vector2[i].M()
					<<" "<<P4Vector11[i].Px()<<" "<<P4Vector11[i].Py()<<" "<<P4Vector11[i].Pz()
					<<" "<<P4Vector12[i].Px()<<" "<<P4Vector12[i].Py()<<" "<<P4Vector12[i].Pz()
					<<" "<<P4Vector21[i].Px()<<" "<<P4Vector21[i].Py()<<" "<<P4Vector21[i].Pz()
					<<" "<<tempV22p4.Px()<<" "<<tempV22p4.Py()<<" "<<tempV22p4.Pz()
					<<endl;





				// Suleyman end
			}

		}

	}

	myMuMuPairsDihedralat18dot5GeV->Write();
	myMuMuPairsDihedralatSideband->Write();
	myMuMuPairsHelicityat18dot5GeV->Write();
	myMuMuPairsHelicityatSideband->Write();
	myMupmumu1Helicityat18dot5GeV->Write();
	myMupmumu1HelicityatSideband->Write();
	myMupmumu2Helicityat18dot5GeV->Write();
	myMupmumu2HelicityatSideband->Write();


	myEventMixingMassHistfinebin->Write();
	myEventMixingMassHist->Write();
	myEventMixingMassHist1->Write();
	myEventMixingMassHist2->Write();
	myFourMuonMassHist->Write();

	myFourMuonReversedV1PxHist->Write();
	myFourMuonReversedV1PyHist->Write();
	myFourMuonReversedV1PzHist->Write();
	myFourMuonReversedV1PxPyHist->Write();
	myFourMuonReversedV2PxHist->Write();
	myFourMuonReversedV2PyHist->Write();
	myFourMuonReversedV2PxPyHist->Write();
	myFourMuonReversedV1V2PxPyHist->Write();

	myFourMuonReversedV11PxHist->Write();
	myFourMuonReversedV11PyHist->Write();

	myFourMuonReversedV12PxHist->Write();
	myFourMuonReversedV12PyHist->Write();

	myFourMuonReversedV21PxHist->Write();
	myFourMuonReversedV21PyHist->Write();

	myFourMuonReversedV22PxHist->Write();
	myFourMuonReversedV22PyHist->Write();

	myFourMuonReversedEachMuonPxPyHist->Write();

	myFourMuonReversedIndividualParPxHist->Write();

	myDoubleMuonHist->Write();

	// myEventMixingMassHistfinebin->Draw("e1");

	cout.precision(30);
	
	myEventMixingMassHistfinebin->Rebin(4);
	myEventMixingMassHistfinebin->SetTitle("");
	myEventMixingMassHistfinebin->GetXaxis()->SetTitleSize(0.06);
	myEventMixingMassHistfinebin->GetXaxis()->SetRange(25,125);
	myEventMixingMassHistfinebin->GetYaxis()->SetTitleSize(0.06);
	myEventMixingMassHistfinebin->GetXaxis()->SetTitleOffset(0.7);
	myEventMixingMassHistfinebin->GetYaxis()->SetTitleOffset(0.8);
	myEventMixingMassHistfinebin->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}e^{+}e^{-}) [GeV]");
	myEventMixingMassHistfinebin->GetYaxis()->SetTitle("Candidates/400 MeV");
	myEventMixingMassHistfinebin->Fit("pol8","","",13.0, 45.0); // 12-35	
	
	// TF1 *h = new TF1("h","11936966.598168237135-4493827.4340615812689*x+726321.87292027298827*pow(x,2)-66371.347260532653308*pow(x,3)+3794.0260392078753284*pow(x,4)-141.18749671628626174*pow(x,5)+3.4301663700965274728*pow(x,6)-0.052587312230767353782*pow(x,7)+0.0004625224632395727193*pow(x,8)-1.7810136675886924501e-06*pow(x,9)",11.8,41.00);

	// h->SetLineColor(4);
	// h->Draw();
	


	// Suleyman// canvas // 
	
	/*TCanvas* myc1=new TCanvas("myc1","myMyXPt",800,600);
	// myFourMuonMassHist->Rebin();
	// myFourMuonMassHist->GetXaxis()->SetRange(120,300);
	myFourMuonMassHist->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	myFourMuonMassHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	myFourMuonMassHist->SetLineColor(2);
	myFourMuonMassHist->Draw("e1");
	myFourMuonReversedV1V2PxPyHist->SetNormFactor(4341);
	// myFourMuonReversedV1V2PxPyHist->Rebin();
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetRange(120,300);
	myFourMuonReversedV1V2PxPyHist->SetLineColor(4);
	myFourMuonReversedV1V2PxPyHist->Draw("e1same");
	myc1->SaveAs("ReversedPxPy.pdf");

	*/



	// TCanvas* myc3=new TCanvas("myc3","BkgModelandDefaultFourmuMass",800,600);
	// myFourMuonMassHist->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	// myFourMuonMassHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	// myFourMuonMassHist->SetLineColor(2);
	// myFourMuonMassHist->Draw("e1");

	// myFourMuonReversedEachMuonPxPyHist->SetNormFactor(4341);
	// myFourMuonReversedEachMuonPxPyHist->SetLineColor(4);
	// myFourMuonReversedEachMuonPxPyHist->Draw("e1same");
	
	// myc3->SaveAs("BkgModelandDefaultFourmuMass.pdf");







	 // TCanvas* myc2=new TCanvas("myc2","BkgModel",800,600);
	 // myFourMuonReversedEachMuonPxPyHist->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]");
	 // myFourMuonReversedEachMuonPxPyHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	 // myFourMuonMassHist->Draw("e1");
	 // myFourMuonReversedEachMuonPxPyHist->Fit("pol8","","",12.0,35.0);
	// myc2->SaveAs("BkgModel.pdf");





	// TCanvas* myc2=new TCanvas("myc2","BkgModel",800,600);
	// myFourMuonReversedV1V2PxPyHist->Rebin(6);
	// myFourMuonReversedV1V2PxPyHist->SetTitle("");
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetTitleSize(0.06);
	// myFourMuonReversedV1V2PxPyHist->GetYaxis()->SetTitleSize(0.06);
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetTitleOffset(0.7);
	// myFourMuonReversedV1V2PxPyHist->GetYaxis()->SetTitleOffset(0.8);
	// myFourMuonReversedV1V2PxPyHist->GetXaxis()->SetTitle("m((#mu^{+}#mu^{-})_{1}(#mu^{+}#mu^{-})_{2}) [GeV]");
	// myFourMuonReversedV1V2PxPyHist->GetYaxis()->SetTitle("Candidates/100 MeV");
	// myFourMuonReversedV1V2PxPyHist->Draw("e1");
	// myFourMuonReversedV1V2PxPyHist->Fit("pol5","","",13.0,25.0);
	// myc2->SaveAs("reversedv1v2pxpy.pdf");
	// myc2->SaveAs("reversedv1v2pxpy.gif");






}
