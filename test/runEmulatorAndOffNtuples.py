import FWCore.ParameterSet.Config as cms

process = cms.Process('L1TEMULATION')

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')

process.load('FWCore.MessageService.MessageLogger_cfi')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
                                #"file:/afs/cern.ch/work/g/ginnocen/public/skim_10_1_wd2.root"
                                "file:/export/d00/scratch/luck/skim_10_1_wd2.root"
                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'POSTLS161_V12::All', '')

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1PP_cfi')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')

from L1Trigger.Configuration.SimL1Emulator_cff import simGtDigis
process.simGtDigis = simGtDigis.clone()
process.simGtDigis.GmtInputTag = 'simGmtDigis'
process.simGtDigis.GctInputTag = 'simCaloStage1LegacyFormatDigis'
process.simGtDigis.TechnicalTriggersInputTags = cms.VInputTag( )

process.l1extraParticles = process.l1ExtraLayer2.clone()

process.ReEmulL1 = cms.Path(process.L1TCaloStage1_PPFromRaw +
                            process.simGtDigis +
                            process.l1extraParticles)
process.schedule = cms.Schedule(process.ReEmulL1)

from L1Trigger.L1TNtuples.customiseL1Ntuple import L1NtupleRAW
process = L1NtupleRAW(process)

process.l1NtupleProducer.gmtSource            = cms.InputTag("none")
process.l1NtupleProducer.gtSource             = cms.InputTag("simGtDigis")
process.l1NtupleProducer.gctCentralJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","cenJets")
process.l1NtupleProducer.gctNonIsoEmSource    = cms.InputTag("simCaloStage1LegacyFormatDigis","nonIsoEm")
process.l1NtupleProducer.gctForwardJetsSource = cms.InputTag("simCaloStage1LegacyFormatDigis","forJets")
process.l1NtupleProducer.gctIsoEmSource       = cms.InputTag("simCaloStage1LegacyFormatDigis","isoEm")
process.l1NtupleProducer.gctEnergySumsSource  = cms.InputTag("simCaloStage1LegacyFormatDigis","")
process.l1NtupleProducer.gctTauJetsSource     = cms.InputTag("simCaloStage1LegacyFormatDigis","tauJets")
process.l1NtupleProducer.gctIsoTauJetsSource  = cms.InputTag("simCaloStage1LegacyFormatDigis","isoTauJets")
