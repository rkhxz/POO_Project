#include <cstring>
namespace classes
{
    double total_amount = 0;
    // Class declarations
    class Child
    {
    public:
        // Constructors
        Child()
        {
            this->firstName = "";
            this->lastName = "";
            this->gender = "";
        }

        Child(string firstNameConstruct, string lastNameConstruct, unsigned short int birthYearConstruct, bool goodConstruct, string letterColor, string city)
        {
            this->firstName = firstNameConstruct;
            this->lastName = lastNameConstruct;
            this->birthYear = birthYearConstruct;
            this->good = goodConstruct;
            this->city = city;
            if (letterColor == "blue")
            {
                this->gender = "male";
            }
            else
            {
                this->gender = "female";
            }
            if (good)
            {
                this->funds = 100;
            }
            else
            {
                this->funds = 10;
            }
        }

        // Destructors
        ~Child()
        {
            //cout << this->firstName << " " << this->lastName << " destructed\n";
        }

        // Getters

        string getFirstName()
        {
            return this->firstName;
        }

        string getLastName()
        {
            return this->lastName;
        }

        unsigned short int getAge()
        {
            return getCurrentYear() - this->birthYear;
        }

        bool isGood()
        {
            return this->good;
        }

        double getFunds()
        {
            return this->funds;
        }

        string getGender()
        {
            return this->gender;
        }

        string getCity()
        {
            return this->city;
        }

        // Setters
        void setFirstName(string value)
        {
            this->firstName = value;
        }

        void setLastName(string value)
        {
            this->lastName = value;
        }

        void setGood(bool value, bool updateFunds = false)
        {
            this->good = value;

            if (!updateFunds)
            {
                return;
            }

            if (good)
            {
                this->funds = genericFunds.find("good")->second;
            }
            else
            {
                this->funds = genericFunds.find("bad")->second;
            }
        }

        void setBirthYear(unsigned short int value)
        {
            this->birthYear = value;
        }

        void setFunds(double value)
        {
            this->funds = value;
        }

        void setCity(string c)
        {
            this->city = c;
        }

        void setGender(string c)
        {
            this->gender = c;
        }

        // Methods
        void reduceFunds(int value)
        {
            this->funds -= value;
        }

    private:
        string firstName;
        string lastName;
        string gender;
        string city;
        bool good;
        unsigned short int birthYear;
        double funds;
    };

    class Letter
    {
    public:
        // Constructors
        Letter()
        {
            int ran = randomBetween(1, 2);
            if (ran == 1)
                this->color = "blue";
            else
                this->color = "pink";
            this->wishlist_items = int(randomBetween(1, 9));
            generateWishlist();
            this->child.setFirstName(mock<string>(0));
            this->child.setLastName(mock<string>(1));
            this->child.setCity(mock<string>(2));
            this->child.setBirthYear(mock<int>(0));
            if (this->color == "blue")
                this->child.setGender("male");
            else
                this->child.setGender("female");
            this->child.setGood(randomBetween(0, 1), true);
        }

        Letter(string clr)
        {
            this->color = clr;
            this->wishlist_items = int(randomBetween(1, 9));
            generateWishlist();
            this->child.setFirstName(mock<string>(0));
            this->child.setLastName(mock<string>(1));
            this->child.setCity(mock<string>(2));
            this->child.setBirthYear(mock<int>(0));
            if (this->color == "blue")
                this->child.setGender("male");
            else
                this->child.setGender("female");
            this->child.setGood(randomBetween(0, 1), true);
        }

        // Setters
        void setLetterColor(string clr)
        {
            this->color = clr;
        }

        void setPresent(string pres[103], int no_of_p)
        {
            this->present_no = no_of_p;
            fstream fout;
            string fname = "datasets/Presents/" + this->getFirstName() + this->getLastName() + ".csv";
            fout.open(fname, ios::out);
            //fout<<this->getFirstName()<<","<<this->getLastName()<<"\n";
            for (int i = 1; i <= no_of_p; i++)
            {
                this->present[i] = pres[i];
                //cout << this->present[i] << "\n";
                fout << this->present[i] << "\n";
            }
        }

        // Getters
        Child getChild()
        {
            return child;
        }
        string getFirstName()
        {
            return child.getFirstName();
        }
        string getLastName()
        {
            return child.getLastName();
        }
        int getAge()
        {
            return child.getAge();
        }

        int getWishlistItemNO()
        {
            return this->wishlist_items;
        }

        string getWishlistItem(int i)
        {
            return this->wishlist[i];
        }

        // Methodes
        void generateWishlist()
        {
            string taken_item[100] = {}, name;
            int n = 1;
            for (int i = 1; i <= this->wishlist_items; i++)
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
                this->wishlist[i] = name;
            }
        }

        void showWishlist()
        {
            cout << "\n\nWishlist for " << this->child.getFirstName() << " " << this->child.getLastName() << " has " << this->wishlist_items << " items.\n";
            for (int i = 1; i <= wishlist_items; i++)
                cout << wishlist[i] << "\n";
        }

        void showPresent()
        {
            loadPresent();
            cout << "\nPresent for " << this->child.getFirstName() << " " << this->child.getLastName() << " contains:\n";
            for (int i = 1; i <= this->present_no; i++)
                cout << present[i] << "\n";
        }

        void loadPresent()
        {
            string fname = "datasets/Presents/" + child.getFirstName() + child.getLastName() + ".csv";
            ifstream reader;
            reader.open(fname);
            if (!reader.is_open())
            { // If file does not exist, return 0 lines.
                cout << "Unable to load file!\n";
            }
            string buffer = "";
            int currentLine = 0;
            int line = getFileLines(fname);
            this->present_no = line;
            while (currentLine < line && reader.good())
            {
                getline(reader, buffer);
                this->present[currentLine] = buffer;
                currentLine++;
            }
        }

    private:
        Child child;
        string color;
        string wishlist[11];
        int wishlist_items;
        string present[103];
        int present_no;
    };

    class Elf
    {
    public:
        // Constructors
        Elf()
        {
            total++;
            this->nr_crt = total;
        }

        Elf(Letter l1)
        {
            this->l = l1;
            this->c = l1.getChild();
            total++;
            this->nr_crt = total;
        }

        // Destructors
        ~Elf()
        {
            //cout << "Elf destructed\n";
        }

        // Setters
        void setLetter(Letter l1)
        {
            this->l = l1;
            this->c = l1.getChild();
            this->createPresent(l1);
        }

        // Getters
        Letter getLetter()
        {
            return this->l;
        }

        // Methods

        void createPresent(Letter &l)
        {
            string present[101];
            int pres_ctr = 1;
            double funds = this->c.getFunds();
            //cout<<funds<<"\n";
            string wish;
            bool done_wish = false;
            bool found = false;
            while (funds)
            {
                while (!done_wish && pres_ctr < l.getWishlistItemNO() && !found)
                {
                    wish = l.getWishlistItem(pres_ctr);
                    //cout << "Wish is: " << wish << "\n";
                    for (int i = 1; i <= inv_item_count && !done_wish; i++)
                    {
                        //cout <<"Inv item is: "<<inventory[i].name << "\n";
                        if (inventory[i].name == wish && inventory[i].price <= funds && !done_wish)
                        {
                            present[pres_ctr] = wish;
                            pres_ctr++;
                            inventory[i].nb_pcs--;
                            funds -= inventory[i].price;
                            break;
                            found = true;
                            total_amount += inventory[i].price;
                            //cout<<present[pres_ctr-1]<<"\n";
                        }
                    }
                    if (found)
                    {
                        found = false;
                    }
                    else
                    {
                        found = true;
                        done_wish = true;
                    }
                }
                present[pres_ctr] = "Candy";
                pres_ctr++;
                funds--;
                total_amount++;
                //cout<<present[pres_ctr-1]<<"\n";
            }
            l.setPresent(present, pres_ctr - 1);
        }

    private:
        Letter l;
        Child c;
        int nr_crt = 0;
        int total;
    };

    class Troll
    {
    public:
        // Constructor
        Troll()
        {
            this->nr_crt++;
            total_no++;
        }

        Troll(int n)
        {
            this->nr_crt++;
            total_no++;
            this->nb_of_children = n;
        }

        // Destructor
        ~Troll()
        {
            total_no--;
        }

        //Setters
        void setNbOfChildre(int n)
        {
            this->nb_of_children = n;
        }

        // Methods
        void showNbofPacks()
        {
            cout << "Number of boys: " << boys << "\n";
            cout << "Number of girls: " << girls << "\n";
        }

        void actTotalAmount(double i)
        {
            total_amount += i / 2;
            cout << "Total money amount is: " << total_amount << "$\n";
        }

        void setLetter(Letter l1[100])
        {
            for (int i = 0; i < nb_of_children; i++)
            {
                Child c = l1[i].getChild();
                if (c.getGender() == "male")
                    boys++;
                else
                    girls++;
                if (!c.isGood())
                    coals++;
            }
            actTotalAmount(coals);
            showNbofPacks();
        }

    private:
        int nr_crt = 0;
        int girls = 0;
        int boys = 0;
        int total_no = 0;
        int nb_of_children = 0;
        double coals = 0;
    };

    class Santa{
    public:
        // Constructors
        Santa(){

        }
        Santa(string n)
        {
            this->Name = n;
            //no_of_cities = 0;
        }
        Santa(string n, string city_order[], int no_of_cities1)
        {
            this->Name = n;
            no_of_cities = no_of_cities1;
            for (int i = 0; i < no_of_cities; i++)
                road[i] = city_order[i];
        }
        // Destructors
        ~Santa()
        {
        }

        // Setters
        void setName(string n)
        {
            this->Name = n;
        }

        // Getters
        int getRoadElements(){
            return no_of_cities;
        }

        string getIElement(int i){
            return road[i];
        }

        // Methodes
        void showRoad()
        {
            cout << "Santa's road is: \n";
            for (int i = 0; i < no_of_cities; i++)
                cout << road[i] << " ";
            cout << "\n";
        }
        string Name;
        string road[1000];
        int no_of_cities = 0;
    };

    class Mrs_Claus : public Santa{
    public:
        // Constructor
        Mrs_Claus(Santa santa)
        {
            this->s = santa;
            this->n_cities = s.getRoadElements();
            for(int i = 0 ; i < this->n_cities; i++)
                this->road1[i] = s.getIElement(i);
        }

        // Destructor
        ~Mrs_Claus()
        {
        }

        //Setters

        // Methodes
        void showRoad()
        {
            cout << "Santa's road contains: " << n_cities << " cities:\n";
            for (int i = 0; i < n_cities; i++)
                cout << road1[i] << "\n";
            //cout << "\n";
        }
        private:
        int n_cities = 0;
        string road1[1000];
        Santa s;
    };
} // namespace classes