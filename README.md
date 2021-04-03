# md5

Recode MD5 and SHA Hashing Algorithms:
1. md5
2. sha256
3. sha224
4. sha384
5. sha512
6. sha512/224
7. sha512/256

See the [subject](https://github.com/dfinnis/md5/blob/master/subject.pdf) for more details.

*Final Score 125/100*


## Getting Started

First clone this repo. <br>
```git clone https://github.com/dfinnis/md5.git; cd md5```

Make the binary *ft_ssl*. <br>
```make```

Then run *ft_ssl* with hashing algorithm then filepath as argument. <br>
```./ft_ssl md5 test/hello.txt```

<img src="https://github.com/dfinnis/md5/blob/master/img/ssl.png" width="56%">


### md5 example

We can compare our output hash with the MD5 standalone, and openssl.

```md5 test/hello.txt```

<img src="https://github.com/dfinnis/md5/blob/master/img/md5.png" width="56%">


### sha example

Here is an example running *ft_ssl* with SHA256. The same works for all SHA family hashes.

```./ft_ssl sha256 test/hello.txt```

<img src="https://github.com/dfinnis/md5/blob/master/img/sha.png" width="90%">


### stdin example

Like *openssl*, you can run *ft_ssl* without arguments. It will then prompt for input from stdin, accepting a hashing algorithm.
Next input whatever text then press ctrl+D. It will then output the hash for the given text.
Here is an example shown against *openssl*.

```./ft_ssl```

<img src="https://github.com/dfinnis/md5/blob/master/img/stdin.png" width="33%">


## Test script

*test.sh* compares the output of *ft_ssl* with the output of *openssl / shasum*.

It will run some unit tests (files in the test folder), random strings, random strings piped into stdin, and random binary files.
It will run these tests for each hashing algorithm emulated, MD5 and SHA family hashes.

```./test.sh```

<img src="https://github.com/dfinnis/md5/blob/master/img/test.png" width="35%">


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
* A small change in message should change the hash extensively
* No two different messages with the same hash value


## How hashing functions work

Though the numbers change, the basic principle is the same for MD5 and SHA family hashes. For MD5:

1. Pad the message until length is a multiple of 512 bits
2. Initialize 4 buffers
3. Process the message 512 bit chunk at a time, adding the result to the hash buffers. For each 512 bit chunk, do 64 rounds of compression (specific bitwise buffer operations)


## Dependencies

None! All dependencies are already contained in the repo.


## References

[Wikipedia MD5 pseudocode](https://en.wikipedia.org/wiki/MD5#Pseudocode)

[Wikipedia SHA-2 pseudocode](https://en.wikipedia.org/wiki/SHA-2#Pseudocode)

[EDUCBA - Introduction to MD5 Algorithm](https://www.educba.com/md5-alogrithm/)

[National Institute of Standards and Technology - Secure Hash Standard](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)

[Information Warfare - description of SHA family hash functions](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf)
