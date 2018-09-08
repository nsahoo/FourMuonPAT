/*
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
using namespace RooFit ;
*/

void mysimultaneousfit()
{

  RooRealVar x("x","mass [GeV]",13,26); 

  
  // Construct signal pdf
  RooRealVar   mean  ("mean"    ,"mean"  ,18.4532,15.0,22.0 );

  RooRealVar nSigMyX_4mu("nSigMyX_4mu", "Number of signal 1 candidates ", 91,  -10.0, 100000000.0); 

  RooRealVar MyXfrac1_4mu("MyXfrac1_4mu","fraction of double gaussian1",0.0302285,0.0,1.0) ;
  RooRealVar CBsigma1_4mu("CBsigma1_4mu","CBsigma1_4mu",0.1586284,0.1,0.3);
  RooRealVar CBalpha1_4mu("CBalpha1_4mu","CBalpha1_4mu",2.13,1.0,10.0);
  RooRealVar CBn1_4mu("CBn1_4mu","CBn1_4mu",0.2,0.0,2.0);
  RooAbsPdf * pdfCB1_4mu = new RooCBShape("pdfCB1_4mu","pdfCB1_4mu",x,mean,CBsigma1_4mu,CBalpha1_4mu,CBn1_4mu);
  RooRealVar CBsigma2_4mu("CBsigma2_4mu","CBsigma2_4mu",0.1586284,0.12,0.17);
  RooRealVar CBalpha2_4mu("CBalpha2_4mu","CBalpha2_4mu",2.13,2.1,2.2);
  RooRealVar CBn2_4mu("CBn2_4mu","CBn2_4mu",1.16,1.1,1.2);
  RooAbsPdf * pdfCB2_4mu = new RooCBShape("pdfCB2_4mu","pdfCB2_4mu",x,mean,CBsigma2_4mu,CBalpha2_4mu,CBn2_4mu);
  mean.setVal( 1.85007e+01 );
  MyXfrac1_4mu.setVal( 3.49987e-01 );
  CBalpha1_4mu.setVal(5.76320e-01);
  CBn1_4mu.setVal( 2.52857e+00 );
  CBsigma1_4mu.setVal( 7.34724e-02 );
  CBalpha2_4mu.setVal(-2.03863e+00);
  CBn2_4mu.setVal( 1.85372e+00 );
  CBsigma2_4mu.setVal( 1.60791e-01 );
  MyXfrac1_4mu.setConstant();
  //mean.setConstant();
  CBalpha1_4mu.setConstant();
  CBn1_4mu.setConstant();
  CBsigma1_4mu.setConstant();
  CBalpha2_4mu.setConstant();
  CBn2_4mu.setConstant();
  CBsigma2_4mu.setConstant();
  
  RooAbsPdf* pdfMyX_4mu = new RooAddPdf("pdfMyX_4mu","pdfMyX_4mu",RooArgList(*pdfCB1_4mu,*pdfCB2_4mu),RooArgList(MyXfrac1_4mu)); 

  //polynominal  
  //    GausEE_peak.setConstant();   
  RooRealVar c1_4mu("c1_4mu", "c1_4mu", -9.46433e-02/*,  -2.0, 2.0*/);
  RooRealVar c2_4mu("c2_4mu", "c2_4mu", -5.60690e-01/*,  -2., 2.0*/);
  RooRealVar c3_4mu("c3_4mu", "c3_4mu", 3.82999e-01/*,  -15., 15.0*/);
  RooRealVar c4_4mu("c4_4mu", "c4_4mu", -1.27946e-01,  -15., 15.0);
  RooRealVar c5_4mu("c5_4mu", "c5_4mu", -2.15607e-01,  -15., 15.0);
  RooRealVar c6_4mu("c6_4mu", "c6_4mu", 1.65804e-01,  -15., 15.0);
  RooRealVar c7_4mu("c7_4mu", "c7_4mu", -5.54591e-02,  -15., 15.0);
  RooRealVar c8_4mu("c8_4mu", "c8_4mu", -5.54591e-02,  -15., 15.0);
  
  RooAbsPdf *  BkgPolPdf_4mu = new RooChebychev("BkgPolPdf_4mu","BkgPolPdf_4mu",x,RooArgSet(c1_4mu,c2_4mu,c3_4mu));
  // RooAbsPdf *  BkgPolPdf = new RooBernstein("BkgPolPdf","BkgPolPdf",x,RooArgSet(c1,c2,c3));
  //  RooRealVar nBkgPol_4mu("nBkgPol_4mu", "Number of signal 2 candidates ", 10000,  0.0, 900000000.0);
  
  //c1->setConstant(); c2->setConstant(); c3->setConstant();  c4->setConstant(); c5->setConstant(); c6->setConstant(); 
  //decided by F-test
  //RooAbsPdf *  BkgPolPdf = new RooGenericPdf("BkgPolPdf","BkgPolPdf","-7991.50657388753097620792686939+1893.07016200460088839463423938*x-183.502862678134391671846969984*pow(x,2)+9.5637857237468733018204147811*pow(x,3)-0.291427643046618278788173483917*pow(x,4)+0.005213768095073623154434017124*pow(x,5)-5.08485406030409416329451932626e-05*pow(x,6)+2.08964397872896200087202214779e-07*pow(x,7)",RooArgSet(x));
  // decided by 14-50 8th order poly 4016evts
  //RooAbsPdf *  BkgPolPdf_4mu = new RooGenericPdf("BkgPolPdf_4mu","BkgPolPdf_4mu","-16714.4937101397736114449799061+4311.0720920080102587235160172*x-468.478153920417355493555078283*pow(x,2)+28.2522013728231122797751595499*pow(x,3)-1.03875540251508957645398822933*pow(x,4)+0.0239087266103714876641639364152*pow(x,5)-0.000337045613627642739844325614484*pow(x,6)+2.66431133280929559198628615857e-06*pow(x,7)-9.05159339903484236808689120894e-09*pow(x,8)",RooArgSet(x));  
  // decided by 13-50 7th order poly 4016evts
  // RooAbsPdf *  BkgPolPdf_4mu = new RooGenericPdf("BkgPolPdf_4mu","BkgPolPdf_4mu","-8029.72556910640741989482194185+1902.4751348672136828099610284*x-184.458579738994046692823758349*pow(x,2)+9.61615353805623307437144831056*pow(x,3)-0.293101221959658320148633947611*pow(x,4)+0.005244993616785415153913607611*pow(x,5)-5.11639490550146143000090348529e-05*pow(x,6)+2.10297441183958885472593883237e-07*pow(x,7)",RooArgSet(x));  
  // decided by 12-35 7th order
  //RooAbsPdf *  BkgPolPdf_4mu = new RooGenericPdf("BkgPolPdf_4mu","BkgPolPdf_4mu","27474.7248644783903728239238262-9175.11990013552713207900524139*x+1265.12681233746570796938613057*pow(x,2)-93.6036137778848456036939751357*pow(x,3)+4.03119528055012299461168367998*pow(x,4)-0.101475314637659352889897945715*pow(x,5)+0.0013873013556274244994365174577*pow(x,6)-7.96923820331946827918382508793e-06*pow(x,7)",RooArgSet(x));
  


  RooRealVar nBkgPol_4mu("nBkgPol_4mu", "Number of signal 2 candidates ", 2720,  0.0, 900000000.0);

      //RooBreit-Wigner
  //  RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX_4muBreitWigner1, nSigMyX_4mu);
  //single gausssian
  //RooExtendPdf *  extendpdfSigMyX = new RooExtendPdf("extendpdfSigMyX","Signal 1 PDF",*pdfMyX_4muGauss1, nSigMyX_4mu);
  //fixed shape from MC
  RooExtendPdf *  extendpdfSigMyX_4mu = new RooExtendPdf("extendpdfSigMyX_4mu","Signal 1 PDF",*pdfMyX_4mu, nSigMyX_4mu);


  RooExtendPdf *  extendpdfBkgPol_4mu = new RooExtendPdf("extendpdfBkgPol_4mu","Signal 1 PDF",*BkgPolPdf_4mu, nBkgPol_4mu);


  RooAddPdf model4mu_sig("model4mu_sig", "model4mu_sig", RooArgList(*extendpdfSigMyX_4mu,*extendpdfBkgPol_4mu), RooArgList(nSigMyX_4mu,nBkgPol_4mu) ) ;
  
  RooAddPdf model4mu_null("model4mu_null", "model4mu_null", RooArgList(*extendpdfBkgPol_4mu), RooArgList(nBkgPol_4mu) ) ;






  // C r e a t e   m o d e l   f o r   2mu2ele
  // -------------------------------------------------------------- 
  //fixed shape from MC
	
   RooRealVar nSigMyX_2mu2ele("nSigMyX_2mu2ele", "Number of signal 1 candidates ", 58,  0.0, 100000000.0);   
	RooRealVar MyXfrac1_2mu2ele("MyXfrac1_2mu2ele","fraction of double gaussian1",0.0302285,0.0,1.0) ;

  RooRealVar BWWidth1_2mu2ele("BWWidth1_2mu2ele","BWWidth1_2mu2ele",0.260748,0.01,3.0);
	RooAbsPdf * pdfBW1_2mu2ele = new RooBreitWigner("pdfBW1_2mu2ele","pdfBW1_2mu2ele",x,mean,BWWidth1_2mu2ele);


	RooRealVar CBsigma1_2mu2ele("CBsigma1_2mu2ele","CBsigma1_2mu2ele",0.1586284,0.1,0.5);
	RooRealVar CBalpha1_2mu2ele("CBalpha1_2mu2ele","CBalpha1_2mu2ele",2.13,0.0,5.0);
	RooRealVar CBn1_2mu2ele("CBn1_2mu2ele","CBn1_2mu2ele",0.2,0.0,10.0);
	RooAbsPdf * pdfCB1_2mu2ele = new RooCBShape("pdfCB1_2mu2ele","pdfCB1_2mu2ele",x,mean,CBsigma1_2mu2ele,CBalpha1_2mu2ele,CBn1_2mu2ele);
 	RooAbsPdf* pdfMyX_2mu2ele = new RooAddPdf("pdfMyX_2mu2ele","pdfMyX_2mu2ele",RooArgList(*pdfCB1_2mu2ele,*pdfBW1_2mu2ele),RooArgList(MyXfrac1_2mu2ele)); 
  BWWidth1_2mu2ele.setVal( 4.51913e-01 );
  // mean.setVal( 1.84714e+01 ); 
  MyXfrac1_2mu2ele.setVal( 6.82784e-01 );
        
  CBalpha1_2mu2ele.setVal( 2.12574e-01 );
  CBn1_2mu2ele.setVal( 2.49742e+01 );   
  CBsigma1_2mu2ele.setVal( 2.25490e-01 );
	CBalpha1_2mu2ele.setConstant(); CBn1_2mu2ele.setConstant();CBsigma1_2mu2ele.setConstant();  
	//mean.setConstant(); 
	MyXfrac1_2mu2ele.setConstant();  BWWidth1_2mu2ele.setConstant();



	
  // GausEE_peak.setConstant();
  RooRealVar c1_2mu2ele("c1_2mu2ele", "c1_2mu2ele", 2.41670e-01/*, -2.0, 2.0*/);
  RooRealVar c2_2mu2ele("c2_2mu2ele", "c2_2mu2ele",-3.98521e-01/*, -2.0, 2.0*/);
  RooRealVar c3_2mu2ele("c3_2mu2ele", "c3_2mu2ele", 1.86775e-01/*, -15.0, 15.0*/);
  RooRealVar c4_2mu2ele("c4_2mu2ele", "c4_2mu2ele", 2.01574e-01/*,  -15., 15.0*/);
  RooAbsPdf *  BkgPolPdf_2mu2ele = new RooChebychev("BkgPolPdf_2mu2ele","BkgPolPdf_2mu2ele",x,RooArgSet(c1_2mu2ele,c2_2mu2ele,c3_2mu2ele,c4_2mu2ele));
	
  


  RooRealVar nBkgPol_2mu2ele("nBkgPol_2mu2ele", "Number of signal 2 candidates ", 460,  0.0, 900000000.0);


  //RooBreit-Wigner
  //RooExtendPdf *  extendpdfSigMyX_2mu2ele = new RooExtendPdf("extendpdfSigMyX_2mu2ele","Signal 1 PDF",*pdfMyX_2mu2eleBreitWigner1, nSigMyX_2mu2ele);
  //single gausssian
  //RooExtendPdf *  extendpdfSigMyX_2mu2ele = new RooExtendPdf("extendpdfSigMyX_2mu2ele","Signal 1 PDF",*pdfMyX_2mu2eleGauss, nSigMyX_2mu2ele);
  //fixed shape from MC
  RooExtendPdf *  extendpdfSigMyX_2mu2ele = new RooExtendPdf("extendpdfSigMyX_2mu2ele","Signal 1 PDF",*pdfMyX_2mu2ele, nSigMyX_2mu2ele);

  
  RooExtendPdf *  extendpdfBkgPol_2mu2ele = new RooExtendPdf("extendpdfBkgPol_2mu2ele","Signal 1 PDF",*BkgPolPdf_2mu2ele, nBkgPol_2mu2ele);


  RooAddPdf model2mu2ele_sig("model2mu2ele_sig", "model2mu2ele_sig", RooArgList(*extendpdfSigMyX_2mu2ele,*extendpdfBkgPol_2mu2ele), RooArgList(nSigMyX_2mu2ele,nBkgPol_2mu2ele) ) ;

   RooAddPdf model2mu2ele_null("model2mu2ele_null", "model2mu2ele_null", RooArgList(*extendpdfBkgPol_2mu2ele), RooArgList(nBkgPol_2mu2ele) ) ;
 



  // G e n e r a t e   e v e n t s   f o r   b o t h   s a m p l e s 
  // ---------------------------------------------------------------

   /*  
  // Generate 1000 events in x and y from model
  RooDataSet *data_4mu = model4mu_sig.generate(RooArgSet(x),2820*10) ;
  RooDataSet *data_2mu2ele = model2mu2ele_sig.generate(RooArgSet(x),520*10);
   */
  
  RooArgSet variables_4mu;
  variables_4mu.add(x);
  //data_4mu= &(RooDataSet::read("haha.txt",variables_4mu,"Q"));
  RooDataSet * data_4mu= &(RooDataSet::read("7and8TeVcombinedMuOniaDoubleMunolightmesoninunselectedpair.txt",variables_4mu,"Q"));
  RooArgSet variables_2mu2ele;
  variables_2mu2ele.add(x);
  RooDataSet * data_2mu2ele= &(RooDataSet::read("2mu2elemass.txt",variables_2mu2ele,"Q"));
  


  // C r e a t e   i n d e x   c a t e g o r y   a n d   j o i n   s a m p l e s 
  // ---------------------------------------------------------------------------
  



  // Define category to distinguish 4mu and 2mu2ele events
  RooCategory sample("sample","sample") ;
  sample.defineType("Upsilon mu+mu-") ;
  sample.defineType("Upsilon e+e-") ;
  
  // Construct combined dataset in (x,sample)
  RooDataSet combData("combData","combined data",x,Index(sample),Import("4mu",*data_4mu),Import("2mu2ele",*data_2mu2ele));
  
  RooFitResult*  myfitresult;
  double NullFitNLL, SigFitNLL;

  // C o n s t r u c t   a   s i m u l t a n e o u s   p d f   i n   ( x , s a m p l e )
  // -----------------------------------------------------------------------------------
  //null-hypothesis test  
  RooSimultaneous simPdf_null("simPdf_null","simultaneous pdf null",sample) ;  
  simPdf_null.addPdf(model4mu_null,"4mu") ;
  simPdf_null.addPdf(model2mu2ele_null,"2mu2ele") ;

  //myfitresult =  simPdf_null.fitTo(combData,Minos(kTRUE), Save(1)) ;
  myfitresult =  simPdf_null.fitTo(combData,Save(1)) ;

  NullFitNLL=myfitresult->minNll();

  myfitresult->Delete();

  //return;

  // Construct a simultaneous pdf using category sample as index
  RooSimultaneous simPdf_sig("simPdf_sig","simultaneous pdf",sample) ;  
  // Associate model with the physics state and model2mu2ele_sig with the control state
  simPdf_sig.addPdf(model4mu_sig,"4mu") ;
  simPdf_sig.addPdf(model2mu2ele_sig,"2mu2ele") ;

  // P e r f o r m   a   s i m u l t a n e o u s   f i t
  // ---------------------------------------------------
  
  // Perform simultaneous fit of model to data and model2mu2ele_sig to data_2mu2ele
  //  simPdf_sig.fitTo(combData);
  myfitresult=  simPdf_sig.fitTo(combData,Minos(kTRUE), Save(1)) ;
  SigFitNLL=myfitresult->minNll();
  

  // P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
  // ----------------------------------------------------------------
  
  // Make a frame for the physics sample
  RooPlot* frame1 = x.frame(Bins(65),Title("Upsilon mu+mu- w/o light mesons")) ;
  
  frame1->GetXaxis()->SetTitleSize(0.05);
  frame1->GetXaxis()->SetLabelSize(0.035);
  frame1->GetXaxis()->SetTitleOffset(0.9);
  // frame->GetYaxis()->SetTitle("pull");
  frame1->GetYaxis()->SetTitleSize(0.05);
  frame1->GetYaxis()->SetTitleOffset(1.25);
  frame1->SetMarkerColor(1);
  frame1->SetMarkerSize(2.0);
  //frame1->SetMinimum(-10);
  //frame1->SetMaximum(120);


  // Plot all data_4mu tagged as physics sample
  combData.plotOn(frame1,Cut("sample==sample::4mu")) ;
  
  // Plot "physics" slice of simultaneous pdf. 
  // NBL You _must_ project the sample index category with data using ProjWData 
  // as a RooSimultaneous makes no prediction on the shape in the index category 
  // and can thus not be integrated
  simPdf_sig.plotOn(frame1,Slice(sample,"4mu"),ProjWData(sample,combData)) ;
  simPdf_sig.plotOn(frame1,Slice(sample,"4mu"),Components("extendpdfBkgPol_4mu"),ProjWData(sample,combData),LineStyle(kDashed)) ;
  
  // The same plot for the control sample slice
  RooPlot* frame2 = x.frame(Bins(30),Title("Upsilon e+e-")) ;
  frame2->GetXaxis()->SetTitleSize(0.05);
  frame2->GetXaxis()->SetLabelSize(0.035);
  frame2->GetXaxis()->SetTitleOffset(0.9);
  // frame2->GetYaxis()->SetTitle("pull");
  frame2->GetYaxis()->SetTitleSize(0.05);
  frame2->GetYaxis()->SetTitleOffset(1.25);
  frame2->SetMarkerColor(1);
  frame2->SetMarkerSize(2.0);
  // frame2->SetMinimum(-10);
  // frame2->SetMaximum(120);



  combData.plotOn(frame2,Cut("sample==sample::2mu2ele")) ;
  simPdf_sig.plotOn(frame2,Slice(sample,"2mu2ele"),ProjWData(sample,combData)) ;
  simPdf_sig.plotOn(frame2,Slice(sample,"2mu2ele"),Components("extendpdfBkgPol_2mu2ele"),ProjWData(sample,combData),LineStyle(kDashed)) ;
  
  
  
  TCanvas* c = new TCanvas("simultaneouspdf","simultaneouspdf",1200,400) ;
  c->Divide(2) ;
  c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
  c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;

  cout<<"NLL for null- and signal-hypothesis="<<NullFitNLL<<" and "<<SigFitNLL<<", 2dNLL="<<2*(NullFitNLL-SigFitNLL)<<", taking dof as 2, single sided p-value="<<TMath::Prob(2*(NullFitNLL-SigFitNLL),2)/2<<endl;
  


}

