#pragma once

#include "validate.h"
#include "complex_validations.h"
#include "constants.h"
#include <string>
#include "elgamal.h"
#include "dto_json.h"
#include "CR_functions.h"

/*
    This file contains the functions that are called by the events.
    (The functions that are called by the events are the functions that are called by the client.)
*/

std::string onChainEncrypt(std::string input, shim_ctx_ptr_t ctx);  
std::string personBorn(shim_ctx_ptr_t ctx, std::string id, std::string taj, std::string name, std::string birth_date);
std::string personDie(shim_ctx_ptr_t ctx, std::string id);
std::string issueHealthExamination(shim_ctx_ptr_t ctx, std::string id, std::string taj, std::string examination_date, int systole, int diastole);
std::string issueLifeInsurance(shim_ctx_ptr_t ctx, std::string id, std::string taj, std::string from, std::string to, int cost, int payment, bool should_pay);
std::string issueWorkPermit(shim_ctx_ptr_t ctx, std::string id, std::string name, std::string from, std::string issuer);
std::string canWork(shim_ctx_ptr_t ctx, std::string id);

