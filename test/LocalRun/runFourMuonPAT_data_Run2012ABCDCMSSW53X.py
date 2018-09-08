import FWCore.ParameterSet.Config as cms

process = cms.Process('NTUPLE')

process.options = cms.untracked.PSet(
        wantSummary = cms.untracked.bool(False)
    )
# import of standard configurations
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.suppressInfo = cms.untracked.vstring( "mkcands" )
process.MessageLogger.suppressWarning = cms.untracked.vstring( "mkcands" )
process.MessageLogger.cerr.FwkReport.reportEvery = 500
MC=False

inputFiles = cms.untracked.vstring()
inputFiles.extend( [
#"dcap://cmsrm-se01.roma1.infn.it/pnfs/roma1.infn.it/data/cms/store/data/Run2012B/MuOniaParked/AOD/22Jan2013-v1/20000/60617BF6-C568-E211-82A1-00215E221812.root",
#"file:/eos/uscms/store/user/sdurgut/FourMuon/PickEvents/Muonia2012B/pickevents_55_1_f50.root",
#"file:/eos/uscms/store/user/sdurgut/FourMuon/PickEvents/Muonia2012B/pickevents_56_1_QUW.root",
#"file:/eos/uscms/store/user/sdurgut/FourMuon/PickEvents/Muonia2012B/pickevents_57_1_iHt.root",

#'file:/uscms/home/mhaytmyr/forSuleyman/EventDisplay/FourMuonMassgt17lt19p5Run12CD.root',
#'/store/data/Run2012A/MuOnia/AOD/22Jan2013-v1/30000/E6C68503-CB83-E211-B833-0025905964BA.root'
#'/store/mc/Summer12DR53X/H0ToUps1SMuMu_m18p5_8TeV-pythia8/AODSIM/PU_RD2_START53_V19F-v1/00000/3212215B-1099-E411-989A-002590AC4B3E.root',
'/store/mc/Summer12DR53X/H0ToUps1SMuMu_m18p5_8TeV-pythia8/AODSIM/PU_RD2_START53_V19F-v1/00000/3A3C037C-1299-E411-AD6A-003048D43944.root'

#'/store/data/Run2012B/MuOnia/AOD/22Jan2013-v1/20000/9221CAFB-0D85-E211-A87E-003048678B0E.root',
#'/store/data/Run2012B/MuOnia/AOD/22Jan2013-v1/20000/2694F1BF-0C85-E211-B005-00261894397B.root',
#'/store/data/Run2012A/MuOnia/AOD/13Jul2012-v1/00000/A42F4CCC-7DD0-E111-9D9C-003048FFD740.root',
#'/store/data/Run2012A/MuOnia/AOD/13Jul2012-v1/00000/7A3561D8-7BD0-E111-8982-003048FFD7BE.root',
#'/store/data/Run2012A/MuOnia/AOD/13Jul2012-v1/00000/7E6A376B-D7D2-E111-8325-003048FFCB84.root',
#'/store/data/Run2012A/MuOnia/AOD/13Jul2012-v1/00000/800E910D-D9CF-E111-9817-0026189438A5.root'
] )



# Input source
process.source = cms.Source("PoolSource",
#                           skipEvents = cms.untracked.uint32(10900),
#	eventsToProcess = cms.untracked.VEventRange(),
		fileNames = inputFiles,
#		lumisToProcess = cms.untracked.VLuminosityBlockRange("196239:453-196239:456","196239:458-196239:459","196239:468-196239:469","196239:475-196239:476","196239:485-196239:492","196239:495-196239:496","196239:501-196239:506","196239:509","196239:511","196239:515-196239:526","196239:532-196239:535","196239:544-196239:547","196239:550-196239:551","196239:556-196239:559","196239:562-196239:563","196239:566-196239:568","196239:570","196239:578-196239:579")
#                            fileNames = cms.untracked.vstring(
#'/store/data/Run2012A/MuOnia/AOD/13Jul2012-v1/00000/F67174CD-D6D2-E111-978C-003048678B18.root',
#'/store/data/Run2012A/MuOnia/AOD/13Jul2012-v1/00000/D83FA399-D6D2-E111-BBDF-003048FFD754.root',
#'/store/data/Run2012A/MuOnia/AOD/22Jan2013-v1/30002/A48FD8A9-B686-E211-8091-00304867924A.root' 

#above file gives error for perigeekinematicstate::state error code 8002
   # ) 
)
process.source.inputCommands = cms.untracked.vstring(
    "keep *",
    "drop L1GlobalTriggerObjectMapRecord_hltL1GtObjectMap__RECO",
    "drop *_MEtoEDMConverter_*_*"
    )

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(-1) )

process.load('Configuration.StandardSequences.GeometryExtended_cff')
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
## GlobalTag prompt processing of 2011 data GR_P_V16
#process.GlobalTag.globaltag = 'GR_P_V16::All' 
#process.GlobalTag.globaltag = 'GR_R_311_V4::All'
## May10 FT_R_42_V13A https://twiki.cern.ch/twiki/bin/viewauth/CMS/Collisions2011Analysis
## Apr21 FT_R_42_V10A  "
#process.GlobalTag.globaltag = 'GR_R_42_V14::All'
#process.GlobalTag.globaltag = cms.string( 'GR_P_V40_AN1::All' ) #2012C prompt v1.
#process.GlobalTag.globaltag = cms.string( 'GR_R_52_V10::All' ) #2012A collision data
#process.GlobalTag.globaltag = cms.string( 'START50_V13::All' ) #MC.
#process.GlobalTag.globaltag = cms.string( 'FT_R_53_V6::All' )  #Jul reprocess data  A&B
process.GlobalTag.globaltag = cms.string( 'FT_53_V21_AN3::All' )  #Jan22 Re-Processing, keep the same version as in another dataset


#process.GlobalTag.globaltag = cms.string( 'FT_53_V21_AN6::All' )  #Jan22 Re-Processing




process.load('Configuration/EventContent/EventContent_cff')
process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi");
process.load("Geometry.CSCGeometry.cscGeometry_cfi");
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi");
process.load("Geometry.DTGeometry.dtGeometry_cfi");
process.load("Geometry.RPCGeometry.rpcGeometry_cfi");
process.load("RecoMuon.DetLayers.muonDetLayerGeometry_cfi");
process.load("Geometry.CaloEventSetup.CaloTopology_cfi");# I added.
process.load("Geometry.CMSCommonData.cmsIdealGeometryXML_cfi"); # I added.
process.load("Geometry.CaloEventSetup.CaloGeometry_cfi"); # I added.

#  Load common sequences
#
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskAlgoTrigConfig_cff')
process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')
process.load('HLTrigger/HLTfilters/hltLevel1GTSeed_cfi')

####################################################################################
##################################good collisions############################################
    
process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                            vertexCollection = cms.InputTag('offlinePrimaryVertices'),
                                            minimumNDOF = cms.uint32(5) ,
                                            maxAbsZ = cms.double(24),
                                            maxd0 = cms.double(2)
                                                      )

process.noscraping = cms.EDFilter("FilterOutScraping",
applyfilter = cms.untracked.bool(True),
debugOn = cms.untracked.bool(False),
numtrack = cms.untracked.uint32(10),
thresh = cms.untracked.double(0.25)
)

# PAT Layer 0+1
process.load("PhysicsTools.PatAlgos.patSequences_cff")

process.load("PhysicsTools.PatAlgos.cleaningLayer1.genericTrackCleaner_cfi")
process.cleanPatTracks.checkOverlaps.muons.requireNoOverlaps = cms.bool(False)
process.cleanPatTracks.checkOverlaps.electrons.requireNoOverlaps = cms.bool(False)
from PhysicsTools.PatAlgos.producersLayer1.muonProducer_cfi import *
patMuons.embedTrack = cms.bool(True)
patMuons.embedPickyMuon = cms.bool(False)
patMuons.embedTpfmsMuon = cms.bool(False)

# Prune generated particles to muons and their parents
process.genMuons = cms.EDProducer("GenParticlePruner",
        src = cms.InputTag("genParticles"),
        select = cms.vstring(
            "drop  *  ",                     # this is the default
            "++keep abs(pdgId) = 13",        # keep muons and their parents
            "drop pdgId == 21 && status = 2" # remove intermediate qcd spam carrying no flavour info
      )
 )

process.load("MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff")
from MuonAnalysis.MuonAssociators.patMuonsWithTrigger_cff import  addMCinfo, useExistingPATMuons, useL1MatchingWindowForSinglets, changeTriggerProcessName, switchOffAmbiguityResolution, addDiMuonTriggers
    # with some customization
if MC:
        addMCinfo(process)
        # since we match inner tracks, keep the matching tight and make it one-to-one
        process.muonMatch.maxDeltaR = 0.05
        process.muonMatch.resolveByMatchQuality = True
addDiMuonTriggers(process)
useExistingPATMuons(process,'cleanPatMuons' , addL1Info=False)
changeTriggerProcessName(process, 'HLT')
switchOffAmbiguityResolution(process) # Switch off ambiguity resolution: allow multiple reco muons to match to the same trigger muon
useL1MatchingWindowForSinglets(process)
process.muonL1Info.maxDeltaR     =0.3
process.muonL1Info.fallbackToME1 = True
process.muonMatchHLTL1.maxDeltaR     = 0.3
process.muonMatchHLTL1.fallbackToME1 = True
process.muonMatchHLTL2.maxDeltaR = 0.3
process.muonMatchHLTL2.maxDPtRel = 10.0
process.muonMatchHLTL3.maxDeltaR = 0.1
process.muonMatchHLTL3.maxDPtRel = 10.0
process.muonMatchHLTCtfTrack.maxDeltaR = 0.1
process.muonMatchHLTCtfTrack.maxDPtRel = 10.0
process.muonMatchHLTTrackMu.maxDeltaR = 0.1
process.muonMatchHLTTrackMu.maxDPtRel = 10.0

#process.reconstruction_step.remove (process.lumiProducer)


from PhysicsTools.PatAlgos.tools.trackTools import *
from RecoTracker.TrackProducer.TrackRefitters_cff import *
process.RungeKuttaTrackerPropagator.Mass =  cms.double(0.493677)

process.refittedGeneralTracks = RecoTracker.TrackProducer.TrackRefitter_cfi.TrackRefitter.clone()
makeTrackCandidates(process,                                        #         patAODTrackCands
        label='TrackCands',                   # output collection will be 'allLayer0TrackCands', 'allLayer1TrackCands', 'selectedLayer1TrackCands'
       # tracks=cms.InputTag('generalTracks'), # input track collection
         tracks=cms.InputTag('generalTracks'),
        particleType='K+',                   # particle type (for assigning a mass), changed by yik to K+ from pi+
        preselection='pt > 0.5',              # preselection cut on candidates. Only methods of 'reco::Candidate' are available, changed to 0.5 from 0.1 by yik
        selection='pt > 0.5',                 # Selection on PAT Layer 1 objects ('selectedLayer1TrackCands'), changed to 0.5 from 0.1 by yik
        isolation={},                         # Isolations to use ('source':deltaR; set to {} for None)
        isoDeposits=[],
        mcAs=None                           # Replicate MC match as the one used for Muons
        );                                    # you can specify more than one collection for this

l1cands = getattr(process, 'patTrackCands')
l1cands.addGenMatch = False

#### Added to produce lumiDetail by max####
#from RecoLuminosity.LumiProducer.lumiProducer_cff import *

#process.lumiProducer = cms.EDProducer("LumiProducer",
#    lumiversion = cms.untracked.string('0001'),
#    ncacheEntries = cms.untracked.uint32(5),
#    connect = cms.string('frontier://LumiProd/CMS_LUMI_PROD')
#)
process.LumiCorrectionSource=cms.ESSource("LumiCorrectionSource",
        connect=cms.string('frontier://LumiCalc/CMS_LUMI_PROD')
)

process.load("Configuration.Geometry.GeometryPilot2_cff")
#Above line was Added to solve error (No data of type "TrackerGeometry" with label "" in record "TrackerDigiGeometryRecord") 

process.mkcands = cms.EDAnalyzer("FourMuonPAT",
     HLTriggerResults = cms.untracked.InputTag("TriggerResults","","HLT"),
##     HLTTriggerSummary = cms.untracked.InputTag("hltTriggerSummaryAOD","","HLT"),
     inputGEN  = cms.untracked.InputTag("genParticles"),
     #VtxSample   = cms.untracked.string('offlinePrimaryVertices'),
     VtxSample   = cms.untracked.string('offlinePrimaryVertices'),
     DoJPsiMassConstraint = cms.untracked.bool(False),
     DoMonteCarloTree = cms.untracked.bool(False),
     MonteCarloParticleId = cms.untracked.int32(20443),
    trackQualities = cms.untracked.vstring('loose','tight','highPurity'),
     MinNumMuPixHits = cms.untracked.int32(1),
     MinNumMuSiHits = cms.untracked.int32(3),
     MaxMuNormChi2 = cms.untracked.double(15),
     MaxMuD0 = cms.untracked.double(10.0),
     MaxJPsiMass = cms.untracked.double(3.4),
     MinJPsiMass = cms.untracked.double(2.7),
     MinNumTrSiHits = cms.untracked.int32(4),
     MinTrPt = cms.untracked.double(0.500),  # changed to 0.500 from 0.300 by yik
     JPsiKKKMaxDR = cms.untracked.double(1.5),
     XCandPiPiMaxDR = cms.untracked.double(1.5),
     UseXDr = cms.untracked.bool(False),
     JPsiKKKMaxMass = cms.untracked.double(5.6),
     JPsiKKKMinMass = cms.untracked.double(5.0),
     resolvePileUpAmbiguity = cms.untracked.bool(True),
     addXlessPrimaryVertex = cms.untracked.bool(True),
     Debug_Output = cms.untracked.bool(False),
##
##  FIXME: use the correct trigger path
##
##  HLT_Dimuon6p5_Jpsi_v1 , HLT_Dimuon6p5_Barrel_Jpsi_v1 , HLT_Dimuon6p5_Barrel_PsiPrime_v1 , HLT_Dimuon6p5_Jpsi_Displaced_v1 
#     TriggersForMatching = cms.untracked.vstring("HLT_Dimuon7_PsiPrime_v1","HLT_Dimuon7_PsiPrime_v2","HLT_Dimuon7_PsiPrime_v3","HLT_Dimuon5_PsiPrime_v1","HLT_Dimuon5_PsiPrime_v2","HLT_Dimuon5_PsiPrime_v3","HLT_Dimuon5_PsiPrime_v4","HLT_Dimuon5_PsiPrime_v5","HLT_Dimuon5_PsiPrime_v6"),  
#     FiltersForMatching = cms.untracked.vstring("hltVertexmumuFilterDimuon7PsiPrime","hltVertexmumuFilterDimuon7PsiPrime","hltVertexmumuFilterDimuon7PsiPrime","hltVertexmumuFilterDimuon5PsiPrime","hltVertexmumuFilterDimuon5PsiPrime","hltVertexmumuFilterDimuon5PsiPrime","hltVertexmumuFilterDimuon5PsiPrime","hltVertexmumuFilterDimuon5PsiPrime","hltVertexmumuFilterDimuon5PsiPrime"),
#     TriggersForJpsi = cms.untracked.vstring("HLT_Dimuon0_Jpsi_Muon_v18","HLT_Dimuon0_Jpsi_Muon_v17","HLT_Dimuon0_Jpsi_Muon_v16","HLT_Dimuon0_Jpsi_Muon_v15","HLT_Dimuon0_Jpsi_Muon_v14","HLT_Dimuon0_Jpsi_Muon_v13","HLT_Dimuon0_Jpsi_Muon_v12","HLT_Dimuon0_Jpsi_Muon_v11","HLT_Dimuon0_Jpsi_Muon_v10"),  
#     FiltersForJpsi = cms.untracked.vstring("hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon"),
#     TriggersForUpsilon = cms.untracked.vstring("HLT_Dimuon0_Upsilon_Muon_v18"),  
#     FiltersForUpsilon = cms.untracked.vstring("hltVertexmumuFilterUpsilonMuon"),

     TriggersForJpsi = cms.untracked.vstring("HLT_Dimuon0_Jpsi_Muon_v18","HLT_Dimuon0_Jpsi_Muon_v17","HLT_Dimuon0_Jpsi_Muon_v16","HLT_Dimuon0_Jpsi_Muon_v15","HLT_Dimuon0_Jpsi_Muon_v14","HLT_Dimuon0_Jpsi_Muon_v13","HLT_Dimuon0_Jpsi_Muon_v12","HLT_Dimuon0_Jpsi_Muon_v11","HLT_Dimuon0_Jpsi_Muon_v10","HLT_Dimuon0_Jpsi_Muon_v9","HLT_Dimuon0_Jpsi_Muon_v8","HLT_Dimuon0_Jpsi_Muon_v7","HLT_Dimuon0_Jpsi_Muon_v6","HLT_Dimuon0_Jpsi_Muon_v5","HLT_Dimuon0_Jpsi_Muon_v4","HLT_Dimuon0_Jpsi_Muon_v3","HLT_Dimuon0_Jpsi_Muon_v2","HLT_Dimuon0_Jpsi_Muon_v1"),  
     FiltersForJpsi = cms.untracked.vstring("hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon","hltVertexmumuFilterJpsiMuon"),

     TriggersForUpsilon = cms.untracked.vstring("HLT_Dimuon0_Upsilon_Muon_v18","HLT_Dimuon0_Upsilon_Muon_v17","HLT_Dimuon0_Upsilon_Muon_v16","HLT_Dimuon0_Upsilon_Muon_v15","HLT_Dimuon0_Upsilon_Muon_v14","HLT_Dimuon0_Upsilon_Muon_v13","HLT_Dimuon0_Upsilon_Muon_v12","HLT_Dimuon0_Upsilon_Muon_v11","HLT_Dimuon0_Upsilon_Muon_v10","HLT_Dimuon0_Upsilon_Muon_v9","HLT_Dimuon0_Upsilon_Muon_v8","HLT_Dimuon0_Upsilon_Muon_v7","HLT_Dimuon0_Upsilon_Muon_v6","HLT_Dimuon0_Upsilon_Muon_v5","HLT_Dimuon0_Upsilon_Muon_v4","HLT_Dimuon0_Upsilon_Muon_v3","HLT_Dimuon0_Upsilon_Muon_v2","HLT_Dimuon0_Upsilon_Muon_v1"),  
     FiltersForUpsilon = cms.untracked.vstring("hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon","hltVertexmumuFilterUpsilonMuon"),




     Chi2NDF_Track =  cms.untracked.double(15.0)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Run2012_FourMuon_ntuple.root')
                                   )
# turn off MC matching for the process
from PhysicsTools.PatAlgos.tools.coreTools import *
removeMCMatching(process, ['All'], outputModules = [])
process.patDefaultSequence.remove(process.patJetCorrFactors)
process.patDefaultSequence.remove(process.patJetCharge)
process.patDefaultSequence.remove(process.patJetPartonMatch)
process.patDefaultSequence.remove(process.patJetGenJetMatch)
process.patDefaultSequence.remove(process.patJetPartons)
#process.patDefaultSequence.remove(process.patJetPartonAssociation)
process.patDefaultSequence.remove(process.patJetFlavourAssociation)
process.patDefaultSequence.remove(process.patJets)
#process.patDefaultSequence.remove(process.metJESCorAK5CaloJet)
#process.patDefaultSequence.remove(process.metJESCorAK5CaloJetMuons)
process.patDefaultSequence.remove(process.patMETs)
process.patDefaultSequence.remove(process.selectedPatJets)
process.patDefaultSequence.remove(process.cleanPatJets)
process.patDefaultSequence.remove(process.countPatJets)
process.out = cms.OutputModule("PoolOutputModule",
        fileName = cms.untracked.string('onia2MuMuPAT.root'),
        outputCommands = cms.untracked.vstring('drop *',
            'keep patMuons_patMuonsWithTrigger_*_NTUPLE',    # All PAT muos including general tracks and matches to triggers
        )
)

process.filter = cms.Sequence(process.primaryVertexFilter+process.noscraping)
#process.patMuonSequence =(process.genMuons*process.patMuonsWithTriggerSequence)
#if not MC:
#    process.patMuonSequence.remove(process.genMuons)

## AF: replace EndPath with path
#process.ntup = cms.EndPath(process.filter*process.patDefaultSequence*process.patMuonsWithTriggerSequence*process.PATfilter*process.mkcands)
#process.ntup = cms.Path(process.filter*process.patDefaultSequence*process.patMuonsWithTriggerSequence*process.PATfilter*process.mkcands)
#process.ntup = cms.Path(process.filter*process.patDefaultSequence*process.patMuonsWithTriggerSequence*process.mkcands)
#process.ntup = cms.Path(process.filter*process.patDefaultSequence*process.patMuonsWithTriggerSequence*process.mkcands*process.lumiProducer)
process.ntup = cms.Path(process.filter*process.patDefaultSequence*process.patMuonsWithTriggerSequence*process.mkcands)


#process.e = cms.EndPath(process.out)
process.schedule = cms.Schedule(process.ntup)
#,process.e )

