//
// Created by manmiddle on 9/27/21.
//

#ifndef LIBRARY_SYSTEM_CUSTOMER_H
#define LIBRARY_SYSTEM_CUSTOMER_H
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <map>
#include <fstream>
#include <utility>
#include "book.h"
using namespace std;

class Customer {
private:
	int mCustomerId{};
	string mName,mAddress;
	set<int> mLoanSet , mReservationSet;

public:
	Customer();
	[[maybe_unused]] Customer(string  name, string address);
	void read(ifstream& inStream);
	[[maybe_unused]] void write(ofstream outStream)const;

	void borrowBook(int bookId);
	void reserveBook(int bookId);
	void returnBook(int bookId);
	void unReserveBook(int bookId);

	[[nodiscard]] bool hasBorrowed() const {return !mLoanSet.empty();}
	[[nodiscard]] const string& name()const {return mName;}
	[[nodiscard]] const string& address()const {return mAddress;}
	[[nodiscard]] int id() const {return mCustomerId;}

	static int MaxCustomerId;

	friend ostream& operator<<(ostream& outStream,const Customer& customer);


};


#endif//LIBRARY_SYSTEM_CUSTOMER_H
