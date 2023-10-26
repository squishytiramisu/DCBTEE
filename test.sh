#!/usr/bin/env bash

if [[ -z "${FPC_PATH}" ]]; then
  echo "Error: FPC_PATH not set"; exit 1
fi

FABRIC_CFG_PATH="${FPC_PATH}/integration/config"
FABRIC_SCRIPTDIR="${FPC_PATH}/fabric/bin/"

. ${FABRIC_SCRIPTDIR}/lib/common_utils.sh
. ${FABRIC_SCRIPTDIR}/lib/common_ledger.sh

# this is the path points to FPC chaincode binary
CC_PATH=${FPC_PATH}/samples/chaincode/DCBTEE/_build/lib/

CC_ID=DCBTEE_test
CC_VER="$(cat ${CC_PATH}/mrenclave)"
CC_EP="OR('SampleOrg.member')"
CC_SEQ="1"


install_chaincode(){
    say "- install DCBTEE chaincode"
    PKG=/tmp/${CC_ID}.tar.gz
    ${PEER_CMD} lifecycle chaincode package --lang fpc-c --label ${CC_ID} --path ${CC_PATH} ${PKG}
    ${PEER_CMD} lifecycle chaincode install ${PKG}

    PKG_ID=$(${PEER_CMD} lifecycle chaincode queryinstalled | awk "/Package ID: ${CC_ID}/{print}" | sed -n 's/^Package ID: //; s/, Label:.*$//;p')

    ${PEER_CMD} lifecycle chaincode approveformyorg -o ${ORDERER_ADDR} -C ${CHAN_ID} --package-id ${PKG_ID} --name ${CC_ID} --version ${CC_VER} --sequence ${CC_SEQ} --signature-policy ${CC_EP}
    ${PEER_CMD} lifecycle chaincode checkcommitreadiness -C ${CHAN_ID} --name ${CC_ID} --version ${CC_VER} --sequence ${CC_SEQ} --signature-policy ${CC_EP}
    ${PEER_CMD} lifecycle chaincode commit -o ${ORDERER_ADDR} -C ${CHAN_ID} --name ${CC_ID} --version ${CC_VER} --sequence ${CC_SEQ} --signature-policy ${CC_EP}

    # create an FPC chaincode enclave
    ${PEER_CMD} lifecycle chaincode initEnclave -o ${ORDERER_ADDR} --peerAddresses "localhost:7051" --name ${CC_ID}
}

run_validation_test() {
  para
  say "Setup ledger"
  ledger_init
  install_chaincode
  para
  say "Run validation tests"
  go run client_app/validation.go
  para
  say "Shutdown ledger"
  ledger_shutdown
  para
  para
}

run_functions_test() {
  para
  say "Setup ledger ..."
  ledger_init
  install_chaincode
  para
  say "Run function tests ..."
  go run client_app/functions.go
  para
  say "Shutdown ledger ..."
  ledger_shutdown
  para
  para
}

run_access_control_test() {
  para
  say "Setup ledger"
  ledger_init
  install_chaincode
  para
  say "Run access control tests"
  go run client_app/access.go
  para
  say "Shutdown ledger"
  ledger_shutdown
  para
  para
}


run_performance_test() {
  para
  say "Setup ledger"
  ledger_init
  install_chaincode
  para
  say "Run performance test"
  go run client_app/performance.go
  para
  say "Shutdown ledger"
  ledger_shutdown
  para
  para
}

export CC_ID
export CHAN_ID

TEST="ALL"
if [ $# -eq 1 ]; then
  TEST=$1
fi

trap ledger_shutdown EXIT

echo "Running tests: ${TEST}"

if [ "$TEST" = "validation" ]; then
  run_validation_test
  exit 0
elif [ "$TEST" = "functions" ]; then
  run_functions_test
  exit 0
elif [ "$TEST" = "access" ]; then
  run_access_control_test
  exit 0
elif [ "$TEST" = "performance" ]; then
  run_performance_test
  exit 0
else
  echo "RUNNING ALL TESTS"
fi




stty -echo
run_functions_test
stty echo


stty -echo
run_validation_test
stty echo

stty -echo
run_access_control_test
stty echo

stty -echo
run_performance_test
stty echo



yell "tests FINISHED"

exit 0

