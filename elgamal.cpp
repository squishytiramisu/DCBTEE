#include <string>
#include <sstream>
#include <openssl/sha.h>
#include <openssl/bn.h>
#include <cstring>
#include "elgamal.h"
#include <vector>


/*
    This implementation is based on the following paper:
    Securing Threshold Cryptosystems against Chosen Ciphertext Attack

    As well as the following implementations:
     - a textbook ElGamal implementation by Christian Cachin
     - https://github.com/noahschmid/threshold_elgamal_python

    The implementation is not optimized for performance,
    but rather for readability and ease of understanding, 
    it is not recommended to use this implementation in production,
    but rather as a reference for understanding the algorithm.

*/


std::string elgamal_encrypt(BIGNUM * g, BIGNUM * g_hat,
                           BIGNUM * q, BIGNUM * p,
                           BIGNUM * y, const std::string & m) {

   BN_CTX * ctx = BN_CTX_new();
   BIGNUM * r = BN_new();
   BIGNUM * s = BN_new();
   BIGNUM * rG = BN_new();
   BIGNUM * h = BN_new();
   BIGNUM * u = BN_new();
   BIGNUM * w = BN_new();
   BIGNUM * u_hat = BN_new();
   BIGNUM * w_hat = BN_new();
   BIGNUM * e = BN_new();
   BIGNUM * f = BN_new();

   // Generate random values for r and s
   BN_rand_range(r, q);

   BN_rand_range(s, q);

   // Calculate rG = y^r mod p
   BN_mod_exp(rG, y, r, p, ctx);

   // Convert rG to a dec string
   std::string rG_dec = BN_bn2dec(rG);

   // Hash the decimal utf8 number using SHA-256
   const unsigned char * utf8_rG = reinterpret_cast <const unsigned char * > (rG_dec.c_str());

   unsigned char hash[SHA256_DIGEST_LENGTH];
   SHA256((const unsigned char * ) utf8_rG, rG_dec.length(), hash);
   BN_bin2bn(hash, SHA256_DIGEST_LENGTH, h);

   // Compute M HEX
   std::string m_hex;
   for (char c: m) {
      m_hex += intToHex((int) c);
   }

   std::string hashHex = BN_bn2hex(h);

   // Compute C
   BIGNUM * m_bn = BN_new();
   BIGNUM * h_bn = BN_new();
   BN_hex2bn( & m_bn, m_hex.c_str());
   BN_hex2bn( & h_bn, hashHex.c_str());

   size_t max_len = std::max(BN_num_bytes(m_bn), BN_num_bytes(h_bn));
   unsigned char * m_bin = static_cast < unsigned char * > (OPENSSL_malloc(max_len));
   unsigned char * h_bin = static_cast < unsigned char * > (OPENSSL_malloc(max_len));
   BN_bn2binpad(m_bn, m_bin, max_len);
   BN_bn2binpad(h_bn, h_bin, max_len);

   // Perform the XOR operation byte-wise
   unsigned char * result_bin = static_cast < unsigned char * > (OPENSSL_malloc(max_len));
   for (size_t i = 0; i < max_len; i++) {
      result_bin[i] = m_bin[i] ^ h_bin[i];
   }
   // Convert the result back to a BIGNUM
   BIGNUM * result_bn = BN_bin2bn(result_bin, max_len, nullptr);

   
   // Convert the result back to a hexadecimal string
   char * resultHex = BN_bn2hex(result_bn);

   std::string c_hex(resultHex);

   //We have to lower because further calculations are case sensitive
   for (auto & c: c_hex) {
      c = tolower(c);
   }

   OPENSSL_free(resultHex);
   BN_free(result_bn);

   // Calculate u = g^r mod p
   BN_mod_exp(u, g, r, p, ctx);
   // Calculate w = g^s mod p
   BN_mod_exp(w, g, s, p, ctx);
   // Calculate u_hat = g_hat^r mod p
   BN_mod_exp(u_hat, g_hat, r, p, ctx);
   // Calculate w_hat = g_hat^s mod p
   BN_mod_exp(w_hat, g_hat, s, p, ctx);

   // return u, w, u_hat, w_hat
   char * u_dec = BN_bn2dec(u);
   char * w_dec = BN_bn2dec(w);
   char * u_hat_dec = BN_bn2dec(u_hat);
   char * w_hat_dec = BN_bn2dec(w_hat);

   // Calculate e 
   hash_2(c_hex, u, w, w_hat, u_hat, q, ctx, e);

   // Calculate f = (s + r * e) % q
   BN_mul(r, r, e, ctx);
   BN_mod_add(f, s, r, q, ctx);

   char * u_str = BN_bn2dec(u);
   char * u_hat_str = BN_bn2dec(u_hat);
   char * e_str = BN_bn2dec(e);
   char * f_str = BN_bn2dec(f);

   BN_CTX_free(ctx);
   BN_free(r);
   BN_free(s);
   BN_free(rG);
   BN_free(h);
   BN_free(u);
   BN_free(w);
   BN_free(u_hat);
   BN_free(w_hat);
   BN_free(e);
   BN_free(f);
   return std::string("OK: ") + c_hex + " " + std::string(u_str) + " " + std::string(u_hat_str) + " " + std::string(e_str) + " " + std::string(f_str);

}

// We can not use standard functions due to the TEE
std::string intToHex(int value) {
   try {
      std::string hexString;
      while (value > 0) {
         int digit = value % 16;
         char hexDigit = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);
         hexString = hexDigit + hexString;
         value /= 16;
      }
      if (hexString.empty()) {
         hexString = "0";
      }
      return hexString;
   } catch (const std::exception & e) {
      throw;
   }
}


void hash_2(const std::string & hx,
   const BIGNUM * g1,
      const BIGNUM * g2,
         const BIGNUM * g3,
            const BIGNUM * g4,
               const BIGNUM * q, BN_CTX * xd, BIGNUM * result) {
   // Convert BIGNUMs to decimal string
   char * g1_dec = BN_bn2dec(g1);
   char * g2_dec = BN_bn2dec(g2);
   char * g3_dec = BN_bn2dec(g3);
   char * g4_dec = BN_bn2dec(g4);

   // Concatenate the input values as a single string
   std::string input_str = hx + g1_dec + g2_dec + g3_dec + g4_dec;

   // Compute the SHA-256 hash
   unsigned char hash[SHA256_DIGEST_LENGTH];
   SHA256(reinterpret_cast <
      const unsigned char * > (input_str.c_str()), input_str.length(), hash);

   // Convert the hash to a BIGNUM
   BN_bin2bn(hash, SHA256_DIGEST_LENGTH, result);

   // Reduce the hash modulo q
   BN_mod(result, result, q, xd);
}
