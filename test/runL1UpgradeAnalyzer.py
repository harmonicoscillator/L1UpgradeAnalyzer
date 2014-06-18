# runL1UpgradeAnalyzer.py
#
# Author: R. Alex Barbieri
#
#

import FWCore.ParameterSet.Config as cms

process = cms.Process('L1UpgradeAnalyzer')

process.load('Configuration.StandardSequences.Services_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring(
        'file:SimL1Emulator_Stage1_HI.root'
    )
)

process.options = cms.untracked.PSet()

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer.root")
)

process.L1UpgradeAnalyzer = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                           InputCollection = cms.InputTag("caloStage1FinalDigis")
)

process.p = cms.Path(process.L1UpgradeAnalyzer)
