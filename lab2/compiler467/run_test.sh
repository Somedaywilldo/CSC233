# build
make

# Tests
echo ----------------------BEGIN----------------------
echo Run pass_1
./compiler467 -Tp ./tests/pass_1.txt
echo -----------------------END-----------------------

echo ----------------------BEGIN----------------------
echo Run fail_1
./compiler467 -Tp ./tests/fail_1.txt
echo -----------------------END-----------------------

echo ----------------------BEGIN----------------------
echo Run fail_2
./compiler467 -Tp ./tests/fail_2.txt
echo -----------------------END-----------------------

echo ----------------------BEGIN----------------------
echo Run fail_3
./compiler467 -Tp ./tests/fail_3.txt
echo -----------------------END-----------------------

echo ----------------------BEGIN----------------------
echo Run fail_4
./compiler467 -Tp ./tests/fail_4.txt
echo -----------------------END-----------------------

echo ----------------------BEGIN----------------------
echo Run fail_5
./compiler467 -Tp ./tests/fail_5.txt
echo -----------------------END-----------------------

echo ----------------------BEGIN----------------------
echo Run fail_6
./compiler467 -Tp ./tests/fail_6.txt
echo -----------------------END-----------------------


echo done
