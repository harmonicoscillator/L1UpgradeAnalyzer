import FWCore.ParameterSet.Config as cms

process = cms.Process('L1TEMULATION')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
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
#"/store/user/mnguyen/Hydjet_Quenched_MinBias_5020GeV/HydjetMB_740pre8_MCHI2_74_V3_53XBS_DIGI-RAW/6da45e4e90741bc03dbd9aec5f36c050/step2_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_100_1_nRy.root"
                                "file:/afs/cern.ch/work/g/ginnocen/public/FilesForUnpackers/skim_10_1_wd2.root"

                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag
process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'auto:run2_mc_HIon')

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')
# Use PPFromRaw because it grabs the MC info correctly, then change parameters
# to match the HI emulator.
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
process.load('L1Trigger.L1TCalorimeter.caloStage1RCTLuts_cff')
process.caloStage1Params.jetSeedThreshold = cms.double(0.)
process.RCTConfigProducers.eicIsolationThreshold = cms.uint32(7)
process.RCTConfigProducers.hOeCut = cms.double(999)
process.RCTConfigProducers.eMinForHoECut = cms.double(999)
process.RCTConfigProducers.eMaxForHoECut = cms.double(999)
process.RCTConfigProducers.hMinForHoECut = cms.double(999)
process.RCTConfigProducers.eMinForFGCut = cms.double(999)


process.p1 = cms.Path(
    process.L1TCaloStage1_PPFromRaw
)

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer.root")
)

process.L1UpgradeAnalyzer = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                           InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                           InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                           InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                           InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                           InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                           legacyRCTDigis = cms.InputTag("simRctDigis")
)

process.p2 = cms.Path(process.L1UpgradeAnalyzer)

process.schedule = cms.Schedule(
    process.p1, process.p2
    )
