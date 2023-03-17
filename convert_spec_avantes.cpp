//root
#include "TROOT.h"
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TGraphErrors.h"

//C, C++
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <iomanip>
#include <time.h>

void read_spec_avantes(TString fileName, TGraphErrors *gr);

int main(int argc, char *argv[]){
  //
  clock_t start, finish;
  start = clock();
  //
  if(argc == 5 && atoi(argv[1]) == 0){
    //
    TString in_file = argv[2];
    TString gr_name = argv[3];
    TString outroot = argv[4];
    //
    std::cout<<"in_file      "<<in_file<<std::endl
	     <<"gr_name      "<<gr_name<<std::endl
	     <<"outroot      "<<outroot<<std::endl;
    ////////////////
    TFile* rootFile = new TFile(outroot.Data(), "RECREATE", " Histograms", 1);
    rootFile->cd();
    if (rootFile->IsZombie()){
      std::cout<<"  ERROR ---> file "<<outroot.Data()<<" is zombi"<<std::endl;
      assert(0);
    }
    //
    TGraphErrors*gr = new TGraphErrors();
    gr->SetNameTitle(gr_name.Data(),gr_name.Data());
    read_spec_avantes(in_file, gr);
    gr->Write();
    rootFile->Close();
    std::cout<<"  Output TGrpah file ---> "<<outroot.Data()<<std::endl;
  }
  else{
    std::cout<<"  runID [1] = 0       "<<std::endl
	     <<"        [2] - in_file "<<std::endl
	     <<"        [3] - gr_name "<<std::endl
	     <<"        [4] - outroot "<<std::endl;
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
      Wave_err = 0.1;
      Sample_err = Sample/10.0 + 10.0;
      gr->SetPointError(n,Wave_err,Sample_err);
    }
    myfile.close();
  }
}
