// Preflight
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <type_traits>
#include <sstream>
#include <vector>
using namespace std;
#include "preflight.h"
using namespace preflight;

// Class declarations
#include "classes.h"
using namespace classes;

// Helpers
const int number_of_children = no_of_children;
Letter letters[number_of_children];
Elf elfs[number_of_children];

string cities[2*number_of_children];
int distances[2*number_of_children][2*number_of_children] = {};
int no_of_cities = 0;
int road1[2*number_of_children];
string final_road[2*number_of_children];

struct city{
    long double lati;
    long double longi;
};
city cities_coord[2*number_of_children];

void generateDistMatrix(){
    for(int i = 0; i < no_of_cities; i++)
        for(int j = 0 ; j < no_of_cities; j++){
            if(i == j)
                distances[i][j] = 0;
            else{
                distances[i][j] = distances[j][i] = computeDistance(cities_coord[i].lati, cities_coord[i].longi, cities_coord[j].lati, cities_coord[j].longi);
                //cout << "Distance from " << cities[i] << " to " << cities[j] << " is :" << distances[i][j] << "\n";
            }
        }
    dijkstra(distances, no_of_cities, no_of_cities-1, road1);
    for(int i = 0; i < no_of_cities; i++){
        final_road[i] = cities[road1[i]];
        //cout << final_road[i] << " ";
    }
}

void generateCityStrings(){
    for(int i = 0; i < number_of_children; i++)
        {
            Child c = letters[i].getChild();
            string city = c.getCity();
            bool registered = false;
            for(int j = 0; j < no_of_cities; j++)
                if(c.getCity() == cities[i]){
                    registered = true;
                    break;
                }
            if(!registered){
                size_t s = c.getCity().find("");
                size_t e = c.getCity().find(",", s);
                size_t f;
                string sub = c.getCity().substr(s , e - s - 1);
                cities[no_of_cities] = sub;
                s = c.getCity().find(",");
                e = c.getCity().find(",", s);
                sub = c.getCity().substr(s +1, e - s - 1);
                //cout << sub << "\n";
                cities_coord[no_of_cities].lati = stod(sub.c_str());
                string str = c.getCity();
                stringstream ss(str);
                vector<string> result;
                while(ss.good()){
                    string substr;
                    getline(ss, substr, ',');
                    result.push_back(substr);
                }
                //for(int i = 0 ; i < result.size(); i++)
                //    cout << result.at(i) << "\n";
                //cout << sub << "\n";
                //sub = c.getCity().substr(e +1, f - e - 1);
                cities_coord[no_of_cities].longi = stod(result.at(2));
                //cout << cities_coord[no_of_cities].lati << " " << cities_coord[no_of_cities].longi << "\n";
                no_of_cities++;
            }
        }
    cities_coord[no_of_cities].lati = 66.503059;
    cities_coord[no_of_cities].longi = 25.726967;
    cities[no_of_cities] = "Rovaniemi";
    no_of_cities++;
    //for(int i = 0; i < no_of_cities; i++)
        //cout << cities[i] << "\n";
    generateDistMatrix();
}

void showPresents(){
    for(int i = 0; i < number_of_children; i++ ){
        letters[i].showPresent();
    }

    ///So that objects won.t get destroyed
    for(int i = 0; i < number_of_children; i++ ){
        elfs[i].getLetter();
    }
}

void generatePresents(){
    for(int i = 0; i < number_of_children; i++ ){
        elfs[i].setLetter(letters[i]);
    }
}

void showWishlists()
{
    for (int i = 0; i < number_of_children; i++)
    {
        letters[i].showWishlist();
    }
    cout << "\n\n";
}

void saveLettersToCSV()
{
    ofstream letterF("datasets/Output/children.csv");
    ofstream citiesF("datasets/Output/cities.csv");
    if (letterF.good())
        for (int i = 0; i < number_of_children; i++)
        {
            Child c = letters[i].getChild();
            letterF << c.getFirstName() << "," << c.getLastName() << "," << c.getAge() << "," << c.getGender() << "," << c.getFunds() << "\n";
        }
    string checked_cities[number_of_children];
    int nb_of_checked_cities = 0;
    bool checked = false;
    if(citiesF.good()){
        for (int i = 0; i < number_of_children; i++){
            Child c = letters[i].getChild();
            for(int j = 0; j < nb_of_checked_cities; j++)
                if(checked_cities[j] == c.getCity()){
                    checked = true;
                    break;
                }
            if(!checked){
                checked_cities[nb_of_checked_cities] = c.getCity();
                nb_of_checked_cities++;
                citiesF << c.getCity() << "\n"; 
                //cout << c.getCity() << "\n";
                checked = false;
            }
        }
    }
}

void saveCitiesToCSV()
{
    ofstream citiesF("datasets/Output/cities.csv");
    string checked_cities[number_of_children];
    int nb_of_checked_cities = 1;
    bool checked = false;
    if(citiesF.good()){
        for (int i = 0; i < number_of_children; i++){
            Child c = letters[i].getChild();
            for(int j = 1; j <= nb_of_checked_cities; j++)
                if(checked_cities[j] == c.getCity()){
                    checked = true;
                    break;
                }
            if(!checked){
                checked_cities[nb_of_checked_cities] = c.getCity();
                nb_of_checked_cities++;
                citiesF << c.getCity() << "\n"; 
                cout << c.getCity() << "\n";
                checked = false;
            }
        }
    }
}

// Main app
int main()
{
    generateInventory(20);
    //ShowInvetory();
    saveInventoryToCSV();
    //showWishlists();
    generatePresents(); 
    generateCityStrings();
    //showPresents();
    //saveCitiesToCSV();
    saveLettersToCSV();
    cout<<"GATA!!\n";
    getch();
    Troll t(number_of_children);
    t.setLetter(letters);
    Santa Santa("Santa", final_road, no_of_cities);
    Mrs_Claus Mrs_Claus(Santa);
    Mrs_Claus.showRoad();
    getch();
    return 0;
}