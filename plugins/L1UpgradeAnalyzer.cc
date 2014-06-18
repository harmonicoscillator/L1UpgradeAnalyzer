// L1UpgradeAnalyzer
//
// Author: R. Alex Barbieri
//
// Used to push the L1Trigger upgrade dataformats to a TTree
//

#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "FWCore/Framework/interface/ESHandle.h"

l1t::L1UpgradeAnalyzer::L1UpgradeAnalyzer(const edm::ParameterSet& ps) {
  EGammaToken_ = consumes<l1t::EGammaBxCollection>(ps.getParameter<edm::InputTag>("InputCollection"));
  TauToken_ = consumes<l1t::TauBxCollection>(ps.getParameter<edm::InputTag>("InputCollection"));
  JetToken_ = consumes<l1t::JetBxCollection>(ps.getParameter<edm::InputTag>("InputCollection"));
  EtSumToken_ = consumes<l1t::EtSumBxCollection>(ps.getParameter<edm::InputTag>("InputCollection"));
  HFRingSumToken_ = consumes<l1t::HFRingSumBxCollection>(ps.getParameter<edm::InputTag>("InputCollection"));
  HFBitCountToken_ = consumes<l1t::HFBitCountBxCollection>(ps.getParameter<edm::InputTag>("InputCollection"));
}

l1t::L1UpgradeAnalyzer::~L1UpgradeAnalyzer() {}

// ------------ method called to produce the data  ------------
void
l1t::L1UpgradeAnalyzer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<l1t::EGammaBxCollection> egammas;
  edm::Handle<l1t::TauBxCollection> taus;
  edm::Handle<l1t::JetBxCollection> jets;
  edm::Handle<l1t::EtSumBxCollection> etsums;
  edm::Handle<l1t::HFRingSumBxCollection> hfringsums;
  edm::Handle<l1t::HFBitCountBxCollection> hfbitcounts;

  iEvent.getByToken(EGammaToken_, egammas);
  iEvent.getByToken(TauToken_, taus);
  iEvent.getByToken(JetToken_, jets);
  iEvent.getByToken(EtSumToken_, etsums);
  iEvent.getByToken(HFRingSumToken_, hfringsums);
  iEvent.getByToken(HFBitCountToken_, hfbitcounts);

  int firstBX = egammas->getFirstBX();
  int lastBX = egammas->getLastBX();

  for(int bx = firstBX; bx <= lastBX; ++bx)
  {
    for(l1t::EGammaBxCollection::const_iterator itEGamma = egammas->begin(bx);
	itEGamma != egammas->end(bx); ++itEGamma)
    {
    }

    for(l1t::TauBxCollection::const_iterator itTau = taus->begin(bx);
	itTau != taus->end(bx); ++itTau)
    {
    }

    for(l1t::JetBxCollection::const_iterator itJet = jets->begin(bx);
	itJet != jets->end(bx); ++itJet)
    {
    }

    for(l1t::EtSumBxCollection::const_iterator itEtSum = etsums->begin(bx);
	itEtSum != etsums->end(bx); ++itEtSum)
    {
    }

    for(l1t::HFRingSumBxCollection::const_iterator itHFRingSum = hfringsums->begin(bx);
	itHFRingSum != hfringsums->end(bx); ++itHFRingSum)
    {
    }

    for(l1t::HFBitCountBxCollection::const_iterator itHFBitCount = hfbitcounts->begin(bx);
	itHFBitCount != hfbitcounts->end(bx); ++itHFBitCount)
    {
    }
  }
}

// ------------ method called once each job just before starting event loop  ------------
void
l1t::L1UpgradeAnalyzer::beginJob(){}

// ------------ method called once each job just after ending the event loop  ------------
void
l1t::L1UpgradeAnalyzer::endJob(){}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
l1t::L1UpgradeAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(l1t::L1UpgradeAnalyzer);
