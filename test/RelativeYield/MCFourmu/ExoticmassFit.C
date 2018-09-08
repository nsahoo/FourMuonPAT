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

void ExoticmassFit() 
{

  TH2F* my2DHist = new TH2F("my2DHist","my2DHist",10.0,18.0,19.0,100.0,-11360.0,-11280.0);

  double JpsiMassmin=14.0, JpsiMassmax=26.0;
  // double JpsiMassmin=14.0, JpsiMassmax=25;
  // double JpsiMassmin=14.0, JpsiMassmax=26.0;
  // double JpsiMassmin=17.0, JpsiMassmax=20.0;    //lowbound range
  //double JpsiMassmin=12.0, JpsiMassmax=30.0;
  //double JpsiMassmin=30.0, JpsiMassmax=41.0;   //36 GeV bump

  double mybinwidth=0.2;

  RooRealVar varMyXmass("varMyXmass", "m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);
  RooRealVar varMyXmassErr("varMyXmassErr", "masserr(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",0.0, 0.5);
  RooRealVar varMyXPt("varMyXPt", "Pt(X) [GeV]",0.0,100.0);
  RooRealVar varMymumu1mass("varMymumu1mass", "m(#mu^{+}#mu^{-})_1 [GeV]",0.0,50.0);  //0-20
  RooRealVar varMymumu1Pt("varMymumu1Pt", "Pt(#mu^{+}#mu^{-})_1 [GeV]",0.0,100.0);
  //  RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,10.0); //0-10
  RooRealVar varMymumu2mass("varMymumu2mass", "m(#mu^{+}#mu^{-})_2 [GeV]",0.0,20.0); //0-10
  RooRealVar varMymumu2Pt("varMymumu2Pt", "Pt(#mu^{+}#mu^{-})_2 [GeV]",0.0,100.0);
  RooRealVar varMymu11Pt("varMymu11Pt", "Pt(#mu)_11 [GeV]",2.0,100.0);
  RooRealVar varMymu12Pt("varMymu12Pt", "Pt(#mu)_12 [GeV]",2.0,100.0);
  RooRealVar varMymu21Pt("varMymu21Pt", "Pt(#mu)_21 [GeV]",2.0,100.0);
  RooRealVar varMymu22Pt("varMymu22Pt", "Pt(#mu)_22 [GeV]",2.0,100.0);
  
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
  
  RooRealVar c1("c1", "c1",-7.37579e-02 ,  -2.0, 2.0);
  RooRealVar c2("c2", "c2",-2.68499e-01 ,  -2., 2.0);
  RooRealVar c3("c3", "c3", -5.54591e-02,  -15., 15.0);
  RooRealVar c4("c4", "c4", -5.54591e-02,  -15., 15.0);
  RooRealVar c5("c5", "c5", -5.54591e-02,  -15., 15.0);
  RooRealVar c6("c6", "c6", -5.54591e-02,  -15., 15.0);
  RooRealVar c7("c7", "c7", -5.54591e-02,  -15., 15.0);
  RooRealVar c8("c8", "c8", -5.54591e-02,  -15., 15.0);
  RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2,c3,c4));

  RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);
  
  RooRealVar b1("b1", "b1",  0.0, 1500000.0);
  RooRealVar b2("b2", "b2", 0.0, 1500000.0);
  RooRealVar b3("b3", "b3", 0.0 , 1500000.0);
  RooRealVar b4("b4", "b4",  0.0, 1500000.0);
  RooRealVar b5("b5", "b5", 0.0, 1500000.0);
  RooRealVar b6("b6", "b6", 0.0 , 1500000.0);
  RooRealVar b7("b7", "b7", 0.0 , 1500000.0);
  RooRealVar b8("b8", "b8", 0.0 , 1500000.0);
  // RooAbsPdf *  BkgPolPdf = new RooBernstein("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(b1,b2,b3,b4,b5,b6,b7,b8));

  //event-mixing curve
  //RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","11936966.598168237135-4493827.4340615812689*varMyXmass+726321.87292027298827*pow(varMyXmass,2)-66371.347260532653308*pow(varMyXmass,3)+3794.0260392078753284*pow(varMyXmass,4)-141.18749671628626174*pow(varMyXmass,5)+3.4301663700965274728*pow(varMyXmass,6)-0.052587312230767353782*pow(varMyXmass,7)+0.0004625224632395727193*pow(varMyXmass,8)-1.7810136675886924501e-06*pow(varMyXmass,9)",RooArgSet(varMyXmass));

  // each muon reversed  px,py bkg shape
  //RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","105052.537906316400039941072464-36309.5328610628203023225069046*varMyXmass+5261.63526839357564313104376197*pow(varMyXmass,2)-418.026819632671049475902691483*pow(varMyXmass,3)+19.9613277705285376839583477704*pow(varMyXmass,4)-0.587176626430905290732198409387*pow(varMyXmass,5)+0.0103779933696005344928581237696*pow(varMyXmass,6)-0.000100350443173522144569946579207*pow(varMyXmass,7)+4.02923221346457858216917385583e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

  // my V1 and V2 reversed px, py bkg shape
  //RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","91523.0059184624551562592387199-31848.8518394639540929347276688*varMyXmass+4673.52203471188931871438398957*pow(varMyXmass,2)-378.618855381031380602507852018*pow(varMyXmass,3)+18.5853001677707183603160956409*pow(varMyXmass,4)-0.567666254894084176818580544932*pow(varMyXmass,5)+0.0105577516707628937808749469696*pow(varMyXmass,6)-0.000109457268090301158185509433629*pow(varMyXmass,7)+4.84575344842764444024444357717e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));

  //default
  //bkg curve determined from signal four-muon mass directly w/ peak range included.
  // RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","70872.6131453393900301307439804-25733.6576625114976195618510246*varMyXmass+3965.80726536954807670554146171*pow(varMyXmass,2)-339.81086792951521147188032046*pow(varMyXmass,3)+17.773631372767599856388187618*pow(varMyXmass,4)-0.583079689037217963054615665897*pow(varMyXmass,5)+0.0117497997044741162020464742*pow(varMyXmass,6)-0.000133284533406250789043176463444*pow(varMyXmass,7)+6.52858001703553969023653864856e-07*pow(varMyXmass,8)",RooArgSet(varMyXmass));



  // BKG Variations

 /*RooRealVar m0("m0", "m0",1.18400e+01, -20.0, 20.0);
  RooRealVar p1("p1", "p1",2.00000e+00, -20.0, 20.0);
  RooRealVar p2("p2", "p2",1.32668e+00,-20.0, 100.0);
  RooRealVar p3("p3", "p3",1.01594e+00, -20.0, 20.0);
  RooRealVar p4("p4", "p4",-1.31418e+00 ,-50.0,50.0);
  RooRealVar p5("p5", "p5",2.97485e-00, -50.0, 50.0);
  
  // RooAbsPdf * BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","p1*pow( (varMyXmass-m0),p2 )*exp(-p3*(varMyXmass-m0))",RooArgSet(varMyXmass,m0,p1,p2,p3));
  // RooAbsPdf * BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","p1*pow( (varMyXmass-m0),p2 ) * exp(-p3*(varMyXmass-m0) + p4*pow( (varMyXmass-m0),p5 ) )",RooArgSet(varMyXmass,m0,p1,p2,p3,p4,p5));
  // RooAbsPdf * BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","p1*pow( (varMyXmass-m0),p2 ) * exp(-p3*(varMyXmass-m0) + p4*pow( (varMyXmass-m0),p5 ) )",RooArgSet(varMyXmass,m0,p1,p2,p3,p4,p5));
  RooAbsPdf * BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","pow( (m0-varMyXmass),p1 )/pow(varMyXmass,p2+p3*TMath::Log(varMyXmass))",RooArgSet(varMyXmass,m0,p1,p2,p3));
*/
  // RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);

      //RooBreit-Wigner
  //  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXBreitWigner1, nSigMyX);
  //single gausssian
  //RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXGauss1, nSigMyX);
  //fixed shape from MC
  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX, nSigMyX);


  RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);

  RooDataSet * alldata= &(RooDataSet::read("../myfourmuonsignal.txt",variables,"Q"));
  // RooDataSet * alldata= &(RooDataSet::read("../myfourmuonsignalYieldChange.txt",variables,"Q"));
  // RooDataSet * alldata= &(RooDataSet::read("a.txt",variables,"Q"));



  //do a null hypothesis fit
  // RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;
  // myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));  
  // double NullFitNLL=myfitresult.minNll();
  // cout<<"Null hypothesis fit NLL="<<NullFitNLL<<endl;

  //do s signal fit scan
  RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
  
  // #define Nscan 200
  // #define scanstp 0.005
  // double scanmean[ Nscan ];
  // double scanNLL[ Nscan ];
  // double myMaxNLL=0;  
  // double myMaxscanmean=18.0;

  // for(int i=0; i<Nscan; i++) 
  //   {
  //     double mymean=18.0 +(double)i*scanstp;
  //     MyMean1.setVal( mymean );
  //     MyMean1.setConstant();
  //     myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));       
  //     scanmean[i]=mymean;
  //     scanNLL[i]=myfitresult.minNll();
  //     if( myfitresult.minNll()< myMaxNLL) {myMaxNLL=myfitresult.minNll(); myMaxscanmean=mymean;}

  //   }
    
  // MyMean1.setVal( myMaxscanmean );MyMean1.setConstant();
  mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));

  gROOT->SetStyle("Plain");  
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
  mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
  //mytotalPdf.paramOn(frame);
  mytotalPdf.plotOn(frame);
  
  frame->SetTitle("");  
  frame->GetXaxis()->SetTitleSize(0.05);
  frame->GetXaxis()->SetLabelSize(0.035);
  frame->GetXaxis()->SetTitleOffset(0.9);
  // frame->GetYaxis()->SetTitle("pull");
  frame->GetYaxis()->SetTitleSize(0.05);
  frame->GetYaxis()->SetTitleOffset(0.9);
  frame->SetMarkerColor(1);
  frame->SetMarkerSize(2.0);
  frame->SetMinimum(-10);
  // frame->SetMaximum(75);
  frame->Draw();
  
  
  RooHist* hpull = frame->pullHist() ;
  if (!hpull) Error("hpull","hpull is nULL");
  hpull->SetMarkerStyle(8);
  hpull->SetMarkerSize(2.0);
  hpull->SetMarkerColor(2);
  hpull->Draw("e1");
  

  /*for( int i=0; i<Nscan; i++) 
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
  gr->GetXaxis()->SetTitleSize(0.05);
  gr->GetYaxis()->SetTitleSize(0.05);


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
  TLine *l2=new TLine(18.460,-1,18.460,1);
  l2->SetLineColor(4);
  l2->Draw();
  TLine *l3=new TLine(18.530,-1,18.530,1);
  l3->SetLineColor(4);
  l3->Draw();*/
 
 //gr->SaveAs("NLL.pdf");
 //gr->SaveAs("NLL.eps");
 //d->Update();


  return;






}  


