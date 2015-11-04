// Read the output of the L1UpgradeAnalyzer and compare the unpacked digis with the emulator digis

// Author: R. Alex Barbieri

#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include <bitset>

void listMismatchedEvents(TString inputFile = "L1UnpackedPureEmulator.root")
{
  TFile *inFile = TFile::Open(inputFile);
  TTree *emulatorResults = (TTree*)inFile->Get("EmulatorResults/L1UpgradeTree");
  TTree *unpackerResults = (TTree*)inFile->Get("UnpackerResults/L1UpgradeTree");

  int event, run, lumi;

  emulatorResults->SetBranchAddress("event",&event);
  emulatorResults->SetBranchAddress("run",&run);
  emulatorResults->SetBranchAddress("lumi",&lumi);

  std::vector<int> *e_tau_hwPt =0;
  std::vector<int> *e_tau_hwEta =0;
  std::vector<int> *e_tau_hwPhi =0;
  std::vector<int> *e_tau_bx =0;
  int e_nTau;
  std::vector<int> *u_tau_hwPt =0;
  std::vector<int> *u_tau_hwEta =0;
  std::vector<int> *u_tau_hwPhi =0;
  std::vector<int> *u_tau_bx =0;
  int u_nTau;

  emulatorResults->SetBranchAddress("tau_hwPt",&e_tau_hwPt);
  emulatorResults->SetBranchAddress("tau_hwEta",&e_tau_hwEta);
  emulatorResults->SetBranchAddress("tau_hwPhi",&e_tau_hwPhi);
  emulatorResults->SetBranchAddress("tau_bx",&e_tau_bx);
  emulatorResults->SetBranchAddress("nTau",&e_nTau);
  unpackerResults->SetBranchAddress("tau_hwPt",&u_tau_hwPt);
  unpackerResults->SetBranchAddress("tau_hwEta",&u_tau_hwEta);
  unpackerResults->SetBranchAddress("tau_hwPhi",&u_tau_hwPhi);
  unpackerResults->SetBranchAddress("tau_bx",&u_tau_bx);
  unpackerResults->SetBranchAddress("nTau",&u_nTau);

  long misses = 0;
  long entries = emulatorResults->GetEntries();
  for(long i = 0; i < entries; i++)
  {
    emulatorResults->GetEntry(i);
    unpackerResults->GetEntry(i);

    int e_offset = 0;
    int u_offset = 0;

    if(e_nTau == 4)
    {
      e_offset = 0;
    }
    else if (e_nTau == 20)
    {
      e_offset = 8;
      continue;
    }
    else
    {
      std::cout << "ERROR, UNKNOWN BX" << std::endl;
      std::cout << "Event: " << event << std::endl;
      continue;
    }

    if(u_nTau == 4)
    {
      u_offset = 0;
    }
    else if (u_nTau == 20)
    {
      u_offset = 8;
    }
    else
    {
      std::cout << "ERROR, UNKNOWN BX" << std::endl;
      std::cout << "Event: " << event << std::endl;
      continue;
    }


    for(int j = 0; j < 4; j++)
    {
      //if(e_tau_hwPt[e_offset+j] > 0) {
      if((((*e_tau_hwPt)[e_offset+j])) != (((*u_tau_hwPt)[u_offset+j])))
	{
	  //std::cout << "MISMATCHED EVENT:" <<std::endl;
	  std::cout << std::dec << "" << run << ":" << lumi << ":" << event << "" << std::endl;
	  std::cout << std::dec << (*e_tau_hwPt)[e_offset+j] << " " << (*u_tau_hwPt)[u_offset+j] << std::endl;

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
  if(argc == 2)
  {
    listMismatchedEvents(argv[1]);
    return 0;
  } else {
    return 1;
  }
}
