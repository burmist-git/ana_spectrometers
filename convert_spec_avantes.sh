#!/bin/bash

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d    : default"
    echo " [0] -30.04.2023         : convert 30.04.2023"
    echo " [0] -info_17.03.2023_02 : gen info file for (17.03.2023_02)"
    echo " [0] -info_30.04.2023    : gen info file for (30.04.2023)"
    echo " [0] -h    : print help"
}

function gen_info {
    dir=$1
    infoFile=$dir/info
    rm -rf $infoFile
    echo "$dir"
    for in_file in $dir/*.TXT; do
        txtfile="$(basename -- "$in_file")"
	gr_name="gr_""$(echo $txtfile | sed 's/\./_/g')"
	echo "$in_file $gr_name" | tee -a $infoFile
    done
}

if [ $# -eq 0 ] 
then    
    printHelp
else
    if [ "$1" = "-d" ]; then
	make clean; make;
	convertlog="convert_spec_avantes.log"
	rm -rf $convertlog
	info_file="../data/17.03.2023_02/info"
	out_root="../data/17.03.2023_02/hist.root"
	./convert_spec_avantes 0 $info_file $out_root | tee -a $convertlog
    elif [ "$1" = "-30.04.2023" ]; then
	make clean; make;
	convertlog="../data/30.04.2023/convert_spec_avantes.log"
	rm -rf $convertlog
	info_file="../data/30.04.2023/info"
	out_root="../data/30.04.2023/hist.root"
	./convert_spec_avantes 0 $info_file $out_root | tee -a $convertlog
    elif [ "$1" = "-info_17.03.2023_02" ]; then
	gen_info "../data/17.03.2023_02/"
    elif [ "$1" = "-info_30.04.2023" ]; then
	gen_info "../data/30.04.2023/"
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi
