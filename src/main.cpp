#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct LegoSet {
  string setNumber;
  string theme;
  string name;
  int partCount;
  int minifigureCount;
  double price;

public:
  void display() {
    cout << "Name: " << name << endl;
    cout << "Number: " << setNumber << endl;
    cout << "Theme: " << theme << endl;
    cout << "Price: $" << fixed << setprecision(2) << price << endl;
    cout << "Minifigures: " << minifigureCount << endl;
    cout << "Piece count: " << partCount << endl;
  }
  void displaySlim() {
    cout << setNumber << " " << name << " " << fixed << setprecision(2) << " $"
         << price << endl;
  }
};

vector<LegoSet> readLegoData(const string &filename) {
  vector<LegoSet> legoSets;
  ifstream file(filename);
  string line;

  if (!file.is_open()) {
    throw runtime_error("Could not open file");
  }

  string header;
  getline(file, header); // read and discard header row

  while (getline(file, line)) {
    istringstream ss(line);
    string token;
    LegoSet set;

    getline(ss, set.setNumber, ',');
    getline(ss, set.theme, ',');
    getline(ss, set.name, ',');
    getline(ss, token, ',');
    set.minifigureCount = stoi(token);
    getline(ss, token, ',');
    set.partCount = stoi(token);
    getline(ss, token, ',');
    set.price = stod(token);

    legoSets.push_back(set);
  }

  file.close();
  return legoSets;
}

void findMostExpensiveSet(const vector<LegoSet> &sets) {
  cout << "The most expensive set is: " << endl;
  LegoSet mostExpensive = sets[0];
  for (const LegoSet &set : sets) {
    if (set.price > mostExpensive.price)
      mostExpensive = set;
  }
  mostExpensive.display();
}
void findLargestPieceCount(const vector<LegoSet> &sets) {
  cout << "The set with the highest parts count: " << endl;
  LegoSet largestPieceCount = sets[0];
  for (const LegoSet &set : sets) {
    if (set.partCount > largestPieceCount.partCount)
      largestPieceCount = set;
  }
  largestPieceCount.display();
}
void searchSetName(const vector<LegoSet> &sets, string searchTerm) {
  vector<LegoSet> results;
  bool found = false;

  for (LegoSet set : sets) {
    if (set.name.find(searchTerm) != string::npos) {
      found = true;
      results.push_back(set);
    }
  }
  if (found) {
    cout << "Sets matching \"" << searchTerm << "\":" << endl;
    for (LegoSet set : results)
      set.displaySlim();
  } else
    cout << "No sets found matching that search term" << endl;
}
// 4. Search themes
void searchThemes(const vector<LegoSet> &sets, string theme) {
  // theme.erase(remove_if(theme.begin(), theme.end(), ::isspace),
  //                      theme.end());
  vector<LegoSet> results;
  cout << "Sets matching \"" << theme << "\":" << endl;
  for (LegoSet set : sets) {
    if (set.theme.find(theme) != string::npos) {
      set.displaySlim();
    }
  }
}
void getPartCountInformation(const vector<LegoSet> &sets) {
  int totalParts = 0;
  int totalSets = sets.size();
  for (const LegoSet &set : sets) {
    totalParts += set.partCount;
  }
  cout << "Average part count for " << totalSets
       << " sets: " << totalParts / totalSets << endl;
}
// show the average, minimum and maximum prices of the sets
void getPriceInformation(const vector<LegoSet> &sets) {
  LegoSet mostExpensive = sets[0];
  LegoSet leastExpensive = sets[0];
  double total = 0;
  int numOfSets = sets.size();

  for (const LegoSet &set : sets) {
    if (set.price > mostExpensive.price)
      mostExpensive = set;
    else if (set.price < leastExpensive.price)
      leastExpensive = set;
    total += set.price;
  }
  cout << "Average price for " << numOfSets << " sets: $" << fixed
       << setprecision(2) << total / numOfSets << endl
       << endl;
  cout << "Least expensive set:" << endl;
  leastExpensive.display();
  cout << endl;
  cout << "Most expensive set:" << endl;
  mostExpensive.display();
}
// Show the average number of minifigures, and the set information for the set
// with the most minifigures
void getMinifigureInformation(const vector<LegoSet> &sets) {
  LegoSet mostMinifigures = sets[0];
  int numOfSets = sets.size();
  int sum = 0;

  for (const LegoSet &set : sets) {
    if (set.minifigureCount > mostMinifigures.minifigureCount)
      mostMinifigures = set;
    sum += set.minifigureCount;
  }

  cout << "Average number of minifigures: " << sum / numOfSets << endl << endl;
  cout << "Set with the most minifigures: " << endl;
  mostMinifigures.display();
}

// How much would it costs? How many parts and minifigures would you have?
void getEverythingInformation(const vector<LegoSet> &sets) {
  double totalPrice = 0.0;
  int totalParts = 0;
  int totalMinifigures = 0;
  for (const LegoSet &set : sets) {
    totalPrice += set.price;
    totalMinifigures += set.minifigureCount;
    totalParts += set.partCount;
  }

  cout << "It would cost: $" << fixed << setprecision(2) << totalPrice << endl;
  cout << "You would have " << totalParts << " pieces in your collection"
       << endl;
  cout << "You would have an army of " << totalMinifigures << " minifigures!"
       << endl;
}

int main() {
  vector<LegoSet> legoSets;
  cout << "Which file(s) to open?" << endl;
  cout << "1. lego1.csv" << endl;
  cout << "2. lego2.csv" << endl;
  cout << "3. lego3.csv" << endl;
  cout << "4. All 3 files" << endl;
  int option;
  cin >> option;

  try {
    vector<LegoSet> legoData1 = readLegoData("data/lego1.csv");
    vector<LegoSet> legoData2 = readLegoData("data/lego2.csv");
    vector<LegoSet> legoData3 = readLegoData("data/lego3.csv");
    switch (option) {
    case 1:
      legoSets = legoData1;
      break;
    case 2:
      legoSets = legoData2;
      break;
    case 3:
      legoSets = legoData3;
      break;
    case 4:
      legoSets.insert(legoSets.end(), legoData1.begin(), legoData1.end());
      legoSets.insert(legoSets.end(), legoData2.begin(), legoData2.end());
      legoSets.insert(legoSets.end(), legoData3.begin(), legoData3.end());
      break;
    default:
      cout << "Invalid option. Exiting." << endl;
      return 1;
    }
  } catch (const exception &e) {
    cerr << "Error reading file(s): " << e.what() << endl;
    return 1;
  }

  int choice;
  cout << "1. Most Expensive set\n";
  cout << "2. Largest piece count\n";
  cout << "3. Search for set name containing...\n";
  cout << "4. Search themes...\n";
  cout << "5. Part count information\n";
  cout << "6. Price information\n";
  cout << "7. Minifigure information\n";
  cout << "8. If you bought one of everything...\n";
  cout << "0. Exit\n";
  cin >> choice;

  cout << "Total number of sets: " << legoSets.size() << endl << endl;

  switch (choice) {
  case 1: {
    findMostExpensiveSet(legoSets);
    break;
  }
  case 2: {
    findLargestPieceCount(legoSets);
    break;
  }
  case 3: {
    string searchTerm;
    getline(cin >> ws, searchTerm);
    searchSetName(legoSets, searchTerm);
    break;
  }
  case 4: {
    string theme;
    getline(cin >> ws, theme);
    searchThemes(legoSets, theme);
    break;
  }
  case 5: {
    getPartCountInformation(legoSets);
    break;
  }
  case 6: {
    getPriceInformation(legoSets);
    break;
  }
  case 7: {
    getMinifigureInformation(legoSets);
    break;
  }
  case 8: {
    cout << "If you bought one of everything..." << endl;
    getEverythingInformation(legoSets);
    break;
  }
  case 0:
    cout << "Exiting...\n";
    break;
  default:
    cout << "Invalid choice. Please try again.\n";
  }

  return 0;
}
