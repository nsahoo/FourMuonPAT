import FWCore.ParameterSet.Config as cms

import FWCore.ParameterSet.Config as cms

process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mix_2012_Summer_50ns_PoissonOOTPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic8TeVCollision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.destinations = ['cerr']
process.MessageLogger.statistics = []
process.MessageLogger.fwkJobReports = []
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(5000)
)

# Input source
process.source = cms.Source("EmptySource")


#GRandom Number Generator
from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
randHelper = RandomNumberServiceHelper(process.RandomNumberGeneratorService)
randHelper.populate()




process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
	version = cms.untracked.string('$Revision: 1.381.2.13 $'),
	annotation = cms.untracked.string('Configuration/GenProduction/python/EightTeV/PYTHIA6_Etab2JpsiJpsi_8TeV_cff.py nevts:100'),
	name = cms.untracked.string('PyReleaseValidation')
)

# Output definition
process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
	splitLevel = cms.untracked.int32(0),
	eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
	outputCommands = process.RAWSIMEventContent.outputCommands,
	fileName = cms.untracked.string('FourMu_BBarMC.root'),
	dataset = cms.untracked.PSet(
		filterName = cms.untracked.string(''),
		dataTier = cms.untracked.string('GEN-SIM')
	),
	SelectEvents = cms.untracked.PSet(
		SelectEvents = cms.vstring('generation_step')
	)
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V19::All')
process.GlobalTag = GlobalTag(process.GlobalTag, 'START53_V18::All','')


import pythia
pythia.readString("TimeShower:nGluonToQuark = 2")


from Configuration.Generator.PythiaUEZ2starSettings_cfi import *

process.generator = cms.EDFilter(
	"Pythia6GeneratorFilter",
	comEnergy = cms.double(8000.0),
	crossSection = cms.untracked.double(48440000000),
	filterEfficiency = cms.untracked.double(5.2e-5),
	pythiaHepMCVerbosity = cms.untracked.bool(False),
	maxEventsToPrint = cms.untracked.int32(0),
	pythiaPylistVerbosity = cms.untracked.int32(0),
	ExternalDecays = cms.PSet(
	EvtGen = cms.untracked.PSet(
		operates_on_particles = cms.vint32(511,521,531,5122), # you can put here the list of particles (PDG IDs)
		use_default_decay = cms.untracked.bool(False),  # to generate a specific signal mode.
		decay_table = cms.FileInPath('GeneratorInterface/ExternalDecays/data/DECAY_NOLONGLIFE.DEC'),
		particle_property_file = cms.FileInPath('GeneratorInterface/ExternalDecays/data/evt.pdl'),
		user_decay_file = cms.FileInPath('GeneratorInterface/ExternalDecays/data/myBBar.dec'),
		list_forced_decays = cms.vstring() #notice we are actually replacing the decay table to force hadrons decaying to muons.
		),
		parameterSets = cms.vstring('EvtGen')
	),
	PythiaParameters = cms.PSet(
		pythiaUESettingsBlock,
		bbbarSettings = cms.vstring('MSEL = 5'), # for b-bbar 
		parameterSets = cms.vstring(
		'pythiaUESettings',
		'bbbarSettings')

	)
)

process.FourMuonFilter = cms.EDFilter("FourLepFilter", # require 4-mu in the final state
		MinPt = cms.untracked.double(2.0),
		MaxPt = cms.untracked.double(4000.0),
		MaxEta = cms.untracked.double(2.5),
		MinEta = cms.untracked.double(0.),
		ParticleID = cms.untracked.int32(13)
)

process.TwoMuonFilter = cms.EDFilter("MCParticlePairFilter",  # require 2-mu mass to be 8.5 - 11.5 GeV
		Status = cms.untracked.vint32(1,1),
		MinPt = cms.untracked.vdouble(2.0,2.0),
		MaxPt = cms.untracked.vdouble(4000.0,4000.0),
		MaxEta = cms.untracked.vdouble( 2.5,2.5),
		MinEta = cms.untracked.vdouble(-2.5,-2.5),
		ParticleID1 = cms.untracked.vint32(13),
		ParticleID2 = cms.untracked.vint32(-13),
		MinInvMass = cms.untracked.double(8.5),
		MaxInvMass = cms.untracked.double(11.5),
)

process.BBbarFilter = cms.EDFilter("myBBbarFilter",
	#MinPt = cms.untracked.double(2.0),
	#MaxPt = cms.untracked.double(4000.0),
	#MaxEta = cms.untracked.double(2.5),
	#MinEta = cms.untracked.double(0.),
	ParticleID = cms.untracked.int32(13)
)

process.ProductionFilterSequence = cms.Sequence(process.generator*process.FourMuonFilter*process.TwoMuonFilter*process.BBbarFilter)



# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)

process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
#process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.endjob_step,process.RAWSIMoutput_step)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 


