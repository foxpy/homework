# needham-schroeder

A little app written in C11 demonstrating Needham-Schroeder protocol.
It supports only Linux because I don't have life for homework projects.
Writing homework in C is already crazy enough.

## server

Server application uses sqlite3 database to store user data and their symmetric keys.
Each user should only know his own symmetric key.
Also, each user knows his unique id and in order to talk to other users, they should
know their unique ids, too.

## client

Client application only initiates requests to server or waits for other clients
to talk to them.

## Data types

1. `ID` — 128-bit number, uniquely identifies user. Generated randomly from Linux entropy pool.
2. `NONCE` — 256-bit number, used only once. Generated randomly from Linux entropy pool.
3. `CIPHER` — 8-bit number, identifies chosen encryption type.
4. `KEY` — 256-bit number, secret symmetric key.

## Encryption types

0. xorshift "encryption" — only first 64 bits of key are used to seed xorshift64 generator,
   and its output is XORed with plaintext to "encrypt" it. That's right, this is insecure.
   Even worse, attacker can switch `CIPHER` flag to `0`, downgrading any secure cipher
   to "xorshift" nonsense. I don't care, this is just a homework. Real protocols never
   include vulnerable ciphers.
1. ChaCha20 encryption — actually a good cipher. Plain ChaCha20 stream cipher with 96-bit nonce.
2. ChaCha20Poly1305 AEAD — I hope to introduce this as well, but I don't have Poly1305
   implemented _yet_. Too bad!

## client-server protocol

1. client sends to server his `ID`, `ID` of user he is willing to connect to, `NONCE` and `CIPHER`.
2. server responds with a container K1 encrypted by chosen cipher with client key. This container
   includes a `NONCE` sent by client, one-time session `KEY` generated for these two users, `ID`
   the user wants to connect to and yet another container K2 (still inside the outer container)
   encrypted by `CIPHER` with `KEY` of second user, it contains a copy of one-time session `KEY`
   and first user `ID`.
3. client checks if `NONCE` and `ID` of user he is willing to connect are the same.

## client-client protocol

Now as client A has obtained data from server, he can connect to client B.
1. Client A sends `CIPHER` and encrypted container K2 obtainer from server to client B.
2. Client B is able to decrypt this container and see who is connecting to him. He also gets
   a one-time session key. Now client B generates random `NONCE`, encrypts it with session
   `KEY` and sends to client A.
3. Client A receives encrypted random `NONCE`, decrypts it, increments by one, encrypts back
   and sends back to client B, proving he knows session key, too. At this point clients are
   free to exchange whatever messages they have.
