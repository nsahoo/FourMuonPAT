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

void ExoticmassFitScan() 
{

  TH2F* my2DHist = new TH2F("my2DHist","my2DHist",10.0,18.0,19.0,100.0,-11360.0,-11280.0);

  // double JpsiMassmin=14.0, JpsiMassmax=50;
  double JpsiMassmin=12.0, JpsiMassmax=35;  
  //double JpsiMassmin=14.0, JpsiMassmax=50.0;    //decided by F-test
  //double JpsiMassmin=12.0, JpsiMassmax=30.0;
  //double JpsiMassmin=30.0, JpsiMassmax=41.0;   //36 GeV bump

  double mybinwidth=0.2;

  RooRealVar varMyXmass("varMyXmass", "m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);
  RooRealVar varMyXmassErr("varMyXmassErr", "masserr(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",0.0, 0.5);
  RooRealVar varMyXPt("varMyXPt", "Pt(X) [GeV]",0.0,100.0);
  RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_1 [GeV]",0.0,20.0);  //0-20
  RooRealVar varMymumu1Pt("varMymumu1Pt", "Pt(#mu^{+}#mu^{-})_1 [GeV]",0.0,100.0);
  //  RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10
  RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10
  RooRealVar varMymumu2Pt("varMymumu2Pt", "Pt(#mu^{+}#mu^{-})_2 [GeV]",0.0,100.0);
  RooRealVar varMymu11Pt("varMymu11Pt", "Pt(#mu)_11 [GeV]",2.,100.0);
  RooRealVar varMymu12Pt("varMymu12Pt", "Pt(#mu)_12 [GeV]",2.,100.0);
  RooRealVar varMymu21Pt("varMymu21Pt", "Pt(#mu)_21 [GeV]",2.,100.0);
  RooRealVar varMymu22Pt("varMymu22Pt", "Pt(#mu)_22 [GeV]",2.,100.0);
  
  RooArgSet variables;
  variables.add(varMyXmass);
  variables.add(varMyXmassErr);
  variables.add(varMyXPt);
  variables.add(varMymumu1mass);
  variables.add(varMymumu1Pt);
  variables.add(varMymumu2mass);
  variables.add(varMymumu2Pt);
  variables.add(varMymu11Pt);
  variables.add(varMymu12Pt);
  variables.add(varMymu21Pt);
  variables.add(varMymu22Pt);
  

  RooArgSet* observables = new RooArgSet(varMyXmass,"observables");
   
  //fixed shape from MC

  RooRealVar   MyMean1  ("MyMean1"    ,"MyMean1"  ,18.4532,15.0,22.0 );
  RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 100,  -10.0, 100000000.0); 

  /*
  RooRealVar   MyMean2  ("MyMean2"    ,"MyMean2"  ,18.4532,15.0,22.0 );
  //free Gaus shape
  RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,18.5,18.2,18.6 );   
  RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  , 0.150, 0.01,0.5 ); 
  RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, GausMean1 ,Gaussigma1 ) ;
  
  //free Breit-Wigner shape
  RooRealVar   GausMean1  ("GausMean1"    ,"GausMean1"  ,18.485,18.2,18.6 );   
  RooRealVar   Gaussigma1 ("Gaussigma1"    ,"Gaussigma1"  , 0.000,0.5 ); 
  RooAbsPdf* pdfMyXBreitWigner1 = new 	RooBreitWigner( "pdfMyXBreitWigner1", "pdfMyXBreitWigner1",  varMyXmass, GausMean1 ,Gaussigma1 ) ;
  //  RooRealVar   Gauswidth1 ("Gauswidth1"    ,"Gauswidth1"  ,  2.56802,0.01,3.0 ); 
  //RooAbsPdf* pdfMyXGauss1 = new RooGaussian( "pdfMyXGauss1", "pdfMyXGauss1",  varMyXmass, MyMean1 ,Gauswidth1 ) ;
  RooRealVar BWMean1("BWMean1","BWMean1",18.4344,15.0,22.0);
  RooRealVar BWWidth1("BWWidth1","BWWidth1",0.260748,0.01,3.0);
  RooAbsPdf * pdfBW1 = new RooBreitWigner("pdfBW1","pdfBW1",varMyXmass,MyMean1,BWWidth1);
  RooRealVar BWMean2("BWMean2","BWMean2",18.5535);
  RooRealVar BWWidth2("BWWidth2","BWWidth2", 0.291299);
  RooAbsPdf * pdfBW2 = new RooBreitWigner("pdfBW2","pdfBW2",varMyXmass,MyMean1,BWWidth2);
  RooRealVar BWMean3("BWMean3","BWMean3",18.5628);
  RooRealVar BWWidth3("BWWidth3","BWWidth3",0.586284);
  RooAbsPdf * pdfBW3 = new RooBreitWigner("pdfBW3","pdfBW3",varMyXmass,BWMean3,BWWidth3);

  RooRealVar LandauSigma1("LandauSigma1","LandauSigma1",0.20,0.0,0.5);
  RooAbsPdf *pdfLandau1 = new RooLandau("pdfLandau1","pdfLandau1",varMyXmass,MyMean1,LandauSigma1);
*/


  RooRealVar MyXfrac1("MyXfrac1","fraction of double gaussian1",0.0302285,0.0,1.0) ;

  RooRealVar CBsigma1("CBsigma1","CBsigma1",0.1586284,0.1,0.3);
  RooRealVar CBalpha1("CBalpha1","CBalpha1",2.13,1.0,10.0);
  RooRealVar CBn1("CBn1","CBn1",0.2,0.0,2.0);
  RooAbsPdf * pdfCB1 = new RooCBShape("pdfCB1","pdfCB1",varMyXmass,MyMean1,CBsigma1,CBalpha1,CBn1);
  RooRealVar CBsigma2("CBsigma2","CBsigma2",0.1586284,0.12,0.17);
  RooRealVar CBalpha2("CBalpha2","CBalpha2",2.13,2.1,2.2);
  RooRealVar CBn2("CBn2","CBn2",1.16,1.1,1.2);
  RooAbsPdf * pdfCB2 = new RooCBShape("pdfCB2","pdfCB2",varMyXmass,MyMean1,CBsigma2,CBalpha2,CBn2);

/*
// Signal Shape from the whole official MC, local sig = 6.0
  MyMean1.setVal( 1.84961e+01 );
  MyXfrac1.setVal( 3.28712e-01 );
  CBalpha1.setVal(5.89859e-01);
  CBn1.setVal( 2.46688e+00 );
  CBsigma1.setVal( 7.86036e-02 );
  CBalpha2.setVal(-1.99301e+00);
  CBn2.setVal( 2.00822e+00 );
  CBsigma2.setVal( 1.66101e-01 );
*/

 // Default
  MyMean1.setVal( 1.85007e+01 );
  MyXfrac1.setVal( 3.49987e-01 );
  CBalpha1.setVal(5.76320e-01);
  CBn1.setVal( 2.52857e+00 );
  CBsigma1.setVal( 7.34724e-02 );
  CBalpha2.setVal(-2.03863e+00);
  CBn2.setVal( 1.85372e+00 );
  CBsigma2.setVal( 1.60791e-01 );


  MyXfrac1.setConstant();
  MyMean1.setConstant();
  CBalpha1.setConstant();
  CBn1.setConstant();
  CBsigma1.setConstant();
  CBalpha2.setConstant();
  CBn2.setConstant();
  CBsigma2.setConstant();


  //  RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfLandau1),RooArgList(MyXfrac1)); 
  RooAbsPdf* pdfMyX = new RooAddPdf("pdfMyX","pdfMyX",RooArgList(*pdfCB1,*pdfCB2),RooArgList(MyXfrac1)); 


  //polynominal  
  //    GausEE_peak.setConstant(); 
  
  RooRealVar c1("c1", "c1", -3.52568e-01,  -2.0, 2.0);
  RooRealVar c2("c2", "c2", -7.43151e-01,  -2., 2.0);
  RooRealVar c3("c3", "c3", 6.67192e-01,  -15., 15.0);
  RooRealVar c4("c4", "c4", -1.27946e-01,  -15., 15.0);
  RooRealVar c5("c5", "c5", -2.15607e-01,  -15., 15.0);
  RooRealVar c6("c6", "c6", 1.65804e-01,  -15., 15.0);
  RooRealVar c7("c7", "c7", -5.54591e-02,  -15., 15.0);
  RooRealVar c8("c8", "c8", -5.54591e-02,  -15., 15.0);

  // RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2,c3,c4,c5,c6,c7,c8));
  // RooAbsPdf *  BkgPolPdf = new RooBernstein("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2,c3));
  RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);
  
  //c1->setConstant(); c2->setConstant(); c3->setConstant();  c4->setConstant(); c5->setConstant(); c6->setConstant(); 
  
  // RooRealVar m0("m0", "m0",1.17893e+01, -10.0, 20.0);
  // RooRealVar p1("p1", "p1",6.11878e+00, -10.0, 10.0);
  // RooRealVar p2("p2", "p2",2.52385e+00, -10.0, 10.0);
  // RooRealVar p3("p3", "p3",4.96666e-01, -10.0, 10.0);
  // RooAbsPdf * BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","p1*pow( (varMyXmass-m0),p2 )*exp(-p3*(varMyXmass-m0))",RooArgSet(varMyXmass,m0,p1,p2,p3));
    // m0.setConstant();
    // p1.setConstant();
    // p2.setConstant();
    // p3.setConstant();




  

  //decided by F-test
  //RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-7991.50657388753097620792686939+1893.07016200460088839463423938*varMyXmass-183.502862678134391671846969984*pow(varMyXmass,2)+9.5637857237468733018204147811*pow(varMyXmass,3)-0.291427643046618278788173483917*pow(varMyXmass,4)+0.005213768095073623154434017124*pow(varMyXmass,5)-5.08485406030409416329451932626e-05*pow(varMyXmass,6)+2.08964397872896200087202214779e-07*pow(varMyXmass,7)",RooArgSet(varMyXmass));

     // decided by 14-50 8th order poly 4016evts
   // RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-16714.4937101397736114449799061+4311.0720920080102587235160172*varMyXmass-468.478153920417355493555078283*pow(varMyXmass,2)+28.2522013728231122797751595499*pow(varMyXmass,3)-1.03875540251508957645398822933*pow(varMyXmass,4)+0.0239087266103714876641639364152*pow(varMyXmass,5)-0.000337045613627642739844325614484*pow(varMyXmass,6)+2.66431133280929559198628615857e-06*pow(varMyXmass,7)-9.05159339903484236808689120894e-09*pow(varMyXmass,8)",RooArgSet(varMyXmass));

    // decided by removing the signal region and fit 14-18 and 19.4 to 50 GeV to pol4
    RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","6795326.6806241339072585105896-2448697.96897635748609900474548*varMyXmass+373806.65283488598652184009552*pow(varMyXmass,2)-31678.855326906432310352101922*pow(varMyXmass,3)+1636.9209978369494820071849972*pow(varMyXmass,4)-52.9986441034045299147692276165*pow(varMyXmass,5)+1.05297735320690488691752761952*pow(varMyXmass,6)-0.0117641928185401208051263921561*pow(varMyXmass,7)+5.66904741946814471004537083765e-05*pow(varMyXmass,8)",RooArgSet(varMyXmass));



      // decided by 13-50 7th order poly 4016evts
   // RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-8029.72556910640741989482194185+1902.4751348672136828099610284*varMyXmass-184.458579738994046692823758349*pow(varMyXmass,2)+9.61615353805623307437144831056*pow(varMyXmass,3)-0.293101221959658320148633947611*pow(varMyXmass,4)+0.005244993616785415153913607611*pow(varMyXmass,5)-5.11639490550146143000090348529e-05*pow(varMyXmass,6)+2.10297441183958885472593883237e-07*pow(varMyXmass,7)",RooArgSet(varMyXmass));

  // decided by 12-35 7th order
  // RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","27474.7248644783903728239238262-9175.11990013552713207900524139*varMyXmass+1265.12681233746570796938613057*pow(varMyXmass,2)-93.6036137778848456036939751357*pow(varMyXmass,3)+4.03119528055012299461168367998*pow(varMyXmass,4)-0.101475314637659352889897945715*pow(varMyXmass,5)+0.0013873013556274244994365174577*pow(varMyXmass,6)-7.96923820331946827918382508793e-06*pow(varMyXmass,7)",RooArgSet(varMyXmass));



   // Reverse V1 V2 Px Py from 14-35 GeV
   // RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","237194.472234576038317754864693-83184.5682315043668495491147041*varMyXmass+12472.3579684840005938895046711*pow(varMyXmass,2)-1046.06323853466165019199252129*pow(varMyXmass,3)+53.7978299350397293210335192271*pow(varMyXmass,4)-1.74091207373653289458559356717*pow(varMyXmass,5)+0.0346798137728134905910515328742*pow(varMyXmass,6)-0.000389410123414547597580498417003*pow(varMyXmass,7)+1.88947722384121715352689983847e-06*pow(varMyXmass,8)",RooArgSet(varMyXmass));


   // Bkg Shape from Evt Mixing 12-35 GeV
   // RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","9643899.38197361677885055541992-3430248.87651908118277788162231*varMyXmass+515913.319884699245449155569077*pow(varMyXmass,2)-42985.4679465790104586631059647*pow(varMyXmass,3)+2178.87391917647983063943684101*pow(varMyXmass,4)-69.0459599047464962495723739266*pow(varMyXmass,5)+1.33961895663048302651532139862*pow(varMyXmass,6)-0.0145826870407996193185207189913*pow(varMyXmass,7)+6.8316265409391134749532425996e-05*pow(varMyXmass,8)",RooArgSet(varMyXmass));


  RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);

      //RooBreit-Wigner
  //  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXBreitWigner1, nSigMyX);
  //single gausssian
  //RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXGauss1, nSigMyX);
  //fixed shape from MC
  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);


  RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);

  RooDataSet * alldata= &(RooDataSet::read("myfourmuonsignalNolm.txt",variables,"Q"));
  // RooDataSet * alldata= &(RooDataSet::read("unique.txt",variables,"Q"));

  //RooDataSet * alldata= &(RooDataSet::read("combinedefault.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combine2012default.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combine2011default.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combineMuOniadefault.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combineDoubleMudefault.txt",variables,"Q"));

  // RooDataSet * alldata= &(RooDataSet::read("2012MuOniasignalstartfromlowmasscombination.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("2012DoubleMuMuOniasignalstartfromlowmasscombination.txt",variables,"Q"));


  //RooDataSet * alldata= &(RooDataSet::read("ToGiovanni2012combinedusingsigmaY.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combine2012default.txt",variables,"Q"));

  //RooDataSet * alldata= &(RooDataSet::read("haha.txt",variables,"Q"));

  //RooDataSet * alldata= &(RooDataSet::read("sharedourMass.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("sharedGioMass.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("notsharedourMass.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combined2011and2012oldsoftwithTMonestationTight.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combined2012oldsoftwithTMonestationTight.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combined2011oldsoftwithTMonestationTight.txt",variables,"Q"));

  //RooDataSet * alldata= &(RooDataSet::read("combined2011and2012newsoftmuonid.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combined2011and2012newsoftmuonidoroldsoftwithTMOneStationLoose.txt",variables,"Q"));
  //RooDataSet * alldata= &(RooDataSet::read("combined2011and2012newsoftmuonidandoldsoftwithTMOneStationTight.txt",variables,"Q"));

//return;

    //RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;

  //do a null hypothesis fit
  RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;
  myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));  
  double NullFitNLL=myfitresult.minNll();
  cout<<"Null hypothesis fit NLL="<<NullFitNLL<<endl;

  /*
 TCanvas * c=new TCanvas("c","c",800,600);
  c->cd();
  RooPlot *frame = varMyXmass.frame( (int)((JpsiMassmax-JpsiMassmin)/mybinwidth) );   //30-12=18
  // RooHist* hpull = frame->pullHist() ;
  // if (!hpull) Error("hpull","hpull is nULL");
//frame->addObject(hpull) ; 
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
//  frame->GetYaxis()->SetTitle("pull");
  frame->GetYaxis()->SetTitleSize(0.05);
  frame->GetYaxis()->SetTitleOffset(1.25);
  frame->SetMarkerColor(1);
  frame->SetMarkerSize(2.0);
  frame->SetMinimum(-10);
  //frame->SetMaximum(75);
  frame->Draw();
  */

  //return;


  //do s signal fit scan
  RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
  
#define Nscan 200
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
    
  MyMean1.setVal( myMaxscanmean );MyMean1.setConstant();
  mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));

  gROOT->SetStyle("Plain");  
  TCanvas * c=new TCanvas("c","c",800,600);
  c->cd();
  RooPlot *frame = varMyXmass.frame( (int)((JpsiMassmax-JpsiMassmin)/mybinwidth) );   //30-12=18


  // RooHist* hpull = frame->pullHist() ;
  // if (!hpull) Error("hpull","hpull is nULL");
//frame->addObject(hpull) ; 
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
//  frame->GetYaxis()->SetTitle("pull");
  frame->GetYaxis()->SetTitleSize(0.05);
  frame->GetYaxis()->SetTitleOffset(0.9);
  frame->SetMarkerColor(1);
  frame->SetMarkerSize(2.0);
  frame->SetMinimum(-10);
  //frame->SetMaximum(75);
  frame->Draw();
  
  
  RooHist* hpull = frame->pullHist() ;
  if (!hpull) Error("hpull","hpull is nULL");
  hpull->SetMarkerStyle(8);
  hpull->SetMarkerSize(2.0);
  hpull->SetMarkerColor(2);
  hpull->Draw("e1");
  

  for( int i=0; i<Nscan; i++) 
    {
      cout<<"i="<<i<<", NLL="<<scanNLL[i]<<", Mean="<<scanmean[i]<<endl;

      my2DHist->Fill(scanmean[i],scanNLL[i]);

      scanNLL[i]=2.0*(scanNLL[i]-myMaxNLL);
    }

  cout<<"maxscanmean="<<myMaxscanmean<<",Null hypothesis fit NLL="<<NullFitNLL<<", max NLL="<<myMaxNLL<<", 2xlog="<<2*(NullFitNLL-myMaxNLL)<<", sqrt(2l1/l0)="<<sqrt(2*(NullFitNLL-myMaxNLL))<<", p-value="<<TMath::Prob(2*(NullFitNLL-myMaxNLL),1)/2<<", take LEE as 267, p-value="<<TMath::Prob(2*(NullFitNLL-myMaxNLL),1)/2*267<<endl;
  
  const Int_t n = 200;
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
  gr->GetYaxis()->SetTitleOffset(0.9);


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
  TLine *l2=new TLine(18.429,-1,18.429,1);
  l2->SetLineColor(4);
  l2->Draw();
  TLine *l3=new TLine(18.4996,-1,18.4996,1);
  l3->SetLineColor(4);
  l3->Draw();
 
 //gr->SaveAs("NLL.pdf");
 //gr->SaveAs("NLL.eps");
 //d->Update();


  return;






}  


