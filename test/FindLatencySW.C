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

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>


void FindLatencySW(){

  TFile *lFile = TFile::Open("L1UpackedReEmulator.root");
  TTree *l1Tree_emu = (TTree*)lFile->Get("EmulatorResults/L1UpgradeTree");
  TTree *l1Tree_unp = (TTree*)lFile->Get("UnpackerResults/L1UpgradeTree");

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


  l1Tree_emu->SetBranchAddress("event",&l1_event);
  l1Tree_emu->SetBranchAddress("run",&l1_run);
  l1Tree_emu->SetBranchAddress("jet_hwPt",jet_hwPt);
  l1Tree_emu->SetBranchAddress("jet_hwPhi",jet_hwPhi);
  l1Tree_emu->SetBranchAddress("jet_hwEta",jet_hwEta);
  l1Tree_emu->SetBranchAddress("jet_hwQual",jet_hwQual);
  l1Tree_emu->SetBranchAddress("jet_hwIso",jet_hwIso);
  l1Tree_emu->SetBranchAddress("jet_pt",jet_pt);
  l1Tree_emu->SetBranchAddress("jet_eta",jet_eta);
  l1Tree_emu->SetBranchAddress("jet_phi",jet_phi);

  l1Tree_emu->SetBranchAddress("egamma_hwPt",egamma_hwPt);
  l1Tree_emu->SetBranchAddress("egamma_hwPhi",egamma_hwPhi);
  l1Tree_emu->SetBranchAddress("egamma_hwEta",egamma_hwEta);
  l1Tree_emu->SetBranchAddress("egamma_hwQual",egamma_hwQual);
  l1Tree_emu->SetBranchAddress("egamma_hwIso",egamma_hwIso);
  l1Tree_emu->SetBranchAddress("egamma_pt",egamma_pt);
  l1Tree_emu->SetBranchAddress("egamma_eta",egamma_eta);
  l1Tree_emu->SetBranchAddress("egamma_phi",egamma_phi);

  l1Tree_unp->SetBranchAddress("event",&l1_event);
  l1Tree_unp->SetBranchAddress("run",&l1_run);

  l1Tree_unp->SetBranchAddress("jet_hwPt",jet_hwPt);
  l1Tree_unp->SetBranchAddress("jet_hwPhi",jet_hwPhi);
  l1Tree_unp->SetBranchAddress("jet_hwEta",jet_hwEta);
  l1Tree_unp->SetBranchAddress("jet_hwQual",jet_hwQual);
  l1Tree_unp->SetBranchAddress("jet_hwIso",jet_hwIso);
  l1Tree_unp->SetBranchAddress("jet_pt",jet_pt);
  l1Tree_unp->SetBranchAddress("jet_eta",jet_eta);
  l1Tree_unp->SetBranchAddress("jet_phi",jet_phi);

  l1Tree_unp->SetBranchAddress("egamma_hwPt",egamma_hwPt);
  l1Tree_unp->SetBranchAddress("egamma_hwPhi",egamma_hwPhi);
  l1Tree_unp->SetBranchAddress("egamma_hwEta",egamma_hwEta);
  l1Tree_unp->SetBranchAddress("egamma_hwQual",egamma_hwQual);
  l1Tree_unp->SetBranchAddress("egamma_hwIso",egamma_hwIso);
  l1Tree_unp->SetBranchAddress("egamma_pt",egamma_pt);
  l1Tree_unp->SetBranchAddress("egamma_eta",egamma_eta);
  l1Tree_unp->SetBranchAddress("egamma_phi",egamma_phi);


  Long64_t l_entries_emu = l1Tree_emu->GetEntries();
  Long64_t l_entries_unp = l1Tree_unp->GetEntries();
  if(l_entries_unp=!l_entries_emu) cout<<"ERROR, different xwwnumber of events"<<std::endl;
  else std::cout<<"number of events on the two files="<<l_entries_emu<<std::endl;

  std::vector<int> jet_hwPt_emu;
  std::vector<int> egamma_hwPt_emu;
  std::vector<int> jet_hwPt_unp;
  std::vector<int> egamma_hwPt_unp;

  
  
  for(Long64_t j = 0; j < l_entries_emu; ++j){
      l1Tree_emu->GetEntry(j);
    for (int i=0;i<4;i++){
      jet_hwPt_emu.push_back(jet_hwPt[i]);
      egamma_hwPt_emu.push_back(egamma_hwPt[i]);
      //std::cout<<"emulator with index="<<j<<", jet_hwPt="<<jet_hwPt[i]<<std::endl;
    }
  }
  
  for(Long64_t j = 0; j < l_entries_emu; ++j){
      l1Tree_unp->GetEntry(j);
    for (int i=0;i<4;i++){
      jet_hwPt_unp.push_back(jet_hwPt[i]);
      egamma_hwPt_unp.push_back(egamma_hwPt[i]);
      //std::cout<<"unpacker with index="<<j<<", jet_hwPt="<<jet_hwPt[i]<<std::endl;

    }
  }
  
  int needle_jet[] = {jet_hwPt_emu[0],jet_hwPt_emu[1],jet_hwPt_emu[2],jet_hwPt_emu[3]};
  int needle_egamma[] = {egamma_hwPt_emu[0],egamma_hwPt_emu[1],egamma_hwPt_emu[2],egamma_hwPt_emu[3]};
  std::vector<int>::iterator itjet;
  std::vector<int>::iterator itgamma;
  itjet = std::search (jet_hwPt_unp.begin(), jet_hwPt_unp.end(), needle_jet, needle_jet+4);
  itgamma = std::search (egamma_hwPt_unp.begin(), egamma_hwPt_unp.end(), needle_egamma, needle_egamma+4);

  if (itjet!=jet_hwPt_unp.end()) std::cout << "frame latency estimated with jets as " << (itjet-jet_hwPt_unp.begin())/2 << '\n';
  else std::cout << "latency for jets not found\n";
  if (itgamma!=egamma_hwPt_unp.end()) std::cout << "frame latency estimated with egammas as " << (itgamma-egamma_hwPt_unp.begin())/2 << '\n';
  else std::cout << "latency for egammas not found\n";

}


