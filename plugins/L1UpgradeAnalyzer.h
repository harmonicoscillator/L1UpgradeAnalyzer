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
      int *jet_hwPt;
      int *jet_hwEta;
      int *jet_hwPhi;
      int *jet_hwQual;
      int *jet_hwIso;
      int *jet_bx;

      double *jet_pt;
      double *jet_eta;
      double *jet_phi;

      int nTau;
      int *tau_hwPt;
      int *tau_hwEta;
      int *tau_hwPhi;
      int *tau_hwQual;
      int *tau_hwIso;
      int *tau_bx;

      double *tau_pt;
      double *tau_eta;
      double *tau_phi;

      int nIsotau;
      int *isotau_hwPt;
      int *isotau_hwEta;
      int *isotau_hwPhi;
      int *isotau_hwQual;
      int *isotau_hwIso;
      int *isotau_bx;

      double *isotau_pt;
      double *isotau_eta;
      double *isotau_phi;

      int nEgamma;
      int *egamma_hwPt;
      int *egamma_hwEta;
      int *egamma_hwPhi;
      int *egamma_hwQual;
      int *egamma_hwIso;
      int *egamma_bx;

      double *egamma_pt;
      double *egamma_eta;
      double *egamma_phi;

      int nEtsum;
      int *etsum_hwPt;
      int *etsum_hwEta;
      int *etsum_hwPhi;
      int *etsum_hwQual;
      int *etsum_hwIso;
      int *etsum_type;
      int *etsum_bx;

      double *etsum_pt;
      double *etsum_eta;
      double *etsum_phi;

      int nHfring;
      int *hfring_hwPt;
      int *hfring_hwEta;
      int *hfring_hwPhi;
      int *hfring_hwQual;
      int *hfring_hwIso;
      int *hfring_bx;

      double *hfring_pt;
      double *hfring_eta;
      double *hfring_phi;

      int nRegions;
      int *region_hwPt;
      int *region_hwEta;
      int *region_hwPhi;
      int *region_tauVeto;
      int *region_bx;

      int nEMCands;
      int *emcand_hwPt;
      int *emcand_hwEta;
      int *emcand_hwPhi;
      int *emcand_hwIso;
      int *emcand_hwQual;
      int *emcand_bx;

      int nLegacyRegions;
      int *legacyregion_raw;
      int *legacyregion_et;
      int *legacyregion_gctEta;
      int *legacyregion_gctPhi;
      int *legacyregion_crate;
      int *legacyregion_card;
      int *legacyregion_index;
      int *legacyregion_bx;

      int nLegacyEmCands;
      int *legacyemcand_raw;
      int *legacyemcand_rank;
      int *legacyemcand_regionEta;
      int *legacyemcand_regionPhi;
      int *legacyemcand_crate;
      int *legacyemcand_card;
      int *legacyemcand_index;
      int *legacyemcand_iso;
      int *legacyemcand_bx;

  };
}

#endif
