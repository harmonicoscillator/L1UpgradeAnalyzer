// Read the output of the L1UpgradeAnalyzer and compare the unpacked digis with the emulator digis

// Author: R. Alex Barbieri

#include "TFile.h"
#include "TTree.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TString.h"
#include "TCut.h"

void plotL1DigisSingleEvent(Long64_t entryNum, TString inputFile = "L1UpgradeAnalyzer.root")
{
  TH1::SetDefaultSumw2();

  TFile *inFile = TFile::Open(inputFile);
  TTree *emulatorResults = (TTree*)inFile->Get("EmulatorResults/L1UpgradeTree");
  TTree *unpackerResults = (TTree*)inFile->Get("UnpackerResults/L1UpgradeTree");

  TCut entryCut = Form("Entry$ == %i", entryNum);

  const int nHISTS = 18;
  TString labels[nHISTS] = {"region_et", "region_eta", "region_phi",
			    "egcand_rank", "egcand_eta", "egcand_phi",
			    "central_jet_hwPt", "central_jet_hwEta", "central_jet_hwPhi",
			    "forward_jet_hwPt", "forward_jet_hwEta", "forward_jet_hwPhi",
			    "iso_egamma_hwPt", "iso_egamma_hwEta", "iso_egamma_hwPhi",
			    "noniso_egamma_hwPt", "noniso_egamma_hwEta", "noniso_egamma_hwPhi"};
  TString projectionnames[nHISTS] = {"legacyregion_et", "legacyregion_gctEta", "legacyregion_gctPhi",
				     "legacyemcand_rank", "legacyemcand_regionEta", "legacyemcand_regionPhi",
				     "jet_hwPt", "jet_hwEta", "jet_hwPhi",
				     "jet_hwPt", "jet_hwEta", "jet_hwPhi",
				     "egamma_hwPt", "egamma_hwEta", "egamma_hwPhi",
				     "egamma_hwPt", "egamma_hwEta", "egamma_hwPhi"};
  TCut projectioncuts[nHISTS] = {"", "", "",
				 "", "", "",
				 "(jet_hwQual&0x2)!=0x2","(jet_hwQual&0x2)!=0x2","(jet_hwQual&0x2)!=0x2",
				 "(jet_hwQual&0x2)==0x2","(jet_hwQual&0x2)==0x2","(jet_hwQual&0x2)==0x2",
				 "egamma_hwIso==1", "egamma_hwIso==1", "egamma_hwIso==1",
				 "egamma_hwIso==0", "egamma_hwIso==0", "egamma_hwIso==0"};
  Int_t minBin[nHISTS] = {0, 0, 0,
			  0, 0, 0,
			  0, 0, 0,
			  0, 0, 0,
  			  0, 0, 0,
			  0, 0, 0};
  Int_t maxBin[nHISTS] = {1024, 22, 18,
			  64, 22, 18,
			  64,22,18,
			  64,22,18,
			  64, 22, 18,
			  64, 22, 18};
  Int_t maxIterator[nHISTS] = {396, 396, 396,
			       144, 144, 144,
			       4, 4, 4,
			       4, 4, 4,
			       4, 4, 4,
			       4, 4, 4};

  TH2I *hists[nHISTS][3];
  TCanvas *c[nHISTS];

  for(int i = 0; i < nHISTS; ++i)
  {
    hists[i][0] = new TH2I(labels[i], ";Iteration;"+labels[i], maxIterator[i], 0, maxIterator[i], maxBin[i]-minBin[i], minBin[i], maxBin[i]);
    hists[i][1] = (TH2I*)hists[i][0]->Clone(labels[i]+"unpacked");
    hists[i][2] = (TH2I*)hists[i][0]->Clone(labels[i]+"div");

    emulatorResults->Project(hists[i][0]->GetName(), projectionnames[i]+":Iteration$", projectioncuts[i]&&entryCut);
    unpackerResults->Project(hists[i][1]->GetName(), projectionnames[i]+":Iteration$", projectioncuts[i]&&entryCut);

    hists[i][2]->Divide(hists[i][1], hists[i][0]);

    hists[i][1]->SetMarkerColor(kRed);
    hists[i][1]->SetLineColor(kRed);

    c[i] = new TCanvas();
    c[i]->Divide(1,2);
    c[i]->cd(1);
    hists[i][0]->Draw("colz");
    // hists[i][1]->Draw("same");

    c[i]->cd(2);
    //hists[i][2]->Draw("colz");
    hists[i][1]->Draw("colz");
  }
}
