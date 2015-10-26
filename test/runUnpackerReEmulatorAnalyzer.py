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
    input = cms.untracked.int32(-1)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
                                #"file:/afs/cern.ch/user/r/richard/EMULATOR/HI_TESTING/txt_unpacking/CMSSW_7_5_2/src/EventFilter/L1TRawToDigi/utils/l1tCalo_2015_EDM.root"
                                #"file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/l1tCalo_EDM.root"
                                #"file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/l1tCalo_EDM_258158.root"
                                #"file:/afs/cern.ch/user/r/richard/EMULATOR/HI_TESTING/txt_unpacking/CMSSW_7_5_2/src/EventFilter/L1TRawToDigi/utils/test7oct4PM_100HICentralEvents.root"
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_258694/l1tCalo_EDM_258694_0.root',
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_258694/l1tCalo_EDM_258694_1.root',
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_258694/l1tCalo_EDM_258694_2.root',
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_258694/l1tCalo_EDM_258694_3.root',
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_258694/l1tCalo_EDM_258694_v2.root'
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_259324/run259324_ls0001_streamPhysicsEGammaCommissioning_StorageManager.dat_Digis_numEvent10000.root'
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_259352/l1tCalo_EDM_259352.root'
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_259637/l1tCalo_EDM_259637.root'
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_259637_centralityMismatches_unpacked.root'
                                #'file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_259818/RUN_259818_unpacked.root'
                                "file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/RUN_259818/run259818EgammaMismatches_100.root"
                            )
                            )

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')

### nominal
### PUS mask
#process.caloStage1Params.jetRegionMask = cms.int32(0b0000100000000000010000)
process.caloStage1Params.jetRegionMask = cms.int32(0)
### EG 'iso' (eta) mask
process.caloStage1Params.egEtaCut = cms.int32(0b0000001111111111000000)
### Single track eta mask
process.caloStage1Params.tauRegionMask = cms.int32(0b1111111100000011111111)
### Centrality eta mask
process.caloStage1Params.centralityRegionMask = cms.int32(0b0000111111111111110000)
### jet seed threshold for 3x3 step of jet finding
process.caloStage1Params.jetSeedThreshold = cms.double(0)
### HTT settings (this won't match anyway yet)
process.caloStage1Params.etSumEtThreshold        = cms.vdouble(0., 7.) #ET, HT


process.simRctUpgradeFormatDigis.emTag = cms.InputTag("caloStage1Digis")
process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("caloStage1Digis")

process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')

process.p1 = cms.Path(
    process.caloStage1Digis +
    process.simRctUpgradeFormatDigis +
    process.simCaloStage1Digis +
    process.simCaloStage1FinalDigis
    )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UnpackedReEmulator_259818_v2.root")
)

process.EmulatorResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                         InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("None"),
                                         legacyRCTDigis = cms.InputTag("None")
)

process.UnpackerResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                         InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("None"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)


process.p2 = cms.Path(process.EmulatorResults + process.UnpackerResults)


process.schedule = cms.Schedule(
    process.p1, process.p2
    )
