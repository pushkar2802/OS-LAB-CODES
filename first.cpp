#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;
    string email;

    Contact() {}
    Contact(string n, string p, string e) : name(n), phoneNumber(p), email(e) {}

    string toString() const {
        return name + "," + phoneNumber + "," + email;
    }
};

class ContactManager {
private:
    vector<Contact> contacts;
    const string filename = "contacts.txt";

    void loadContacts() {
        ifstream file(filename);
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, phone, email;

            getline(ss, name, ',');
            getline(ss, phone, ',');
            getline(ss, email, ',');

            contacts.push_back(Contact(name, phone, email));
        }
        file.close();
    }

    void saveContacts() const {
        ofstream file(filename);
        if (!file.is_open()) return;

        for (const auto& contact : contacts) {
            file << contact.toString() << endl;
        }
        file.close();
    }

public:
    ContactManager() {
        loadContacts();
    }

    ~ContactManager() {
        saveContacts();
    }

    void addContact(const Contact& contact) {
        contacts.push_back(contact);
    }

    void deleteContact(const string& name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->name == name) {
                contacts.erase(it);
                break;
            }
        }
    }

    void viewContacts() const {
        if (contacts.empty()) {
            cout << "No contacts are available." << endl;
            return;
        }

        cout << setw(20) << left << "Name"
             << setw(15) << left << "Phone"
             << "Email" << endl;

        for (const auto& contact : contacts) {
            cout << setw(20) << left << contact.name
                 << setw(15) << left << contact.phoneNumber
                 << contact.email << endl;
        }
    }
};

void displayMenu() {
    cout << "Contact Manager Menu" << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. Delete Contact" << endl;
    cout << "3. View Contacts" << endl;
    cout << "4. Exit" << endl;
    cout << "Select an option: ";
}

int main() {
    ContactManager manager;
    int choice;
    string name, phone, email;

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phone);
                cout << "Enter email: ";
                getline(cin, email);
                manager.addContact(Contact(name, phone, email));
                cout << "Contact added." << endl;
                break;
            case 2:
                cout << "Enter name of contact to delete: ";
                getline(cin, name);
                manager.deleteContact(name);
                cout << "Contact deleted (if existed)." << endl;
                break;
            case 3:
                manager.viewContacts();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
}
