package main

import (
	"os"
    "strings"
	fpc "github.com/hyperledger/fabric-private-chaincode/client_sdk/go/pkg/gateway"
	"github.com/hyperledger/fabric-private-chaincode/integration/client_sdk/go/utils"
	"github.com/hyperledger/fabric/common/flogging"
)

var logger = flogging.MustGetLogger("AccessControl")

func main() {
	ccID := os.Getenv("CC_ID")
	logger.Infof("Use Chaincode ID: %v", ccID)

	channelID := os.Getenv("CHAN_ID")
	logger.Infof("Use channel: %v", channelID)

	network, _ := utils.SetupNetwork(channelID)
	contract := fpc.GetContract(network, ccID)

    params := struct{
        k int
        n int
        G int
        GH int
        Q int
        P int
        Y int
    }{
        k: 3,
        n: 5,
        G: 696045,
        GH: 1445688,
        Q: 26681,
        P: 2614739,
        Y: 1391988,
    }

	transactions := []struct {
        Name string
        Args []string
		Desc string
    }{
        {
            Name: "initAccessControl",
            Args: []string{"PersonBorn:Org1,Org2;PersonDie:Org1;IssueHealthExamination:Org1;IssueLifeInsurance:Org1;IssueWorkPermit:Org1;hasWorkPermit:Org1;initEncryption:Org1;","Org1"},
            Desc: "transaction to initialize access control: should succeed",
        },
        {
            Name: "initEncryption",
            Args: []string{"696045", "1445688", "26681", "2614739", "1391988","Org3"},
            Desc: "transaction to initialize encryption parameters: should fail, insufficent rights",
        },
        {
            Name: "PersonBorn",
            Args: []string{"123123000", "123123000", "Alice Monoro", "20001112","Org3"},
			Desc: "transaction to create person (Alice): should fail, insufficent rights",
        },
		{
            Name: "IssueHealthExamination",
            Args: []string{"123123000", "123123000", "20201010", "120", "80","Org3"},
			Desc: "transaction to create health record for (Alice): should fail, insufficent rights",
        },
		{
            Name: "IssueLifeInsurance",
            Args: []string{"123123000", "123123000", "20201010", "20301010","100", "200","Org3"},
			Desc: "transaction to create life insurance for (Alice): should fail, insufficent rights",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123000", "Alice Monoro", "20201010", "WorkPermitAgency","Org3"},
			Desc: "transaction to create work permit for (Alice): should fail, insufficent rights",
        },
        {
            Name: "hasWorkPermit",
            Args: []string{"123123000","Org3"},
            Desc: "transaction to check if (Alice) has work permit: should fail, insufficent rights",
        },
		{
            Name: "PersonDie",
            Args: []string{"123123000","Org3"},
			Desc: "transaction to register (Alice) as dead: should fail, insufficent rights",
        },
        {
            Name: "divider",
            Desc: "Next transactions should succeed, because Org1 has access to all functions",
        },
        {
            Name: "initEncryption",
            Args: []string{"696045", "1445688", "26681", "2614739", "1391988","Org1"},
            Desc: "transaction to initialize encryption parameters: should succeed",
        },
        {
            Name: "PersonBorn",
            Args: []string{"123123000", "123123000", "Alice Monoro", "20001112","Org1"},
			Desc: "transaction to create person (Alice): should succeed",
        },
		{
            Name: "IssueHealthExamination",
            Args: []string{"123123000", "123123000", "20201010", "120", "80","Org1"},
			Desc: "transaction to create health record for (Alice): should succeed",
        },
		{
            Name: "IssueLifeInsurance",
            Args: []string{"123123000", "123123000", "20201010", "20301010","100", "200","Org1"},
			Desc: "transaction to create life insurance for (Alice): should succeed",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123000", "Alice Monoro", "20201010", "WorkPermitAgency","Org1"},
			Desc: "transaction to create work permit for (Alice): should succeed",
        },
        {
            Name: "hasWorkPermit",
            Args: []string{"123123000","Org1"},
            Desc: "transaction to check if (Alice) has work permit: should succeed",
        },
		{
            Name: "PersonDie",
            Args: []string{"123123000","Org1"},
			Desc: "transaction to register (Alice) as dead: should succeed",
        },

    }
    
    logger.Infof("Public encryption parameters: Threshold(k/n): %v/%v Group generators(G/G_hat): %v/%v, Group order: %v, Modulus: %v, Public Key: %v", params.k, params.n, params.G,params.GH ,params.Q, params.P, params.Y)
    

    // Iterate through the transactions and invoke them
    for _, tx := range transactions {

        if(strings.Contains(string(tx.Name), "divider")){
            logger.Infof("------------------------------------------------------")
            logger.Infof("%s", tx.Desc)
            logger.Infof("------------------------------------------------------")
            continue
        }

        result, err1 := contract.SubmitTransaction(tx.Name, tx.Args...)
		logger.Infof("Invoking %s %s ", tx.Name, tx.Desc)
        if err1 != nil {
           logger.Fatalf("Something went wrong: " + err1.Error())
        }

        if (strings.Contains(string(tx.Desc), "succeed")) {
            logger.Infof("Result: %s", string(result))
        }else{
            logger.Infof("Transaction failed: %s", string(result))
        }

    }


	
}