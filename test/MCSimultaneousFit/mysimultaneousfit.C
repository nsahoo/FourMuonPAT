void mysimultaneousfit()
{
	double mybinwidth = 0.1;
	double x15min = 12.0, x15max = 18.0;
	double x18min = 15.0, x18max = 21.0;
	double x25min = 21.0, x25max = 29.0;
	double x36min = 32.0, x36max = 40.0;
	double x50min = 45.0, x50max = 55.0;

	// double x15min = 13.0, x15max = 16.5;
	// double x18min = 15.0, x18max = 20.5;
	// double x25min = 21.0, x25max = 27.5;
	// double x36min = 32.0, x36max = 39.0;
	// double x50min = 45.0, x50max = 54.0;


	RooRealVar x15("x15","mass [GeV]",x15min,x15max);
	RooRealVar x18("x18","mass [GeV]",x18min,x18max);
	RooRealVar x25("x25","mass [GeV]",x25min,x25max);
	RooRealVar x36("x36","mass [GeV]",x36min,x36max);
	RooRealVar x50("x50","mass [GeV]",x50min,x50max);


	
	// Construct signal pdf
	RooRealVar   mean15  ("mean15"    ,"mean15"  ,1.49951e+01/*,14.0,16.0*/ );
	RooRealVar   mean18  ("mean18"    ,"mean18"  ,1.84859e+01/*,17.5,19.5*/ );
	RooRealVar   mean25  ("mean25"    ,"mean25"  ,2.49840e+01/*,24.0,25.0*/ );
	RooRealVar   mean36  ("mean36"    ,"mean36"  ,3.59621e+01/*,35.0,36.0*/ );
	RooRealVar   mean50  ("mean50"    ,"mean50"  ,4.99372e+01/*,49.0,51.0*/ );

	RooRealVar nSigMyX_15GeV("nSigMyX_15GeV", "Number of signal 1 candidates ", 2.40194e+03/*,  -10.0, 100000000.0*/);
	RooRealVar nSigMyX_18GeV("nSigMyX_18GeV", "Number of signal 1 candidates ", 3.97801e+03/*,  -10.0, 100000000.0*/);
	RooRealVar nSigMyX_25GeV("nSigMyX_25GeV", "Number of signal 1 candidates ", 3.86038e+03/*,  -10.0, 100000000.0*/);
	RooRealVar nSigMyX_36GeV("nSigMyX_36GeV", "Number of signal 1 candidates ", 3.02297e+03/*,  -10.0, 100000000.0*/);
	RooRealVar nSigMyX_50GeV("nSigMyX_50GeV", "Number of signal 1 candidates ", 1.94701e+03/*,  -10.0, 100000000.0*/);


	// RooRealVar MyXfrac_15GeV("MyXfrac_15GeV","fraction of double CB",0.0302285,0.0,1.0) ;
	// RooRealVar MyXfrac_18GeV("MyXfrac_18GeV","fraction of double CB",0.0302285,0.0,1.0) ;
	// RooRealVar MyXfrac_25GeV("MyXfrac_25GeV","fraction of double CB",0.0302285,0.0,1.0) ;
	// RooRealVar MyXfrac_36GeV("MyXfrac_36GeV","fraction of double CB",0.0302285,0.0,1.0) ;
	// RooRealVar MyXfrac_50GeV("MyXfrac_50GeV","fraction of double CB",0.0302285,0.0,1.0) ;

	// RooRealVar MyXfrac("MyXfrac","fraction of double CB",0.0302285,0.0,1.0) ;
	// RooRealVar CBalpha1("CBalpha1","CBalpha1",2.13,1.0,10.0);
	// RooRealVar CBn1("CBn1","CBn1",0.2,0.0,2.0);
	// RooRealVar CBalpha2("CBalpha2","CBalpha2",2.13,2.1,2.2);
	// RooRealVar CBn2("CBn2","CBn2",1.16,1.1,1.2);


	// CB sigma is changing with 2nd order poly. sigma(m)=am^2+bm+c
	RooRealVar p0_Sigma1("p0_Sigma1","p0_Sigma1",1.76677e-02,-0.1,0.1);
	RooRealVar p1_Sigma1("p1_Sigma1","p1_Sigma1",3.75986e-03,0.0,0.1);
	RooRealVar p2_Sigma1("p2_Sigma1","p2_Sigma1",-0.2,0.2);

	RooRealVar p0_Alpha1("p0_Alpha1","p0_Alpha1",0.55,0.0,1.0);
	RooRealVar p1_Alpha1("p1_Alpha1","p1_Alpha1",0.03,0.0,0.1);
	RooRealVar p2_Alpha1("p2_Alpha1","p2_Alpha1",0.0/*,-0.1,0.1*/);

	RooRealVar p0_n1("p0_n1","p0_n1",4.00931e+00,0.,10.);
	RooRealVar p1_n1("p1_n1","p1_n1",-1.56685e-01,-2.5, 1.1);
	RooRealVar p2_n1("p2_n1","p2_n1",1.65468e-03, 0.0,0.1);



	RooRealVar p0_Sigma2("p0_Sigma2","p0_Sigma2", 7.90870e-02 , -0.2, 0.2 );
	RooRealVar p1_Sigma2("p1_Sigma2","p1_Sigma2",3.56044e-03,0.0,0.1);
	RooRealVar p2_Sigma2("p2_Sigma2","p2_Sigma2",1.76605e-04,0.0,0.1);

	RooRealVar p0_Alpha2("p0_Alpha2","p0_Alpha2",-2.21,-10.0,0.);
	RooRealVar p1_Alpha2("p1_Alpha2","p1_Alpha2",0.0/*,-100.,100.9*/);
	RooRealVar p2_Alpha2("p2_Alpha2","p2_Alpha2",0.0/*,-100.0,100.15*/);

	RooRealVar p0_n2("p0_n2","p0_n2",1.062,0.0, 10.0);
	RooRealVar p1_n2("p1_n2","p1_n2",0.0/*,-100.,100.9*/);
	RooRealVar p2_n2("p2_n2","p2_n2",0.0/*,-100.0,100.15*/);

	RooRealVar p0_frac("p0_frac","p0_frac",0.4639,0.0,1.);
	RooRealVar p1_frac("p1_frac","p1_frac",0.0/*,-2.,2.*/);
	RooRealVar p2_frac("p2_frac","p2_frac",0.0/*,0.0,1.*/);

	RooFormulaVar *CBsigma1_15GeV = new RooFormulaVar("CBsigma1_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_Sigma1,p1_Sigma1,p2_Sigma1) );
	RooFormulaVar *CBsigma1_18GeV = new RooFormulaVar("CBsigma1_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_Sigma1,p1_Sigma1,p2_Sigma1) );
	RooFormulaVar *CBsigma1_25GeV = new RooFormulaVar("CBsigma1_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_Sigma1,p1_Sigma1,p2_Sigma1) );
	RooFormulaVar *CBsigma1_36GeV = new RooFormulaVar("CBsigma1_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_Sigma1,p1_Sigma1,p2_Sigma1) );
	RooFormulaVar *CBsigma1_50GeV = new RooFormulaVar("CBsigma1_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_Sigma1,p1_Sigma1,p2_Sigma1) );

	RooFormulaVar *CBalpha1_15GeV = new RooFormulaVar("CBalpha1_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_Alpha1,p1_Alpha1,p2_Alpha1) );
	RooFormulaVar *CBalpha1_18GeV = new RooFormulaVar("CBalpha1_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_Alpha1,p1_Alpha1,p2_Alpha1) );
	RooFormulaVar *CBalpha1_25GeV = new RooFormulaVar("CBalpha1_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_Alpha1,p1_Alpha1,p2_Alpha1) );
	RooFormulaVar *CBalpha1_36GeV = new RooFormulaVar("CBalpha1_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_Alpha1,p1_Alpha1,p2_Alpha1) );
	RooFormulaVar *CBalpha1_50GeV = new RooFormulaVar("CBalpha1_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_Alpha1,p1_Alpha1,p2_Alpha1) );

	RooFormulaVar *CBn1_15GeV = new RooFormulaVar("CBn1_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_n1,p1_n1,p2_n1) );
	RooFormulaVar *CBn1_18GeV = new RooFormulaVar("CBn1_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_n1,p1_n1,p2_n1) );
	RooFormulaVar *CBn1_25GeV = new RooFormulaVar("CBn1_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_n1,p1_n1,p2_n1) );
	RooFormulaVar *CBn1_36GeV = new RooFormulaVar("CBn1_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_n1,p1_n1,p2_n1) );
	RooFormulaVar *CBn1_50GeV = new RooFormulaVar("CBn1_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_n1,p1_n1,p2_n1) );



	RooFormulaVar *CBsigma2_15GeV = new RooFormulaVar("CBsigma2_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_Sigma2,p1_Sigma2,p2_Sigma2) );
	RooFormulaVar *CBsigma2_18GeV = new RooFormulaVar("CBsigma2_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_Sigma2,p1_Sigma2,p2_Sigma2) );
	RooFormulaVar *CBsigma2_25GeV = new RooFormulaVar("CBsigma2_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_Sigma2,p1_Sigma2,p2_Sigma2) );
	RooFormulaVar *CBsigma2_36GeV = new RooFormulaVar("CBsigma2_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_Sigma2,p1_Sigma2,p2_Sigma2) );
	RooFormulaVar *CBsigma2_50GeV = new RooFormulaVar("CBsigma2_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_Sigma2,p1_Sigma2,p2_Sigma2) );

	RooFormulaVar *CBalpha2_15GeV = new RooFormulaVar("CBalpha2_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_Alpha2,p1_Alpha2,p2_Alpha2) );
	RooFormulaVar *CBalpha2_18GeV = new RooFormulaVar("CBalpha2_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_Alpha2,p1_Alpha2,p2_Alpha2) );
	RooFormulaVar *CBalpha2_25GeV = new RooFormulaVar("CBalpha2_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_Alpha2,p1_Alpha2,p2_Alpha2) );
	RooFormulaVar *CBalpha2_36GeV = new RooFormulaVar("CBalpha2_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_Alpha2,p1_Alpha2,p2_Alpha2) );
	RooFormulaVar *CBalpha2_50GeV = new RooFormulaVar("CBalpha2_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_Alpha2,p1_Alpha2,p2_Alpha2) );

	RooFormulaVar *CBn2_15GeV = new RooFormulaVar("CBn2_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_n2,p1_n2,p2_n2) );
	RooFormulaVar *CBn2_18GeV = new RooFormulaVar("CBn2_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_n2,p1_n2,p2_n2) );
	RooFormulaVar *CBn2_25GeV = new RooFormulaVar("CBn2_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_n2,p1_n2,p2_n2) );
	RooFormulaVar *CBn2_36GeV = new RooFormulaVar("CBn2_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_n2,p1_n2,p2_n2) );
	RooFormulaVar *CBn2_50GeV = new RooFormulaVar("CBn2_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_n2,p1_n2,p2_n2) );

	RooFormulaVar *frac_15GeV = new RooFormulaVar("frac_15GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean15,p0_frac,p1_frac,p2_frac) );
	RooFormulaVar *frac_18GeV = new RooFormulaVar("frac_18GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean18,p0_frac,p1_frac,p2_frac) );
	RooFormulaVar *frac_25GeV = new RooFormulaVar("frac_25GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean25,p0_frac,p1_frac,p2_frac) );
	RooFormulaVar *frac_36GeV = new RooFormulaVar("frac_36GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean36,p0_frac,p1_frac,p2_frac) );
	RooFormulaVar *frac_50GeV = new RooFormulaVar("frac_50GeV","@1+@2*@0+@3*@0*@0",RooArgList(mean50,p0_frac,p1_frac,p2_frac) );


	
	RooAbsPdf * pdfCB1_15GeV = new RooCBShape("pdfCB1_15GeV","pdfCB1_15GeV",x15,mean15,*CBsigma1_15GeV,*CBalpha1_15GeV,*CBn1_15GeV);
	RooAbsPdf * pdfCB1_18GeV = new RooCBShape("pdfCB1_18GeV","pdfCB1_18GeV",x18,mean18,*CBsigma1_18GeV,*CBalpha1_18GeV,*CBn1_18GeV);
	RooAbsPdf * pdfCB1_25GeV = new RooCBShape("pdfCB1_25GeV","pdfCB1_25GeV",x25,mean25,*CBsigma1_25GeV,*CBalpha1_25GeV,*CBn1_25GeV);
	RooAbsPdf * pdfCB1_36GeV = new RooCBShape("pdfCB1_36GeV","pdfCB1_36GeV",x36,mean36,*CBsigma1_36GeV,*CBalpha1_36GeV,*CBn1_36GeV);
	RooAbsPdf * pdfCB1_50GeV = new RooCBShape("pdfCB1_50GeV","pdfCB1_50GeV",x50,mean50,*CBsigma1_50GeV,*CBalpha1_50GeV,*CBn1_50GeV);

	
	RooAbsPdf * pdfCB2_15GeV = new RooCBShape("pdfCB2_15GeV","pdfCB2_15GeV",x15,mean15,*CBsigma2_15GeV,*CBalpha2_15GeV,*CBn2_15GeV);
	RooAbsPdf * pdfCB2_18GeV = new RooCBShape("pdfCB2_18GeV","pdfCB2_18GeV",x18,mean18,*CBsigma2_18GeV,*CBalpha2_18GeV,*CBn2_18GeV);
	RooAbsPdf * pdfCB2_25GeV = new RooCBShape("pdfCB2_25GeV","pdfCB2_25GeV",x25,mean25,*CBsigma2_25GeV,*CBalpha2_25GeV,*CBn2_25GeV);
	RooAbsPdf * pdfCB2_36GeV = new RooCBShape("pdfCB2_36GeV","pdfCB2_36GeV",x36,mean36,*CBsigma2_36GeV,*CBalpha2_36GeV,*CBn2_36GeV);
	RooAbsPdf * pdfCB2_50GeV = new RooCBShape("pdfCB2_50GeV","pdfCB2_50GeV",x50,mean50,*CBsigma2_50GeV,*CBalpha2_50GeV,*CBn2_50GeV);

	

	RooAbsPdf * pdfMyX_15GeV = new RooAddPdf("pdfMyX_15GeV","pdfMyX_15GeV",RooArgList(*pdfCB1_15GeV,*pdfCB2_15GeV),RooArgList(*frac_15GeV)); 
	RooAbsPdf * pdfMyX_18GeV = new RooAddPdf("pdfMyX_18GeV","pdfMyX_18GeV",RooArgList(*pdfCB1_18GeV,*pdfCB2_18GeV),RooArgList(*frac_18GeV)); 
	RooAbsPdf * pdfMyX_25GeV = new RooAddPdf("pdfMyX_25GeV","pdfMyX_25GeV",RooArgList(*pdfCB1_25GeV,*pdfCB2_25GeV),RooArgList(*frac_25GeV)); 
	RooAbsPdf * pdfMyX_36GeV = new RooAddPdf("pdfMyX_36GeV","pdfMyX_36GeV",RooArgList(*pdfCB1_36GeV,*pdfCB2_36GeV),RooArgList(*frac_36GeV)); 
	RooAbsPdf * pdfMyX_50GeV = new RooAddPdf("pdfMyX_50GeV","pdfMyX_50GeV",RooArgList(*pdfCB1_50GeV,*pdfCB2_50GeV),RooArgList(*frac_50GeV)); 





	RooExtendPdf *  extendpdfSigMyX_15GeV = new RooExtendPdf("extendpdfSigMyX_15GeV","Signal 1 PDF", *pdfMyX_15GeV, nSigMyX_15GeV);
	RooExtendPdf *  extendpdfSigMyX_18GeV = new RooExtendPdf("extendpdfSigMyX_18GeV","Signal 1 PDF", *pdfMyX_18GeV, nSigMyX_18GeV);
	RooExtendPdf *  extendpdfSigMyX_25GeV = new RooExtendPdf("extendpdfSigMyX_25GeV","Signal 1 PDF", *pdfMyX_25GeV, nSigMyX_25GeV);
	RooExtendPdf *  extendpdfSigMyX_36GeV = new RooExtendPdf("extendpdfSigMyX_36GeV","Signal 1 PDF", *pdfMyX_36GeV, nSigMyX_36GeV);
	RooExtendPdf *  extendpdfSigMyX_50GeV = new RooExtendPdf("extendpdfSigMyX_50GeV","Signal 1 PDF", *pdfMyX_50GeV, nSigMyX_50GeV);



	RooAddPdf model_15GeV("model_15GeV", "model_15GeV", RooArgList(*extendpdfSigMyX_15GeV), RooArgList(nSigMyX_15GeV) ) ;
	RooAddPdf model_18GeV("model_18GeV", "model_18GeV", RooArgList(*extendpdfSigMyX_18GeV), RooArgList(nSigMyX_18GeV) ) ;
	RooAddPdf model_25GeV("model_25GeV", "model_25GeV", RooArgList(*extendpdfSigMyX_25GeV), RooArgList(nSigMyX_25GeV) ) ;
	RooAddPdf model_36GeV("model_36GeV", "model_36GeV", RooArgList(*extendpdfSigMyX_36GeV), RooArgList(nSigMyX_36GeV) ) ;
	RooAddPdf model_50GeV("model_50GeV", "model_50GeV", RooArgList(*extendpdfSigMyX_50GeV), RooArgList(nSigMyX_50GeV) ) ;
	


	

	RooArgSet variables_15GeV;
	RooArgSet variables_18GeV;
	RooArgSet variables_25GeV;
	RooArgSet variables_36GeV;
	RooArgSet variables_50GeV;


	variables_15GeV.add(x15);
	variables_18GeV.add(x18);
	variables_25GeV.add(x25);
	variables_36GeV.add(x36);
	variables_50GeV.add(x50);




	RooDataSet * data_15GeV= &(RooDataSet::read("myfourmuonsignal15GeV.txt",variables_15GeV,"Q"));
	RooDataSet * data_18GeV= &(RooDataSet::read("myfourmuonsignal18GeV.txt",variables_18GeV,"Q"));
	RooDataSet * data_25GeV= &(RooDataSet::read("myfourmuonsignal25GeV.txt",variables_25GeV,"Q"));
	RooDataSet * data_36GeV= &(RooDataSet::read("myfourmuonsignal36GeV.txt",variables_36GeV,"Q"));
	RooDataSet * data_50GeV= &(RooDataSet::read("myfourmuonsignal50GeV.txt",variables_50GeV,"Q"));



	RooCategory sample("sample","sample") ;
	sample.defineType("15 GeV") ;
	sample.defineType("18 GeV") ;
	sample.defineType("25 GeV") ;
	sample.defineType("36 GeV") ;
	sample.defineType("50 GeV") ;

	RooArgSet simfitVariables;
	simfitVariables.add(x15);
	simfitVariables.add(x18);
	simfitVariables.add(x25);
	simfitVariables.add(x36);
	simfitVariables.add(x50);
	



	RooDataSet combData("combData","combined data",simfitVariables,Index(sample),
		Import("15GeV",*data_15GeV),
		Import("18GeV",*data_18GeV),
		Import("25GeV",*data_25GeV),
		Import("36GeV",*data_36GeV),
		Import("50GeV",*data_50GeV)
		);


	RooFitResult*  myfitresult;
	RooSimultaneous simPdf_sig("simPdf_sig","simultaneous pdf",sample) ;  
	simPdf_sig.addPdf(model_15GeV,"15GeV") ;
	simPdf_sig.addPdf(model_18GeV,"18GeV") ;
	simPdf_sig.addPdf(model_25GeV,"25GeV") ;
	simPdf_sig.addPdf(model_36GeV,"36GeV") ;
	simPdf_sig.addPdf(model_50GeV,"50GeV") ;




	myfitresult =  simPdf_sig.fitTo(combData,Minos(kTRUE), Save(1)) ;

	

	// P l o t   m o d e l   s l i c e s   o n   d a t a    s l i c e s 
	// ----------------------------------------------------------------

	// RooPlot* frame2 = x15.frame(/*Bins(65),*/Title("13 GeV")) ;
	RooPlot *frame2 = x15.frame( (int)((x15max-x15min)/mybinwidth) );
	frame2->GetXaxis()->SetTitleSize(0.05);
	frame2->GetXaxis()->SetLabelSize(0.035);
	frame2->GetXaxis()->SetTitleOffset(0.9);
	frame2->GetYaxis()->SetTitleSize(0.05);
	frame2->GetYaxis()->SetTitleOffset(1.25);
	frame2->SetMarkerColor(1);
	frame2->SetMarkerSize(2.0);
	//frame2->SetMinimum(-10);
	// frame2->SetMaximum(10);
	//frame2->GetYaxis()->SetTitle("pull");
	// Plot all data_4mu tagged as physics sample
	combData.plotOn(frame2,Cut("sample==sample::15GeV")) ;
	simPdf_sig.plotOn(frame2,Slice(sample,"15GeV"),ProjWData(sample,combData)) ;
	// simPdf_sig.plotOn(frame2,Slice(sample,"11GeV"),Components("extendpdfBkgPol_4mu"),ProjWData(sample,combData),LineStyle(kDashed)) ;
	/*(
	RooHist* hpull2 = frame2->pullHist() ;
	if (!hpull2) Error("hpull","hpull is nULL");
	hpull2->SetMarkerStyle(8);
	hpull2->SetMarkerSize(2.0);
	hpull2->SetMarkerColor(2);
	*/
	// RooPlot* frame3 = x18.frame(/*Bins(65),*/Title("18 GeV")) ;
	RooPlot *frame3 = x18.frame( (int)((x18max-x18min)/mybinwidth) );
	frame3->GetXaxis()->SetTitleSize(0.05);
	frame3->GetXaxis()->SetLabelSize(0.035);
	frame3->GetXaxis()->SetTitleOffset(0.9);
	frame3->GetYaxis()->SetTitleSize(0.05);
	frame3->GetYaxis()->SetTitleOffset(1.25);
	frame3->SetMarkerColor(1);
	frame3->SetMarkerSize(2.0);
	// frame3->SetMinimum(-10);
	// frame3->SetMaximum(10);
	// frame3->GetYaxis()->SetTitle("pull");
	// Plot all data_4mu tagged as physics sample
	combData.plotOn(frame3,Cut("sample==sample::18GeV")) ;
	simPdf_sig.plotOn(frame3,Slice(sample,"18GeV"),ProjWData(sample,combData)) ;
	// simPdf_sig.plotOn(frame3,Slice(sample,"11GeV"),Components("extendpdfBkgPol_4mu"),ProjWData(sample,combData),LineStyle(kDashed)) ;
	/*
	RooHist* hpull3 = frame3->pullHist() ;
	if (!hpull3) Error("hpull","hpull is nULL");
	hpull3->SetMarkerStyle(8);
	hpull3->SetMarkerSize(2.0);
	hpull3->SetMarkerColor(2);
*/
	// RooPlot* frame4 = x25.frame(/*Bins(65),*/Title("25 GeV")) ;
	RooPlot *frame4 = x25.frame( (int)((x25max-x25min)/mybinwidth) );
	frame4->GetXaxis()->SetTitleSize(0.05);
	frame4->GetXaxis()->SetLabelSize(0.035);
	frame4->GetXaxis()->SetTitleOffset(0.9);
	frame4->GetYaxis()->SetTitleSize(0.05);
	frame4->GetYaxis()->SetTitleOffset(1.25);
	frame4->SetMarkerColor(1);
	frame4->SetMarkerSize(2.0);
	// frame4->SetMinimum(-10);
	// frame4->SetMaximum(10);
	// frame4->GetYaxis()->SetTitle("pull");
	// Plot all data_4mu tagged as physics sample
	combData.plotOn(frame4,Cut("sample==sample::25GeV")) ;
	simPdf_sig.plotOn(frame4,Slice(sample,"25GeV"),ProjWData(sample,combData)) ;
	// simPdf_sig.plotOn(frame4,Slice(sample,"11GeV"),Components("extendpdfBkgPol_4mu"),ProjWData(sample,combData),LineStyle(kDashed)) ;
	/*
	RooHist* hpull4 = frame4->pullHist() ;
	if (!hpull4) Error("hpull","hpull is nULL");
	hpull4->SetMarkerStyle(8);
	hpull4->SetMarkerSize(2.0);
	hpull4->SetMarkerColor(2);
*/
	// RooPlot* frame5 = x36.frame(/*Bins(65),*/Title("36 GeV")) ;
	RooPlot *frame5 = x36.frame( (int)((x36max-x36min)/mybinwidth) );
	frame5->GetXaxis()->SetTitleSize(0.05);
	frame5->GetXaxis()->SetLabelSize(0.035);
	frame5->GetXaxis()->SetTitleOffset(0.9);
	frame5->GetYaxis()->SetTitleSize(0.05);
	frame5->GetYaxis()->SetTitleOffset(1.25);
	frame5->SetMarkerColor(1);
	frame5->SetMarkerSize(2.0);
	// frame5->SetMinimum(-10);
	// frame5->SetMaximum(10);
	// frame5->GetYaxis()->SetTitle("pull");
	// Plot all data_4mu tagged as physics sample
	combData.plotOn(frame5,Cut("sample==sample::36GeV")) ;
	simPdf_sig.plotOn(frame5,Slice(sample,"36GeV"),ProjWData(sample,combData)) ;
	// simPdf_sig.plotOn(frame5,Slice(sample,"11GeV"),Components("extendpdfBkgPol_4mu"),ProjWData(sample,combData),LineStyle(kDashed)) ;
	/*
	RooHist* hpull5 = frame5->pullHist() ;
	if (!hpull5) Error("hpull","hpull is nULL");
	hpull5->SetMarkerStyle(8);
	hpull5->SetMarkerSize(2.0);
	hpull5->SetMarkerColor(2);
*/
	// RooPlot* frame6 = x50.frame(/*Bins(65),*/Title("50 GeV")) ;
	RooPlot *frame6 = x50.frame( (int)((x50max-x50min)/mybinwidth) );
	frame6->GetXaxis()->SetTitleSize(0.05);
	frame6->GetXaxis()->SetLabelSize(0.035);
	frame6->GetXaxis()->SetTitleOffset(0.9);
	frame6->GetYaxis()->SetTitleSize(0.05);
	frame6->GetYaxis()->SetTitleOffset(1.25);
	frame6->SetMarkerColor(1);
	frame6->SetMarkerSize(2.0);
	// frame6->SetMinimum(-10);
	// frame6->SetMaximum(10);
	// frame6->GetYaxis()->SetTitle("pull");
	// Plot all data_4mu tagged as physics sample
	combData.plotOn(frame6,Cut("sample==sample::50GeV")) ;
	simPdf_sig.plotOn(frame6,Slice(sample,"50GeV"),ProjWData(sample,combData)) ;
	// simPdf_sig.plotOn(frame6,Slice(sample,"50GeV"),Components("extendpdfBkgPol_4mu"),ProjWData(sample,combData),LineStyle(kDashed)) ;
	/*
	RooHist* hpull6 = frame6->pullHist() ;
	if (!hpull6) Error("hpull","hpull is nULL");
	hpull6->SetMarkerStyle(8);
	hpull6->SetMarkerSize(2.0);
	hpull6->SetMarkerColor(2);
*/
	
	TCanvas* c = new TCanvas("simultaneouspdf","simultaneouspdf",1200,400) ;
	c->Divide(2,3) ;
	// c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1->GetYaxis()->SetTitleOffset(1.4) ; frame1->Draw() ;
	c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ; // hpull2->Draw("e1");
	c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ; // hpull3->Draw("e1");
	c->cd(3) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ; // hpull4->Draw("e1");
	c->cd(4) ; gPad->SetLeftMargin(0.15) ; frame5->GetYaxis()->SetTitleOffset(1.4) ; frame5->Draw() ; // hpull5->Draw("e1");
	c->cd(5) ; gPad->SetLeftMargin(0.15) ; frame6->GetYaxis()->SetTitleOffset(1.4) ; frame6->Draw() ; // hpull6->Draw("e1");


}

