// Read the output of the L1UpgradeAnalyzer and compare the unpacked digis with the emulator digis

// Author: R. Alex Barbieri

#include "TFile.h"
#include "TTree.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TString.h"
#include "TCut.h"

void plotL1Digis(TString inputFile = "L1UpgradeAnalyzer.root")
{
  TH1::SetDefaultSumw2();

  TFile *inFile = TFile::Open(inputFile);
  TTree *emulatorResults = (TTree*)inFile->Get("EmulatorResults/L1UpgradeTree");
  TTree *unpackerResults = (TTree*)inFile->Get("UnpackerResults/L1UpgradeTree");

  const int nHISTS = 18;
  TString labels[nHISTS] = {"region_et", "region_eta", "region_phi",
			    "egcand_rank", "egcand_eta", "egcand_phi",
			    "central_jet_hwPt", "central_jet_hwEta", "central_jet_hwPhi",
			    "forward_jet_hwPt", "forward_jet_hwEta", "forward_jet_hwPhi",
			    "ETT", "HTT",
			    "MET Rank", "MET Phi", "MHT Rank", "MHT Phi"};
  TString projectionnames[nHISTS] = {"legacyregion_et", "legacyregion_gctEta", "legacyregion_gctPhi",
				     "legacyemcand_rank", "legacyemcand_regionEta", "legacyemcand_regionPhi",
				     "jet_hwPt", "jet_hwEta", "jet_hwPhi",
				     "jet_hwPt", "jet_hwEta", "jet_hwPhi",
				     "etsum_hwPt", "etsum_hwPt",
				     "etsum_hwPt","etsum_hwPhi","etsum_hwPt","etsum_hwPhi"};
  TCut projectioncuts[nHISTS] = {"", "", "",
				 "", "", "",
				 "(jet_hwQual&0x2)!=0x2","(jet_hwQual&0x2)!=0x2","(jet_hwQual&0x2)!=0x2",
				 "(jet_hwQual&0x2)==0x2","(jet_hwQual&0x2)==0x2","(jet_hwQual&0x2)==0x2",
				 "etsum_type==0","etsum_type==1",
				 "etsum_type==2","etsum_type==2","etsum_type==3","etsum_type==3"};
  Int_t minBin[nHISTS] = {0, 0, 0,
			  0, 0, 0,
			  0, 0, 0,
			  0, 0, 0,
			  0, 0,
			  0, 0, 0, 0};
  Int_t maxBin[nHISTS] = {1024, 22, 18,
			  64, 22, 18,
			  64,22,18,
			  64,22,18,
			  4096, 4096,
			  4096, 30, 128, 30};

  TH1I *hists[nHISTS][3];
  TCanvas *c[nHISTS];

  for(int i = 0; i < nHISTS; ++i)
  {
    hists[i][0] = new TH1I(labels[i], ";"+labels[i], maxBin[i]-minBin[i], minBin[i], maxBin[i]);
    hists[i][1] = (TH1I*)hists[i][0]->Clone(labels[i]+"unpacked");
    hists[i][2] = (TH1I*)hists[i][0]->Clone(labels[i]+"div");

    emulatorResults->Project(hists[i][0]->GetName(), projectionnames[i], projectioncuts[i]);
    unpackerResults->Project(hists[i][1]->GetName(), projectionnames[i], projectioncuts[i]);

    hists[i][2]->Divide(hists[i][1], hists[i][0]);

    hists[i][1]->SetMarkerColor(kRed);
    hists[i][1]->SetLineColor(kRed);

    c[i] = new TCanvas();
    c[i]->Divide(1,2);
    c[i]->cd(1);
    hists[i][0]->Draw("hist");
    hists[i][1]->Draw("p same");

    c[i]->cd(2);
    hists[i][2]->Draw("p e");
  }
}
