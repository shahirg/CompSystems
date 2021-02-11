#script to count number of total lines within a given number of files
total_lines=0;
for FILE in "$@"
do
	x=$(wc -l <$FILE);
	total_lines=`expr $total_lines + $x`;
	echo "$FILE $x lines\nCurrent Total = $total_lines\n";       	
done
echo "Total lines = $total_lines";
