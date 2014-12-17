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
  EGammaToken_ = consumes<l1t::EGammaBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2Collection"));
  TauToken_ = consumes<l1t::TauBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2TauCollection"));
  JetToken_ = consumes<l1t::JetBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2Collection"));
  EtSumToken_ = consumes<l1t::EtSumBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2Collection"));
  CaloSpareToken_ = consumes<l1t::CaloSpareBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2CaloSpareCollection"));
  RegionToken_ = consumes<l1t::CaloRegionBxCollection>(ps.getParameter<edm::InputTag>("InputLayer1Collection"));
}

l1t::L1UpgradeAnalyzer::~L1UpgradeAnalyzer() {}

// ------------ method called to produce the data  ------------
void
l1t::L1UpgradeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // boilerplate
  edm::Handle<l1t::EGammaBxCollection> egammas;
  edm::Handle<l1t::TauBxCollection> taus;
  edm::Handle<l1t::JetBxCollection> jets;
  edm::Handle<l1t::EtSumBxCollection> etsums;
  edm::Handle<l1t::CaloSpareBxCollection> calospares;
  edm::Handle<l1t::CaloRegionBxCollection> regions;

  iEvent.getByToken(EGammaToken_, egammas);
  iEvent.getByToken(TauToken_, taus);
  iEvent.getByToken(JetToken_, jets);
  iEvent.getByToken(EtSumToken_, etsums);
  iEvent.getByToken(CaloSpareToken_, calospares);
  iEvent.getByToken(RegionToken_, regions);

  int firstBX = egammas->getFirstBX();
  int lastBX = egammas->getLastBX();

  // Begin analysis
  event = iEvent.id().event();
  run = iEvent.id().run();
  //lumi = iEvent.id().lumi();

  nJet = 0;
  nTau = 0;
  nEgamma = 0;
  nEtsum = 0;
  nCentrality = 0;
  nV2 = 0;
  nRegions = 0;

  for(int bx = firstBX; bx <= lastBX; ++bx)
  {
    for(l1t::EGammaBxCollection::const_iterator itEGamma = egammas->begin(bx);
	itEGamma != egammas->end(bx); ++itEGamma)
    {
      egamma_hwPt[nEgamma] = itEGamma->hwPt();
      egamma_hwEta[nEgamma] = itEGamma->hwEta();
      egamma_hwPhi[nEgamma] = itEGamma->hwPhi();
      egamma_hwQual[nEgamma] = itEGamma->hwQual();
      egamma_hwIso[nEgamma] = itEGamma->hwIso();
      egamma_pt[nEgamma] = itEGamma->pt();
      egamma_eta[nEgamma] = itEGamma->eta();
      egamma_phi[nEgamma] = itEGamma->phi();

      nEgamma++;
    }

    for(l1t::TauBxCollection::const_iterator itTau = taus->begin(bx);
	itTau != taus->end(bx); ++itTau)
    {
      tau_hwPt[nTau] = itTau->hwPt();
      tau_hwEta[nTau] = itTau->hwEta();
      tau_hwPhi[nTau] = itTau->hwPhi();
      tau_hwQual[nTau] = itTau->hwQual();
      tau_hwIso[nTau] = itTau->hwIso();
      tau_pt[nTau] = itTau->pt();
      tau_eta[nTau] = itTau->eta();
      tau_phi[nTau] = itTau->phi();

      nTau++;
    }

    for(l1t::JetBxCollection::const_iterator itJet = jets->begin(bx);
	itJet != jets->end(bx); ++itJet)
    {
      jet_hwPt[nJet] = itJet->hwPt();
      jet_hwEta[nJet] = itJet->hwEta();
      jet_hwPhi[nJet] = itJet->hwPhi();
      jet_hwQual[nJet] = itJet->hwQual();
      jet_hwIso[nJet] = itJet->hwIso();
      jet_pt[nJet] = itJet->pt();
      jet_eta[nJet] = itJet->eta();
      jet_phi[nJet] = itJet->phi();

      const bool verbose = false;
      if(verbose)
      {
	std::cout << "pt: " << itJet->pt() << " eta: " << itJet->eta() << " phi: " << itJet->phi() << std::endl;
      }
      nJet++;
    }

    for(l1t::EtSumBxCollection::const_iterator itEtSum = etsums->begin(bx);
	itEtSum != etsums->end(bx); ++itEtSum)
    {
      etsum_hwPt[nEtsum] = itEtSum->hwPt();
      etsum_hwEta[nEtsum] = itEtSum->hwEta();
      etsum_hwPhi[nEtsum] = itEtSum->hwPhi();
      etsum_hwQual[nEtsum] = itEtSum->hwQual();
      etsum_hwIso[nEtsum] = itEtSum->hwIso();
      etsum_pt[nEtsum] = itEtSum->pt();
      etsum_eta[nEtsum] = itEtSum->eta();
      etsum_phi[nEtsum] = itEtSum->phi();

      etsum_type[nEtsum] = itEtSum->getType();

      nEtsum++;
    }

    for(l1t::CaloSpareBxCollection::const_iterator itCaloSpare = calospares->begin(bx);
	itCaloSpare != calospares->end(bx); ++itCaloSpare)
    {
      if(l1t::CaloSpare::CaloSpareType::V2 == itCaloSpare->getType())
      {
	v2_hwPt[nV2] = itCaloSpare->hwPt();
	v2_hwEta[nV2] = itCaloSpare->hwEta();
	v2_hwPhi[nV2] = itCaloSpare->hwPhi();
	v2_hwQual[nV2] = itCaloSpare->hwQual();
	v2_hwIso[nV2] = itCaloSpare->hwIso();
	v2_pt[nV2] = itCaloSpare->pt();
	v2_eta[nV2] = itCaloSpare->eta();
	v2_phi[nV2] = itCaloSpare->phi();

	nV2++;
      }
      else if (l1t::CaloSpare::CaloSpareType::Centrality == itCaloSpare->getType())
      {
	centrality_hwPt[nCentrality] = itCaloSpare->hwPt();
	centrality_hwEta[nCentrality] = itCaloSpare->hwEta();
	centrality_hwPhi[nCentrality] = itCaloSpare->hwPhi();
	centrality_hwQual[nCentrality] = itCaloSpare->hwQual();
	centrality_hwIso[nCentrality] = itCaloSpare->hwIso();
	centrality_pt[nCentrality] = itCaloSpare->pt();
	centrality_eta[nCentrality] = itCaloSpare->eta();
	centrality_phi[nCentrality] = itCaloSpare->phi();

	nCentrality++;
      }
    }

    for(l1t::CaloRegionBxCollection::const_iterator itCaloRegion = regions->begin(bx);
	itCaloRegion != regions->end(bx); ++itCaloRegion)
    {
      region_hwPt[nRegions] = itCaloRegion->hwPt();
      region_hwEta[nRegions] = itCaloRegion->hwEta();
      region_hwPhi[nRegions] = itCaloRegion->hwPhi();
      region_tauVeto[nRegions] = itCaloRegion->hwQual();

      nRegions++;
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
  //UpgradeTree->Branch("lumi", &lumi, "lumi/I");

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

  v2_hwPt = new int[MAXSIZE];
  v2_hwEta = new int[MAXSIZE];
  v2_hwPhi = new int[MAXSIZE];
  v2_hwQual = new int[MAXSIZE];
  v2_hwIso = new int[MAXSIZE];

  v2_pt = new double[MAXSIZE];
  v2_eta = new double[MAXSIZE];
  v2_phi = new double[MAXSIZE];

  centrality_hwPt = new int[MAXSIZE];
  centrality_hwEta = new int[MAXSIZE];
  centrality_hwPhi = new int[MAXSIZE];
  centrality_hwQual = new int[MAXSIZE];
  centrality_hwIso = new int[MAXSIZE];

  centrality_pt = new double[MAXSIZE];
  centrality_eta = new double[MAXSIZE];
  centrality_phi = new double[MAXSIZE];

  region_hwPt = new int[MAXSIZE];
  region_hwEta = new int[MAXSIZE];
  region_hwPhi = new int[MAXSIZE];
  region_tauVeto = new int[MAXSIZE];

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

  UpgradeTree->Branch("nV2",&nV2,"nV2/I");
  UpgradeTree->Branch("v2_hwPt",v2_hwPt,"v2_hwPt[nV2]/I");
  UpgradeTree->Branch("v2_hwEta",v2_hwEta,"v2_hwEta[nV2]/I");
  UpgradeTree->Branch("v2_hwPhi",v2_hwPhi,"v2_hwPhi[nV2]/I");
  UpgradeTree->Branch("v2_hwQual",v2_hwQual,"v2_hwQual[nV2]/I");
  UpgradeTree->Branch("v2_hwIso",v2_hwIso,"v2_hwIso[nV2]/I");

  UpgradeTree->Branch("v2_pt",v2_pt,"v2_pt[nV2]/D");
  UpgradeTree->Branch("v2_eta",v2_eta,"v2_eta[nV2]/D");
  UpgradeTree->Branch("v2_phi",v2_phi,"v2_phi[nV2]/D");

  UpgradeTree->Branch("nCentrality",&nCentrality,"nCentrality/I");
  UpgradeTree->Branch("centrality_hwPt",centrality_hwPt,"centrality_hwPt[nCentrality]/I");
  UpgradeTree->Branch("centrality_hwEta",centrality_hwEta,"centrality_hwEta[nCentrality]/I");
  UpgradeTree->Branch("centrality_hwPhi",centrality_hwPhi,"centrality_hwPhi[nCentrality]/I");
  UpgradeTree->Branch("centrality_hwQual",centrality_hwQual,"centrality_hwQual[nCentrality]/I");
  UpgradeTree->Branch("centrality_hwIso",centrality_hwIso,"centrality_hwIso[nCentrality]/I");

  UpgradeTree->Branch("centrality_pt",centrality_pt,"centrality_pt[nCentrality]/D");
  UpgradeTree->Branch("centrality_eta",centrality_eta,"centrality_eta[nCentrality]/D");
  UpgradeTree->Branch("centrality_phi",centrality_phi,"centrality_phi[nCentrality]/D");

  UpgradeTree->Branch("nRegions",&nRegions,"nRegions/I");
  UpgradeTree->Branch("region_hwPt",region_hwPt,"region_hwPt[nRegions]/I");
  UpgradeTree->Branch("region_hwEta",region_hwEta,"region_hwEta[nRegions]/I");
  UpgradeTree->Branch("region_hwPhi",region_hwPhi,"region_hwPhi[nRegions]/I");
  UpgradeTree->Branch("region_tauVeto",region_tauVeto,"region_tauVeto[nRegions]/I");

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

  delete v2_hwPt;
  delete v2_hwEta;
  delete v2_hwPhi;
  delete v2_hwQual;
  delete v2_hwIso;

  delete v2_pt;
  delete v2_eta;
  delete v2_phi;

  delete centrality_hwPt;
  delete centrality_hwEta;
  delete centrality_hwPhi;
  delete centrality_hwQual;
  delete centrality_hwIso;

  delete centrality_pt;
  delete centrality_eta;
  delete centrality_phi;

  delete region_hwPt;
  delete region_hwEta;
  delete region_hwPhi;
  delete region_tauVeto;
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
