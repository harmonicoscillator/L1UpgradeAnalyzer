import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')

recordOverrides = { ('L1RCTParametersRcd', None) : ('L1RCTParametersRcd_L1TDevelCollisions_ExtendedScaleFactorsV4_HIDisabledFGHOE', None) }
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag
process.GlobalTag = customiseGlobalTag(process.GlobalTag, 'auto:run2_data', recordOverrides)
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")

process.source = cms.Source( "PoolSource",
    fileNames = cms.untracked.vstring(
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/FE492579-3273-E511-A753-02163E0146F8.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/04C7E49A-3273-E511-9994-02163E0141EC.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/143F6A65-3273-E511-A3D9-02163E011834.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/32062764-3273-E511-B1C3-02163E01422C.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/3E6F499A-3273-E511-A07B-02163E01424B.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/5295B07B-3273-E511-B9D5-02163E01452F.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/5862F676-3273-E511-8248-02163E0137F1.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/5A498671-3273-E511-A058-02163E011890.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/5EE4B39A-3273-E511-BFE5-02163E0141EC.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/723F3465-3273-E511-B52C-02163E013815.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/86F74965-3273-E511-906E-02163E011962.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/AC5B5264-3273-E511-85BD-02163E01430B.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/C4941A6E-3273-E511-AC70-02163E0128B4.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/CAF7EC64-3273-E511-A06A-02163E0146A5.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/D2E30175-3273-E511-A2BF-02163E011F6F.root',
        'root://eoscms//eos/cms/store/data/Run2015D/ZeroBias/RAW/v1/000/259/163/00000/FE73DC65-3273-E511-89D1-02163E011A96.root',
    )
)

# limit the number of events to be processed
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32( -1 )
)

# enable the TrigReport and TimeReport
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool( True ),
    #SkipEvent = cms.untracked.vstring('ProductNotFound')
)


# override the L1 menu from an Xml file
process.l1GtTriggerMenuXml = cms.ESProducer("L1GtTriggerMenuXmlProducer",
  TriggerMenuLuminosity = cms.string('startup'),
  DefXmlFile = cms.string('L1Menu_CollisionsHeavyIons2015.v3_KKHecked.xml'),
  VmeXmlFile = cms.string('')
)
process.L1GtTriggerMenuRcdSource = cms.ESSource("EmptyESSource",
  recordName = cms.string('L1GtTriggerMenuRcd'),
  iovIsRunNotTime = cms.bool(True),
  firstValid = cms.vuint32(1)
)
process.es_prefer_l1GtParameters = cms.ESPrefer('L1GtTriggerMenuXmlProducer','l1GtTriggerMenuXml')

process.load( 'Configuration.StandardSequences.RawToDigi_Data_cff' )
process.load( 'Configuration.StandardSequences.SimL1Emulator_cff' )
import L1Trigger.Configuration.L1Trigger_custom
#

# 2015 Run2 emulator
import L1Trigger.L1TCalorimeter.L1TCaloStage1_customForHLT
process = L1Trigger.L1TCalorimeter.L1TCaloStage1_customForHLT.customiseL1EmulatorFromRaw( process )

#
process = L1Trigger.Configuration.L1Trigger_custom.customiseResetPrescalesAndMasks( process )

process.SimL1Emulator_noMuons = cms.Sequence(process.hcalDigis+process.simHcalTriggerPrimitiveDigis+process.ecalDigis+process.simRctDigis+process.simRctUpgradeFormatDigis+process.simCaloStage1Digis+process.simCaloStage1FinalDigis+process.simCaloStage1LegacyFormatDigis+process.gtDigis+process.simGtDigis)
process.simGtDigis.GmtInputTag = cms.InputTag("gtDigis")
process.SimL1EmulatorPath = cms.Path(process.SimL1Emulator_noMuons)

process.hltL1GtTrigReport = cms.EDAnalyzer( "L1GtTrigReport",
    PrintVerbosity = cms.untracked.int32( 10 ),
    UseL1GlobalTriggerRecord = cms.bool( False ),
    PrintOutput = cms.untracked.int32( 3 ),
    L1GtRecordInputTag = cms.InputTag( "simGtDigis" )
)
process.hltTrigReport = cms.EDAnalyzer( "HLTrigReport",
    ReferencePath = cms.untracked.string( "HLTriggerFinalPath" ),
    ReferenceRate = cms.untracked.double( 100.0 ),
    serviceBy = cms.untracked.string( "never" ),
    resetBy = cms.untracked.string( "never" ),
    reportBy = cms.untracked.string( "job" ),
    HLTriggerResults = cms.InputTag( 'TriggerResults','','HLT' )
)
process.HLTAnalyzerEndpath = cms.EndPath( process.hltL1GtTrigReport + process.hltTrigReport )

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')

## zero the walls
process.caloStage1Params.regionPUSParams = cms.vdouble((0, 0, 0, 0,
                                                        1, 0, 0, 0, 0, 0, 0,
                                                        0, 0, 0, 0, 0, 0, 1,
                                                        0, 0, 0, 0))



process.load("HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi")
process.hltbitanalysis.HLTProcessName = cms.string('HLT')
process.hltbitanalysis.hltresults = cms.InputTag( 'TriggerResults','','HLT' )
process.hltbitanalysis.l1GtReadoutRecord = cms.InputTag('simGtDigis','','TEST')
process.hltbitanalysis.l1GctHFBitCounts = cms.InputTag('gctDigis','','TEST')
process.hltbitanalysis.l1GctHFRingSums = cms.InputTag('gctDigis','','TEST')
process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)
process.hltBitAnalysis = cms.EndPath(process.hltbitanalysis)
process.TFileService = cms.Service("TFileService",
                                   fileName=cms.string("openHLT.root"))

process.L1UpgradeAnalyzer = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                           InputLayer2Collection = cms.InputTag("simCaloStage1FinalDigis"),
                                           InputLayer2TauCollection = cms.InputTag("simCaloStage1FinalDigis:rlxTaus"),
                                           InputLayer2IsoTauCollection = cms.InputTag("simCaloStage1FinalDigis:isoTaus"),
                                           InputLayer2CaloSpareCollection = cms.InputTag("simCaloStage1FinalDigis:HFRingSums"),
                                           InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                           legacyRCTDigis = cms.InputTag("simRctDigis")
)
process.L1UpgradeAnalyzerPath = cms.EndPath(process.L1UpgradeAnalyzer)

process.schedule = cms.Schedule( *(process.SimL1EmulatorPath, process.HLTAnalyzerEndpath, process.hltBitAnalysis, process.L1UpgradeAnalyzerPath))
