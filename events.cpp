#include "events.h"


std::string personBorn(shim_ctx_ptr_t ctx, std::string id, std::string taj, std::string name, std::string birth_date) {

   //Validate request
   if (!validPersonBorn(id, taj, name, birth_date, ctx)) {
      return "ERROR: Invalid request";
   }

   // create new person
   person_t new_person;
   new_person.id = (char * ) id.c_str();
   new_person.taj = (char * ) taj.c_str();
   new_person.name = (char * ) name.c_str();
   new_person.birth_date = (char * ) birth_date.c_str();
   new_person.death_date = "";

   return putPerson(new_person, ctx);
}

std::string personDie(shim_ctx_ptr_t ctx, std::string id) {

   if (!validPersonDie(id, ctx)) {
      return "ERROR: Person does not exist or already dead";
   }
   person_t the_person = getPerson((id).c_str(), ctx);
   the_person.death_date = "TODO";
   return putPerson(the_person, ctx);
}

std::string issueHealthExamination(shim_ctx_ptr_t ctx, std::string id, std::string taj, std::string examination_date, int systole, int diastole) {

   if (!validIssueHealthExamination(id, taj, examination_date, systole, diastole, ctx)) {
      return "ERROR: Invalid request";
   }

   health_examination_t new_examination;
   new_examination.date = (char * ) examination_date.c_str();
   new_examination.systole = systole;
   new_examination.diastole = diastole;
   new_examination.taj = (char * ) taj.c_str();
   new_examination.id = (char * ) id.c_str();

   return putHealthExamination(new_examination, ctx);
}

std::string issueLifeInsurance(shim_ctx_ptr_t ctx, std::string id, std::string taj, std::string from, std::string to, int cost, int payment, bool should_pay) {

   if (!validIssueLifeInsurance(id, taj, from, to, cost, payment, ctx)) {
      return "ERROR: Invalid request";
   }

   life_insurance_t new_life_insurance;
   new_life_insurance.id = (char * ) id.c_str();
   new_life_insurance.taj = (char * ) taj.c_str();
   new_life_insurance.from = (char * ) from.c_str();
   new_life_insurance.to = (char * ) to.c_str();
   new_life_insurance.cost = cost;
   new_life_insurance.payment = payment;
   new_life_insurance.should_pay = should_pay;

   return putLifeInsurance(new_life_insurance, ctx);
}

std::string issueWorkPermit(shim_ctx_ptr_t ctx, std::string id, std::string name, std::string from, std::string issuer) {

   if (!validIssueWorkPermit(id, name, from, issuer, ctx)) {
      return "ERROR: Person does not exist or is not eligible for work permit";
   }

   work_permit_t new_work_permit;
   new_work_permit.id = (char * ) id.c_str();
   new_work_permit.name = (char * ) name.c_str();
   new_work_permit.from = (char * ) from.c_str();
   new_work_permit.issuer = (char * ) issuer.c_str();

   return putWorkPermit(new_work_permit, ctx);
}

std::string canWork(shim_ctx_ptr_t ctx, std::string id) {
   if (!validCanWork(id, ctx)) {
      return "ERROR: Person does not exist";
   }

   if (hasWorkPermit(id, ctx)) {
      return "has work permit";
   }
   return "has no permit";
}

std::string onChainEncrypt(std::string input, shim_ctx_ptr_t ctx) {

   //Get parameters
   uint32_t g_len;
   uint32_t g_hat_len;
   uint32_t q_len;
   uint32_t p_len;
   uint32_t y_len;
   uint8_t g[MAX_VALUE_SIZE];
   uint8_t g_hat[MAX_VALUE_SIZE];
   uint8_t q[MAX_VALUE_SIZE];
   uint8_t p[MAX_VALUE_SIZE];
   uint8_t y[MAX_VALUE_SIZE];

   get_public_state("g", g, sizeof(g), & g_len, ctx);
   get_public_state("g_hat", g_hat, sizeof(g_hat), & g_hat_len, ctx);
   get_public_state("q", q, sizeof(q), & q_len, ctx);
   get_public_state("p", p, sizeof(p), & p_len, ctx);
   get_public_state("y", y, sizeof(y), & y_len, ctx);

   if (g_len == 0 || g_hat_len == 0 || q_len == 0 || p_len == 0 || y_len == 0) {
      return "ERROR: Encryption parameters not initialized";
   }

   BIGNUM * g_bn = BN_new();
   BIGNUM * g_hat_bn = BN_new();
   BIGNUM * q_bn = BN_new();
   BIGNUM * p_bn = BN_new();
   BIGNUM * y_bn = BN_new();
   BIGNUM * m_bn = BN_new();

   BN_dec2bn( & g_bn, (const char * ) g);
   BN_dec2bn( & g_hat_bn, (const char * ) g_hat);
   BN_dec2bn( & q_bn, (const char * ) q);
   BN_dec2bn( & p_bn, (const char * ) p);
   BN_dec2bn( & y_bn, (const char * ) y);

   //Encrypted data
   return elgamal_encrypt(g_bn, g_hat_bn, q_bn, p_bn, y_bn, input);
}