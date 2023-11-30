echo "Enter the 1st number"
read n1
echo "Enter the 2nd number"
read n2
echo "Menu:"
echo "1)Addition"
echo "2)Subtraction"
echo "3)Multiplication"
echo "4)Division"
echo "Enter the choice"
read ch
case $ch in
1) echo "Addition is: $((n1+n2))";;
2) echo "Subtraction is: $((n1-n2))";;
3) echo "Multiplication is: $((n1*n2))";;
4) echo "Division is: $((n1/n2))";;
*) echo "Enter valid choice";;
esac
