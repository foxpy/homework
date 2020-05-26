```c
#include "serial.h"
```

Emulates Serial port data flow.

### serial_cfg_t

Stores configuration for Serial emulator.
Fields:

`data_bits` - number of bits transmitted per packet. Possible values:
`DATA_BITS_5`, `DATA_BITS_6`, `DATA_BITS_7`, `DATA_BITS_8` and `DATA_BITS_9`.

`parity` - type of parity bit used for integrity check. Possible values:
`PARITY_NONE`, `PARITY_ODD` and `PARITY_EVEN`.

`stop_bits` - number of stop bits. Possible values:
`STOP_BITS_1` and `STOP_BITS_2`.

### serial_encode()

```c
void serial_encode(bits_t *dst, bits_t *src, serial_cfg_t *cfg);
```

Encodes `src` bits to `dst` bits, simulating
Serial port data flow according to settings pointed by `cfg`.
Encoded bits are pulled from `src`. If there are still bits in `src`, but
their amount is not enough for successful encoding, they are left in `src`.
Returns number of encoded packets.

### serial_decode()

```c
size_t serial_decode(bits_t *dst, bits_t *src, serial_cfg_t *cfg);
```

Decodes simulated Serial port data flow from `src` to `dst`
using settings pointed by `cfg`.
Packets with parity mismatch or broken start/stop bits are still
decoded as is, and number of malformed packets +
possible retransmissions is returned.
Decoded bits are pulled from `src`. If there are still bits in `src`, but
their amount is not enough for successful decoding, they are left in `src`.

### serial_packet_length()

```c
unsigned char serial_packet_length(serial_cfg_t *cfg);
```

Returns bit length of Serial packet encoded using `cfg` settings.
