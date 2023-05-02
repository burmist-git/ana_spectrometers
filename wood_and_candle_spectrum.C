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

Int_t wood_and_candle_spectrum(){
  TString fileN01 = "../data/30.04.2023/hist.root";
  TFile *f01 = new TFile(fileN01.Data());
  //  
  TGraph *gr_01 = (TGraph*)f01->Get("gr_background_TXT");
  TGraph *gr_02 = (TGraph*)f01->Get("gr_candle_TXT");
  TGraph *gr_03 = (TGraph*)f01->Get("gr_wood_TXT");
  //
  gr_01->SetMarkerStyle(1);
  gr_02->SetMarkerStyle(1);
  gr_03->SetMarkerStyle(1);
  //
  gr_01->SetMarkerColor(kBlack);
  gr_02->SetMarkerColor(kRed);
  gr_03->SetMarkerColor(kBlue+2);
  //
  gr_01->SetLineColor(kBlack);
  gr_02->SetLineColor(kRed);
  gr_03->SetLineColor(kBlue+2);
  //
  gr_01->SetLineWidth(2);
  gr_02->SetLineWidth(2);
  gr_03->SetLineWidth(2);
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
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_01);
  mg->Add(gr_02);
  mg->Add(gr_03);
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
  leg01->AddEntry(gr_01, "background", "pl");
  leg01->AddEntry(gr_02, "candle", "pl");
  leg01->AddEntry(gr_03, "Wooden match", "pl");
  leg01->Draw();
  //
  return 0;
}
