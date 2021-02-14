# md5

Recode MD5 and SHA Hashing Algorithms:
1. md5
2. sha256
3. sha224
4. sha384
5. sha512
6. sha512/224
7. sha512/256

## Getting Started

Clone this repo to your machine. Then make, creating the binary ```ft_ssl```.
```
➜  git clone https://github.com/dfinnis/md5.git
...
➜  cd md5
➜  md5 git:(master) make
...
```

### Examples

Run ```./ft_ssl```, followed by hashing algorithm, then any filepath. You can see the output hash is the same as the MD5 standalone, and openssl.
```
➜  md5 git:(master) ./ft_ssl md5 test/hello.txt
MD5 (test/hello.txt) = b1946ac92492d2347c6235b4d2611184
➜  md5 git:(master) md5 test/hello.txt
MD5 (test/hello.txt) = b1946ac92492d2347c6235b4d2611184
➜  md5 git:(master) openssl md5 test/hello.txt
MD5(test/hello.txt)= b1946ac92492d2347c6235b4d2611184
```

Here is an example for SHA256. The same works for all SHA family hashes.
```
➜  md5 git:(master) ./ft_ssl sha256 test/hello.txt
SHA256 (test/hello.txt) = 5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03
➜  md5 git:(master) openssl sha256 test/hello.txt
SHA256(test/hello.txt)= 5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03
➜  md5 git:(master) shasum -a 256 test/hello.txt
5891b5b522d5df086d0ff0b110fbd9d21bb4fc7163af34d08286a2e846f6be03  test/hello.txt
```

Like ```openssl```, you can run ```ft_ssl``` without arguments. It will then prompt for input from stdin, accepting a hashing algorithm.
Next input whatever text followed by control-D. It will then output the hash for the given text.
Here is an example shown against ```openssl```.
```
➜  md5 git:(master) ./ft_ssl
FT_SSL> md5
hash this
d2e196667eeb24381125d3d4230d8bfb
➜  md5 git:(master) openssl
OpenSSL> md5
hash this
d2e196667eeb24381125d3d4230d8bfb
```

### Prerequisites

None! All dependencies are already contained in the repo.

## Tests

Run the test script ```./test.sh``` .
It will compare the output of ```ft_ssl``` with the output of ```openssl```/```shasum```.

It will run some unit tests (files in the test folder), random strings, random strings piped into stdin, and random binary files.
It will run these tests for each hashing algorithm emulated, MD5 and SHA family hashes.

![md5 test output](https://github.com/dfinnis/md5/blob/master/test/md5_test_output.png?raw=true)

## Flags

```ft_ssl``` supports the following flags, emulating the behaviour of the MD5 standalone.

* ```-p``` echo STDIN to STDOUT and append the checksum to STDOUT
* ```-q``` quiet mode
* ```-r``` reverse the format of the output
* ```-s``` print the sum of the given string

## Ideal hashing

The ideal cryptographic hash function has 5 main properties:

* Deterministic, the same message always results in the same hash
* Quick to compute
* Infeasible to reverse engineer a message from its hash (one-way)
* a small change in message should change the hash extensively
* no two different messages with the same hash value

## How hashing functions work

Though the numbers change, the basic principle is the same for MD5 and SHA family hashes. For MD5:

1. Pad the message until length is a multiple of 512 bytes
2. Initialize 4 buffers
3. Process the message 512 byte chunk at a time, adding the result to the hash.
4. For each 512 byte chunk, do 64 rounds of compression (specific bitwise buffer operations)

## References

[Wikipedia MD5 pseudocode](https://en.wikipedia.org/wiki/MD5#Pseudocode)

[Wikipedia SHA-2 pseudocode](https://en.wikipedia.org/wiki/SHA-2#Pseudocode)

[EDUCBA - Introduction to MD5 Algorithm](https://www.educba.com/md5-alogrithm/)

[National Institute of Standards and Technology - Secure Hash Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)

[Information Warfare - description of SHA family hash functions](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf)
