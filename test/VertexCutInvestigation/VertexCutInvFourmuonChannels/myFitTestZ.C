RooDataSet* dataSet(0);
//#include "sPlotMaker.hh"
//gStyle->SetOptFit(111111);
gStyle->SetOptFit(111111);
gSystem->Load("libRooFit");

using namespace RooFit;
using namespace RooStats;


void myFitTestZ() 
{            
   double JpsiMassmin=60.0, JpsiMassmax=115.0; 

  double mybinwidth=1.0;
  
  RooRealVar varMyXmass("varMyXmass", "m(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) [GeV]",JpsiMassmin,JpsiMassmax);

  RooArgSet variables;
  
  variables.add(varMyXmass);  


  RooArgSet* observables = new RooArgSet(varMyXmass,"observables");
 

  //free Gaus shape
  RooRealVar   myMean  ("myMean"    ,"myMean"  ,91.0 ,89.0 ,95. );   
  RooRealVar   mySigma ("mySigma"    ,"mySigma"  ,2.0,1.5, 3.0  ); 
  RooAbsPdf* pdfMyXGauss = new RooGaussian( "pdfMyXGauss", "pdfMyXGauss",  varMyXmass, myMean ,mySigma ) ;
  RooRealVar nSigMyX("nSigMyX", "Number of signal 1 candidates ", 100,  0.0, 100000000.0); 
  
  //free Breit-Wigner shape
  RooAbsPdf* pdfMyXBreitWigner1 = new 	RooBreitWigner( "pdfMyXBreitWigner1", "pdfMyXBreitWigner1",  varMyXmass, myMean ,mySigma ) ;

  //CB
  RooRealVar CBalpha("CBalpha","CBalpha",1.0,0.5,2.0);
  RooRealVar CBn("CBn","CBn",30.0,0.0,150.0);
  RooAbsPdf * pdfMyXCB1 = new RooCBShape("pdfCB1","pdfCB1",varMyXmass,myMean,mySigma,CBalpha,CBn);
  
 	
  //    GausEE_peak.setConstant();
  RooRealVar c1("c1", "c1",-7.37579e-02 ,  -2.0, 2.0);
  RooRealVar c2("c2", "c2",-2.68499e-01 ,  -2., 2.0);
  RooRealVar c3("c3", "c3", -5.54591e-02,  -15., 15.0);
  RooRealVar c4("c4", "c4", -5.54591e-02,  -15., 15.0);
  RooRealVar c5("c5", "c5", -5.54591e-02,  -15., 15.0);
  RooRealVar c6("c6", "c6", -5.54591e-02,  -15., 15.0);


  RooAbsPdf *  BkgPolPdf = new RooChebychev("BkgPolPdf","BkgPolPdf",varMyXmass,RooArgSet(c1,c2,c3,c4));
	
  RooRealVar nBkgPol("nBkgPol", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);

  //single CB
  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXCB1, nSigMyX);
  //RooBreit-Wigner
  //RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXBreitWigner1, nSigMyX);
  //single gausssian
  //RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyXGauss, nSigMyX);

  
  RooExtendPdf *  extendpdfBkgPol = new RooExtendPdf("extendpdfBkgPol","Signal 1 PDF",*BkgPolPdf, nBkgPol);

  //dataset 
   RooDataSet * alldata=&(RooDataSet::read("myZnovtx1e-30.txt",variables,"Q"));


   //RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
  RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfBkgPol), RooArgList(nBkgPol) ) ;

  myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));  
  double NullFitNLL=myfitresult.minNll();
  //    return;

  RooAddPdf mytotalPdf("mytotPdf", "mytotPdf", RooArgList(*extendpdfSigMyX,*extendpdfBkgPol), RooArgList(nSigMyX,nBkgPol) ) ;
    myfitresult= mytotalPdf.fitTo(*alldata,Minos(kTRUE), Save(1));
  double SigFitNLL=myfitresult.minNll();
  
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
  //  mytotalPdf.paramOn(frame,Parameters(RooArgSet(nSigMyX)) );
  mytotalPdf.paramOn(frame,Format("NEU", AutoPrecision(3)));
  mytotalPdf.plotOn(frame);
  
  frame->SetTitle("");  
  frame->GetXaxis()->SetTitleSize(0.05);
  frame->GetXaxis()->SetLabelSize(0.035);
  frame->GetXaxis()->SetTitleOffset(0.9);
  frame->GetYaxis()->SetTitleSize(0.05);
  frame->GetYaxis()->SetTitleOffset(0.9);
  frame->SetMarkerColor(1);
  frame->SetMarkerSize(2.0);
  //frame->SetMinimum(-10);
  //frame->SetMaximum(75);
  frame->Draw();
  
  
  
  RooHist* hpull = frame->pullHist() ;
  if (!hpull) Error("hpull","hpull is nULL");
  hpull->SetMarkerStyle(8);
  hpull->SetMarkerSize(2.0);
  hpull->SetMarkerColor(2);
  //hpull->Draw("e1");
  

  //  TCanvas * cx=new TCanvas("cx","cx",800,200);
  //cx->cd();
  // hpull->Draw("e1");


  //calculate the background area [18,19]--signal, [16.5,17.5]--low-sideband, [19.5,20.5]--high-sideband
  varMyXmass.setRange("selection",18.0, 19.0);
  RooAbsReal*  NBkgatSig=BkgPolPdf->createIntegral(RooArgSet(varMyXmass),"selection");
  varMyXmass.setRange("selection1",16.0, 17.0);
  RooAbsReal*  NBkgatLow=BkgPolPdf->createIntegral(RooArgSet(varMyXmass),"selection1");
  varMyXmass.setRange("selection2",20.0, 21.0);
  RooAbsReal*  NBkgatHigh=BkgPolPdf->createIntegral(RooArgSet(varMyXmass),"selection2");
  float NBkgatSigNum, NBkgatLowNum, NBkgatHighNum;
  NBkgatSigNum=NBkgatSig->getVal(); 
  NBkgatLowNum=NBkgatLow->getVal();
  NBkgatHighNum=NBkgatHigh->getVal();
  //  cout<<"NBkgatSig="<<NBkgatSigNum<<",NBkgatLow="<<NBkgatLowNum<<",NBkgatHigh="<<NBkgatHighNum<<",(NBkgatLowNum+NBkgatHighNum)/NBkgatSigNum="<<(NBkgatLowNum+NBkgatHighNum)/NBkgatSigNum<<endl;
  cout<<"Null/Signal hypothesis fit NLL="<<NullFitNLL<<"/"<<SigFitNLL<<", sqrt(2*Dll)="<<sqrt(2*(NullFitNLL-SigFitNLL))<<endl;


    return;
 
  
  //  Bp_peak.setConstant();
  // Bp_width.setConstant();
 myMean.setConstant();
 //c1.setConstant();c2.setConstant();




 
  myfitresult= mytotalPdf.fitTo(*alldata, Minos(kTRUE), Save());  
  
  //RooFitResult *  myfitresult=totalPdf.fitTo(*alldata, Minos(kTRUE), Save() );
  
  TFile * myhbk= new TFile("myhbksPlot.root","recreate");
  sPlotMaker mysplottest(alldata,myfitresult, RooArgList(*extendpdfBkgPol, *extendpdfSigMyX),RooArgList(),RooArgList(nBkgPol,nSigMyX), RooArgList());
  //sPlotMaker mysplottest(alldata,myfitresult, RooArgList(*extendpdfBkgPol, *extendpdfSigBp,*myB0toksShape),RooArgList(),RooArgList(nBkgPol,nSigMyX,nB0toKs), RooArgList());
 

  TH1F * myMyXPt=mysplottest.makeShist(&varMyXPt,&nSigMyX,50);
  TH1F * myBckMyXPt=mysplottest.makeShist(&varMyXPt,&nBkgPol,50);
  myMyXPt->SetName("myMyXPt");
  myMyXPt->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-}#mu^{+}#mu^{-}) GeV");
  myMyXPt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMyXPt->SetName("myBckMyXPt");
  myMyXPt->Write();
  myBckMyXPt->Write();

  
   TH1F * myMymumu1mass=mysplottest.makeShist(&varMymumu1mass,&nSigMyX,200);
  TH1F * myBckMymumu1mass=mysplottest.makeShist(&varMymumu1mass,&nBkgPol,200);
  myMymumu1mass->SetName("myMymumu1mass");
  myMymumu1mass->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}}_{1} GeV");
  myMymumu1mass->GetYaxis()->SetTitle("Candidatess/50 MeV");
  myBckMymumu1mass->SetName("myBckMymumu1mass");
  myMymumu1mass->Write();
  myBckMymumu1mass->Write();
  

   TH1F * myMymumu1Pt=mysplottest.makeShist(&varMymumu1Pt,&nSigMyX,50);
  TH1F * myBckMymumu1Pt=mysplottest.makeShist(&varMymumu1Pt,&nBkgPol,50);
  myMymumu1Pt->SetName("myMymumu1Pt");
  myMymumu1Pt->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{1} GeV");
  myMymumu1Pt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMymumu1Pt->SetName("myBckMymumu1Pt");
  myMymumu1Pt->Write();
  myBckMymumu1Pt->Write();

  TH1F * myMymumu2mass=mysplottest.makeShist(&varMymumu2mass,&nSigMyX,100);
  TH1F * myBckMymumu2mass=mysplottest.makeShist(&varMymumu2mass,&nBkgPol,100);
  myMymumu2mass->SetName("myMymumu2mass");
  myMymumu2mass->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}}_{2} GeV");
  myMymumu2mass->GetYaxis()->SetTitle("Candidatess/100 MeV");
  myBckMymumu2mass->SetName("myBckMymumu2mass");
  myMymumu2mass->Write();
  myBckMymumu2mass->Write();

  TH1F * myMymumu2Pt=mysplottest.makeShist(&varMymumu2Pt,&nSigMyX,50);
  TH1F * myBckMymumu2Pt=mysplottest.makeShist(&varMymumu2Pt,&nBkgPol,50);
  myMymumu2Pt->SetName("myMymumu2Pt");
  myMymumu2Pt->GetXaxis()->SetTitle("p_{T}(#mu^{+}#mu^{-})_{1} GeV");
  myMymumu2Pt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMymumu2Pt->SetName("myBckMymumu2Pt");
  myMymumu2Pt->Write();
  myBckMymumu2Pt->Write();


  TH1F * myMymu11Pt=mysplottest.makeShist(&varMymu11Pt,&nSigMyX,50);
  TH1F * myBckMymu11Pt=mysplottest.makeShist(&varMymu11Pt,&nBkgPol,50);
  myMymu11Pt->SetName("myMymu11Pt");
  myMymu11Pt->GetXaxis()->SetTitle("p_{T}(#mu^{+})_{1} GeV");
  myMymu11Pt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMymu11Pt->SetName("myBckMymu11Pt");
  myMymu11Pt->Write();
  myBckMymu11Pt->Write();

  TH1F * myMymu12Pt=mysplottest.makeShist(&varMymu12Pt,&nSigMyX,50);
  TH1F * myBckMymu12Pt=mysplottest.makeShist(&varMymu12Pt,&nBkgPol,50);
  myMymu12Pt->SetName("myMymu12Pt");
  myMymu12Pt->GetXaxis()->SetTitle("p_{T}(#mu^{-})_{1} GeV");
  myMymu12Pt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMymu12Pt->SetName("myBckMymu12Pt");
  myMymu12Pt->Write();
  myBckMymu12Pt->Write();

  TH1F * myMymu21Pt=mysplottest.makeShist(&varMymu21Pt,&nSigMyX,50);
  TH1F * myBckMymu21Pt=mysplottest.makeShist(&varMymu21Pt,&nBkgPol,50);
  myMymu21Pt->SetName("myMymu21Pt");
  myMymu21Pt->GetXaxis()->SetTitle("p_{T}(#mu^{+})_{2} GeV");
  myMymu21Pt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMymu21Pt->SetName("myBckMymu21Pt");
  myMymu21Pt->Write();
  myBckMymu21Pt->Write();

  TH1F * myMymu22Pt=mysplottest.makeShist(&varMymu22Pt,&nSigMyX,50);
  TH1F * myBckMymu22Pt=mysplottest.makeShist(&varMymu22Pt,&nBkgPol,50);
  myMymu22Pt->SetName("myMymu22Pt");
  myMymu22Pt->GetXaxis()->SetTitle("p_{T}(#mu^{-})_{2} GeV");
  myMymu22Pt->GetYaxis()->SetTitle("Candidatess/2 GeV");
  myBckMymu22Pt->SetName("myBckMymu22Pt");
  myMymu22Pt->Write();
  myBckMymu22Pt->Write();


  TH1F * myMymumu1muplusmass=mysplottest.makeShist(&varMymumu1muplusmass,&nSigMyX,1000);
  TH1F * myBckMymumu1muplusmass=mysplottest.makeShist(&varMymumu1muplusmass,&nBkgPol,1000);
  myMymumu1muplusmass->SetName("myMymumu1muplusmass");
  myMymumu1muplusmass->GetXaxis()->SetTitle("m((#mu^{+}#mu^{-})_{1}#mu^{+}) GeV");
  myMymumu1muplusmass->GetYaxis()->SetTitle("Candidatess/100 MeV");
  myBckMymumu1muplusmass->SetName("myBckMymumu1muplusmass");
  myMymumu1muplusmass->Write();
  myBckMymumu1muplusmass->Write();


  TH1F * myMymumu1muminusmass=mysplottest.makeShist(&varMymumu1muminusmass,&nSigMyX,1000);
  TH1F * myBckMymumu1muminusmass=mysplottest.makeShist(&varMymumu1muminusmass,&nBkgPol,1000);
  myMymumu1muminusmass->SetName("myMymumu1muminusmass");
  myMymumu1muminusmass->GetXaxis()->SetTitle("m((#mu^{+}#mu^{-})_{1}#mu^{-}) GeV");
  myMymumu1muminusmass->GetYaxis()->SetTitle("Candidatess/100 MeV");
  myBckMymumu1muminusmass->SetName("myBckMymumu1muminusmass");
  myMymumu1muminusmass->Write();
  myBckMymumu1muminusmass->Write();

  TH1F * myMymuplusmumu2mass=mysplottest.makeShist(&varMymuplusmumu2mass,&nSigMyX,1000);
  TH1F * myBckMymuplusmumu2mass=mysplottest.makeShist(&varMymuplusmumu2mass,&nBkgPol,1000);
  myMymuplusmumu2mass->SetName("myMymuplusmumu2mass");
  myMymuplusmumu2mass->GetXaxis()->SetTitle("m(#mu^{+}(#mu^{+}#mu^{-})_{2}) GeV");
  myMymuplusmumu2mass->GetYaxis()->SetTitle("Candidatess/100 MeV");
  myBckMymuplusmumu2mass->SetName("myBckMymuplusmumu2mass");
  myMymuplusmumu2mass->Write();
  myBckMymuplusmumu2mass->Write();

  TH1F * myMymuminusmumu2mass=mysplottest.makeShist(&varMymuminusmumu2mass,&nSigMyX,1000);
  TH1F * myBckMymuminusmumu2mass=mysplottest.makeShist(&varMymuminusmumu2mass,&nBkgPol,1000);
  myMymuminusmumu2mass->SetName("myMymuminusmumu2mass");
  myMymuminusmumu2mass->GetXaxis()->SetTitle("m(#mu^{-}(#mu^{+}#mu^{-})_{2}) GeV");
  myMymuminusmumu2mass->GetYaxis()->SetTitle("Candidatess/100 MeV");
  myBckMymuminusmumu2mass->SetName("myBckMymuminusmumu2mass");
  myMymuminusmumu2mass->Write();
  myBckMymuminusmumu2mass->Write();


  TH1F * myFourMuVtxProb=mysplottest.makeShist(&varFourMuVtxProb,&nSigMyX,20);
  TH1F * myBckFourMuVtxProb=mysplottest.makeShist(&varFourMuVtxProb,&nBkgPol,20);
  myFourMuVtxProb->SetName("myFourMuVtxProb");
  myFourMuVtxProb->GetXaxis()->SetTitle("Vtx Probability");
  myFourMuVtxProb->GetYaxis()->SetTitle("");
  myBckFourMuVtxProb->SetName("myBckFourMuVtxProb");
  myFourMuVtxProb->Write();
  myBckFourMuVtxProb->Write();

  TH1F * myMumu1Mumu2DisXY=mysplottest.makeShist(&varMumu1Mumu2DisXY,&nSigMyX,200);
  TH1F * myBckMumu1Mumu2DisXY=mysplottest.makeShist(&varMumu1Mumu2DisXY,&nBkgPol,200);
  myMumu1Mumu2DisXY->SetName("myMumu1Mumu2DisXY");
  myMumu1Mumu2DisXY->GetXaxis()->SetTitle("#Delta_{XY} between dimuon pairs [cm]");
  myMumu1Mumu2DisXY->GetYaxis()->SetTitle("");
  myBckMumu1Mumu2DisXY->SetName("myBckMumu1Mumu2DisXY");
  myMumu1Mumu2DisXY->Write();
  myBckMumu1Mumu2DisXY->Write();

  TH1F * myMumu1Mumu2DisZ=mysplottest.makeShist(&varMumu1Mumu2DisZ,&nSigMyX,1000);
  TH1F * myBckMumu1Mumu2DisZ=mysplottest.makeShist(&varMumu1Mumu2DisZ,&nBkgPol,1000);
  myMumu1Mumu2DisZ->SetName("myMumu1Mumu2DisZ");
  myMumu1Mumu2DisZ->GetXaxis()->SetTitle("#Delta_{Z} between dimuon pairs [cm]");
  myMumu1Mumu2DisZ->GetYaxis()->SetTitle("");
  myBckMumu1Mumu2DisZ->SetName("myBckMumu1Mumu2DisZ");
  myMumu1Mumu2DisZ->Write();
  myBckMumu1Mumu2DisZ->Write();



 /*
 variables.add(varMyXPt);
  variables.add(varMymumu1mass);
  variables.add(varMymumu1Pt);
  variables.add(varMymumu2mass);
  variables.add(varMymumu2Pt);
  variables.add(varMymu11Pt);
  variables.add(varMymu12Pt);
  variables.add(varMymu21Pt);
  variables.add(varMymu22Pt);
  variables.add(varMymumu1muplusmass);
  variables.add(varMymumu1muminusmass);
  variables.add(varMymuplusmumu2mass);
  variables.add(varMymuminusmumu2mass);
varFourMuVtxProb
varMumu1Mumu2DisXY
varMumu1Mumu2DisZ
  */



}

