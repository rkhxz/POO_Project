#include <map>
#include <cstring>
#include <chrono>
#include <ctime>
#include <cmath>

namespace preflight
{
// Constants
#define M_PI 3.14159265358979323846 /* pi */
    const map<string, int> genericFunds{{"good", 100}, {"bad", 10}};

    ////////MODIFY NUMBER OF CHILDREN => Affects the whole program
    const int no_of_children = 800;

    //Starting Mocks
    const short int mockFirstName = 0;
    const short int mockLastName = 1;
    const short int mockCity = 2;
    const short int mockToy = 3;

    //Int Mocks
    const short int mockBirthYear = 0;
    const short int mockPrice = 1;
    const short int mockNbOfPieces = 2;

// Defines
#define null NULL

    //Structs
    struct Inventory
    {
        int nb_pcs = 0;
        int price = 0;
        string name = "";
    };
    Inventory inventory[100];
    int inv_item_count = 1;

    // Helper functions

    // Replace getch from deprecated conio library
    void getch()
    {
        do
        {
            cout << '\n'
                 << "Press a key to continue...";
            fflush(stdin);
        } while (getchar() != '\n');
    }

    unsigned short int getCurrentYear()
    {
        auto now = chrono::system_clock::now();
        std::time_t now_c = chrono::system_clock::to_time_t(now);
        struct tm *parts = localtime(&now_c);

        return parts->tm_year + 1900; // Year + offset
    }

    int getFileLines(string filename)
    {
        ifstream reader;
        reader.open(filename);

        if (!reader.is_open())
        { // If file does not exist, return 0 lines.
            return 0;
        }

        string buffer;
        int lines = 0;
        while (reader.good())
        {
            lines++;
            getline(reader, buffer);
        }

        return lines;
    }

    string getFileLine(string filename, long long line)
    {
        ifstream reader;
        reader.open(filename);

        if (!reader.is_open())
        { // If file does not exist, return 0 lines.
            return "";
        }

        string buffer = "";
        long long currentLine = 0;
        while (currentLine < line && reader.good())
        {
            getline(reader, buffer);
            currentLine++;
        }

        return buffer;
    }

    long long randomBetween(long long min, long long max)
    {
        //srand(time(null));
        return rand() % (max - min + 1) + min;
    }

    void saveInventoryToCSV()
    {
        ofstream inv("datasets/Output/inventory.csv");
        if (inv.good())
            for (int i = 1; i <= inv_item_count; i++)
            {
                inv << inventory[i].name << "," << inventory[i].nb_pcs << "," << inventory[i].price << "\n";
            }
        inv.close();
    }

    // Templates

    template <typename T>
    T mock(short int type)
    {
    }

    template <>
    string mock(short int type)
    {
        string fileName;
        string returnable = "";
        FILE *f;
        char f_name[40];
        ifstream reader;

        switch (type)
        {
        case mockFirstName:
            fileName = "datasets/Input/first_names.csv";
            strcpy(f_name, fileName.c_str());
            reader.open(f_name);
            if (reader.is_open())
            {
                reader.close();
                returnable = getFileLine(fileName, randomBetween(0, getFileLines(fileName)));
            }
            else
            {
                returnable = "";
            }

            break;
        case mockLastName:
            fileName = "datasets/Input/last_names.csv";
            strcpy(f_name, fileName.c_str());
            reader.open(f_name);
            if (reader.is_open())
            {
                reader.close();
                returnable = getFileLine(fileName, randomBetween(0, getFileLines(fileName)));
            }
            else
            {
                returnable = "";
            }
            break;

        case mockCity:
            fileName = "datasets/Input/worldcities.csv";
            strcpy(f_name, fileName.c_str());
            reader.open(f_name);
            if (reader.is_open())
            {
                reader.close();
                returnable = getFileLine(fileName, randomBetween(0, getFileLines(fileName)));
            }
            else
            {
                returnable = "";
            }
            break;

        case mockToy:
            fileName = "datasets/Input/toys.csv";
            strcpy(f_name, fileName.c_str());
            reader.open(f_name);
            if (reader.is_open())
            {
                reader.close();
                returnable = getFileLine(fileName, randomBetween(0, getFileLines(fileName)));
                returnable = returnable.substr(0, returnable.length() - 1);
            }
            else
            {
                returnable = "";
            }
            break;
        default:
            break;
        }

        if (reader.is_open())
        {
            reader.close();
        }

        return returnable;
    }

    template <>
    int mock(short int type)
    {
        int returnable;
        switch (type)
        {
        case mockBirthYear:
            returnable = getCurrentYear() - int(randomBetween(5, 17));
            break;

        case mockPrice:
            returnable = int(randomBetween(0, 90));
            break;

        case mockNbOfPieces:
            returnable = int(randomBetween(0, 10));
            break;

        default:
            break;
        }
        return returnable;
    }

    // Generate Inventory

    void generateInventory(int nb_of_inv_items)
    {
        string taken_item[100] = {}, name;
        int n = 1;
        for (int i = 1; i <= nb_of_inv_items; i++)
        {
            bool avail = false;
            while (!avail)
            {
                name = mock<string>(3);
                for (int j = 1; j <= n; j++)
                    if (name == taken_item[j])
                    {
                        avail = false;
                        break;
                    }
                    else
                        avail = true;
            }
            taken_item[n] = name;
            n++;
            inventory[i].name = name;
            inventory[i].nb_pcs = mock<int>(2);
            inventory[i].price = mock<int>(1);
            inv_item_count++;
        }
        inv_item_count--;
    }

    void ShowInvetory()
    {
        cout << "Item name\t\tPrice\t\tNb. Pcs\n";
        cout << "------------------------------------------------\n";
        for (int i = 1; i <= inv_item_count; i++)
            cout << inventory[i].name << "\t\t" << inventory[i].price << "\t\t" << inventory[i].nb_pcs << "\n";
    }

    // CURL

    const string apiKey = "AIzaSyB5fVfi2GdXK1Nqt-ijctN1ryJ6JR96a4k";

    double distance;

    size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string *)userp)->append((char *)contents, size * nmemb);
        return size * nmemb;
    }

    // Utility function for
    // converting degrees to radians
    long double toRadians(const long double degree)
    {
        // cmath library in C++
        // defines the constant
        // M_PI as the value of
        // pi accurate to 1e-30
        long double one_deg = (M_PI) / 180;
        return (one_deg * degree);
    }

    int computeDistance(long double lat1, long double long1, long double lat2, long double long2)
    {
        // Convert the latitudes
        // and longitudes
        // from degree to radians.
        lat1 = toRadians(lat1);
        long1 = toRadians(long1);
        lat2 = toRadians(lat2);
        long2 = toRadians(long2);

        // Haversine Formula
        long double dlong = long2 - long1;
        long double dlat = lat2 - lat1;

        long double ans = pow(sin(dlat / 2), 2) +
                          cos(lat1) * cos(lat2) *
                              pow(sin(dlong / 2), 2);

        ans = 2 * asin(sqrt(ans));

        // Radius of Earth in
        // Kilometers, R = 6371
        // Use R = 3956 for miles
        long double R = 6371;

        // Calculate the result
        ans = ans * R;

        return ans;
    }
    int road[2*no_of_children];
    int visited[2*no_of_children];
    int n_visited = 0;
    bool first_run = true;
    // Dijkstra
    void dijkstra(int G[2 * no_of_children][2 * no_of_children], int n, int startnode, int road[2*no_of_children])
    {
        if(first_run){
            first_run = false;
            road[n_visited] = startnode;
            visited[n_visited] = startnode;
            n_visited++;
        }
        int new_start;
        int min = 999999;
        for (int i = 0; i < n; i++)
            {
                if(G[startnode][i] < min && startnode != i){
                    bool ok = true;
                    for(int j = 0; j < n_visited; j++)
                        if(visited[j] == i || road[j] == i)
                            ok = false;
                    if(ok){
                        min = G[startnode][i];
                        new_start = i;
                    }
                }
            }
        visited[n_visited] = new_start;
        road[n_visited] = new_start;
        G[new_start][startnode] = G[startnode][new_start] = 99999999;
        //cout << road[n_visited] << " ";
        n_visited++;
        if(n_visited < n)
            dijkstra(G, n, new_start, road);
    }
} // namespace preflight
