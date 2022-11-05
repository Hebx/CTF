import random
from secret import FLAG


def str2bin(x):
    return "".join([bin(ord(c))[2:].zfill(8) for c in x])


def bin2str(b):
    return "".join(chr(int(b[i: i + 8], 2)) for i in range(0, len(b), 8))


def flip_bit(b, n): return b[:n] + str(int(not int(b[n]))) + b[n + 1:]


def calc_redundant_bits(m):
    for i in range(m):
        if 2 ** i >= m + i + 1:
            return i


def pos_redundant_bits(data, r):
    # Place redundancy bits to the positions of the power of 2
    j = 0
    k = 1
    m = len(data)
    res = ""
    # Insert '0' to the positions of the power of 2
    for i in range(1, m + r + 1):
        if i == 2 ** j:
            res = res + "0"
            j += 1
        else:
            res = res + data[-1 * k]
            k += 1

    return res[::-1]


def calc_parity_bits(arr, r):
    n = len(arr)

    # Searching for r parity bit
    for i in range(r):
        val = 0
        for j in range(1, n + 1):

            # If position has 1 in ith significant
            # position then Bitwise OR the array value
            # to find parity bit value.
            if j & (2 ** i) == (2 ** i):
                val = val ^ int(arr[-1 * j])
                # -1 * j is given since array is reversed

        # String Concatenation
        # (0 to n - 2^r) + parity bit + (n - 2^r + 1 to n)
        arr = arr[: n - (2 ** i)] + str(val) + arr[n - (2 ** i) + 1:]
    return arr


def hamming_encode(ct, r):
    bin_ct = bin(ord(ct))[2:].zfill(8)
    arr = pos_redundant_bits(bin_ct, r)
    arr = calc_parity_bits(arr, r)
    return arr


def flip_bit_randomly(arr):
    random_pos = random.randint(0, len(arr))
    if random_pos != len(arr):
        arr = flip_bit(arr, random_pos)
    return arr


def encode(message, r):
    res = ""
    for char in message:
        part = hamming_encode(char, r)
        part = flip_bit_randomly(part)
        res += part
    if len(res) % 8 != 0:
        res += "0" * 12

    return bin2str(res)


if __name__ == "__main__":

    r = calc_redundant_bits(8)
    res = FLAG

    for _ in range(8):
        res = encode(res, r)

    with open("enc.bin", "w") as w:
        w.write(res)
