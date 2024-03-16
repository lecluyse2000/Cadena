//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.cpp
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure


#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include "hashtable.h"
#include <algorithm>

#define PRIME_1 57649
#define PRIME_2 86969


HashTable::HashTable(const std::size_t size)
{
   m_table.resize(size);
   m_numberBuckets = 0;
   m_vectorSize = size;

}

void HashTable::resize(const std::size_t size)
{
   m_table.resize(size);
}

bool HashTable::isEmpty() const noexcept 
{
   if(m_numberBuckets == 0)
   {
      return true;
   }

   return false;
}

int HashTable::getSize() const noexcept
{
   return(m_numberBuckets);
}

std::size_t HashTable::hashFunction(const std::string& key) const
{
   size_t hashValue = 76963;

   for(const auto& character : key) {
      hashValue = (hashValue * PRIME_1) ^ (character * PRIME_2);
   }


   return hashValue & (m_vectorSize - 1);
}

void HashTable::insertNode(const std::string& key, const std::string& value)
{
   const std::size_t hashValue = hashFunction(key);
   m_numberBuckets++;

   m_table[hashValue].emplace_back(key, value);
   std::cout << "The password was added!\n";
}

void HashTable::removeNode(const std::string& key)
{
   const std::size_t hashValue = hashFunction(key);
   bool entryFound = false;

   for(std::size_t i = 0; i < m_table[hashValue].size(); ++i) {
      if(m_table[hashValue][i].website == key) {
         entryFound = true;
         m_table[hashValue].erase(m_table[hashValue].begin() + i);
      }
   }

   if(entryFound) {
      std::cout << "The password was removed!\n";
   } else {
      std::cout << "The password was not found!\n";
   }
}

std::string HashTable::searchTable(const std::string& key) const noexcept
{
   const std::size_t hashValue = hashFunction(key);
   for(const auto& i : m_table[hashValue]) {
      if(i.website == key) {
         return i.password;
      }
   }   

   return("The login could not be found!\n");
}

void HashTable::printTable() const noexcept
{
   //This is the first lambda function I have ever implemented
   auto printWebsiteVector = [](const std::vector<login>& entry ) {
      for(const auto& theLogin : entry) {
         std::cout << "Website: " << theLogin.website << "\nPassword: " 
                   << theLogin.password << "\n\n";
      }
   };

   std::for_each(m_table.begin(), m_table.end(), printWebsiteVector);
}

void HashTable::changePassword(const std::string& key, const std::string& newPassword)
{
   const std::size_t hashValue = hashFunction(key);

   for(auto& entry : m_table[hashValue]) {
      if(entry.website == key) {
         entry.password = newPassword;
      }
   }
}
