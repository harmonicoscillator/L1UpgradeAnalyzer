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
                                #"file:/afs/cern.ch/user/r/richard/EMULATOR/HI_TESTING/txt_unpacking/CMSSW_7_5_2/src/EventFilter/L1TRawToDigi/utils/l1tCalo_2015_EDM.root"
                                "file:/afs/cern.ch/work/g/ginnocen/public/FirmwareTestsHI/edmfiles/l1tCalo_EDM_run258158_ls0341_streamExpress.root"
                            )
                            )

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run1_data', '')

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')

### mask 4 and 17
# process.caloStage1Params.regionPUSParams = cms.vdouble((0, 0, 0, 0,
#                                                         1, 0, 0, 0, 0, 0, 0,
#                                                         0, 0, 0, 0, 0, 0, 1,
#                                                         0, 0, 0, 0))

### no mask
process.caloStage1Params.regionPUSParams = cms.vdouble((0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0))


# # raw data from MP card
# process.load('EventFilter.L1TRawToDigi.stage1MP7BufferRaw_cfi')
# # pack into arrays
# latencies = [ 41, 0 ]
# offsets   = [ 0,  54 ]

# process.stage1Raw.nFramesPerEvent    = cms.untracked.int32(6)
# process.stage1Raw.nFramesOffset    = cms.untracked.vuint32(offsets)
# process.stage1Raw.nFramesLatency   = cms.untracked.vuint32(latencies)

# process.stage1Raw.rxFile = cms.untracked.string("/data/L1Ts1calo/ModifiedMP7Dumps/data_20150303_RCTInput_64H2TausEvents_fw2271/rx_summary_final.txt")
# process.stage1Raw.txFile = cms.untracked.string("/data/L1Ts1calo/ModifiedMP7Dumps/data_20150303_RCTInput_64H2TausEvents_fw2271/tx_summary_final.txt")

# # raw to digi
# # I think this will unpack both the rct digis and the Layer 2 digis
# process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')
# process.caloStage1Digis.InputLabel = cms.InputTag('stage1Raw')

#process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
#process.simCaloStage1Digis.FirmwareVersion = cms.uint32(3)
process.simRctUpgradeFormatDigis.emTag = cms.InputTag("caloStage1Digis")
process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("caloStage1Digis")

process.p1 = cms.Path(
    #process.stage1Raw +
    #process.caloStage1Digis +
    process.simRctUpgradeFormatDigis +
    process.simCaloStage1Digis +
    process.simCaloStage1FinalDigis
    )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpackedReEmulator.root")
)

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
