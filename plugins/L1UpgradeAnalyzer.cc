// L1UpgradeAnalyzer
//
// Author: R. Alex Barbieri
//
// Used to push the L1Trigger upgrade dataformats to a TTree
//

#include "L1UpgradeAnalyzer.h"
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
l1t::L1UpgradeAnalyzer::analyze(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // boilerplate
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

  // Begin analysis
  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.id().lumi();

  nJet = 0;
  nTau = 0;
  nEgamma = 0;
  nEtsum = 0;
  nHFringsum = 0;
  nHFbitcount = 0;

  for(int bx = firstBX; bx <= lastBX; ++bx)
  {
    for(l1t::EGammaBxCollection::const_iterator itEGamma = egammas->begin(bx);
	itEGamma != egammas->end(bx); ++itEGamma)
    {
      nEgamma++;
    }

    for(l1t::TauBxCollection::const_iterator itTau = taus->begin(bx);
	itTau != taus->end(bx); ++itTau)
    {
      nTau++;
    }

    for(l1t::JetBxCollection::const_iterator itJet = jets->begin(bx);
	itJet != jets->end(bx); ++itJet)
    {
      nJet++;
    }

    for(l1t::EtSumBxCollection::const_iterator itEtSum = etsums->begin(bx);
	itEtSum != etsums->end(bx); ++itEtSum)
    {
      nEtsum++;
    }

    for(l1t::HFRingSumBxCollection::const_iterator itHFRingSum = hfringsums->begin(bx);
	itHFRingSum != hfringsums->end(bx); ++itHFRingSum)
    {
      nHFringsum++;
    }

    for(l1t::HFBitCountBxCollection::const_iterator itHFBitCount = hfbitcounts->begin(bx);
	itHFBitCount != hfbitcounts->end(bx); ++itHFBitCount)
    {
      nHFbitcount++;
    }
  }

  UpgradeTree->Fill();
}

// ------------ method called once each job just before starting event loop  ------------
void
l1t::L1UpgradeAnalyzer::beginJob()
{
  UpgradeTree = fs->make<TTree>("L1UpgradeTree","L1 Trigger Upgrade Dataformats");

  UpgradeTree->Branch("event",&event,"event/I");
  UpgradeTree->Branch("run", &run, "run/I");
  UpgradeTree->Branch("lumi", &lumi, "lumi/I");

  const unsigned int MAXSIZE = 1000;

  jet_hwPt = new int[MAXSIZE];
  jet_hwEta = new int[MAXSIZE];
  jet_hwPhi = new int[MAXSIZE];
  jet_hwQual = new int[MAXSIZE];
  jet_hwIso = new int[MAXSIZE];

  jet_pt = new double[MAXSIZE];
  jet_eta = new double[MAXSIZE];
  jet_phi = new double[MAXSIZE];

  tau_hwPt = new int[MAXSIZE];
  tau_hwEta = new int[MAXSIZE];
  tau_hwPhi = new int[MAXSIZE];
  tau_hwQual = new int[MAXSIZE];
  tau_hwIso = new int[MAXSIZE];

  tau_pt = new double[MAXSIZE];
  tau_eta = new double[MAXSIZE];
  tau_phi = new double[MAXSIZE];

  egamma_hwPt = new int[MAXSIZE];
  egamma_hwEta = new int[MAXSIZE];
  egamma_hwPhi = new int[MAXSIZE];
  egamma_hwQual = new int[MAXSIZE];
  egamma_hwIso = new int[MAXSIZE];

  egamma_pt = new double[MAXSIZE];
  egamma_eta = new double[MAXSIZE];
  egamma_phi = new double[MAXSIZE];

  etsum_hwPt = new int[MAXSIZE];
  etsum_hwEta = new int[MAXSIZE];
  etsum_hwPhi = new int[MAXSIZE];
  etsum_hwQual = new int[MAXSIZE];
  etsum_hwIso = new int[MAXSIZE];
  etsum_type = new int[MAXSIZE];

  etsum_pt = new double[MAXSIZE];
  etsum_eta = new double[MAXSIZE];
  etsum_phi = new double[MAXSIZE];

  hfringsum_hwPt = new int[MAXSIZE];
  hfringsum_hwEta = new int[MAXSIZE];
  hfringsum_hwPhi = new int[MAXSIZE];
  hfringsum_hwQual = new int[MAXSIZE];
  hfringsum_hwIso = new int[MAXSIZE];

  hfringsum_pt = new double[MAXSIZE];
  hfringsum_eta = new double[MAXSIZE];
  hfringsum_phi = new double[MAXSIZE];

  hfbitcount_hwPt = new int[MAXSIZE];
  hfbitcount_hwEta = new int[MAXSIZE];
  hfbitcount_hwPhi = new int[MAXSIZE];
  hfbitcount_hwQual = new int[MAXSIZE];
  hfbitcount_hwIso = new int[MAXSIZE];

  hfbitcount_pt = new double[MAXSIZE];
  hfbitcount_eta = new double[MAXSIZE];
  hfbitcount_phi = new double[MAXSIZE];

  UpgradeTree->Branch("nJet",&nJet,"nJet/I");
  UpgradeTree->Branch("jet_hwPt",jet_hwPt,"jet_hwPt[nJet]/I");
  UpgradeTree->Branch("jet_hwEta",jet_hwEta,"jet_hwEta[nJet]/I");
  UpgradeTree->Branch("jet_hwPhi",jet_hwPhi,"jet_hwPhi[nJet]/I");
  UpgradeTree->Branch("jet_hwQual",jet_hwQual,"jet_hwQual[nJet]/I");
  UpgradeTree->Branch("jet_hwIso",jet_hwIso,"jet_hwIso[nJet]/I");

  UpgradeTree->Branch("jet_pt",jet_pt,"jet_pt[nJet]/D");
  UpgradeTree->Branch("jet_eta",jet_eta,"jet_eta[nJet]/D");
  UpgradeTree->Branch("jet_phi",jet_phi,"jet_phi[nJet]/D");

  UpgradeTree->Branch("nTau",&nTau,"nTau/I");
  UpgradeTree->Branch("tau_hwPt",tau_hwPt,"tau_hwPt[nTau]/I");
  UpgradeTree->Branch("tau_hwEta",tau_hwEta,"tau_hwEta[nTau]/I");
  UpgradeTree->Branch("tau_hwPhi",tau_hwPhi,"tau_hwPhi[nTau]/I");
  UpgradeTree->Branch("tau_hwQual",tau_hwQual,"tau_hwQual[nTau]/I");
  UpgradeTree->Branch("tau_hwIso",tau_hwIso,"tau_hwIso[nTau]/I");

  UpgradeTree->Branch("tau_pt",tau_pt,"tau_pt[nTau]/D");
  UpgradeTree->Branch("tau_eta",tau_eta,"tau_eta[nTau]/D");
  UpgradeTree->Branch("tau_phi",tau_phi,"tau_phi[nTau]/D");

  UpgradeTree->Branch("nEgamma",&nEgamma,"nEgamma/I");
  UpgradeTree->Branch("egamma_hwPt",egamma_hwPt,"egamma_hwPt[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwEta",egamma_hwEta,"egamma_hwEta[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwPhi",egamma_hwPhi,"egamma_hwPhi[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwQual",egamma_hwQual,"egamma_hwQual[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwIso",egamma_hwIso,"egamma_hwIso[nEgamma]/I");

  UpgradeTree->Branch("egamma_pt",egamma_pt,"egamma_pt[nEgamma]/D");
  UpgradeTree->Branch("egamma_eta",egamma_eta,"egamma_eta[nEgamma]/D");
  UpgradeTree->Branch("egamma_phi",egamma_phi,"egamma_phi[nEgamma]/D");

  UpgradeTree->Branch("nEtsum",&nEtsum,"nEtsum/I");
  UpgradeTree->Branch("etsum_hwPt",etsum_hwPt,"etsum_hwPt[nEtsum]/I");
  UpgradeTree->Branch("etsum_hwEta",etsum_hwEta,"etsum_hwEta[nEtsum]/I");
  UpgradeTree->Branch("etsum_hwPhi",etsum_hwPhi,"etsum_hwPhi[nEtsum]/I");
  UpgradeTree->Branch("etsum_hwQual",etsum_hwQual,"etsum_hwQual[nEtsum]/I");
  UpgradeTree->Branch("etsum_hwIso",etsum_hwIso,"etsum_hwIso[nEtsum]/I");
  UpgradeTree->Branch("etsum_type",etsum_type,"etsum_type[nEtsum]/I");

  UpgradeTree->Branch("etsum_pt",etsum_pt,"etsum_pt[nEtsum]/D");
  UpgradeTree->Branch("etsum_eta",etsum_eta,"etsum_eta[nEtsum]/D");
  UpgradeTree->Branch("etsum_phi",etsum_phi,"etsum_phi[nEtsum]/D");

  UpgradeTree->Branch("nHFringsum",&nHFringsum,"nHFringsum/I");
  UpgradeTree->Branch("hfringsum_hwPt",hfringsum_hwPt,"hfringsum_hwPt[nHFringsum]/I");
  UpgradeTree->Branch("hfringsum_hwEta",hfringsum_hwEta,"hfringsum_hwEta[nHFringsum]/I");
  UpgradeTree->Branch("hfringsum_hwPhi",hfringsum_hwPhi,"hfringsum_hwPhi[nHFringsum]/I");
  UpgradeTree->Branch("hfringsum_hwQual",hfringsum_hwQual,"hfringsum_hwQual[nHFringsum]/I");
  UpgradeTree->Branch("hfringsum_hwIso",hfringsum_hwIso,"hfringsum_hwIso[nHFringsum]/I");

  UpgradeTree->Branch("hfringsum_pt",hfringsum_pt,"hfringsum_pt[nHFringsum]/D");
  UpgradeTree->Branch("hfringsum_eta",hfringsum_eta,"hfringsum_eta[nHFringsum]/D");
  UpgradeTree->Branch("hfringsum_phi",hfringsum_phi,"hfringsum_phi[nHFringsum]/D");

  UpgradeTree->Branch("nHFbitcount",&nHFbitcount,"nHFbitcount/I");
  UpgradeTree->Branch("hfbitcount_hwPt",hfbitcount_hwPt,"hfbitcount_hwPt[nHFbitcount]/I");
  UpgradeTree->Branch("hfbitcount_hwEta",hfbitcount_hwEta,"hfbitcount_hwEta[nHFbitcount]/I");
  UpgradeTree->Branch("hfbitcount_hwPhi",hfbitcount_hwPhi,"hfbitcount_hwPhi[nHFbitcount]/I");
  UpgradeTree->Branch("hfbitcount_hwQual",hfbitcount_hwQual,"hfbitcount_hwQual[nHFbitcount]/I");
  UpgradeTree->Branch("hfbitcount_hwIso",hfbitcount_hwIso,"hfbitcount_hwIso[nHFbitcount]/I");

  UpgradeTree->Branch("hfbitcount_pt",hfbitcount_pt,"hfbitcount_pt[nHFbitcount]/D");
  UpgradeTree->Branch("hfbitcount_eta",hfbitcount_eta,"hfbitcount_eta[nHFbitcount]/D");
  UpgradeTree->Branch("hfbitcount_phi",hfbitcount_phi,"hfbitcount_phi[nHFbitcount]/D");
}

// ------------ method called once each job just after ending the event loop  ------------
void
l1t::L1UpgradeAnalyzer::endJob()
{
  delete jet_hwPt;
  delete jet_hwEta;
  delete jet_hwPhi;
  delete jet_hwQual;
  delete jet_hwIso;

  delete jet_pt;
  delete jet_eta;
  delete jet_phi;

  delete tau_hwPt;
  delete tau_hwEta;
  delete tau_hwPhi;
  delete tau_hwQual;
  delete tau_hwIso;

  delete tau_pt;
  delete tau_eta;
  delete tau_phi;

  delete egamma_hwPt;
  delete egamma_hwEta;
  delete egamma_hwPhi;
  delete egamma_hwQual;
  delete egamma_hwIso;

  delete egamma_pt;
  delete egamma_eta;
  delete egamma_phi;

  delete etsum_hwPt;
  delete etsum_hwEta;
  delete etsum_hwPhi;
  delete etsum_hwQual;
  delete etsum_hwIso;
  delete etsum_type;

  delete etsum_pt;
  delete etsum_eta;
  delete etsum_phi;

  delete hfringsum_hwPt;
  delete hfringsum_hwEta;
  delete hfringsum_hwPhi;
  delete hfringsum_hwQual;
  delete hfringsum_hwIso;

  delete hfringsum_pt;
  delete hfringsum_eta;
  delete hfringsum_phi;

  delete hfbitcount_hwPt;
  delete hfbitcount_hwEta;
  delete hfbitcount_hwPhi;
  delete hfbitcount_hwQual;
  delete hfbitcount_hwIso;

  delete hfbitcount_pt;
  delete hfbitcount_eta;
  delete hfbitcount_phi;
}

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
