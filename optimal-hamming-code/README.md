# optimal Hamming code

This software is supposed to pick the most optimal Hamming code
for your purpose, shrink it and create generator and parity-check matrices.

# How to build?

```bash
git clone --recursive https://github.com/foxpy/optimal-hamming-code
cd optimal-hamming-code
mkdir build
cd build
cmake ..
cmake --build .
```

Resulting binary will be `optimal-hamming-code`.

# Sample outputs

```bash
; ./optimal-hamming-code --help
Find the most optimal Hamming code with specified information
vector bit length, also generate appropriate matrices G and H

Usage: ./optimal-hamming-code [OPTIONS...]

 Long options:
  --k=UNSIGNED ( default = 4) information vector bits
;
; ./optimal-hamming-code
The best appropriate Hamming code is (7,4,3)
Generator matrix G:
1 0 1 1
1 1 1 0
0 0 1 0
1 1 0 1
0 0 0 1
0 1 0 0
1 0 0 0
Parity check matrix H:
0 0 0 1 1 1 1
0 1 1 0 0 1 1
1 0 1 0 1 0 1
Random information vector I: 1 1 0 0
Encoded message C: 1 0 0 0 0 1 1
Adding error at 7: 1 0 0 0 0 1 0
Syndrome S: 1 1 1
;
; ./optimal-hamming-code --k=11
The best appropriate Hamming code is (15,11,3)
Generator matrix G:
1 0 1 1 1 0 1 0 1 0 1
1 1 1 0 0 1 1 0 0 1 1
0 0 1 0 0 0 0 0 0 0 0
1 1 0 1 1 1 1 1 0 0 0
0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0 0
1 1 0 1 0 0 0 1 1 1 1
0 0 0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 1 0 0 0
0 0 0 1 0 0 0 0 0 0 0
0 1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0 0
Parity check matrix H:
0 0 0 0 0 0 0 1 1 1 1 1 1 1 1
0 0 0 1 1 1 1 0 0 0 0 1 1 1 1
0 1 1 0 0 1 1 0 0 1 1 0 0 1 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
Random information vector I: 0 0 1 1 1 1 1 1 0 1 0
Encoded message C: 0 0 1 1 1 1 1 1 0 1 0 1 1 0 0
Adding error at 15: 0 0 1 1 1 1 1 1 0 1 0 1 1 0 1
Syndrome S: 1 1 1 1
;
```
