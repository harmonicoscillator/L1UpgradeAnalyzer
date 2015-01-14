import FWCore.ParameterSet.Config as cms

process = cms.Process('L1')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)


# Output definition

process.output = cms.OutputModule(
    "PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = cms.untracked.vstring("keep *",
					   "drop *_mix_*_*"),
    fileName = cms.untracked.string('L1T_EDM.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    )
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')

# enable debug message logging for our modules
process.MessageLogger = cms.Service(
    "MessageLogger",
    threshold  = cms.untracked.string('WARNING'),
    categories = cms.untracked.vstring('*'),
#    l1t   = cms.untracked.PSet(
#	threshold  = cms.untracked.string('DEBUG')
#    ),
#    debugModules = cms.untracked.vstring('*'),
#        'stage1Raw',
#        'caloStage1Digis'
#    ),
#    cout = cms.untracked.PSet(
#    )
)

# TTree output file
process.load("CommonTools.UtilAlgos.TFileService_cfi")
process.TFileService.fileName = cms.string('l1t.root')


# user stuff

# raw data from MP card
process.load('EventFilter.L1TRawToDigi.stage1MP7BufferRaw_cfi')
process.stage1Raw.nFramesOffset    = cms.untracked.int32(0)
process.stage1Raw.nFramesLatency   = cms.untracked.int32(90)
process.stage1Raw.rxFile = cms.untracked.string("/afs/cern.ch/user/r/richard/EMULATOR/CMSSW_7_3_0_pre2/src/EventFilter/L1TRawToDigi/test/input/physicsevent/rx_summary.txt")
process.stage1Raw.txFile = cms.untracked.string("/afs/cern.ch/user/r/richard/EMULATOR/CMSSW_7_3_0_pre2/src/EventFilter/L1TRawToDigi/test/input/physicsevent/tx_summary.txt")
#process.stage1Raw.rxFile = cms.untracked.string("/afs/cern.ch/work/r/richard/public/mp7dumps/test1_1s_ECALcstPattern/datasummary_832/rx_summary.txt")
#process.stage1Raw.txFile = cms.untracked.string("/afs/cern.ch/work/r/richard/public/mp7dumps/test1_1s_ECALcstPattern/datasummary_832/tx_summary.txt")



# dump raw data
process.dumpRaw = cms.EDAnalyzer(
    "DumpFEDRawDataProduct",
    label = cms.untracked.string("stage1Raw"),
    feds = cms.untracked.vint32 ( 1300 ),
    dumpPayload = cms.untracked.bool ( True )
)

# raw to digi
# I think this will unpack both the rct digis and the Layer 2 digis
process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')
process.caloStage1Digis.InputLabel = cms.InputTag('stage1Raw')

process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff')
process.simCaloStage1Digis.FirmwareVersion = cms.uint32(3)
process.simCaloStage1Digis.CaloRegions = cms.InputTag("caloStage1Digis")
process.simCaloStage1Digis.CaloEmCands = cms.InputTag("caloStage1Digis")

process.L1JetComparator = cms.EDAnalyzer("l1t::L1JetComparator",
                                         JetCollection1 = cms.InputTag("caloStage1Digis"),
                                         JetCollection2 = cms.InputTag("simCaloStage1Digis"),
                                         RegionCollection = cms.InputTag("caloStage1Digis")
                                         )


# Path and EndPath definitions
process.path = cms.Path(
    process.stage1Raw
    #+process.dumpRaw
    +process.caloStage1Digis
    +process.simCaloStage1Digis
    +process.L1JetComparator
)

process.out = cms.EndPath(
    process.output
)
