#!/usr/bin/python3

from challenge import RSA

def main():
    encoded_flag = open('output.txt').read().split(' ')[1].strip()
    flag = b''
    while b'HTB' not in flag:
        crypto = RSA()
        flag = crypto.decrypt(bytearray.fromhex(encoded_flag))
    print(flag.decode())

if __name__ == '__main__':
    main()
