//my
#include "infoStr.hh"

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

void read_K6487(TString fileName, TGraphErrors *gr);
void read_K2400(TString fileName, TGraphErrors *gr);

int main(int argc, char *argv[]){
  //
  clock_t start, finish;
  start = clock();
  //
  if(argc == 5 && atoi(argv[1]) == 0){
    //
    TString input_dir = argv[2];
    TString info_file = argv[3];
    TString outputRootFile = argv[4];
    //
    std::cout<<std::endl
	     <<"input_dir      "<<input_dir<<std::endl
	     <<"info_file      "<<info_file<<std::endl
    	     <<"outputRootFile "<<outputRootFile<<std::endl;
    infoStr info_s;
    info_s.readFromFile(info_file.Data());
    info_s.printInfo();
    ////////////////
    TFile* rootFile = new TFile(outputRootFile.Data(), "RECREATE", " Histograms", 1);
    rootFile->cd();
    if (rootFile->IsZombie()){
      std::cout<<"  ERROR ---> file "<<outputRootFile.Data()<<" is zombi"<<std::endl;
      assert(0);
    }
    for(unsigned int i = 0; i < info_s.filename.size(); i++){
    //for(unsigned int i = 0; i < 1; i++){
      TString in_file_name_full = input_dir; in_file_name_full += "/";
      in_file_name_full += info_s.filename.at(i);
      TGraphErrors*gr = new TGraphErrors();
      gr->SetNameTitle(info_s.gr_name_title.at(i).Data(),info_s.gr_name_title.at(i).Data());
      //
      if(info_s.KID.at(i) == "K6487")
	read_K6487(in_file_name_full, gr);
      else if(info_s.KID.at(i) == "K2400")
	read_K2400(in_file_name_full, gr);
      else
	assert(0);
      //
      gr->Write();
      gr->Delete();
    }
    rootFile->Close();
    std::cout<<"  Output TGrpah file ---> "<<outputRootFile.Data()<<std::endl;
  }
  else{
    std::cout<<"  runID [1] = 0                "<<std::endl
	     <<"        [2] - input dir        "<<std::endl
	     <<"        [3] - info file        "<<std::endl
	     <<"        [4] - output root file "<<std::endl;
  }  //
  finish = clock();
  std::cout<<"-------------------------"<<std::endl
  	   <<"Working time : "<<((finish - start)/CLOCKS_PER_SEC)<<" (sec)"<<std::endl
  	   <<"-------------------------"<<std::endl;
  //
  return 0;
}

//Voltage(V)      Current(A)      DiodeCurrent(A) DiodeCurrent Std(A)
//0.0000E+0       131.5434E-15    0.0000E+0       0.0000E+0
//2.0000E+0       79.2482E-12     0.0000E+0       0.0000E+0
//4.0000E+0       99.6221E-12     0.0000E+0       0.0000E+0
//6.0000E+0       114.6803E-12    0.0000E+0       0.0000E+0
void read_K6487(TString fileName, TGraphErrors *gr){
  std::cout<<" Reading --> "<<fileName<<std::endl;
  std::ifstream myfile(fileName.Data());
  std::string mot;
  Double_t Voltage;
  Double_t Current;
  Double_t Voltage_err;
  Double_t Current_err;
  Double_t DiodeCurrent;
  Double_t DiodeCurrent_Std;
  if(myfile.is_open()){
    for(Int_t i = 0;i<5;i++)
      myfile>>mot;
    while(myfile>>Voltage>>Current>>DiodeCurrent>>DiodeCurrent_Std){
      Int_t n = gr->GetN();
      gr->SetPoint(n,Voltage, Current);
      //std::cout<<Voltage<<Voltage<<std::endl
      //       <<Current<<Current<<std::endl;
      Voltage_err = Voltage/100.0 + 0.001;
      Current_err = Current/10.0 + 1.0e-13;
      gr->SetPointError(n,Voltage_err,Current_err);
    }
    myfile.close();
  }
}

//0.0000E+0       4.0767E-8
//5.0000E-1       -2.6559E-9
//1.0000E+0       -1.0743E-9
//1.5000E+0       -6.2948E-10
//2.0000E+0       -3.2374E-10
void read_K2400(TString fileName, TGraphErrors *gr){
  std::cout<<" Reading --> "<<fileName<<std::endl;
  std::ifstream myfile(fileName.Data());
  Double_t Voltage;
  Double_t Current;
  Double_t Voltage_err;
  Double_t Current_err;
  if(myfile.is_open()){
    while(myfile>>Voltage>>Current){
      Int_t n = gr->GetN();
      gr->SetPoint(n,Voltage, Current);
      //std::cout<<Voltage<<Voltage<<std::endl
      //       <<Current<<Current<<std::endl;
      Voltage_err = Voltage/100.0 + 0.001;
      Current_err = Current/10.0 + 1.0e-13;
      gr->SetPointError(n,Voltage_err,Current_err);
    }
    myfile.close();
  }
}

/*
void readDatTrkFile(TString fileName, Double_t &theta, Double_t &phi, 
                    Double_t &x_int, Double_t &y_int, Double_t &z_int, 
                    Double_t &xe0, Double_t &ye0, Double_t &ze0, 
                    Double_t &distToEarth, Double_t &distToTerzina, Double_t &angleTrzinaTrk, Double_t &nphotons_per_m2){
  x_int = -999.0;
  y_int = -999.0;
  z_int = -999.0;
  xe0 = -999.0;
  ye0 = -999.0;
  ze0 = -999.0;
  distToEarth = -999.0;
  distToTerzina = -999.0;
  angleTrzinaTrk = -999.0;
  nphotons_per_m2 = -999.0;
  //
  std::ifstream myfile(fileName.Data());
  std::string mot;
  if(myfile.is_open()){
    for(Int_t i = 0;i<12;i++)
      myfile>>mot;
    myfile>>theta>>phi>>x_int>>y_int>>z_int>>xe0>>ye0>>ze0>>distToEarth>>distToTerzina>>angleTrzinaTrk>>nphotons_per_m2;
    myfile.close();
  }
}
*/
