//
// Created by stefko on 2/5/26.
//

#include <iostream>
#include <fstream>
#include "Property.h"

const char *SAVE_FILE = "data.txt";

int strLen(const char *str) {
    int size = 0;
    while (str[size] != '\0') {
        size++;
    }
    return size;
}

char *strCpy(const char *sor, char *cpy) {
    int index = 0;
    while (sor[index] != '\0') {
        cpy[index] = sor[index];
        index++;
    }
    cpy[index] = '\0';
    return cpy;
}

std::ofstream createFile() {
    std::ofstream out(SAVE_FILE);
    if (!out) {
        std::cout << "Could not save the properties!" << std::endl;
    }
    return out;
}

void printTitle(const int &propertyCount) {
    std::cout << "---Real Estate Manager---" << std::endl;
    std::cout << "Current properties in system: " << propertyCount << std::endl;
    std::cout << std::endl;
}

void printMenuOptions() {
    std::cout << "Menu" << std::endl;
    std::cout << "1. Add property" << std::endl;
    std::cout << "2. Remove property" << std::endl;
    std::cout << "3. Rent out property" << std::endl;
    std::cout << "4. Release property" << std::endl;
    std::cout << "5. List all properties" << std::endl;
    std::cout << "6. Filter available properties" << std::endl;
    std::cout << "7. Financial report" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter choice: ";
}


void menuOptionOne(int &propertyCount, int &capacity, int &lastId, property *&properties) {
    if (propertyCount >= capacity) {
        int newCapacity = capacity * 2;
        property *newProperties = new property [newCapacity];
        for (int i = 0; i < propertyCount; i++) {
            newProperties[i] = properties[i];
        }
        delete[] properties;
        capacity = newCapacity;
        properties = newProperties;
    }
    newPropertyNullValues(capacity,properties);
    lastId++;
    properties[propertyCount].id = lastId;
    char strStatus[5] = {'F', 'R', 'E', 'E', '\0'};
    char cpy1[5] = {" "};
    properties[propertyCount].status = new char[5];
    strCpy(strStatus, cpy1);
    strCpy(cpy1, properties[propertyCount].status);
    std::cout << "--- ADD PROPERTY ---" << std::endl;
    std::cin.ignore();
    std::cout << "Enter type: ";
    char str1[BUFFER];
    std::cin.getline(str1, BUFFER);
    char *newStr1 = new char[strLen(str1) + 1];
    strCpy(str1, newStr1);
    properties[propertyCount].type = new char [strLen(str1) + 1];
    strCpy(newStr1, properties[propertyCount].type);
    delete [] newStr1;
    std::cout << "Enter address: ";
    char str2[BUFFER];
    std::cin.getline(str2, BUFFER);
    char *newStr2 = new char[strLen(str2) + 1];
    strCpy(str2, newStr2);
    properties[propertyCount].address = new char [strLen(str2) + 1];
    strCpy(newStr2, properties[propertyCount].address);
    delete [] newStr2;
    std::cout << "Enter area (sq. m.): ";
    std::cin >> properties[propertyCount].area;
    std::cout << "Enter price (EUR): ";
    std::cin >> properties[propertyCount].rent;
    properties[propertyCount].isRented = false;
    properties[propertyCount].newTenant.name = new char[1];
    properties[propertyCount].newTenant.name[0] = '\0';
    properties[propertyCount].newTenant.number = new char[1];
    properties[propertyCount].newTenant.number[0] = '\0';
    properties[propertyCount].newTenant.term = 0;
    std::cout << ">> Property added successfully with ID " << lastId << "!" << std::endl;
    std::cout << std::endl;
    propertyCount++;
}

void menuOptionTwo(int &propertyCount, property *&properties) {
    if (!propertyCount || !properties) {
        return;
    }
    int removeIdValue;
    std::cout << "--- REMOVE PROPERTY ---" << std::endl;
    std::cout << "Enter property ID: ";
    std::cin >> removeIdValue;
    bool notFound = true;
    int index = 0;
    for (int i = 0; i < propertyCount; ++i) {
        if (properties[i].id == removeIdValue) {
            notFound = false;
            index = i;
            break;
        }
    }
    if (notFound) {
        std::cout << ">> Error: Property ID " << removeIdValue << " not found!" << std::endl;
        return;
    }
    delete[] properties[index].address;
    delete [] properties[index].type;
    delete [] properties[index].status;
    delete [] properties[index].newTenant.name;
    delete [] properties[index].newTenant.number;
    for (int i = index; i < propertyCount - 1; ++i) {
        properties[i] = properties[i + 1];
    }
    propertyCount--;
    std::cout << ">> Property ID " << removeIdValue << " removed successfully!" << std::endl;
}

void menuOptionThree(property *&properties, int &propertyCount) {
    int currId;
    std::cout << "--- RENT OUT PROPERTY ---" << std::endl;
    std::cout << "Enter property ID: ";
    std::cin >> currId;
    bool notFound = true;
    int index = 0;
    for (int i = 0; i < propertyCount; ++i) {
        if (properties[i].id == currId) {
            notFound = false;
            index = i;
            break;
        }
    }
    if (properties[index].isRented) {
        std::cout << "Property is already rented!" << std::endl;
        return;
    }
    if (notFound) {
        std::cout << ">> Error: Property ID " << currId << " not found!" << std::endl;
        return;
    }
    std::cout << "Enter tenant name: ";
    char str1[BUFFER];
    std::cin.ignore();
    std::cin.getline(str1, BUFFER);
    char *newStr1 = new char[strLen(str1) + 1];
    strCpy(str1, newStr1);
    strCpy(newStr1, properties[index].newTenant.name);
    delete []newStr1;
    std::cout << "Enter tenant phone: ";
    char str2[BUFFER];
    std::cin.getline(str2, BUFFER);
    char *newStr2 = new char[strLen(str2) + 1];
    strCpy(str2, newStr2);
    strCpy(newStr2, properties[index].newTenant.number);
    delete []newStr2;
    properties[index].isRented = true;
    char rentedText[] = {'R', 'E', 'N', 'T', 'E', 'D', '\0'};
    strCpy(rentedText, properties[index].status);
    std::cout << ">> Successfully renter property it ID " << currId << " to \"" << properties[index].newTenant.name <<
            " \"" << std::endl;
}

void menuOptionFour(property *&properties, int &propertyCount) {
    int currId;
    std::cout << "--- RELEASE PROPERTY ---" << std::endl;
    std::cout << "Enter property ID: ";
    std::cin >> currId;
    int index = 0;
    for (int i = 0; i < propertyCount; ++i) {
        if (properties[i].id == currId) {
            index = i;
        }
    }
    if (!properties[index].isRented) {
        std::cout << ">> Error: Property with ID " << currId << " is already FREE!" << std::endl;
        return;
    }
    char *cpyTenantName = new char[strLen(properties[index].newTenant.name) + 1];
    strCpy(properties[index].newTenant.name, cpyTenantName);
    properties[index].newTenant.name[0] = {'\0'};
    properties[index].newTenant.number[0] = {'\0'};
    properties[index].newTenant.term = 0;
    properties[index].isRented = false;
    properties[index].status = new char[5];
    char freeStr[] = {'F', 'R', 'E', 'E', '\0'};
    strCpy(freeStr, properties[index].status);
    std::cout << ">> Property with ID " << currId << " is now FREE. Tenant \"" << cpyTenantName << "\" has been removed"
            << std::endl;
    delete [] cpyTenantName;
}

void menuOptionFive(property *&properties, const int &propertyCount) {
    std::cout << "--- ALL PROPERTIES ---" << std::endl;
    for (int i = 0; i < propertyCount; i++) {
        std::cout << "----------------------------------------------------------------------------------" << std::endl;
        std::cout << "ID: " << properties[i].id << " | Type: " << properties[i].type << " | Area: " << properties[i].
                area << " sq.m. | Price: " << properties[i].rent << " EUR | Status: " << properties[i].status <<
                std::endl;
        std::cout << "      > Address: " << properties[i].address << std::endl;
        if (properties[i].isRented) {
            std::cout << "      > Tenant: " << properties[i].newTenant.name << " (Phone: " << properties[i].newTenant.
                    number << ")" << std::endl;
        }
    }
    std::cout << ">> End of list." << std::endl;
}

void menuOptionSix(property *&properties, const int &propertyCount) {
    std::cout << "--- AVAILABLE PROPERTIES (FREE) ---" << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;
    int countFree = 0;
    for (int i = 0; i < propertyCount; i++) {
        if (!properties[i].isRented) {
            std::cout << "ID: " << properties[i].id << " | Type: " << properties[i].type << " | Area: " << properties[i]
                    .
                    area << " sq.m. | Price: " << properties[i].rent << " EUR | Status: " << properties[i].status <<
                    std::endl;
            std::cout << "      > Address: " << properties[i].address << std::endl;
            countFree++;
        }
    }
    if (countFree != 1) {
        std::cout << ">> Found " << countFree << " available properties." << std::endl;
    } else {
        std::cout << ">> Found " << countFree << " available property." << std::endl;
    }
}

void menuOptionSeven(property *&properties, const int &propertyCount) {
    std::cout << "--- FINANCIAL REPORT ---" << std::endl;
    double possibleIncome = 0;
    double currIncome = 0;
    for (int i = 0; i < propertyCount; ++i) {
        possibleIncome += properties[i].rent;
        if (properties[i].isRented) {
            currIncome += properties[i].rent;
        }
    }
    std::cout << "Total possible monthly income: " << possibleIncome << " EUR" << std::endl;
    std::cout << "Current actual income: " << currIncome << " EUR" << std::endl;
    std::cout << "Lost revenue (vacant properties): " << possibleIncome - currIncome << " EUR" << std::endl;
}

void menuOptionEight(const int &propertyCount, const int &lastID, const int &capacity, property *&properties) {
    std::ofstream out = createFile();
    if (!out.is_open()) {
        std::cout << "File could not be opened!" << std::endl;
        return;
    }
    int stats[] = {propertyCount, lastID, capacity};
    for (int i = 0; i < 3; ++i) {
        out << stats[i] << " ";
    }
    out << std::endl;
    for (int i = 0; i < propertyCount; ++i) {
        out << properties[i].id << '|' << properties[i].address << '|' << properties[i].type << '|' << properties[i].
                area << '|' << properties[i].rent << '|' << properties[i].status << '|' << properties[i].isRented << '|'
                << properties
                [i].newTenant.name << '|' << properties[i].newTenant.number << '|' << properties[i].newTenant.term <<
                '|' << std::endl;
    }
    out.close();
    std::cout << "Data saved to " << SAVE_FILE << ". Goodbye!" << std::endl;
}

void readFile(int &propertyCount, int &lastID, int &capacity, property *&properties) {
    std::ifstream in(SAVE_FILE);
    if (!in.is_open()) {
        return;
    }
    in >> propertyCount >> lastID >> capacity;
    if (capacity > 1) {
        delete [] properties;
        properties = new property[capacity];
    }
    char bufferText[BUFFER];
    for (int i = 0; i < propertyCount; ++i) {
        in >> properties[i].id;
        in.ignore();
        in.getline(bufferText, BUFFER, '|');
        properties[i].address = new char[strLen(bufferText) + 1];
        strCpy(bufferText, properties[i].address);
        in.getline(bufferText, BUFFER, '|');
        properties[i].type = new char[strLen(bufferText) + 1];
        strCpy(bufferText, properties[i].type);
        in >> properties[i].area;
        in.ignore();
        in >> properties[i].rent;
        in.ignore();
        in.getline(bufferText, BUFFER, '|');
        properties[i].status = new char[strLen(bufferText) + 1];
        strCpy(bufferText, properties[i].status);
        in >> properties[i].isRented;
        in.ignore();
        in.getline(bufferText, BUFFER, '|');
        properties[i].newTenant.name = new char[strLen(bufferText) + 1];
        strCpy(bufferText, properties[i].newTenant.name);
        in.getline(bufferText, BUFFER, '|');
        properties[i].newTenant.number = new char[strLen(bufferText) + 1];
        strCpy(bufferText, properties[i].newTenant.number);
        in >> properties[i].newTenant.term;
        in.ignore();
    }

    in.close();
}

void freePropertiesMemory(property *&properties, int &propertyCount) {
    for (int i = 0; i < propertyCount; ++i) {
        delete[] properties[i].address;
        delete [] properties[i].type;
        delete [] properties[i].status;
        delete [] properties[i].newTenant.name;
        delete [] properties[i].newTenant.number;
    }
    delete [] properties;
}

void newPropertyNullValues(int &capacity, property *&properties) {
    for (int i = 0; i < capacity; ++i) {
        properties[i].address = nullptr;
        properties[i].type=nullptr;
        properties[i].status = nullptr;
        properties[i].newTenant.name = nullptr;
        properties[i].newTenant.number = nullptr;
    }
}

void mainLoop() {
    int lastId = 0;
    int propertyCount = 0;
    int menuOption = 0;
    int capacity = 1;
    property *properties = new property [capacity];
    newPropertyNullValues(capacity,properties);
    readFile(propertyCount, lastId, capacity, properties);
    do {
        printTitle(propertyCount);
        printMenuOptions();
        std::cin >> menuOption;
        switch (menuOption) {
            case 1: menuOptionOne(propertyCount, capacity, lastId, properties);
                break;
            case 2: menuOptionTwo(propertyCount, properties);
                break;
            case 3: menuOptionThree(properties, propertyCount);
                break;
            case 4: menuOptionFour(properties, propertyCount);
                break;
            case 5: menuOptionFive(properties, propertyCount);
                break;
            case 6: menuOptionSix(properties, propertyCount);
                break;
            case 7: menuOptionSeven(properties, propertyCount);
                break;
            case 8: menuOptionEight(propertyCount, lastId, capacity, properties);
                break;
            default: std::cout << ">> Invalid menu option!" << std::endl;
                break;
        }
    } while (menuOption != 8);
    freePropertiesMemory(properties,propertyCount);
}
