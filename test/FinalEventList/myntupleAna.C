#define myntuple_cxx
#include "myntuple.h"
#include <TH2.h>



#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"
#include "TVector3.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


#define muon_mass 0.10565837
#define jpsi_mass 3.0967

#define PI  3.141592653589793238463

// struct DeltaR
// {
//     string s;
//     float value;
// };

// bool compareByR(const data &a, const data &b)
// {
//     return a.word.size() < b.word.size();
// }

void myntuple::Loop()
{

	TFile* myhbk = new TFile ("output.root","recreate");

	TH1F* myMuMuMuMumassV1mumubelowV1nolightmeson = new TH1F("myMuMuMuMumassV1mumubelowV1nolightmeson","myMuMuMuMumassV1mumubelowV1nolightmeson",65,13.0,26.0);
	myMuMuMuMumassV1mumubelowV1nolightmeson->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
	myMuMuMuMumassV1mumubelowV1nolightmeson->GetYaxis()->SetTitle("Candidates/200 MeV");

	TH1F* myUpsilonMass = new TH1F("myUpsilonMass","myUpsilonMass",500,0,50);
	TH1F* myMuMuMass = new TH1F("myMuMuMass","myMuMuMass",500,0,50);

	TH1F* myUpsilonMassSignalRegion = new TH1F("myUpsilonMassSignalRegion","myUpsilonMassSignalRegion",500,0,50);
	TH1F* myMuMuMassSignalRegion = new TH1F("myMuMuMassSignalRegion","myMuMuMassSignalRegion",500,0,50);
	TH1F* myUpsilonMassSidebandRegion = new TH1F("myUpsilonMassSidebandRegion","myUpsilonMassSidebandRegion",500,0,50);
	TH1F* myMuMuMassSidebandRegion = new TH1F("myMuMuMassSidebandRegion","myMuMuMassSidebandRegion",500,0,50);


	TH2F* myMuMuEtaVsPtat18dot5GeV = new TH2F("myMuMuEtaVsPtat18dot5GeV","myMuMuEtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	TH2F* myMuMuEtaVsPtatSideband = new TH2F("myMuMuEtaVsPtatSideband","myMuMuEtaVsPtatSideband",60,-3,3, 300,0,30);	
	TH2F* myUpsilonEtaVsPtat18dot5GeV = new TH2F("myUpsilonEtaVsPtat18dot5GeV","myUpsilonEtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	TH2F* myUpsilonEtaVsPtatSideband = new TH2F("myUpsilonEtaVsPtatSideband","myUpsilonEtaVsPtatSideband",60,-3,3, 300,0,30);

	TH1F* myMuMuEtaat18dot5GeV = new TH1F("myMuMuEtaat18dot5GeV","myMuMuEtaat18dot5GeV",60,-3,3);
	TH1F* myMuMuEtaatSideband = new TH1F("myMuMuEtaatSideband","myMuMuEtaatSideband",60,-3,3);
	TH1F* myMuMuPtat18dot5GeV = new TH1F("myMuMuPtat18dot5GeV","myMuMuPtat18dot5GeV",300,0,30);
	TH1F* myMuMuPtatSideband = new TH1F("myMuMuPtatSideband","myMuMuPtatSideband",300,0,30);

	TH1F* myUpsilonEtaat18dot5GeV = new TH1F("myUpsilonEtaat18dot5GeV","myUpsilonEtaat18dot5GeV",60,-3,3);
	TH1F* myUpsilonEtaatSideband = new TH1F("myUpsilonEtaatSideband","myUpsilonEtaatSideband",60,-3,3);
	TH1F* myUpsilonPtat18dot5GeV = new TH1F("myUpsilonPtat18dot5GeV","myUpsilonPtat18dot5GeV",300,0,30);
	TH1F* myUpsilonPtatSideband = new TH1F("myUpsilonPtatSideband","myUpsilonPtatSideband",300,0,30);



	TH2F* myFourMuonEtaVsPtat18dot5GeV = new TH2F("myFourMuonEtaVsPtat18dot5GeV","myFourMuonEtaVsPtat18dot5GeV",60,-3,3, 300,0,30);
	TH2F* myFourMuonEtaVsPtatSideband = new TH2F("myFourMuonEtaVsPtatSideband","myFourMuonEtaVsPtatSideband",60,-3,3, 300,0,30);
	

	TH1F* myFourMuonEtaat18dot5GeV = new TH1F("myFourMuonEtaat18dot5GeV","myFourMuonEtaat18dot5GeV",60,-3,3);
	TH1F* myFourMuonPtat18dot5GeV = new TH1F("myFourMuonPtat18dot5GeV","myFourMuonPtat18dot5GeV",300,0,30);
	TH1F* myFourMuonEtaatSideband = new TH1F("myFourMuonEtaatSideband","myFourMuonEtaatSideband",60,-3,3);
	TH1F* myFourMuonPtatSideband = new TH1F("myFourMuonPtatSideband","myFourMuonPtatSideband",300,0,30);
	

	TH1F* myFourMuonMomentumat18dot5GeV = new TH1F("myFourMuonMomentumat18dot5GeV","myFourMuonMomentumat18dot5GeV",1000,0,100);
	TH1F* myFourMuonMomentumatSideband = new TH1F("myFourMuonMomentumatSideband","myFourMuonMomentumatSideband",1000,0,100);
	



	TH1F * myMu1PtSignalRegion = new TH1F("myMu1PtSignalRegion","myMu1PtSignalRegion",300,0,30);
	myMu1PtSignalRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #Upsilon(1S)");
	myMu1PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu2PtSignalRegion = new TH1F("myMu2PtSignalRegion","myMu2PtSignalRegion",300,0,30);
	myMu2PtSignalRegion->GetXaxis()->SetTitle("#mu^{-} p_{T} from #Upsilon(1S)");
	myMu2PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu3PtSignalRegion = new TH1F("myMu3PtSignalRegion","myMu3PtSignalRegion",300,0,30);
	myMu3PtSignalRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #mu^{+}#mu^{-}");
	myMu3PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu4PtSignalRegion = new TH1F("myMu4PtSignalRegion","myMu4PtSignalRegion",300,0,30);
	myMu4PtSignalRegion->GetXaxis()->SetTitle("#mu^{-} p_{T} from #mu^{+}#mu^{-}");
	myMu4PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");

	TH1F * myMu1PtSidebandRegion = new TH1F("myMu1PtSidebandRegion","myMu1PtSidebandRegion",300,0,30);
	myMu1PtSidebandRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #Upsilon(1S)");
	myMu1PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu2PtSidebandRegion = new TH1F("myMu2PtSidebandRegion","myMu2PtSidebandRegion",300,0,30);
	myMu2PtSidebandRegion->GetXaxis()->SetTitle("#mu^{-} p_{T} from #Upsilon(1S)");
	myMu2PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu3PtSidebandRegion = new TH1F("myMu3PtSidebandRegion","myMu3PtSidebandRegion",300,0,30);
	myMu3PtSidebandRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #mu^{+}#mu^{-}");
	myMu3PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu4PtSidebandRegion = new TH1F("myMu4PtSidebandRegion","myMu4PtSidebandRegion",300,0,30);
	myMu4PtSidebandRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #mu^{+}#mu^{-}");
	myMu4PtSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");



	TH1F * myMu1EtaSignalRegion = new TH1F("myMu1EtaSignalRegion","myMu1EtaSignalRegion",12,-3,3);
	myMu1EtaSignalRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #Upsilon(1S)");
	myMu1EtaSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");

	TH1F * myMu2EtaSignalRegion = new TH1F("myMu2EtaSignalRegion","myMu2EtaSignalRegion",12,-3,3);
	myMu2EtaSignalRegion->GetXaxis()->SetTitle("#mu^{-} p_{T} from #Upsilon(1S)");
	myMu2EtaSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu3EtaSignalRegion = new TH1F("myMu3EtaSignalRegion","myMu3EtaSignalRegion",12,-3,3);
	myMu3EtaSignalRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #mu^{+}#mu^{-}");
	myMu3EtaSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu4EtaSignalRegion = new TH1F("myMu4EtaSignalRegion","myMu4EtaSignalRegion",12,-3,3);
	myMu4EtaSignalRegion->GetXaxis()->SetTitle("#mu^{-} p_{T} from #mu^{+}#mu^{-}");
	myMu4EtaSignalRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");

	TH1F * myMu1EtaSidebandRegion = new TH1F("myMu1EtaSidebandRegion","myMu1EtaSidebandRegion",12,-3,3);
	myMu1EtaSidebandRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #Upsilon(1S)");
	myMu1EtaSidebandRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu2EtaSidebandRegion = new TH1F("myMu2EtaSidebandRegion","myMu2EtaSidebandRegion",12,-3,3);
	myMu2EtaSidebandRegion->GetXaxis()->SetTitle("#mu^{-} p_{T} from #Upsilon(1S)");
	myMu2EtaSidebandRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu3EtaSidebandRegion = new TH1F("myMu3EtaSidebandRegion","myMu3EtaSidebandRegion",12,-3,3);
	myMu3EtaSidebandRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #mu^{+}#mu^{-}");
	myMu3EtaSidebandRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");
	TH1F * myMu4EtaSidebandRegion = new TH1F("myMu4EtaSidebandRegion","myMu4EtaSidebandRegion",12,-3,3);
	myMu4EtaSidebandRegion->GetXaxis()->SetTitle("#mu^{+} p_{T} from #mu^{+}#mu^{-}");
	myMu4EtaSidebandRegion->GetYaxis()->SetTitle("Candidates/0.5 GeV");

	TH1F * myDeltaR14 = new TH1F("myDeltaR14","myDeltaR14",1000,0,10);
	TH1F * myDeltaR23 = new TH1F("myDeltaR23","myDeltaR23",1000,0,10);

	TH1F* myfourmuonwithdeltaR14and23 = new TH1F("myfourmuonwithdeltaR14and23","myfourmuonwithdeltaR14and23",65,13.0,26.0);



	TH1F* myMu12Ctauat18dot5GeV = new TH1F("myMu12Ctauat18dot5GeV","myMu12Ctauat18dot5GeV",2000,-0.5,0.5);
	TH1F* myMu12CtauatSideband = new TH1F("myMu12CtauatSideband","myMu12CtauatSideband",2000,-0.5,0.5);
	TH1F* myMu34Ctauat18dot5GeV = new TH1F("myMu34Ctauat18dot5GeV","myMu34Ctauat18dot5GeV",2000,-0.5,0.5);
	TH1F* myMu34CtauatSideband = new TH1F("myMu34CtauatSideband","myMu34CtauatSideband",2000,-0.5,0.5);
	
	TH1F* myMu14Ctauat18dot5GeV = new TH1F("myMu14Ctauat18dot5GeV","myMu14Ctauat18dot5GeV",2000,-0.5,0.5);
	TH1F* myMu14CtauatSideband = new TH1F("myMu14CtauatSideband","myMu14CtauatSideband",2000,-0.5,0.5);
	TH1F* myMu23Ctauat18dot5GeV = new TH1F("myMu23Ctauat18dot5GeV","myMu23Ctauat18dot5GeV",2000,-0.5,0.5);
	TH1F* myMu23CtauatSideband = new TH1F("myMu23CtauatSideband","myMu23CtauatSideband",2000,-0.5,0.5);


	TH1F* myFourMuonCtauat18dot5GeV = new TH1F("myFourMuonCtauat18dot5GeV","myFourMuonCtauat18dot5GeV",2000,-0.5,0.5);
	TH1F* myFourMuonCtauatSideband = new TH1F("myFourMuonCtauatSideband","myFourMuonCtauatSideband",2000,-0.5,0.5);
	
	
	TH1F* fourmutest = new TH1F("fourmutest","fourmutest",65,13.0,26.0);
	TH1F* myMuMuMassTest = new TH1F("myMuMuMassTest","myMuMuMassTest",500,0,50);



	TH1F* myChargeCorrelatedFourMuonMass = new TH1F("myChargeCorrelatedFourMuonMass","myChargeCorrelatedFourMuonMass",65,13.0,26.0);

	TH1F* myChargeCorrelatedFourMuonMass2 = new TH1F("myChargeCorrelatedFourMuonMass2","myChargeCorrelatedFourMuonMass2",65,13.0,26.0);

	TH1F* myChargeCorrelationDeltaRCut = new TH1F("myChargeCorrelationDeltaRCut","myChargeCorrelationDeltaRCut",65,13.0,26.0);

	TH1F* mySameSignCorrelation = new TH1F("mySameSignCorrelation","mySameSignCorrelation",65,13.0,26.0);
	mySameSignCorrelation->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
	mySameSignCorrelation->GetYaxis()->SetTitle("Candidates/200 MeV");

	TH1F* myOppositeSignCorrelation = new TH1F("myOppositeSignCorrelation","myOppositeSignCorrelation",65,13.0,26.0);
	myOppositeSignCorrelation->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
	myOppositeSignCorrelation->GetYaxis()->SetTitle("Candidates/200 MeV");

	TH1F* myNoChargeCorrelation = new TH1F("myNoChargeCorrelation","myNoChargeCorrelation",65,13.0,26.0);
	myNoChargeCorrelation->GetXaxis()->SetTitle("m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
	myNoChargeCorrelation->GetYaxis()->SetTitle("Candidates/200 MeV");


	
	TH1F* myFourMuEtaforOppositeChargeCorrelation = new TH1F("myFourMuEtaforOppositeChargeCorrelation","myFourMuEtaforOppositeChargeCorrelation",60,-3,3);
	myFourMuEtaforOppositeChargeCorrelation->GetXaxis()->SetTitle("4#mu #eta");
	myFourMuEtaforOppositeChargeCorrelation->GetYaxis()->SetTitle("Candidates/0.1");

	TH1F* myFourMuEtaforSameChargeCorrelation = new TH1F("myFourMuEtaforSameChargeCorrelation","myFourMuEtaforSameChargeCorrelation",60,-3,3);
	myFourMuEtaforSameChargeCorrelation->GetXaxis()->SetTitle("4#mu #eta");
	myFourMuEtaforSameChargeCorrelation->GetYaxis()->SetTitle("Candidates/0.1");
	TH1F* myFourMuEtaforNoChargeCorrelation = new TH1F("myFourMuEtaforNoChargeCorrelation","myFourMuEtaforNoChargeCorrelation",60,-3,3);
	myFourMuEtaforNoChargeCorrelation->GetXaxis()->SetTitle("4#mu #eta");
	myFourMuEtaforNoChargeCorrelation->GetYaxis()->SetTitle("Candidates/0.1");
	
	TH1F * mytestdR12 = new TH1F("mytestdR12","mytestdR12",100,0,10);
	TH1F * mytestdR13 = new TH1F("mytestdR13","mytestdR13",100,0,10);
	TH1F * mytestdR14 = new TH1F("mytestdR14","mytestdR14",100,0,10);
	TH1F * mytestdR23 = new TH1F("mytestdR23","mytestdR23",100,0,10);
	TH1F * mytestdR24 = new TH1F("mytestdR24","mytestdR24",100,0,10);
	TH1F * mytestdR34 = new TH1F("mytestdR34","mytestdR34",100,0,10);

	TH1F * myDr14Signal = new TH1F("myDr14Signal","myDr14Signal",100,0,10);
	TH1F * myDr14Sideband = new TH1F("myDr14Sideband","myDr14Sideband",100,0,10);
	TH1F * myDr23Signal = new TH1F("myDr23Signal","myDr23Signal",100,0,10);
	TH1F * myDr23Sideband = new TH1F("myDr23Sideband","myDr23Sideband",100,0,10);

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();

	Long64_t nbytes = 0, nb = 0;
	int counter = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) 
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;




		TLorentzVector fitmu11p4,fitmu12p4,fitmu21p4,fitmu22p4;
		TVector3 wrongPair1V3, wrongPair2V3, mu11V3, mu12V3, mu21V3, mu22V3;

		fitmu11p4.SetXYZM( fitmu11px, fitmu11py, fitmu11pz, muon_mass);
		fitmu12p4.SetXYZM( fitmu12px, fitmu12py, fitmu12pz, muon_mass); 
		fitmu21p4.SetXYZM( fitmu21px, fitmu21py, fitmu21pz, muon_mass); 
		fitmu22p4.SetXYZM( fitmu22px, fitmu22py, fitmu22pz, muon_mass);
		
		// mu11V3.SetXYZ(fitmu11p4.Px(),fitmu11p4.Py(),fitmu11p4.Pz());
		// mu12V3.SetXYZ(fitmu12p4.Px(),fitmu12p4.Py(),fitmu12p4.Pz());
		// mu21V3.SetXYZ(fitmu21p4.Px(),fitmu21p4.Py(),fitmu21p4.Pz());
		// mu22V3.SetXYZ(fitmu22p4.Px(),fitmu22p4.Py(),fitmu22p4.Pz());

		bool isSignalRegion = fourmuonmass > 18.1 && fourmuonmass < 18.7;
		// bool isSidebandRegion = (fourmuonmass>17.7 && fourmuonmass<18.0) || (fourmuonmass>19.5 && fourmuonmass<19.8); // default selection
		bool isSidebandRegion = (fourmuonmass>17.7 && fourmuonmass<18.1) || (fourmuonmass>18.8 && fourmuonmass<19.2);

		float dR12,dR13,dR14,dR23,dR24,dR34;
		dR12 = fitmu11p4.DeltaR(fitmu12p4);
		dR13 = fitmu11p4.DeltaR(fitmu21p4);
		dR14 = fitmu11p4.DeltaR(fitmu22p4);
		dR23 = fitmu12p4.DeltaR(fitmu21p4);
		dR24 = fitmu12p4.DeltaR(fitmu22p4);
		dR34 = fitmu21p4.DeltaR(fitmu22p4);

		string deltaRStringArr[6] = {"dR12","dR13","dR14","dR23","dR24","dR34"};
		float deltaRFloatArr[6] = {dR12,dR13,dR14,dR23,dR24,dR34};
		for(int i = 0;i<6;i++)
		{
			for (int j = i+1; j < 6; j++)
			{
				if(deltaRFloatArr[i]>deltaRFloatArr[j])
				{
					float tmp1 = deltaRFloatArr[i];
					deltaRFloatArr[i] = deltaRFloatArr[j];
					deltaRFloatArr[j] = tmp1;

					string tmp2 = deltaRStringArr[i];
					deltaRStringArr[i] = deltaRStringArr[j];
					deltaRStringArr[j] = tmp2;

				}
			}
		}

		// cout<<"Delta R float  values: "<<deltaRFloatArr[0]<<" "<<deltaRFloatArr[1]<<" "<<deltaRFloatArr[2]<<" "<<deltaRFloatArr[3]<<" "<<deltaRFloatArr[4]<<" "<<deltaRFloatArr[5]<<endl;
		// cout<<"Delta R string values: "<<deltaRStringArr[0]<<" "<<deltaRStringArr[1]<<" "<<deltaRStringArr[2]<<" "<<deltaRStringArr[3]<<" "<<deltaRStringArr[4]<<" "<<deltaRStringArr[5]<<endl;


		myMuMuMuMumassV1mumubelowV1nolightmeson->Fill(fourmuonmass);
		myUpsilonMass->Fill((fitmu11p4 + fitmu12p4).M());
		myMuMuMass->Fill((fitmu21p4 + fitmu22p4).M());

		if((fitmu21p4+fitmu22p4).M()>8)
		{
			myDeltaR14->Fill(fitmu11p4.DeltaR(fitmu22p4));
			myDeltaR23->Fill(fitmu12p4.DeltaR(fitmu21p4));
		}

		// if( (fitmu11p4+fitmu22p4).M()<3.0 || (fitmu12p4+fitmu21p4).M()<3.0)
		// if((fitmu21p4+fitmu22p4).M()>4 && (fitmu21p4+fitmu22p4).M()<8 && fourmuonvtxprob>0.80)
		// if((fitmu21p4+fitmu22p4).M()> 8 && fourmuonvtxprob>0.80)
		if((fitmu11p4+fitmu22p4).M()<4.0 && (fitmu12p4+fitmu21p4).M()<4.0  && fourmuonvtxprob>0.80)
		// if(fourmuonvtxprob>0.80)
		{
			fourmutest->Fill(fourmuonmass);
			myMuMuMassTest->Fill((fitmu21p4+fitmu22p4).M());
		}


		if(fitmu11p4.DeltaR(fitmu22p4)>0.05 && fitmu12p4.DeltaR(fitmu21p4)>0.05) myfourmuonwithdeltaR14and23->Fill(fourmuonmass);


		if( 1
			&& fitmu11p4.DeltaR(fitmu22p4) < fitmu11p4.DeltaR(fitmu12p4)
			&& fitmu12p4.DeltaR(fitmu21p4) < fitmu21p4.DeltaR(fitmu22p4)
			) myChargeCorrelatedFourMuonMass->Fill(fourmuonmass);


			if( fitmu11p4.DeltaR(fitmu22p4) < 0.5 || fitmu12p4.DeltaR(fitmu21p4) < 0.5
				) 
				myChargeCorrelationDeltaRCut->Fill(fourmuonmass);


			if( 1
				&& fitmu11p4.DeltaR(fitmu22p4) < fitmu11p4.DeltaR(fitmu12p4)
				&& fitmu11p4.DeltaR(fitmu22p4) < fitmu21p4.DeltaR(fitmu22p4)
				&& fitmu12p4.DeltaR(fitmu21p4) < fitmu11p4.DeltaR(fitmu12p4)
				&& fitmu12p4.DeltaR(fitmu21p4) < fitmu21p4.DeltaR(fitmu22p4)
				) 
				myChargeCorrelatedFourMuonMass2->Fill(fourmuonmass);

			
			if( ("dR14" == deltaRStringArr[0] || "dR14" == deltaRStringArr[1]) && ("dR23" == deltaRStringArr[0] || "dR23" == deltaRStringArr[1]))
			{
				myOppositeSignCorrelation->Fill(fourmuonmass);
				myFourMuEtaforOppositeChargeCorrelation->Fill( (fitmu11p4+fitmu12p4+fitmu21p4+fitmu22p4).Eta()  );

			}

			else if ( ( "dR13" == deltaRStringArr[0] || "dR13" == deltaRStringArr[1]) && ("dR24" == deltaRStringArr[0] || "dR24" == deltaRStringArr[1]) )
			{
				mySameSignCorrelation->Fill(fourmuonmass);
				myFourMuEtaforSameChargeCorrelation->Fill( (fitmu11p4+fitmu12p4+fitmu21p4+fitmu22p4).Eta()  );

			}
			else
			{
				myNoChargeCorrelation->Fill(fourmuonmass);
				myFourMuEtaforNoChargeCorrelation->Fill( (fitmu11p4+fitmu12p4+fitmu21p4+fitmu22p4).Eta()  );

			}


			// }
			if(isSignalRegion)
			{
				myDr14Signal->Fill( fitmu11p4.DeltaR(fitmu22p4) );
				myDr23Signal->Fill( fitmu12p4.DeltaR(fitmu21p4) );

				myUpsilonEtaVsPtat18dot5GeV->Fill( (fitmu11p4 + fitmu12p4).Eta(), (fitmu11p4 + fitmu12p4).Pt());
				myMuMuEtaVsPtat18dot5GeV->Fill( (fitmu21p4 + fitmu22p4).Eta(), (fitmu21p4 + fitmu22p4).Pt());

				myUpsilonEtaat18dot5GeV->Fill((fitmu11p4 + fitmu12p4).Eta());
				myUpsilonPtat18dot5GeV->Fill((fitmu11p4 + fitmu12p4).Pt());

				myMuMuEtaat18dot5GeV->Fill((fitmu21p4 + fitmu22p4).Eta());
				myMuMuPtat18dot5GeV->Fill((fitmu21p4 + fitmu22p4).Pt());

				myFourMuonEtaat18dot5GeV->Fill((fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Eta());
				myFourMuonPtat18dot5GeV->Fill((fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Pt());


				myFourMuonEtaVsPtat18dot5GeV->Fill( (fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Eta(), (fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Pt()  );
				myFourMuonMomentumat18dot5GeV->Fill( (fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).P() );



				myMu1PtSignalRegion->Fill(fitmu11p4.Pt());
				myMu2PtSignalRegion->Fill(fitmu12p4.Pt());
				myMu3PtSignalRegion->Fill(fitmu21p4.Pt());
				myMu4PtSignalRegion->Fill(fitmu22p4.Pt());


				myUpsilonMassSignalRegion->Fill((fitmu11p4 + fitmu12p4).M());
				myMuMuMassSignalRegion->Fill((fitmu21p4 + fitmu22p4).M());

				myMu12Ctauat18dot5GeV->Fill(mu12ctau);
				myMu34Ctauat18dot5GeV->Fill(mu34ctau);
				myMu14Ctauat18dot5GeV->Fill(mu14ctau);
				myMu23Ctauat18dot5GeV->Fill(mu23ctau);

				myFourMuonCtauat18dot5GeV->Fill(fourmuctau);

			}
			if(isSidebandRegion)
			{

				myDr14Sideband->Fill( fitmu11p4.DeltaR(fitmu22p4) );
				myDr23Sideband->Fill( fitmu12p4.DeltaR(fitmu21p4) );




				myUpsilonEtaVsPtatSideband->Fill( (fitmu11p4 + fitmu12p4).Eta(), (fitmu11p4 + fitmu12p4).Pt());
				myMuMuEtaVsPtatSideband->Fill( (fitmu21p4 + fitmu22p4).Eta(), (fitmu21p4 + fitmu22p4).Pt());
				myFourMuonEtaVsPtatSideband->Fill( (fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Eta(), (fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Pt()  );
				myFourMuonMomentumatSideband->Fill( (fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).P() );


				myUpsilonEtaatSideband->Fill((fitmu11p4 + fitmu12p4).Eta());
				myUpsilonPtatSideband->Fill((fitmu11p4 + fitmu12p4).Pt());

				myMuMuEtaatSideband->Fill((fitmu21p4 + fitmu22p4).Eta());
				myMuMuPtatSideband->Fill((fitmu21p4 + fitmu22p4).Pt());

				myFourMuonEtaatSideband->Fill((fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Eta());
				myFourMuonPtatSideband->Fill((fitmu11p4 + fitmu12p4 + fitmu21p4 + fitmu22p4).Pt());


				myMu1PtSidebandRegion->Fill(fitmu11p4.Pt());
				myMu2PtSidebandRegion->Fill(fitmu12p4.Pt());
				myMu3PtSidebandRegion->Fill(fitmu21p4.Pt());
				myMu4PtSidebandRegion->Fill(fitmu22p4.Pt());

				myUpsilonMassSidebandRegion->Fill((fitmu11p4 + fitmu12p4).M());
				myMuMuMassSidebandRegion->Fill((fitmu21p4 + fitmu22p4).M());

				myMu12CtauatSideband->Fill(mu12ctau);
				myMu34CtauatSideband->Fill(mu34ctau);
				myMu14CtauatSideband->Fill(mu14ctau);
				myMu23CtauatSideband->Fill(mu23ctau);

				myFourMuonCtauatSideband->Fill(fourmuctau);


			}

		}









		myhbk->Write();
	}
