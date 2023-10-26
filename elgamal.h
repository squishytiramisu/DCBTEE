#pragma once


#include <openssl/bn.h>
#include <string>
#include <tuple>


std::string elgamal_encrypt(BIGNUM* g, BIGNUM* g_hat, BIGNUM* q, BIGNUM* p, BIGNUM* y, const std::string& m);

std::string intToHex(int value);

void hash_2(const std::string& hx, const BIGNUM* g1, const BIGNUM* g2, const BIGNUM* g3, const BIGNUM* g4, const BIGNUM* q,BN_CTX* xd, BIGNUM* result);