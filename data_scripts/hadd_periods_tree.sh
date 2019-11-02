for D in `find . -maxdepth 1 -mindepth 1 -type d`
do
	if [ ${D} != ".alrb" ] && [ ${D} != ".rucio_jcorrado" ]
	then

		newname=$(echo $(basename $D) | tr '.' '_' | sed 's/\(.*\)_\([^_]*\)$/\1.\2/g')
		printf $newname
		outfile="$newname.root"
		infiles="$D/*.root"
		hadd -O -j $outfile $infiles 
		printf $outfile 
	fi
done	
