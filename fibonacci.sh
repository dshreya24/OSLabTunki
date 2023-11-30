read -p "Enter the number: " number
x=0
y=1
i=2
echo "Fibonacci Series of 1st $number numbers: "
echo "$x"
echo "$y"
while [ $i -lt $number ]
do
i=`expr $i + 1`
z=`expr $x + $y`
echo "$z"
x=$y
y=$z
done
