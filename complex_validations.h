#pragma once


#include "validate.h"
#include "constants.h"


/*
Validations:
 - id is valid
 - taj number is valid
 - name is not empty
 - name is not too long
 - name has no special characters
 - date of birth is valid
 - taj is not already registered
*/
bool validPersonBorn(std::string id, std::string taj, std::string name, std::string birth_date, shim_ctx_ptr_t ctx);

bool validIssueLifeInsurance(std::string id, std::string taj, std::string from, std::string to, int cost, int payment, shim_ctx_ptr_t ctx);

bool validIssueHealthExamination(std::string id, std::string taj, std::string examination_date, int systole, int diastole, shim_ctx_ptr_t ctx);

bool validIssueWorkPermit(std::string id, std::string name, std::string from, std::string issuer, shim_ctx_ptr_t ctx);

bool validPersonDie(std::string id, shim_ctx_ptr_t ctx);

bool validPayRequest(std::string id, shim_ctx_ptr_t ctx);

bool validRevokeWorkPermit(std::string id, shim_ctx_ptr_t ctx);

bool validCanWork(std::string id, shim_ctx_ptr_t ctx);