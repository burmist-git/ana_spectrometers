#!/bin/bash

function printHelp {
    echo " --> ERROR in input arguments "
    echo " [0] -d    : default"
    echo " [0] -info : gen info file"
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
    elif [ "$1" = "-info" ]; then
	gen_info "../data/17.03.2023_02/"
    elif [ "$1" = "-h" ]; then
        printHelp
    else
        printHelp
    fi
fi
