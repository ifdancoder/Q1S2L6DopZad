#include <string>
#include <iostream>
#include <locale>
#include <fstream>
#include <vector>s

using namespace std;

class Currency
{
private:
    string name;
    double cost;
public:
    Currency() : Currency("", 0)
    {
    }
    Currency(string nm, double cst) : name(nm), cost(cst)
    {
    }
    string getName() const
    {
        return name;
    }
    double getCost() const
    {
        return cost;
    }
    friend ostream& operator<< (ostream& out, const Currency& curr);
};

ostream& operator<< (ostream& out, const Currency& curr)
{
    out << curr.getName() << " : " << curr.getCost();
    return out;
}

class Currencies
{
private:
    vector<Currency> currses;
    int n;
public:
    Currencies(int n) : n(n)
    {
        if (n > 2 || n < 1)
        {
            cerr << "Error! Number of currencies is invalid. We will use 2 currencies." << endl;
            n = 2;
        }
    }
    void getCurrenciesFromFile(string fname = "Яндекс.html") {
        const string before_numb = R"(data-statlog="news_rates_manual.id)";
        const string after_numb = R"(data-statlog-showed="1">)";
        const string after_name = R"(</a>)";

        const string before_value = R"(class='inline-stocks__value_inner'>)";
        const string after_value = R"(</span>)";

        ifstream fin(fname);
        if (fin)
        {
            string buf, name;
            double cost;
            while (!fin.eof())
            {
                getline(fin, buf);
                int p1 = 0, p2 = 0;
                for (int i = 0; i < n && buf.find(before_numb, p2) + 1; i++)
                {
                    p1 = buf.find(after_numb, buf.find(before_numb, p2));
                    p1 = buf.find(R"(>)", p1) + 1;
                    p2 = buf.find(after_name, p1);
                    string name = buf.substr(p1, p2 - p1);
                    p2 += after_name.size();
                    p1 = buf.find(before_value, p2) + before_value.size();
                    p2 = buf.find(after_value, p1);
                    cost = stod(buf.substr(p1, p2 - p1));
                    p2 += after_value.size();
                    currses.push_back(Currency(name, cost));
                }
            }
        }
    }
    friend ostream& operator<< (ostream& out, const Currencies& currs);
};

ostream& operator<< (ostream& out, const Currencies& currs)
{
    for (int i = 0; i < currs.currses.size(); i++) {
        out << i + 1 << ") " << currs.currses[i] << endl;
    }
    return out;
}

int main()
{
    // #Доп. задание
    setlocale(LC_ALL, "Russian");
    Currencies css(2); /* Аргумент обозначает количество валют, которые нужно считать из файла (допустимые значения -> 1-2).
                          Есть проблема с кодировкой слов с кириллицей */
    css.getCurrenciesFromFile(/* Можно передать строку-имя html-файла в качестве аргумента */);
    cout << css;

    cout << endl << endl;
}
