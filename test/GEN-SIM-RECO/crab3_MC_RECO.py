from WMCore.Configuration import Configuration
config = Configuration()

config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'Step2_H02JpsiMuMu'



config.section_('JobType')
config.JobType.psetName = 'Step2_JpsiJpsi_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_RECO.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['Step2_JpsiMuMu_RECO.root']


config.section_('Data')
config.Data.inputDataset = '/GEN-SIM-H02JpsiMuMu/sdurgut-crab_H02JpsiMuMu-f5a46f036e3f9a12f585078c9b2fa7b7/USER'
#config.Data.outputPrimaryDataset = 'GEN-SIM-RECO-H02UpsMuMu_ArtifactTest'
#config.Data.inputDBS = 'global'
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

#NJOBS = 500  # This is not a configuration parameter, but an auxiliary variable that we use in the next line.
config.Data.totalUnits = 500
config.Data.outLFNDirBase = '/store/user/sdurgut/FourMuon/GEN-SIM-RECO-H02JpsiMuMu'
#config.Data.lumiMask = 'Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON_MuonPhys.txt'
config.Data.publication = True
#config.Data.outputDatasetTag = 'GEN-SIM-H02UpsMuMu_ArtifactTest'


config.section_('User')


config.section_('Site')
# config.Site.storageSite = 'cmseos.fnal.gov'
# config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.storageSite = 'T3_US_FNALLPC' 

