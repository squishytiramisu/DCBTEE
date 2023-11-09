#include "shim.h"
#include "logging.h"
#include <string>
#include "dto_json.h"
#include "validate.h"
#include "complex_validations.h"
#include "CR_functions.h"
#include "constants.h"
#include "elgamal.h"
#include "events.h"
#include "access.h"


// Prepares the result to be sent back to the client
void prepareResult(std::string result, uint8_t* response, uint32_t max_response_len, uint32_t* actual_response_len){
    int neededSize = result.size();
    if (max_response_len < neededSize)
    {
        *actual_response_len = 0;
        result = "ERROR"; // Response buffer is too small
    }
    memcpy(response, result.c_str(), neededSize);
    *actual_response_len = neededSize;
}

// Starting point of the chaincode
int invoke(
    uint8_t* response,
    uint32_t max_response_len,
    uint32_t* actual_response_len,
    shim_ctx_ptr_t ctx)
{
    LOG_DEBUG("DCBTEECC: +++ Executing DCBTEE chaincode invocation +++");

    // Get function name and parameters
    std::string function_name;
    std::vector<std::string> params;
    get_func_and_params(function_name, params, ctx);
    std::string result;

    // Get transaction creator
    char tx_creator_name_msp_id[1024];
    char tx_creator_name_dn[1024];
    get_creator_name(tx_creator_name_msp_id, sizeof(tx_creator_name_msp_id),
        tx_creator_name_dn, sizeof(tx_creator_name_dn), ctx);
    std::string signature = params[params.size()-1];
    params.pop_back();

    if(function_name == "initAccessControl"){
        result = initAccessControl(params[0], ctx) ? "OK" : "ERROR";
        prepareResult(result, response, max_response_len, actual_response_len);
        return 0;
    }

    // Access control validation
    if(!isAllowedToInvoke(function_name,tx_creator_name_msp_id, tx_creator_name_dn, signature, ctx)){
        LOG_DEBUG("DCBTEECC: Not allowed to invoke");
        result = "ERROR";
        prepareResult(result, response, max_response_len, actual_response_len);
        return 0;
    }

    /////////////// FUNCTION SWITCH ///////////////////////
    // Here we forward the request to the appropriate function
    if(function_name == "PersonBorn"){
        if(params.size() != 4){
            LOG_DEBUG("personCC: PersonBorn: Wrong number of arguments");
            result = "ERROR";
            prepareResult(result, response, max_response_len, actual_response_len);
            return 0;
        }
        std::string id = params[0];
        std::string taj = params[1];
        std::string name = params[2];
        std::string birth_date = params[3];
        result = personBorn(ctx, id, taj, name, birth_date);

    }else if(function_name == "PersonDie"){
        if(params.size() != 1){
            LOG_DEBUG("personCC: PersonDie: Wrong number of arguments");
            result = "ERROR";
            prepareResult(result, response, max_response_len, actual_response_len);
            return 0;
        }
        std::string id = params[0];
        result = personDie(ctx, id);

    }else if(function_name == "IssueHealthExamination"){
        if(params.size() != 5){
            result = "ERROR";
            prepareResult(result, response, max_response_len, actual_response_len);
            LOG_DEBUG("personCC: IssueHealthExamination: Wrong number of arguments");
            return 0;
        }
        std::string id = params[0];
        std::string taj = params[1];
        std::string examination_date = params[2];
        int systole = std::stoi(params[3]);
        int diastole = std::stoi(params[4]);
        result = issueHealthExamination(ctx, id, taj, examination_date, systole, diastole);

    }else if(function_name == "IssueLifeInsurance"){
        if(params.size() != 6){
            LOG_DEBUG("personCC: IssueLifeInsurance: Wrong number of arguments");
            result = "ERROR";
            prepareResult(result, response, max_response_len, actual_response_len);
            return 0;
        }
        std::string id = params[0];
        std::string taj = params[1];
        std::string from = params[2];
        std::string to = params[3];
        int cost = std::stoi(params[4]);
        int payment = std::stoi(params[5]);
        bool should_pay = false;
        result = issueLifeInsurance(ctx, id, taj, from, to, cost, payment, false);

    }else if(function_name == "IssueWorkPermit"){
        if(params.size() != 4){
            LOG_DEBUG("personCC: IssueWorkPermit: Wrong number of arguments");
            result = "ERROR";
            prepareResult(result, response, max_response_len, actual_response_len);
            return 0;
        }
        std::string id = params[0];
        std::string name = params[1];
        std::string from = params[2];
        std::string issuer = params[3];
        result = issueWorkPermit(ctx, id, name, from, issuer);

    }else if(function_name == "hasWorkPermit")
    {
        if(params.size() != 1){
            LOG_DEBUG("personCC: hasWorkPermit: Wrong number of arguments");
            result = "ERROR";
            prepareResult(result, response, max_response_len, actual_response_len);
            return 0;
        }
        std::string id = params[0];
        result = canWork(ctx, id);
        result = onChainEncrypt(result, ctx);
    }

    else if(function_name == "initEncryption"){
        result = initEncryption(params[0], params[1], params[2], params[3], params[4], ctx) ? "OK" : "ERROR";
    }

    else if(function_name == "initAccessControl"){
        result = initAccessControl(params[0], ctx) ? "OK" : "ERROR";
    }

    else{
        LOG_DEBUG("DCBTEECC: RECEIVED UNKNOWN transaction '%s'", function_name);
        return 0;
    }
    /////////////// RETURNING ///////////////////////

    prepareResult(result, response, max_response_len, actual_response_len);

    LOG_DEBUG("DCBTEECC: Response: %s", result.c_str());
    LOG_DEBUG("DCBTEECC: +++ Executing done +++");
    return 0;
}


