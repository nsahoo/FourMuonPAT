void PDFnnloAsym_comp(){


//setTDRStyle();
gStyle->SetOptStat(0);

  int nbins = 11;
  float binning[] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1, 2.4};
  float xd[12] = {0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.85, 2.1, 2.4};
  double dxd[11];

    for(int j=0; j<11; ++j){
        dxd[j] = (xd[j+1]-xd[j])/2;

   std::cout << "Bin width " << j  << "=" << 2*dxd[j]  << std::endl;

    }

  TH1F *CT10nlo = new TH1F( "CT10nlo", "", nbins, binning);
  TH1F *HERAnlo = new TH1F( "HERAnlo", "", nbins, binning);
  TH1F *MMHTnlo = new TH1F( "MMHTnlo", "", nbins, binning);
  TH1F *NNPDFnlo = new TH1F( "NNPDFnlo", "", nbins, binning);

  float ct10_nlo_PDFp[]={0.00550,0.00562,0.00563,0.00553,0.00574,0.00553,0.00556,0.00555,0.00548,0.00537,0.00501}; 
  float ct10_nlo_PDFm[]={0.00572,0.00588,0.00604,0.00607,0.00642,0.00648,0.00673,0.00682,0.00677,0.00674,0.00625}; 

  float hera_nlo_PDFp[]={0.004968,0.005141,0.005264,0.005443,0.005760,0.005849,0.006196,0.006051,0.006265,0.006956,0.007803}; 
  float hera_nlo_PDFm[]={0.004257,0.004376,0.004507,0.004686,0.004987,0.005143,0.005388,0.005438,0.005480,0.006021,0.006669};

  float mmht_nlo_PDFp[]={0.004848,  0.004905,  0.004829,  0.004866,  0.005049,  0.005118,  0.005268,  0.005488,  0.005693,  0.005730,  0.005693}; 
  float mmht_nlo_PDFm[]={0.002966,  0.003003,  0.002972,  0.003020,  0.003146,  0.003398,  0.003795,  0.004244,  0.004759,  0.005225,  0.005511}; 

  float nnpdf_nlo_PDF[]={0.002474,  0.002321,  0.002092,  0.001878,  0.001906,  0.001930,  0.002046,  0.002135,  0.002253,  0.002465,  0.002841}; 



  for (int ii = 1; ii <= nbins; ii ++) {

  CT10nlo->SetBinContent(ii, 0 + (ct10_nlo_PDFp[ii-1] + ct10_nlo_PDFm[ii-1])/2 - ct10_nlo_PDFm[ii-1]);
  CT10nlo->SetBinError(ii, (ct10_nlo_PDFp[ii-1] + ct10_nlo_PDFm[ii-1])/2);

  HERAnlo->SetBinContent(ii, 0 + (hera_nlo_PDFp[ii-1] + hera_nlo_PDFm[ii-1])/2 - hera_nlo_PDFm[ii-1]);
  HERAnlo->SetBinError(ii, (hera_nlo_PDFp[ii-1] + hera_nlo_PDFm[ii-1])/2);

  MMHTnlo->SetBinContent(ii, 0 + (mmht_nlo_PDFp[ii-1] + mmht_nlo_PDFm[ii-1])/2 - mmht_nlo_PDFm[ii-1]);
  MMHTnlo->SetBinError(ii, (mmht_nlo_PDFp[ii-1] + mmht_nlo_PDFm[ii-1])/2);

  NNPDFnlo->SetBinContent(ii, 0);
  NNPDFnlo->SetBinError(ii, nnpdf_nlo_PDF[ii-1]);

}


TCanvas *nlo = new TCanvas("nlo", "nlo",800,800);
nlo->cd();

CT10nlo->SetFillColor(kYellow);
HERAnlo->SetFillColor(7);
MMHTnlo->SetFillColor(9);
NNPDFnlo->SetFillColor(2);

CT10nlo->SetMarkerColor(kYellow);
HERAnlo->SetMarkerColor(7);
MMHTnlo->SetMarkerColor(9);
NNPDFnlo->SetMarkerColor(2);

CT10nlo->SetLineColor(kYellow);
HERAnlo->SetLineColor(7);
MMHTnlo->SetLineColor(9);
NNPDFnlo->SetLineColor(2);

CT10nlo->SetMarkerStyle(0);
HERAnlo->SetMarkerStyle(0);
MMHTnlo->SetMarkerStyle(0);
NNPDFnlo->SetMarkerStyle(0);

//CT10nlo->SetFillStyle(3144);
HERAnlo->SetFillStyle(3006);
MMHTnlo->SetFillStyle(3004);
//NNPDFnlo->SetFillStyle(3005);

CT10nlo->GetXaxis()->SetTitle("Muon |#eta|");
CT10nlo->GetYaxis()->SetTitle("Asymmetry: PDF Uncertainty");
CT10nlo->GetYaxis()->SetRangeUser(-0.035,0.035);

CT10nlo->Draw("E2");
HERAnlo->Draw("SAMEE2");

MMHTnlo->Draw("SAMEE2");
NNPDFnlo->Draw("SAMEE2");


    TLegend *legend = new TLegend(0.188442,0.171654,0.655779,0.407874);
    legend->AddEntry(CT10nlo,"CT10 NNLO","f");   
    legend->AddEntry(HERAnlo,"HERAPDF1.5 NNLO","f");
    legend->AddEntry(MMHTnlo,"MMHT2014 NNLO","f");
    legend->AddEntry(NNPDFnlo,"NNPF3.0 NNLO","f");
    legend->SetFillColor(kWhite);
    legend->SetBorderSize(0);
    legend->Draw();




}
