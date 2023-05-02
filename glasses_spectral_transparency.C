//C, C++
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <math.h>

#include <time.h>

using namespace std;

Int_t glasses_spectral_transparency(){
  TString fileN01 = "../data/30.04.2023/hist.root";
  TFile *f01 = new TFile(fileN01.Data());
  //  
  TGraph *gr_01 = (TGraph*)f01->Get("gr_rNNL");
  TGraph *gr_02 = (TGraph*)f01->Get("gr_rNaOchi");
  TGraph *gr_03 = (TGraph*)f01->Get("gr_rNNA");
  TGraph *gr_04 = (TGraph*)f01->Get("gr_rPolaroid");
  TGraph *gr_05 = (TGraph*)f01->Get("gr_rRayBan");
  TGraph *gr_06 = (TGraph*)f01->Get("gr_rLAB");
  TGraph *gr_07 = (TGraph*)f01->Get("gr_rGlass");
  //
  gr_01->SetMarkerStyle(1);
  gr_02->SetMarkerStyle(1);
  gr_03->SetMarkerStyle(1);
  gr_04->SetMarkerStyle(1);
  gr_05->SetMarkerStyle(1);
  gr_06->SetMarkerStyle(1);
  gr_07->SetMarkerStyle(1);
  //
  gr_01->SetMarkerColor(kBlack);
  gr_02->SetMarkerColor(kRed);
  gr_03->SetMarkerColor(kBlue);
  gr_04->SetMarkerColor(kMagenta);
  gr_05->SetMarkerColor(kGreen+2);
  gr_06->SetMarkerColor(kBlue+2);
  gr_07->SetMarkerColor(kMagenta+2);
  //
  gr_01->SetLineColor(kBlack);
  gr_02->SetLineColor(kRed);
  gr_03->SetLineColor(kBlue);
  gr_04->SetLineColor(kMagenta);
  gr_05->SetLineColor(kGreen+2);
  gr_06->SetLineColor(kBlue+2);
  gr_07->SetLineColor(kMagenta+2);
  //
  gr_01->SetLineWidth(2);
  gr_02->SetLineWidth(2);
  gr_03->SetLineWidth(2);
  gr_04->SetLineWidth(2);
  gr_05->SetLineWidth(2);
  gr_06->SetLineWidth(2);
  gr_07->SetLineWidth(2);
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,1000);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.08);
  gPad->SetTopMargin(0.02);
  gPad->SetBottomMargin(0.08);
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_01);
  mg->Add(gr_02);
  mg->Add(gr_03);
  mg->Add(gr_04);
  mg->Add(gr_05);
  mg->Add(gr_06);
  mg->Add(gr_07);
  //mg->GetXaxis()->SetRangeUser(100,1500);
  //mg->GetYaxis()->SetRangeUser(-0.2,6.0);
  //mg->SetMinimum(1.0e-11);
  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("Wavelength, nm");
  mg->GetYaxis()->SetTitle("ADC, counts a.u.");
  //c1->SaveAs("sig_wf_sim_7km_4pe.pdf");
  //c1->SaveAs("sig_wf_sim_15km_4pe.pdf");
  //c1->SaveAs("sig_wf_sim_25km_4pe.pdf");
  TLegend *leg01 = new TLegend(0.6,0.6,0.9,0.9,"","brNDC");
  leg01->AddEntry(gr_01, "", "pl");
  leg01->AddEntry(gr_02, "", "pl");
  leg01->AddEntry(gr_03, "", "pl");
  leg01->AddEntry(gr_04, "", "pl");
  leg01->AddEntry(gr_05, "", "pl");
  leg01->AddEntry(gr_06, "", "pl");
  leg01->AddEntry(gr_07, "", "pl");
  leg01->Draw();
  //
  return 0;
}
