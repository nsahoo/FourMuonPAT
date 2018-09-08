# Auto generated configuration file
# using: 
# Revision: 1.381.2.13 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Step2_UpsilonPhi --step DIGI,L1,DIGI2RAW,HLT:GRun,RAW2DIGI,L1Reco,RECO --conditions START52_V5::All --datamix NODATAMIXER --eventcontent RECOSIM --datatier GEN-SIM-RECO --filein file:EtbVVGen.root --no_exec -n 100
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
	#'file:/uscmst1b_scratch/lpc1/3DayLifetime/mhaytmyr/EtabVV_MC/EtabVVPsi2sPhi_GEN-SIM_RUNNO.root'
#	'file:/eos/uscms/store/user/mhaytmyr/Etab_GEN-SIM/EtabVVJpsiJpsi_GEN-SIM_RUNNO.root'
#	'file:/eos/uscms/store/user/mhaytmyr/Etab_GEN-SIM/H0ToJpsiJpsi/EtabVVJpsiJpsi_GEN-SIM_RUNNO.root'
#	'file:/eos/uscms/store/user/lpcbphy/Maksat/Etab_GEN_SIM/EtabVVJpsiJpsi_GEN-SIM_RUNNO.root'
	#'file:/eos/uscms/store/user/lpcbphy/Suleyman/FourMuon/MC/GEN_SIM_Higgs_Upsilon1SMuMu_NoEtaCut/FILENAME'
	'root://cmsxrootd.fnal.gov//store/user/sdurgut/FourMuon/GEN-SIM-H02UpsMuMu_ArtifactTest/FILENAME'
#	'file:EtabVVJpsiJpsi_GEN-SIM_RUNNO.root'
	)
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.381.2.13 $'),
    annotation = cms.untracked.string('Step2_UpsilonPhi nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    #fileName = cms.untracked.string('Step2_JpsiJpsiMContinues_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiPhiMContinues_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiOmegaMContinues_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiUpsilonMContinues_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_PhiUpsilonMContinues_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_OmegaUpsilonMContinues_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_OmegaUpsilonM18p5_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_PhiUpsilonM18p5_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiUpsilonM18p5_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiOmegaM18p5_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiPhiM18p5_RECO_RUNNO.root'),
    #fileName = cms.untracked.string('Step2_JpsiJpsiM18p5_RECO_RUNNO.root'),
    fileName = cms.untracked.string('Step2_Upsilon1SMuMu_RECO_RUNNO.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RECO')
    )
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V18::All', '')
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup_GRun', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step])

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions
