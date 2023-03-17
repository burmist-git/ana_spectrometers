#!/bin/bash

# Me 08 Jun 2022 14:02:24 CEST
# Autor: Leonid Burmistrov

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d    : default"
    echo " [0] -info : create info files"
    echo " [0] -h    : print help"
}

function test_f {
    echo "$1"
}

function gen_info {
    #filename doseapprox type PCBID sampleID cells w_wo_res chID KID sampleID2 temperature date time irradiationtime dose_in_H2O fluence flux radsession
    #G0_IV_PCB1_S3_30um_wores_K6487.txt      0 IV PCB1 S3 30um wores ch01 K6487 n1 22.0 01.03.2023 15:00 68 1 -999.0 -999.0 0
    #G0_IV_PCB1_S1_40um_wores_ch01_K6487.txt 0 IV PCB1 S1 40um wores ch01 K6487 n1 22.0 01.03.2023 15:00 68 1 -999.0 -999.0 0
    #dir="../data/IrradiationTests/01_0_Gy/"
    dir=$1
    infoFile=$dir/info
    rm -rf $infoFile
    echo "$dir"
    echo "filename doseapprox type PCBID sampleID cells w_wo_res chID KID sampleID2 temperature date time irradiationtime dose_in_H2O fluence flux radsession" | tee -a $infoFile
    for txtfilefull in $dir/*.txt; do
	txtfile="$(basename -- "$txtfilefull")"
	doseapprox="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | sed 's/G//g' | awk '{print $1}')"
	type="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $2}')"
	PCBID="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $3}')"
	sampleID="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $4}')"
	cells="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $5}')"
	w_wo_res="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $6}')"
	chID="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $7}')"
	KID="$(echo $txtfile | sed 's/_/ /g' | sed 's/.txt//g' | awk '{print $8}')"
	sampleID2="n1"
	temperature="22.0"
	date="01.03.2023"
	time="15:00"
	irradiationtime="68"
	dose_in_H2O="1"
	fluence="-999.0"
	flux="-999.0"
	radsession="0"
	echo "$txtfile $doseapprox $type $PCBID $sampleID $cells $w_wo_res $chID $KID $sampleID2 $temperature $date $time $irradiationtime $dose_in_H2O $fluence $flux $radsession" | tee -a $infoFile
    done
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	make clean; make;
	convertIVlog="convertIV.log"
	rm -rf $convertIVlog
	for input_dir in ../data/IrradiationTests/*/; do
	    echo "Converting --> $input_dir"
	    info_file=$input_dir"info"
	    outputRootFile=$input_dir"hist.root";
	    ./convertIV 0 $input_dir $info_file $outputRootFile | tee -a $convertIVlog
	    echo ""
	    echo ""
	    echo ""
	done
    elif [ "$1" = "-info" ]; then
	for input_dir in ../data/IrradiationTests/*_Gy/; do
	    gen_info $input_dir
	done
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi
