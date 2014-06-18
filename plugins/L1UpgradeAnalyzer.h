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
#include "FWCore/Framework/interface/EDProducer.h"
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
#include "DataFormats/L1Trigger/interface/HFRingSum.h"
#include "DataFormats/L1Trigger/interface/HFBitCount.h"

namespace l1t {

  class L1UpgradeAnalyzer : public edm::EDAnalyzer {
  public:
    explicit L1UpgradeAnalyzer(const edm::ParameterSet& ps);
    ~L1UpgradeAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
      virtual void beginJob() override;
      virtual void analyze(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------

      edm::EDGetToken EGammaToken_;
      edm::EDGetToken TauToken_;
      edm::EDGetToken JetToken_;
      edm::EDGetToken EtSumToken_;
      edm::EDGetToken HFRingSumToken_;
      edm::EDGetToken HFBitCountToken_;

      edm::Service<TFileService> fs;
      TTree *UpgradeTree;

      int event;
      int run;
      int lumi;

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

      int nHFringsum;
      int *hfringsum_hwPt;
      int *hfringsum_hwEta;
      int *hfringsum_hwPhi;
      int *hfringsum_hwQual;
      int *hfringsum_hwIso;

      double *hfringsum_pt;
      double *hfringsum_eta;
      double *hfringsum_phi;

      int nHFbitcount;
      int *hfbitcount_hwPt;
      int *hfbitcount_hwEta;
      int *hfbitcount_hwPhi;
      int *hfbitcount_hwQual;
      int *hfbitcount_hwIso;

      double *hfbitcount_pt;
      double *hfbitcount_eta;
      double *hfbitcount_phi;
  };
}

#endif
