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

// ------------ method called to produce the data  ------------
void
l1t::L1UpgradeAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // boilerplate

  //edm::Handle<FEDRawDataCollection> rawdata;
  //iEvent.getByToken(FEDRawToken_, rawdata);
  //const FEDRawData& data = rawdata->FEDData(1352);
  //FEDHeader header(data.data());

  edm::Handle<L1CaloRegionCollection> legacyregions;
  edm::Handle<L1CaloEmCollection> legacyemcands;

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

  nLegacyRegions = 0;
  nLegacyEmCands = 0;

  if(doLegacyRct)
  {
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

  const unsigned int MAXSIZE = 1000;


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


  if(doLegacyRct)
  {
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
