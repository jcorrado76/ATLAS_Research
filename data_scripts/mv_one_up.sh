for directory in ./*
do
	if [ -d "$directory" ]
	then
		echo "$directory"
		mv "$directory"/* ./
		rm -r "$directory"
	fi
done
