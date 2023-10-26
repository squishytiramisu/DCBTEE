
#pragma once


#include <iostream>
#include <string>
#include "shim.h"

template <typename T>
bool isNotNull(const T* ptr);

bool isEmpty(const std::string& str);

bool containsOnlyNumbers(const std::string& str);

bool hasLength(const std::string& str, size_t length);

bool isValidTaj(const std::string& str);

bool isValidName(const std::string& str);

bool isValidBirthDate(const std::string& str);

bool isFutureDate(const std::string& str);

bool containsOnlyLetters(const std::string& str);

bool isShorterThan(const std::string& str, size_t length);

bool hasNoSpecialCharacters(const std::string& str);

bool isValidId(const std::string& str);

bool isValidDate(const std::string& str);

bool isValidCost(int cost);

bool isValidPayment(int payment);


//CTX predicates
bool tajExists(const std::string& str, shim_ctx_ptr_t ctx);

bool idExists(const std::string& str, shim_ctx_ptr_t ctx);

bool isAlive(const std::string& str, shim_ctx_ptr_t ctx);

bool hasLifeInsurance(const std::string& taj, shim_ctx_ptr_t ctx);

bool isHealthy(const std::string& id, shim_ctx_ptr_t ctx);

bool hasWorkPermit(const std::string& id, shim_ctx_ptr_t ctx);