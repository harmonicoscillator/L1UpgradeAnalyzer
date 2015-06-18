# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SingleElectronPt10_cfi.py -s GEN,SIM,DIGI,L1 --pileup=NoPileUp --geometry DB --conditions=auto:startup -n 1 --no_exec
import FWCore.ParameterSet.Config as cms


# options
import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing('analysis')
options.register('streamer',
                 0,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Use streamer file as input")
options.register('dumpRaw',
                 False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Print RAW data")
options.register('dumpDigis',
                 False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Print digis")
options.register('histos',
                 False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Produce standard histograms")
options.register('edm',
                 False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Produce EDM file")
options.register('RunAnalyzer',
                 False,
                 VarParsing.VarParsing.multiplicity.singleton,
                 VarParsing.VarParsing.varType.bool,
                 "Run Analyzer Unpacker")

                 
options.parseArguments()

process = cms.Process('Raw2Digi')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

# Input source
if (options.streamer) :
    process.source = cms.Source(
        "NewEventStreamFileReader",
        fileNames = cms.untracked.vstring (options.inputFiles)
    )
else :
    process.source = cms.Source (
        "PoolSource",
        fileNames = cms.untracked.vstring (options.inputFiles)
    )

# N events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)


process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)


# enable debug message logging for our modules
process.MessageLogger = cms.Service(
    "MessageLogger",
    threshold  = cms.untracked.string('INFO'),
    categories = cms.untracked.vstring('L1T', 'L1TCaloEvents'),
#    debugModules = cms.untracked.vstring(
#        'mp7BufferDumpToRaw',
#        'l1tDigis',
#        'caloStage1Digis'
#    )
)


# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:startup', '')


# dump raw data
process.dumpRaw = cms.EDAnalyzer( 
    "DumpFEDRawDataProduct",
    label = cms.untracked.string("rawDataCollector"),
    feds = cms.untracked.vint32 ( 1352 ),
    dumpPayload = cms.untracked.bool ( options.dumpRaw )
)

# raw to digi
process.load('EventFilter.L1TRawToDigi.caloStage1Digis_cfi')
process.caloStage1Digis.InputLabel = cms.InputTag('rawDataCollector')

# Path and EndPath definitions
process.path = cms.Path(
    process.dumpRaw
    +process.caloStage1Digis
)

if (options.RunAnalyzer):
   process.TFileService = cms.Service("TFileService",fileName = cms.string("L1UnpackedUnpacker.root"))
   process.UnpackerResults = cms.EDAnalyzer('l1t::L1UpgradeAnalyzer',
                                         InputLayer2Collection = cms.InputTag("caloStage1Digis"),
                                         InputLayer2TauCollection = cms.InputTag("caloStage1Digis:rlxTaus"),
                                         InputLayer2IsoTauCollection = cms.InputTag("caloStage1Digis:isoTaus"),
                                         InputLayer2CaloSpareCollection = cms.InputTag("caloStage1Digis:HFRingSums"),
                                         InputLayer1Collection = cms.InputTag("None"),
                                         legacyRCTDigis = cms.InputTag("caloStage1Digis"),
                                         FEDRawCollection = cms.InputTag("rawDataCollector")
   )
   process.myanalyzer = cms.Path(
   process.UnpackerResults
   )


# optional histograms & text dump
if (options.dumpDigis or options.histos):
    process.load("CommonTools.UtilAlgos.TFileService_cfi")
    #process.TFileService.fileName = cms.string('l1tCalo_histos.root')

    process.load('L1Trigger.L1TCalorimeter.l1tStage2CaloAnalyzer_cfi')
    process.l1tStage2CaloAnalyzer.towerToken   = cms.InputTag("None")
    process.l1tStage2CaloAnalyzer.clusterToken = cms.InputTag("None")
    process.l1tStage2CaloAnalyzer.mpEGToken    = cms.InputTag("None")
    process.l1tStage2CaloAnalyzer.mpJetToken   = cms.InputTag("None")
    process.l1tStage2CaloAnalyzer.mpTauToken   = cms.InputTag("None")
    process.l1tStage2CaloAnalyzer.mpEtSumToken = cms.InputTag("None")
    process.l1tStage2CaloAnalyzer.egToken      = cms.InputTag("caloStage1Digis")
    process.l1tStage2CaloAnalyzer.jetToken     = cms.InputTag("caloStage1Digis")
    process.l1tStage2CaloAnalyzer.tauToken     = cms.InputTag("caloStage1Digis","rlxTaus")
    process.l1tStage2CaloAnalyzer.etSumToken   = cms.InputTag("caloStage1Digis")
    process.l1tStage2CaloAnalyzer.doText       = cms.untracked.bool(options.dumpDigis)
    process.l1tStage2CaloAnalyzer.doHistos     = cms.untracked.bool(options.histos)

    process.analyzer = cms.Path(
        process.l1tStage2CaloAnalyzer
    )

    if (options.dumpDigis):
        process.load('L1Trigger.L1GctAnalyzer.dumpGctDigis_cfi')
        process.dumpGctDigis.doRctEm = cms.untracked.bool(True)
        process.dumpGctDigis.doRegions = cms.untracked.bool(True)
        process.dumpGctDigis.doInternEm = cms.untracked.bool(False)
        process.dumpGctDigis.doEm = cms.untracked.bool(False)
        process.dumpGctDigis.doJets = cms.untracked.bool(False)
        process.dumpGctDigis.doEnergySums = cms.untracked.bool(False)
        process.dumpGctDigis.doFibres = cms.untracked.bool(False)
        process.dumpGctDigis.doEmulated = cms.untracked.bool(False)
        process.dumpGctDigis.doHardware = cms.untracked.bool(True)
        process.dumpGctDigis.outFile = cms.untracked.string('')
        process.dumpGctDigis.rawInput = cms.untracked.InputTag("caloStage1Digis")

        process.analyzer.insert(1,process.dumpGctDigis)


# optional EDM file
if (options.edm):
    process.output = cms.OutputModule(
        "PoolOutputModule",
        outputCommands = cms.untracked.vstring("keep *"),
        fileName = cms.untracked.string('l1tCalo_EDM.root')
    )

    process.out = cms.EndPath(
        process.output
    )
    
    
