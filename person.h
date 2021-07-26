#ifndef PERSON_H
#define PERSON_H

#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

class Person
{
public:
    struct Element
    {
        struct Date
        {
            int day = 0;
            int month = 0;
            int year = 0;
        } date;
        string name;
        int price = 0;
        string category;
        string istochnik;
    };
    struct DohodElement
    {
        struct Date
        {
            int day = 0;
            int month = 0;
            int year = 0;
        } date;
        string name;
        int price = 0;
        string service;
        int people = 0;
        int sebest = 0;
        string istochnik;
    };
    struct Price {
        string cat;
        string ist;
        int price = 0;
        int sum = 0;
        int proc = 0;
    };
private:
    int version = 1;
    bool save = false;
    vector<Price> Rashod_Statistik;
    string User_name;
    vector<Element> Rashod;
    vector<string> Rashod_category;
    vector<string> Rashod_istochnik;
    vector<DohodElement> Dohod;
    vector<string> Dohod_istochnik;

public:
    Person();
    ~Person();
    const string& Get_Name();

    void Set_Rashod(const Element& elem);
    int Get_Rashod_Istochnik_Size();
    int Get_Rashod_Category_Size();
    int Get_Rashod_Size();
    int Get_Rashod_Statictic_Size();
    string& Get_Rashod_Istochnik_Str(const int& i);
    string& Get_Rashod_Category_Str(const int& i);
    Element& Get_Rashod_Element(const int& i);
    int Get_Rashod_Element_Begin(const int& day,const int& month,const int& year);
    int Get_Rashod_Element_End(const int& day,const int& month,const int& year);
    void Rashod_Erase(const int& i);
    void Rashod_Statistic(const int& start, const int& end);
    Price& Get_Rashod_Statistic_Element(const int& i);

    void Set_Dohod(const DohodElement& elem);
    int Get_Dohod_Istochnik_Size();
    int Get_Dohod_Size();
    string& Get_Dohod_Istochnik_Str(const int& i);
    DohodElement& Get_Dohod_Element(const int& i);
    int Get_Dohod_Element_Begin(const int& day,const int& month,const int& year);
    int Get_Dohod_Element_End(const int& day,const int& month,const int& year);
    void Dohod_Erase(const int& i);
    vector<pair<pair<int,int>, int>> Get_Dohod_Statistik(int& maxprice);


private:
    void Save();
    void Rashod_Sort_Date();
    void Set_Category();
    void Dohod_Sort_Date();
};

#endif // PERSON_H
