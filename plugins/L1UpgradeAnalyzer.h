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
#include "DataFormats/L1TCalorimeter/interface/CaloEmCand.h"

#include "DataFormats/L1CaloTrigger/interface/L1CaloEmCand.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloRegion.h"
#include "DataFormats/L1CaloTrigger/interface/L1CaloCollections.h"

//#include <DataFormats/FEDRawData/interface/FEDRawDataCollection.h>
//#include <DataFormats/FEDRawData/interface/FEDHeader.h>
//#include <DataFormats/FEDRawData/interface/FEDTrailer.h>
//#include <DataFormats/FEDRawData/interface/FEDNumbering.h>


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

      edm::EDGetToken legacyRegionToken_;
      edm::EDGetToken legacyEmCandToken_;

      bool doLayer1 = true;
      //bool doTaus = true;
      //bool doIsoTaus = true;
      bool doLegacyRct = true;

      edm::Service<TFileService> fs;
      TTree *UpgradeTree;

      int event;
      //int FEDBXID;
      int run;
      int lumi;

      int nLegacyRegions;
      int *legacyregion_raw;
      int *legacyregion_et;
      int *legacyregion_gctEta;
      int *legacyregion_gctPhi;
      int *legacyregion_crate;
      int *legacyregion_card;
      int *legacyregion_index;
      int *legacyregion_bx;

      int nLegacyEmCands;
      int *legacyemcand_raw;
      int *legacyemcand_rank;
      int *legacyemcand_regionEta;
      int *legacyemcand_regionPhi;
      int *legacyemcand_crate;
      int *legacyemcand_card;
      int *legacyemcand_index;
      int *legacyemcand_iso;
      int *legacyemcand_bx;

  };
}

#endif
