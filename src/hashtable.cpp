// Author: Caden LeCluyse
// Date: 2/19/24
// File: hashtable.cpp
// Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure

#include "hashtable.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

static constexpr int primeOne{ 57'649 };
static constexpr int primeTwo{ 86'969 };

HashTable::~HashTable()
{
   std::ranges::for_each(m_table, [](std::vector<login>& entry) {
      entry.clear();
   });
}

bool HashTable::isEmpty() const noexcept { return m_table.empty(); }

[[nodiscard]] constexpr std::size_t HashTable::hashFunction(std::string_view key) const noexcept
{
   std::size_t hashValue = 76'963;
   std::ranges::for_each(key, [&hashValue](const char character) {
      hashValue = (hashValue * primeOne) ^ (character * primeTwo);
   });

   return hashValue & (m_table.size() - 1);
}

bool HashTable::verifyEntry(std::string_view key) const noexcept
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [&key](const login& entry) {
      return entry.website == key;
   });

   return itr != m_table[hashValue].end();
}

void HashTable::resize()
{
   m_table.resize(m_table.size() * 2);
   std::vector<std::vector<login>> newHashTable(m_table.size());

   std::ranges::for_each(m_table, [&newHashTable, this](const std::vector<login>& vector) {
      std::ranges::for_each(vector, [&newHashTable, this](const login& entry) {
         const std::size_t newHash = this->hashFunction(entry.website);
         newHashTable[newHash].push_back(entry);
      });
   });

   m_table.swap(newHashTable);
}

void HashTable::insertNode(std::string& key, std::string& username, std::string& password)
{
   // 717/1024 gives a load factor of .7, plus idk why anyone would need more than 200 logins
   // But I'll let them have upto 717, I honestly wasn't going to implement resizing but figured I probably should
   if (m_numberLogins + 1 == 717) {
      throw(std::runtime_error("MAX number of logins reached!\n"));
   }
   const std::size_t hashValue = hashFunction(key);
   m_table[hashValue].emplace_back(std::move(key), std::move(username), std::move(password));
   m_numberLogins++;

   if (static_cast<double>(m_numberLogins) / m_table.size() >= 0.7) {
      resize();
   }
}

void HashTable::removeNode(std::string_view key)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   m_table[hashValue].erase(itr);
   m_numberLogins--;
}

login HashTable::searchTable(std::string_view key) const noexcept
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   return *itr;
}

void HashTable::printTable() const noexcept
{
   // This is the first lambda function I have ever implemented
   std::ranges::for_each(m_table, [](const auto& vector) {
      std::ranges::for_each(vector, [](const login& t_login) {
         const auto [website, username, password] = t_login;
         std::cout << "\nWebsite: " << website << "\nUsername: " << username << "\nPassword: " << password << '\n'
                   << std::endl;
      });
   });
}

void HashTable::changeUsername(std::string_view key, std::string&& newUsername)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   itr->username = newUsername;
}

void HashTable::changePassword(std::string_view key, std::string&& newPassword)
{
   const std::size_t hashValue = hashFunction(key);
   const auto itr = std::ranges::find_if(m_table[hashValue], [key](const login& entry) {
      return entry.website == key;
   });

   itr->password = newPassword;
}
