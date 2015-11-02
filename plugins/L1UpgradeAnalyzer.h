// L1UpgradeAnalyzer
//
// Author: R. Alex Barbieri
//
// Used to push the L1Trigger upgrade dataformats to a TTree
//

#ifndef L1UpgradeAnalyzer_h
#define L1UpgradeAnalyzer_h

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/L1Trigger/interface/CaloSpare.h"
#include "DataFormats/L1TCalorimeter/interface/CaloRegion.h"
#include "DataFormats/L1TCalorimeter/interface/CaloEmCand.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloEmCand.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"

//#include <DataFormats/FEDRawData/interface/FEDRawDataCollection.h>
//#include <DataFormats/FEDRawData/interface/FEDHeader.h>
//#include <DataFormats/FEDRawData/interface/FEDTrailer.h>
//#include <DataFormats/FEDRawData/interface/FEDNumbering.h>
#include <vector>


#include "TTree.h"

namespace l1t {

  class L1UpgradeAnalyzer : public edm::EDAnalyzer {
  public:
    explicit L1UpgradeAnalyzer(const edm::ParameterSet& ps);
    virtual ~L1UpgradeAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
      virtual void beginJob();
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob();

      void clearAllGlobalVectors();

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------


      //edm::EDGetToken FEDRawToken_;
      edm::EDGetToken EGammaToken_;
      edm::EDGetToken TauToken_;
      edm::EDGetToken isoTauToken_;
      edm::EDGetToken JetToken_;
      edm::EDGetToken EtSumToken_;
      edm::EDGetToken CaloSpareToken_;
      edm::EDGetToken HFBitCountToken_;

      edm::EDGetToken RegionToken_;
      edm::EDGetToken EmCandToken_;

      edm::EDGetToken legacyRegionToken_;
      edm::EDGetToken legacyEmCandToken_;

      bool doLayer1 = true;
      //bool doTaus = true;
      //bool doIsoTaus = true;
      bool doLegacyRct = true;

      edm::Service<TFileService> fs;
      TTree *UpgradeTree;

      int event;
      //int FEDBXID;
      int run;
      int lumi;

      int nJet;
      std::vector<int> jet_hwPt;
      std::vector<int> jet_hwEta;
      std::vector<int> jet_hwPhi;
      std::vector<int> jet_hwQual;
      std::vector<int> jet_hwIso;
      std::vector<int> jet_bx;

      std::vector<double> jet_pt;
      std::vector<double> jet_eta;
      std::vector<double> jet_phi;

      int nTau;
      std::vector<int> tau_hwPt;
      std::vector<int> tau_hwEta;
      std::vector<int> tau_hwPhi;
      std::vector<int> tau_hwQual;
      std::vector<int> tau_hwIso;
      std::vector<int> tau_bx;

      std::vector<double> tau_pt;
      std::vector<double> tau_eta;
      std::vector<double> tau_phi;

      int nIsotau;
      std::vector<int> isotau_hwPt;
      std::vector<int> isotau_hwEta;
      std::vector<int> isotau_hwPhi;
      std::vector<int> isotau_hwQual;
      std::vector<int> isotau_hwIso;
      std::vector<int> isotau_bx;

      std::vector<double> isotau_pt;
      std::vector<double> isotau_eta;
      std::vector<double> isotau_phi;

      int nEgamma;
      std::vector<int> egamma_hwPt;
      std::vector<int> egamma_hwEta;
      std::vector<int> egamma_hwPhi;
      std::vector<int> egamma_hwQual;
      std::vector<int> egamma_hwIso;
      std::vector<int> egamma_bx;

      std::vector<double> egamma_pt;
      std::vector<double> egamma_eta;
      std::vector<double> egamma_phi;

      int nEtsum;
      std::vector<int> etsum_hwPt;
      std::vector<int> etsum_hwEta;
      std::vector<int> etsum_hwPhi;
      std::vector<int> etsum_hwQual;
      std::vector<int> etsum_hwIso;
      std::vector<int> etsum_type;
      std::vector<int> etsum_bx;

      std::vector<double> etsum_pt;
      std::vector<double> etsum_eta;
      std::vector<double> etsum_phi;

      int nHfring;
      std::vector<int> hfring_hwPt;
      std::vector<int> hfring_hwEta;
      std::vector<int> hfring_hwPhi;
      std::vector<int> hfring_hwQual;
      std::vector<int> hfring_hwIso;
      std::vector<int> hfring_bx;

      std::vector<double> hfring_pt;
      std::vector<double> hfring_eta;
      std::vector<double> hfring_phi;

      int nHfbits;
      std::vector<int> hfbits_hwPt;
      std::vector<int> hfbits_hwEta;
      std::vector<int> hfbits_hwPhi;
      std::vector<int> hfbits_hwQual;
      std::vector<int> hfbits_hwIso;
      std::vector<int> hfbits_bx;

      std::vector<double> hfbits_pt;
      std::vector<double> hfbits_eta;
      std::vector<double> hfbits_phi;

      int nRegions;
      std::vector<int> region_hwPt;
      std::vector<int> region_hwEta;
      std::vector<int> region_hwPhi;
      std::vector<int> region_tauVeto;
      std::vector<int> region_bx;

      int nEMCands;
      std::vector<int> emcand_hwPt;
      std::vector<int> emcand_hwEta;
      std::vector<int> emcand_hwPhi;
      std::vector<int> emcand_hwIso;
      std::vector<int> emcand_hwQual;
      std::vector<int> emcand_bx;

      int nLegacyRegions;
      std::vector<int> legacyregion_raw;
      std::vector<int> legacyregion_et;
      std::vector<int> legacyregion_gctEta;
      std::vector<int> legacyregion_gctPhi;
      std::vector<int> legacyregion_crate;
      std::vector<int> legacyregion_card;
      std::vector<int> legacyregion_index;
      std::vector<int> legacyregion_bx;

      int nLegacyEmCands;
      std::vector<int> legacyemcand_raw;
      std::vector<int> legacyemcand_rank;
      std::vector<int> legacyemcand_regionEta;
      std::vector<int> legacyemcand_regionPhi;
      std::vector<int> legacyemcand_crate;
      std::vector<int> legacyemcand_card;
      std::vector<int> legacyemcand_index;
      std::vector<int> legacyemcand_iso;
      std::vector<int> legacyemcand_bx;

  };
}

#endif
