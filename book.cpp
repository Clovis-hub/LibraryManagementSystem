//
// Created by manmiddle on 9/27/21.
//
#include "book.h"
#include <iostream>
#include <string>
#include <utility>


int Book::MaxBookId=0;

Book::Book() = default;
Book::Book(string  Author, string  Title) :mBookId(++MaxBookId), mAuthor(std::move(Author)), mTitle(std::move(Title)) {}
void Book::write(ofstream &outStream) const {
	outStream.write((char*) &mBookId, sizeof mBookId);
	outStream<<mAuthor<<endl;
	outStream<<mTitle<<endl;
	outStream.write((char*) &mBorrowed ,sizeof mBorrowed);
	outStream.write((char*)&mCustomerId,sizeof mCustomerId);
	//Number of reservation and reservation identity then .

	{
		unsigned int reservationListSize=mReservationList.size();
		outStream.write((char*)&reservationListSize,sizeof reservationListSize);
		for (int customerId :mReservationList) {
			outStream.write((char*)&customerId,sizeof customerId);
		}

	}
}
void Book::read(ifstream &inStream) {
	inStream.read((char*)&mBookId,sizeof mBookId);
	getline(inStream,mAuthor);
	getline(inStream,mTitle);


	inStream.read((char*) &mBorrowed,sizeof mBorrowed);
	inStream.read((char*) &mCustomerId, sizeof mCustomerId);
	// First Read the number of reservation then Read the reservation identity themselves

	{
		int reservationListSize;
		inStream.read((char*) &reservationListSize, sizeof reservationListSize);
		for (int count = 0; count < reservationListSize; ++count) {
			int customerId;
			inStream.read((char*) &customerId , sizeof customerId);
			mReservationList.push_back(customerId);

		}
	}
}
ostream &operator<<(ostream &outStream, const Book &book) {
	outStream<<" "<<book.mTitle<<"by"<<book.mAuthor<<endl;
	if (book.mBorrowed){
		outStream<<endl<<" Borrowed By :  "<<Library::sCustomerMap[book.mCustomerId].name()<<"."<<endl;
	}
	if(book.mReservationList.empty()){
		outStream<<endl<<"   Reserved by :   ";
		for ([[maybe_unused]] int customerId :book.mReservationList) {
			outStream<< "," <<Library::sCustomerMap[customerId].name();
		}
		outStream<<"."<<endl;
	}
	return outStream;
}

void Book::borrowBook(int customerId) {
	mBorrowed=true;
	mCustomerId=customerId;
}

unsigned int Book::reserveBook(int customerId) {
	mReservationList.push_back(customerId);
	return mReservationList.size();
}

void Book::unReserveBook(int customerId) {
	mReservationList.remove(customerId);
}
void Book::returnBook() {
	mBorrowed= false;
}
