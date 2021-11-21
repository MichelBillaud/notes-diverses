#!/bin/bash -x

function fabriquer() {
	(
		cd ../progs
		(cd $1 ; make mrproper)
		zip -r ../ZIPS/$1 $1
	)
}

fabriquer DemoFactory

