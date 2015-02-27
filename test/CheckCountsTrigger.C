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

void CheckCountsTrigger(bool isemulator=true){

  TString l1_input= "L1UnpackedPureEmulator.root";
  TString treefilename;
  if(isemulator) treefilename="EmulatorResults/L1UpgradeTree";
  else treefilename="UnpackerResults/L1UpgradeTree";
  TFile *lFile = TFile::Open(l1_input.Data());
  TTree *l1Tree = (TTree*)lFile->Get(treefilename.Data());
  
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

  Int_t isotau_hwPt[Ntaus];
  Int_t isotau_hwPhi[Ntaus];
  Int_t isotau_hwEta[Ntaus];
  Int_t isotau_hwQual[Ntaus];
  Int_t isotau_hwIso[Ntaus];
  Double_t isotau_pt[Ntaus];
  Double_t isotau_eta[Ntaus];
  Double_t isotau_phi[Ntaus];


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

  l1Tree->SetBranchAddress("isotau_hwPt",isotau_hwPt);
  l1Tree->SetBranchAddress("isotau_hwPhi",isotau_hwPhi);
  l1Tree->SetBranchAddress("isotau_hwEta",isotau_hwEta);
  l1Tree->SetBranchAddress("isotau_hwQual",isotau_hwQual);
  l1Tree->SetBranchAddress("isotau_hwIso",isotau_hwIso);
  l1Tree->SetBranchAddress("isotau_pt",isotau_pt);
  l1Tree->SetBranchAddress("isotau_eta",isotau_eta);
  l1Tree->SetBranchAddress("isotau_phi",isotau_phi);

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
  
  
  const int jetsteps=6;
  const int egammasteps=7;
  const int isoegammasteps=6;
  const int tausteps=6;
  const int isotausteps=6;
  
  int isjetsabove[jetsteps]={0,0,0,0,0,0};
  int isegammasabove[egammasteps]={0,0,0,0,0,0};
  int isisoegammasabove[isoegammasteps]={0,0,0,0,0,0};
  int istausabove[tausteps]={0,0,0,0,0,0};
  int isisotausabove[isotausteps]={0,0,0,0,0,0};

  double energyjetthres[jetsteps]={16.,32.,52.,68.,92.,128.};
  double energyegammathres[egammasteps]={5.,10.,20.,25.,30.,35.,40.};
  double energyisoegammathres[isoegammasteps]={18.,20.,22.,25.,28.,30};
  double energytauthres[tausteps]={16.,32.,52.,68.,92.,128.};
  double energyisotauthres[isotausteps]={16.,32.,52.,68.,92.,128.};


  Long64_t l_entries = l1Tree->GetEntries();
  std::cout<<"number of events="<<l_entries<<std::endl;

  for(Long64_t j = 0; j < l_entries; ++j){
    l1Tree->GetEntry(j);

    int counter_jetsabove[jetsteps]={0,0,0,0,0,0};
    int counter_egammasabove[egammasteps]={0,0,0,0,0,0,0};
    int counter_isoegammasabove[isoegammasteps]={0,0,0,0,0,0};
    int counter_tausabove[tausteps]={0,0,0,0,0,0};
    int counter_isotausabove[isotausteps]={0,0,0,0,0,0};


    for (int i=0;i<Njets;i++){
       
      for(int m=0;m<jetsteps;m++) {if((jet_hwPt[i]*4)>energyjetthres[m])  counter_jetsabove[m]++;}
      for(int m=0;m<egammasteps;m++) {if((egamma_hwPt[i]*4)>energyegammathres[m])  counter_egammasabove[m]++;}
      for(int m=0;m<isoegammasteps;m++) { if((egamma_hwPt[i]*4)>energyisoegammathres[m] && egamma_hwIso[i]==1) counter_isoegammasabove[m]++;}
    }

    for (int i=0;i<Ntaus;i++){

      for(int m=0;m<tausteps;m++) {if((tau_hwPt[i]*4)>energytauthres[m])  counter_tausabove[m]++;}
      for(int m=0;m<isotausteps;m++) {if((isotau_hwPt[i]*4)>energyisotauthres[m])  counter_isotausabove[m]++;}
    }


    for(int m=0;m<jetsteps;m++){ if(counter_jetsabove[m]>0)isjetsabove[m]++; }
    for(int m=0;m<egammasteps;m++){ if(counter_egammasabove[m]>0)isegammasabove[m]++; }
    for(int m=0;m<isoegammasteps;m++){ if(counter_isoegammasabove[m]>0)isisoegammasabove[m]++; }
    for(int m=0;m<tausteps;m++){ if(counter_tausabove[m]>0)istausabove[m]++; }
    for(int m=0;m<isotausteps;m++){ if(counter_isotausabove[m]>0)isisotausabove[m]++; }

  }

  cout<<"--------------- jets --------------"<<endl;
  for(int m=0;m<jetsteps;m++){ cout<<"number of events with a jet above="<<energyjetthres[m]<<" is ="<<isjetsabove[m]<<endl; }
  cout<<"--------------- egammas --------------"<<endl;
  for(int m=0;m<egammasteps;m++){ cout<<"number of events with a jet above="<<energyegammathres[m]<<" is ="<<isegammasabove[m]<<endl; }
  cout<<"--------------- iso egammas --------------"<<endl;
  for(int m=0;m<isoegammasteps;m++){ cout<<"number of events with a jet above="<<energyisoegammathres[m]<<" is ="<<isisoegammasabove[m]<<endl; }
  cout<<"--------------- tau --------------"<<endl;
  for(int m=0;m<tausteps;m++){ cout<<"number of events with a tau above="<<energytauthres[m]<<" is ="<<istausabove[m]<<endl; }
  cout<<"--------------- isotaus --------------"<<endl;
  for(int m=0;m<isotausteps;m++){ cout<<"number of events with a isotau above="<<energyisotauthres[m]<<" is ="<<isisotausabove[m]<<endl; }

}


