#include "validate.h"
#include "dto_json.h"
#include "shim.h"

#include <numeric>
#include <vector>
#include "constants.h"

#include "CR_functions.h"

template <typename T>
bool isNotNull(const T* ptr) {
    return ptr != nullptr;
}

bool isEmpty(const std::string& str) {
    return str.empty();
}

bool containsOnlyNumbers(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool hasLength(const std::string& str, size_t length) {
    return str.length() == length;
}

bool isValidTaj(const std::string& str){
    if(!isEmpty(str) && hasLength(str,9) && containsOnlyNumbers(str) ){
        return true;
    }
    return false;
}

bool isValidBirthDate(const std::string& str){
    if(!isEmpty(str) && hasLength(str,8) && containsOnlyNumbers(str) ){
        return true;
    }
    return false;
}


bool isValidName(const std::string& str){
    if(!isEmpty(str) && isShorterThan(str,100) && containsOnlyLetters(str) ){
        return true;
    }
    return false;
}

bool containsOnlyLetters(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool isShorterThan(const std::string& str, size_t length) {
    return str.length() < length;
}

bool hasNoSpecialCharacters(const std::string& str) {
    for (char c : str) {
        if (!std::isalnum(c)) {
            return false;
        }
    }
    return true;
}

bool isValidDate(const std::string& str){
    if(hasLength(str,8) && containsOnlyNumbers(str) ){
        return true;
    }
    return false;
}

bool isValidCost(int cost){
    if(cost > 0){
        return true;
    }
    return false;
}

bool isValidPayment(int payment){
    if(payment > 0){
        return true;
    }
    return false;
}

bool isValidId(const std::string& str){
    if(!isEmpty(str) && hasLength(str,9) && hasNoSpecialCharacters(str) ){
        return true;
    }
    return false;
}


// CTX ACCESS

bool tajExists(const std::string& taj, shim_ctx_ptr_t ctx){

    data_map_t the_datamap = getDataMap(ctx);
    for (const auto& pair : the_datamap.persons) {
        if (pair.second.taj == taj) {
            return true;
        }
    }
    return false;
}



bool idExists(const std::string& id, shim_ctx_ptr_t ctx){

    person_t person = getPerson(id, ctx);
    if(person.id == id){
        return true;
    }
    return false;
}

bool isAlive(const std::string& id, shim_ctx_ptr_t ctx){

    person_t person = getPerson(id, ctx);
    
    if(person.id == id && person.death_date.empty()){
        return true;
    }

    return false;
}


bool isHealthy(const std::string& id, shim_ctx_ptr_t ctx){

    health_examination_t health_examination = getHealthExamination(id, ctx);
    if(health_examination.id == id
        && health_examination.diastole > 50
        && health_examination.diastole < 100 
        && health_examination.systole > 90 
        && health_examination.systole < 150){
        return true;
    }

    return false;
}

bool hasLifeInsurance(const std::string& id, shim_ctx_ptr_t ctx){

    life_insurance_t life_insurance = getLifeInsurance(id, ctx);

    if(life_insurance.id == id){
        return true;
    }

    return false;
}

bool hasWorkPermit(const std::string& id, shim_ctx_ptr_t ctx){

    work_permit_t work_permit = getWorkPermit(id, ctx);

    if(work_permit.id == id && work_permit.from != ""){
        return true;
    }

    return false;
}