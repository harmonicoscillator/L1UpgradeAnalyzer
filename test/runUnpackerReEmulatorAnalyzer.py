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
                                "/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/0037C0FF-2691-E511-855D-02163E011BC2.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/0E9ECE70-2891-E511-BC9C-02163E014133.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/146745D1-2791-E511-B7E7-02163E0141C0.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/30417A4C-2791-E511-97DA-02163E014186.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/4234B736-2891-E511-807E-02163E01458B.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/4ADEFD61-2791-E511-84E2-02163E01446D.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/5ECDE1DF-2691-E511-8D69-02163E014178.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/64D20DB8-2691-E511-A9E2-02163E014285.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/745CCFC5-2691-E511-B680-02163E014127.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/9826FCBD-2791-E511-889E-02163E01454A.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/B41CF1C5-2791-E511-9AEB-02163E014146.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/BC78B4DF-2791-E511-996A-02163E0141A9.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/D49A6CFD-2691-E511-8801-02163E0144E7.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/D6EC84E0-2791-E511-9BBF-02163E0141AE.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/DCDC2F20-2991-E511-82D5-02163E014644.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/E8E7122D-2791-E511-B2C7-02163E012148.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/FA37E0CB-2691-E511-B503-02163E014480.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/FAE312FC-2691-E511-B034-02163E0143C4.root",
"/store/express/Run2015E/HIExpressPhysics/FEVT/Express-v1/000/262/296/00000/FE06483E-2991-E511-A214-02163E014438.root",

                            )
                            )

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_cff')
process.load('L1Trigger.L1TCalorimeter.caloStage1Params_HI_cfi')
process.caloStage1Params.minimumBiasThresholds = cms.vint32(1,1,2,2)

process.simRctUpgradeFormatDigis.emTag = cms.InputTag("caloStage1Digis")
process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("caloStage1Digis")

process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')
process.caloStage1Digis.InputLabel = cms.InputTag("rawDataRepacker")

process.p1 = cms.Path(
    process.caloStage1Digis +
    process.simRctUpgradeFormatDigis +
    process.simCaloStage1Digis +
    process.simCaloStage1FinalDigis
    )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UnpackedReEmulator.root")
)

process.EmulatorResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                         InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                         InputLayer2HFBitCountCollection = cms.InputTag("simCaloStage1FinalDigis:HFBitCounts"),
                                         InputLayer1Collection = cms.InputTag("None"),
                                         legacyRCTDigis = cms.InputTag("None")
)

process.UnpackerResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                         InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                         InputLayer2HFBitCountCollection = cms.InputTag("caloStage1Digis:HFBitCounts"),
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)


process.p2 = cms.Path(process.EmulatorResults + process.UnpackerResults)


process.schedule = cms.Schedule(
    process.p1, process.p2
    )
