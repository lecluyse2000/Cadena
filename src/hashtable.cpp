//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.cpp
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure


#include <ranges>
#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <iostream>
#include "hashtable.h"
#include <algorithm>

#define PRIME_1 57649
#define PRIME_2 86969

HashTable::HashTable() : m_table(256) {}

HashTable::~HashTable()
{
   std::ranges::for_each(m_table, [](std::vector<login>& entry) {
      entry.clear();
   }); 
}

bool HashTable::isEmpty() const noexcept 
{
   return m_table.empty();
}

[[nodiscard]] constexpr std::size_t HashTable::hashFunction(std::string_view key) const noexcept
{
   size_t hashValue = 76963;
   std::ranges::for_each(key, [&hashValue](const char character) {
      hashValue = (hashValue * PRIME_1) ^ (character * PRIME_2);
   });

   return hashValue & (m_vectorSize - 1);
}

void HashTable::resize()
{
   m_vectorSize *= 2;
   m_table.resize(m_vectorSize);
   std::vector<std::vector<login>> newHashTable(m_vectorSize); 

   std::ranges::for_each(m_table, [&newHashTable, this](const std::vector<login>& vector) {
      std::ranges::for_each(vector, [&newHashTable, this](const login& entry) {
         const std::size_t newHash = this->hashFunction(entry.website);
         newHashTable[newHash].push_back(entry);
      });
   });

   m_table.swap(newHashTable);
}

void HashTable::insertNode(std::string& key, std::string& username, std::string& value)
{
   //717/1024 gives a load factor of .7, plus idk why anyone would need more than 200 logins
   //But I'll let them have upto 717, I honestly wasn't going to implement resizing but figured I probably should
   if(m_numberLogins + 1 == 717) {
      std::cerr << "MAX number of logins reached! Why do you have so many logins?\n";
      return;
   }
   const std::size_t hashValue = hashFunction(key);
   m_table[hashValue].emplace_back(std::move(key), std::move(username), std::move(value));
   m_numberLogins++;

   if(static_cast<double>(m_numberLogins) / m_vectorSize >= 0.7) {
      resize();
   }
}

bool HashTable::removeNode(std::string_view key)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
         return entry.website == key;
   });

   if(itr != m_table[hashValue].end()) {
      m_table[hashValue].erase(itr);
      m_numberLogins--;
      return true;
   } 
   return false;
}

login HashTable::searchTable(std::string_view key) const noexcept
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;   
   });

   if(itr != m_table[hashValue].end()) {
      return *itr;
   }
   return{"NULL", "NULL", "NULL"};
}

void HashTable::printTable() const noexcept
{
   //This is the first lambda function I have ever implemented
   std::ranges::for_each(m_table, [](const std::vector<login>& entry) {
      std::ranges::for_each(entry, [](const login& t_login) {
         std::cout << "Website: " << t_login.website << "\nUsername: " 
                   << t_login.username  << "\nPassword: " << t_login.password << '\n' 
                   << std::endl;
      });
   });
}

bool HashTable::changeUsername(std::string_view key, std::string&& newUsername)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   if(itr != m_table[hashValue].end()) {
      itr->username = newUsername;
      return true;
   } 
   return false;
}

bool HashTable::changePassword(std::string_view key, std::string&& newPassword)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   if(itr != m_table[hashValue].end()) {
      itr->password = newPassword;
      return true;
   } 
   return false;
}
