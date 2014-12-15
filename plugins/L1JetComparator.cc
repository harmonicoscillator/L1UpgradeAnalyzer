// L1JetComparator
//
// Author: R. Alex Barbieri
//
// Used to push the L1Trigger upgrade dataformats to a TTree
//

#ifndef L1JetComparator_h
#define L1JetComparator_h

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

//#include "DataFormats/L1Trigger/interface/EGamma.h"
//#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
//#include "DataFormats/L1Trigger/interface/EtSum.h"
//#include "DataFormats/L1Trigger/interface/CaloSpare.h"
#include "DataFormats/L1TCalorimeter/interface/CaloRegion.h"
//#include "DataFormats/L1TCalorimeter/interface/CaloEmCand.h"

#include "DataFormats/L1Trigger/interface/BXVector.h"

#include "TTree.h"
#include "TH1I.h"

namespace l1t {

  class L1JetComparator : public edm::EDAnalyzer {
  public:
    explicit L1JetComparator(const edm::ParameterSet& ps);
    virtual ~L1JetComparator();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

  private:
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    // ----------member data ---------------------------

    edm::EDGetToken JetToken1_;
    edm::EDGetToken JetToken2_;
    edm::EDGetToken RegionToken_;

    edm::Service<TFileService> fs;
    TTree *JetComparator;

    TH1I *h_cenjet1_hwPt;
    TH1I *h_cenjet1_hwEta;
    TH1I *h_cenjet1_hwPhi;
    TH1I *h_forjet1_hwPt;
    TH1I *h_forjet1_hwEta;
    TH1I *h_forjet1_hwPhi;

    TH1I *h_cenjet2_hwPt;
    TH1I *h_cenjet2_hwEta;
    TH1I *h_cenjet2_hwPhi;
    TH1I *h_forjet2_hwPt;
    TH1I *h_forjet2_hwEta;
    TH1I *h_forjet2_hwPhi;

    int event;
    int run;
    int lumi;

    int nJet1;
    int *jet1_hwPt;
    int *jet1_hwEta;
    int *jet1_hwPhi;
    int *jet1_hwQual;
    int *jet1_hwIso;

    int nJet2;
    int *jet2_hwPt;
    int *jet2_hwEta;
    int *jet2_hwPhi;
    int *jet2_hwQual;
    int *jet2_hwIso;

    int nRegions;
    int *region_hwPt;
    int *region_hwEta;
    int *region_hwPhi;
    int *region_tauVeto;
  };
}

#endif

void printNonMatching(int run, int lumi, int event)
{
  std::cout<< "Jet Collections do not Match!!" << std::endl;
  std::cout << "Run: "<<run<< " Lumi: " << lumi << " Event: " << event << std::endl;
}

l1t::L1JetComparator::L1JetComparator(const edm::ParameterSet& ps) {
  JetToken1_ = consumes<l1t::JetBxCollection>(ps.getParameter<edm::InputTag>("JetCollection1"));
  JetToken2_ = consumes<l1t::JetBxCollection>(ps.getParameter<edm::InputTag>("JetCollection2"));
  RegionToken_ = consumes<l1t::CaloRegionBxCollection>(ps.getParameter<edm::InputTag>("RegionCollection"));
}

l1t::L1JetComparator::~L1JetComparator() {}

// ------------ method called to produce the data  ------------
void
l1t::L1JetComparator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // boilerplate
  edm::Handle<l1t::JetBxCollection> jets1;
  edm::Handle<l1t::JetBxCollection> jets2;
  edm::Handle<l1t::CaloRegionBxCollection> regions;

  iEvent.getByToken(JetToken1_, jets1);
  iEvent.getByToken(JetToken2_, jets2);
  iEvent.getByToken(RegionToken_, regions);

  // int firstBX = jets1->getFirstBX();
  // int lastBX = jets1->getLastBX();

  // int firstBX2 = jets2->getFirstBX();
  // int lastBX2 = jets2->getLastBX();

  // if ((firstBX != firstBX2) || (lastBX != lastBX2) )
  // {
  //   std::cout << "BX do not match between input samples, returning." << std::endl;
  //   return;
  // }

  // Begin analysis
  event = iEvent.id().event();
  run = iEvent.id().run();
  lumi = iEvent.id().luminosityBlock();

  nJet1 = 0;
  nJet2 = 0;
  nRegions = 0;

  //for(int bx = firstBX; bx <= lastBX; ++bx)
  int bx = 0;
  {
    for(l1t::JetBxCollection::const_iterator itJet = jets1->begin(bx);
	itJet != jets1->end(bx); ++itJet)
    {
      jet1_hwPt[nJet1] = itJet->hwPt();
      jet1_hwEta[nJet1] = itJet->hwEta();
      jet1_hwPhi[nJet1] = itJet->hwPhi();
      jet1_hwQual[nJet1] = itJet->hwQual();
      jet1_hwIso[nJet1] = itJet->hwIso();

      bool forward = false;
      if((jet1_hwQual[nJet1] & 0x2) == 0x2)
	forward = true;

      if(!forward)
      {
	h_cenjet1_hwPt->Fill(jet1_hwPt[nJet1]);
	h_cenjet1_hwEta->Fill(jet1_hwEta[nJet1]);
	h_cenjet1_hwPhi->Fill(jet1_hwPhi[nJet1]);
      } else {
	h_forjet1_hwPt->Fill(jet1_hwPt[nJet1]);
	h_forjet1_hwEta->Fill(jet1_hwEta[nJet1]);
	h_forjet1_hwPhi->Fill(jet1_hwPhi[nJet1]);
      }

      nJet1++;
    }

    for(l1t::JetBxCollection::const_iterator itJet = jets2->begin(bx);
	itJet != jets2->end(bx); ++itJet)
    {
      jet2_hwPt[nJet2] = itJet->hwPt();
      jet2_hwEta[nJet2] = itJet->hwEta();
      jet2_hwPhi[nJet2] = itJet->hwPhi();
      jet2_hwQual[nJet2] = itJet->hwQual();
      jet2_hwIso[nJet2] = itJet->hwIso();

      bool forward = false;
      if((jet2_hwQual[nJet2] & 0x2) == 0x2)
	forward = true;

      if(!forward)
      {
	h_cenjet2_hwPt->Fill(jet2_hwPt[nJet2]);
	h_cenjet2_hwEta->Fill(jet2_hwEta[nJet2]);
	h_cenjet2_hwPhi->Fill(jet2_hwPhi[nJet2]);
      } else {
	h_forjet2_hwPt->Fill(jet2_hwPt[nJet2]);
	h_forjet2_hwEta->Fill(jet2_hwEta[nJet2]);
	h_forjet2_hwPhi->Fill(jet2_hwPhi[nJet2]);
      }

      nJet2++;
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

  JetComparator->Fill();

  if(nJet1 != nJet2)
    printNonMatching(run, lumi, event);

  for(int i = 0; i < nJet1; i++)
  {
    if(jet1_hwPt[i] != jet2_hwPt[i])
      printNonMatching(run,lumi,event);
    if(jet1_hwEta[i] != jet2_hwEta[i])
      printNonMatching(run,lumi,event);
    if(jet1_hwPhi[i] != jet2_hwPhi[i])
      printNonMatching(run,lumi,event);
  }
}

// ------------ method called once each job just before starting event loop  ------------
void
l1t::L1JetComparator::beginJob()
{
  JetComparator = fs->make<TTree>("JetComparator","L1 Trigger Upgrade Dataformats");

  JetComparator->Branch("event",&event,"event/I");
  JetComparator->Branch("run", &run, "run/I");
  JetComparator->Branch("lumi", &lumi, "lumi/I");

  const unsigned int MAXSIZE = 500;

  jet1_hwPt = new int[MAXSIZE];
  jet1_hwEta = new int[MAXSIZE];
  jet1_hwPhi = new int[MAXSIZE];
  jet1_hwQual = new int[MAXSIZE];
  jet1_hwIso = new int[MAXSIZE];

  jet2_hwPt = new int[MAXSIZE];
  jet2_hwEta = new int[MAXSIZE];
  jet2_hwPhi = new int[MAXSIZE];
  jet2_hwQual = new int[MAXSIZE];
  jet2_hwIso = new int[MAXSIZE];

  region_hwPt = new int[MAXSIZE];
  region_hwEta = new int[MAXSIZE];
  region_hwPhi = new int[MAXSIZE];
  region_tauVeto = new int[MAXSIZE];

  JetComparator->Branch("nJet1",&nJet1,"nJet1/I");
  JetComparator->Branch("jet1_hwPt",jet1_hwPt,"jet1_hwPt[nJet1]/I");
  JetComparator->Branch("jet1_hwEta",jet1_hwEta,"jet1_hwEta[nJet1]/I");
  JetComparator->Branch("jet1_hwPhi",jet1_hwPhi,"jet1_hwPhi[nJet1]/I");
  JetComparator->Branch("jet1_hwQual",jet1_hwQual,"jet1_hwQual[nJet1]/I");
  JetComparator->Branch("jet1_hwIso",jet1_hwIso,"jet1_hwIso[nJet1]/I");

  JetComparator->Branch("nJet2",&nJet2,"nJet2/I");
  JetComparator->Branch("jet2_hwPt",jet2_hwPt,"jet2_hwPt[nJet2]/I");
  JetComparator->Branch("jet2_hwEta",jet2_hwEta,"jet2_hwEta[nJet2]/I");
  JetComparator->Branch("jet2_hwPhi",jet2_hwPhi,"jet2_hwPhi[nJet2]/I");
  JetComparator->Branch("jet2_hwQual",jet2_hwQual,"jet2_hwQual[nJet2]/I");
  JetComparator->Branch("jet2_hwIso",jet2_hwIso,"jet2_hwIso[nJet2]/I");

  JetComparator->Branch("nRegions",&nRegions,"nRegions/I");
  JetComparator->Branch("region_hwPt",region_hwPt,"region_hwPt[nRegions]/I");
  JetComparator->Branch("region_hwEta",region_hwEta,"region_hwEta[nRegions]/I");
  JetComparator->Branch("region_hwPhi",region_hwPhi,"region_hwPhi[nRegions]/I");
  JetComparator->Branch("region_tauVeto",region_tauVeto,"region_tauVeto[nRegions]/I");

  // h_cenjet1_hwPt = new TH1I("h_cenjet1_hwPt","cenjet1_hwPt",64,0,64);
  // h_cenjet1_hwEta = new TH1I("h_cenjet1_hwEta","cenjet1_hwEta",16,0,16);
  // h_centjet1_hwPhi = new TH1I("h_cenjet1_hwPhi","cenjet1_hwPhi",18,0,18);
  // h_forjet1_hwPt = new TH1I("h_forjet1_hwPt","forjet1_hwPt",64,0,64);
  // h_forjet1_hwEta = new TH1I("h_forjet1_hwEta","forjet1_hwEta",16,0,16);
  // h_forjet1_hwPhi = new TH1I("h_forjet1_hwPhi","forjet1_hwPhi",18,0,18);

  // h_cenjet2_hwPt = new TH1I("h_cenjet2_hwPt","cenjet2_hwPt",64,0,64);
  // h_cenjet2_hwEta = new TH1I("h_cenjet2_hwEta","cenjet2_hwEta",16,0,16);
  // h_cenjet2_hwPhi = new TH1I("h_cenjet2_hwPhi","cenjet2_hwPhi",18,0,18);
  // h_forjet2_hwPt = new TH1I("h_forjet2_hwPt","forjet2_hwPt",64,0,64);
  // h_forjet2_hwEta = new TH1I("h_forjet2_hwEta","forjet2_hwEta",16,0,16);
  // h_forjet2_hwPhi = new TH1I("h_forjet2_hwPhi","forjet2_hwPhi",18,0,18);
  h_cenjet1_hwPt = fs->make<TH1I>("h_cenjet1_hwPt","cenjet1_hwPt",64,0,64);
  h_cenjet1_hwEta = fs->make<TH1I>("h_cenjet1_hwEta","cenjet1_hwEta",16,0,16);
  h_cenjet1_hwPhi = fs->make<TH1I>("h_cenjet1_hwPhi","cenjet1_hwPhi",18,0,18);
  h_forjet1_hwPt = fs->make<TH1I>("h_forjet1_hwPt","forjet1_hwPt",64,0,64);
  h_forjet1_hwEta = fs->make<TH1I>("h_forjet1_hwEta","forjet1_hwEta",16,0,16);
  h_forjet1_hwPhi = fs->make<TH1I>("h_forjet1_hwPhi","forjet1_hwPhi",18,0,18);

  h_cenjet2_hwPt = fs->make<TH1I>("h_cenjet2_hwPt","cenjet2_hwPt",64,0,64);
  h_cenjet2_hwEta = fs->make<TH1I>("h_cenjet2_hwEta","cenjet2_hwEta",16,0,16);
  h_cenjet2_hwPhi = fs->make<TH1I>("h_cenjet2_hwPhi","cenjet2_hwPhi",18,0,18);
  h_forjet2_hwPt = fs->make<TH1I>("h_forjet2_hwPt","forjet2_hwPt",64,0,64);
  h_forjet2_hwEta = fs->make<TH1I>("h_forjet2_hwEta","forjet2_hwEta",16,0,16);
  h_forjet2_hwPhi = fs->make<TH1I>("h_forjet2_hwPhi","forjet2_hwPhi",18,0,18);
}

// ------------ method called once each job just after ending the event loop  ------------
void
l1t::L1JetComparator::endJob()
{
  // h_cenjet1_hwPt->Write();
  // h_cenjet1_hwEta->Write();
  // h_centjet1_hwPhi->Write();
  // h_forjet1_hwPt->Write();
  // h_forjet1_hwEta->Write();
  // h_forjet1_hwPhi->Write();

  // h_cenjet2_hwPt->Write();
  // h_cenjet2_hwEta->Write();
  // h_cenjet2_hwPhi->Write();
  // h_forjet2_hwPt->Write();
  // h_forjet2_hwEta->Write();
  // h_forjet2_hwPhi->Write();

  delete jet1_hwPt;
  delete jet1_hwEta;
  delete jet1_hwPhi;
  delete jet1_hwQual;
  delete jet1_hwIso;

  delete jet2_hwPt;
  delete jet2_hwEta;
  delete jet2_hwPhi;
  delete jet2_hwQual;
  delete jet2_hwIso;

  delete region_hwPt;
  delete region_hwEta;
  delete region_hwPhi;
  delete region_tauVeto;

  // delete h_cenjet1_hwPt;
  // delete h_cenjet1_hwEta;
  // delete h_centjet1_hwPhi;
  // delete h_forjet1_hwPt;
  // delete h_forjet1_hwEta;
  // delete h_forjet1_hwPhi;

  // delete h_cenjet2_hwPt;
  // delete h_cenjet2_hwEta;
  // delete h_cenjet2_hwPhi;
  // delete h_forjet2_hwPt;
  // delete h_forjet2_hwEta;
  // delete h_forjet2_hwPhi;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
l1t::L1JetComparator::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(l1t::L1JetComparator);
