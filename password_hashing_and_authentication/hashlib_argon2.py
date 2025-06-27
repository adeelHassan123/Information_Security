import hashlib
import os  # To generate random salts
from argon2 import PasswordHasher

def hash_password_argon2(username: str, password: str) -> str:
    
    ph = PasswordHasher()
    combined = username + password
    hashed_password = ph.hash(combined)
    return hashed_password

def hash_password_sha512(username: str, password: str) -> str:
    
    salt = os.urandom(16)  
    
    combined = username + password + salt.hex() 
    
    combined_bytes = combined.encode('utf-8')
    
    sha512_hash = hashlib.sha512()
    
    sha512_hash.update(combined_bytes)
    
    hashed_password = sha512_hash.hexdigest()
    
    return hashed_password, salt.hex()  

while True:
    username = input("Enter your username: ")
    password = input("Enter your password: ")

    hashed_password, salt = hash_password_sha512(username, password)
    
    print(f"SHA-512 Hashed password (unique to username): {hashed_password}")
    print(f"Salt used: {salt}")

    hashed_password_argon2 = hash_password_argon2(username, password)
    print(f"Argon2 Hashed password (unique to username): {hashed_password_argon2}")
    
    continue_input = input("Do you want to hash another password? (y/n): ")
    if continue_input.lower() != 'y':
        break
