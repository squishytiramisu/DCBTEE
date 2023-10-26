#pragma once

#include <string>
#include "shim.h"
#include <map>
#include <vector>
#include "constants.h"
#include <algorithm>

bool isAllowedToInvoke(std::string
   function,
   std::string caller,
   std::string caller_msp,
   std::string signature,
   shim_ctx_ptr_t ctx
);

bool initEncryption(std::string g, std::string g_hat, std::string q, std::string p, std::string y, shim_ctx_ptr_t ctx);

bool initAccessControl(std::string configString, shim_ctx_ptr_t ctx);

std::map < std::string, std::vector < std::string >> parseConfig(std::string configString);

bool validSignature(std::string signature, std::string publicKey);