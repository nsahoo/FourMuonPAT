from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'Run2012D'



config.section_('JobType')
config.JobType.psetName = 'runFourMuonPAT_data_Run2012ABCDCMSSW53X.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['Run2012_FourMuon_ntuple.root']


config.section_('Data')
config.Data.inputDataset = '/MuOnia/Run2012D-22Jan2013-v1/AOD'
config.Data.unitsPerJob = 10
config.Data.splitting = 'LumiBased'
config.Data.outLFNDirBase = '/store/group/lpcbphy/noreplica/sdurgut/CrossSection/FourMuonNtuple'
config.Data.lumiMask = 'Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON_MuonPhys.txt'


config.section_('User')


config.section_('Site')
# config.Site.storageSite = 'cmseos.fnal.gov'
# config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.storageSite = 'T3_US_FNALLPC' 

