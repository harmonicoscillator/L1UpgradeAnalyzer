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
  isoTauToken_ = consumes<l1t::TauBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2IsoTauCollection"));
  JetToken_ = consumes<l1t::JetBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2Collection"));
  EtSumToken_ = consumes<l1t::EtSumBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2Collection"));
  CaloSpareToken_ = consumes<l1t::CaloSpareBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2CaloSpareCollection"));

  edm::InputTag Layer1 = ps.getParameter<edm::InputTag>("InputLayer1Collection");
  if(Layer1.label() != "None")
  {
    RegionToken_ = consumes<l1t::CaloRegionBxCollection>(Layer1);
    EmCandToken_ = consumes<l1t::CaloEmCandBxCollection>(Layer1);
  }
  else
    doLayer1 = false;

  legacyRegionToken_ = consumes<L1CaloRegionCollection>(ps.getParameter<edm::InputTag>("legacyRCTDigis"));
  legacyEmCandToken_ = consumes<L1CaloEmCollection>(ps.getParameter<edm::InputTag>("legacyRCTDigis"));
}

l1t::L1UpgradeAnalyzer::~L1UpgradeAnalyzer() {}

// ------------ method called to produce the data  ------------
void
l1t::L1UpgradeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // boilerplate
  edm::Handle<l1t::EGammaBxCollection> egammas;
  edm::Handle<l1t::TauBxCollection> taus;
  edm::Handle<l1t::TauBxCollection> isotaus;
  edm::Handle<l1t::JetBxCollection> jets;
  edm::Handle<l1t::EtSumBxCollection> etsums;
  edm::Handle<l1t::CaloSpareBxCollection> calospares;

  edm::Handle<l1t::CaloRegionBxCollection> regions;
  edm::Handle<l1t::CaloEmCandBxCollection> emcands;

  edm::Handle<L1CaloRegionCollection> legacyregions;
  edm::Handle<L1CaloEmCollection> legacyemcands;

  iEvent.getByToken(EGammaToken_, egammas);
  iEvent.getByToken(TauToken_, taus);
  iEvent.getByToken(isoTauToken_, isotaus);
  iEvent.getByToken(JetToken_, jets);
  iEvent.getByToken(EtSumToken_, etsums);
  iEvent.getByToken(CaloSpareToken_, calospares);

  if(doLayer1) {
    iEvent.getByToken(RegionToken_, regions);
    iEvent.getByToken(EmCandToken_, emcands);
  }

  iEvent.getByToken(legacyRegionToken_, legacyregions);
  iEvent.getByToken(legacyEmCandToken_, legacyemcands);

  // Begin analysis
  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.id().luminosityBlock();

  nJet = 0;
  nTau = 0;
  nIsotau = 0;
  nEgamma = 0;
  nEtsum = 0;
  nHfring = 0;

  nRegions = 0;
  nEMCands = 0;

  nLegacyRegions = 0;
  nLegacyEmCands = 0;

  for(int bx = egammas->getFirstBX(); bx <= egammas->getLastBX(); ++bx)
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
      egamma_bx[nEgamma] = bx;

      nEgamma++;
    }
  }

  for(int bx = taus->getFirstBX(); bx <= taus->getLastBX(); ++bx)
  {
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
      tau_bx[nTau] = bx;

      nTau++;
    }
  }

  for(int bx = isotaus->getFirstBX(); bx <= isotaus->getLastBX(); ++bx)
  {
    for(l1t::TauBxCollection::const_iterator itIsoTau = isotaus->begin(bx);
	itIsoTau != isotaus->end(bx); ++itIsoTau)
    {
      isotau_hwPt[nIsotau] = itIsoTau->hwPt();
      isotau_hwEta[nIsotau] = itIsoTau->hwEta();
      isotau_hwPhi[nIsotau] = itIsoTau->hwPhi();
      isotau_hwQual[nIsotau] = itIsoTau->hwQual();
      isotau_hwIso[nIsotau] = itIsoTau->hwIso();
      isotau_pt[nIsotau] = itIsoTau->pt();
      isotau_eta[nIsotau] = itIsoTau->eta();
      isotau_phi[nIsotau] = itIsoTau->phi();
      isotau_bx[nIsotau] = bx;

      nIsotau++;
    }
  }

  for(int bx = jets->getFirstBX(); bx <= jets->getLastBX(); ++bx)
  {
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
      jet_bx[nJet] = bx;

      const bool verbose = false;
      if(verbose)
      {
	std::cout << "pt: " << itJet->pt() << " eta: " << itJet->eta() << " phi: " << itJet->phi() << std::endl;
      }
      nJet++;
    }
  }

  for(int bx = etsums->getFirstBX(); bx <= etsums->getLastBX(); ++bx)
  {
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
      etsum_bx[nEtsum] = bx;

      etsum_type[nEtsum] = itEtSum->getType();

      nEtsum++;
    }
  }

  // for(l1t::CaloSpareBxCollection::const_iterator itCaloSpare = calospares->begin(bx);
  // 	itCaloSpare != calospares->end(bx); ++itCaloSpare)
  // {
  //   if(l1t::CaloSpare::CaloSpareType::V2 == itCaloSpare->getType())
  //   {
  // 	v2_hwPt[nV2] = itCaloSpare->hwPt();
  // 	v2_hwEta[nV2] = itCaloSpare->hwEta();
  // 	v2_hwPhi[nV2] = itCaloSpare->hwPhi();
  // 	v2_hwQual[nV2] = itCaloSpare->hwQual();
  // 	v2_hwIso[nV2] = itCaloSpare->hwIso();
  // 	v2_pt[nV2] = itCaloSpare->pt();
  // 	v2_eta[nV2] = itCaloSpare->eta();
  // 	v2_phi[nV2] = itCaloSpare->phi();

  // 	nV2++;
  //   }
  //   else if (l1t::CaloSpare::CaloSpareType::Centrality == itCaloSpare->getType())
  //   {
  // 	centrality_hwPt[nCentrality] = itCaloSpare->hwPt();
  // 	centrality_hwEta[nCentrality] = itCaloSpare->hwEta();
  // 	centrality_hwPhi[nCentrality] = itCaloSpare->hwPhi();
  // 	centrality_hwQual[nCentrality] = itCaloSpare->hwQual();
  // 	centrality_hwIso[nCentrality] = itCaloSpare->hwIso();
  // 	centrality_pt[nCentrality] = itCaloSpare->pt();
  // 	centrality_eta[nCentrality] = itCaloSpare->eta();
  // 	centrality_phi[nCentrality] = itCaloSpare->phi();

  // 	nCentrality++;
  //   }
  // }

  if(doLayer1)
  {
    for(int bx = regions->getFirstBX(); bx <= regions->getLastBX(); ++bx)
    {
      for(l1t::CaloRegionBxCollection::const_iterator itCaloRegion = regions->begin(bx);
	  itCaloRegion != regions->end(bx); ++itCaloRegion)
      {
	region_hwPt[nRegions] = itCaloRegion->hwPt();
	region_hwEta[nRegions] = itCaloRegion->hwEta();
	region_hwPhi[nRegions] = itCaloRegion->hwPhi();
	region_tauVeto[nRegions] = itCaloRegion->hwQual();
	region_bx[nRegions] = bx;

	nRegions++;
      }
    }

    for(int bx = emcands->getFirstBX(); bx <= emcands->getLastBX(); ++bx)
    {
      for(l1t::CaloEmCandBxCollection::const_iterator itCaloEmCand = emcands->begin(bx);
	  itCaloEmCand != emcands->end(bx); ++itCaloEmCand)
      {
	emcand_hwPt[nEMCands] = itCaloEmCand->hwPt();
	emcand_hwEta[nEMCands] = itCaloEmCand->hwEta();
	emcand_hwPhi[nEMCands] = itCaloEmCand->hwPhi();
	emcand_hwIso[nEMCands] = itCaloEmCand->hwIso();
	emcand_hwQual[nEMCands] = itCaloEmCand->hwQual();
	emcand_bx[nEMCands] = bx;

	nEMCands++;
      }
    }
  }


  for(std::vector<L1CaloRegion>::const_iterator rgn=legacyregions->begin(); rgn!=legacyregions->end(); ++rgn)
  {
    legacyregion_raw[nLegacyRegions] = rgn->raw();
    legacyregion_et[nLegacyRegions] = rgn->et();
    legacyregion_gctEta[nLegacyRegions] = rgn->id().ieta();
    legacyregion_gctPhi[nLegacyRegions] = rgn->id().iphi();
    legacyregion_crate[nLegacyRegions] = rgn->rctCrate();
    legacyregion_card[nLegacyRegions] = rgn->rctCard();
    legacyregion_index[nLegacyRegions] = rgn->rctRegionIndex();
    legacyregion_bx[nLegacyRegions] = rgn->bx();

    nLegacyRegions++;
  }

  for (std::vector<L1CaloEmCand>::const_iterator em=legacyemcands->begin(); em!=legacyemcands->end(); ++em)
  {
    legacyemcand_raw[nLegacyEmCands] = em->raw();
    legacyemcand_rank[nLegacyEmCands] = em->rank();
    legacyemcand_regionEta[nLegacyEmCands] = em->regionId().ieta();
    legacyemcand_regionPhi[nLegacyEmCands] = em->regionId().iphi();
    legacyemcand_crate[nLegacyEmCands] = em->rctCrate();
    legacyemcand_card[nLegacyEmCands] = em->rctCard();
    legacyemcand_index[nLegacyEmCands] = em->index();
    legacyemcand_iso[nLegacyEmCands] = em->isolated();
    legacyemcand_bx[nLegacyEmCands] = em->bx();

    nLegacyEmCands++;
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
  jet_bx = new int[MAXSIZE];

  jet_pt = new double[MAXSIZE];
  jet_eta = new double[MAXSIZE];
  jet_phi = new double[MAXSIZE];

  tau_hwPt = new int[MAXSIZE];
  tau_hwEta = new int[MAXSIZE];
  tau_hwPhi = new int[MAXSIZE];
  tau_hwQual = new int[MAXSIZE];
  tau_hwIso = new int[MAXSIZE];
  tau_bx = new int[MAXSIZE];

  tau_pt = new double[MAXSIZE];
  tau_eta = new double[MAXSIZE];
  tau_phi = new double[MAXSIZE];

  isotau_hwPt = new int[MAXSIZE];
  isotau_hwEta = new int[MAXSIZE];
  isotau_hwPhi = new int[MAXSIZE];
  isotau_hwQual = new int[MAXSIZE];
  isotau_hwIso = new int[MAXSIZE];
  isotau_bx = new int[MAXSIZE];

  isotau_pt = new double[MAXSIZE];
  isotau_eta = new double[MAXSIZE];
  isotau_phi = new double[MAXSIZE];

  egamma_hwPt = new int[MAXSIZE];
  egamma_hwEta = new int[MAXSIZE];
  egamma_hwPhi = new int[MAXSIZE];
  egamma_hwQual = new int[MAXSIZE];
  egamma_hwIso = new int[MAXSIZE];
  egamma_bx = new int[MAXSIZE];

  egamma_pt = new double[MAXSIZE];
  egamma_eta = new double[MAXSIZE];
  egamma_phi = new double[MAXSIZE];

  etsum_hwPt = new int[MAXSIZE];
  etsum_hwEta = new int[MAXSIZE];
  etsum_hwPhi = new int[MAXSIZE];
  etsum_hwQual = new int[MAXSIZE];
  etsum_hwIso = new int[MAXSIZE];
  etsum_type = new int[MAXSIZE];
  etsum_bx = new int[MAXSIZE];

  etsum_pt = new double[MAXSIZE];
  etsum_eta = new double[MAXSIZE];
  etsum_phi = new double[MAXSIZE];

  region_hwPt = new int[MAXSIZE];
  region_hwEta = new int[MAXSIZE];
  region_hwPhi = new int[MAXSIZE];
  region_tauVeto = new int[MAXSIZE];
  region_bx = new int[MAXSIZE];

  emcand_hwPt = new int[MAXSIZE];
  emcand_hwEta = new int[MAXSIZE];
  emcand_hwPhi = new int[MAXSIZE];
  emcand_hwIso = new int[MAXSIZE];
  emcand_hwQual = new int[MAXSIZE];
  emcand_bx = new int[MAXSIZE];

  legacyregion_raw = new int[MAXSIZE];
  legacyregion_et = new int[MAXSIZE];
  legacyregion_gctEta = new int[MAXSIZE];
  legacyregion_gctPhi = new int[MAXSIZE];
  legacyregion_crate = new int[MAXSIZE];
  legacyregion_card = new int[MAXSIZE];
  legacyregion_index = new int[MAXSIZE];
  legacyregion_bx = new int[MAXSIZE];

  legacyemcand_raw = new int[MAXSIZE];
  legacyemcand_rank = new int[MAXSIZE];
  legacyemcand_regionEta = new int[MAXSIZE];
  legacyemcand_regionPhi = new int[MAXSIZE];
  legacyemcand_crate = new int[MAXSIZE];
  legacyemcand_card = new int[MAXSIZE];
  legacyemcand_index = new int[MAXSIZE];
  legacyemcand_iso = new int[MAXSIZE];
  legacyemcand_bx = new int[MAXSIZE];


  UpgradeTree->Branch("nJet",&nJet,"nJet/I");
  UpgradeTree->Branch("jet_hwPt",jet_hwPt,"jet_hwPt[nJet]/I");
  UpgradeTree->Branch("jet_hwEta",jet_hwEta,"jet_hwEta[nJet]/I");
  UpgradeTree->Branch("jet_hwPhi",jet_hwPhi,"jet_hwPhi[nJet]/I");
  UpgradeTree->Branch("jet_hwQual",jet_hwQual,"jet_hwQual[nJet]/I");
  UpgradeTree->Branch("jet_hwIso",jet_hwIso,"jet_hwIso[nJet]/I");
  UpgradeTree->Branch("jet_bx",jet_bx,"jet_bx[nJet]/I");

  UpgradeTree->Branch("jet_pt",jet_pt,"jet_pt[nJet]/D");
  UpgradeTree->Branch("jet_eta",jet_eta,"jet_eta[nJet]/D");
  UpgradeTree->Branch("jet_phi",jet_phi,"jet_phi[nJet]/D");

  UpgradeTree->Branch("nTau",&nTau,"nTau/I");
  UpgradeTree->Branch("tau_hwPt",tau_hwPt,"tau_hwPt[nTau]/I");
  UpgradeTree->Branch("tau_hwEta",tau_hwEta,"tau_hwEta[nTau]/I");
  UpgradeTree->Branch("tau_hwPhi",tau_hwPhi,"tau_hwPhi[nTau]/I");
  UpgradeTree->Branch("tau_hwQual",tau_hwQual,"tau_hwQual[nTau]/I");
  UpgradeTree->Branch("tau_hwIso",tau_hwIso,"tau_hwIso[nTau]/I");
  UpgradeTree->Branch("tau_bx",tau_bx,"tau_bx[nTau]/I");

  UpgradeTree->Branch("tau_pt",tau_pt,"tau_pt[nTau]/D");
  UpgradeTree->Branch("tau_eta",tau_eta,"tau_eta[nTau]/D");
  UpgradeTree->Branch("tau_phi",tau_phi,"tau_phi[nTau]/D");

  UpgradeTree->Branch("nIsotau",&nIsotau,"nIsotau/I");
  UpgradeTree->Branch("isotau_hwPt",isotau_hwPt,"isotau_hwPt[nIsotau]/I");
  UpgradeTree->Branch("isotau_hwEta",isotau_hwEta,"isotau_hwEta[nIsotau]/I");
  UpgradeTree->Branch("isotau_hwPhi",isotau_hwPhi,"isotau_hwPhi[nIsotau]/I");
  UpgradeTree->Branch("isotau_hwQual",isotau_hwQual,"isotau_hwQual[nIsotau]/I");
  UpgradeTree->Branch("isotau_hwIso",isotau_hwIso,"isotau_hwIso[nIsotau]/I");
  UpgradeTree->Branch("isotau_bx",isotau_bx,"isotau_bx[nIsotau]/I");

  UpgradeTree->Branch("isotau_pt",isotau_pt,"isotau_pt[nIsotau]/D");
  UpgradeTree->Branch("isotau_eta",isotau_eta,"isotau_eta[nIsotau]/D");
  UpgradeTree->Branch("isotau_phi",isotau_phi,"isotau_phi[nIsotau]/D");

  UpgradeTree->Branch("nEgamma",&nEgamma,"nEgamma/I");
  UpgradeTree->Branch("egamma_hwPt",egamma_hwPt,"egamma_hwPt[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwEta",egamma_hwEta,"egamma_hwEta[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwPhi",egamma_hwPhi,"egamma_hwPhi[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwQual",egamma_hwQual,"egamma_hwQual[nEgamma]/I");
  UpgradeTree->Branch("egamma_hwIso",egamma_hwIso,"egamma_hwIso[nEgamma]/I");
  UpgradeTree->Branch("egamma_bx",egamma_bx,"egamma_bx[nEgamma]/I");

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
  UpgradeTree->Branch("etsum_bx",etsum_bx,"etsum_bx[nEtsum]/I");

  UpgradeTree->Branch("etsum_pt",etsum_pt,"etsum_pt[nEtsum]/D");
  UpgradeTree->Branch("etsum_eta",etsum_eta,"etsum_eta[nEtsum]/D");
  UpgradeTree->Branch("etsum_phi",etsum_phi,"etsum_phi[nEtsum]/D");

  if(doLayer1)
  {
    UpgradeTree->Branch("nRegions",&nRegions,"nRegions/I");
    UpgradeTree->Branch("region_hwPt",region_hwPt,"region_hwPt[nRegions]/I");
    UpgradeTree->Branch("region_hwEta",region_hwEta,"region_hwEta[nRegions]/I");
    UpgradeTree->Branch("region_hwPhi",region_hwPhi,"region_hwPhi[nRegions]/I");
    UpgradeTree->Branch("region_tauVeto",region_tauVeto,"region_tauVeto[nRegions]/I");
    UpgradeTree->Branch("region_bx",region_bx,"region_bx[nRegions]/I");

    UpgradeTree->Branch("nEMCands",&nEMCands,"nEMCands/I");
    UpgradeTree->Branch("emcand_hwPt",emcand_hwPt,"emcand_hwPt[nEMCands]/I");
    UpgradeTree->Branch("emcand_hwEta",emcand_hwEta,"emcand_hwEta[nEMCands]/I");
    UpgradeTree->Branch("emcand_hwPhi",emcand_hwPhi,"emcand_hwPhi[nEMCands]/I");
    UpgradeTree->Branch("emcand_hwIso",emcand_hwIso,"emcand_hwIso[nEMCands]/I");
    UpgradeTree->Branch("emcand_hwQual",emcand_hwQual, "emcand_hwQual[nEMCands]/I");
    UpgradeTree->Branch("emcand_bx",emcand_bx,"emcand_bx[nEMCands]/I");
  }

  UpgradeTree->Branch("nLegacyRegions",&nLegacyRegions,"nLegacyRegions/I");
  UpgradeTree->Branch("legacyregion_raw",legacyregion_raw,"legacyregion_raw[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_et",legacyregion_et,"legacyregion_et[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_gctEta",legacyregion_gctEta,"legacyregion_gctEta[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_gctPhi",legacyregion_gctPhi,"legacyregion_gctPhi[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_crate",legacyregion_crate,"legacyregion_crate[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_card",legacyregion_card,"legacyregion_card[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_index",legacyregion_index,"legacyregion_index[nLegacyRegions]/I");
  UpgradeTree->Branch("legacyregion_bx",legacyregion_bx,"legacyregion_bx[nLegacyRegions]/I");

  UpgradeTree->Branch("nLegacyEmCands",&nLegacyEmCands,"nLegacyEmCands/I");
  UpgradeTree->Branch("legacyemcand_raw",legacyemcand_raw,"legacyemcand_raw[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_rank",legacyemcand_rank,"legacyemcand_rank[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_regionEta",legacyemcand_regionEta,"legacyemcand_regionEta[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_regionPhi",legacyemcand_regionPhi,"legacyemcand_regionPhi[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_crate",legacyemcand_crate,"legacyemcand_crate[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_card",legacyemcand_card,"legacyemcand_card[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_index",legacyemcand_index,"legacyemcand_index[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_iso",legacyemcand_iso,"legacyemcand_iso[nLegacyEmCands]/I");
  UpgradeTree->Branch("legacyemcand_bx",legacyemcand_bx,"legacyemcand_bx[nLegacyEmCands]/I");


}

// ------------ method called once each job just after ending the event loop  ------------
void
l1t::L1UpgradeAnalyzer::endJob()
{
  //deletes necessary in endjob?
  // delete jet_hwPt;
  // delete jet_hwEta;
  // delete jet_hwPhi;
  // delete jet_hwQual;
  // delete jet_hwIso;

  // delete jet_pt;
  // delete jet_eta;
  // delete jet_phi;

  // delete tau_hwPt;
  // delete tau_hwEta;
  // delete tau_hwPhi;
  // delete tau_hwQual;
  // delete tau_hwIso;

  // delete tau_pt;
  // delete tau_eta;
  // delete tau_phi;

  // delete egamma_hwPt;
  // delete egamma_hwEta;
  // delete egamma_hwPhi;
  // delete egamma_hwQual;
  // delete egamma_hwIso;

  // delete egamma_pt;
  // delete egamma_eta;
  // delete egamma_phi;

  // delete etsum_hwPt;
  // delete etsum_hwEta;
  // delete etsum_hwPhi;
  // delete etsum_hwQual;
  // delete etsum_hwIso;
  // delete etsum_type;

  // delete etsum_pt;
  // delete etsum_eta;
  // delete etsum_phi;

  // delete region_hwPt;
  // delete region_hwEta;
  // delete region_hwPhi;
  // delete region_tauVeto;

  // delete emcand_hwPt;
  // delete emcand_hwEta;
  // delete emcand_hwPhi;
  // delete emcand_hwIso;
  // delete emcand_hwQual;
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
