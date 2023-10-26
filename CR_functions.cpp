
#include "CR_functions.h"


person_t getPerson(std::string key,  shim_ctx_ptr_t ctx)
{
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        person_t person;
        return person;
    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    // check if person exists
    if (the_datamap.persons.find(key) == the_datamap.persons.end())
    {
        LOG_DEBUG("datamapCC: person does not exist");
        person_t the_person;
        return the_person;
    }
    return the_datamap.persons[key];
}

health_examination_t getHealthExamination(std::string id, shim_ctx_ptr_t ctx)
{
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        health_examination_t health_examination;
        return health_examination;
    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    // check if health_examination exists
    if (the_datamap.health_examinations.find(id) == the_datamap.health_examinations.end())
    {
        LOG_DEBUG("datamapCC: health_examination does not exist");
        health_examination_t the_health_examination;
        return the_health_examination;
    }
    return the_datamap.health_examinations[id];
}

life_insurance_t getLifeInsurance(std::string id, shim_ctx_ptr_t ctx)
{
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        life_insurance_t life_insurance;
        return life_insurance;
    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    // check if life_insurance exists
    if (the_datamap.life_insurances.find(id) == the_datamap.life_insurances.end())
    {
        LOG_DEBUG("datamapCC: life_insurance does not exist");
        life_insurance_t the_life_insurance;
        return the_life_insurance;
    }
    return the_datamap.life_insurances[id];

}

work_permit_t getWorkPermit(std::string id, shim_ctx_ptr_t ctx)
{
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        work_permit_t work_permit;
        return work_permit;
    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    // check if work_permit exists
    if (the_datamap.work_permits.find(id) == the_datamap.work_permits.end())
    {
        LOG_DEBUG("datamapCC: work_permit does not exist");
        work_permit_t the_work_permit;
        return the_work_permit;
    }
    return the_datamap.work_permits[id];

}


std::string putPerson(person_t person, shim_ctx_ptr_t ctx){
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        putDataMap(ctx);
        get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);
    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
     // check if work_permit exists
    if (the_datamap.persons.find(person.id) == the_datamap.persons.end())
    {
        the_datamap.persons.insert(std::pair<std::string, person_t>(person.id, person));
    }else{
        the_datamap.persons[person.id] = person;
    }

    std::string datamap_json = marshal_data_map(&the_datamap);
    put_state(DATAMAP_KEY, (uint8_t*)datamap_json.c_str(), datamap_json.length(), ctx);
    return OK;
}

std::string putHealthExamination(health_examination_t health_examination, shim_ctx_ptr_t ctx){
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        putDataMap(ctx);
        get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    the_datamap.health_examinations.insert(std::pair<std::string, health_examination_t>(health_examination.id, health_examination));

    std::string datamap_json = marshal_data_map(&the_datamap);
    put_state(DATAMAP_KEY, (uint8_t*)datamap_json.c_str(), datamap_json.length(), ctx);
    return OK;
}

std::string putLifeInsurance(life_insurance_t life_insurance, shim_ctx_ptr_t ctx){
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        putDataMap(ctx);
        get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    the_datamap.life_insurances.insert(std::pair<std::string, life_insurance_t>(life_insurance.id, life_insurance));

    std::string datamap_json = marshal_data_map(&the_datamap);
    put_state(DATAMAP_KEY, (uint8_t*)datamap_json.c_str(), datamap_json.length(), ctx);
    return OK;
}

std::string putWorkPermit(work_permit_t work_permit, shim_ctx_ptr_t ctx){
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    if (datamap_bytes_len == 0)
    {
        LOG_DEBUG("datamapCC: datamap does not exist");
        putDataMap(ctx);
    }

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);
    
    the_datamap.work_permits.insert(std::pair<std::string, work_permit_t>(work_permit.id, work_permit));

    std::string datamap_json = marshal_data_map(&the_datamap);
    put_state(DATAMAP_KEY, (uint8_t*)datamap_json.c_str(), datamap_json.length(), ctx);
    return OK;
}

std::string putDataMap(shim_ctx_ptr_t ctx){

    data_map_t the_datamap;
    std::string datamap_json = marshal_data_map(&the_datamap);
    put_state(DATAMAP_KEY, (uint8_t*)datamap_json.c_str(), datamap_json.length(), ctx);
    return OK;
}

// For development purposes only
data_map_t getDataMap(shim_ctx_ptr_t ctx){
    // check if datamap exists
    uint32_t datamap_bytes_len = 0;
    uint8_t datamap_bytes[MAX_VALUE_SIZE];

    get_state(DATAMAP_KEY, datamap_bytes, sizeof(datamap_bytes), &datamap_bytes_len, ctx);

    // get datamap datamap from json
    data_map_t the_datamap;
    unmarshal_data_map(&the_datamap, (const char*)datamap_bytes, datamap_bytes_len);

    return the_datamap;
}
