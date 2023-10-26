#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string>
#include <map>


/*
    This file contains the data transfer objects for the chaincode.
    As well as the marshalling and unmarshalling functions.
*/


typedef struct person{
    std::string id;
    std::string taj;
    std::string name;
    std::string birth_date;
    std::string death_date;
} person_t;

typedef struct health_examination{
    std::string id;
    std::string taj;
    int systole;
    int diastole;
    std::string date;
} health_examination_t;

typedef struct life_insurance{
    std::string id;
    std::string taj;
    std::string from;
    std::string to;
    int cost;
    int payment;
    bool should_pay;
} life_insurance_t;

typedef struct work_permit{
    std::string id;
    std::string name;
    std::string from;
    std::string issuer;
} work_permit_t;

typedef struct data_map{
    std::map <std::string, person_t> persons;
    std::map <std::string, health_examination_t> health_examinations;
    std::map <std::string, life_insurance_t> life_insurances;
    std::map <std::string, work_permit_t> work_permits;
} data_map_t;




std::string marshal_person(person_t* person);
std::string marshal_health_examination(health_examination_t* health_examination);
std::string marshal_life_insurance(life_insurance_t* life_insurance);
std::string marshal_work_permit(work_permit_t* work_permit);
std::string marshal_data_map(data_map_t* data_map);

int unmarshal_person(person_t* person, const char* json_bytes, uint32_t json_len);
int unmarshal_health_examination(health_examination_t* health_examination, const char* json_bytes, uint32_t json_len);
int unmarshal_life_insurance(life_insurance_t* life_insurance, const char* json_bytes, uint32_t json_len);
int unmarshal_work_permit(work_permit_t* work_permit, const char* json_bytes, uint32_t json_len);
int unmarshal_data_map(data_map_t* data_map, const char* json_bytes, uint32_t json_len);




