//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.cpp
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure


#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <iostream>
#include "hashtable.h"
#include <algorithm>

#define PRIME_1 57649
#define PRIME_2 86969

HashTable::HashTable() : m_table(256)
{
   m_vectorSize = 256;
}

HashTable::~HashTable()
{
   for(auto& vec : m_table) {
       vec.clear();
   }
}

void HashTable::resize(const std::size_t size)
{
   m_table.resize(size);
}

bool HashTable::isEmpty() const noexcept 
{
   return m_table.empty();
}

const std::size_t HashTable::hashFunction(const std::string_view key) const noexcept
{
   size_t hashValue = 76963;
   std::for_each(key.begin(), key.end(), [&hashValue](const char character) {
      hashValue = (hashValue * PRIME_1) ^ (character * PRIME_2);
   });

   return hashValue & (m_vectorSize - 1);
}

void HashTable::insertNode(const std::string& key, const std::string& value)
{
   const std::size_t hashValue = hashFunction(key);
   m_table[hashValue].emplace_back(key, value);
   std::cout << "The password was added!\n";
}

void HashTable::removeNode(const std::string_view key)
{
   const std::size_t hashValue = hashFunction(key);

   for(auto itr = m_table[hashValue].begin(); itr != m_table[hashValue].end(); ++itr) {
      if(itr->website == key) {
         m_table[hashValue].erase(itr);
         std::cout << "The password was removed!\n";
         return;
      }
   }

   std::cout << "The password was not found!\n";
}

const std::string HashTable::searchTable(const std::string_view key) const noexcept
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::find_if(m_table[hashValue].begin(), m_table[hashValue].end(), [&key](const login& entry) {
      return entry.website == key;   
   });

   if(itr != m_table[hashValue].end()) {
      return (*itr).website;
   }
   return("The login could not be found!\n");
}

void HashTable::printTable() const noexcept
{
   //This is the first lambda function I have ever implemented
   std::for_each(m_table.begin(), m_table.end(), [](const std::vector<login>& entry) {
      for(const auto& theLogin : entry) {
         std::cout << "Website: " << theLogin.website << "\nPassword: " 
                   << theLogin.password  << std::endl;
      }
   });
}

void HashTable::changePassword(const std::string_view key, const std::string& newPassword)
{
   const std::size_t hashValue = hashFunction(key);

   for(auto& entry : m_table[hashValue]) {
      if(entry.website == key) {
         entry.password = newPassword;
         std::cout << "Password successfully changed!\n";
         return;
      }
   }

   std::cout << "Could not find given website!\n";
}
