#include "person.h"

Person::Person()
{
    ifstream fobj;
    fobj.open("User.base", ios::binary);
    if (fobj.is_open())
    {
        int ver = 0;
        fobj.read((char*)(&ver), sizeof(int));
        if(ver == version)
        {
            int namesize = 0;
            fobj.read((char*)(&namesize), sizeof(int));
            char* name = new char[namesize];
            fobj.read((char*)(name), sizeof(char) * namesize);
            User_name = name;
            delete [] name;

            int rashcatsize = 0;
            fobj.read((char*)(&rashcatsize), sizeof(int));
            for (int i=0; i< rashcatsize; i++)
            {
                int nsize = 0;
                fobj.read((char*)(&nsize), sizeof(int));
                char* rname = new char[nsize];
                fobj.read((char*)(rname), sizeof(char) * nsize);
                Rashod_category.push_back(rname);
                delete [] rname;
            }

            int rashistsize = 0;
            fobj.read((char*)(&rashistsize), sizeof(int));
            for (int i=0; i< rashistsize; i++)
            {
                int nsize = 0;
                fobj.read((char*)(&nsize), sizeof(int));
                char* rname = new char[nsize];
                fobj.read((char*)(rname), sizeof(char) * nsize);
                Rashod_istochnik.push_back(rname);
                delete [] rname;
            }

            int rashsize = 0;
            fobj.read((char*)(&rashsize), sizeof(int));
            for (int i=0; i< rashsize; i++)
            {
                Element temp;
                int nsize = 0;
                fobj.read((char*)(&nsize), sizeof(int));
                char* rname = new char[nsize];
                fobj.read((char*)(rname), sizeof(char) * nsize);
                temp.name = rname;
                delete [] rname;
                fobj.read((char*)(&temp.date), sizeof(temp.date));

                int catsize = 0;
                fobj.read((char*)(&catsize), sizeof(int));
                char* catname = new char[catsize];
                fobj.read((char*)(catname), sizeof(char) * catsize);
                temp.category = catname;
                delete [] catname;

                int istsize = 0;
                fobj.read((char*)(&istsize), sizeof(int));
                char* istname = new char[istsize];
                fobj.read((char*)(istname), sizeof(char) * istsize);
                temp.istochnik = istname;
                delete [] istname;

                fobj.read((char*)(&temp.price), sizeof(int));

                Rashod.push_back(temp);
            }

            int dohistsize = 0;
            fobj.read((char*)(&dohistsize), sizeof(int));
            for (int i=0; i< dohistsize; i++)
            {
                int nsize = 0;
                fobj.read((char*)(&nsize), sizeof(int));
                char* rname = new char[nsize];
                fobj.read((char*)(rname), sizeof(char) * nsize);
                Dohod_istochnik.push_back(rname);
                delete [] rname;
            }

            int dohsize = 0;
            fobj.read((char*)(&dohsize), sizeof(int));
            for (int i=0; i< dohsize; i++)
            {
                DohodElement temp;
                int nsize = 0;
                fobj.read((char*)(&nsize), sizeof(int));
                char* rname = new char[nsize];
                fobj.read((char*)(rname), sizeof(char) * nsize);
                temp.name = rname;
                delete [] rname;
                fobj.read((char*)(&temp.date), sizeof(temp.date));
                fobj.read((char*)(&temp.people), sizeof(int));
                fobj.read((char*)(&temp.sebest), sizeof(int));
                fobj.read((char*)(&temp.price), sizeof(int));

                int sersize = 0;
                fobj.read((char*)(&sersize), sizeof(int));
                char* sername = new char[sersize];
                fobj.read((char*)(sername), sizeof(char) * sersize);
                temp.service = sername;
                delete [] sername;

                int istsize = 0;
                fobj.read((char*)(&istsize), sizeof(int));
                char* istname = new char[istsize];
                fobj.read((char*)(istname), sizeof(char) * istsize);
                temp.istochnik = istname;
                delete [] istname;

                Dohod.push_back(temp);
            }
            save = true;
            fobj.close();
        }
        else
        {
            fobj.close();
            exit(-1);
        }
    }
    else
    {
        this->User_name = "Полина";
        Set_Category();
        Rashod.reserve(100);
        Dohod.reserve(100);
        save = true;
    }
}

Person::~Person()
{
}

const string& Person::Get_Name()
{
    return User_name;
}

void Person::Set_Rashod(const Element& elem)
{
    Rashod.push_back(elem);
    Rashod_Sort_Date();
    Save();
}

int Person::Get_Rashod_Istochnik_Size()
{
    return Rashod_istochnik.size();
}

int Person::Get_Rashod_Category_Size()
{
    return Rashod_category.size();
}

int Person::Get_Rashod_Size()
{
    return Rashod.size();
}

int Person::Get_Rashod_Statictic_Size()
{
    return Rashod_Statistik.size();
}

string &Person::Get_Rashod_Istochnik_Str(const int &i)
{
    return Rashod_istochnik[i];
}

string &Person::Get_Rashod_Category_Str(const int &i)
{
    return Rashod_category[i];
}

Person::Element &Person::Get_Rashod_Element(const int &i)
{
    return Rashod[i];
}

int Person::Get_Rashod_Element_Begin(const int &day, const int &month, const int &year)
{
    for(int i=0,max=Rashod.size();i<max;i++)
    {
        if(year < Rashod[i].date.year)
            return i;
        else if(year == Rashod[i].date.year && month < Rashod[i].date.month)
            return i;
        else if(year == Rashod[i].date.year && month == Rashod[i].date.month && day <= Rashod[i].date.day)
            return i;
    }
    return Rashod.size();
}

int Person::Get_Rashod_Element_End(const int &day, const int &month, const int &year)
{
    for(int i=Rashod.size()-1,max=0;i>=max;i--)
    {
        if(year > Rashod[i].date.year)
            return i;
        else if(year == Rashod[i].date.year && month > Rashod[i].date.month)
            return i;
        else if(year == Rashod[i].date.year && month == Rashod[i].date.month && day >= Rashod[i].date.day)
            return i;
    }
    return -1;
}

void Person::Save()
{
    if(save)
    {
        ofstream fobj;
        fobj.open("User.base", ios::binary);
        fobj.write((char*)(&version), sizeof(int));

        int namesize = int(User_name.size() + 1);
        fobj.write((char*)(&namesize), sizeof(int));
        fobj.write((char*)(User_name.data()), sizeof(char) * namesize);

        int rashcatsize = int(Rashod_category.size());
        fobj.write((char*)(&rashcatsize), sizeof(int));
        for (auto& now : Rashod_category)
        {
            int nsize = int(now.size() + 1);
            fobj.write((char*)(&nsize), sizeof(int));
            fobj.write((char*)(now.data()), sizeof(char) * nsize);
        }

        int rashistsize = int(Rashod_istochnik.size());
        fobj.write((char*)(&rashistsize), sizeof(int));
        for (auto& now : Rashod_istochnik)
        {
            int nsize = int(now.size() + 1);
            fobj.write((char*)(&nsize), sizeof(int));
            fobj.write((char*)(now.data()), sizeof(char) * nsize);
        }

        int rashsize = int(Rashod.size());
        fobj.write((char*)(&rashsize), sizeof(int));
        for (auto& now : Rashod)
        {
            int nsize = int(now.name.size() + 1);
            fobj.write((char*)(&nsize), sizeof(int));
            fobj.write((char*)(now.name.data()), sizeof(char) * nsize);
            fobj.write((char*)(&now.date), sizeof(now.date));

            int catsize = int(now.category.size() + 1);
            fobj.write((char*)(&catsize), sizeof(int));
            fobj.write((char*)(now.category.data()), sizeof(char) * catsize);

            int istsize = int(now.istochnik.size() + 1);
            fobj.write((char*)(&istsize), sizeof(int));
            fobj.write((char*)(now.istochnik.data()), sizeof(char) * istsize);

            fobj.write((char*)(&now.price), sizeof(int));
        }

        int dohistsize = int(Dohod_istochnik.size());
        fobj.write((char*)(&dohistsize), sizeof(int));
        for (auto& now : Dohod_istochnik)
        {
            int nsize = int(now.size() + 1);
            fobj.write((char*)(&nsize), sizeof(int));
            fobj.write((char*)(now.data()), sizeof(char) * nsize);
        }

        int dohsize = int(Dohod.size());
        fobj.write((char*)(&dohsize), sizeof(int));
        for (auto& now : Dohod)
        {
            int nsize = int(now.name.size() + 1);
            fobj.write((char*)(&nsize), sizeof(int));
            fobj.write((char*)(now.name.data()), sizeof(char) * nsize);

            fobj.write((char*)(&now.date), sizeof(now.date));
            fobj.write((char*)(&now.people), sizeof(int));
            fobj.write((char*)(&now.sebest), sizeof(int));
            fobj.write((char*)(&now.price), sizeof(int));

            int sersize = int(now.service.size() + 1);
            fobj.write((char*)(&sersize), sizeof(int));
            fobj.write((char*)(now.service.data()), sizeof(char) * sersize);

            int istsize = int(now.istochnik.size() + 1);
            fobj.write((char*)(&istsize), sizeof(int));
            fobj.write((char*)(now.istochnik.data()), sizeof(char) * istsize);
        }
        fobj.close();
    }
}

void Person::Rashod_Sort_Date()
{
    sort(Rashod.begin(), Rashod.end(), [](Element& a, Element& b)
    {
        if (a.date.year < b.date.year)
            return true;
        else if (a.date.year == b.date.year && a.date.month < b.date.month)
            return true;
        else if (a.date.year == b.date.year && a.date.month == b.date.month && a.date.day < b.date.day)
            return true;
        else
            return false;
    });
}

void Person::Set_Category()
{
    Rashod_category.push_back("Еда");
    Rashod_category.push_back("Косметика");
    Rashod_category.push_back("Здоровье");
    Rashod_category.push_back("Одежда");
    Rashod_category.push_back("Общепит");
    Rashod_category.push_back("Транспорт");
    Rashod_category.push_back("Хоз.товары");
    Rashod_category.push_back("Связь");
    Rashod_category.push_back("Учеба");
    Rashod_category.push_back("Танцы");
    Rashod_category.push_back("Другие");

    Rashod_istochnik.push_back("Я");
    Rashod_istochnik.push_back("Мама");

    Dohod_istochnik.push_back("Авито");
    Dohod_istochnik.push_back("ВК");
    Dohod_istochnik.push_back("Знакомые");
    Dohod_istochnik.push_back("Коменты");
    Dohod_istochnik.push_back("Отклики");
    Dohod_istochnik.push_back("Постоянные");
    Dohod_istochnik.push_back("Сарафан");
    Dohod_istochnik.push_back("ТФП");
    Dohod_istochnik.push_back("Фотограф");
    Dohod_istochnik.push_back("Чаты");
    Dohod_istochnik.push_back("ПодгонТФП");
    Dohod_istochnik.push_back("ГруппаМНН");
    Dohod_istochnik.push_back("Визажисты");
    Dohod_istochnik.push_back("ЯндексУслуги");
    Dohod_istochnik.push_back("Связи");
}

void Person::Rashod_Erase(const int& i)
{
    Rashod.erase(Rashod.begin()+i);
    Rashod_Sort_Date();
    Save();
}

void Person::Rashod_Statistic(const int& start, const int& end)
{
    Rashod_Statistik.clear();
    for (auto& cat : Rashod_category)
    {
        for (auto& ist : Rashod_istochnik)
        {
            Rashod_Statistik.push_back(Price{cat, ist, 0, 0,0});
        }
    }

    for (int i=start;i<=end;i++)
    {
        for (auto& pr : Rashod_Statistik)
        {
            if (pr.cat == Rashod[i].category && pr.ist == Rashod[i].istochnik)
                pr.price += Rashod[i].price;
            if (pr.cat == Rashod[i].category)
                pr.sum += Rashod[i].price;
        }
    }

    sort(Rashod_Statistik.begin(), Rashod_Statistik.end(), [](Price& a, Price& b)
    {
        if (a.ist > b.ist)
            return true;
        else
            return false;
    });
    auto it = Rashod_Statistik.begin();
    it += Rashod_category.size();
    sort(Rashod_Statistik.begin(),it, [](Price& a, Price& b)
    {
        if (a.price > b.price)
            return true;
        else
            return false;
    });
    sort(it, Rashod_Statistik.end(), [](Price& a, Price& b)
    {
        if (a.price > b.price)
            return true;
        else
            return false;
    });


    vector<int> istsum;
    for (int i=0;i<Get_Rashod_Istochnik_Size();i++)
    {
        istsum.push_back(0);
    }

    for (int i = 0; i < Get_Rashod_Category_Size(); i++)
    {
        for (int j = 0; j < Get_Rashod_Istochnik_Size(); j++)
        {
            int pro = 0;
            istsum[j] += Rashod_Statistik[i + j * Rashod_category.size()].price;
            if (Rashod_Statistik[i + j * Rashod_category.size()].sum != 0)
            {
                pro = int((Rashod_Statistik[i + j * Rashod_category.size()].price * 1000) / Rashod_Statistik[i + j * Rashod_category.size()].sum);
                pro % 10 >= 5 ? (pro /= 10) += 1 : (pro /= 10);
                Rashod_Statistik[i + j * Rashod_category.size()].proc=pro;
            }
        }
    }

    int sum = 0,i=0;
    for (auto& now : istsum)
    {
        sum += now;
        Rashod_Statistik.push_back(Price{" ", Rashod_istochnik[i++], 0, now,0});
    }
    Rashod_Statistik.push_back(Price{" ", " ", 0, sum,0});
}

Person::Price &Person::Get_Rashod_Statistic_Element(const int &i)
{
    return Rashod_Statistik[i];
}

void Person::Set_Dohod(const DohodElement &elem)
{
    Dohod.push_back(elem);
    Dohod_Sort_Date();
    Save();
}

int Person::Get_Dohod_Istochnik_Size()
{
    return Dohod_istochnik.size();
}

int Person::Get_Dohod_Size()
{
    return Dohod.size();
}

string &Person::Get_Dohod_Istochnik_Str(const int &i)
{
    return Dohod_istochnik[i];
}

Person::DohodElement &Person::Get_Dohod_Element(const int &i)
{
    return Dohod[i];
}

int Person::Get_Dohod_Element_Begin(const int &day, const int &month, const int &year)
{
    for(int i=0,max=Dohod.size();i<max;i++)
    {
        if(year < Dohod[i].date.year)
            return i;
        else if(year == Dohod[i].date.year && month < Dohod[i].date.month)
            return i;
        else if(year == Dohod[i].date.year && month == Dohod[i].date.month && day <= Dohod[i].date.day)
            return i;
    }
    return Dohod.size();
}

int Person::Get_Dohod_Element_End(const int &day, const int &month, const int &year)
{
    for(int i=Dohod.size()-1,max=0;i>=max;i--)
    {
        if(year > Dohod[i].date.year)
            return i;
        else if(year == Dohod[i].date.year && month > Dohod[i].date.month)
            return i;
        else if(year == Dohod[i].date.year && month == Dohod[i].date.month && day >= Dohod[i].date.day)
            return i;
    }
    return -1;
}

void Person::Dohod_Erase(const int &i)
{
    Dohod.erase(Dohod.begin()+i);
    Dohod_Sort_Date();
    Save();
}

vector<pair<pair<int,int>, int>> Person::Get_Dohod_Statistik(int& maxprice)
{
    vector<pair<pair<int,int>, int>> temp;
    int month = 0;
    int year = 0;
    int sum = 0;
    for(auto& now: Dohod)
    {
        if(year == 0)
        {
            year = now.date.year;
        }

        while(year != now.date.year || month != now.date.month)
        {
            temp.push_back(pair(pair(month,year),sum));
            if(sum > maxprice)
                maxprice = sum;
            sum = 0;
            month++;
            if(month>11)
            {
                year++;
                month = 0;
            }
        }
        sum += now.price;
    }
    if(sum > maxprice)
        maxprice = sum;
    temp.push_back(pair(pair(month,year),sum));
    return temp;
}

void Person::Dohod_Sort_Date()
{
    sort(Dohod.begin(), Dohod.end(), [](DohodElement& a, DohodElement& b)
    {
        if (a.date.year < b.date.year)
            return true;
        else if (a.date.year == b.date.year && a.date.month < b.date.month)
            return true;
        else if (a.date.year == b.date.year && a.date.month == b.date.month && a.date.day < b.date.day)
            return true;
        else
            return false;
    });
}
