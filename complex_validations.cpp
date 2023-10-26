#include "validate.h"


/*
This file contains complex, stateful validations for FPC events.
*/

bool validPersonBorn(std::string id, std::string taj, std::string name, std::string birth_date, shim_ctx_ptr_t ctx) {
   if (!isValidTaj(taj) ||
      !isValidId(id) ||
      !isValidName(name) ||
      !isValidBirthDate(birth_date) ||
      idExists(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validIssueLifeInsurance(std::string id, std::string taj, std::string from, std::string to, int cost, int payment, shim_ctx_ptr_t ctx) {

   if (!isValidTaj(taj) ||
      !isValidId(id) ||
      !isValidDate(from) ||
      !isValidDate(to) ||
      !isValidCost(cost) ||
      !isValidPayment(payment) ||
      !idExists(id, ctx) ||
      !isAlive(id, ctx) ||
      !isHealthy(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validIssueHealthExamination(std::string id, std::string taj, std::string examination_date, int systole, int diastole, shim_ctx_ptr_t ctx) {

   if (!isValidTaj(taj) ||
      !isValidId(id) ||
      !isValidDate(examination_date) ||
      !idExists(id, ctx) ||
      !isAlive(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validIssueWorkPermit(std::string id, std::string name, std::string from, std::string issuer, shim_ctx_ptr_t ctx) {

   if (!isValidId(id) ||
      !isValidName(name) ||
      !isValidDate(from) ||
      !idExists(id, ctx) ||
      !isAlive(id, ctx) ||
      !hasLifeInsurance(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validPersonDie(std::string id, shim_ctx_ptr_t ctx) {

   if (!isValidId(id) ||
      !idExists(id, ctx) ||
      !isAlive(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validPayRequest(std::string id, shim_ctx_ptr_t ctx) {

   if (!isValidId(id) ||
      !idExists(id, ctx) ||
      isAlive(id, ctx) ||
      !hasLifeInsurance(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validRevokeWorkPermit(std::string id, shim_ctx_ptr_t ctx) {

   if (!isValidId(id) ||
      !hasWorkPermit(id, ctx)
   ) {
      return false;
   }

   return true;
}

bool validCanWork(std::string id, shim_ctx_ptr_t ctx) {

   if (!isValidId(id) ||
      !idExists(id, ctx)
   ) {
      return false;
   }

   return true;
}