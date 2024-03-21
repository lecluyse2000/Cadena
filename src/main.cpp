//Author: Caden LeCluyse
//Date: 2/20/24
//File: main.cpp
//Note: I realize this could've been implemented (probably in a better way too) using std::unordered_map, I just wanted to better understand the data structure

#include <iostream>
#include <limits>
#include "hashtable.h"
#include <sodium.h>
#include <stdexcept>
#include <string>


void printMenu()
{
   std::cout << "\n1) Print all passwords\n2) Print specific password\n3) Add a password\n"
             << "4) Remove a password\n5) Change a password\n6) Exit program\nYour choice: ";
}

void clearInputStream()
{
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int recieveUserInputMenu() 
{
   std::string userInput = "";
   printMenu();

   while(!(std::cin >> userInput) || userInput.size() != 1 || !isdigit(userInput[0]) 
         || std::stoi(userInput) > 6 || std::stoi(userInput) < 1) {
      clearInputStream();
      std::cout << "\nIncorrect input! Try again.\nYour choice: "; 
   } 

   std::cout << std::endl;

   return std::stoi(userInput);
}

//Main driver code here
int main()
{
   //Initialize libsodium
   if (sodium_init() < 0) {
      std::cerr << "Failed to initialize Libsodium" << std::endl;
      return 1;
   } else {
      std::cout << "Libsodium initialized successfully!\n\n";
   }
   
   HashTable passwordManager;
   bool keepGoing = true;
   std::string userInput = "";
   std::string userInput2 = "";
   std::string userInput3 = "";
   std::cout << "Welcome to Caden's Password Manager!\n";
   const std::vector<std::string> top_websites = {
        "google.com",
        "youtube.com",
        "facebook.com",
        "baidu.com",
        "wikipedia.org",
        "yahoo.com",
        "amazon.com",
        "qq.com",
        "reddit.com",
        "taobao.com",
        "twitter.com",
        "tmall.com",
        "instagram.com",
        "live.com",
        "vk.com",
        "sohu.com",
        "jd.com",
        "360.cn",
        "weibo.com",
        "sina.com.cn",
        "yandex.ru",
        "login.tmall.com",
        "blogspot.com",
        "netflix.com",
        "linkedin.com",
        "twitch.tv",
        "google.com.hk",
        "yahoo.co.jp",
        "microsoft.com",
        "aliexpress.com",
        "microsoftonline.com",
        "office.com",
        "bing.com",
        "pinterest.com",
        "t.co",
        "mail.ru",
        "ebay.com",
        "github.com",
        "microsoftonline.com",
        "whatsapp.com",
        "imgur.com",
        "msn.com",
        "ok.ru",
        "imdb.com",
        "alibaba.com",
        "stackexchange.com",
        "aliexpress.com",
        "huanqiu.com",
        "wikia.com",
        "bilibili.com",
        "amazon.co.jp",
        "adobe.com",
        "dropbox.com",
        "naver.com",
        "google.co.jp",
        "craigslist.org",
        "salesforce.com",
        "cnn.com",
        "booking.com",
        "googleusercontent.com",
        "sogou.com",
        "bbc.co.uk",
        "aparat.com",
        "fc2.com",
        "tumblr.com",
        "t.me",
        "paypal.com",
        "google.com.br",
        "espncricinfo.com",
        "zhihu.com",
        "blogspot.in",
        "gmw.cn",
        "office365.com",
        "amazon.de",
        "amazon.in",
        "yelp.com",
        "alipay.com",
        "nih.gov",
        "nike.com",
        "huffpost.com",
        "pixnet.net",
        "google.com.mx",
        "weixin.qq.com",
        "youth.cn",
        "dailymotion.com",
        "ifeng.com",
        "google.co.uk",
        "wikimedia.org"
      };

   while(keepGoing) {
      userInput = "";
      switch(recieveUserInputMenu()) {
         case 1:
            passwordManager.printTable();
            break;
         case 2:
            std::cout << "What is the website of the login you want to get? ";

            if(!(std::cin >> userInput)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }

            {
            const login returnedLogin = passwordManager.searchTable(userInput);
            std::cout << "Website: " << userInput << "\nUsername:  " 
                      << returnedLogin.username << "\nPassword: " << returnedLogin.password
                      << '\n' << std::endl;
            }

            clearInputStream();
            break;
         case 3:
            std::cout << "What is the name of the website you want to add? ";
            
            if(!(std::cin >> userInput)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }

            clearInputStream();
            std::cout << "\nWhat is the username you would like to add? ";
            
            if(!(std::cin >> userInput2)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }

            clearInputStream();
            std::cout << "What is the password you would like to add? ";
            if(!(std::cin >> userInput3)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }

            passwordManager.insertNode(userInput, userInput2, userInput3);
            break;
         case 4:
            for(const auto& i : top_websites) {
               passwordManager.insertNode(i, "blablabla", "blablablabla");
            }
            
            break;
         case 5:
            std::cout << "What is the name of the website you want to change? ";
            
            if(!(std::cin >> userInput)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }
            
            clearInputStream();
            std::cout << "\nWhat is the password you would like to add: ";
            
            if(!(std::cin >> userInput2)) {
               std::cerr << "Failed to recieve user input, aborting program!\n";
               return 1;
            }

            clearInputStream();
            passwordManager.changePassword(userInput, userInput2);
            break;
         case 6:
            keepGoing = false;
            std::cout << "Exiting...\n\n";
            break;
      }
   }

   return 0;
}
