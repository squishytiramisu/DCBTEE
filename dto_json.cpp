#include "dto_json.h"
#include "parson.h"

/*
    This file contains the data transfer objects for the chaincode.
    As well as the marshalling and unmarshalling functions.
*/

std::string marshal_person(person_t * person) {
   JSON_Value * root_value = json_value_init_object();
   JSON_Object * root_object = json_value_get_object(root_value);
   json_object_set_string(root_object, "id", person -> id.c_str());
   json_object_set_string(root_object, "taj", person -> taj.c_str());
   json_object_set_string(root_object, "name", person -> name.c_str());
   json_object_set_string(root_object, "birth_date", person -> birth_date.c_str());
   json_object_set_string(root_object, "death_date", person -> death_date.c_str());
   char * serialized_string = json_serialize_to_string(root_value);
   std::string out(serialized_string);
   json_free_serialized_string(serialized_string);
   json_value_free(root_value);
   return out;
}

std::string marshal_health_examination(health_examination_t * health_examination) {
   JSON_Value * root_value = json_value_init_object();
   JSON_Object * root_object = json_value_get_object(root_value);
   json_object_set_string(root_object, "id", health_examination -> id.c_str());
   json_object_set_string(root_object, "taj", health_examination -> taj.c_str());
   json_object_set_number(root_object, "systole", health_examination -> systole);
   json_object_set_number(root_object, "diastole", health_examination -> diastole);
   json_object_set_string(root_object, "date", health_examination -> date.c_str());
   char * serialized_string = json_serialize_to_string(root_value);
   std::string out(serialized_string);
   json_free_serialized_string(serialized_string);
   json_value_free(root_value);
   return out;
}

std::string marshal_life_insurance(life_insurance_t * life_insurance) {
   JSON_Value * root_value = json_value_init_object();
   JSON_Object * root_object = json_value_get_object(root_value);
   json_object_set_string(root_object, "id", life_insurance -> id.c_str());
   json_object_set_string(root_object, "taj", life_insurance -> taj.c_str());
   json_object_set_string(root_object, "from", life_insurance -> from.c_str());
   json_object_set_string(root_object, "to", life_insurance -> to.c_str());
   json_object_set_number(root_object, "cost", life_insurance -> cost);
   json_object_set_number(root_object, "payment", life_insurance -> payment);
   json_object_set_boolean(root_object, "should_pay", life_insurance -> should_pay);
   char * serialized_string = json_serialize_to_string(root_value);
   std::string out(serialized_string);
   json_free_serialized_string(serialized_string);
   json_value_free(root_value);
   return out;
}

std::string marshal_work_permit(work_permit_t * work_permit) {
   JSON_Value * root_value = json_value_init_object();
   JSON_Object * root_object = json_value_get_object(root_value);
   json_object_set_string(root_object, "id", work_permit -> id.c_str());
   json_object_set_string(root_object, "name", work_permit -> name.c_str());
   json_object_set_string(root_object, "from", work_permit -> from.c_str());
   json_object_set_string(root_object, "issuer", work_permit -> issuer.c_str());
   char * serialized_string = json_serialize_to_string(root_value);
   std::string out(serialized_string);
   json_free_serialized_string(serialized_string);
   json_value_free(root_value);
   return out;
}

int unmarshal_person(person_t * person,
   const char * json_bytes, uint32_t json_len) {
   JSON_Value * root = json_parse_string(json_bytes);
   person -> id = json_object_get_string(json_object(root), "id");
   person -> taj = json_object_get_string(json_object(root), "taj");
   person -> name = json_object_get_string(json_object(root), "name");
   person -> birth_date = json_object_get_string(json_object(root), "birth_date");
   person -> death_date = json_object_get_string(json_object(root), "death_date");
   json_value_free(root);
   return 1;
}

int unmarshal_health_examination(health_examination_t * health_examination,
   const char * json_bytes, uint32_t json_len) {
   JSON_Value * root = json_parse_string(json_bytes);
   health_examination -> id = json_object_get_string(json_object(root), "id");
   health_examination -> taj = json_object_get_string(json_object(root), "taj");
   health_examination -> systole = json_object_get_number(json_object(root), "systole");
   health_examination -> diastole = json_object_get_number(json_object(root), "diastole");
   health_examination -> date = json_object_get_string(json_object(root), "date");
   json_value_free(root);
   return 1;
}

int unmarshal_life_insurance(life_insurance_t * life_insurance,
   const char * json_bytes, uint32_t json_len) {
   JSON_Value * root = json_parse_string(json_bytes);
   life_insurance -> id = json_object_get_string(json_object(root), "id");
   life_insurance -> taj = json_object_get_string(json_object(root), "taj");
   life_insurance -> from = json_object_get_string(json_object(root), "from");
   life_insurance -> to = json_object_get_string(json_object(root), "to");
   life_insurance -> cost = json_object_get_number(json_object(root), "cost");
   life_insurance -> payment = json_object_get_number(json_object(root), "payment");
   life_insurance -> should_pay = json_object_get_boolean(json_object(root), "should_pay");
   json_value_free(root);
   return 1;
}

int unmarshal_work_permit(work_permit_t * work_permit,
   const char * json_bytes, uint32_t json_len) {
   JSON_Value * root = json_parse_string(json_bytes);
   work_permit -> id = json_object_get_string(json_object(root), "id");
   work_permit -> name = json_object_get_string(json_object(root), "name");
   work_permit -> from = json_object_get_string(json_object(root), "from");
   work_permit -> issuer = json_object_get_string(json_object(root), "issuer");
   json_value_free(root);
   return 1;
}

// data map

std::string marshal_data_map(data_map_t * data_map) {
   JSON_Value * root_value = json_value_init_object();
   JSON_Object * root_object = json_value_get_object(root_value);

   // Marshal persons map
   JSON_Value * persons_value = json_value_init_object();
   JSON_Object * persons_object = json_value_get_object(persons_value);

   for (const auto & entry: data_map -> persons) {
      JSON_Value * person_value = json_value_init_object();
      JSON_Object * person_object = json_value_get_object(person_value);

      json_object_set_string(person_object, "id", entry.second.id.c_str());
      json_object_set_string(person_object, "taj", entry.second.taj.c_str());
      json_object_set_string(person_object, "name", entry.second.name.c_str());
      json_object_set_string(person_object, "birth_date", entry.second.birth_date.c_str());
      json_object_set_string(person_object, "death_date", entry.second.death_date.c_str());

      json_object_set_value(persons_object, entry.first.c_str(), person_value);
   }

   json_object_set_value(root_object, "persons", persons_value);

   // Marshal health_examinations map
   JSON_Value * health_examinations_value = json_value_init_object();
   JSON_Object * health_examinations_object = json_value_get_object(health_examinations_value);

   for (const auto & entry: data_map -> health_examinations) {
      JSON_Value * health_exam_value = json_value_init_object();
      JSON_Object * health_exam_object = json_value_get_object(health_exam_value);

      json_object_set_string(health_exam_object, "id", entry.second.id.c_str());
      json_object_set_string(health_exam_object, "taj", entry.second.taj.c_str());
      json_object_set_number(health_exam_object, "systole", entry.second.systole);
      json_object_set_number(health_exam_object, "diastole", entry.second.diastole);
      json_object_set_string(health_exam_object, "date", entry.second.date.c_str());

      json_object_set_value(health_examinations_object, entry.first.c_str(), health_exam_value);
   }

   json_object_set_value(root_object, "health_examinations", health_examinations_value);

   // Marshal life_insurances map
   JSON_Value * life_insurances_value = json_value_init_object();
   JSON_Object * life_insurances_object = json_value_get_object(life_insurances_value);

   for (const auto & entry: data_map -> life_insurances) {
      JSON_Value * life_insurance_value = json_value_init_object();
      JSON_Object * life_insurance_object = json_value_get_object(life_insurance_value);

      json_object_set_string(life_insurance_object, "id", entry.second.id.c_str());
      json_object_set_string(life_insurance_object, "taj", entry.second.taj.c_str());
      json_object_set_string(life_insurance_object, "from", entry.second.from.c_str());
      json_object_set_string(life_insurance_object, "to", entry.second.to.c_str());
      json_object_set_number(life_insurance_object, "cost", entry.second.cost);
      json_object_set_number(life_insurance_object, "payment", entry.second.payment);
      json_object_set_boolean(life_insurance_object, "should_pay", entry.second.should_pay);

      json_object_set_value(life_insurances_object, entry.first.c_str(), life_insurance_value);
   }

   json_object_set_value(root_object, "life_insurances", life_insurances_value);

   // Marshal work_permits map
   JSON_Value * work_permits_value = json_value_init_object();
   JSON_Object * work_permits_object = json_value_get_object(work_permits_value);

   for (const auto & entry: data_map -> work_permits) {
      JSON_Value * work_permit_value = json_value_init_object();
      JSON_Object * work_permit_object = json_value_get_object(work_permit_value);

      json_object_set_string(work_permit_object, "id", entry.second.id.c_str());
      json_object_set_string(work_permit_object, "name", entry.second.name.c_str());
      json_object_set_string(work_permit_object, "from", entry.second.from.c_str());
      json_object_set_string(work_permit_object, "issuer", entry.second.issuer.c_str());

      json_object_set_value(work_permits_object, entry.first.c_str(), work_permit_value);
   }

   json_object_set_value(root_object, "work_permits", work_permits_value);

   char * json_str = json_serialize_to_string_pretty(root_value);
   std::string result(json_str);

   json_value_free(root_value);
   return result;
}

// Function to unmarshal a JSON string into a data_map_t object
int unmarshal_data_map(data_map_t * data_map,
   const char * json_bytes, uint32_t json_len) {

   JSON_Value * root_value = json_parse_string(json_bytes);
   JSON_Object * root_object = json_value_get_object(root_value);

   // Unmarshal persons map
   JSON_Object * persons_object = json_object_get_object(root_object, "persons");
   size_t count = json_object_get_count(persons_object);

   for (size_t i = 0; i < count; ++i) {
      const char * key = json_object_get_name(persons_object, i);
      JSON_Object * person_object = json_object_get_object(persons_object, key);
      person_t person;

      person.id = json_object_get_string(person_object, "id");
      person.taj = json_object_get_string(person_object, "taj");
      person.name = json_object_get_string(person_object, "name");
      person.birth_date = json_object_get_string(person_object, "birth_date");
      person.death_date = json_object_get_string(person_object, "death_date");

      data_map -> persons[key] = person;
   }

   // Unmarshal health_examinations map
   JSON_Object * health_examinations_object = json_object_get_object(root_object, "health_examinations");
   count = json_object_get_count(health_examinations_object);

   for (size_t i = 0; i < count; ++i) {
      const char * key = json_object_get_name(health_examinations_object, i);
      JSON_Object * health_exam_object = json_object_get_object(health_examinations_object, key);
      health_examination_t health_exam;

      health_exam.id = json_object_get_string(health_exam_object, "id");
      health_exam.taj = json_object_get_string(health_exam_object, "taj");
      health_exam.systole = (int) json_object_get_number(health_exam_object, "systole");
      health_exam.diastole = (int) json_object_get_number(health_exam_object, "diastole");
      health_exam.date = json_object_get_string(health_exam_object, "date");

      data_map -> health_examinations[key] = health_exam;
   }

   // Unmarshal life_insurances map
   JSON_Object * life_insurances_object = json_object_get_object(root_object, "life_insurances");
   count = json_object_get_count(life_insurances_object);

   for (size_t i = 0; i < count; ++i) {
      const char * key = json_object_get_name(life_insurances_object, i);
      JSON_Object * life_insurance_object = json_object_get_object(life_insurances_object, key);
      life_insurance_t life_insurance;

      life_insurance.id = json_object_get_string(life_insurance_object, "id");
      life_insurance.taj = json_object_get_string(life_insurance_object, "taj");
      life_insurance.from = json_object_get_string(life_insurance_object, "from");
      life_insurance.to = json_object_get_string(life_insurance_object, "to");
      life_insurance.cost = (int) json_object_get_number(life_insurance_object, "cost");
      life_insurance.payment = (int) json_object_get_number(life_insurance_object, "payment");
      life_insurance.should_pay = json_object_get_boolean(life_insurance_object, "should_pay");

      data_map -> life_insurances[key] = life_insurance;
   }

   // Unmarshal work_permits map
   JSON_Object * work_permits_object = json_object_get_object(root_object, "work_permits");
   count = json_object_get_count(work_permits_object);

   for (size_t i = 0; i < count; ++i) {
      const char * key = json_object_get_name(work_permits_object, i);
      JSON_Object * work_permit_object = json_object_get_object(work_permits_object, key);
      work_permit_t work_permit;

      work_permit.id = json_object_get_string(work_permit_object, "id");
      work_permit.name = json_object_get_string(work_permit_object, "name");
      work_permit.from = json_object_get_string(work_permit_object, "from");
      work_permit.issuer = json_object_get_string(work_permit_object, "issuer");

      data_map -> work_permits[key] = work_permit;
   }

   json_value_free(root_value);
   return 1;
}