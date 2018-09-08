//root -l /eos/uscms/store/user/yik/Reddy/psimumurootfile/PsiMassData.root
//.L Psi2SmassFit.C
//Psi2SmassFit(mymumu2012A)
//Psi2SmassFit(mymumu2012B)
//Psi2SmassFit(mymumu2012C)
//Psi2SmassFit(mymumu2012D)
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TGraph.h"


RooDataSet* dataSet(0);
// #include "sPlotMaker.hh"
gStyle->SetOptFit(111111);
gSystem->Load("libRooFit");

using namespace RooFit;
using namespace RooStats;

void ExoticmassFittxt() 
{

	// TFile *f1 = TFile::Open("DoubleMu2011and2012withEBEonlyTripleMu5Trig.root");
	// TFile *f2 = TFile::Open("../makePlots/Combined_11and12_FourMuonVtxCL0p001.root");
	// TFile *f3 = TFile::Open("../makePlots/Combined_11and12_FourMuonVtxCL0p01.root");
	// TFile *f4 = TFile::Open("../makePlots/Combined_11and12_FourMuonVtxCL0p1.root");

	// myFourmuChg0ARCmassandanotherdimultY1sEBE->Rebin();
	
	TFile* myhbk = new TFile ("deneme.root","recreate");
	TH2F* my2DHist = new TH2F("my2DHist","my2DHist",10.0,18.0,19.0,100.0,-11360.0,-11280.0);
	TH1F* myUpsHist = new TH1F("myUpsHist","myUpsHist",5,9.0,10.0);

	double UpsMass = 9.0;
	for(int i=0;i<5;i++)
	{
		UpsMass = UpsMass + i*0.2;


		double JpsiMassmin=14.0, JpsiMassmax=25;  
		//double JpsiMassmin=17.0, JpsiMassmax=20.0;    //lowbound range
		//double JpsiMassmin=12.0, JpsiMassmax=30.0;
		//double JpsiMassmin=30.0, JpsiMassmax=41.0;   //36 GeV bump

		double mybinwidth=0.1;

		RooRealVar varMyXmass("varMyXmass", "m(#Upsilon(1S)#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);
		RooRealVar varMyXPt("varMyXPt", "Pt(X) [GeV]",0.0,100.0);
		RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_1 [GeV]",UpsMass, (UpsMass+0.2) );  //0-20
		RooRealVar varMymumu1Pt("varMymumu1Pt", "Pt(#mu^{+}#mu^{-})_1 [GeV]",0.0,100.0);
		//  RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10
		RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10

		RooRealVar varMymumu2Pt("varMymumu2Pt", "Pt(#mu^{+}#mu^{-})_2 [GeV]",0.0,100.0);

		RooRealVar varMymu11Pt("varMymu11Pt", "Pt(#mu)_11 [GeV]",2.,100.0);
		RooRealVar varMymu12Pt("varMymu12Pt", "Pt(#mu)_12 [GeV]",2.,100.0);
		RooRealVar varMymu21Pt("varMymu21Pt", "Pt(#mu)_21 [GeV]",2.,100.0);
		RooRealVar varMymu22Pt("varMymu22Pt", "Pt(#mu)_22 [GeV]",2.,100.0);
		

		/*
		float JpsiMassmin=12.0, JpsiMassmax=30;
		RooRealVar varMyXmass("varMyXmass", "m(#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);
		RooRealVar varMyXPt("varMyXPt", "Pt(X) [GeV]",0.0,100.0);
		RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_1 [GeV]",0.0,20.0);  //0-20
		RooRealVar varMymumu1Pt("varMymumu1Pt", "Pt(#mu^{+}#mu^{-})_1 [GeV]",0.0,100.0);
		RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10
		RooRealVar varMymumu2Pt("varMymumu2Pt", "Pt(#mu^{+}#mu^{-})_2 [GeV]",0.0,100.0);

		RooRealVar varMymu11Pt("varMymu11Pt", "Pt(#mu)_11 [GeV]",2.,100.0);
		RooRealVar varMymu12Pt("varMymu12Pt", "Pt(#mu)_12 [GeV]",2.,100.0);
		RooRealVar varMymu21Pt("varMymu21Pt", "Pt(#mu)_21 [GeV]",2.,100.0);
		RooRealVar varMymu22Pt("varMymu22Pt", "Pt(#mu)_22 [GeV]",2.,100.0);
		*/

		
		RooArgSet variables;
		variables.add(varMymumu1mass);
		variables.add(varMyXmass);
		/*variables.add(varMyXPt);
		variables.add(varMymumu1Pt);
		variables.add(varMymumu2mass);
		variables.add(varMymumu2Pt);
		variables.add(varMymu11Pt);
		variables.add(varMymu12Pt);
		variables.add(varMymu21Pt);
		variables.add(varMymu22Pt);
	*/

		RooArgSet* observables = new RooArgSet(varMyXmass,"observables");
		
		
	 
		//fixed shape from MC

		RooRealVar   MyMean1  ("MyMean1"    ,"MyMean1"  ,18.4532,15.0,22.0 );
		RooRealVar   MyMean2  ("MyMean2"    ,"MyMean2"  ,18.4532,15.0,22.0 );

		//free Gaus shape
		RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,18.5,18.2,18.6 );   
		RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  , 0.000,0.5 ); 
		RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, GausMean1 ,Gaussigma1 ) ;
		RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 100,  -10.0, 100000000.0); 
	 
		//  RooRealVar   Gauswidth1 ("Gauswidth1"    ,"Gauswidth1"  ,  2.56802,0.01,3.0 ); 
		//RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, MyMean1 ,Gauswidth1 ) ;
		RooRealVar BWMean1("BWMean1","BWMean1",18.4344,15.0,22.0);
		RooRealVar BWWidth1("BWWidth1","BWWidth1",0.260748,0.01,3.0);
		RooAbsPdf * pdfBW1 = new RooBreitWigner("pdfBW1","pdfBW1",varMyXmass,MyMean1,BWWidth1);
		RooRealVar BWMean2("BWMean2","BWMean2",18.5535/*,15.0,22.0*/);
		RooRealVar BWWidth2("BWWidth2","BWWidth2", 0.291299/*,0.01,3.0*/);
		RooAbsPdf * pdfBW2 = new RooBreitWigner("pdfBW2","pdfBW2",varMyXmass,MyMean1,BWWidth2);
		RooRealVar BWMean3("BWMean3","BWMean3",18.5628/*,15.0,22.0*/);
		RooRealVar BWWidth3("BWWidth3","BWWidth3",0.586284/*,0.01,3.0*/);
		RooAbsPdf * pdfBW3 = new RooBreitWigner("pdfBW3","pdfBW3",varMyXmass,BWMean3,BWWidth3);

		RooRealVar LandauSigma1("LandauSigma1","LandauSigma1",0.20,0.0,0.5);
		RooAbsPdf *pdfLandau1 = new RooLandau("pdfLandau1","pdfLandau1",varMyXmass,MyMean1,LandauSigma1);

		RooRealVar MyXfrac1("MyXfrac1","fraction of double gaussian1",0.0302285,0.0,1.0) ;
		RooRealVar MyXfrac2("MyXfrac2","fraction of double gaussian2", 0.714023,0.0,1.0);
		RooRealVar MyXfrac3("MyXfrac3","fraction of double gaussian2",1.0/*,0.0,1.0*/);

		RooRealVar CBsigma1("CBsigma1","CBsigma1",0.1586284,0.1,0.3);
		RooRealVar CBalpha1("CBalpha1","CBalpha1",2.13,1.0,10.0);
		RooRealVar CBn1("CBn1","CBn1",0.2,0.0,2.0);
		RooAbsPdf * pdfCB1 = new RooCBShape("pdfCB1","pdfCB1",varMyXmass,MyMean1,CBsigma1,CBalpha1,CBn1);
		RooRealVar CBsigma2("CBsigma2","CBsigma2",0.1586284,0.12,0.17);
		RooRealVar CBalpha2("CBalpha2","CBalpha2",2.13,2.1,2.2);
		RooRealVar CBn2("CBn2","CBn2",1.16,1.1,1.2);
		RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2","pdfCB2",varMyXmass,MyMean1,CBsigma2,CBalpha2,CBn2);
		BWWidth1.setVal( 1.99612e-01 ); 
		//MyMean1.setVal( 1.84835e+01 );
		MyXfrac1.setVal( 6.91003e-01 );
		CBalpha1.setVal( 1.90301e+00 );
		CBn1.setVal( 1.60176e+00 );
		CBsigma1.setVal( 1.51348e-01 );
		CBalpha1.setConstant(); CBn1.setConstant();CBsigma1.setConstant();  
		//MyMean1.setConstant(); 
		MyXfrac1.setConstant();  BWWidth1.setConstant();

		//  RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfLandau1),RooArgList(MyXfrac1)); 
		RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfBW1),RooArgList(MyXfrac1)); 




		//polynominal  
		//    GausEE_peak.setConstant(); 
		
		RooRealVar c1("c1", "c1",-7.37579e-02 ,  -2.0, 2.0);
		RooRealVar c2("c2", "c2",-2.68499e-01 ,  -2., 2.0);
		RooRealVar c3("c3", "c3", -5.54591e-02,  -15., 15.0);
		RooRealVar c4("c4", "c4", -5.54591e-02,  -15., 15.0);
		RooRealVar c5("c5", "c5", -5.54591e-02,  -15., 15.0);
		RooRealVar c6("c6", "c6", -5.54591e-02,  -15., 15.0);
		RooRealVar c7("c7", "c7", -5.54591e-02,  -15., 15.0);
		RooRealVar c8("c8", "c8", -5.54591e-02,  -15., 15.0);
		RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2,c3,c4));


		// RooRealVar m0("m0", "m0",1.17893e+01, -10.0, 20.0);
		// RooRealVar p1("p1", "p1",6.11878e+00, -10.0, 10.0);
		// RooRealVar p2("p2", "p2",2.52385e+00, -10.0, 10.0);
		// RooRealVar p3("p3", "p3",4.96666e-01, -10.0, 10.0);
		// RooAbsPdf * BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","p1*pow( (varMyXmass-m0),p2 )*exp(-p3*(varMyXmass-m0))",RooArgSet(varMyXmass,m0,p1,p2,p3));
	   	// m0.setConstant();
	   	// p1.setConstant();
	   	// p2.setConstant();
	   	// p3.setConstant();
	  // each muon reversed  px,py


		// RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);
		


		// fit to Combined 11 data
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-38293.3144779279537033289670944+17159.9142512196558527648448944*varMyXmass-3278.49251533258575364015996456*pow(varMyXmass,2)+348.786914259012291950057260692*pow(varMyXmass,3)-22.6149452039908460676542745205*pow(varMyXmass,4)+0.916402473643803894276516075479*pow(varMyXmass,5)-0.0227032536242202896692443658822*pow(varMyXmass,6)+0.000314974996703257725198105143605*pow(varMyXmass,7)-1.87686617916218881687033439437e-06*pow(varMyXmass,8)",RooArgSet(varMyXmass));


		// Fit to 2012 Combined data
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-36581.4728696329912054352462292+17167.0861075830871413927525282*varMyXmass-3399.23267597407129869679920375*pow(varMyXmass,2)+371.252790516125401154567953199*pow(varMyXmass,3)-24.5071203301254989526114513865*pow(varMyXmass,4)+1.00411414853278935233049651288*pow(varMyXmass,5)-0.0250146015705909018078667571672*pow(varMyXmass,6)+0.000347454372888166657887959454243*pow(varMyXmass,7)-2.06573391233682070471013719759e-06*pow(varMyXmass,8)",RooArgSet(varMyXmass));



		// Muonia 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 1 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","19909.5154609132368932478129864-7025.96288013389585103141143918*varMyXmass+1049.79390010624615570122841746*pow(varMyXmass,2)-86.9038700449025327543495222926*pow(varMyXmass,3)+4.37092092281864452729678305332*pow(varMyXmass,4)-0.137086615272722478486855379742*pow(varMyXmass,5)+0.00262272656441522736617266708947*pow(varMyXmass,6)-2.80179054029315623684272262839e-05*pow(varMyXmass,7)+1.28037145277807212641031859093e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// Muonia 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 2 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","21992.4658481148726423271000385-7304.53158062209331546910107136*varMyXmass+1000.61335187563418003264814615*pow(varMyXmass,2)-73.211524192528571575167006813*pow(varMyXmass,3)+3.08235005847367959930238612287*pow(varMyXmass,4)-0.0738079585978086705200240658087*pow(varMyXmass,5)+0.000885937499308461816685533740667*pow(varMyXmass,6)-2.72379257529252402986121202322e-06*pow(varMyXmass,7)-2.46023433012926345986895416626e-08*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// Muonia 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 3 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","47574.7664796716344426386058331-16628.0238118233137356583029032*varMyXmass+2448.83939924076685201725922525*pow(varMyXmass,2)-198.751092006647269272434641607*pow(varMyXmass,3)+9.74532864393748887721358187264*pow(varMyXmass,4)-0.296152139472315445445360637677*pow(varMyXmass,5)+0.00545236091351225266726787666016*pow(varMyXmass,6)-5.55948689736559205679632122976e-05*pow(varMyXmass,7)+2.40005224581793608702902365071e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));
		
		// Muonia 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 4 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","80743.9600065317936241626739502-29099.9952250483656825963407755*varMyXmass+4446.70490873212747828802093863*pow(varMyXmass,2)-377.133420664358254725812003016*pow(varMyXmass,3)+19.4763200062924468625169538427*pow(varMyXmass,4)-0.628947240063316370672907851258*pow(varMyXmass,5)+0.0124330709997749339068562335342*pow(varMyXmass,6)-0.000137836292177412079182699522484*pow(varMyXmass,7)+6.57220832752771843948398720198e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// Muonia 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 5 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","95518.5016386040661018341779709-34465.1557469024992315098643303*varMyXmass+5270.61281703701570222619920969*pow(varMyXmass,2)-447.187872914205456709169084206*pow(varMyXmass,3)+23.0956020020131234105065232143*pow(varMyXmass,4)-0.745653995173023775855369876808*pow(varMyXmass,5)+0.0147329914812780009281123483333*pow(varMyXmass,6)-0.000163217133099681076680714797433*pow(varMyXmass,7)+7.77519079517404183951763407823e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~`Fit With 9th order polynomial~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 1 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","15533.3159105534705304307863116-4987.89333230971624288940802217*varMyXmass+645.669463397423555761633906513*pow(varMyXmass,2)-42.2210682302909745544639008585*pow(varMyXmass,3)+1.34151013999610380089677619253*pow(varMyXmass,4)-0.00683695976473675925272344144901*pow(varMyXmass,5)-0.000910888950425496005808279065263*pow(varMyXmass,6)+2.97409433896731022347551670615e-05*pow(varMyXmass,7)-3.77811327698320129485245848222e-07*pow(varMyXmass,8)+1.72601458389812032856242151902e-09*pow(varMyXmass,9)",RooArgSet(varMyXmass));

		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 2 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","8619.9611686734260729281231761-1178.20543257841404738428536803*varMyXmass-220.205304724284474104933906347*pow(varMyXmass,2)+65.3516470765745793869427870959*pow(varMyXmass,3)-6.77972621169415656794399183127*pow(varMyXmass,4)+0.382773006077435473670789178868*pow(varMyXmass,5)-0.0128756642582360976423405674041*pow(varMyXmass,6)+0.0002579487452374040995332904469*pow(varMyXmass,7)-2.84350175443021033815723004612e-06*pow(varMyXmass,8)+1.32733561226701504343849878772e-08*pow(varMyXmass,9)",RooArgSet(varMyXmass));


		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 3 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-67362.181201549989054910838604+34887.3679719706851756200194359*varMyXmass-7620.20361172035245544975623488*pow(varMyXmass,2)+927.414894428052889452374074608*pow(varMyXmass,3)-69.6916968940170420410140650347*pow(varMyXmass,4)+3.37017942965373196173572978296*pow(varMyXmass,5)-0.105338873521735140736943492357*pow(varMyXmass,6)+0.00205972643036276799669015424854*pow(varMyXmass,7)-2.29338703536448193466210088154e-05*pow(varMyXmass,8)+1.11079669024533994753581723873e-07*pow(varMyXmass,9)",RooArgSet(varMyXmass));

		
		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 4 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-108505.553300714032957330346107+53832.8711592854451737366616726*varMyXmass-11409.6295225413978187134489417*pow(varMyXmass,2)+1358.94120350575758493505418301*pow(varMyXmass,3)-100.514785332438279397138103377*pow(varMyXmass,4)+4.80326050657108716279708460206*pow(varMyXmass,5)-0.148762492598954965128399408059*pow(varMyXmass,6)+0.00288782235400868473804147917861*pow(varMyXmass,7)-3.19659064091081261595878038051e-05*pow(varMyXmass,8)+1.54069262159070615855199098444e-07*pow(varMyXmass,9)",RooArgSet(varMyXmass));

		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 5 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-525265.479301556828431785106659+241352.243294300016714259982109*varMyXmass-48270.9873126212842180393636227*pow(varMyXmass,2)+5514.32212151463681948371231556*pow(varMyXmass,3)-396.667780744403103199147153646*pow(varMyXmass,4)+18.6493276626714177268695493694*pow(varMyXmass,5)-0.573720721927874155454674109933*pow(varMyXmass,6)+0.011150436853473378456813591697*pow(varMyXmass,7)-0.000124391054389505820425981807986*pow(varMyXmass,8)+6.07603937983140767919358702503e-07*pow(varMyXmass,9)",RooArgSet(varMyXmass));


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~`Fit With 8th order polynomial~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 1 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","16808.4291155208957206923514605-5583.15135181049754464766010642*varMyXmass+766.696454008043019712204113603*pow(varMyXmass,2)-56.289273152933667176966991974*pow(varMyXmass,3)+2.37216626726537249680859531509*pow(varMyXmass,4)-0.0562131579376248663448834008705*pow(varMyXmass,5)+0.000636951791402753627127641955497*pow(varMyXmass,6)-8.9738495600426198945905910398e-07*pow(varMyXmass,7)-3.00480278233099341700888936998e-08*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 2 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","18795.2099570725986268371343613-5897.3152158560751558979973197*varMyXmass+733.895252393992223005625419319*pow(varMyXmass,2)-45.013794043057025362486456288*pow(varMyXmass,3)+1.2713581489118799261461845162*pow(varMyXmass,4)-0.00147978270819280779795057423343*pow(varMyXmass,5)-0.000870852641198703483586818219209*pow(varMyXmass,6)+2.1051032719141878356327104993e-05*pow(varMyXmass,7)-1.62136685953880369993629914985e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));


		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 3 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","57612.8248294533259468153119087-20454.8637853734544478356838226*varMyXmass+3069.32457453805955083225853741*pow(varMyXmass,2)-254.806167166496209119941340759*pow(varMyXmass,3)+12.8408836162457262730640650261*pow(varMyXmass,4)-0.403380291067683249828235148016*pow(varMyXmass,5)+0.00773073352038740248953763156692*pow(varMyXmass,6)-8.27717621823077028160586809946e-05*pow(varMyXmass,7)+3.79450837272099691210153465243e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		
		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 4 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","82825.8435347671475028619170189-29858.7446694479986035730689764*varMyXmass+4560.72967919311395235126838088*pow(varMyXmass,2)-386.481459711979539406456751749*pow(varMyXmass,3)+19.9405827203714771655995718902*pow(varMyXmass,4)-0.64341048366927899859746275979*pow(varMyXmass,5)+0.0127110918715345987128895188789*pow(varMyXmass,6)-0.000140863867753461720344620999867*pow(varMyXmass,7)+6.71547304324451644925043219958e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// Combined 2011 and 2012 myFourmuChg0ARCmassandanotherdimultY1sEBE 5 Sigma Fit
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","110191.237916142898029647767544-39944.1038708430860424414277077*varMyXmass+6140.91742062210141739342361689*pow(varMyXmass,2)-524.252876887811680717277340591*pow(varMyXmass,3)+27.2712525231373099643406021642*pow(varMyXmass,4)-0.887785670732783249725628138549*pow(varMyXmass,5)+0.0177062017477561568778998690732*pow(varMyXmass,6)-0.000198208575891578955320559973785*pow(varMyXmass,7)+9.55079308395921070903747222836e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));



		//event-mixing curve
		//RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","11936966.598168237135-4493827.4340615812689*varMyXmass+726321.87292027298827*pow(varMyXmass,2)-66371.347260532653308*pow(varMyXmass,3)+3794.0260392078753284*pow(varMyXmass,4)-141.18749671628626174*pow(varMyXmass,5)+3.4301663700965274728*pow(varMyXmass,6)-0.052587312230767353782*pow(varMyXmass,7)+0.0004625224632395727193*pow(varMyXmass,8)-1.7810136675886924501e-06*pow(varMyXmass,9)",RooArgSet(varMyXmass));

		//bkg curve determined from signal four-muon mass directly w/ peak range included.


		// default bkg shape
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","33126.0698659494082676246762276-11959.109171291665916214697063*varMyXmass+1829.1839542918912684399401769*pow(varMyXmass,2)-155.199920521619787905365228653*pow(varMyXmass,3)+8.01568734619957012910163030028*pow(varMyXmass,4)-0.258818327081083543461659246532*pow(varMyXmass,5)+0.00511481893214218476251264888788*pow(varMyXmass,6)-5.66766466306412754878017723481e-05*pow(varMyXmass,7)+2.70047300670175391843012271606e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// each muon reversed  px,py bkg shape
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","105052.537906316400039941072464-36309.5328610628203023225069046*varMyXmass+5261.63526839357564313104376197*pow(varMyXmass,2)-418.026819632671049475902691483*pow(varMyXmass,3)+19.9613277705285376839583477704*pow(varMyXmass,4)-0.587176626430905290732198409387*pow(varMyXmass,5)+0.0103779933696005344928581237696*pow(varMyXmass,6)-0.000100350443173522144569946579207*pow(varMyXmass,7)+4.02923221346457858216917385583e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

		// my V1 and V2 reversed px, py bkg shape
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","91523.0059184624551562592387199-31848.8518394639540929347276688*varMyXmass+4673.52203471188931871438398957*pow(varMyXmass,2)-378.618855381031380602507852018*pow(varMyXmass,3)+18.5853001677707183603160956409*pow(varMyXmass,4)-0.567666254894084176818580544932*pow(varMyXmass,5)+0.0105577516707628937808749469696*pow(varMyXmass,6)-0.000109457268090301158185509433629*pow(varMyXmass,7)+4.84575344842764444024444357717e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));






		// 2011 2012 Only Upsilon Trigger with EBE
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","59613.4740602556121302768588066-21097.7072206073971756268292665*varMyXmass+3155.37604792785941754118539393*pow(varMyXmass,2)-260.958981010684794910048367456*pow(varMyXmass,3)+13.0890307587984242587708649808*pow(varMyXmass,4)-0.408724813138533649148342874469*pow(varMyXmass,5)+0.00777461860765311842808023001794*pow(varMyXmass,6)-8.24723379546567783799151940549e-05*pow(varMyXmass,7)+3.73801318888428812576733362497e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));
		// 2011 2012 Only Jpsi Trigger With EBE
		// RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","36234.0922249599825590848922729-13263.9247917399352445499971509*varMyXmass+2072.32660622212779344408772886*pow(varMyXmass,2)-180.817085238408651548525085673*pow(varMyXmass,3)+9.65840494099485269430260814261*pow(varMyXmass,4)-0.324085376260399182779536886301*pow(varMyXmass,5)+0.00668321736536352239976821465461*pow(varMyXmass,6)-7.75594868567119758492184322662e-05*pow(varMyXmass,7)+3.88324972781104464492995913261e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));


		RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);
			
		//  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXGauss1, nSigMyX);//single gausssian
		RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);//fixed shape

		RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);

		//RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
		//RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;

		//RooDataSet * alldata= &(RooDataSet::read("myfourmuonsignal.txt",RooArgSet(varMyXmass,varMymumu1mass,varMymumu1Pt,varMymumu2mass,varMymumu2Pt,varMymu11Pt,varMymu12Pt,varMymu21Pt,varMymu22Pt),"Q"));


		// RooDataSet * alldata= &(RooDataSet::read("myfourmuonsignal.txt",variables,"Q"));



		// RooDataSet * alldata= &(RooDataSet::read("hhhh.txt",variables,"Q"));
		// RooDataSet * alldata= &(RooDataSet::read("myMuOniadefault2011and2012.txt",variables,"Q"));

		// This is the default one
		RooDataSet * alldata= &(RooDataSet::read("myDimu1and4mu.txt",variables,"Q"));
		// RooDataSet * alldata= &(RooDataSet::read("a.txt",variables,"Q"));

		// RooDataHist alldata("alldata","alldata",varMyXmass, myFourmuChg0ARCmassandanotherdimultY1sEBE);
		
		//do a null hypothesis fit


		/*RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;
		myfitresult = mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));  
		double NullFitNLL = myfitresult->minNll();
		cout<<"Null hypothesis fit NLL="<<NullFitNLL<<endl;
	*/
		//do s signal fit scan
		RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
		// RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;
		
	/*	#define Nscan 200
		#define scanstp 0.005
		double scanmean[ Nscan ];
		double scanNLL[ Nscan ];
		double myMaxNLL=0;  
		double myMaxscanmean=18.0;

		for(int i=0; i<Nscan; i++) 
			{
				double mymean=18.0 +(double)i*scanstp;
				MyMean1.setVal( mymean );
				MyMean1.setConstant();
				myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));       
				scanmean[i]=mymean;
				scanNLL[i]=myfitresult.minNll();
				if( myfitresult.minNll()< myMaxNLL) {myMaxNLL=myfitresult.minNll(); myMaxscanmean=mymean;}

			}
			
		MyMean1.setVal( myMaxscanmean );MyMean1.setConstant();*/
		mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));





		// Signal Events and Bkg Events // Choose Signal with to be 150 MeV

		/*varMyXmass.setRange("selection",JpsiMassmin,JpsiMassmax);

		RooAbsReal*  pdfSigtotal=pdfMyX->createIntegral(RooArgSet(varMyXmass),"selection");
		RooAbsReal* BkgPolPdftotal=BkgPolPdf->createIntegral(RooArgSet(varMyXmass),"selection");

		double mySigma = 0.15;
		varMyXmass.setRange("selection1",18.485-3.0*mySigma, 18.485+3.0*mySigma);
		RooAbsReal*  pdfsignalregion=pdfMyX->createIntegral(RooArgSet(varMyXmass),"selection1");
		RooAbsReal* BkgPolPdfsignalregion=BkgPolPdf->createIntegral(RooArgSet(varMyXmass),"selection1");

		// double nSiginSignalRegionNormalized = pdfsignalregion.getVal();
		// double nBkginSignalRegionNormalized = BkgPolPdfsignalregion.getVal();
		// double nSig = pdfSigtotal->getVal();
		// double nBkg = BkgPolPdftotal->getVal();

		double mySigratio = pdfsignalregion.getVal()/pdfSigtotal->getVal();
		double myBkgRatio = BkgPolPdfsignalregion.getVal()/BkgPolPdftotal->getVal();

		double RatioSignalOverBkg = (mySigratio*nSigMyX.getVal())/(myBkgRatio*nBkgPol.getVal() + mySigratio*nSigMyX.getVal());

		double nSiginSignalRegion = mySigratio*nSigMyX.getVal();
		double nBkginSignalRegion = myBkgRatio*nBkgPol.getVal();
		double nSiginSignalRegionErr = mySigratio*nSigMyX.getError();
		double nBkginSignalRegionErr = myBkgRatio*nBkgPol.getError();

	*/






		gROOT->SetStyle("Plain");
		gStyle->SetStatStyle(0000);
		gStyle->SetStatFormat(0000);
		gStyle->SetOptStat(10);
		gStyle->SetStatY(0.9);
		gStyle->SetStatX(0.9);
		// gStyle->SetStatStyle(1011);
		gStyle->SetStatTextColor(2);
		gStyle->SetHistFillColor(kBlue);
		gStyle->SetOptFit(11111);

		TCanvas * c=new TCanvas("c","c",800,600);
		c->cd();
		RooPlot *frame = varMyXmass.frame( (int)((JpsiMassmax-JpsiMassmin)/mybinwidth) );   //30-12=18





		// RooHist* hpull = frame->pullHist() ;
		// if (!hpull) Error("hpull","hpull is nULL");
		// frame->addObject(hpull) ; 
		// RooPlot* frame3 = varMyXmass.frame(Title("Pull Distribution")) ;  
		// frame3->addPlotable(hpull,"P") ;  

		alldata.plotOn(frame, DataError(RooAbsData::SumW2) );
		mytotalPdf.plotOn(frame, Components(RooArgSet(*extendpdfBkgPol)),LineStyle(kDashed),LineColor(kBlue),Range(JpsiMassmin, JpsiMassmax) );
		//mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
		//mytotalPdf.paramOn(frame);
		mytotalPdf.plotOn(frame);
		
		frame->SetTitle("");  
		frame->GetXaxis()->SetTitleSize(0.05);
		frame->GetXaxis()->SetLabelSize(0.035);
		frame->GetXaxis()->SetTitleOffset(0.9);
		frame->GetYaxis()->SetTitleSize(0.05);
		frame->GetYaxis()->SetTitleOffset(1.0);
		// frame->GetYaxis()->SetTitle("Candidates/200MeV");
		frame->SetMarkerColor(1);
		frame->SetMarkerSize(2.0);
		// frame->SetMinimum(-10);
		// frame->SetMaximum(120);
		frame->Draw();
		// TLatex *t = new TLatex();
		// t->SetNDC();
		// t->SetTextAlign(22);
		// t->SetTextColor(2);
		// t->SetTextFont(22);
		// t->SetTextSizePixels(22);
		// t->SetTextSize(0.045);
		// t->DrawLatex(0.72,0.85,"HLT_TripleMu5");
		// t->DrawLatex(0.72,0.80,"2011 & 2012");
	 //  	t->DrawLatex(0.72,0.75,"DoubleMu");

		myUpsHist->Fill(nSigMyX.getVal());



		//Stupid drawlatex only accepts constant char array
		// stringstream ss1,ss2;
		// ss1 << nSiginSignalRegion;
		// ss2 << nBkginSignalRegion;
		// string str1 = ss1.str();
		// const char* cstr1 = str1.c_str();
		// string str2 = ss2.str();
		// const char* cstr2 = str2.c_str();

		// t->DrawLatex(0.72,0.70,"Sig Yield = 13#pm5");
		// t->DrawLatex(0.80,0.70, cstr1);
		// t->DrawLatex(0.72,0.65,"Bkg Yield = 272#pm17");
		// t->DrawLatex(0.80,0.65, cstr2);

		// frame->SaveAs("4Tight.gif");
		
		
		/*RooHist* hpull = frame->pullHist() ;
		if (!hpull) Error("hpull","hpull is nULL");
		hpull->SetMarkerStyle(8);
		hpull->SetMarkerSize(2.0);
		hpull->SetMarkerColor(2);
		hpull->Draw("e1");
		*/

		// for( int i=0; i<Nscan; i++) 
		// 	{
		// 		cout<<"i="<<i<<", NLL="<<scanNLL[i]<<", Mean="<<scanmean[i]<<endl;

		// 		my2DHist->Fill(scanmean[i],scanNLL[i]);

		// 		scanNLL[i]=2.0*(scanNLL[i]-myMaxNLL);
		// 	}



		// cout<<"maxscanmean="<<myMaxscanmean<<",Null hypothesis fit NLL="<<NullFitNLL<<", max NLL="<<myMaxNLL<<", 2xlog="<<2*(NullFitNLL-myMaxNLL)<<", sqrt(2l1/l0)="<<sqrt(2*(NullFitNLL-myMaxNLL))<<", p-value="<<TMath::Prob(2*(NullFitNLL-myMaxNLL),1)/2<<", take LEE as 267, p-value="<<TMath::Prob(2*(NullFitNLL-myMaxNLL),1)/2*267<<endl;
		
		// cout<<"Sig Yield = "<<nSiginSignalRegion<<"#pm"<<nSiginSignalRegionErr<<endl;
		// cout<<"Bkg Yield = "<<nBkginSignalRegion<<"#pm"<<nBkginSignalRegionErr<<endl;

		// cout<<"str1 = "<<str1<<endl;
		// const Int_t n = 200;



	/*
		TCanvas *d = new TCanvas("d","d",800,600);
		d->cd();
		// my2DHist->Draw();

		TGraph *gr = new TGraph(200,scanmean,scanNLL);
		gr->SetMinimum(-1);
		gr->SetTitle("");
		gr->GetXaxis()->SetTitle("mass [GeV]");
		gr->GetYaxis()->SetTitle("2*(#Delta NLL)");
		gr->GetXaxis()->SetTitleSize(0.06);
		gr->GetYaxis()->SetTitleSize(0.06);
		gr->GetXaxis()->SetTitleOffset(0.8);
		gr->GetYaxis()->SetTitleOffset(0.8);


		gr->SetMarkerColor(4);
		gr->SetMarkerStyle(1);
		gr->Draw("ALP");

		TLine *line = new TLine(17.9,myMaxNLL,19,myMaxNLL);
		line->SetLineColor(kRed);
		line->Draw();

		TLine *line1 = new TLine(17.9,(myMaxNLL+1),19,(myMaxNLL+1));
		line1->SetLineColor(kRed);
		line1->Draw();

		TLine *l1=new TLine(17.9,1,19.1,1);
		l1->SetLineColor(2);
		l1->Draw();
		TLine *l2=new TLine(18.45063,-1,18.45063,1);
		l2->SetLineColor(4);
		l2->Draw();
		TLine *l3=new TLine(18.51805,-1,18.51805,1);
		l3->SetLineColor(4);
		l3->Draw();
	 
	*/

	}
	myUpsHist->Write();
	
	return;

	/*
	GausMean1.setConstant();

	RooFitResult *   myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE),Save()); 

	TFile * myhbk= new TFile("myhbksPlot.root","recreate");

	sPlotMaker mysplottest(alldata,myfitresult, RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(), RooArgList(nSigMyX,nBkgPol), RooArgList());
	//sPlotMaker mysplottest(alldata,myfitresult, RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(), RooArgList(nBkgPol, nSigMyX), RooArgList());

	TH1F * myMuMu1MassSig=mysplottest.makeShist(&varMymumu1mass,&nSigMyX,100);
	myMuMu1MassSig->SetName("myMuMu1MassSig");
	myMuMu1MassSig->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}1}  GeV");
	myMuMu1MassSig->Write();

	TH1F * myMuMu1MassBkg=mysplottest.makeShist(&varMymumu1mass,&nBkgPol,100);
	myMuMu1MassBkg->SetName("myMuMu1MassBkg");
	myMuMu1MassBkg->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}1}  GeV");
	myMuMu1MassBkg->Write();

	TH1F * myMuMu2MassSig=mysplottest.makeShist(&varMymumu2mass,&nSigMyX,500);
	myMuMu2MassSig->SetName("myMuMu2MassSig");
	myMuMu2MassSig->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}2}  GeV");
	myMuMu2MassSig->Write();

	TH1F * myMuMu2MassBkg=mysplottest.makeShist(&varMymumu2mass,&nBkgPol,500);
	myMuMu2MassBkg->SetName("myMuMu2MassBkg");
	myMuMu2MassBkg->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}2}  GeV");
	myMuMu2MassBkg->Write();

	//  return;
	
	// use a RooWorkspace to store the pdf models, prior informations, list of parameters,...
	 RooWorkspace myWS("myWS");
	 myWS.import(alldata,Rename("roohist_data_mass_cat0"));
	 myWS.import(mytotalPdf,RecycleConflictNodes()),
	 //myWS.import(mytotalPdf,RecycleConflictNodes(),RenameVariable("nSigEta","pdfEta_norm"),RenameVariable("nBck","BkgPdf_norm"));
	 myWS.import(*BkgPolPdf,RecycleConflictNodes());
	 myWS.import(*pdfMyXGauss1,RecycleConflictNodes());
//   myWS.import(nSigEta,RenameVariable("pdfEta_norm"));
//   myWS.import(nBck,RenameVariable("BkgPdf_norm"));
//   myWS.import(*priorPOI,RecycleConflictNodes());
//   myWS.import(*priorNuisance,RecycleConflictNodes());  
	 myWS.defineSet("observables",*observables,kTRUE);
//   myWS.defineSet("parameters",*parameters,kTRUE);
//   myWS.defineSet("POI",*POI,kTRUE);  

	 // store the workspace in a ROOT file  
	 TFile file("myEtaPDFValues.root","RECREATE");
	 file.cd();
	 myWS.Write();
	 file.Write();
	 file.Close();
	*/




}  


