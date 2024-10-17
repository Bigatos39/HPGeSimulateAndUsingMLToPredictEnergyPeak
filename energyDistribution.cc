#include <cmath>
#include <iostream>
#include <string>
#include <vector>

double gausFuncion(double *x, double *par) {
  return ((1 / sqrt(2 * TMath::Pi()) * par[1]) *
          TMath::Exp((-1 / 2) * pow((x[0] - par[0]) / par[1], 2))) *
         par[2];
}

void energyDistribution() {
  const std::string rootFile;

  std::cout << "Name of ROOT file: ";
  std::cin >> rootFile;

  TFile *f = new TFile(rootFile);
  TTree *tree = static_cast<TTree *>(f->Get("HPGe"));
  int nEntries = tree->GetEntries();

  // Get sigma
  float FWHM;
  std::cout << "FWHM is: ";
  std::cin >> FWHM;
  float sigma = FWHM / (2 * sqrt(2 * log(2)));

  TH1F *h1 = new TH1F("Energy Distribution", "Energy Distribution", 400, 0, 3);
  float eDep;
  tree->SetBranchAddress("eDep", &eDep);

  for (int i = 0; i < nEntries; i++) {
    tree->GetEntry(i);

    double par[3] = {eDep, sigma, 1};
    for (int j = 0; j < 400; j++) {
      double x = h1->GetXaxis()->GetBinCenter(j + 1);
      h1->Fill(x, gausFuncion(&x, par)); // Fill histogram with Gaussian value
    }
  }

  TCanvas *c = new TCanvas();
  c->cd();
  h1->Draw();
}
