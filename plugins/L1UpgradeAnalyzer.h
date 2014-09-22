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

      edm::EDGetToken EGammaToken_;
      edm::EDGetToken TauToken_;
      edm::EDGetToken JetToken_;
      edm::EDGetToken EtSumToken_;
      edm::EDGetToken CaloSpareToken_;
      edm::EDGetToken RegionToken_;

      edm::Service<TFileService> fs;
      TTree *UpgradeTree;

      int event;
      int run;
      //int lumi;

      int nJet;
      int *jet_hwPt;
      int *jet_hwEta;
      int *jet_hwPhi;
      int *jet_hwQual;
      int *jet_hwIso;

      double *jet_pt;
      double *jet_eta;
      double *jet_phi;

      int nTau;
      int *tau_hwPt;
      int *tau_hwEta;
      int *tau_hwPhi;
      int *tau_hwQual;
      int *tau_hwIso;

      double *tau_pt;
      double *tau_eta;
      double *tau_phi;

      int nEgamma;
      int *egamma_hwPt;
      int *egamma_hwEta;
      int *egamma_hwPhi;
      int *egamma_hwQual;
      int *egamma_hwIso;

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

      double *etsum_pt;
      double *etsum_eta;
      double *etsum_phi;

      int nCentrality;
      int *centrality_hwPt;
      int *centrality_hwEta;
      int *centrality_hwPhi;
      int *centrality_hwQual;
      int *centrality_hwIso;

      double *centrality_pt;
      double *centrality_eta;
      double *centrality_phi;

      int nV2;
      int *v2_hwPt;
      int *v2_hwEta;
      int *v2_hwPhi;
      int *v2_hwQual;
      int *v2_hwIso;

      double *v2_pt;
      double *v2_eta;
      double *v2_phi;

      int nRegions;
      int *region_hwPt;
      int *region_hwEta;
      int *region_hwPhi;
      int *region_tauVeto;
  };
}

#endif
