//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TMath.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <time.h>

void read_spec_avantes(TString fileName, TGraphErrors *gr);
void get_ration(TGraphErrors *gr_r, TGraphErrors *gr, TGraphErrors *gr_n);
Double_t get_wl_err(Double_t wl);
Double_t get_sample_err(Double_t a);

int main(int argc, char *argv[]){
  //
  clock_t start, finish;
  start = clock();
  //
  if(argc == 4 && atoi(argv[1]) == 0){
    //
    TString info_file = argv[2];
    TString outroot   = argv[3];
    //
    std::cout<<"info_file "<<info_file<<std::endl
	     <<"outroot   "<<outroot<<std::endl;
    //    
    TString in_file;
    TString gr_name;
    ////////////////
    TFile* rootFile = new TFile(outroot.Data(), "RECREATE", " Histograms", 1);
    rootFile->cd();
    if (rootFile->IsZombie()){
      std::cout<<"  ERROR ---> file "<<outroot.Data()<<" is zombi"<<std::endl;
      assert(0);
    }
    //
    std::vector<TGraphErrors*> gr_v;
    std::ifstream myfile(info_file.Data());
    if(myfile.is_open()){
      while(myfile>>in_file>>gr_name){
	TGraphErrors *gr = new TGraphErrors();
	gr->SetNameTitle(gr_name.Data(),gr_name.Data());
	read_spec_avantes(in_file, gr);
	//gr->Write();
	gr_v.push_back(gr);
	//gr->Delete();
      }
      myfile.close();
    }
    //
    for(unsigned int i = 0;i<gr_v.size();i++){
      gr_v.at(i)->Write();
      std::cout<<i<<" "<<gr_v.at(i)->GetTitle()<<std::endl;
    }
    //0.4mm
    TGraphErrors *gr_r01 = new TGraphErrors();
    gr_r01->SetNameTitle("gr_0_4mm_resin_R","gr_0_4mm_resin_R");
    get_ration(gr_r01, gr_v.at(0),gr_v.at(1));
    gr_r01->Write();
    //1.12mm
    TGraphErrors *gr_r02 = new TGraphErrors();
    gr_r02->SetNameTitle("gr_1_12mm_resin_R","gr_1_12mm_resin_R");
    get_ration(gr_r02, gr_v.at(2),gr_v.at(3));
    gr_r02->Write();
    //1.4mm
    TGraphErrors *gr_r03 = new TGraphErrors();
    gr_r03->SetNameTitle("gr_1_4mm_resin_R","gr_1_4mm_resin_R");
    get_ration(gr_r03, gr_v.at(4),gr_v.at(5));
    gr_r03->Write();
    //
    rootFile->Close();
    std::cout<<"  Output TGrpah file ---> "<<outroot.Data()<<std::endl;
  }
  else{
    std::cout<<"  runID [1] = 0         "<<std::endl
	     <<"        [2] - info file "<<std::endl
	     <<"        [4] - outroot   "<<std::endl;
  }  //
  finish = clock();
  std::cout<<"-------------------------"<<std::endl
  	   <<"Working time : "<<((finish - start)/CLOCKS_PER_SEC)<<" (sec)"<<std::endl
  	   <<"-------------------------"<<std::endl;
  //
  return 0;
}

//0.4mm
//Integration time [ms]:   1.000
//Averaging Nr. [scans]: 10
//Smoothing Nr. [pixels]: 1
//Data measured with spectrometer [name]: 1808445U1
//Wave   Sample   Dark     ReferenceScope
//[nm]   [counts] [counts] [counts] 
//
//176.578   20.295  496.001  496.001
//176.920    3.450  397.679  397.679
//177.262   -7.423  138.903  138.903
//177.604    8.920 -146.109 -146.109
//177.946    2.223 -151.693 -151.693
void read_spec_avantes(TString fileName, TGraphErrors *gr){
  std::cout<<" Reading --> "<<fileName<<std::endl;
  std::ifstream myfile(fileName.Data());
  std::string mot=" ";
  Double_t Wave;
  Double_t Sample;
  Double_t Wave_err;
  Double_t Sample_err;
  Double_t Dark;
  Double_t ReferenceScope;
  if(myfile.is_open()){
    while(mot!="ReferenceScope")
      myfile>>mot;
    myfile>>mot;
    myfile>>mot;
    myfile>>mot;
    myfile>>mot;
    //myfile>>mot;
    //std::cout<<"mot "<<mot<<std::endl;
    while(myfile>>Wave>>Sample>>Dark>>ReferenceScope){
      //std::cout<<"Wave "<<Wave<<"Sample "<<Sample<<std::endl;
      Int_t n = gr->GetN();
      gr->SetPoint( n, Wave, Sample);
      Wave_err = get_wl_err(Wave);
      Sample_err = get_sample_err(Sample);
      gr->SetPointError(n,Wave_err,Sample_err);
    }
    myfile.close();
  }
}

void get_ration(TGraphErrors *gr_r, TGraphErrors *gr, TGraphErrors *gr_n){
  Int_t n = gr->GetN();
  Int_t nr = 0;
  Double_t wl, a, an, r;
  Double_t wl_err, a_err, an_err, r_err;
  for(Int_t i = 0;i<n;i++){
    gr->GetPoint(i,wl,a);
    an = gr_n->Eval(wl);
    wl_err = get_wl_err(wl);
    a_err = get_sample_err(a);
    an_err = get_sample_err(an);
    if(an>0.0 && a>0.0){
      r = a/an;
      r_err = r*TMath::Sqrt(a_err/a*a_err/a + an_err/an*an_err/an);
      gr_r->SetPoint( nr, wl, r);
      gr_r->SetPointError( nr, wl_err, r_err);
      nr++;
    }
  }
}

Double_t get_wl_err(Double_t wl){
  return 0.1;
}

Double_t get_sample_err(Double_t a){
  return a/10.0 + 10.0;
}
