#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

class  Location { //main class for the program private vairables all the data i need incldues in my vector
private:
    string name;
    int population;
    int yearRecorded;
    string leader;
    string leaderAdress;
    string history;
    double lat;
    double lon;

public: // sets up all variables to be used in class
    Location() = default;
    Location(string name, int population, int yearRecorded, string leader, string leaderAdress, string history, double lat, double lon){
        this->name = name;
        this->population = population;
        this->yearRecorded = yearRecorded;
        this->leader = leader;
        this->leaderAdress = leaderAdress;
        this->history = history;
        this->lat = lat;
        this->lon = lon;
    }

    void new_location() {//gets all required data for a location to be added to the vector and contains validation on the data to ensure correct datatpye
        cout << "enter place name";
        while (true) {
            getline(cin, name);

            if (!name.empty()) {
                break;
            }
            else {
                cout << "place name cannot be blank";
            }
        }

        cout << "enter population";
        while (!(cin >> population)){
            cout << "please enter a valid number";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "enter the year population data was collected";
        while (!(cin >> yearRecorded)){
            cout << "please enter a valid number";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "enter the leader name";
        getline(cin, leader);


        cout << "enter the leader address";
        getline(cin, leaderAdress);


        cout << "enter the history";
        getline(cin, history);


        cout << "enter latitude"; //validation on lat and long to ensure they are in a correct range and they are ints
        while (true){

            if (cin >> lat) {
                if (lat >= -90 && lat <= 90) {
                    break;
                }
                else {
                    cout << "error: input out of range" << endl;
                }
            }
            else {
                cout << "please enter a valid number" << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "enter longitude";
        while (true){
            if (cin >> lon) {
                if (lon >= -180 && lon <= 180) {
                    break;
                }
                else {
                    cout << "error: input out of range" << endl;
                }
            }
            else {
                cout << "please enter a valid number" << endl;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string getname() const {//intailises getters for all data so it can be written
        return name;
    }
    int getpopulation() const {
        return population;
    }
    int getyearRecorded() const {
        return yearRecorded;
    }
    string getleader() const {
        return leader;
    }
    string getleaderAddress() const {
        return leaderAdress;
    }
    string gethistory() const {
        return history;
    }
    double getlat() const {
        return lat;
    }
    double getlon() const {
        return lon;
    }

    void display_location() const { //displays all the infomation about one location
        std::cout << "Name: " << name << endl;
        std::cout << "Population: " << population << endl;
        std::cout << "Year Recorded: " << yearRecorded << endl;
        std::cout << "Leader: " << leader << endl;
        std::cout << "Leader Address: " << leaderAdress << endl;
        std::cout << "History: " << history << endl;
        std::cout << "Latitude: " << lat << endl;
        std::cout << "Longitude: " << lon << "\n" << endl;

    }


};

double distance (int  a, int b, const vector<Location>& locations ){//haversine formula to calcuate distance between lat and long of two places
    double alat = locations[a].getlat() *M_PI / 180.0; ;
    double alon = locations[a].getlon() *M_PI / 180.0; ;
    double blat = locations[b].getlat() *M_PI / 180.0; ;
    double blon = locations[b].getlon() *M_PI / 180.0; ;

    double dLat = (alat - blat);
    double dLon = (alon - blon);

    double x = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) * cos(alat) * cos(blat) ;
    double rad = 6371;
    double c = 2 * asin(sqrt(x));
    return rad * c;
}

int main() {

    int menu;// intalises the input for the main menu and the vecotr
    vector<Location> locations;

/*
    ifstream myFile("locations.txt");// open the txt containing location detials


    std::string line;
    while (std::getline(myFile, line)) {//loops taking all the data out of the text file by splitting it by white spaces
        std::stringstream ss(line);

        std::string name, leader, leaderAdress, history;
        int population, yearRecorded;
        double lat, lon;


        ss >> name >> population >> yearRecorded >> leader >> leaderAdress >> history >> lat >> lon;



        Location loc(name, population, yearRecorded, leader, leaderAdress, history, lat, lon);

        locations.push_back(loc);
    }
    myFile.close();
*/

    do {//runs a do while to ensure the main menu input is valid


        cout << "Location Storage program " << std::endl;//show the user all menu option
        cout << "enter 1 to add a location \n";
        cout << "enter 2 to delete a location \n";
        cout << "enter 3 to display a location \n";
        cout << "enter 4 to find the distance between 2 locations\n";
        cout << "enter 5 to display all stored locations\n";
        cout << "enter 6 to leave\n" << endl;
        while (!(cin >> menu)){//loop to ensure the input entered for the main menu is valid
            cout << "please enter a valid number";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (menu) {
                case 1: {//menu option one runs the code from the location class and adds it to the vector
                    Location temp;
                    temp.new_location();
                    locations.push_back(temp);
                    break;
                }
                case 2: {
                    string name;//taks a a place name and deletes all content of the vector related to that placemname
                    cout << "enter place name";
                    getline(cin, name);
                    bool check = false;



                    for (int i = 0; i < locations.size() ; i++) {
                        if (locations[i].getname() ==  name){
                            locations.erase(locations.begin() + i);
                            check = true;
                            break;

                        }
                    }


                }

                case 3: {
                    bool check2 = false;
                    string name; // takes a placenamame and finds it location in the vecore before sending that location to the display function in the class
                    cout << "enter place name";
                    getline(cin, name);
                    for (int i = 0; i < locations.size() ; i++) {
                        if (locations[i].getname() ==  name) {
                            locations[i].display_location();
                            check2 = true;
                        }



                    }
                    if (check2 == true){
                    cout << "returning to menu" << endl;
                    }
                    else {
                        cout << "location not found"<< endl;
                    }
                    break;

                }
                case 4: {//takes two placeanames and puts them into the haversine formula
                    string a;
                    int ia = -1;
                    cout << "enter place name for location 1";
                    getline(cin, a);
                    for (int i = 0; i < locations.size() ; i++) {
                        if (locations[i].getname() ==  a) {
                            ia = i;
                            break;
                        }
                    }
                    string b;
                    int ib = -1;
                    cout << "enter place name for location 2";
                    getline(cin, b);
                    for (int i = 0; i < locations.size() ; i++) {
                        if (locations[i].getname() ==  b) {
                            ib = i;
                            break;
                        }
                    }
                    if (ib == -1 || ia == -1) {
                        cout << "Locations not found" << endl;
                    }
                    else {
                        double dis = distance(ia,ib,locations);
                         cout  << "distance between " << a << " and " << b  << " is "<< dis << "\n" <<endl;
                    }

                    break;
                }

                case 5: { //displays the names of all locations stored in the program
                    for (int i = 0; i < locations.size() ; i++) {
                        cout << "stored locations:";
                        cout << locations[i].getname() << endl;

                    }
                    break;
                }
                case 6: { // message for exiting the program
                    cout << "exiting porgram" << endl;
/*
                    ofstream writefile("locations.txt"); //writes it into the text file by calling the the data using the getter functions
                    for (int i = 0; i < locations.size() ; i++) {
                        writefile << locations[i].getname() << " "
                        << locations[i].getpopulation() << " "
                        << locations[i].getyearRecorded() << " "
                        << locations[i].getleader() << " "
                        << locations[i].getleaderAddress() << " "
                        << locations[i].gethistory() << " "
                        << locations[i].getlat() << " "
                        << locations[i].getlon() << "\n";
                    }
                    writefile.close();

                    break;
*/
                }

                default: { //if the user entered something that isn't one of the suggested menu options display a error message
                    cout << "error enter a valid number \n" << endl;
                    break;
                }
            }

    } while (menu != 6); // actaully exits the while loop and ends the code

    return 0;
}