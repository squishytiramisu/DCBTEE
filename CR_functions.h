#pragma once

#include <iostream>
#include <string>
#include "constants.h"
#include "shim.h"
#include "dto_json.h"


/*
    This file contains the function to create, read and update the state of a private data.
    The state is stored in a json format, which is stored in the ledger privately.
*/

person_t getPerson(std::string key,  shim_ctx_ptr_t ctx);

health_examination_t getHealthExamination(std::string id,  shim_ctx_ptr_t ctx);

work_permit_t getWorkPermit(std::string id, shim_ctx_ptr_t ctx);

life_insurance_t getLifeInsurance(std::string id, shim_ctx_ptr_t ctx);

data_map_t getDataMap(shim_ctx_ptr_t ctx);


std::string putPerson(person_t person, shim_ctx_ptr_t ctx);

std::string putHealthExamination(health_examination_t health_examination, shim_ctx_ptr_t ctx);

std::string putWorkPermit(work_permit_t work_permit, shim_ctx_ptr_t ctx);

std::string putLifeInsurance(life_insurance_t life_insurance, shim_ctx_ptr_t ctx);

std::string putDataMap(shim_ctx_ptr_t ctx);