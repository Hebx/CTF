#/usr/bin/python3

from Crypto.Util.number import bytes_to_long
from challenge import RSA

def main():
    output = open('output.txt').read().split(' ')[1].strip()
    crypto = RSA()
    flag = b''
    first = bytes_to_long(bytearray.fromhex(output))
    num = first

    print(f"first = {first}\n------------------------------")

    while num >= first:
        crypto = RSA()
        flag = crypto.decrypt(bytearray.fromhex(output))
        num = bytes_to_long(flag)

    #print(f"p = {crypto.p}")
    #print(f"q = {crypto.q}")
    #print(f"e = {crypto.e}")
    #print(f"n = {crypto.n}")
    #print(f"d = {crypto.d}")
    #print(f"num = {num}")
    #print(f"mod = {num % crypto.n}")
    #print(f"test = {first % num}")
    print(flag.decode())

if __name__ == '__main__':
    main()
