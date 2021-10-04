//
// Created by manmiddle on 9/27/21.
//

#ifndef LIBRARY_SYSTEM_LIBRARY_H
#define LIBRARY_SYSTEM_LIBRARY_H
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <map>
#include <fstream>
#include <algorithm>
#include <utility>
#include "book.h"
#include "customer.h"

using namespace std;
/**
 * A prototype for Book and Customer Class .
 * it help us to call and use it inside the library class without trouble .
 */
class Book;
class Customer;

class Library {
public:
	Library();
public:
    static map<int,Book> sBookMap;
    static map<int,Customer> sCustomerMap;

private:
	[[maybe_unused]] static string sBinaryPath;
	[[maybe_unused]]  static bool lookUpBook(const string& author , const string& title, [[maybe_unused]] Book *bookPtr=nullptr);
	[[maybe_unused]] static bool lookUpCustomer(const string& name , const string& address, [[maybe_unused]] Customer *customerPtr=nullptr);
	 static void addBook();
	 static void deleteBook();
	 static void borrowBook();
	 static void listBooks();
	 static void addCustomer();
	 static void deleteCustomer();
	 static void listCustomers();
	 static void reserveBook();
	 static void returnBook();
	 static void load();
	 static void save();
};


#endif//LIBRARY_SYSTEM_LIBRARY_H
