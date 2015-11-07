// Read the output of the L1UpgradeAnalyzer and compare the unpacked digis with the emulator digis

// Author: R. Alex Barbieri

#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <bitset>
#include <TString.h>

enum testObject{
  Jets=0,
  EGammas=1,
  Taus=2,
  Centrality=3
};

void listMismatchedEvents(TString inputFile = "L1UnpackedPureEmulator.root", testObject type = Jets)
{
  TFile *inFile = TFile::Open(inputFile);
  TTree *emulatorResults = (TTree*)inFile->Get("EmulatorResults/L1UpgradeTree");
  TTree *unpackerResults = (TTree*)inFile->Get("UnpackerResults/L1UpgradeTree");

  int event, run, lumi;

  emulatorResults->SetBranchAddress("event",&event);
  emulatorResults->SetBranchAddress("run",&run);
  emulatorResults->SetBranchAddress("lumi",&lumi);

  std::vector<int> *e_hwPt =0;
  std::vector<int> *e_hwEta =0;
  std::vector<int> *e_hwPhi =0;
  std::vector<int> *e_bx =0;
  int e_N;
  std::vector<int> *u_hwPt =0;
  std::vector<int> *u_hwEta =0;
  std::vector<int> *u_hwPhi =0;
  std::vector<int> *u_bx =0;
  int u_N;

  TString prefix;
  TString nPrefix;
  switch(type) {
  case Jets:
    prefix = "jet";
    nPrefix = "Jet";
    break;
  case EGammas:
    prefix = "egamma";
    nPrefix = "Egamma";
    break;
  case Taus:
    prefix = "tau";
    nPrefix = "Tau";
    break;
  case Centrality:
    prefix = "hfring";
    nPrefix = "Hfring";
    break;
  default:
    prefix = "jet";
    nPrefix = "Jet";
    break;
  }

  emulatorResults->SetBranchAddress(prefix + "_hwPt",&e_hwPt);
  emulatorResults->SetBranchAddress(prefix + "_hwEta",&e_hwEta);
  emulatorResults->SetBranchAddress(prefix + "_hwPhi",&e_hwPhi);
  emulatorResults->SetBranchAddress(prefix + "_bx",&e_bx);
  emulatorResults->SetBranchAddress("n"+nPrefix,&e_N);
  unpackerResults->SetBranchAddress(prefix + "_hwPt",&u_hwPt);
  unpackerResults->SetBranchAddress(prefix + "_hwEta",&u_hwEta);
  unpackerResults->SetBranchAddress(prefix + "_hwPhi",&u_hwPhi);
  unpackerResults->SetBranchAddress(prefix + "_bx",&u_bx);
  unpackerResults->SetBranchAddress("n"+nPrefix,&u_N);

  long misses = 0;
  long entries = emulatorResults->GetEntries();
  for(long i = 0; i < entries; i++)
  {
    emulatorResults->GetEntry(i);
    unpackerResults->GetEntry(i);

    int e_offset = 0;
    int u_offset = 0;

    // e_offset will always be 0, but make sure that we are not one of the
    // 1/100 events with multiple RCT BX.
    // there are 4 taus per event, 8 jets, 8 egammas, and 1 centrality
    if(e_N == 4)
    {
      e_offset = 0;
    }
    else if (e_N == 8)
    {
      e_offset = 0;
    }
    else if (e_N == 1)
    {
      e_offset = 0;
    }
    else
    {
      // there are multiple BX here and I don't know the alignment
      // skip the event
      continue;
    }

    // there are 20 taus per events, 40 jets, 40 egammas, and 5 centralities because of extra BX
    if (u_N == 5)
    {
      u_offset = 2;
    }
    else if (u_N == 20)
    {
      u_offset = 8;
    }
    else if (u_N == 40)
    {
      u_offset = 16;
    }
    else
    {
      std::cout << "ERROR, UNKNOWN BX" << std::endl;
      std::cout << "Event: " << event << std::endl;
      continue;
    }


    for(int j = 0; j < e_N; j++)
    {
      //if(e_hwPt[e_offset+j] > 0) {
      if((((*e_hwPt)[e_offset+j])) != (((*u_hwPt)[u_offset+j])))
	{
	  std::cout << std::dec << "" << run << ":" << lumi << ":" << event << "" << std::endl;
	  //std::cout << std::dec << (*e_hwPt)[e_offset+j] << " " << (*u_hwPt)[u_offset+j] << std::endl;

	  misses++;
	  break;
	}
	//}
    }
  }
  std::cout << "Misses: " << misses << std::endl;
}

int main(int argc, char **argv)
{
  if(argc == 3)
  {
    listMismatchedEvents(argv[1], (testObject)atoi(argv[2]));
    return 0;
  } else {
    return 1;
  }
}
