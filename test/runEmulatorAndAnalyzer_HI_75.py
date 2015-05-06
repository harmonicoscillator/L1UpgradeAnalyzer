## runEmulatorAndAnalyzer_HI.py
##
## Author: Alex Barbieri
##
## Warning: this only works in 7_5_0_pre1 and newer because of database/config changes
## set the booleans just below this statement to tailor behavior for HI data/mc

MONTECARLO=True

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
"/store/user/mnguyen/Hydjet_Quenched_MinBias_5020GeV/HydjetMB_740pre8_MCHI2_74_V3_53XBS_DIGI-RAW/6da45e4e90741bc03dbd9aec5f36c050/step2_DIGI_L1_DIGI2RAW_HLT_RAW2DIGI_L1Reco_100_1_nRy.root"

                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag as customiseGlobalTag
if MONTECARLO:
    process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'MCHI2_74_V3')
else:
    process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = 'GR_P_V27A')
process.GlobalTag.connect   = 'frontier://FrontierProd/CMS_CONDITIONS'

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')

if MONTECARLO:
    # HCAL TP hack for MC only
    process.load('L1Trigger.L1TCalorimeter.L1TRerunHCALTP_FromRaw_cff')
    process.ecalDigis.InputLabel = cms.InputTag("rawDataCollector")
    process.hcalDigis.InputLabel = cms.InputTag("rawDataCollector")
    process.simRctDigis.ecalDigis = cms.VInputTag( cms.InputTag( 'ecalDigis:EcalTriggerPrimitives' ) )
    process.simRctDigis.hcalDigis = cms.VInputTag( cms.InputTag( 'simHcalTriggerPrimitiveDigis' ) )

    process.L1TCaloStage1_HIFromRaw_MC = cms.Sequence(
        process.ecalDigis
        +process.L1TRerunHCALTP_FromRAW
        +process.simRctDigis
        +process.L1TCaloStage1
        +process.simGtDigis
    )

    process.p1 = cms.Path(
        process.L1TCaloStage1_HIFromRaw_MC
    )
else:
    process.p1 = cms.Path(
        process.L1TCaloStage1_HIFromRaw
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
