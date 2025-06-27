# Simple SHA-512 implementation in Python without using any libraries

# Constants for SHA-512
K = [
    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f1f4e2f9, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac5c5b,
    0x2de92c6f592b0275, 0x4a7484aa6ea6d9b1, 0x5cb0a9dcbd41fbd4, 0x76f988da2d2d7bbf,
    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fc3e7a, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ff3, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f0a6e19f4, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7f8f4c5d6a,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c724cd, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4b2f836ed72, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
]

# Right rotate
def right_rotate(x, n):
    return ((x >> n) | (x << (64 - n))) & 0xFFFFFFFFFFFFFFFF

# Padding the message to fit the block size
def pad_message(message):
    bit_length = len(message) * 8
    message += b'\x80'
    while (len(message) * 8) % 1024 != 896:
        message += b'\x00'
    message += bit_length.to_bytes(16, 'big')
    return message

# SHA-512 Hash function
def sha512(message):
    # Pad the message
    message = pad_message(message)

    # Initial hash values
    h = [
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    ]

    # Process each 1024-bit block
    for i in range(0, len(message), 128):
        block = message[i:i + 128]

        # Break the block into 16 64-bit words
        w = [int.from_bytes(block[j:j+8], 'big') for j in range(0, 128, 8)]
        
        # Extend the 16 words into 80 words
        for t in range(16, 80):
            s0 = right_rotate(w[t - 15], 1) ^ right_rotate(w[t - 15], 8) ^ (w[t - 15] >> 7)
            s1 = right_rotate(w[t - 2], 19) ^ right_rotate(w[t - 2], 61) ^ (w[t - 2] >> 6)
            w.append((w[t - 16] + s0 + w[t - 7] + s1) & 0xFFFFFFFFFFFFFFFF)

        # Initialize working variables
        a, b, c, d, e, f, g, h_ = h

        # Main loop
        for t in range(80):
            t1 = (h_ + right_rotate(e, 14) ^ right_rotate(e, 18) ^ right_rotate(e, 41) + ((e & f) ^ (~e & g)) + K[t] + w[t]) & 0xFFFFFFFFFFFFFFFF
            t2 = (right_rotate(a, 28) ^ right_rotate(a, 34) ^ right_rotate(a, 39) + ((a & b) ^ (a & c) ^ (b & c))) & 0xFFFFFFFFFFFFFFFF

            h_ = g
            g = f
            f = e
            e = (d + t1) & 0xFFFFFFFFFFFFFFFF
            d = c
            c = b
            b = a
            a = (t1 + t2) & 0xFFFFFFFFFFFFFFFF

        # Add the compressed block to the hash
        h = [(x + y) & 0xFFFFFFFFFFFFFFFF for x, y in zip(h, [a, b, c, d, e, f, g, h_])]

    # Return the final hash
    return ''.join([hex(x)[2:].zfill(16) for x in h])

# Get input from the user
username = input("Enter the username to hash: ").encode('utf-8')
passward= input("Enter the password to hash: ").encode('utf-8')

combine = username+passward
# Call SHA-512
hashed_message = sha512(combine)

# Print the result
print("SHA-512 Hash of the message:", hashed_message)
