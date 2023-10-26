#include "access.h"


bool isAllowedToInvoke(std::string
   function,
   std::string caller,
   std::string caller_msp,
   std::string signature,
   shim_ctx_ptr_t ctx) {

   //Check signature
   if (!validSignature(signature, caller)) {
      return false;
   }

   //Get config
   uint32_t config_bytes_len = 0;
   uint8_t config_bytes[MAX_VALUE_SIZE];
   get_public_state("config", config_bytes, sizeof(config_bytes), & config_bytes_len, ctx);

   //Parse config
   auto vector = parseConfig(std::string((const char * ) config_bytes))[function];

   // For the prototype, we use the callers signature passed as a parameter
   //auto it = std::find(vector.begin(), vector.end(), caller_msp);
   auto it = std::find(vector.begin(), vector.end(), signature);
   if (it != vector.end()) {
      return true;
   } else {
      return false;
   }
}

bool initEncryption(std::string g, std::string g_hat, std::string q, std::string p, std::string y, shim_ctx_ptr_t ctx) {
   put_public_state("g", (uint8_t * ) g.c_str(), g.size(), ctx);
   put_public_state("g_hat", (uint8_t * ) g_hat.c_str(), g_hat.size(), ctx);
   put_public_state("q", (uint8_t * ) q.c_str(), q.size(), ctx);
   put_public_state("p", (uint8_t * ) p.c_str(), p.size(), ctx);
   put_public_state("y", (uint8_t * ) y.c_str(), y.size(), ctx);
   return true;
}

bool initAccessControl(std::string configString, shim_ctx_ptr_t ctx) {

   //Check whether config already exists
   uint32_t config_len;
   uint8_t config[MAX_VALUE_SIZE];
   get_public_state("config", config, sizeof(config), & config_len, ctx);
   if (config_len > 0) {
      LOG_DEBUG("DCBTEECC: Config already exists");
      return false;
   }

   put_public_state("config", (uint8_t * ) configString.c_str(), configString.size(), ctx);
   return true;
}

std::map < std::string, std::vector < std::string >> parseConfig(std::string configString) {
   std::map < std::string, std::vector < std::string >> dataMap;
   size_t pos = 0;
   while (pos < configString.length()) {
      size_t colonPos = configString.find(':', pos);
      if (colonPos == std::string::npos) {
         break;
      }
      std::string name = configString.substr(pos, colonPos - pos);
      pos = colonPos + 1;
      size_t semicolonPos = configString.find(';', pos);
      std::string orgData = configString.substr(pos, semicolonPos - pos);
      std::vector < std::string > orgs;
      size_t commaPos = 0;
      while (commaPos < orgData.length()) {
         size_t nextCommaPos = orgData.find(',', commaPos);
         if (nextCommaPos == std::string::npos) {
            nextCommaPos = orgData.length();
         }
         orgs.push_back(orgData.substr(commaPos, nextCommaPos - commaPos));
         commaPos = nextCommaPos + 1;
      }
      dataMap[name] = orgs;
      pos = semicolonPos + 1;
   }
   return dataMap;
}

//The prototype does not check the signature 
bool validSignature(std::string signature, std::string publicKey) {
   return true;
}