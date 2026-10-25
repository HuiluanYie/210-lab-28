// COMSC-210 | Lab 28 | Huiluan Yie

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

// Function prototype
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();
void sort_goats(list<Goat>&);
void reverse_goats(list<Goat>&);
double average_age(const list<Goat>&);
void year_later(list<Goat>&);

// helper function
int add_age(int, const Goat&);
Goat year_older(Goat);
bool too_old(const Goat&); 


int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 8) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                cout << "Sorting goat data.\n";
                sort_goats(trip);
                break;
            case 5:
                cout << "Reversing goat data.\n";
                reverse_goats(trip);
                break;
            case 6:
                cout << fixed << setprecision(1);
                cout << "Average goat age: " << average_age(trip) << '\n';
                break;
            case 7:
                year_later(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    return 0;
}

int main_menu() {
    cout << "\n*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n";
    cout << "[5] Reverse goat order\n";
    cout << "[6] Find goat average age\n";
    cout << "[7] Increase all goat's age\n";
    cout << "[8] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 8) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

// function definition
void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void sort_goats(list<Goat>& trip)
{
    trip.sort();
    cout << "The goats are now sorted by name.\n";
}

void reverse_goats(list<Goat>& trip)
{
    reverse(trip.begin(), trip.end());
    cout << "The goat order was reversed.\n";
}

double average_age(const list<Goat>& trip)
{
    int total = accumulate(trip.begin(), trip.end(), 0, add_age);
    double s = trip.size();
    return total / s;
}

void year_later(list<Goat>& trip)
{
    transform(trip.begin(), trip.end(), trip.begin(), year_older);
    trip.erase(remove_if(trip.begin(), trip.end(), too_old), trip.end());
    //// Remove villagers with a friendship level below 5
    //villagers.erase(remove_if(villagers.begin(), villagers.end(), 
    //  [](const Villager& v){ return v.friendshipLevel < 5; }), villagers.end());

    cout << "\nEvery goat aged one year.\n";
}

// helper
int add_age(int sum, const Goat& goat)
{
    return sum + goat.get_age();
}

Goat year_older(Goat goat)
{
    goat.set_age(goat.get_age() + 1);
    return goat;
}

bool too_old(const Goat& g)
{
    return g.get_age() > 20;
}

//[](const Villager& v){ return v.friendshipLevel < 5; }

// transform(villagers.begin(), villagers.end(), villagers.begin(), [](Villager& v) { v.friendshipLevel += 1; return v; });
// [](Villager& v) { v.friendshipLevel += 1; return v; }
