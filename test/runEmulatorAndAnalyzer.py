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
    input = cms.untracked.int32(10)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
#'root://xrootd.unl.edu//store/user/richard/Pyquen_Unquenched_AllQCDPhoton30_PhotonFilter35GeV_eta3_TuneZ2_Hydjet1p8_2760GeV/AllQCDPhoton30_53X_RAW_v5/4a6cb19dc394a76eb728ac0977b9e992/PbPb_GENSIMRAW_100_1_Hlx.root'
#'root://xrootd.unl.edu//store/user/icali/HIHighPt/HIMinBiasUPC_Skim_HLT_HIJet55_v2/72e9032319e369ee7d3493bb45d1ee7d/SD_HIJet55_1001_1_f4s.root'
'root://xrootd.unl.edu//store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_v2/35880fcf9fb9fd84b27cd1405e09ffd1/SD_MinBiasHI_1000_1_nOG.root'
                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'GR_P_V27A::All', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'STARTHI53_LV1::All', '')

# HCAL TP hack
#process.load('L1Trigger.L1TCalorimeter.L1TRerunHCALTP_FromRaw_cff')

process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')

#process.simRctDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'simHcalTriggerPrimitiveDigis' ) )

#process.caloStage1Params.jetSeedThreshold = cms.double(10.0);


process.p1 = cms.Path(
#    process.L1TRerunHCALTP_FromRAW
#    +process.ecalDigis
#    +process.simRctDigis
#    +process.L1TCaloStage1
    process.L1TCaloStage1_HIFromRaw
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer.root")
)

process.L1UpgradeAnalyzer = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                           InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                           InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                           InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                           InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis")
)

process.p2 = cms.Path(process.L1UpgradeAnalyzer)


process.schedule = cms.Schedule(
    process.p1, process.p2
    )
