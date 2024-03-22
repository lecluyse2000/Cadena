#include <memory>
#include <array>
#include <utility>
#include <string>
#include "HashTable.h"


bool HashTable::isEmpty() const
{
    if(numberBuckets == 0)
    {
        return true;
    }
    return false;
}

std::size_t HashTable::hashFunction(const std::string& key, std::size_t arraySize)
{
    size_t hashValue = 0;
    for(char character : key)
    {
        hashValue = (hashValue << 5) + character;
    }
    return hashValue & (arraySize - 1);
}

void insertNode(std::pair<std::string, std::string> Node)
{
    std::size_t hashValue = hashFunction(Node.first, Node.second);
    if(m_table[hashValue]) 


}

