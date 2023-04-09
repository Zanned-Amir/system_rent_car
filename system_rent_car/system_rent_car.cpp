#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
// This class stores information about a car, including the car model, maximum power, and mileage.
class car
{
private:
    
	string model;
	int max_power;
	float kilometrage;
public:
	//car(string model, int max_power, float kilometrage) : model(model), max_power(max_power), kilometrage(kilometrage) {};
    string get_model() {
        return model;
    }

    int get_max_power() {
        return max_power;
    }

    float get_kilometrage() {
        return kilometrage;
    }

    void set_model(string m) {
        model = m;
    }

    void set_max_power(int p) {
        max_power = p;
    }

    void set_kilometrage(float kilo) {
        kilometrage = kilo;
    }
};
//This class stores information about a user, including their nameand ID.
class user
{
private:
    string name;
    int id;
public:
    string get_name() {
        return name;
    }
    int  get_id() {
        return id;
    }
    void set_name(string n) {
        name = n;
    }
    void set_cin(int c) {
        id = c;
    }
    void show_user();
    bool existed(int id);
    string add_user();
};
//This class stores information about a rental invoice, including the invoice number, customer name, car model, car number, rental days, and total rental amount.
class invoice{
    private:
    int invoice_number;
    string customer_name;
    string car_model;
    string car_number;
    int rent_days;
    float  total_rent_amount;
    public:
        invoice(int invoice_number, string customer_name, string car_model, int rent_days, float  total_rent_amount):invoice_number(invoice_number),customer_name(customer_name),car_model(car_model),rent_days(rent_days),total_rent_amount(total_rent_amount){}
        int get_invoice_number() {
            return invoice_number;
        }

        string get_customer_name() {
            return customer_name;
        }

        string get_car_model() {
            return car_model;
        }

        string get_car_number() {
            return car_number;
        }

        int get_rent_days() {
            return rent_days;
        }

        float get_total_rental_amount() {
            return total_rent_amount;
        }

        void set_customer_name(string cust_name) {
            customer_name = cust_name;
        }

        void set_car_model(string model) {
            car_model = model;
        }

        void set_car_number(string number) {
            car_number = number;
        }

        void set_rent_days(int days) {
            rent_days = days;
        }

        void set_total_rental_amount(float amount) {
            total_rent_amount = amount;
        }
};
//This class contains methods for managing the rental car system, such as adding cars, showing available cars, reserving cars, generating invoices, and showing invoices.
class rental_system
{   
    private:
    vector<pair <car,bool>> t;
    string user_name;
    string car_number ;
    string model;
    int rent_days;
    int invoice_number;
    float total_rent_amount;
    int free_cars;
    int reserved_cars;
    public:
    rental_system(){
        set_car();
    };
    int login();
    void add_car();
    void show_car();
    void show_car_reserved();
    void show_car_free();
    void set_car();
    void update_car();
    void select_car();
   int calculate_rent();
    void generate_invoice();
    void show_invoices();
   bool  existed_car(string k);
    void unload_data();
    void number_cars();
};
//This function displays a list of all the users stored in the user_data.txt file. It opens the file in input/output mode and reads each line of the file. Then, it extracts the user_name and user_id values from each line and prints them in table format using the setw manipulator to ensure the table is properly formatted. Finally, it closes the file.
void user::show_user() {
    fstream file3;
    string line;
    file3.open("user_data.txt", ios::out | ios::in);

    cout << "\033[1m\033[35m"; // set bold and magenta color
    cout << "----------------------------------------------" << endl;
    cout << "|   User Name    |    User ID    |" << endl;
    cout << "----------------------------------------------" << endl;

    while (getline(file3, line)) {
        int comma1 = line.find(",");
        int comma2 = line.find(",", comma1 + 1);
        string user_name = line.substr(0, comma1);
        string user_id = line.substr(comma1 + 1, comma2 - comma1 - 1);

        // Output user data in table format
        cout << "| " << setw(15) << left << user_name << " | ";
        cout << setw(12) << left << user_id << " |" << endl;
    }

    cout << "----------------------------------------------" << endl;
    cout << "\033[0m"; // reset formatting
    file3.close();
}
//This function adds a new user to the user_data.txt file. It prompts the user to enter the name and ID of the new user. Then, it opens the file in append mode and writes the new user's information to the end of the file in the format name,ID,. Finally, it closes the file and returns the name of the new user.
string user::add_user()
{
    string nam;
    fstream file3;
    file3.open("user_data.txt",ios::app |ios::out | ios::in);
    do {
        int i = 0;
        cout << "user :" << endl;
        cin >> nam;
        name = nam;
        cout << "cin :" << endl;
        cin >> id;
        if (existed(id) != true) { cout<<"existed user"<<endl; }
    } while (existed(id)!=true);
    file3 << nam << "," << id << "," << endl;
    file3.close();
    return nam;
}
//This function generates an invoice for a rental. It first calls the add_user() function to add a new user to the user_data.txt file and stores the returned value in user_name. Then, it reads the current invoice number from a file called int.txt, increments it by 1, and writes the new value back to the file. It stores the incremented value in invoice_number. Next, it calculates the rental cost by calling the calculate_rent() function and stores the result in total. Finally, it writes the invoice information to a file called invoice.txt in the format invoice_number,user_name,model,car_number,rent_days,total. It also displays the invoice information on the screen.
void rental_system::generate_invoice() {
    user u;
    int n=0;
    string user_name = u.add_user();
    string text;
    fstream file;
    fstream file1;
    file.open("int.txt", ios::in | ios::out);
    getline(file, text);
    if (text !="")
        n = stoi(text);
    n = n + 1;
    file1.open("int.txt", ios::in | ios::out);
    file1 << n << endl;
    file1.close();
    invoice_number = n;
    float total = calculate_rent();
    ofstream invoice_file("invoice.txt", ios::app);
    invoice_file << n << ","
        << user_name << ","
        << model << ","
        << car_number << ","
        << rent_days << ","
        << total  << endl;
    invoice_file.close();

    cout << "=======================================================================" << endl;
    cout << "                         INVOICE                   " << endl;
    cout << "=======================================================================" << endl;
    cout << "                                           " << endl;
    cout << "Invoice Number: " << n << endl;
    cout << "Customer Name: " << user_name << endl;
    cout << "Car Model: " << model << endl;
    cout << "Car Number: " << car_number << endl;
    cout << "Rental Days: " << rent_days << endl;
    cout << "Rental Amount: " << total << endl;
    cout << "                                           " << endl;
    cout << "========================================================================" << endl;
    file.close();
  
}
//This function counts the number of free and reserved cars in the rental system. It loops through each element of the vector t, which contains pairs of car objects and a boolean value indicating whether the car is reserved or not. If the boolean value is true, it increments the reserved_cars counter, otherwise it increments the free_cars counter.
void rental_system::number_cars() {
  
    for (int i = 0; i < t.size(); i++) {
        if (t[i].second == true) {
             free_cars++;
        }
        else {
            reserved_cars++;

        }

    }
}
//This function displays a list of all the invoices stored in the invoice.txt file. It opens the file, reads each line of the file, extracts the invoice information from each line, and prints it in table format using the setw manipulator to ensure the table is properly formatted. Finally, it closes the file.
void rental_system::show_invoices() {
    ifstream invoice_file("invoice.txt");
    if (!invoice_file.is_open()) {
        cout << "Unable to open invoice file." << endl;
        return;
    }

    cout << "====================================================================================" << endl;
    cout << setw(10) << "Invoice #" << setw(20) << "Customer Name" << setw(20) << "Car Model" << setw(15) << "Car Number" << setw(15) << "Rent Days" << setw(20) << "Rental Amount" << endl;
    cout << "====================================================================================" << endl;

    string line;
    while (getline(invoice_file, line)) {
        string invoice_number = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1);
        string user_name = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1);
        string model = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1);
        string car_number = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1);
        string rent_days = line.substr(0, line.find(","));
        line = line.substr(line.find(",")+1 );
        string total = line;

        cout << setw(10) << invoice_number << setw(20) << user_name << setw(20) << model << setw(15) << car_number << setw(15) << rent_days << setw(20) << total << endl;
    }

    invoice_file.close();
}
//This function calculates the rental cost for a car. It prompts the user to enter the car number, rental days, and daily cost. Then, it calculates the total rental cost by multiplying the rental days by the daily cost and returns the result.
int rental_system::calculate_rent() {
    float price;
    cout << "__________________________________" << endl;
    cout << "car number :" << endl;
    cin >> car_number;
    cout << "   rent_days : " << endl;
    cin >> rent_days;
    cout << "daily cost   : " << endl;
    cin >> price;
    return ( (float)price * rent_days);
}
// This function verifies if a car is available for rental. It takes two arguments: an integer n representing the index of the car to be checked, and a vector t containing pairs of car objects and a boolean value indicating whether the car is reserved or not. If the boolean value of the n-th element of the vector is true, it returns false, indicating that the car is not available. Otherwise, it returns true, indicating that the car is available.
bool verif2(int n, vector<pair <car, bool>> t) {
    bool test = false;
    if (t[n].second == true) {
        test = true;
        cout << "valided car" << endl;
    }
    else if (t[n].second == false) {
        cout << "invalide car choose again " << endl;
        test = false;
    }

    return test;
}
// This function allows the user to update information about a car that is already in the rental system. The user is prompted to select a car from a list of available cars, and then enter new information for that car, including the model name, maximum power, and kilometrage. The user can also specify whether the car is reserved or not.
void rental_system::update_car() {
    int n, d1;
    float d2;
    bool test;
    string d, answer;
    show_car();
    car k;
    do {
        do {
            cout << "Choose a car to update (enter its number): ";
            cin >> n;
        } while ((n < 0) || (n >= t.size()));
    } while (verif2(n, t) != true);

    cout << "Update model name (skip by entering '-'): ";
    cin.ignore();
    getline(cin, d);
    if (d != "-") {
        t[n].first.set_model(d);
    }

    cout << "Update max power (skip by entering '-'): ";
    cin >> d2;
    if (d2 != -1) {
        t[n].first.set_max_power(d2);
    }

    cout << "Update kilometrage (skip by entering '-'): ";
    cin >> d1;
    if (d1 != -1) {
        t[n].first.set_kilometrage(d1);
    }

    cout << "Is the car reserved (yes/no)? (skip by entering '-'): ";
    cin.ignore();
    getline(cin, answer);
    if (answer == "yes") {
        t[n].second = true;
    }
    else if (answer == "no") {
        t[n].second = false;
    }
}
 // This function prompts the user to select a car from a list, validates the user's input, and sets the selected car's status to "reserved."
void rental_system::select_car()
{    
    int n;
    do {
        do {
            cout << "choose car  n*          :" << endl;
            cin >> n;
        } while ((n < 0) || (n >= t.size()));
    } while (verif2(n,t) != true);
    model = t[n].first.get_model();
    t[n].second = false;

    
}
//This function verifies if a given password matches the password stored in a file. It returns a boolean value indicating if the password is valid or not.
bool verif(string pass) {
    bool  j;
    string test;
    ifstream file("pass.txt");
    getline(file, test);
    test == pass ?j= true:  j= false ;
    return j;
}
//Reads car data from "data_car.txt" and creates pairs of car objects and their rental status, then adds them to a vector.
void rental_system::set_car() {
    fstream file;
    string line;
    car c;
    file.open("data_car.txt");
    while (getline(file, line)) {
        int comma1 = line.find(",");
        int comma2 = line.find(",", comma1 + 1);
        int comma3 = line.find(",", comma2 + 1);
        c.set_model(line.substr(0, comma1));
        c.set_max_power(stoi(line.substr(comma1 + 1, comma2 - comma1 - 1)));
        c.set_kilometrage(stof(line.substr(comma2 + 1, comma3 - comma2 - 1)));
        bool rental_status = (line.substr(comma3 + 1, line.size() - comma3 - 2) == "1");
        t.push_back(make_pair(c, rental_status));
    }
    file.close();
}
// This function displays a list of all  free (not rented) cars available in the rental system,
void rental_system::show_car_free() {
    fstream file;
    file.open("cars_not_reserved.txt", ios::trunc| ios::in | ios::out);
    cout << "\033[1m\033[33m"; // set bold and yellow color
    cout << "free cars :" << endl;
    cout << free_cars << endl;
    cout << "_______________________________________________________" << endl;
    cout << left << setw(6) << "| n* " << left << setw(6) << "| model" << left << setw(28) << "| max_power" << left << setw(18) << "| kilometrage" << "|" << endl;
    cout << "________________________________________________________" << endl;
    for (int i = 0; i < t.size(); i++) {
        if (t[i].second == true) {
            cout << left << setw(6) << "| " + to_string(i) << left << setw(6) << "| " + t[i].first.get_model() << left << setw(28) << "| " + to_string(t[i].first.get_max_power()) << left << setw(18) << "| " + to_string(t[i].first.get_kilometrage()) << "|" << endl;
            cout << "________________________________________________________" << endl;
            file << t[i].first.get_model() << "," << t[i].first.get_max_power() << "," << t[i].first.get_kilometrage() << "," << t[i].second << "," << endl;
        }
    }
    cout << "\033[0m"; // reset formatting
    file.close();
}
// This function displays a list of all cars available in the rental system, along with their model, maximum power, kilometrage, and rental status (rented or not rented).
void rental_system::show_car() {
    cout << "cars :" << endl;
    cout << reserved_cars + free_cars << endl;
    cout << "________________________________________________________________________" << endl;
    cout << left << setw(6) << "| n* " << left << setw(6) << "| model" << left << setw(28) << "  | max_power" << left << setw(18) << "  | kilometrage" << "  | available" << "|" <<endl;
    cout << "________________________________________________________________________" << endl;
    for (int i = 0; i < t.size(); i++) {
        cout << left << setw(6) << "| " + to_string(i) << left << setw(6) << "| " + t[i].first.get_model() << left << setw(28) << "| " + to_string(t[i].first.get_max_power()) << left << setw(18) << "| " + to_string(t[i].first.get_kilometrage()) << "|";
        if (t[i].second == true) { 
        cout << "\033[1m\033[32m";
        cout << " yes" << endl;
        cout << "\033[0m";
            }
        else {
            cout << "\033[1m\033[31m"; 
            cout << " no " << endl;
            cout << "\033[0m";
        }
            cout << "________________________________________________________________________" << endl;
        
    }
}
//- This function displays a list of all cars that are currently reserved in the rental system, along with their model, maximum power, and kilometrage.It also saves the list of reserved cars to a file named "cars_reserved.txt".
void rental_system::show_car_reserved() {
    fstream file;
    file.open("cars_reserved.txt", ios::trunc | ios::in | ios::out);
    cout << "\033[1m\033[31m"; // set bold and red color
    cout << "reserved cars :" << endl;
    cout << reserved_cars << endl;
    cout << "_______________________________________________________" << endl;
    cout << left << setw(6) << "| n* " << left << setw(6) << "| model" << left << setw(28) << "| max_power" << left << setw(18) << "| kilometrage" << "|" << endl;
    cout << "________________________________________________________" << endl;
    for (int i = 0; i < t.size(); i++) {
        if (t[i].second == false) {
            cout << left << setw(6) << "| " + to_string(i) << left << setw(6) << "| " + t[i].first.get_model() << left << setw(28) << "| " + to_string(t[i].first.get_max_power()) << left << setw(18) << "| " + to_string(t[i].first.get_kilometrage()) << "|" << endl;
            cout << "________________________________________________________" << endl;
            file << t[i].first.get_model() << "," << t[i].first.get_max_power() << "," << t[i].first.get_kilometrage() << "," << t[i].second << "," << endl;
        }
    }
    cout << "\033[0m"; // reset formatting
    file.close();
}
//  - This function displays a banner for the rental system on the console.
void show() {
    cout << "\033[1m\033[36m"; // set bold and cyan color
    cout << "\t \t" << "                                                               " << endl;
    cout << "\t \t" << "_______________________________________________________________" << endl;
    cout<<"\t \t"<<"_______________________________________________________________" << endl;
    cout<<"\t \t"<<"___ R.E.N.T.A.L. .S.Y.S.T.E.M. .C.A.R. .M.A.N.A.G.E.M.E.N.T. __" << endl;
    cout<<"\t \t"<<"_______________________________________________________________" << endl;
    cout << "\033[0m"; // reset formatting
}

//  - This function allows the user to login to the rental system by entering a password. If the password is correct, the function returns 1, otherwise it returns 0.
int rental_system::login() {
    string pass;
    int k;
    show();
    cout << "\t \t" << "----password:  " << endl;
    cin >> pass;
    if (verif(pass)) {
        k = 1;
        cout << "\033[1m\033[32m"; // set bold and green color
        cout << "\t \t" << "----------------     acces valid      ------------------------" << endl;
        cout << "\033[0m"; // reset formatting
    }
    else {
        k = 0;
        cout << "\033[1m\033[31m"; // set bold and red color
        cout << "\t \t" << "----------------     acces denied     ------------------------" << endl;
        cout << "\033[0m"; // reset formatting
    }
    return k;
}
//  - This function is used to add a new car to the rental system. It prompts the user for the car's model, maximum power, and kilometerage, and then adds the car to the system by creating a new pair consisting of the car object and a boolean value indicating whether the car is currently rented or not. The pair is inserted at the beginning of a vector of pairs representing all cars in the system. The function also writes the car's information to a file called "data_car.txt". The user can choose to add another car or exit the function.
void rental_system::add_car() {
    fstream file1;
    file1.open("data_car.txt",ios::app|ios:: in );
    car c;
    int k1, k2;
    string test, k, answer;
   
        do {
            do {
                int i = 0;
                cout << "\t \t" << "____   insert model  :                                   ______" << endl;
                cin >> k;
         
                if (existed_car(k) == true) { cout << "existed car" << endl; }
            } while (existed_car(k)==true);
            c.set_model(k);
            do {
                cout << "\t \t" << "____   insert max_power  :                                   ______" << endl;
                cin >> k1;
            } while (k1 < 0);
            c.set_max_power(k1);
            do {
                cout << "\t \t" << "____   insert kilometrage  :                                   ______" << endl;
                cin >> k2;
            } while (k2 < 0);
            c.set_kilometrage(k2);

            t.insert(t.begin(), make_pair(c, true));
            file1 << c.get_model() << "," << c.get_max_power() << "," << c.get_kilometrage() <<","<<true <<"," << endl;
            cout << " wanna add anthor car or leave  tab yes or no :" << endl;
            cin >> answer;
        } while (answer == "yes");
    
    file1.close();
}
// this function check if user exist in file user_data.txt  and return bool  
bool rental_system::existed_car(string k) {
    fstream file2;
    string line;
    bool test = false;
    file2.open("data_car.txt", ios::in | ios::out);
    while (getline(file2, line))
    {
        int comma1 = line.find(",", 0);
        string modelc = line.substr(0, comma1);
        if( k==modelc) { test = true; }
    }
    file2.close();
    return test;

}
bool user::existed(int id) {
    fstream  file;
    string line;
    bool test = true;
        file.open("user_data.txt", ios::in | ios::out);
        while (getline(file, line))
        {
          int comma1=line.find(",",0) ;
          int comma2 = line.find(",", comma1 + 1);
          string namec = line.substr(0, comma1);
        int  idc =stoi( line.substr(comma1 + 1, comma2 - comma1 - 1));
        if ( (idc == id)) { test = false; }
          
        }
        file.close();
        return test;

}
//  - This function saves the data of the cars in three different files: "cars_not_reserved.txt", "cars_reserved.txt", and "data.txt".First, it opens the "cars_not_reserved.txt" file and writes the information of the cars that are not reserved in it.Next, it opens the "cars_reserved.txt" file and writes the information of the cars that are reserved in it.Finally, it opens the "data.txt" file and writes the information of all the cars in it.The information of each car is saved in the format "model,max_power,kilometrage,reserved".
void rental_system::unload_data() {
    fstream file;
    file.open("cars_not_reserved.txt", ios::trunc | ios::in | ios::out);
    for (int i = 0; i < t.size(); i++) {
        if (t[i].second == true) {
            file << t[i].first.get_model() << "," << t[i].first.get_max_power() << "," << t[i].first.get_kilometrage() << "," << t[i].second << "," << endl;
        }

    }
    file.close();
    fstream file1;
    file.open("cars_reserved.txt", ios::trunc | ios::in | ios::out);
    for (int i = 0; i < t.size(); i++) {
        if (t[i].second == false) {
            file1 << t[i].first.get_model() << "," << t[i].first.get_max_power() << "," << t[i].first.get_kilometrage() << "," << t[i].second << "," << endl;
        }

    }
    file1.close();
    fstream file2;
    file2.open("data.txt", ios::trunc | ios::in | ios::out);
    for (int i = 0; i < t.size(); i++) {
            file2 << t[i].first.get_model() << "," << t[i].first.get_max_power() << "," << t[i].first.get_kilometrage() << "," << t[i].second << "," << endl;
      

    }
    file2.close();
}
//function is used to display a menu of options to the userand prompt them to select an option.The function prints the options to the console in different colorsand formats to make them stand out.The user's choice is read from the console and returned as an integer value.
int display() {
    int choice;
    cout << "\033[1m\033[36m"; // set bold and cyan color
    cout << "---------------------------" << endl;
    cout << "|      CAR RESERVATION     |" << endl;
    cout << "---------------------------" << endl << endl;
    cout << "\033[0m"; // reset formatting
    cout << "Please select an option:" << endl << endl;
    cout << "\033[1m\033[32m"; // set bold and green color
    cout << "0. Reserve a car" << endl;
    cout << "1. Add a car" << endl;
    cout << "2. Update a car" << endl;
    cout << "3. Show user" << endl;
    cout << "4. Add user" << endl;
    cout << "5. show_car" << endl;
    cout << "6. show_car_reserved" << endl;
    cout << "7. show_car_free" << endl;
    cout << "8. show_invoices" << endl;
    cout << "9. exited" << endl;
    cout << "\033[0m"; // reset formatting
    cout << endl << "Enter your choice: ";
    cin >> choice;
    cout << endl << "\033[1m\033[33m"; // set bold and yellow color
    cout << "You entered: " << choice << endl;
    cout << "\033[0m"; // reset formatting
    return choice;
}


       
// main programme
int main(){
    string answer;
    user c1;
    rental_system c;
    c.number_cars();
    int test = c.login();
    if (test == 1)
    {
        do {
            int k = display();
            switch (k) {
            case 0:
                c.show_car();
                c.select_car();
                c.generate_invoice();
                break;
            case 1:
                c.add_car();
                break;
            case 2:
                c.update_car();
                break;
            case 3:
                c1.show_user();
                break;
            case 4:
                c1.add_user();
                break;
            case 5:
                c.show_car();

                break;
            case 6:
                c.show_car_reserved();
                break;
            case 7:
                c.show_car_free();
                break;
            case 8:
                c.show_invoices();
                break;
            case 9:
                goto exit;
            default:
                cout << "\033[1m\033[31m"; // set bold and red color
                cout << " wrong number !!!" << endl;
                cout << "\033[0m"; // reset formatting
                break;
            }
            cout << "do you wanna exit tab yes or no" << endl;

            cin >> answer;
        } while (answer != "yes");
        c.unload_data();



    }
    cout << "\033[1m\033[31m"; // set bold and red color
exit:
    cout << "exited " << endl;
    return 0;
    cout << "\033[0m"; // reset formatting
}

