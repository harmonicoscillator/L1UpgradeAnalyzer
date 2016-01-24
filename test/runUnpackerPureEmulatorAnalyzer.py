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
    input = cms.untracked.int32(1)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
                                #"/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_13_HI/GEN-SIM-DIGI-RAW-HLTDEBUG/PU_75X_mcRun2_HeavyIon_v12-v1/00000/002B568D-54B5-E511-90DB-00266CFAE074.root",
                                #"/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_13_HI/GEN-SIM-DIGI-RAW-HLTDEBUG/PU_75X_mcRun2_HeavyIon_v12-v1/00000/20FA8A7F-52B5-E511-9319-7845C4FC3893.root",
                                #"/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_13_HI/GEN-SIM-DIGI-RAW-HLTDEBUG/PU_75X_mcRun2_HeavyIon_v12-v1/00000/3E322ED5-53B5-E511-A3BD-00266CF268B8.root",
                                #"/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_13_HI/GEN-SIM-DIGI-RAW-HLTDEBUG/PU_75X_mcRun2_HeavyIon_v12-v1/00000/90D27128-52B5-E511-A90E-7845C4FC399E.root"
                                "/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_5020GeV/GEN-SIM-DIGI-RAW-HLTDEBUG/75X_mcRun2_asymptotic_ppAt5TeV_v3-v1/00000/063E58E3-4CB5-E511-B142-7845C4FC3B8A.root",
                                "/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_5020GeV/GEN-SIM-DIGI-RAW-HLTDEBUG/75X_mcRun2_asymptotic_ppAt5TeV_v3-v1/00000/80F17F87-4EB5-E511-99F5-3417EBE528B2.root",
                                "/store/relval/CMSSW_7_5_8_patch2/RelValPhotonJets_Pt_10_5020GeV/GEN-SIM-DIGI-RAW-HLTDEBUG/75X_mcRun2_asymptotic_ppAt5TeV_v3-v1/00000/F0C3C7CB-4DB5-E511-A423-001D09FDD80D.root"

                            )
                            )

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
# recordOverrides = { ('L1TCaloParamsRcd', None) : ('L1TCaloParams_collisions_HI_v0_mc', None) }
# process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_HeavyIon_v12', recordOverrides)
# process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_mcRun2_asymptotic_ppAt5TeV_v3', '')

#process.load('L1Trigger.L1TCalorimeter.caloConfigStage1PP_cfi')
#process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_cff')
#process.load('L1Trigger.L1TCalorimeter.caloStage1Params_cfi')
#process.load('L1Trigger.L1TCalorimeter.caloStage1Params_HI_cfi')
#process.caloStage1Params.minimumBiasThresholds = cms.vint32(1,1,2,2)

process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
from L1Trigger.Configuration.SimL1Emulator_cff import simRctDigis
process.simRctDigis = simRctDigis
process.simRctDigis.ecalDigis = cms.VInputTag( cms.InputTag( 'ecalDigis:EcalTriggerPrimitives' ) )
#process.simRctDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'simHcalTriggerPrimitiveDigis' ) )
process.simRctDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'hcalDigis' ) )

#process.simRctUpgradeFormatDigis.emTag = cms.InputTag("caloStage1Digis")
#process.simRctUpgradeFormatDigis.regionTag = cms.InputTag("caloStage1Digis")

process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')
#process.caloStage1Digis.InputLabel = cms.InputTag("rawDataRepacker")

process.l1cpr = cms.EDAnalyzer("L1TCaloParamsViewer")
process.l1RCTParametersTest = cms.EDAnalyzer("L1RCTParametersTester")

process.p1 = cms.Path(
    #process.l1cpr +
    process.l1RCTParametersTest 
#    process.ecalDigis +
#    process.hcalDigis +
#    process.caloStage1Digis +
#    process.simRctDigis +
#    process.simRctUpgradeFormatDigis +
#    process.simCaloStage1Digis +
#    process.simCaloStage1FinalDigis
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
                                         InputLayer1Collection = cms.InputTag("simRctUpgradeFormatDigis"),
                                         legacyRCTDigis = cms.InputTag("simRctDigis")
)

process.UnpackerResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                         InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                         InputLayer2HFBitCountCollection = cms.InputTag("caloStage1Digis:HFBitCounts"),
                                         InputLayer1Collection = cms.InputTag("None"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis")
)


process.p2 = cms.Path(process.EmulatorResults + process.UnpackerResults)


process.schedule = cms.Schedule(
    process.p1, process.p2
    )
