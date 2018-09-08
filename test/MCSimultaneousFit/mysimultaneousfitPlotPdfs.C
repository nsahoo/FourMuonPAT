void mysimultaneousfitPlotPdfs()
{
	double mybinwidth = 0.1;
	double x15min = 12.0, x15max = 55.0;
	double x18min = 12.0, x18max = 55.0;
	double x25min = 12.0, x25max = 55.0;
	double x36min = 12.0, x36max = 55.0;
	double x50min = 12.0, x50max = 55.0;

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


	// CB sigma is changing with 2nd order poly. sigma(m)=am^2+bm+c
	RooRealVar p0_Sigma1("p0_Sigma1","p0_Sigma1",-4.34577e-02/*,-0.1,0.1*/);
	RooRealVar p1_Sigma1("p1_Sigma1","p1_Sigma1",8.63698e-03/*,0.0,0.1*/);
	RooRealVar p2_Sigma1("p2_Sigma1","p2_Sigma1",-3.50281e-05/*,0.2*/);

	RooRealVar p0_Alpha1("p0_Alpha1","p0_Alpha1",7.12586e-01/*,0.0,1.0*/);
	RooRealVar p1_Alpha1("p1_Alpha1","p1_Alpha1",2.66283e-02/*,0.0,0.1*/);
	RooRealVar p2_Alpha1("p2_Alpha1","p2_Alpha1",0.0/*,-0.1,0.1*/);

	RooRealVar p0_n1("p0_n1","p0_n1",3.61857e+00/*,0.,10.*/);
	RooRealVar p1_n1("p1_n1","p1_n1",-1.24540e-01/*,-2.5, 1.1*/);
	RooRealVar p2_n1("p2_n1","p2_n1",1.18573e-03/*, 0.0,0.1*/);



	RooRealVar p0_Sigma2("p0_Sigma2","p0_Sigma2", 3.31557e-02 /*, -0.2, 0.2 */);
	RooRealVar p1_Sigma2("p1_Sigma2","p1_Sigma2",7.23185e-03/*,0.0,0.1*/);
	RooRealVar p2_Sigma2("p2_Sigma2","p2_Sigma2",1.03334e-04/*,0.0,0.1*/);

	RooRealVar p0_Alpha2("p0_Alpha2","p0_Alpha2",-2.13578e+00/*,-10.0,0.*/);
	RooRealVar p1_Alpha2("p1_Alpha2","p1_Alpha2",0.0/*,-100.,100.9*/);
	RooRealVar p2_Alpha2("p2_Alpha2","p2_Alpha2",0.0/*,-100.0,100.15*/);

	RooRealVar p0_n2("p0_n2","p0_n2",1.38287e+00/*,0.0, 10.0*/);
	RooRealVar p1_n2("p1_n2","p1_n2",0.0/*,-100.,100.9*/);
	RooRealVar p2_n2("p2_n2","p2_n2",0.0/*,-100.0,100.15*/);

	RooRealVar p0_frac("p0_frac","p0_frac",4.58803e-01/*,0.0,1.*/);
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



	RooAddPdf mytotalPdf_15GeV("mytotalPdf_15GeV", "mytotalPdf_15GeV", RooArgList(*extendpdfSigMyX_15GeV), RooArgList(nSigMyX_15GeV) ) ;
	RooAddPdf mytotalPdf_18GeV("mytotalPdf_18GeV", "mytotalPdf_18GeV", RooArgList(*extendpdfSigMyX_18GeV), RooArgList(nSigMyX_18GeV) ) ;
	RooAddPdf mytotalPdf_25GeV("mytotalPdf_25GeV", "mytotalPdf_25GeV", RooArgList(*extendpdfSigMyX_25GeV), RooArgList(nSigMyX_25GeV) ) ;
	RooAddPdf mytotalPdf_36GeV("mytotalPdf_36GeV", "mytotalPdf_36GeV", RooArgList(*extendpdfSigMyX_36GeV), RooArgList(nSigMyX_36GeV) ) ;
	RooAddPdf mytotalPdf_50GeV("mytotalPdf_50GeV", "mytotalPdf_50GeV", RooArgList(*extendpdfSigMyX_50GeV), RooArgList(nSigMyX_50GeV) ) ;

	RooPlot *frame_15 = x15.frame();
	RooPlot *frame_18 = x18.frame();
	RooPlot *frame_25 = x25.frame();
	RooPlot *frame_36 = x36.frame();
	RooPlot *frame_50 = x50.frame();

	gROOT->SetStyle("Plain");  
	TCanvas * c=new TCanvas("c","c",800,600);
	c->cd();

	mytotalPdf_15GeV.plotOn(frame_15,LineColor(2));
	frame_15->SetTitle("");  
	frame_15->GetXaxis()->SetTitleSize(0.05);
	frame_15->GetXaxis()->SetLabelSize(0.035);
	frame_15->GetXaxis()->SetTitleOffset(0.9);
	frame_15->GetYaxis()->SetTitleSize(0.05);
	frame_15->GetYaxis()->SetTitleOffset(0.9);
	frame_15->SetMarkerColor(5);
	frame_15->SetFillColor(2);
	frame_15->SetLineColor(5);
	frame_15->SetMarkerSize(2.0);
	frame_15->Draw();
	mytotalPdf_18GeV.plotOn(frame_18,LineColor(3));
	frame_18->Draw("same");
	mytotalPdf_25GeV.plotOn(frame_25,LineColor(4));
	frame_25->Draw("same");
	mytotalPdf_36GeV.plotOn(frame_36,LineColor(5));
	frame_36->Draw("same");
	mytotalPdf_50GeV.plotOn(frame_50,LineColor(6));
	frame_50->Draw("same");


	

}

