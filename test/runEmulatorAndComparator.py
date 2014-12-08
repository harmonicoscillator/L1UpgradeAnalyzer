import FWCore.ParameterSet.Config as cms

process = cms.Process('L1TEMULATION')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')

# Select the Message Logger output you would like to see:
process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
#'root://xrootd.unl.edu//store/user/richard/Pyquen_Unquenched_AllQCDPhoton30_PhotonFilter35GeV_eta3_TuneZ2_Hydjet1p8_2760GeV/AllQCDPhoton30_53X_RAW_v5/4a6cb19dc394a76eb728ac0977b9e992/PbPb_GENSIMRAW_100_1_Hlx.root'
#'root://xrootd.unl.edu//store/user/icali/HIHighPt/HIMinBiasUPC_Skim_HLT_HIJet55_v2/72e9032319e369ee7d3493bb45d1ee7d/SD_HIJet55_1001_1_f4s.root'
#'root://xrootd.unl.edu//store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_v2/35880fcf9fb9fd84b27cd1405e09ffd1/SD_MinBiasHI_1000_1_nOG.root'
"file:/afs/cern.ch/work/g/ginnocen/public/skim_10_1_wd2.root"
                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_P_V27A::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_LV1::All', '')
process.GlobalTag.connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG')
process.GlobalTag.globaltag = cms.string('POSTLS161_V12::All')

#process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
process.simCaloStage1Digis.FirmwareVersion = cms.uint32(3)

process.p1 = cms.Path(
    process.L1TCaloStage1_PPFromRaw
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1JetComparator.root")
)

process.L1JetComparator = cms.EDAnalyzer("l1t::L1JetComparator",
                                         JetCollection1 = cms.InputTag("simCaloStage1FinalDigis"),
                                         JetCollection2 = cms.InputTag("simCaloStage1Digis"),
                                         RegionCollection = cms.InputTag("simRctUpgradeFormatDigis")
                                         )

process.p2 = cms.Path(process.L1JetComparator)


process.schedule = cms.Schedule(
    process.p1, process.p2
    )
