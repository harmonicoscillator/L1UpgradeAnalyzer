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
    input = cms.untracked.int32(-1)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
#'root://xrootd.unl.edu//store/user/richard/Pyquen_Unquenched_AllQCDPhoton30_PhotonFilter35GeV_eta3_TuneZ2_Hydjet1p8_2760GeV/AllQCDPhoton30_53X_RAW_v5/4a6cb19dc394a76eb728ac0977b9e992/PbPb_GENSIMRAW_100_1_Hlx.root'
#'root://xrootd.unl.edu//store/user/icali/HIHighPt/HIMinBiasUPC_Skim_HLT_HIJet55_v2/72e9032319e369ee7d3493bb45d1ee7d/SD_HIJet55_1001_1_f4s.root'
#'root://xrootd.unl.edu//store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_v2/35880fcf9fb9fd84b27cd1405e09ffd1/SD_MinBiasHI_1000_1_nOG.root'
#"file:/afs/cern.ch/work/g/ginnocen/public/skim_10_1_wd2.root"
#"file:/afs/cern.ch/user/g/ginnocen/public/MP7tests_data_260_1Jet75/l1tCalo_2015_EDM.root"
#"file:/afs/cern.ch/user/g/ginnocen/public/MP7tests_data_1Jet75/l1tCalo_2015_EDM.root"
"file:/afs/cern.ch/user/r/richard/TESTING/CMSSW_7_4_0_pre6/src/l1tCalo_2015_EDM.root"
                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_P_V27A::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_LV1::All', '')
process.GlobalTag.connect = cms.string('frontier://FrontierProd/CMS_COND_31X_GLOBALTAG')
process.GlobalTag.globaltag = cms.string('POSTLS161_V12::All')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')



# HCAL TP hack
#process.load('L1Trigger.L1TCalorimeter.L1TRerunHCALTP_FromRaw_cff')

#process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
process.simCaloStage1Digis.FirmwareVersion = cms.uint32(3)
process.simRctUpgradeFormatDigis.emTag = cms.InputTag("caloStage1Digis")
process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("caloStage1Digis")

#process.simRctDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'simHcalTriggerPrimitiveDigis' ) )

#process.caloStage1Params.jetSeedThreshold = cms.double(10.0);


#process.p1 = cms.Path(
#    process.L1TRerunHCALTP_FromRAW
#    +process.ecalDigis
#    +process.simRctDigis
#    +process.L1TCaloStage1
#    process.L1TCaloStage1_PPFromRaw
#)

process.p1 = cms.Path(
    process.simRctUpgradeFormatDigis +
    process.simCaloStage1Digis +
    process.simCaloStage1FinalDigis
    )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer.root")
)

# process.L1UpgradeAnalyzer = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
#                                            InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
#                                            InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
#                                            InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
#                                            InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
#                                            InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
#                                            legacyRCTDigis = cms.InputTag("caloStage1Digis")
# )

# process.p2 = cms.Path(process.L1UpgradeAnalyzer)

process.EmulatorResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                         InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)

process.UnpackerResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                         InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)


process.p2 = cms.Path(process.EmulatorResults + process.UnpackerResults)


process.schedule = cms.Schedule(
    process.p1, process.p2
    )
