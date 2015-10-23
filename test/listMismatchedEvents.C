// Read the output of the L1UpgradeAnalyzer and compare the unpacked digis with the emulator digis

// Author: R. Alex Barbieri

#include "TFile.h"
#include "TTree.h"
#include <iostream>

void listMismatchedEvents(TString inputFile = "L1UnpackedPureEmulator.root")
{
  TFile *inFile = TFile::Open(inputFile);
  TTree *emulatorResults = (TTree*)inFile->Get("EmulatorResults/L1UpgradeTree");
  TTree *unpackerResults = (TTree*)inFile->Get("UnpackerResults/L1UpgradeTree");

  int event, run, lumi;

  emulatorResults->SetBranchAddress("event",&event);
  emulatorResults->SetBranchAddress("run",&run);
  emulatorResults->SetBranchAddress("lumi",&lumi);

  int e_hfring_hwPt[40];
  int e_hfring_bx[40];
  int e_nHfring;
  int u_hfring_hwPt[40];
  int u_hfring_bx[40];
  int u_nHfring;

  emulatorResults->SetBranchAddress("hfring_hwPt",e_hfring_hwPt);
  emulatorResults->SetBranchAddress("hfring_bx",e_hfring_bx);
  emulatorResults->SetBranchAddress("nHfring",&e_nHfring);
  unpackerResults->SetBranchAddress("hfring_hwPt",u_hfring_hwPt);
  unpackerResults->SetBranchAddress("hfring_bx",u_hfring_bx);
  unpackerResults->SetBranchAddress("nHfring",&u_nHfring);

  long misses = 0;
  long entries = emulatorResults->GetEntries();
  for(long i = 0; i < entries; i++)
  {
    emulatorResults->GetEntry(i);
    unpackerResults->GetEntry(i);

    int e_offset = 0;
    int u_offset = 0;

    if(e_nHfring == 1)
    {
      e_offset = 0;
    }
    else if (e_nHfring == 5)
    {
      e_offset = 2;
      continue;
    }
    else
    {
      std::cout << "ERROR, UNKNOWN BX" << std::endl;
      std::cout << "Event: " << event << std::endl;
      continue;
    }

    if(u_nHfring == 1)
    {
      u_offset = 0;
    }
    else if (u_nHfring == 5)
    {
      u_offset = 2;
    }
    else
    {
      std::cout << "ERROR, UNKNOWN BX" << std::endl;
      std::cout << "Event: " << event << std::endl;
      continue;
    }


    for(int j = 0; j < 1; j++)
    {
      if(e_hfring_hwPt[e_offset+j] != u_hfring_hwPt[u_offset+j])
      {
	//std::cout << "MISMATCHED EVENT:" <<std::endl;
	std::cout << "\"" << run << ":" << lumi << ":" << event << "\"," << std::endl;
	std::cout << "Emu: " << e_hfring_hwPt[e_offset+j] << " Unp: " << u_hfring_hwPt[u_offset+j] << std::endl;
	misses++;
	break;
      }
    }
  }
  std::cout << "Misses: " << misses << std::endl;
}

int main(int argc, char **argv)
{
  if(argc == 2)
  {
    listMismatchedEvents(argv[1]);
    return 0;
  } else {
    return 1;
  }
}
