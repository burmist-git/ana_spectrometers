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

Int_t plots_IV(){
  TString fileN01 = "../data/IrradiationTests/01_0_Gy/hist.root";
  TString fileN02 = "../data/IrradiationTests/02_1_Gy/hist.root";
  TString fileN03 = "../data/IrradiationTests/03_2_Gy/hist.root";
  TString fileN04 = "../data/IrradiationTests/04_3_Gy/hist.root";
  TString fileN05 = "../data/IrradiationTests/05_5_Gy/hist.root";
  TString fileN06 = "../data/IrradiationTests/06_5_Gy_ND/hist.root";
  TString fileN07 = "../data/IrradiationTests/07_7_Gy/hist.root";
  TString fileN08 = "../data/IrradiationTests/08_10_Gy/hist.root";
  TString fileN09 = "../data/IrradiationTests/09_20_Gy/hist.root";
  TString fileN10 = "../data/IrradiationTests/10_30_Gy/hist.root";

  
  
  
  
  
  
  

  
  TFile *f01 = new TFile(fileN01.Data());
  TFile *f02 = new TFile(fileN02.Data());
  TGraph *gr_01 = (TGraph*)f01->Get("gr_G0_IV_PCB1_S3_35um_wores_ch01_K6487_n1");
  TGraph *gr_02 = (TGraph*)f02->Get("gr_G30_IV_PCB1_S4_35um_wores_ch01_K6487_n1");
  //
  gr_01->SetMarkerStyle(1);
  gr_02->SetMarkerStyle(1);
  //
  gr_01->SetMarkerColor(kBlack);
  gr_02->SetMarkerColor(kRed);
  //
  gr_01->SetLineColor(kBlack);
  gr_02->SetLineColor(kRed);
  //
  gr_01->SetLineWidth(2);
  gr_02->SetLineWidth(2);
  //
  TCanvas *c1 = new TCanvas("c1","c1",10,10,1200,400);
  gStyle->SetPalette(1);
  gStyle->SetFrameBorderMode(0);
  gROOT->ForceStyle();
  gStyle->SetOptStat(kFALSE);
  //  
  c1->SetRightMargin(0.01);
  c1->SetLeftMargin(0.08);
  c1->SetTopMargin(0.02);
  c1->SetBottomMargin(0.08);
  //
  //
  gPad->SetGridx();
  gPad->SetGridy();
  //
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(gr_01);
  mg->Add(gr_02);
  ///mg->GetXaxis()->SetRangeUser(4950,6000);
  //mg->GetYaxis()->SetRangeUser(-0.2,6.0);
  mg->SetMinimum(1.0e-11);
  mg->Draw("APL");
  //mg->GetXaxis()->SetTitle("time, ns");
  //mg->GetYaxis()->SetTitle("Amplitude, single p.e.");
  //c1->SaveAs("sig_wf_sim_7km_4pe.pdf");
  //c1->SaveAs("sig_wf_sim_15km_4pe.pdf");
  //c1->SaveAs("sig_wf_sim_25km_4pe.pdf");
  return 0;
}
