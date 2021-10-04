//
// Created by manmiddle on 9/27/21.
//

#include "customer.h"

int Customer::MaxCustomerId;

Customer::Customer() = default;
[[maybe_unused]] Customer::Customer(string  name, string address) : mCustomerId(++MaxCustomerId),mName(std::move(name)), mAddress(std::move(address)) {}
void Customer::read(ifstream &inStream) {
	inStream.read((char*) &mCustomerId , sizeof mCustomerId);
	getline(inStream,mName);
	getline(inStream,mAddress);

	{
		int loanSetSize;
		inStream.read((char*) &loanSetSize, sizeof loanSetSize);
		for (int count = 0; count < loanSetSize; ++count) {
			int bookId;
			inStream.read((char*) &bookId,sizeof bookId);
			mLoanSet.insert(bookId);
		}
		{
			int reservationListSize;
			inStream.read((char*) &reservationListSize, sizeof reservationListSize);

			for (int count = 0; count < reservationListSize; ++count) {
				int bookId;
				inStream.read((char*) &bookId,sizeof bookId);
				mLoanSet.insert(bookId);

			}
		}
	}
}
[[maybe_unused]] void Customer::write(ofstream outStream) const {
	outStream.write((char *) &mCustomerId, sizeof mCustomerId);
	outStream << mName << endl;
	outStream << mAddress << endl;

	// first write a set size and then the individual value of the set

	{
		unsigned int loanSetSize = mLoanSet.size();
		outStream.write((char *) &loanSetSize, sizeof loanSetSize);
		for (int bookId : mLoanSet) {
			outStream.write((char *) &bookId, sizeof bookId);
		}
	}
	{
		unsigned int reservationListSize=mReservationSet.size();
		outStream.write((char*) &reservationListSize,sizeof reservationListSize);
		for (int bookId :mReservationSet) {
			outStream.write((char*) &bookId,sizeof bookId);
		}
	}
}
void Customer::borrowBook(int bookId) {
	mLoanSet.insert(bookId);
}
void Customer::reserveBook(int bookId) {
	mReservationSet.insert(bookId);
}
void Customer::returnBook(int bookId) {
	mLoanSet.erase(bookId);
}
void Customer::unReserveBook(int bookId) {
	mReservationSet.erase(bookId);
}
ostream &operator<<(ostream &outStream, const Customer& customer) {
	outStream << customer.mCustomerId << ". " << customer.mName
	          << ", " << customer.mAddress << ".";
	if (customer.mLoanSet.empty()) {
		outStream << endl << " Borrowed books: ";
		for (int bookId : customer.mLoanSet) {
			outStream << ","<< Library::sBookMap[bookId].author();
		}
	}
	if (!customer.mReservationSet.empty()) {
		outStream << endl << " Reserved books: ";
		for (int bookId : customer.mReservationSet) {
			outStream << ","<< Library::sBookMap[bookId].title();
		}
	}
	return outStream;
}
