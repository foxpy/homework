# ecc-exists

This is my homework too complex to remain in
main homework repository. It checks if ECC with
given parameters exists by these bounds:
- [Singleton bound](https://en.wikipedia.org/wiki/Singleton_bound)
- [Hamming bound](https://en.wikipedia.org/wiki/Hamming_bound)
- Gilbert bound
- [Gilbert-Varshamov bound](https://en.wikipedia.org/wiki/Gilbert%E2%80%93Varshamov_bound)

## How to build?

```bash
git clone --recursive https://github.com/foxpy/ecc-exists
cd ecc-exists
mkdir build
cd build
cmake ..
cmake --build .
```

## How to run?

```bash
# Check if Hamming (7, 4) code exists
./ecc-exists -v --q=2 --n=7 --k=4 --d=3
```
