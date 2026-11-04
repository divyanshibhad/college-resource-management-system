
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int MAX_RESOURCES = 100;
const string DATA_FILE = "data/resources.txt";

struct Resource {
    int id;
    string title;
    string category;
    string filePath;
};

Resource resources[MAX_RESOURCES];
int resourceCount = 0;

// Clear invalid input from the input stream
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Load saved resources from the file
void loadResources() {
    ifstream file(DATA_FILE);

    if (!file.is_open()) {
        return;
    }

    resourceCount = 0;

    while (resourceCount < MAX_RESOURCES &&
           file >> resources[resourceCount].id) {

        file.ignore();

        getline(file, resources[resourceCount].title);
        getline(file, resources[resourceCount].category);
        getline(file, resources[resourceCount].filePath);

        resourceCount++;
    }

    file.close();
}

// Save resources to the file
void saveResources() {
    ofstream file(DATA_FILE);

    for (int i = 0; i < resourceCount; i++) {
        file << resources[i].id << '\n';
        file << resources[i].title << '\n';
        file << resources[i].category << '\n';
        file << resources[i].filePath << '\n';
    }

    file.close();
}

// Display one resource
void showResource(const Resource &resource) {
    cout << "\nID: " << resource.id;
    cout << "\nTitle: " << resource.title;
    cout << "\nCategory: " << resource.category;
    cout << "\nFile path / link: " << resource.filePath;
    cout << "\n";
}

// Display all resources
void listResources() {
    if (resourceCount == 0) {
        cout << "\nNo resources have been added yet.\n";
        return;
    }

    cout << "\n--- All College Resources ---\n";

    for (int i = 0; i < resourceCount; i++) {
        showResource(resources[i]);
    }
}

// Add a new resource
void addResource() {
    if (resourceCount == MAX_RESOURCES) {
        cout << "\nResource limit reached.\n";
        return;
    }

    Resource newResource;
    newResource.id = resourceCount + 1;

    cout << "\nEnter resource title: ";
    getline(cin, newResource.title);

    cout << "Enter category "
         << "(Notes / PDFs / Papers / Study Material / Other): ";
    getline(cin, newResource.category);

    cout << "Enter local file path or share link: ";
    getline(cin, newResource.filePath);

    resources[resourceCount] = newResource;
    resourceCount++;

    saveResources();

    cout << "\nResource added successfully."
         << " ID: " << newResource.id << "\n";
}

// Search resources by title or category
void searchResources() {
    string keyword;

    cout << "\nEnter title or category to search: ";
    getline(cin, keyword);

    bool found = false;

    for (int i = 0; i < resourceCount; i++) {
        if (resources[i].title.find(keyword) != string::npos ||
            resources[i].category.find(keyword) != string::npos) {

            showResource(resources[i]);
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo matching resources found.\n";
    }
}

// Display available categories
void showCategories() {
    cout << "\n--- Resource Categories ---\n";
    cout << "1. Notes\n";
    cout << "2. PDFs\n";
    cout << "3. Previous-year papers\n";
    cout << "4. Study material\n";
    cout << "5. Subject resources\n";
    cout << "6. Other\n";
}

// Display the main menu
void showMenu() {
    cout << "\n===== College Resource Management System =====\n";
    cout << "1. List all resources\n";
    cout << "2. Add a resource\n";
    cout << "3. Search resources\n";
    cout << "4. View categories\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    loadResources();

    int choice = 0;

    do {
        showMenu();

        if (!(cin >> choice)) {
            clearInput();
            cout << "\nPlease enter a number from 1 to 5.\n";
            continue;
        }

        clearInput();

        switch (choice) {
            case 1:
                listResources();
                break;

            case 2:
                addResource();
                break;

            case 3:
                searchResources();
                break;

            case 4:
                showCategories();
                break;

            case 5:
                saveResources();
                cout << "\nResources saved. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid option. Choose 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}
