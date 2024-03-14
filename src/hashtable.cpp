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

   std::fill(m_table.begin(), m_table.end(), login());
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

   //if(m_table[hashValue & (m_vectorSize - 1)].website != "NULL") {
     // for(std::size_t i = 0; i < m_vectorSize; ++i) {
      //   if(m_table[i].website == "NULL") {
       //     hashValue ^= i * (PRIME_2 >> 3);
        // }
         //if(m_table[hashValue & (m_vectorSize - 1)].website == "NULL") {
          //  break;
         //}
      //}
   //}

   return hashValue & (m_vectorSize - 1);
}

void HashTable::insertNode(const std::string& key, const std::string& value)
{
   std::size_t hashValue = hashFunction(key);
   m_table[hashValue].website = key;
   m_table[hashValue].password = value;
   m_numberBuckets++;

   std::cout << "The password was added!\n";
}

void HashTable::removeNode(const std::string& key)
{
   std::size_t hashValue = hashFunction(key);
   m_table[hashValue].website = "NULL";
   m_table[hashValue].password = "NULL";
   
   std::cout << "The password was removed!\n";
}

std::string HashTable::searchTable(const std::string& key) const noexcept
{
   std::size_t hashValue = hashFunction(key);
   if(m_table[hashValue].password == "NULL") {
      return "Unable to find given password!\n";
   }

   return m_table[hashValue].password;
}

void HashTable::printTable() const noexcept
{
   //This is the first lambda function I have ever implemented
   auto printWebsite = [](const login& entry) {
      if(entry.website != "NULL") {
         std::cout << "Website: " << entry.website << "\nPassword: " << entry.password << "\n\n";
      }
   };

   std::for_each(m_table.begin(), m_table.end(), printWebsite);
}
