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
    input = cms.untracked.int32(100)
    )

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
                            fileNames = cms.untracked.vstring(
'root://xrootd.cmsaf.mit.edu//store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_166_1_NpX.root'
                                # # 1
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_100_1_cwZ.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_101_1_Y8q.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_102_1_Tmr.root',

#     #2
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_103_1_8aJ.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_104_1_aye.root',

    ## 3
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_105_1_Muz.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_106_1_c2m.root',

    ## 4
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_107_1_96s.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_108_1_xnb.root',

    ## 5
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_109_1_NWe.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_10_1_0tY.root',

    ## 6
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_110_1_fkm.root',
# '/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_112_1_sHP.root',

    ## 7
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_114_1_K2E.root',
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_115_1_h4h.root',

    ## 8
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_120_1_RnI.root',
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_121_1_2Fu.root',
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_122_1_wlm.root',

    ## 9
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_123_1_soE.root',
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_124_1_p5Y.root',

    ## 10
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_126_1_pCl.root',
#'/store/user/icali/HIMinBiasUPC/HIMinBiasUPC_Skim_HLT_HIMinBiasHfOrBSC_Centrality0-10//64ca16868e481177958780733023cfa2/SD_MB_Cen0_10_128_1_FuJ.root',
    #"file:/afs/cern.ch/work/r/richard/public/HI_L1_FirmwareTesting/Mismatched_HI_Jets_RAW.root"
                            )
)

process.options = cms.untracked.PSet()

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

process.load('L1Trigger.L1TCalorimeter.caloConfigStage1HI_cfi')
process.load('L1Trigger.L1TCalorimeter.L1TCaloStage1_HIFromRaw_cff')
#process.load("L1Trigger.L1TCalorimeter.L1TCaloStage1_PPFromRaw_cff")
#process.load('L1Trigger.L1TCalorimeter.caloStage1RCTLuts_cff')
#process.caloStage1Params.jetSeedThreshold = cms.double(0.)
#process.RCTConfigProducers.eicIsolationThreshold = cms.uint32(7)
#process.RCTConfigProducers.hOeCut = cms.double(999)
#process.RCTConfigProducers.eMinForHoECut = cms.double(999)
#process.RCTConfigProducers.eMaxForHoECut = cms.double(999)
#process.RCTConfigProducers.hMinForHoECut = cms.double(999)
#process.RCTConfigProducers.eMinForFGCut = cms.double(999)


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


# ############### settings
# ### old standard
# ### PUS mask
# process.caloStage1Params.regionPUSParams = cms.vdouble((0, 0, 0, 0,
#                                                        0, 0, 0, 0, 0, 0, 0,
#                                                        0, 0, 0, 0, 0, 0, 0,
#                                                        0, 0, 0, 0))
# ### EG 'iso' (eta) mask
# process.caloStage1Params.isoTauEtaMin = cms.int32(0b1111110000000000111111) # 6<= eta <= 15

# ### Single track eta mask
# process.caloStage1Params.isoTauEtaMax = cms.int32(0b1111111100000011111111) # 8 <= eta <= 13

# ### jet seed threshold for 3x3 step of jet finding
# process.caloStage1Params.jetSeedThreshold = cms.double(0)

# ### Zeros
# ### PUS mask
# process.caloStage1Params.regionPUSParams = cms.vdouble((0, 0, 0, 0,
#                                                        0, 0, 0, 0, 0, 0, 0,
#                                                        0, 0, 0, 0, 0, 0, 0,
#                                                        0, 0, 0, 0))
# ### EG 'iso' (eta) mask
# process.caloStage1Params.isoTauEtaMin = cms.int32(0b1111111111111111111111) #currently the inversion of FW

# ### Single track eta mask
# process.caloStage1Params.isoTauEtaMax = cms.int32(0b1111000000000000001111) #forward taus are bugs

# ### jet seed threshold for 3x3 step of jet finding
# process.caloStage1Params.jetSeedThreshold = cms.double(0)

# ### HTT settings (this won't match anyway yet)
# process.caloStage1Params.etSumEtThreshold        = cms.vdouble(0., 0.) #ET, HT

### nominal
### PUS mask
process.caloStage1Params.regionPUSParams = cms.vdouble((0, 0, 0, 0,
                                                       1, 0, 0, 0, 0, 0, 0,
                                                       0, 0, 0, 0, 0, 0, 1,
                                                       0, 0, 0, 0))
### EG 'iso' (eta) mask
process.caloStage1Params.isoTauEtaMin = cms.int32(0b1111110000000000111111) #currently the inversion of FW

### Single track eta mask
process.caloStage1Params.isoTauEtaMax = cms.int32(0b1111111100000011111111) #forward taus are bugs

### jet seed threshold for 3x3 step of jet finding
process.caloStage1Params.jetSeedThreshold = cms.double(0)

### HTT settings (this won't match anyway yet)
process.caloStage1Params.etSumEtThreshold        = cms.vdouble(0., 7.) #ET, HT

# ### left side
# ### PUS mask
# process.caloStage1Params.regionPUSParams = cms.vdouble((1, 1, 1, 1,
#                                                        1, 1, 1, 1, 1, 1, 1,
#                                                        0, 0, 0, 0, 0, 0, 0,
#                                                        0, 0, 0, 0))
# ### EG 'iso' (eta) mask
# process.caloStage1Params.isoTauEtaMin = cms.int32(0b0000000000011111111111) #currently the inversion of FW

# ### Single track eta mask
# process.caloStage1Params.isoTauEtaMax = cms.int32(0b1111111111100000001111) #forward taus are bugs

# ### jet seed threshold for 3x3 step of jet finding
# process.caloStage1Params.jetSeedThreshold = cms.double(5)

# ### HTT settings (this won't match anyway yet)
# process.caloStage1Params.etSumEtThreshold        = cms.vdouble(0., 0.) #ET, HT

# ### alternating
# ### PUS mask
# process.caloStage1Params.regionPUSParams = cms.vdouble((1, 0, 1, 0,
#                                                         1, 0, 1, 0, 1, 0, 1,
#                                                         0, 1, 0, 1, 0, 1, 0,
#                                                         1, 0, 1, 0))
# ### EG 'iso' (eta) mask
# process.caloStage1Params.isoTauEtaMin = cms.int32(0b0101010101010101010101) #currently the inversion of FW

# ### Single track eta mask
# process.caloStage1Params.isoTauEtaMax = cms.int32(0b1111010101010101011111) #forward taus are bugs

# ### jet seed threshold for 3x3 step of jet finding
# process.caloStage1Params.jetSeedThreshold = cms.double(2.5)

# ### HTT settings (this won't match anyway yet)
# process.caloStage1Params.etSumEtThreshold        = cms.vdouble(0., 40.) #ET, HT
