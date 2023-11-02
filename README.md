


# DCBTEE Demo

## Fulfilling Data Comprehensibility on Blockchain with Trusted Execution Environments

This is a prototype implementation of protocol, should not be used in production, has not been audited by external security audits.

## Boostrapping
1. Install Hyperledger Fabric FPC docker development environment
2. Place the current github repository into to path: $FPC_PATH/samples/chaincodes/
3. Run make clean && make ( With the docker development environment)
4. Invoke testing script by calling bash ./test.sh in this repository


### License notice

Platform and framework, tools:
Hyperledger Fabric Private Chaincode: https://github.com/hyperledger/fabric-private-chaincode

Threshold ElGamal (partial) implementation based on the following paper:
    Securing Threshold Cryptosystems against Chosen Ciphertext Attack

As well as the following implementations:
- a textbook ElGamal implementation by Christian Cachin
- https://github.com/noahschmid/threshold_elgamal_python
