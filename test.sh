
RESET="\x1b[0m"
BRIGHT="\x1b[1m"
RED="\x1b[31m"
GREEN="\x1b[32m"
CLEAR="\E[H\E[2J"

# make fclean
make
printf $CLEAR
echo "$BRIGHT Launching MD5 Performance Test... $RESET\n"

count=0
correct=0

cmd="./ft_ssl md5 tests/empty.txt"
control="md5 tests/empty.txt"
output=$(eval "$cmd")
output2=$(eval "$control")
if [ "$output" = "$output2" ]
then
	echo "$GREEN empty:\t\t\tOK $RESET"
else
	echo "$RED empty:\t\t\tERROR $RESET"
	echo $output
	echo $output2
fi

cmd="./ft_ssl md5 tests/gnl_test.txt"
control="md5 tests/gnl_test.txt"
output=$(eval "$cmd")
output2=$(eval "$control")
if [ "$output" = "$output2" ]
then
	echo "$GREEN gnl_test:\t\tOK $RESET"
else
	echo "$RED gnl_test:\t\tERROR $RESET"
	echo $output
	echo $output2
fi