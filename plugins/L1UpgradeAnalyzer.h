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

  class L1UpgradeAnalyzer : public edm::EDProducer {
  public:
    explicit L1UpgradeAnalyzer(const edm::ParameterSet& ps);
    ~L1UpgradeAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
      virtual void beginJob() override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
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
  };
}

#endif
