#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TMath.h>
#include <TRint.h>
#include <TTree.h>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using ll = long long;

// Gaussian smearing function using Box-Muller transform
float edep_stdgaus() {
  float r1 = (float)rand() / RAND_MAX;
  float r2 = (float)rand() / RAND_MAX;
  return sqrt(-2. * log(r1)) * sin(2. * TMath::Pi() * r2);
}

// Energy resolution function (empirical formula)
float edep_resolution(float &edep, float &edepstdgaus) {
  float a = -.00201318113010741;
  float b = .0656080516326055;
  float c = -.0640353973874513;
  float deltaedep =
      ((a + b * sqrt(edep + c * edep * edep)) / 2.35482) * edepstdgaus;
  return edep + deltaedep;
}

// Reads ROOT data and fills histogram
void INPUT() {
  float edep;
  float edepstdgaus, edepresolution;

  // Create a histogram for energy distribution
  TH1F *hist =
      new TH1F("EnergyDistribution",
               "Energy Distribution; Energy (MeV); Events", 1000, 0, 3);

  char name[100];
  std::cout << "\nEnter the ROOT file name: ";
  std::cin >> name;

  // Open the ROOT file and access the tree "HPGe"
  TFile *file = TFile::Open(name);

  TTree *tree = static_cast<TTree *>(file->Get("HPGe"));
  double fEdep; // type root file is double
  tree->SetBranchAddress("fEdep", &fEdep);

  ll nentries = tree->GetEntries(); // Get the number of entries in the tree
  for (ll i = 0; i < nentries; i++) {
    tree->GetEntry(i); // Get data from each entry

    edep = fEdep;
    edepstdgaus = edep_stdgaus(); // Apply Gaussian smearing
    edepresolution =
        edep_resolution(edep, edepstdgaus); // Apply energy resolution

    // Fill the histogram
    hist->Fill(edepresolution);
  }
  file->Close();

  TCanvas *c1 = new TCanvas("c1", "Energy Distribution", 800, 600);
  c1->cd();
  hist->Draw();

  c1->SaveAs("EnergyDistribution.pdf");
}

// Main function
int main() {
  TRint myApp("", nullptr, nullptr);

  INPUT(); // Call the INPUT function to process data from ROOT file

  myApp.Run();

  return 0;
}
