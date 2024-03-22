#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include <array>
#include <utility>
#include <string>

class HashTable
{
    private:
        static std::size_t arraySize = 8;
        static int numberBuckets = 0;
        auto m_table = std::make_unique<std::array<std::pair<std::string, std::string>, arraySize>>();
        
    public:
        bool isEmpty() const;
        std::size_t hashFunction(const std::string& key, std::size_t arraySize);
        void insertNode(std::pair<std::string, std::string>);
        void removeNode(const std::string key);
        std::string searchTable(const std::string key) const;
        void printTable() const;
}


#endif
