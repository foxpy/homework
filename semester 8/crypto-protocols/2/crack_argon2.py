#!/bin/env python3
from argon2 import PasswordHasher
import threading
import time
import sys,os
import optparse

# Auther Vishal Biswas (https://twitter.com/CyberKnight00)
# I have adapted this ugly utility to be useful in scripts
# Why would you care about colourful output when your exit
# codes are messed up and program output is not captured
# by shell? That's just amazing. I hate humanity.

def check(word):
    print('.', end='', file=sys.stderr)
    sys.stderr.flush()
    success = False
    try:
        if(ph.verify(hash, word) == True) :
            success = True
    except:
        pass
    if success:
        print(f"{hash} -> {word}")
        exit(0)

# Start

if __name__ == '__main__':
    parser = optparse.OptionParser()
    parser.add_option('-v', '--verbose', action="store_true", help = "Verbose = True" )
    parser.add_option('-c', '--crack', action="store", dest="argon2_hash", help="Argon2 hash to be crack")
    parser.add_option('-w', '--wordlist', action="store", dest="wordlist", help="Wordlist for crack salted hash")

    options, args = parser.parse_args()

    if not options.argon2_hash:
        print("[+] Specify a Argon2 hash")
        print("[+] Example usage crack_Argon2.py -c argon2_hash -w path-to-wordlist")
        exit()

    else:
        hash = options.argon2_hash

    wordlist_tmp = '/usr/share/wordlists/fasttrack.txt'

    if not options.wordlist :
        wordlist = wordlist_tmp

    else:
        wordlist = options.wordlist

    ph = PasswordHasher()

    with open (wordlist, 'r', encoding='utf-8') as list:
        for word in list.read().splitlines():
            check(word)
    exit(1)
