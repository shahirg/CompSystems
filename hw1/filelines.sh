#script to count total file lines in current directory

total_lines=0;

for FILE in "$@"
do
	x=$(wc -l < $FILE);
	echo "$FILE $x lines";
	total_lines=`expr $total_lines + $x`;
	echo "Current Total = $total_lines\n";       	
done
echo "Total lines = $total_lines";
