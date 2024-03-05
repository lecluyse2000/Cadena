//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.cpp
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure


#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include "hashtable.h"

HashTable::HashTable(std::size_t size)
{
   m_table.resize(size);
   m_numberBuckets = 0;
   m_vectorSize = size;
   for(auto i = m_table.begin(); i != m_table.end(); ++i) {
      *i = std::make_pair("NULL", "NULL");
   }
}

void HashTable::resize(std::size_t size)
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
   int primeNumber = 57649;
   size_t hashValue = 0;
   for(const auto& character : key) {
      hashValue = (hashValue * primeNumber) + character;
   }
   return hashValue & (m_vectorSize - 1);
}

void HashTable::insertNode(const std::string& key, const std::string& value)
{
   bool keyExists = false;
   std::size_t hashValue = hashFunction(key);
   if(m_table[hashValue].first != "NULL" && m_table[hashValue].first != key) {
      std::cout << "Oh no! We have a collision!\n";
      keyExists = true;
   }
   if(!keyExists) {
      m_table[hashValue].first = key;
      m_table[hashValue].second = value;
      m_numberBuckets++;
      std::cout << "The password was added!\n";
   }
}

void HashTable::removeNode(const std::string& key)
{
   std::size_t hashValue = hashFunction(key);
   m_table[hashValue].first = "NULL";
   m_table[hashValue].second = "NULL";
   std::cout << "The password was removed!\n";
}

std::string HashTable::searchTable(const std::string& key) const noexcept
{
   std::size_t hashValue = hashFunction(key);
   if(m_table[hashValue].second == "NULL") {
      return "Unable to find given password!\n";
   }
   return m_table[hashValue].second;
}

void HashTable::printTable() const noexcept
{
   for(const auto& i : m_table) {
      if(i.first != "NULL") {
         std::cout << "Website: " << i.first << "\nPassword: " << i.second << "\n\n";
      }
   }
}
