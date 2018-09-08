//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jan 26 21:04:06 2017 by ROOT version 5.32/00
// from TTree mytree/mytree
// found on file: finalselectionntuple.root
//////////////////////////////////////////////////////////

#ifndef myntuple_h
#define myntuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class myntuple {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         fourmuonmass;
   Float_t         fourmuonmassErr;
   Float_t         mupmumhighmass;
   Float_t         mupmumhighmassErr;
   Float_t         mupmumhighmassFit;
   Float_t         mupmumlowmassFit;
   Float_t         mupmummasswrong1;
   Float_t         mupmummasswrong2;
   Float_t         fourmuonvtxprob;
   Float_t         rawfourmuonpt;
   Float_t         mupmummupmass;
   Float_t         mupmummummass;
   Float_t         runnum;
   Float_t         evtnum;
   Float_t         luminum;
   Float_t         dupnum;
   Float_t         mupmumhighmassFitN;
   Float_t         mupmumlowmassFitN;
   Float_t         fitmu11px;
   Float_t         fitmu11py;
   Float_t         fitmu11pz;
   Float_t         fitmu12px;
   Float_t         fitmu12py;
   Float_t         fitmu12pz;
   Float_t         fitmu21px;
   Float_t         fitmu21py;
   Float_t         fitmu21pz;
   Float_t         rawmu11px;
   Float_t         rawmu11py;
   Float_t         rawmu11pz;
   Float_t         rawmu12px;
   Float_t         rawmu12py;
   Float_t         rawmu12pz;
   Float_t         rawmu21px;
   Float_t         rawmu21py;
   Float_t         rawmu21pz;
   Float_t         rawmu22px;
   Float_t         rawmu22py;
   Float_t         rawmu22pz;
   Float_t         fitmu22px;
   Float_t         fitmu22py;
   Float_t         fitmu22pz;
   Float_t         mypidx;
   Float_t         mu12ctau;
   Float_t         mu34ctau;
   Float_t         mu14ctau;
   Float_t         mu23ctau;
   Float_t         fourmuctau;

   // List of branches
   TBranch        *b_fourmuonmass;   //!
   TBranch        *b_fourmuonmassErr;   //!
   TBranch        *b_mupmumhighmass;   //!
   TBranch        *b_mupmumhighmassErr;   //!
   TBranch        *b_mupmumhighmassFit;   //!
   TBranch        *b_mupmumlowmassFit;   //!
   TBranch        *b_mupmummasswrong1;   //!
   TBranch        *b_mupmummasswrong2;   //!
   TBranch        *b_fourmuonvtxprob;   //!
   TBranch        *b_rawfourmuonpt;   //!
   TBranch        *b_mupmummupmass;   //!
   TBranch        *b_mupmummummass;   //!
   TBranch        *b_runnum;   //!
   TBranch        *b_evtnum;   //!
   TBranch        *b_luminum;   //!
   TBranch        *b_dupnum;   //!
   TBranch        *b_mupmumhighmassFitN;   //!
   TBranch        *b_mupmumlowmassFitN;   //!
   TBranch        *b_fitmu11px;   //!
   TBranch        *b_fitmu11py;   //!
   TBranch        *b_fitmu11pz;   //!
   TBranch        *b_fitmu12px;   //!
   TBranch        *b_fitmu12py;   //!
   TBranch        *b_fitmu12pz;   //!
   TBranch        *b_fitmu21px;   //!
   TBranch        *b_fitmu21py;   //!
   TBranch        *b_fitmu21pz;   //!
   TBranch        *b_rawmu11px;   //!
   TBranch        *b_rawmu11py;   //!
   TBranch        *b_rawmu11pz;   //!
   TBranch        *b_rawmu12px;   //!
   TBranch        *b_rawmu12py;   //!
   TBranch        *b_rawmu12pz;   //!
   TBranch        *b_rawmu21px;   //!
   TBranch        *b_rawmu21py;   //!
   TBranch        *b_rawmu21pz;   //!
   TBranch        *b_rawmu22px;   //!
   TBranch        *b_rawmu22py;   //!
   TBranch        *b_rawmu22pz;   //!
   TBranch        *b_fitmu22px;   //!
   TBranch        *b_fitmu22py;   //!
   TBranch        *b_fitmu22pz;   //!
   TBranch        *b_mypidx;   //!
   TBranch        *b_mu12ctau;   //!
   TBranch        *b_mu34ctau;   //!
   TBranch        *b_mu14ctau;   //!
   TBranch        *b_mu23ctau;   //!
   TBranch        *b_fourmuctau;   //!

   myntuple(TTree *tree=0);
   virtual ~myntuple();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef myntuple_cxx
myntuple::myntuple(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("finalselectionntuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("finalselectionntuple.root");
      }
      f->GetObject("mytree",tree);

   }
   Init(tree);
}

myntuple::~myntuple()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t myntuple::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t myntuple::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void myntuple::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fourmuonmass", &fourmuonmass, &b_fourmuonmass);
   fChain->SetBranchAddress("fourmuonmassErr", &fourmuonmassErr, &b_fourmuonmassErr);
   fChain->SetBranchAddress("mupmumhighmass", &mupmumhighmass, &b_mupmumhighmass);
   fChain->SetBranchAddress("mupmumhighmassErr", &mupmumhighmassErr, &b_mupmumhighmassErr);
   fChain->SetBranchAddress("mupmumhighmassFit", &mupmumhighmassFit, &b_mupmumhighmassFit);
   fChain->SetBranchAddress("mupmumlowmassFit", &mupmumlowmassFit, &b_mupmumlowmassFit);
   fChain->SetBranchAddress("mupmummasswrong1", &mupmummasswrong1, &b_mupmummasswrong1);
   fChain->SetBranchAddress("mupmummasswrong2", &mupmummasswrong2, &b_mupmummasswrong2);
   fChain->SetBranchAddress("fourmuonvtxprob", &fourmuonvtxprob, &b_fourmuonvtxprob);
   fChain->SetBranchAddress("rawfourmuonpt", &rawfourmuonpt, &b_rawfourmuonpt);
   fChain->SetBranchAddress("mupmummupmass", &mupmummupmass, &b_mupmummupmass);
   fChain->SetBranchAddress("mupmummummass", &mupmummummass, &b_mupmummummass);
   fChain->SetBranchAddress("runnum", &runnum, &b_runnum);
   fChain->SetBranchAddress("evtnum", &evtnum, &b_evtnum);
   fChain->SetBranchAddress("luminum", &luminum, &b_luminum);
   fChain->SetBranchAddress("dupnum", &dupnum, &b_dupnum);
   fChain->SetBranchAddress("mupmumhighmassFitN", &mupmumhighmassFitN, &b_mupmumhighmassFitN);
   fChain->SetBranchAddress("mupmumlowmassFitN", &mupmumlowmassFitN, &b_mupmumlowmassFitN);
   fChain->SetBranchAddress("fitmu11px", &fitmu11px, &b_fitmu11px);
   fChain->SetBranchAddress("fitmu11py", &fitmu11py, &b_fitmu11py);
   fChain->SetBranchAddress("fitmu11pz", &fitmu11pz, &b_fitmu11pz);
   fChain->SetBranchAddress("fitmu12px", &fitmu12px, &b_fitmu12px);
   fChain->SetBranchAddress("fitmu12py", &fitmu12py, &b_fitmu12py);
   fChain->SetBranchAddress("fitmu12pz", &fitmu12pz, &b_fitmu12pz);
   fChain->SetBranchAddress("fitmu21px", &fitmu21px, &b_fitmu21px);
   fChain->SetBranchAddress("fitmu21py", &fitmu21py, &b_fitmu21py);
   fChain->SetBranchAddress("fitmu21pz", &fitmu21pz, &b_fitmu21pz);
   fChain->SetBranchAddress("rawmu11px", &rawmu11px, &b_rawmu11px);
   fChain->SetBranchAddress("rawmu11py", &rawmu11py, &b_rawmu11py);
   fChain->SetBranchAddress("rawmu11pz", &rawmu11pz, &b_rawmu11pz);
   fChain->SetBranchAddress("rawmu12px", &rawmu12px, &b_rawmu12px);
   fChain->SetBranchAddress("rawmu12py", &rawmu12py, &b_rawmu12py);
   fChain->SetBranchAddress("rawmu12pz", &rawmu12pz, &b_rawmu12pz);
   fChain->SetBranchAddress("rawmu21px", &rawmu21px, &b_rawmu21px);
   fChain->SetBranchAddress("rawmu21py", &rawmu21py, &b_rawmu21py);
   fChain->SetBranchAddress("rawmu21pz", &rawmu21pz, &b_rawmu21pz);
   fChain->SetBranchAddress("rawmu22px", &rawmu22px, &b_rawmu22px);
   fChain->SetBranchAddress("rawmu22py", &rawmu22py, &b_rawmu22py);
   fChain->SetBranchAddress("rawmu22pz", &rawmu22pz, &b_rawmu22pz);
   fChain->SetBranchAddress("fitmu22px", &fitmu22px, &b_fitmu22px);
   fChain->SetBranchAddress("fitmu22py", &fitmu22py, &b_fitmu22py);
   fChain->SetBranchAddress("fitmu22pz", &fitmu22pz, &b_fitmu22pz);
   fChain->SetBranchAddress("mypidx", &mypidx, &b_mypidx);
   fChain->SetBranchAddress("mu12ctau", &mu12ctau, &b_mu12ctau);
   fChain->SetBranchAddress("mu34ctau", &mu34ctau, &b_mu34ctau);
   fChain->SetBranchAddress("mu14ctau", &mu14ctau, &b_mu14ctau);
   fChain->SetBranchAddress("mu23ctau", &mu23ctau, &b_mu23ctau);
   fChain->SetBranchAddress("fourmuctau", &fourmuctau, &b_fourmuctau);
   Notify();
}

Bool_t myntuple::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void myntuple::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t myntuple::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef myntuple_cxx
