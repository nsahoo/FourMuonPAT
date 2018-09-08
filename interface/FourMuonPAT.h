// -*- C++ -*-
//
// Package:    FourMuonPAT
// Class:      FourMuonPAT
// 
/**\class FourMuonPAT FourMuonPAT.cc myAnalyzers/FourMuonPAT/src/FourMuonPAT.cc

 Description: <one line class summary>
Make rootTuple for JPsiKKK reconstruction

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  
//
//

#ifndef _FourMuonPAT_h
#define _FourMuonPAT_h

// system include files
#include <memory>

// user include files
#include "../interface/VertexReProducer.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Math/interface/Error.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/Math/interface/Point3D.h"
#include "DataFormats/Math/interface/Vector3D.h"


#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/TransientTrackKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackFromFTSFactory.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Candidate/interface/VertexCompositeCandidate.h"
#include "DataFormats/V0Candidate/interface/V0Candidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "RecoVertex/V0Producer/interface/V0Producer.h"
#include "RecoVertex/VertexTools/interface/VertexDistanceXY.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"

#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"

#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "PhysicsTools/RecoUtils/interface/CheckHitPattern.h"

#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"

#include <vector>
#include <utility>

#include "CLHEP/Matrix/Vector.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"

#include "DataFormats/MuonReco/interface/MuonSelectors.h"

//
// class decleration
//

using std::vector;
using namespace edm;
using namespace reco;
using namespace std;

class FourMuonPAT : public EDAnalyzer {
public:
  explicit FourMuonPAT(const ParameterSet&);
  ~FourMuonPAT();

  
private:
  virtual void beginJob() ;
  virtual void beginRun(Run const & iRun, EventSetup const& iSetup);
  virtual void analyze(const Event&, const EventSetup&);
  virtual void endJob() ;


 virtual int GetHitsBefore(const EventSetup& setup, const vector<reco::Track>& trks, RefCountedKinematicTree& fitTr)
        {
        static CheckHitPattern checkHitPattern;
	VertexState Vrtx;
        Vrtx=fitTr->currentDecayVertex()->vertexState();
	int totalhit=0;
	for(unsigned int i=0; i<trks.size(); i++)
	{
	CheckHitPattern::Result hitMu1info = checkHitPattern.analyze(setup,trks[i],Vrtx, true);
	totalhit = totalhit+(int)hitMu1info.hitsInFrontOfVert;
	}

	return totalhit; 
        }

virtual int GetMissesAfter(const EventSetup& setup, const vector<reco::Track>& trks, RefCountedKinematicTree& VrtxTree)
        {
        static CheckHitPattern checkHitPattern;
	VertexState Vrtx;
        Vrtx=VrtxTree->currentDecayVertex()->vertexState();
        int totalmiss=0;
	for(unsigned int j=0; j<trks.size(); j++){
        CheckHitPattern::Result hitMu1info = checkHitPattern.analyze(setup,trks[j],Vrtx, true);
	totalmiss = totalmiss+(int)hitMu1info.missHitsAfterVert;
	}
        return totalmiss;
        }

  //get ctau from primary vertex
  /*
virtual double GetcTau(RefCountedKinematicVertex& decayVrtx, RefCountedKinematicParticle& kinePart, Vertex& primVrtx, BeamSpot& bs)
	{	TVector3 vtx;
		TVector3 pvtx;
                vtx.SetXYZ((*decayVrtx).position().x(), (*decayVrtx).position().y(), 0);
                pvtx.SetXYZ(bs.x0(), bs.y0(), 0);
                VertexDistanceXY vdistXY;
		TVector3 pperp(kinePart->currentState().globalMomentum().x(),
                           kinePart->currentState().globalMomentum().y(), 0);

                TVector3 vdiff = vtx - pvtx;
         	double cosAlpha = vdiff.Dot(pperp) / (vdiff.Perp() * pperp.Perp());
         	Measurement1D distXY = vdistXY.distance(Vertex(*decayVrtx), Vertex(primVrtx));
       double ctauPV = distXY.value() * cosAlpha * kinePart->currentState().mass() / pperp.Perp();
	return ctauPV;

	}

virtual double GetcTauErr(RefCountedKinematicVertex& decayVrtx, RefCountedKinematicParticle& kinePart, Vertex& primVrtx, BeamSpot& bs)
        {       
                TVector3 pperp(kinePart->currentState().globalMomentum().x(),
                           kinePart->currentState().globalMomentum().y(), 0);
		AlgebraicVector vpperp(3);
                            vpperp[0] = pperp.x();
                            vpperp[1] = pperp.y();
                            vpperp[2] = 0.;

		GlobalError v1e = (Vertex(*decayVrtx)).error();
        	GlobalError v2e = primVrtx.error();
        	AlgebraicSymMatrix vXYe = asHepMatrix(v1e.matrix()) + asHepMatrix(v2e.matrix());
       		double ctauErrPV = sqrt(vXYe.similarity(vpperp)) * kinePart->currentState().mass() / (pperp.Perp2());

        return ctauErrPV;

        }
  */
  //get ctau from beamspot
  virtual double GetcTau(RefCountedKinematicVertex& decayVrtx, RefCountedKinematicParticle& kinePart, Vertex& bs)
  {	TVector3 vtx;
    TVector3 pvtx;
    vtx.SetXYZ((*decayVrtx).position().x(), (*decayVrtx).position().y(), 0);
    pvtx.SetXYZ(bs.position().x(), bs.position().y(), 0);
    VertexDistanceXY vdistXY;
    TVector3 pperp(kinePart->currentState().globalMomentum().x(),
		   kinePart->currentState().globalMomentum().y(), 0);
    
    TVector3 vdiff = vtx - pvtx;
    double cosAlpha = vdiff.Dot(pperp) / (vdiff.Perp() * pperp.Perp());
    Measurement1D distXY = vdistXY.distance(Vertex(*decayVrtx), Vertex(bs));
    double ctauPV = distXY.value() * cosAlpha * kinePart->currentState().mass() / pperp.Perp();
    return ctauPV;    
  }
  
  virtual double GetcTauErr(RefCountedKinematicVertex& decayVrtx, RefCountedKinematicParticle& kinePart, Vertex& bs)
  {       
    TVector3 pperp(kinePart->currentState().globalMomentum().x(),
		   kinePart->currentState().globalMomentum().y(), 0);
    AlgebraicVector vpperp(3);
    vpperp[0] = pperp.x();
    vpperp[1] = pperp.y();
    vpperp[2] = 0.;
    
    GlobalError v1e = (Vertex(*decayVrtx)).error();
    GlobalError v2e = bs.error();
    AlgebraicSymMatrix vXYe = asHepMatrix(v1e.matrix()) + asHepMatrix(v2e.matrix());
    double ctauErrPV = sqrt(vXYe.similarity(vpperp)) * kinePart->currentState().mass() / (pperp.Perp2());
    
    return ctauErrPV;    
  }
  


  double deltaR(double eta1, double phi1, double eta2, double phi2) {
    double deta = eta1 - eta2;
    double dphi = phi1 - phi2;
    while (dphi >   M_PI) dphi -= 2*M_PI;
    while (dphi <= -M_PI) dphi += 2*M_PI;
    return sqrt(deta*deta + dphi*dphi);
  }
  


/*	
  const reco::DeDxDataValueMap * energyLoss;
  Int_t iexception_dedx;

  virtual double getSigmaOfLogdEdx(double logde);
  virtual float getEnergyLoss(const reco::TrackRef & track);
  virtual double nsigmaofdedx(const reco::TrackRef & track, double & theo, double & sigma);
  virtual double getLogdEdx(double bg);
  virtual double GetMass(const reco::TrackRef & track);
  */

  // ----------member data ---------------------------
  string proccessName_;
  HLTConfigProvider hltConfig_;

  InputTag hlTriggerResults_;
  InputTag inputGEN_;
  string vtxSample;
  bool doMC;
  int MCParticle;
  bool doJPsiMassCost;
  int MuPixHits_c;
  int MuSiHits_c;
  double MuNormChi_c;
  double MuD0_c;

  double JMaxM_c;
  double JMinM_c;
  int PiSiHits_c;
  double PiPt_c;
  double JPiPiDR_c;
  double XPiPiDR_c;
  bool UseXDr_c;	
  double JPiPiMax_c;
  double JPiPiMin_c;
	
  bool resolveAmbiguity_; 
  bool addXlessPrimaryVertex_;
  vector<string>      TriggersForJpsi_;
  vector<string>      FiltersForJpsi_;
  vector<string>      TriggersForUpsilon_;
  vector<string>      FiltersForUpsilon_;

  int JpsiMatchTrig[50], UpsilonMatchTrig[50];

  vector<string>      TriggersForMatching_;
  vector<string>      FiltersForMatching_;
  int  MatchingTriggerResult[50];
  bool Debug_;
  double Chi_Track_;

  TTree* X_One_Tree_;

  unsigned int        runNum, evtNum, lumiNum;
  
  vector<unsigned int>* trigRes;
  vector<std::string>* trigNames;
  vector<unsigned int>* L1TT;
  vector<std::string>* MatchTriggerNames;

  float               priVtxX, priVtxY, priVtxZ, priVtxXE, priVtxYE, priVtxZE, priVtxChiNorm, priVtxChi, priVtxCL;
  vector<float>       *PriVtxXCorrX, *PriVtxXCorrY, *PriVtxXCorrZ;
  vector<double>      *PriVtxXCorrEX, *PriVtxXCorrEY, *PriVtxXCorrEZ;
  vector<float>	      *PriVtxXCorrC2, *PriVtxXCorrCL;

  unsigned int         nMu;
  vector<float>       *muPx, *muPy, *muPz, *muD0, *muD0E, *muDz, *muChi2, *muGlChi2,  *mufHits;   
  vector<bool>        *muFirstBarrel, *muFirstEndCap;
  vector<float>       *muDzVtx, *muDxyVtx;   
  vector<int>         *muNDF, *muGlNDF, *muPhits, *muShits, *muGlMuHits, *muType, *muQual;
  vector<int>         *muTrack;
  vector<float>       *muCharge;
  vector<float>       *muIsoratio;
  vector<int>         *muIsGoodLooseMuon, *muIsGoodLooseMuonNew, *muIsGoodSoftMuonNewIlse,*muIsGoodSoftMuonNewIlseMod, *muIsGoodTightMuon,*muIsJpsiTrigMatch, *muIsUpsTrigMatch, *munMatchedSeg;
  //added by zhenhu for MuonID
  vector<float>       *muMVAMuonID, *musegmentCompatibility; 
 
  unsigned int        nMyFourMuon;
  vector<bool>        *MyFourMuonTrigMatch;
  vector<float>       *MyFourMuonMass, *MyFourMuonMassErr, *MyFourMuonVtxCL, *MyFourMuonVtxC2, *MyFourMuonPx, *MyFourMuonPy, *MyFourMuonPz,*MyFourMuonCTau,*MyFourMuonCTauErr;
  //////////New vars//////
  vector<bool> *MyMu1TrigMatchVtxSD, *MyMu2TrigMatchVtxSD, *MyMu3TrigMatchVtxSD, *MyMu4TrigMatchVtxSD;
  vector<bool> *MyMu1TrigMatchL3FilterSD, *MyMu2TrigMatchL3FilterSD, *MyMu3TrigMatchL3FilterSD, *MyMu4TrigMatchL3FilterSD;
  //

  vector<float> *My1234Mass, *My1324Mass, *My1423Mass;
  vector<double> *My1234JpsiDisXY, *My1324JpsiDisXY, *My1423JpsiDisXY, *My1234JpsiDisZ, *My1324JpsiDisZ, *My1423JpsiDisZ;
  vector<int> *MyHitBeforeVrtx, *MyMissAfterVrtx,*MyJpsi1HitsBeforeMu12,*MyJpsi1MissAfterMu12,*MyJpsi2HitsBeforeMu34,*MyJpsi2MissAfterMu34,*MyJpsi3HitsBeforeMu13,*MyJpsi3MissAfterMu13,*MyJpsi4HitsBeforeMu24,*MyJpsi4MissAfterMu24,*MyJpsi5HitsBeforeMu14,*MyJpsi5MissAfterMu14,*MyJpsi6HitsBeforeMu23,*MyJpsi6MissAfterMu23, *MyFourMuonChg;
  vector<double> *MyJpsi1CTau_Mu12,*MyJpsi1CTauErr_Mu12,*MyJpsi1ChiProb_Mu12,*MyJpsi2CTau_Mu34,*MyJpsi2CTauErr_Mu34,*MyJpsi2ChiProb_Mu34,*MyJpsi3CTau_Mu13,*MyJpsi3CTauErr_Mu13,*MyJpsi3ChiProb_Mu13,*MyJpsi4CTau_Mu24,*MyJpsi4CTauErr_Mu24,*MyJpsi4ChiProb_Mu24,*MyJpsi5CTau_Mu14,*MyJpsi5CTauErr_Mu14,*MyJpsi5ChiProb_Mu14,*MyJpsi6CTau_Mu23,*MyJpsi6CTauErr_Mu23,*MyJpsi6ChiProb_Mu23;

  vector<float> *MyJpsi1Mass_Mu12, *MyJpsi2Mass_Mu34, *MyJpsi3Mass_Mu13, *MyJpsi4Mass_Mu24, *MyJpsi5Mass_Mu14, *MyJpsi6Mass_Mu23;
  vector<float> *MyJpsi1MassErr_Mu12, *MyJpsi2MassErr_Mu34, *MyJpsi3MassErr_Mu13, *MyJpsi4MassErr_Mu24, *MyJpsi5MassErr_Mu14, *MyJpsi6MassErr_Mu23;
  
  //added by yik, for a mupmum pair only
  unsigned int         nmumuonly;
  vector<float> *mumuonlyMass,*mumuonlyMassErr, *mumuonlyVtxCL, *mumuonlyPx, *mumuonlyPy, *mumuonlyPz,  *mumuonlymu1Idx, *mumuonlymu2Idx, 
    *mumuonlyctau, *mumuonlyctauerr;
  vector<int> *mumuonlymuoverlapped, *mumuonlyChg, *mumuonlynsharedSeg;
  //added by yik end
  
  
  float mybxlumicorr,myrawbxlumi;
  ////////////////////////  
  vector<int>         *MyFourMuonMu1Idx, *MyFourMuonMu2Idx, *MyFourMuonMu3Idx, *MyFourMuonMu4Idx;
  vector<float>       *MyFourMuonMu4Px, *MyFourMuonMu4Py, *MyFourMuonMu4Pz, *MyFourMuonMu4fChi2;
  vector<float>       *MyFourMuonMu3Px, *MyFourMuonMu3Py, *MyFourMuonMu3Pz, *MyFourMuonMu3fChi2;
  vector<float>       *MyFourMuonMu2Px, *MyFourMuonMu2Py, *MyFourMuonMu2Pz, *MyFourMuonMu2fChi2;
  vector<float>       *MyFourMuonMu1Px, *MyFourMuonMu1Py, *MyFourMuonMu1Pz, *MyFourMuonMu1fChi2;
  vector<int>         *MyFourMuonMu4fNDF,*MyFourMuonMu3fNDF,*MyFourMuonMu2fNDF, *MyFourMuonMu1fNDF;
  vector<float>       *MyFourMuonDecayVtxX, *MyFourMuonDecayVtxY, *MyFourMuonDecayVtxZ;
  vector<float>       *MyFourMuonDecayVtxXE, *MyFourMuonDecayVtxYE, *MyFourMuonDecayVtxZE;
  vector<float>       *MyFourMuoncosAlpha, *MyFourMuonFLSig,  *MyFourMuonrVtxMag2D, *MyFourMuonsigmaRvtxMag2D;
  vector<float>       *MyFourMuonTrkIsoOverFourMuSumpt, *MyFourMuonTrkIsoOverFourMuVectpt;
  vector<int>         *MyFourMuonOverlap12,*MyFourMuonOverlap13, *MyFourMuonOverlap14,*MyFourMuonOverlap23,*MyFourMuonOverlap24,*MyFourMuonOverlap34;
  vector<int>         *MyFourMuonSharedSeg12,*MyFourMuonSharedSeg13, *MyFourMuonSharedSeg14,*MyFourMuonSharedSeg23,*MyFourMuonSharedSeg24,*MyFourMuonSharedSeg34;


  //Do MC tree
  unsigned int         nxMC; 
  vector<int>          *MC_xPdgId;
  vector<float>        *MC_YmuPx, *MC_YmuPy, *MC_YmuPz, *MC_YmuM, *MC_YmuChg, *MC_YmuPdgId;
  vector<float>        *MC_HmuPx, *MC_HmuPy, *MC_HmuPz, *MC_HmuM, *MC_HmuChg, *MC_HmuPdgId;
  vector<float>        *MC_xPx, *MC_xPy, *MC_xPz, *MC_xM, *MC_xChg;
  //Do MC tree end


};

#endif
