//
// Created by stefko on 2/5/26.
//

#ifndef PROPERTY_MANAGMENT_SYSTEM_PROPERTY_H
#define PROPERTY_MANAGMENT_SYSTEM_PROPERTY_H

#endif //PROPERTY_MANAGMENT_SYSTEM_PROPERTY_H

const int BUFFER = 1000;

struct tenant {
    char *name;
    char *number;
    int term;
};

struct property {
    int id;
    char *address;
    char *type;
    double area;
    double rent;
    char *status;
    tenant newTenant;
    bool isRented;
};


int strLen(const char *str);

char *strCpy(const char *sor, char *cpy);

std::ofstream createFile();

void printTitle(const int *propertyCount);

void printMenuOptions();

void menuOptionOne(int &propertyCount, int &capacity, int &lastId, property *&properties);

void menuOptionTwo(int &propertyCount, property *&properties);

void menuOptionThree(property *&properties, int &propertyCount);

void menuOptionFour(property *&properties, int &propertyCount);

void menuOptionFive(property *&properties, const int &propertyCount);

void menuOptionSix(property *&properties, const int &propertyCount);

void menuOptionSeven(property *&properties, const int &propertyCount);

void menuOptionEight(const int &propertyCount, const int &lastID, const int &capacity, property *&properties);

void readFile(int &propertyCount, int &lastID, int &capacity, property *&properties);

void mainLoop();
