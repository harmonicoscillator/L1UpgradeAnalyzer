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
        'file:/afs/cern.ch/user/g/ginnocen/public/MP7testsP5/l1tCalo_2015_EDM.root'
    )
)

process.options = cms.untracked.PSet()

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("L1UpgradeAnalyzer_rct.root")
)

process.L1UpgradeAnalyzer = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                           InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                           InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                           InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                           InputLayer1Collection = cms.InputTag("None"),
                                           InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                           legacyRCTDigis = cms.InputTag("caloStage1Digis")
)

process.p = cms.Path(process.L1UpgradeAnalyzer)
