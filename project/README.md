# S-DES

### slolution

Accept 10-bit binary numbers and make two keys. It is then used to encrypt an 8-bit binary number.

Or decryption  Ciphertext.

***

### test plan

Test 3 sets of data to verify the correctness of the program.

***

### test results

##### T1

10-bit key: 1 0 0 0 1 0 0 0 1 1

key1:  1 0 1 0 0 0 1 0

key2:  0 0 0 1 1 0 1 1

8-bit plaintext: 0 0 1 0 0 1 0 0

Ciphertext: 0 0 0 0 1 0 1 0

***

##### T2

10-bit key: 1 0 1 0 1 0 1 0 1 0

key1:  1 1 1 0 0 1 0 0

key2:  0 1 0 1 0 0 1 1

8-bit plaintext: 1 0 1 0 1 0 1 0

Ciphertext: 0 1 1 0 1 0 1 1

***

##### T3

10-bit key: 0 0 1 0 0 1 0 0 1 1

key1:  0 0 1 0 0 1 1 1

key2:  0 1 1 0 1 0 1 0

8-bit plaintext: 1 0 0 1 0 0 1 0

Ciphertext: 0 1 1 1 1 1 0 0

***

### Input request

About receiving data, my program has made a request. Only accept 0 or 1 int type numbers. If you enter another type, you will be asked to re-enter it. There is also the length of the key, which is also required to be 10-bit, and Ciphertext is required to be only 8-bit.

If you select the function interface, there are no restrictions. If the input is not of int type, the program will crash.

# Diffie-Hellman

### slolution

Accept a prime number within 100 as p, and take a prime number in the range of 1-(p-1) as g. Take xa and xb in the range of 2-(p-1). Then calculate the key based on the characteristics of the modulo operation. This key should be the same for alice and bob.

***

### test plan

Test 3 sets of data to verify the correctness of the program.

***

### test results

##### T1

p=11, g=7, xA=3 and xB=4, k=5

##### T2

p=97, g=5, xA=36 and xB=58, k=75

##### T3

p=5, g=2, xA=3 and xB=2, k=4

***

### Input request

My program is not set to limit the input type, if the input is not int type data, the program will crash. If it is an int type, the value range of p is limited to a prime number of 3-100, and the value of g is based on the value of p. The range of g is a prime number of 1-(p-1). , Xa is the same as xb, in the range of 2-(p-1).

