# Auto generated configuration file
# using: 
# Revision: 1.381.2.13 
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/EightTeV/PYTHIA6_Etab2JpsiJpsi_8TeV_cff.py -s GEN,SIM --conditions START53_V19::All --datatier GEN-SIM --pileup 2012_Summer_50ns_PoissonOOTPU --datamix NODATAMIXER --eventcontent RAWSIM --no_exec -n 100
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
#process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.destinations = ['cerr']
process.MessageLogger.statistics = []
process.MessageLogger.fwkJobReports = []
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet(
	input = cms.untracked.int32(100)
#	output = cms.untracked.int32(10)
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
	#outputCommands = process.RAWSIMEventContent.outputCommands,
	outputCommands = process.RAWSIMEventContent.outputCommands,
	#outputCommands = cms.untracked.vstring("keep edmHepMCProduct_source_*_*",
	fileName = cms.untracked.string('H0toJpsiMuMu_GEN-SIM.root'),
	
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

process.etafilter = cms.EDFilter("PythiaFilter",
	MaxEta = cms.untracked.double(9999.0),
	MinEta = cms.untracked.double(-9999.0),
 #   ParticleID = cms.untracked.int32(10551)
	ParticleID = cms.untracked.int32(35)
	#ParticleID = cms.untracked.int32(551)
)

'''
process.jpsifilter = cms.EDFilter("PythiaDauVFilter",
	MotherID = cms.untracked.int32(10551),
	verbose = cms.untracked.int32(0),
	ParticleID = cms.untracked.int32(443),
	MaxEta = cms.untracked.vdouble(2.6, 2.6),
	MinEta = cms.untracked.vdouble(-2.6, -2.6),
	DaughterIDs = cms.untracked.vint32(13, -13),
	MinPt = cms.untracked.vdouble(1.8, 1.8),
#    MinP = cms.untracked.vdouble(2.5, 2.5),
	NumberDaughters = cms.untracked.int32(2)
)
'''

from Configuration.Generator.PythiaUESettings_cfi import *

process.generator = cms.EDFilter("Pythia8GeneratorFilter",

	#################################FSR  added by Suleyman################################
			ExternalDecays = cms.PSet(
				Photospp355 = cms.untracked.PSet(
					parameterSets = cms.vstring("setExponentiation","setInfraredCutOff","setMomentumConservationThreshold"),
				setExponentiation = cms.bool(True),
				setInfraredCutOff = cms.double(0.00011),
				setMomentumConservationThreshold = cms.double(20.0) # 0.5GeV
				),
				parameterSets = cms.vstring( "Photospp355")
			),

	UseExternalGenerators = cms.untracked.bool(True),
	################################################################################################

	pythiaHepMCVerbosity = cms.untracked.bool(False),
	maxEventsToPrint = cms.untracked.int32(1),
	pythiaPylistVerbosity = cms.untracked.int32(1),
	displayPythiaCards = cms.untracked.bool(False),
	comEnergy = cms.double(8000.0),
	PythiaParameters = cms.PSet(
		pythiaUESettingsBlock,
		pythiaEtab = cms.vstring(
 #	'Bottomonium:gg2QQbar[3S1(1)]g = on', #Upsilon(1S) Process
# 	'Bottomonium:gg2QQbar[3P0(1)]g = on ', #Turns on Chi_0b Process(10551) 
#	'Bottomonium:qg2QQbar[3P0(1)]q = on', (3=2S+1, P=L, 0 = J(Total Angular Mom.), 1=Color)			    
#	'Bottomonium:qqbar2QQbar[3P0(1)]g = on',
#	'10551:addChannel 1 1.00 100 443 443', #Chi_0b -> JpsiJpsi
#       '10551:m0 = 8.',
#	'10551:mMin = 6.0',
#	'10551:mMax = 9.5',
#	'10551:mWidth = 4',
#	'10551:oneChannel = 1 1.00 100 443 223',

#	' Bottomonium:gg2QQbar[3P1(1)]g = on', #Turns on (chi_1b) Process (20551)
#	'Bottomonium:qg2QQbar[3P1(1)]q = on',
#	'Bottomonium:qqbar2QQbar[3P1(1)]g = on',

#	'Bottomonium:gg2QQbar[3P2(1)]g = on', #Turns on (chi_2b) Process(555)
#	'Bottomonium:qg2QQbar[3P2(1)]q = on',
#	'Bottomonium:qqbar2QQbar[3P2(1)]g = on',

#	'Bottomonium:gg2QQbar[3S1(8)]g = on',
#	'Charmonium:gg2QQbar[3P0(1)]g = on',
	 

#	'Bottomonium:qg2QQbar[1S0(8)]q = on',
#	'Bottomonium:qqbar2QQbar[1S0(8)]g = on',
	 'Higgs:useBSM = on',
		'HiggsBSM:gg2H2 = on',
		#'HiggsBSM:ffbar2H2 = on',
		'HiggsH2:coup2d = 10.0',
		'HiggsH2:coup2u = 10.0',
		'HiggsH2:coup2Z = 0.0',
		'HiggsH2:coup2W = 0.0',
		'HiggsA3:coup2H2Z = 0.0',
		'HiggsH2:coup2A3A3 = 0.0',
		'HiggsH2:coup2H1H1 = 0.0',
		'443:onMode = off',
		'443:onIfMatch 13 13',
	'333:onMode = off',
	'333:onIfMatch 13 13',
	#'223:onMode = off',
	#'223:onIfMatch 13 13',
	'553:onMode = off',
	'553:onIfMatch 13 13',
############### For Floating Mass Distribution#######
#        '35:mMin = 15', 
#        '35:mMax = 25',
#        '35:m0   = 23.  ! Higgs mass',
#	'35:mWidth = 10 !Higgs Width',
############# For Fixed Mass Distribution#############
		#'35:mMin = 0',
		'35:mMax = 25.0',
		'35:mMin = 0.0',
		'35:m0   = 18.5',
		'35:mWidth = 0.0',
#        '35:addChannel 1 1.00 100 443 443',
		'35:addChannel 1 1.00 100 13 -13 443',
#        '35:addChannel 1 1.00 100 443 333',
#        '35:addChannel 1 1.00 100 443 223',
#        '35:addChannel 1 1.00 100 443 553',
#  	 '35:addChannel 1 1.00 100 333 553',
#        '35:addChannel 1 1.00 100 223 553',
		'35:onMode = off',
		#'35:onIfMatch 443 333'), ##Jpsi Phi decay channel!
		'35:onIfMatch 13 -13 443'), ## Y(1S) mumu
#        '35:onIfMatch 443 443'), ##Jpsi Jpsi decay channel!
	  #  '35:onIfMatch 443 223'), ##Jpsi Omega decay channel!
	   # '35:onIfMatch 443 553'), ##Jpsi Upsilon decay channel!
	  #  '35:onIfMatch 333 553'), ##Phi Upsilon decay channel!
	   # '35:onIfMatch 223 553'), ##Omega Upsilon decay channel!
		# This is a vector of ParameterSet names to be read, in this order
		parameterSets = cms.vstring(
			'pythiaEtab')
	)
)


#process.ProductionFilterSequence = cms.Sequence(process.generator+process.etafilter+process.jpsifilter)
process.ProductionFilterSequence = cms.Sequence(process.generator+process.etafilter)

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


