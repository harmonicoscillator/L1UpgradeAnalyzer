#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1I.h>
#include <TH2I.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>

#include <vector>
#include <iostream>
#include <map>

const int Njets = 8;
const int Negammas = 8;
const int Ntaus = 4;
const int Netsums = 4;
const int Nregions = 396;
const int Nemcands = 144;

void DumpEvents(int isemulator=true,bool debugJets=false,bool debugEtsums=true){


  if(isemulator) std::cout<<"Dumping emulator"<<std::endl;
  else std::cout<<"Dumping unpacker"<<std::endl;
  TString l1_input= "L1UnpackedPureEmulator.root";
  TFile *lFile = TFile::Open(l1_input.Data());
  TString treename;
  if(isemulator) treename="EmulatorResults/L1UpgradeTree";
  else treename="UnpackerResults/L1UpgradeTree";
  TTree *l1Tree = (TTree*)lFile->Get(treename.Data());

  Int_t l1_event, l1_run;
  Int_t l1_num;

  Int_t jet_hwPt[Njets];
  Int_t jet_hwPhi[Njets];
  Int_t jet_hwEta[Njets];
  Int_t jet_hwQual[Njets];
  Int_t jet_hwIso[Njets];
  Double_t jet_pt[Njets];
  Double_t jet_eta[Njets];
  Double_t jet_phi[Njets];

  Int_t egamma_hwPt[Negammas];
  Int_t egamma_hwPhi[Negammas];
  Int_t egamma_hwEta[Negammas];
  Int_t egamma_hwQual[Negammas];
  Int_t egamma_hwIso[Negammas];
  Double_t egamma_pt[Negammas];
  Double_t egamma_eta[Negammas];
  Double_t egamma_phi[Negammas];

  Int_t tau_hwPt[Ntaus];
  Int_t tau_hwPhi[Ntaus];
  Int_t tau_hwEta[Ntaus];
  Int_t tau_hwQual[Ntaus];
  Int_t tau_hwIso[Ntaus];
  Double_t tau_pt[Ntaus];
  Double_t tau_eta[Ntaus];
  Double_t tau_phi[Ntaus];

  Int_t etsum_hwPt[Netsums];
  Int_t etsum_hwPhi[Netsums];
  Int_t etsum_hwEta[Netsums];
  Int_t etsum_hwQual[Netsums];
  Int_t etsum_hwIso[Netsums];
  Int_t etsum_type[Netsums];
  Double_t etsum_pt[Netsums];
  Double_t etsum_eta[Netsums];
  Double_t etsum_phi[Netsums];


  Int_t legacyregion_et[Nregions];
  Int_t legacyregion_gctEta[Nregions];
  Int_t legacyregion_gctPhi[Nregions];
  Int_t legacyregion_crate[Nregions];
  Int_t legacyregion_card[Nregions];
  Int_t legacyregion_index[Nregions];

  Int_t legacyemcand_rank[Nemcands];
  Int_t legacyemcand_regionEta[Nemcands];
  Int_t legacyemcand_regionPhi[Nemcands];
  Int_t legacyemcand_crate[Nemcands];
  Int_t legacyemcand_card[Nemcands];
  Int_t legacyemcand_index[Nemcands];
  Int_t legacyemcand_iso[Nemcands];

  l1Tree->SetBranchAddress("event",&l1_event);
  l1Tree->SetBranchAddress("run",&l1_run);

  l1Tree->SetBranchAddress("jet_hwPt",jet_hwPt);
  l1Tree->SetBranchAddress("jet_hwPhi",jet_hwPhi);
  l1Tree->SetBranchAddress("jet_hwEta",jet_hwEta);
  l1Tree->SetBranchAddress("jet_hwQual",jet_hwQual);
  l1Tree->SetBranchAddress("jet_hwIso",jet_hwIso);
  l1Tree->SetBranchAddress("jet_pt",jet_pt);
  l1Tree->SetBranchAddress("jet_eta",jet_eta);
  l1Tree->SetBranchAddress("jet_phi",jet_phi);

  l1Tree->SetBranchAddress("tau_hwPt",tau_hwPt);
  l1Tree->SetBranchAddress("tau_hwPhi",tau_hwPhi);
  l1Tree->SetBranchAddress("tau_hwEta",tau_hwEta);
  l1Tree->SetBranchAddress("tau_hwQual",tau_hwQual);
  l1Tree->SetBranchAddress("tau_hwIso",tau_hwIso);
  l1Tree->SetBranchAddress("tau_pt",tau_pt);
  l1Tree->SetBranchAddress("tau_eta",tau_eta);
  l1Tree->SetBranchAddress("tau_phi",tau_phi);

  l1Tree->SetBranchAddress("egamma_hwPt",egamma_hwPt);
  l1Tree->SetBranchAddress("egamma_hwPhi",egamma_hwPhi);
  l1Tree->SetBranchAddress("egamma_hwEta",egamma_hwEta);
  l1Tree->SetBranchAddress("egamma_hwQual",egamma_hwQual);
  l1Tree->SetBranchAddress("egamma_hwIso",egamma_hwIso);
  l1Tree->SetBranchAddress("egamma_pt",egamma_pt);
  l1Tree->SetBranchAddress("egamma_eta",egamma_eta);
  l1Tree->SetBranchAddress("egamma_phi",egamma_phi);

  l1Tree->SetBranchAddress("etsum_hwPt",etsum_hwPt);
  l1Tree->SetBranchAddress("etsum_hwPhi",etsum_hwPhi);
  l1Tree->SetBranchAddress("etsum_hwEta",etsum_hwEta);
  l1Tree->SetBranchAddress("etsum_hwQual",etsum_hwQual);
  l1Tree->SetBranchAddress("etsum_hwIso",etsum_hwIso);
  l1Tree->SetBranchAddress("etsum_type",etsum_type);
  l1Tree->SetBranchAddress("etsum_pt",etsum_pt);
  l1Tree->SetBranchAddress("etsum_eta",etsum_eta);
  l1Tree->SetBranchAddress("etsum_phi",etsum_phi);



  l1Tree->SetBranchAddress("legacyregion_et",legacyregion_et);
  l1Tree->SetBranchAddress("legacyregion_gctEta",legacyregion_gctEta);
  l1Tree->SetBranchAddress("legacyregion_gctPhi",legacyregion_gctPhi);
  l1Tree->SetBranchAddress("legacyregion_crate",legacyregion_crate);
  l1Tree->SetBranchAddress("legacyregion_card",legacyregion_card);
  l1Tree->SetBranchAddress("legacyregion_index",legacyregion_index);

  l1Tree->SetBranchAddress("legacyemcand_rank",legacyemcand_rank);
  l1Tree->SetBranchAddress("legacyemcand_regionEta",legacyemcand_regionEta);
  l1Tree->SetBranchAddress("legacyemcand_regionPhi",legacyemcand_regionPhi);
  l1Tree->SetBranchAddress("legacyemcand_crate",legacyemcand_crate);
  l1Tree->SetBranchAddress("legacyemcand_card",legacyemcand_card);
  l1Tree->SetBranchAddress("legacyemcand_index",legacyemcand_index);
  l1Tree->SetBranchAddress("legacyemcand_iso",legacyemcand_iso);
  
  TString namecoll[4]={"TotEt","TotHT","MissEt","MissHt"};


  Long64_t l_entries = l1Tree->GetEntries();
  std::cout<<"number of events="<<l_entries<<std::endl;

  for(Long64_t j = 0; j < l_entries; ++j){
    l1Tree->GetEntry(j);
    std::cout<<"=================== event="<<j<<" ==================="<<std::endl;

    if(debugJets){
      for (int i=0;i<8;i++){
      }
    }
    if(debugEtsums){
      for (int i=0;i<4;i++){
        std::cout<<"etsum_type="<<namecoll[etsum_type[i]].Data()<<", et="<<etsum_hwPt[i]<<", eta="<<etsum_hwEta[i]<<", phi="<<etsum_hwPhi[i]<<std::endl;
      }
    }
  }
}


