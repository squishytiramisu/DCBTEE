package main

import (
	"os"
    "strings"
	fpc "github.com/hyperledger/fabric-private-chaincode/client_sdk/go/pkg/gateway"
	"github.com/hyperledger/fabric-private-chaincode/integration/client_sdk/go/utils"
	"github.com/hyperledger/fabric/common/flogging"
)

var logger = flogging.MustGetLogger("VALIDATION")

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
            Args: []string{"PersonBorn:Org1;PersonDie:Org1;IssueHealthExamination:Org1;IssueLifeInsurance:Org1;IssueWorkPermit:Org1;hasWorkPermit:Org1;initEncryption:Org1;","Org1"},
            Desc: "transaction to initialize access control",
        },
        {
            Name: "initEncryption",
            Args: []string{"696045", "1445688", "26681", "2614739", "1391988","Org1"},
            Desc: "transaction to initialize encryption parameters",
        },
        {
            Name: "PersonBorn",
            Args: []string{"123123123", "123123123", "Johnatan Merquic", "12","Org1"},
			Desc: "transaction to create invalid person: should fail",
        },
        {
            Name: "PersonBorn",
            Args: []string{"123123000", "123123000", "Alice Monoro", "20001112","Org1"},
			Desc: "transaction to create valid person (Alice): should succeed",
        },
        {
            Name: "PersonBorn",
            Args: []string{"123123111", "123123111", "Bob Monoro", "20021112","Org1"},
			Desc: "transaction to create valid person (Bob): should succeed",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123123", "Alice Monoro", "20201010", "WorkPermitAgency","Org1"},
			Desc: "transaction to create work permit for invalid person",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123000", "Alice Monoro", "20201010", "WorkPermitAgency","Org1"},
			Desc: "transaction to create work permit for valid person (Alice) should fail, no life insurance",
		},
		{
            Name: "IssueLifeInsurance",
            Args: []string{"123123123", "123123123", "20201010", "20301010","100", "200","Org1"},
			Desc: "transaction to create life insurance for invalid person should fail",
		},
		{
            Name: "IssueLifeInsurance",
            Args: []string{"123123000", "123123000", "20201010", "20301010","100", "200","Org1"},
			Desc: "transaction to create life insurance for valid person (Alice) should fail, no health record",
		},
		{
            Name: "IssueHealthExamination",
            Args: []string{"123123123", "123123123", "20201010", "120", "80","Org1"},
			Desc: "transaction to create health record for invalid person should fail",
		},
		{
            Name: "IssueHealthExamination",
            Args: []string{"123123000", "123123000", "20201010", "120", "80","Org1"},
			Desc: "transaction to create health record for valid person (Alice) should succeed",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123000", "Alice Monoro", "20201010", "WorkPermitAgency","Org1"},
			Desc: "transaction to create work permit for valid person (Alice) should fail, no life insurance",
        },
		{
            Name: "IssueLifeInsurance",
            Args: []string{"123123000", "123123000", "20201010", "20301010","100", "200","Org1"},
			Desc: "transaction to create life insurance for valid person (Alice) should succeed",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123000", "Alice Monoro", "20201010", "WorkPermitAgency","Org1"},
			Desc: "transaction to create work permit for valid person (Alice) should succeed now",
        },
		{
            Name: "IssueHealthExamination",
            Args: []string{"123123111", "123123111", "20201010", "210", "100","Org1"},
			Desc: "transaction to create health record (unhealty) for valid person (Bob) should succeed",
        },
		{
            Name: "IssueWorkPermit",
            Args: []string{"123123111", "Bob Monoro", "20201010", "WorkPermitAgency","Org1"},
			Desc: "transaction to create work permit for valid person (Bob) should fail, no life insurance",
        },
		{
            Name: "IssueLifeInsurance",
            Args: []string{"123123111", "123123111", "20201010", "20301010","100", "200","Org1"},
			Desc: "transaction to create work permit for valid person (Bob) should fail, not healthy",
        },
		{
            Name: "PersonDie",
            Args: []string{"123123123","Org1"},
			Desc: "transaction to invalid person dies, should fail",
        },
		{
            Name: "PersonDie",
            Args: []string{"123123111","Org1"},
			Desc: "transaction to valid person (Bob) dies, should succeed",
        },
		{
            Name: "IssueHealthExamination",
            Args: []string{"123123111", "123123111", "20201010", "120", "180","Org1"},
			Desc: "transaction to create health record (healthy) for valid person (Bob) should fail, dead",
        },

    }
    logger.Infof("Public encryption parameters: Threshold(k/n): %v/%v Group generators(G/G_hat): %v/%v, Group order: %v, Modulus: %v, Public Key: %v", params.k, params.n, params.G,params.GH ,params.Q, params.P, params.Y)

    
    // Iterate through the transactions and invoke them
    for _, tx := range transactions {
        result, err1 := contract.SubmitTransaction(tx.Name, tx.Args...)
		logger.Infof("Invoking %s %s ", tx.Name, tx.Desc)
        if err1 != nil {
           logger.Fatalf("Failed to invoke transaction: " + err1.Error())
        }

        if (strings.Contains(string(result), "ERROR") && !strings.Contains(string(tx.Desc), "succeed")) {
            logger.Infof("Transaction failed: %s", string(result))
        }else{
            logger.Infof("Result: %s", string(result))
        }

    }


	
}