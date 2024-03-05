//Author: Caden LeCluyse
//Date: 2/19/24
//File: hashtable.h
//Purpose: Implement a password manager in c++ using a hash table, so I can better understand the data structure

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <utility>
#include <string>

class HashTable
{
    private:
        int m_numberBuckets;
        std::size_t m_vectorSize;
        std::vector<std::pair<std::string, std::string>> m_table; 
        
    public:
      HashTable(std::size_t size);
      void resize(std::size_t size);
      bool isEmpty() const noexcept;
      int getSize() const noexcept;
      std::size_t hashFunction(const std::string& key) const;
      void insertNode(const std::string& key, const std::string& value);
      void removeNode(const std::string& key);
      std::string searchTable(const std::string& key) const noexcept;
      void printTable() const noexcept;
};

#endif
