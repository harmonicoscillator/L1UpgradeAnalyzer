// Read the output of the L1UpgradeAnalyzer and compare the unpacked digis with the emulator digis

// Author: R. Alex Barbieri

#include "TFile.h"
#include "TTree.h"
#include "TH1I.h"
#include "TH2I.h"
#include "TCanvas.h"
#include "TString.h"
#include "TCut.h"

void plotRctDigis(TString inputFile)
{
  TFile *inFile = TFile::Open(inputFile);
  TTree *emulatorResults = (TTree*)inFile->Get("L1UpgradeAnalyzer/EmulatorResults");
  TTree *unpackerResults = (TTree*)inFile->Get("L1UpgradeAnalyzer/UnpackerResults");

  const int nHISTS = 6;
  TString labels[nHISTS] = {"region_et", "region_eta", "region_phi", "egcand_rank", "egcand_eta", "egcand_phi"};
  TString projectionnames[nHISTS] = {"legacyregion_et", "legacyregion_gctEta", "legacyregion_gctPhi",
				     "legacyemcand_rank", "legacyemcand_regionEta", "legacyemcand_regionPhi"};
  TCut projectioncuts[nHISTS] = {"", "", "", "", "", ""};
  Int_t minBin[nHISTS] = {0, 0, 0, 0, 0, 0};
  Int_t maxBin[nHISTS] = {1024, 22, 18, 64, 22, 18};

  TH1I *hists[nHISTS][2];
  TCanvas *c[nHISTS];

  for(int i = 0; i < nHISTS; ++i)
  {
    hists[i][0] = new TH1I(labels[i], ":"+labels[i], maxBin[i]-minBin[i], minBin[i], maxBin[i]);
    hists[i][1] = hists[i][0]->Clone(labels[i]+"unpacked");

    emulatorResults->Project(hists[i][0]->GetName(), projectionnames[i], projectioncuts[i]);
    unpackerResults->Project(hists[i][1]->GetName(), projectionnames[i], projectioncuts[i]);

    hists[i][1]->SetMarkerColor(kRed);
    hists[i][1]->SetLineColor(kRed);

    c[i] = new TCanvas();
    hists[i][0]->Draw();
    hists[i][1]->Draw("same");
  }
}
