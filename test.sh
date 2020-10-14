
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
echo "And above all," > file

#### -- test HASH -- ####
test_hash()
{
	HASH=$1
	if [ $HASH == "md5" ]
	then
		openssl=""
	else
		openssl="openssl"
	fi
	echo "$BRIGHT $HASH $RESET"
	#### -- UNIT tests -- ####
	unit_test()
	{
		FILEPATH=$1
		./ft_ssl $HASH $FILEPATH > test/test_unit.txt 2> test/test_unit_err.txt
		$openssl $HASH $FILEPATH > test/test_unit2.txt 2> test/test_unit2_err.txt
		dif=$(eval "diff test/test_unit.txt test/test_unit2.txt;
					diff test/test_unit_err.txt test/test_unit2_err.txt")
		if [ "$dif" = "" ]
		then
			((correct+=1))
			# echo "$GREEN OK: $FILEPATH $RESET" ## Flag -v --verbose??!!!
		else
			echo "$RED ERROR:$FILEPATH $RESET                                $dif"
		fi
		((count+=1))

		if [ "$correct" == "$count" ]
		then
			echo "$GREEN Unit tests: \t\t$correct / $count OK   $RESET $CLEAR_LINE"
		elif [ "$correct" == "0" ]
		then
			echo "$RED Unit tests: \t\t$correct / $count ERROR $RESET $CLEAR_LINE"
		else
			echo "$YELLOW Unit tests: \t\t$correct / $count      $RESET $CLEAR_LINE"
		fi
		rm test/test_unit.txt test/test_unit2.txt test/test_unit_err.txt test/test_unit2_err.txt
	}

	unit_test file
	unit_test test/empty.txt
	unit_test test/hello.txt
	unit_test test/gnl_test.txt
	unit_test test/correction.txt

	unit_test test/random_str.txt
	unit_test test/random_str1.txt
	unit_test test/random_str2.txt
	unit_test test/random_str3.txt
	unit_test test/random_str4.txt
	unit_test test/random_str5.txt
	unit_test test/random_str6.txt
	unit_test test/random_str7.txt
	unit_test test/random_str8.txt
	unit_test test/random_str9.txt

	unit_test test/random_binary0.txt
	unit_test test/random_binary1.txt
	unit_test test/random_binary2.txt
	unit_test test/random_binary3.txt
	unit_test test/random_binary2_err.txt
	unit_test test/random_binary3_err.txt

	unit_test test/lorem_ipsum.txt
	unit_test test/some_hipster_ipsum
	unit_test test/some_hipster_ipsum_sum

	unit_test test/contradiction_long.txt
	unit_test test/the_best_player_around_the_whole_universe.cor
	unit_test test/the_best_player_around_the_whole_universe.s
	unit_test test/big_smoke_order_remix
	unit_test test/max_line.txt

	## ERROR, MULTIPLE & FLAG tests
	unit_test test/does_not_exist.txt
	unit_test test/
	unit_test "test/does_not_exist.txt test/gnl_test.txt"

	unit_test "-q test/empty.txt"
	unit_test "-q test/gnl_test.txt"
	unit_test "-r test/empty.txt"
	unit_test "-r test/gnl_test.txt"
	unit_test "-s test/empty.txt"
	unit_test "-s test/gnl_test.txt"

	unit_test "-q test/empty.txt test/gnl_test.txt"
	unit_test "-q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt test/gnl_test.txt"
	unit_test "-r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt test/gnl_test.txt"
	unit_test "-s test/gnl_test.txt test/gnl_test.txt"

	unit_test "test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"

	unit_test "-q test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "test/empty.txt -q test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "test/empty.txt test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -q test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -q test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -q test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -q test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -r test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -r test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -r test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -r test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -s test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -s test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -s test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q test/empty.txt -s test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"

	unit_test "-r test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "test/empty.txt -r test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "test/empty.txt test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -q test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -q test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -q test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -q test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -r test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -r test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -r test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -r test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -s test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -s test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -s test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r test/empty.txt -s test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"

	unit_test "-s test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "test/empty.txt -s test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "test/empty.txt test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -q test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -q test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -q test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -q test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -r test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -r test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -r test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -r test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -s test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -s test/gnl_test.txt -q test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -s test/gnl_test.txt -r test/gnl_test.txt test/gnl_test.txt"
	unit_test "-s test/empty.txt -s test/gnl_test.txt -s test/gnl_test.txt test/gnl_test.txt"

	unit_test "-q -r -s test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q -q -s test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r -r -s test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-q -s -s test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"
	unit_test "-r -s -s test/empty.txt test/gnl_test.txt test/gnl_test.txt test/gnl_test.txt"

	unit_test "test/random_binary1.txt test/random_binary2.txt unit_test test/random_binary3.txt"

	unit_test "-s \"pity those that aren\'t following baerista on spotify.\""
	unit_test "-q test/big_smoke_order_remix"
	unit_test "-s \"wubba lubba dub dub\""
	unit_test "-s \"!@#$%^&*()~{}|<>,.\""
	unit_test "-s \"I mean.....\""
	unit_test "-s \"Does Donny?\""

	#### -- More UNIT tests -- ####
	unit_test2()
	{
		PREFIX=$1
		SUFFIX=$2
		echo $PREFIX | ./ft_ssl $HASH $SUFFIX > test/test_unit.txt 2> test/test_unit_err.txt
		echo $PREFIX | $openssl $HASH $SUFFIX > test/test_unit2.txt 2> test/test_unit2_err.txt
		dif=$(eval "diff test/test_unit.txt test/test_unit2.txt;
				diff test/test_unit_err.txt test/test_unit2_err.txt")
		if [ "$dif" = "" ]
		then
			((correct+=1))
			# echo "$GREEN OK: $PREFIX | $HASH $SUFFIX $RESET"
		else
			echo "$RED $PREFIX | $HASH $SUFFIX $RESET                           $dif"
		fi
		((count+=1))
		if [ "$correct" == "$count" ]
		then
			echo "$GREEN Unit tests: \t\t$correct / $count OK   $RESET $CLEAR_LINE"
		elif [ "$correct" == "0" ]
		then
			echo "$RED Unit tests: \t\t$correct / $count ERROR $RESET $CLEAR_LINE"
		else
			echo "$YELLOW Unit tests: \t\t$correct / $count      $RESET $CLEAR_LINE"
		fi
		rm test/test_unit.txt test/test_unit2.txt test/test_unit_err.txt test/test_unit2_err.txt
	}

	unit_test2 "pickle rick"
	unit_test2 "Do not pity the dead, Harry." "-p"
	unit_test2 "Pity the living." "-q -r"
	unit_test2 "be sure to handle edge cases carefully" "-p file"
	unit_test2 "some of this will not make sense at first" "file"
	unit_test2 "but eventually you will understand" "-p -r file"
	unit_test2 "GL HF let's go" "-p -s \"foo\" file"
	unit_test2 "one more thing" "-r -p -s \"foo\" file -s \"bar\""
	unit_test2 "just to be extra clear" "-r -q -p -s \"foo\" file"
	unit_test2 "I mean..." "-q -r -s \"...you know?\""
	unit_test2 "Wait..." "-q -r -s \"...what?\" file -s -p -s -q"
	unit_test2 "Salutations!" "-p -p -s -s \"Donny does\" file -s -p -s -r"
	unit_test2 "Magic mirror on the wall, think I wanna smash them all?" "-p"
	unit_test2 "Speed up now, Gas Pedal??" "-p"

	echo
	#### -- RANDOM STRINGS -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		openssl rand -base64 $random_len > test/test_random.txt
		cmd="./ft_ssl $HASH test/test_random.txt"
		control="$openssl $HASH test/test_random.txt"
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
		rm test/test_random.txt
	done
	echo

	#### -- RANDOM -S STRINGS -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		random_str=$(eval "openssl rand -base64 $random_len")
		cmd="./ft_ssl $HASH -s \"$random_str\""
		control="$openssl $HASH -s \"$random_str\""
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
	#### -- RANDOM echo -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		random_str=$(eval "openssl rand -base64 $random_len")
		cmd="echo \"$random_str\" | ./ft_ssl md5"
		control="echo \"$random_str\" | openssl md5"
		output=$(eval "$cmd")
		output2=$(eval "$control")
		if [ "$output" = "$output2" ]
		then
			((correct+=1))
			((random_correct+=1))
		else
			echo "$RED ERROR: echo \"random string\" | ./ft_ssl $RESET                            "
			echo "$random_str"
			echo "./ft_ssl: $output"
			echo "openssl:  $output2"
		fi
		((count+=1))
		((random_count+=1))
		if [ "$random_correct" == "$random_count" ]
		then
			echo "$GREEN echo \"str\" | ./ft_ssl: $random_correct / $random_count OK   $RESET $CLEAR_LINE"
		elif [ "$random_correct" == "0" ]
		then
			echo "$RED echo \"str\" | ./ft_ssl: $random_correct / $random_count ERROR $RESET $CLEAR_LINE"
		else
			echo "$YELLOW echo \"str\" | ./ft_ssl: $random_correct / $random_count      $RESET $CLEAR_LINE"
		fi
		# rm test/test_random.txt
	done

	echo
	#### -- RANDOM BINARY -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		cat /dev/urandom | head -c $random_len > test/test_random.txt
		cmd="./ft_ssl $HASH test/test_random.txt"
		control="$openssl $HASH test/test_random.txt"
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
		rm test/test_random.txt
	done

	# #### -- MD5 STATS -- ####
	# echo
	# if [ "$correct" == "$count" ]
	# then
	# 	echo "\n\t     md5 total:$GREEN $correct / $count OK $RESET\n"
	# elif [ "$correct" == "0" ]
	# then
	# 	echo "\n\t     md5 total:$RED $correct / $count $RESET\n"	
	# else
	# 	echo "\n\t     md5 total:$YELLOW $correct / $count $RESET\n"
	# fi
}

#### -- EXEC TEST HASH -- ####
test_hash "md5"
# test_hash "sha256"


test_sha()
{
	SHA=$1
	echo "\n\n$BRIGHT sha$SHA $RESET"
	#### -- SHA UNIT test -- ####
	unit_correct=0
	unit_count=0
	unit_test_sha()
	{
		FILEPATH=$1
		./ft_ssl sha$SHA -q $FILEPATH > test/test_unit.txt 2> test/test_unit_err.txt
		shasum -a $SHA $FILEPATH | awk '{print $1;}' > test/test_unit2.txt 2> test/test_unit2_err.txt
		dif=$(eval "diff test/test_unit.txt test/test_unit2.txt;
					diff test/test_unit_err.txt test/test_unit2_err.txt")
		if [ "$dif" = "" ]
		then
			((correct+=1))
			((unit_correct+=1))
			# echo "$GREEN OK: $FILEPATH $RESET" ## Flag -v --verbose??!!!
		else
			echo "$RED ERROR:$FILEPATH $RESET                                \n$dif"
		fi
		((count+=1))
		((unit_count+=1))
		if [ "$unit_correct" == "$unit_count" ]
		then
			echo "$GREEN Unit tests: \t\t$unit_correct / $unit_count OK   $RESET $CLEAR_LINE"
		elif [ "$unit_correct" == "0" ]
		then
			echo "$RED Unit tests: \t\t$unit_correct / $unit_count ERROR $RESET $CLEAR_LINE"
		else
			echo "$YELLOW Unit tests: \t\t$unit_correct / $unit_count      $RESET $CLEAR_LINE"
		fi
		rm test/test_unit.txt test/test_unit2.txt test/test_unit_err.txt test/test_unit2_err.txt
	}

	unit_test_sha file
	unit_test_sha test/empty.txt
	unit_test_sha test/hello.txt
	unit_test_sha test/gnl_test.txt
	unit_test_sha test/correction.txt

	unit_test_sha test/random_str.txt
	unit_test_sha test/random_str1.txt
	unit_test_sha test/random_str2.txt
	unit_test_sha test/random_str3.txt
	unit_test_sha test/random_str4.txt
	unit_test_sha test/random_str5.txt
	unit_test_sha test/random_str6.txt
	unit_test_sha test/random_str7.txt
	unit_test_sha test/random_str8.txt
	unit_test_sha test/random_str9.txt

	unit_test_sha test/random_binary0.txt
	unit_test_sha test/random_binary1.txt
	unit_test_sha test/random_binary2.txt
	unit_test_sha test/random_binary3.txt
	unit_test_sha test/random_binary2_err.txt
	unit_test_sha test/random_binary3_err.txt

	unit_test_sha test/lorem_ipsum.txt
	unit_test_sha test/some_hipster_ipsum
	unit_test_sha test/some_hipster_ipsum_sum

	unit_test_sha test/contradiction_long.txt
	unit_test_sha test/the_best_player_around_the_whole_universe.cor
	unit_test_sha test/the_best_player_around_the_whole_universe.s
	unit_test_sha test/big_smoke_order_remix
	unit_test_sha test/max_line.txt

	echo
	#### -- RANDOM STRINGS -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		openssl rand -base64 $random_len > test/test_random.txt
		cmd="./ft_ssl sha$SHA -q test/test_random.txt"
		control="shasum -a $SHA test/test_random.txt | awk '{print \$1;}'"
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
		rm test/test_random.txt
	done

	echo
	#### -- RANDOM echo -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		random_str=$(eval "openssl rand -base64 $random_len")
		cmd="echo \"$random_str\" | ./ft_ssl sha$SHA"
		control="echo \"$random_str\" | shasum -a $SHA  | awk '{print \$1;}'"
		output=$(eval "$cmd")
		output2=$(eval "$control")
		if [ "$output" = "$output2" ]
		then
			((correct+=1))
			((random_correct+=1))
		else
			echo "$RED ERROR: echo \"random string\" | ./ft_ssl $RESET                            "
			echo "$random_str"
			echo "./ft_ssl: $output"
			echo "openssl:  $output2"
		fi
		((count+=1))
		((random_count+=1))
		if [ "$random_correct" == "$random_count" ]
		then
			echo "$GREEN echo \"str\" | ./ft_ssl: $random_correct / $random_count OK   $RESET $CLEAR_LINE"
		elif [ "$random_correct" == "0" ]
		then
			echo "$RED echo \"str\" | ./ft_ssl: $random_correct / $random_count ERROR $RESET $CLEAR_LINE"
		else
			echo "$YELLOW echo \"str\" | ./ft_ssl: $random_correct / $random_count      $RESET $CLEAR_LINE"
		fi
	done

	echo
	#### -- RANDOM BINARY -- ####
	random_correct=0
	random_count=0
	while [ $random_count -lt 100 ]
	do
		random_len=$(( ( RANDOM % 1000 )  + 1 ))
		cat /dev/urandom | head -c $random_len > test/test_random.txt
		cmd="./ft_ssl sha$SHA -q test/test_random.txt"
		control="shasum -a $SHA test/test_random.txt | awk '{print \$1;}'"
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
		rm test/test_random.txt
	done


	# #### -- SHA256 STATS -- ####
	# echo
	# if [ "$correct" == "$count" ]
	# then
	# 	echo "\n\t  $SHA total:$GREEN $correct / $count OK $RESET\n"
	# elif [ "$correct" == "0" ]
	# then
	# 	echo "\n\t  $SHA total:$RED $correct / $count $RESET\n"	
	# else
	# 	echo "\n\t  $SHA total:$YELLOW $correct / $count $RESET\n"
	# fi
}

test_sha 256
test_sha 224
test_sha 384
test_sha 512
test_sha 512224
test_sha 512256

#### -- FINAL STATS -- ####
echo
echo
if [ "$correct" == "$count" ]
then
	echo " Passed $GREEN $correct / $count $RESET total tests\n"
elif [ "$correct" == "0" ]
then
	echo " Passed $RED $correct / $count $RESET total tests\n"	
else
	echo " Passed $YELLOW $correct / $count $RESET total tests\n"
fi

#### -- END -- ####
rm file ft_ssl ## make fclean