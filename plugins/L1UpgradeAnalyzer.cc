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
  HFBitCountToken_ = consumes<l1t::CaloSpareBxCollection>(ps.getParameter<edm::InputTag>("InputLayer2HFBitCountCollection"));
  //FEDRawToken_ = consumes<FEDRawDataCollection>(ps.getParameter<edm::InputTag>("FEDRawCollection"));

  edm::InputTag Layer1 = ps.getParameter<edm::InputTag>("InputLayer1Collection");
  if(Layer1.label() != "None")
  {
    RegionToken_ = consumes<l1t::CaloRegionBxCollection>(Layer1);
    EmCandToken_ = consumes<l1t::CaloEmCandBxCollection>(Layer1);
  }
  else
    doLayer1 = false;

  edm::InputTag rctLabel = ps.getParameter<edm::InputTag>("legacyRCTDigis");
  if(rctLabel.label() != "None")
  {
    legacyRegionToken_ = consumes<L1CaloRegionCollection>(rctLabel);
    legacyEmCandToken_ = consumes<L1CaloEmCollection>(rctLabel);
  }
  else
    doLegacyRct = false;
}

l1t::L1UpgradeAnalyzer::~L1UpgradeAnalyzer() {}

void
l1t::L1UpgradeAnalyzer::clearAllGlobalVectors()
{
      jet_hwPt.clear();
      jet_hwEta.clear();
      jet_hwPhi.clear();
      jet_hwQual.clear();
      jet_hwIso.clear();
      jet_bx.clear();

      jet_pt.clear();
      jet_eta.clear();
      jet_phi.clear();

      tau_hwPt.clear();
      tau_hwEta.clear();
      tau_hwPhi.clear();
      tau_hwQual.clear();
      tau_hwIso.clear();
      tau_bx.clear();

      tau_pt.clear();
      tau_eta.clear();
      tau_phi.clear();

      isotau_hwPt.clear();
      isotau_hwEta.clear();
      isotau_hwPhi.clear();
      isotau_hwQual.clear();
      isotau_hwIso.clear();
      isotau_bx.clear();

      isotau_pt.clear();
      isotau_eta.clear();
      isotau_phi.clear();

      egamma_hwPt.clear();
      egamma_hwEta.clear();
      egamma_hwPhi.clear();
      egamma_hwQual.clear();
      egamma_hwIso.clear();
      egamma_bx.clear();

      egamma_pt.clear();
      egamma_eta.clear();
      egamma_phi.clear();

      etsum_hwPt.clear();
      etsum_hwEta.clear();
      etsum_hwPhi.clear();
      etsum_hwQual.clear();
      etsum_hwIso.clear();
      etsum_type.clear();
      etsum_bx.clear();

      etsum_pt.clear();
      etsum_eta.clear();
      etsum_phi.clear();

      hfring_hwPt.clear();
      hfring_hwEta.clear();
      hfring_hwPhi.clear();
      hfring_hwQual.clear();
      hfring_hwIso.clear();
      hfring_bx.clear();

      hfring_pt.clear();
      hfring_eta.clear();
      hfring_phi.clear();

      hfbits_hwPt.clear();
      hfbits_hwEta.clear();
      hfbits_hwPhi.clear();
      hfbits_hwQual.clear();
      hfbits_hwIso.clear();
      hfbits_bx.clear();

      hfbits_pt.clear();
      hfbits_eta.clear();
      hfbits_phi.clear();

      region_hwPt.clear();
      region_hwEta.clear();
      region_hwPhi.clear();
      region_tauVeto.clear();
      region_bx.clear();

      emcand_hwPt.clear();
      emcand_hwEta.clear();
      emcand_hwPhi.clear();
      emcand_hwIso.clear();
      emcand_hwQual.clear();
      emcand_bx.clear();

      legacyregion_raw.clear();
      legacyregion_et.clear();
      legacyregion_gctEta.clear();
      legacyregion_gctPhi.clear();
      legacyregion_crate.clear();
      legacyregion_card.clear();
      legacyregion_index.clear();
      legacyregion_bx.clear();

      legacyemcand_raw.clear();
      legacyemcand_rank.clear();
      legacyemcand_regionEta.clear();
      legacyemcand_regionPhi.clear();
      legacyemcand_crate.clear();
      legacyemcand_card.clear();
      legacyemcand_index.clear();
      legacyemcand_iso.clear();
      legacyemcand_bx.clear();

}

// ------------ method called to produce the data  ------------
void
l1t::L1UpgradeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // boilerplate
  clearAllGlobalVectors();

  //edm::Handle<FEDRawDataCollection> rawdata;
  //iEvent.getByToken(FEDRawToken_, rawdata);
  //const FEDRawData& data = rawdata->FEDData(1352);
  //FEDHeader header(data.data());

  edm::Handle<l1t::EGammaBxCollection> egammas;
  edm::Handle<l1t::TauBxCollection> taus;
  edm::Handle<l1t::TauBxCollection> isotaus;
  edm::Handle<l1t::JetBxCollection> jets;
  edm::Handle<l1t::EtSumBxCollection> etsums;
  edm::Handle<l1t::CaloSpareBxCollection> calospares;
  edm::Handle<l1t::CaloSpareBxCollection> hfbitcounts;

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
  iEvent.getByToken(HFBitCountToken_, hfbitcounts);

  if(doLayer1) {
    iEvent.getByToken(RegionToken_, regions);
    iEvent.getByToken(EmCandToken_, emcands);
  }

  if(doLegacyRct)
  {
    iEvent.getByToken(legacyRegionToken_, legacyregions);
    iEvent.getByToken(legacyEmCandToken_, legacyemcands);
  }

  // Begin analysis
  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.id().luminosityBlock();
  //FEDBXID=header.bxID();

  nJet = 0;
  nTau = 0;
  nIsotau = 0;
  nEgamma = 0;
  nEtsum = 0;
  nHfring = 0;
  nHfbits = 0;

  nRegions = 0;
  nEMCands = 0;

  nLegacyRegions = 0;
  nLegacyEmCands = 0;

  for(int bx = egammas->getFirstBX(); bx <= egammas->getLastBX(); ++bx)
  {
    for(l1t::EGammaBxCollection::const_iterator itEGamma = egammas->begin(bx);
	itEGamma != egammas->end(bx); ++itEGamma)
    {
      egamma_hwPt.push_back(itEGamma->hwPt());
      egamma_hwEta.push_back(itEGamma->hwEta());
      egamma_hwPhi.push_back(itEGamma->hwPhi());
      egamma_hwQual.push_back(itEGamma->hwQual());
      egamma_hwIso.push_back(itEGamma->hwIso());
      egamma_pt.push_back(itEGamma->pt());
      egamma_eta.push_back(itEGamma->eta());
      egamma_phi.push_back(itEGamma->phi());
      egamma_bx.push_back(bx);

      nEgamma++;
    }
  }

  for(int bx = taus->getFirstBX(); bx <= taus->getLastBX(); ++bx)
  {
    for(l1t::TauBxCollection::const_iterator itTau = taus->begin(bx);
	itTau != taus->end(bx); ++itTau)
    {
      tau_hwPt.push_back(itTau->hwPt());
      tau_hwEta.push_back(itTau->hwEta());
      tau_hwPhi.push_back(itTau->hwPhi());
      tau_hwQual.push_back(itTau->hwQual());
      tau_hwIso.push_back(itTau->hwIso());
      tau_pt.push_back(itTau->pt());
      tau_eta.push_back(itTau->eta());
      tau_phi.push_back(itTau->phi());
      tau_bx.push_back(bx);

      nTau++;
    }
  }

  for(int bx = isotaus->getFirstBX(); bx <= isotaus->getLastBX(); ++bx)
  {
    for(l1t::TauBxCollection::const_iterator itIsoTau = isotaus->begin(bx);
	itIsoTau != isotaus->end(bx); ++itIsoTau)
    {
      isotau_hwPt.push_back(itIsoTau->hwPt());
      isotau_hwEta.push_back(itIsoTau->hwEta());
      isotau_hwPhi.push_back(itIsoTau->hwPhi());
      isotau_hwQual.push_back(itIsoTau->hwQual());
      isotau_hwIso.push_back(itIsoTau->hwIso());
      isotau_pt.push_back(itIsoTau->pt());
      isotau_eta.push_back(itIsoTau->eta());
      isotau_phi.push_back(itIsoTau->phi());
      isotau_bx.push_back(bx);

      nIsotau++;
    }
  }

  for(int bx = jets->getFirstBX(); bx <= jets->getLastBX(); ++bx)
  {
    for(l1t::JetBxCollection::const_iterator itJet = jets->begin(bx);
	itJet != jets->end(bx); ++itJet)
    {
      jet_hwPt.push_back(itJet->hwPt());
      jet_hwEta.push_back(itJet->hwEta());
      jet_hwPhi.push_back(itJet->hwPhi());
      jet_hwQual.push_back(itJet->hwQual());
      jet_hwIso.push_back(itJet->hwIso());
      jet_pt.push_back(itJet->pt());
      jet_eta.push_back(itJet->eta());
      jet_phi.push_back(itJet->phi());
      jet_bx.push_back(bx);

      nJet++;
    }
  }

  for(int bx = etsums->getFirstBX(); bx <= etsums->getLastBX(); ++bx)
  {
    for(l1t::EtSumBxCollection::const_iterator itEtSum = etsums->begin(bx);
	itEtSum != etsums->end(bx); ++itEtSum)
    {
      etsum_hwPt.push_back( itEtSum->hwPt());
      etsum_hwEta.push_back( itEtSum->hwEta());
      etsum_hwPhi.push_back( itEtSum->hwPhi());
      etsum_hwQual.push_back( itEtSum->hwQual());
      etsum_hwIso.push_back( itEtSum->hwIso());
      etsum_pt.push_back( itEtSum->pt());
      etsum_eta.push_back( itEtSum->eta());
      etsum_phi.push_back( itEtSum->phi());
      etsum_bx.push_back( bx);

      etsum_type.push_back( itEtSum->getType());

      nEtsum++;
    }
  }

  for(int bx = calospares->getFirstBX(); bx <= calospares->getLastBX(); ++bx)
  {
    for(l1t::CaloSpareBxCollection::const_iterator itCaloSpare = calospares->begin(bx);
  	itCaloSpare != calospares->end(bx); ++itCaloSpare)
    {
      if(l1t::CaloSpare::CaloSpareType::HFRingSum == itCaloSpare->getType())
      {
  	hfring_hwPt.push_back(itCaloSpare->hwPt());
  	hfring_hwEta.push_back(itCaloSpare->hwEta());
  	hfring_hwPhi.push_back(itCaloSpare->hwPhi());
  	hfring_hwQual.push_back(itCaloSpare->hwQual());
  	hfring_hwIso.push_back(itCaloSpare->hwIso());

  	hfring_pt.push_back(itCaloSpare->pt());
  	hfring_eta.push_back(itCaloSpare->eta());
  	hfring_phi.push_back(itCaloSpare->phi());

	hfring_bx.push_back(bx);

  	nHfring++;
      }
    }
  }

  for(int bx = hfbitcounts->getFirstBX(); bx <= hfbitcounts->getLastBX(); ++bx)
  {
    for(l1t::CaloSpareBxCollection::const_iterator itCaloSpare = hfbitcounts->begin(bx);
  	itCaloSpare != hfbitcounts->end(bx); ++itCaloSpare)
    {
      if (l1t::CaloSpare::CaloSpareType::HFBitCount == itCaloSpare->getType())
      {
  	hfbits_hwPt.push_back(itCaloSpare->hwPt());
  	hfbits_hwEta.push_back(itCaloSpare->hwEta());
  	hfbits_hwPhi.push_back(itCaloSpare->hwPhi());
  	hfbits_hwQual.push_back(itCaloSpare->hwQual());
  	hfbits_hwIso.push_back(itCaloSpare->hwIso());

  	hfbits_pt.push_back(itCaloSpare->pt());
  	hfbits_eta.push_back(itCaloSpare->eta());
  	hfbits_phi.push_back(itCaloSpare->phi());

	hfbits_bx.push_back(bx);

  	nHfbits++;
      }
    }
  }

  if(doLayer1)
  {
    for(int bx = regions->getFirstBX(); bx <= regions->getLastBX(); ++bx)
    {
      for(l1t::CaloRegionBxCollection::const_iterator itCaloRegion = regions->begin(bx);
	  itCaloRegion != regions->end(bx); ++itCaloRegion)
      {
	region_hwPt.push_back(itCaloRegion->hwPt());
	region_hwEta.push_back(itCaloRegion->hwEta());
	region_hwPhi.push_back(itCaloRegion->hwPhi());
	region_tauVeto.push_back(itCaloRegion->hwQual());
	region_bx.push_back(bx);

	nRegions++;
      }
    }

    for(int bx = emcands->getFirstBX(); bx <= emcands->getLastBX(); ++bx)
    {
      for(l1t::CaloEmCandBxCollection::const_iterator itCaloEmCand = emcands->begin(bx);
	  itCaloEmCand != emcands->end(bx); ++itCaloEmCand)
      {
	emcand_hwPt.push_back(itCaloEmCand->hwPt());
	emcand_hwEta.push_back(itCaloEmCand->hwEta());
	emcand_hwPhi.push_back(itCaloEmCand->hwPhi());
	emcand_hwIso.push_back(itCaloEmCand->hwIso());
	emcand_hwQual.push_back(itCaloEmCand->hwQual());
	emcand_bx.push_back(bx);

	nEMCands++;
      }
    }
  }

  if(doLegacyRct)
  {
    for(std::vector<L1CaloRegion>::const_iterator rgn=legacyregions->begin(); rgn!=legacyregions->end(); ++rgn)
    {
      legacyregion_raw.push_back(rgn->raw());
      legacyregion_et.push_back(rgn->et());
      legacyregion_gctEta.push_back(rgn->id().ieta());
      legacyregion_gctPhi.push_back(rgn->id().iphi());
      legacyregion_crate.push_back(rgn->rctCrate());
      legacyregion_card.push_back(rgn->rctCard());
      legacyregion_index.push_back(rgn->rctRegionIndex());
      legacyregion_bx.push_back(rgn->bx());

      nLegacyRegions++;
    }

    for (std::vector<L1CaloEmCand>::const_iterator em=legacyemcands->begin(); em!=legacyemcands->end(); ++em)
    {
      legacyemcand_raw.push_back(em->raw());
      legacyemcand_rank.push_back(em->rank());
      legacyemcand_regionEta.push_back(em->regionId().ieta());
      legacyemcand_regionPhi.push_back(em->regionId().iphi());
      legacyemcand_crate.push_back(em->rctCrate());
      legacyemcand_card.push_back(em->rctCard());
      legacyemcand_index.push_back(em->index());
      legacyemcand_iso.push_back(em->isolated());
      legacyemcand_bx.push_back(em->bx());

      nLegacyEmCands++;
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
  //UpgradeTree->Branch("FEDBXID", &FEDBXID, "FEDBXID/I");

  UpgradeTree->Branch("nJet",&nJet,"nJet/I");
  UpgradeTree->Branch("jet_hwPt",&jet_hwPt);
  UpgradeTree->Branch("jet_hwEta",&jet_hwEta);
  UpgradeTree->Branch("jet_hwPhi",&jet_hwPhi);
  UpgradeTree->Branch("jet_hwQual",&jet_hwQual);
  UpgradeTree->Branch("jet_hwIso",&jet_hwIso);
  UpgradeTree->Branch("jet_bx",&jet_bx);

  UpgradeTree->Branch("jet_pt",&jet_pt);
  UpgradeTree->Branch("jet_eta",&jet_eta);
  UpgradeTree->Branch("jet_phi",&jet_phi);

  UpgradeTree->Branch("nTau",&nTau,"nTau/I");
  UpgradeTree->Branch("tau_hwPt",&tau_hwPt);
  UpgradeTree->Branch("tau_hwEta",&tau_hwEta);
  UpgradeTree->Branch("tau_hwPhi",&tau_hwPhi);
  UpgradeTree->Branch("tau_hwQual",&tau_hwQual);
  UpgradeTree->Branch("tau_hwIso",&tau_hwIso);
  UpgradeTree->Branch("tau_bx",&tau_bx);

  UpgradeTree->Branch("tau_pt",&tau_pt);
  UpgradeTree->Branch("tau_eta",&tau_eta);
  UpgradeTree->Branch("tau_phi",&tau_phi);

  UpgradeTree->Branch("nIsotau",&nIsotau,"nIsotau/I");
  UpgradeTree->Branch("isotau_hwPt",&isotau_hwPt);
  UpgradeTree->Branch("isotau_hwEta",&isotau_hwEta);
  UpgradeTree->Branch("isotau_hwPhi",&isotau_hwPhi);
  UpgradeTree->Branch("isotau_hwQual",&isotau_hwQual);
  UpgradeTree->Branch("isotau_hwIso",&isotau_hwIso);
  UpgradeTree->Branch("isotau_bx",&isotau_bx);

  UpgradeTree->Branch("isotau_pt",&isotau_pt);
  UpgradeTree->Branch("isotau_eta",&isotau_eta);
  UpgradeTree->Branch("isotau_phi",&isotau_phi);

  UpgradeTree->Branch("nEgamma",&nEgamma,"nEgamma/I");
  UpgradeTree->Branch("egamma_hwPt",&egamma_hwPt);
  UpgradeTree->Branch("egamma_hwEta",&egamma_hwEta);
  UpgradeTree->Branch("egamma_hwPhi",&egamma_hwPhi);
  UpgradeTree->Branch("egamma_hwQual",&egamma_hwQual);
  UpgradeTree->Branch("egamma_hwIso",&egamma_hwIso);
  UpgradeTree->Branch("egamma_bx",&egamma_bx);

  UpgradeTree->Branch("egamma_pt",&egamma_pt);
  UpgradeTree->Branch("egamma_eta",&egamma_eta);
  UpgradeTree->Branch("egamma_phi",&egamma_phi);

  UpgradeTree->Branch("nEtsum",&nEtsum,"nEtsum/I");
  UpgradeTree->Branch("etsum_hwPt",&etsum_hwPt);
  UpgradeTree->Branch("etsum_hwEta",&etsum_hwEta);
  UpgradeTree->Branch("etsum_hwPhi",&etsum_hwPhi);
  UpgradeTree->Branch("etsum_hwQual",&etsum_hwQual);
  UpgradeTree->Branch("etsum_hwIso",&etsum_hwIso);
  UpgradeTree->Branch("etsum_type",&etsum_type);
  UpgradeTree->Branch("etsum_bx",&etsum_bx);

  UpgradeTree->Branch("etsum_pt",&etsum_pt);
  UpgradeTree->Branch("etsum_eta",&etsum_eta);
  UpgradeTree->Branch("etsum_phi",&etsum_phi);

  UpgradeTree->Branch("nHfring",&nHfring,"nHfring/I");
  UpgradeTree->Branch("hfring_hwPt",&hfring_hwPt);
  UpgradeTree->Branch("hfring_hwEta",&hfring_hwEta);
  UpgradeTree->Branch("hfring_hwPhi",&hfring_hwPhi);
  UpgradeTree->Branch("hfring_hwQual",&hfring_hwQual);
  UpgradeTree->Branch("hfring_hwIso",&hfring_hwIso);
  UpgradeTree->Branch("hfring_bx",&hfring_bx);

  UpgradeTree->Branch("hfring_pt",&hfring_pt);
  UpgradeTree->Branch("hfring_eta",&hfring_eta);
  UpgradeTree->Branch("hfring_phi",&hfring_phi);

  UpgradeTree->Branch("nHfbits",&nHfbits,"nHfbits/I");
  UpgradeTree->Branch("hfbits_hwPt",&hfbits_hwPt);
  UpgradeTree->Branch("hfbits_hwEta",&hfbits_hwEta);
  UpgradeTree->Branch("hfbits_hwPhi",&hfbits_hwPhi);
  UpgradeTree->Branch("hfbits_hwQual",&hfbits_hwQual);
  UpgradeTree->Branch("hfbits_hwIso",&hfbits_hwIso);
  UpgradeTree->Branch("hfbits_bx",&hfbits_bx);

  UpgradeTree->Branch("hfbits_pt",&hfbits_pt);
  UpgradeTree->Branch("hfbits_eta",&hfbits_eta);
  UpgradeTree->Branch("hfbits_phi",&hfbits_phi);


  if(doLayer1)
  {
    UpgradeTree->Branch("nRegions",&nRegions,"nRegions/I");
    UpgradeTree->Branch("region_hwPt",&region_hwPt);
    UpgradeTree->Branch("region_hwEta",&region_hwEta);
    UpgradeTree->Branch("region_hwPhi",&region_hwPhi);
    UpgradeTree->Branch("region_tauVeto",&region_tauVeto);
    UpgradeTree->Branch("region_bx",&region_bx);

    UpgradeTree->Branch("nEMCands",&nEMCands,"nEMCands/I");
    UpgradeTree->Branch("emcand_hwPt",&emcand_hwPt);
    UpgradeTree->Branch("emcand_hwEta",&emcand_hwEta);
    UpgradeTree->Branch("emcand_hwPhi",&emcand_hwPhi);
    UpgradeTree->Branch("emcand_hwIso",&emcand_hwIso);
    UpgradeTree->Branch("emcand_hwQual",&emcand_hwQual);
    UpgradeTree->Branch("emcand_bx",&emcand_bx);
  }

  if(doLegacyRct)
  {
    UpgradeTree->Branch("nLegacyRegions",&nLegacyRegions,"nLegacyRegions/I");
    UpgradeTree->Branch("legacyregion_raw",&legacyregion_raw);
    UpgradeTree->Branch("legacyregion_et",&legacyregion_et);
    UpgradeTree->Branch("legacyregion_gctEta",&legacyregion_gctEta);
    UpgradeTree->Branch("legacyregion_gctPhi",&legacyregion_gctPhi);
    UpgradeTree->Branch("legacyregion_crate",&legacyregion_crate);
    UpgradeTree->Branch("legacyregion_card",&legacyregion_card);
    UpgradeTree->Branch("legacyregion_index",&legacyregion_index);
    UpgradeTree->Branch("legacyregion_bx",&legacyregion_bx);

    UpgradeTree->Branch("nLegacyEmCands",&nLegacyEmCands,"nLegacyEmCands/I");
    UpgradeTree->Branch("legacyemcand_raw",&legacyemcand_raw);
    UpgradeTree->Branch("legacyemcand_rank",&legacyemcand_rank);
    UpgradeTree->Branch("legacyemcand_regionEta",&legacyemcand_regionEta);
    UpgradeTree->Branch("legacyemcand_regionPhi",&legacyemcand_regionPhi);
    UpgradeTree->Branch("legacyemcand_crate",&legacyemcand_crate);
    UpgradeTree->Branch("legacyemcand_card",&legacyemcand_card);
    UpgradeTree->Branch("legacyemcand_index",&legacyemcand_index);
    UpgradeTree->Branch("legacyemcand_iso",&legacyemcand_iso);
    UpgradeTree->Branch("legacyemcand_bx",&legacyemcand_bx);
  }
}

// ------------ method called once each job just after ending the event loop  ------------
void
l1t::L1UpgradeAnalyzer::endJob()
{
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
