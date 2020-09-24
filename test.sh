
RESET="\x1b[0m"
BRIGHT="\x1b[1m"
RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
CLEAR_SCREEN="\E[H\E[2J"
CLEAR_LINE="\r\c"

# make fclean
make
printf $CLEAR_SCREEN
echo "$BRIGHT Launching MD5 Performance Test... $RESET\n"

count=0
correct=0

#### -- UNIT TESTS -- ####
unit_test()
{
	FILEPATH=$1
	cmd="./ft_ssl md5 $FILEPATH"
	control="md5 $FILEPATH"
	output=$(eval "$cmd")
	output2=$(eval "$control")
	if [ "$output" = "$output2" ]
	then
		echo "$GREEN OK: $FILEPATH $RESET" ##
		((correct+=1))
	else
		echo "$RED ERROR: $FILEPATH $RESET"
		echo $output2
		echo $output
	fi
	((count+=1))
}

unit_test tests/empty.txt
unit_test tests/gnl_test.txt
unit_test tests/correction.txt
unit_test tests/does_not_exist.txt
unit_test tests/
unit_test "tests/does_not_exist.txt tests/gnl_test.txt"

unit_test "-q tests/empty.txt"
unit_test "-q tests/gnl_test.txt"
unit_test "-r tests/empty.txt"
unit_test "-r tests/gnl_test.txt"
unit_test "-s tests/empty.txt"
unit_test "-s tests/gnl_test.txt"

unit_test "-q tests/empty.txt tests/gnl_test.txt"
unit_test "-q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt tests/gnl_test.txt"
unit_test "-r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt tests/gnl_test.txt"
unit_test "-s tests/gnl_test.txt tests/gnl_test.txt"

unit_test "tests/empty.txt tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"

unit_test "-q tests/empty.txt tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "tests/empty.txt -q tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "tests/empty.txt tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -q tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -q tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -q tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -q tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -r tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -r tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -r tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -r tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -s tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -s tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -s tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-q tests/empty.txt -s tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"

unit_test "-r tests/empty.txt tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "tests/empty.txt -r tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "tests/empty.txt tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -q tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -q tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -q tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -q tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -r tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -r tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -r tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -r tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -s tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -s tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -s tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-r tests/empty.txt -s tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"

unit_test "-s tests/empty.txt tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "tests/empty.txt -s tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "tests/empty.txt tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -q tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -q tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -q tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -q tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -r tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -r tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -r tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -r tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -s tests/gnl_test.txt tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -s tests/gnl_test.txt -q tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -s tests/gnl_test.txt -r tests/gnl_test.txt tests/gnl_test.txt"
unit_test "-s tests/empty.txt -s tests/gnl_test.txt -s tests/gnl_test.txt tests/gnl_test.txt"

#### -- UNIT STATS -- ####
if [ "$correct" == "$count" ]
then
	echo "$GREEN Unit tests: \t\t$correct / $count OK   $RESET"
elif [ "$correct" == "0" ]
then
	echo "$RED Unit tests: \t\t$correct / $count ERROR $RESET"
else
	echo "$YELLOW Unit tests: \t\t$correct / $count      $RESET"
fi

#### -- RANDOM STRINGS -- ####
random_correct=0
random_count=0
while [ $random_count -lt 100 ]
do
	random_len=$(( ( RANDOM % 1000 )  + 1 ))
	openssl rand -base64 $random_len > tests/test_random.txt
	cmd="./ft_ssl md5 tests/test_random.txt"
	control="md5 tests/test_random.txt"
	output=$(eval "$cmd")
	output2=$(eval "$control")
	if [ "$output" = "$output2" ]
	then
		((correct+=1))
		((random_correct+=1))
	fi
	((count+=1))
	((random_count+=1))
	if [ "$random_correct" == "$random_count" ]
	then
		echo "$GREEN Random string > file: \t$random_correct / $random_count OK   $RESET $CLEAR_LINE"
	elif [ "$random_correct" == "0" ]
	then
		echo "$RED Random string > file: \t$random_correct / $random_count ERROR $RESET $CLEAR_LINE"
	else
		echo "$YELLOW Random string > file: \t$random_correct / $random_count      $RESET $CLEAR_LINE"
	fi
	rm tests/test_random.txt
done
echo

#### -- RANDOM -S STRINGS -- ####
random_correct=0
random_count=0
while [ $random_count -lt 100 ]
do
	random_len=$(( ( RANDOM % 1000 )  + 1 ))
	random_str=$(eval "openssl rand -base64 $random_len")
	cmd="./ft_ssl md5 -s \"$random_str\""
	control="md5 -s \"$random_str\""
	output=$(eval "$cmd")
	output2=$(eval "$control")
	if [ "$output" = "$output2" ]
	then
		((correct+=1))
		((random_correct+=1))
	fi
	((count+=1))
	((random_count+=1))
	if [ "$random_correct" == "$random_count" ]
	then
		echo "$GREEN Random -s \"string\": \t$random_correct / $random_count OK   $RESET $CLEAR_LINE"
	elif [ "$random_correct" == "0" ]
	then
		echo "$RED Random -s \"string\": \t$random_correct / $random_count ERROR $RESET $CLEAR_LINE"
	else
		echo "$YELLOW Random -s \"string\": \t$random_correct / $random_count      $RESET $CLEAR_LINE"
	fi
done
echo

#### -- RANDOM BINARY -- ####
random_correct=0
random_count=0
while [ $random_count -lt 100 ]
do
	random_len=$(( ( RANDOM % 1000 )  + 1 ))
	cat /dev/urandom | head -c $random_len > tests/test_random.txt
	cmd="./ft_ssl md5 tests/test_random.txt"
	control="md5 tests/test_random.txt"
	output=$(eval "$cmd")
	output2=$(eval "$control")
	if [ "$output" = "$output2" ]
	then
		((correct+=1))
		((random_correct+=1))
	fi
	((count+=1))
	((random_count+=1))
	if [ "$random_correct" == "$random_count" ]
	then
		echo "$GREEN Random binary > file: \t$random_correct / $random_count OK   $RESET $CLEAR_LINE"
	elif [ "$random_correct" == "0" ]
	then
		echo "$RED Random binary > file: \t$random_correct / $random_count ERROR $RESET $CLEAR_LINE"
	else
		echo "$YELLOW Random binary > file: \t$random_correct / $random_count      $RESET $CLEAR_LINE"
	fi
	rm tests/test_random.txt
done

#### -- FINAL STATS -- ####
echo
if [ "$correct" == "$count" ]
then
	echo "\nPassed $GREEN $correct / $count $RESET total tests\n"
elif [ "$correct" == "0" ]
then
	echo "\nPassed $RED $correct / $count $RESET total tests\n"	
else
	echo "\nPassed $YELLOW $correct / $count $RESET total tests\n"
fi

#### -- END -- ####
rm ft_ssl ## make fclean