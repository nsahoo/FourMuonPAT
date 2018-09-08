from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'FourMu_BBarMC_test101'

config.section_('JobType')
config.JobType.psetName = 'FourMu_UpsilonInvMassCut_MSEL5_8TeV_pythia6MPI_off_FSRGSplit_off_BtoJpsi_off_ISRGsplitwithinputbPDF_off.py'
config.JobType.pluginName = 'PrivateMC'
config.JobType.outputFiles = ['FourMu_BBarMC.root']

config.section_('Data')
config.Data.inputDataset = ''
config.Data.outputPrimaryDataset = 'GEN-SIM-FourMu-BBarMC'
config.Data.splitting = 'EventBased'
config.Data.unitsPerJob = 10000000
config.JobType.eventsPerLumi = 1000000

NJOBS = 3000  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.outLFNDirBase = '/store/user/sdurgut/BBbarMC'
#config.Data.lumiMask = 'Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON_MuonPhys.txt'
config.Data.publication = True
config.Data.outputDatasetTag = 'GEN-SIM-BBbarMC_Test101'

config.section_('User')

config.section_('Site')
# config.Site.storageSite = 'cmseos.fnal.gov'
# config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.storageSite = 'T3_US_FNALLPC' 
