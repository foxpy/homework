A collection of some error correction codes.

### Repetition (3, 1)

The [repetition code](repetition31/doc.md)
simply sends the same message three times.

### Hamming (8, 4)

The [Hamming code](hamming84/doc.md) is a simple
trick to improve efficiency of repetition code.
This library implements (8, 4) Hamming code with additional parity
to detect number of overall errors.

### Interleaver

[Interleaver](interleaver/doc.md) is not actually an
error correction code by itself, but it helps other
error correction codes to keep up with burst errors.
