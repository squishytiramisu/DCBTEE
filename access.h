#pragma once

#include <string>
#include "shim.h"
#include <map>
#include <vector>
#include "constants.h"
#include <algorithm>


/*
   The access control configuration is stored in the ledger as a string.
   The string is parsed into a map of function names and a vector of allowed caller MSPs.
*/

// Returns true if the caller is allowed to invoke the function
bool isAllowedToInvoke(std::string
   function,
   std::string caller,
   std::string caller_msp,
   std::string signature,
   shim_ctx_ptr_t ctx
);


// Initialize encryption by saving the public encryption parameters
bool initEncryption(std::string g, std::string g_hat, std::string q, std::string p, std::string y, shim_ctx_ptr_t ctx);

// Initialize access control by saving the access control configuration
bool initAccessControl(std::string configString, shim_ctx_ptr_t ctx);

// Parse the access control configuration from a string to a map
std::map < std::string, std::vector < std::string >> parseConfig(std::string configString);

// Returns true whether the signature is valid
bool validSignature(std::string signature, std::string publicKey);