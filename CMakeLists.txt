cmake_minimum_required(VERSION 3.5.1)

set(SOURCE_FILES
    main_cc.cpp
    dto_json.cpp
    validate.cpp
    complex_validations.cpp
    CR_functions.cpp
    elgamal.cpp
    access.cpp
    events.cpp
    )



#include($ENV{FPC_PATH}/samples/chaincode/helloworld/libBLS/CMakeLists.txt)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
include($ENV{FPC_PATH}/ecc_enclave/enclave/CMakeLists-common-app-enclave.txt)







