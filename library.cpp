//
// Created by manmiddle on 9/27/21.
//

#include "library.h"
#include <map>



map<int, Book> Library::sBookMap;
map<int, Customer> Library::sCustomerMap;
[[maybe_unused]] string Library::sBinaryPath("Library.bin");

[[maybe_unused]] bool Library::lookUpBook(const string &author, const string &title, [[maybe_unused]] Book *bookPtr) {
	for (const pair<int, Book> entry : sBookMap) {
		const Book &book = entry.second;
		if ((book.author() == author) && (book.title() == title)) {
			if (bookPtr != nullptr) {
				*bookPtr = book;
			}
			return true;
		}
	}
	return false;
}

bool Library::lookUpCustomer(const string& name,
                             const string& address, Customer* customerPtr /*=nullptr*/){
	for (const pair<int,Customer> entry : sCustomerMap) {
		const Customer &customer = entry.second;
		if ((customer.name() == name) &&
		    (customer.address() == address)) {
			if (customerPtr != nullptr) {
				*customerPtr = customer;
			}
			return true;
		}
	}
	return false;
}
Library::Library() {
	load();
	bool quit = false;
	while (!quit) {
		cout << "1. Add Book" << endl
		     << "2. Delete Book" << endl
		     << "3. List Books" << endl
		     << "4. Add Customer" << endl
		     << "5. Delete Customer" << endl
		     << "6. List Customers" << endl
		     << "7. Borrow Book" << endl
		     << "8. Reserve Book" << endl
		     << "9. Return Book" << endl
		     << "0. Quit" << endl
		     << ": ";
		int choice = 0;
        cin>>choice;
		switch (choice) {
			case 1:
				addBook();
				break;
			case 2:
				deleteBook();
				break;
			case 3:
				listBooks();
				break;
			case 4:
				addCustomer();
				break;
			case 5:
				deleteCustomer();
				break;
			case 6:
				listCustomers();
				break;
			case 7:
				borrowBook();
				break;
			case 8:
				reserveBook();
				break;
			case 9:
				returnBook();
				break;
			case 0:
				quit = true;
				break;
		}
		cout << endl;
	}
	save();
}
void Library::addBook() {
	string author;
	cout << "Author: ";
	cin>>author;
	string title;
	cout << "Title: ";
	  cin>>title;
	if (lookUpBook(author, title)) {
		cout << endl
		     << "The book "
		        " << title << "
		        " by "
		     << author << " already exists." << endl;
		return;
	}
	Book book(author, title);
	sBookMap[book.bookId()] = book;
	cout << endl
	     << "Added: " << book << endl;
}
void Library::deleteBook() {
	string author;
	cout << "Author: ";
	cin >> author;
	string title;
	cout << "Title: ";
	cin >> title;
	Book book;
	if (!lookUpBook(author, title, &book)) {
		cout << endl
		     << "There is no book "
		        " << title << "
		        " by "
		     << "author " << author << "." << endl;
		return;
	}
	for (pair<int, Customer> entry : sCustomerMap) {
		Customer &customer = entry.second;
		customer.returnBook(book.bookId());
		customer.unReserveBook(book.bookId());
		sCustomerMap[customer.id()] = customer;
	}
	sBookMap.erase(book.bookId());
	cout << endl
	     << "Deleted." << endl;
}
void Library::listBooks() {
	if (sBookMap.empty()) {
		cout << "No books." << endl;
		return;
	}
	for (const pair<int, Book> entry : sBookMap) {
		const Book &book = entry.second;
		cout << book << endl;
	}
}
void Library::addCustomer() {
	string name;
	cout << "Name: ";
	cin >> name;
	string address;
	cout << "Address: ";
	cin >> address;
	if (lookUpCustomer(name, address)) {
		cout << endl
		     << "A customer with name " << name
		     << " and address " << address << " already exists."
		     << endl;
		return;
	}
	Customer customer(name, address);
	sCustomerMap[customer.id()] = customer;
	cout << endl
	     << "Added." << endl;
}
void Library::deleteCustomer() {
	string name;
	cout << "Name: ";
	cin >> name;
	string address;
	cout << "Address: ";
	cin >> address;
	Customer customer;
	if (!lookUpCustomer(name, address, &customer)) {
		cout << endl
		     << "There is no customer with name " << name
		     << " and address " << address << "." << endl;
		return;
	}
	if (customer.hasBorrowed()) {
		cout << "Customer " << name << " has borrowed at least "
		     << "one book and cannot be deleted." << endl;
		return;
	}
	for (pair<int, Book> entry : sBookMap) {
		Book &book = entry.second;
		book.unReserveBook(customer.id());
		sBookMap[book.bookId()] = book;
	}
	cout << endl
	     << "Deleted." << endl;
	sCustomerMap.erase(customer.id());
}
void Library::listCustomers() {
	if (sCustomerMap.empty()) {
		cout << "No customers." << endl;
		return;
	}
	for (const pair<int, Customer> entry : sCustomerMap) {
		const Customer &customer = entry.second;
		cout << customer << endl;
	}
}
void Library::reserveBook() {
	string author;
	cout << "Author: ";
	cin >> author;
	string title;
	cout << "Title: ";
	cin >> title;
	Book book;
	if (!lookUpBook(author, title, &book)) {
		cout << endl
		     << "There is no book "<< title <<" by "
		     << "author " << author << "." << endl;
		return;
	}
	if (!book.borrowed()) {
		cout << endl
		     << "The book with author " << author
		     << " and title "
		        " << title << "
		        " has not been "
		     << "borrowed. Please borrow the book instead." << endl;
		return;
	}
	string name;
	cout << "Customer name: ";
	cin >> name;
	string address;
	cout << "Address: ";
	cin >> address;
	Customer customer;
	if (!lookUpCustomer(name, address, &customer)) {
		cout << endl
		     << "No customer with name " << name
		     << " and address " << address << " exists." << endl;
		return;
	}
	if (book.customerId() == customer.id()) {
		cout << endl
		     << "The book has already been borrowed by "
		     << name << "." << endl;
		return;
	}
	customer.reserveBook(book.bookId());
	unsigned int position = book.reserveBook(customer.id());
	sBookMap[book.bookId()] = book;
	sCustomerMap[customer.id()] = customer;
	cout << endl
	     << position << "nd reserve." << endl;
}
void Library::returnBook() {
	string author;
	cout << "Author : ";
	cin >> author;
	string title;
	cout << "title : ";
	cin >> title;

	Book book;
	if (!lookUpBook(author, title, &book)) {
		cout << endl
		     << "The book " << title << " by " << author << " exists" << endl;
	}
	if (!book.borrowed()) {
		cout << endl
		     << " The book " << title << " By " << author << " Has not been borrowed " << endl;
		return;
	}
	book.returnBook();
	cout << endl
	     << " returned " << endl;
	Customer customer = sCustomerMap[book.customerId()];
	customer.returnBook(book.bookId());
	sCustomerMap[customer.id()] = customer;

	list<int> &reservationList = book.reservationList();
	if (!reservationList.empty()) {
		int newCustomerId = reservationList.front();
		reservationList.erase(reservationList.begin());
		book.borrowBook(newCustomerId);
		Customer newCustomer = sCustomerMap[newCustomerId];
		newCustomer.borrowBook(book.bookId());
		sCustomerMap[newCustomerId] = newCustomer;
		cout << endl
		     << "Borrowed by " << newCustomer.name() << endl;
	}
	sBookMap[book.bookId()] = book;
}
void Library::borrowBook() {
	string author;
	cout << "Author: ";
	cin >> author;
	string title;
	cout << "Title: ";
	cin >> title;
	Book book;
	if (!lookUpBook(author, title, &book)) {
		cout << endl
		     << "There is no book "
		        " << title << "
		        " by "
		     << "author " << author << "." << endl;
		return;
	}
	if (book.borrowed()) {
		cout << endl
		     << "The book "
		        " << title << "
		        " by "
		     << author
		     << " has already been borrowed." << endl;
		return;
	}
	string name;
	cout << "Customer name: ";
	cin >> name;
	string address;
	cout << "Address: ";
	cin >> address;
	Customer customer;
	if (!lookUpCustomer(name, address, &customer)) {
		cout << endl
		     << "There is no customer with name " << name
		     << " and address " << address << "." << endl;
		return;
	}
	book.borrowBook(customer.id());
	customer.borrowBook(book.bookId());
	sBookMap[book.bookId()] = book;
	sCustomerMap[customer.id()] = customer;
	cout << endl
	     << "Borrowed." << endl;
}
void Library::load() {
	ifstream inStream(sBinaryPath);
	if (inStream) {
		int numberOfBooks;
		inStream.read((char *) &numberOfBooks, sizeof numberOfBooks);
		for (int count = 0; count < numberOfBooks; ++count) {
			Book book;
			book.read(inStream);
			sBookMap[book.bookId()] = book;
			Book::MaxBookId = max(Book::MaxBookId, book.bookId());
		}
		int numberOfCustomers;
		inStream.read((char *) &numberOfCustomers, sizeof numberOfCustomers);
		for (int count = 0; count < numberOfCustomers; ++count) {
			Customer customer;
			customer.read(inStream);
			sCustomerMap[customer.id()] = customer;
			Customer ::MaxCustomerId = max(Customer::MaxCustomerId, customer.id());
		}
	}
}
void Library::save() {
	ofstream outStream(sBinaryPath);

	if (outStream) {
		unsigned int numberOfBooks = sBookMap.size();
		outStream.write((char *) &numberOfBooks, sizeof numberOfBooks);
		for (const pair<int, Book> entry : sBookMap) {
			const Book &book = entry.second;
			book.write(outStream);
		}
	}
}
