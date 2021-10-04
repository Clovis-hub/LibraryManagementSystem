//
// Created by manmiddle on 9/27/21.
//

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <map>
#include <fstream>
#include <utility>
#include "customer.h"
#include "library.h"

#include <ostream>

using namespace std;
class Book {
private :
	bool mBorrowed = false;
	int mBookId{} , mCustomerId{};
	string mAuthor, mTitle;
	list<int>mReservationList;
public :
	Book();
	Book(string  mAuthor, string  mTitle);
	const string& author()const {return mAuthor;}
	const string& title()const {return mTitle;}
	void read(ifstream&  inStream);
	void write(ofstream& outStream) const;
	void borrowBook(int customerId);
	unsigned int reserveBook(int customerId);
	void unReserveBook(int customerId);
	void returnBook();
	int bookId()const {return mBookId;}
	bool borrowed()const {return mBorrowed;}
	int customerId() const {return mCustomerId;}
	list<int>& reservationList(){return mReservationList;}
	[[maybe_unused]] static int MaxBookId;
	friend ostream &operator<<(ostream &outStream, const Book &book);

};


#endif//LIBRARY_SYSTEM_BOOK_H
