/*This is a hotel billing system, the person who will used this program is the facilitator of the hotel
or the casher. It is use to properly manage all the information about the customers, rooms,
and also to process the payment of the guest.*/
#include <iostream>
#include<fstream>
#include<string>
static bool program_started = true;
bool checkout = false;
using namespace std;

//Declare all the function
void Main_menu();
void book_a_room();
void customer_records();
void check_out();
void reformat_file();
void rooms_alloted();
void modify_records();
void save_file();
void reciept(int room);
void records_to_struct();
void record();
string replaceChar(string str);
int room_available(int room);
void compute_cost(int room);

//For rooms alloted, storage of the occupied rooms number
int occufied_room[11];
//Use to the store the room no. of customer as ID to become a pointer in the struct
int customer_id;

//Create a struct for guest information with an array declaration
struct Customer_info {
    string first, last;
    string address;
    string mob, email;
    string checkindate, checkintime;
    string checkoutdate, checkouttime;
    int room, adults, children, nights;
    int deposit, cost, balance;
} guest[11];

int main() {
    Main_menu();
    return 0;
}
void Main_menu(){
    /*When we terminate our program the struct value will be deleted,
    So we need a file to store all the values. When we run the program this function will read
    the record in "struct record.txt" and put it in the struct*/
    records_to_struct();
    //After getting the record we need to delete all the files in order to prevent duplicate record
    reformat_file();
    //Save it again now base on the struct that we have, this will save struct as outline to the records to struct function
    record();
    //This will save the record to "guest record.txt" and will serve as the customer record
    save_file();
    char option;
    system("clear");
    cout << "      *******************************************"
    << "\n\t\tHOTEL MANAGEMENT SYSTEM"
    << "\n\t\t   * MAIN MENU * "
    << "\n      *******************************************"
    << "\n\n\t\t 1. Book a Room"
    << "\n\t\t 2. Customer Records"
    << "\n\t\t 3. Rooms Alloted"
    << "\n\t\t 4. Check Out"
    << "\n\t\t 5. Modify Records"
    << "\n\t\t 6. Exit"
    << "\n\n      *******************************************"
    << "\n\tEnter your option here : ";
    cin >> option;
    switch (option) {
        case '1':
            book_a_room();
            break;
        case '2':
            customer_records();
            break;
        case '3':
            rooms_alloted();
            break;
        case '4':
            check_out();
            break;
        case '5':
            modify_records();
            break;
        case '6':
            system("clear");
            cout<< "\n\n      *******************************************"
            << "\n\n\t\t    Exited . . ."
            << "\n\n      *******************************************\n\n";
            exit(1);
            break;
        default:
            Main_menu();
    }
}
void book_a_room() {
    char choicedo;
    //Ask for a room number and check if it is available
    do {
    system("clear");
    cout << "      *******************************************"
    << "\n\t\tHOTEL MANAGEMENT SYSTEM"
    << "\n\t\t   * BOOK A ROOM *"
    << "\n      *******************************************\n\n";
        cout << "\t (This will serve as your customer ID)\n";
        cout << "\t Room No.(0 to Exit) : ";
        cin >> customer_id;
        //in case the user wanted to exit
        if(customer_id == 0) Main_menu();
        //Use the room no. as a customer ID to specify which array place she belong
        guest[customer_id].room = customer_id;
    } while(!room_available(guest[customer_id].room));
    //Put that number into the array of occupied room in the same place of itself.
    occufied_room[customer_id] = customer_id;
    cin.ignore();
    cout << "\t Nights : ";
    //get all the necesarry information
    cin>>guest[customer_id].nights;
    cin.ignore();
    cout << "\t First name : ";
    getline(cin, guest[customer_id].first);
    cout << "\t Last name : ";
    getline(cin, guest[customer_id].last);
    cout << "\t Full address : ";
    getline(cin, guest[customer_id].address);
    cout << "\t Mobile No. : ";
    getline(cin, guest[customer_id].mob);
    cout << "\t Email : ";
    getline(cin, guest[customer_id].email);
    cout << "\t Check in date : ";
    getline(cin, guest[customer_id].checkindate);
    cout << "\t Check in time : ";
    getline(cin, guest[customer_id].checkintime);
    cout << "\t Check out date : ";
    getline(cin, guest[customer_id].checkoutdate);
    cout << "\t Check out time : ";
    getline(cin, guest[customer_id].checkouttime);
    cout << "\t Adults : ";
    cin>>guest[customer_id].adults;
    cout << "\t Children : ";
    cin>>guest[customer_id].children;
    //Check if the user wants to settle the payment
    cout<< "\n      *******************************************\n";
    cout << "      Do you want to settle your payment now?(Y/N): ";
    cin >> choicedo;
    if(toupper(choicedo) == 'Y') {
        //Call the receipt function to process the payment
        compute_cost(customer_id);
        reciept(customer_id);
    } else {
        compute_cost(customer_id);
    }
    Main_menu();
}
void customer_records(){
    system("clear");
    char choicce;
    cout << "      *******************************************"
    << "\n\t\tHOTEL MANAGEMENT SYSTEM"
    << "\n\t\t   * CUSTOMER RECORDS *"
    << "\n      *******************************************";
    cout << "\n\tGuest Information: ";
    //call the stored data and open it
    fstream data;
    char word[100];
    data.open("guest record.txt",ios::in);
    if(!data) {
        cout << "File not found." << endl;
        exit(1);
    } else {
        // if the data is found display all the data
        while(!data.eof()) {
            data.getline(word,100);
            cout << word << "\n";
            data.getline(word,100);
            cout << word << "\n";
        }
        data.close();
        cout << "      *******************************************" << endl;
        cout << "\t Press E to exit : ";
        cin >>choicce;
        if(choicce=='e'||choicce=='E') Main_menu();
        else customer_records();
    }
}
void rooms_alloted(){
    system("clear");
    char choice;
    string space;
    cout << "      ********************************************"
    << "\n\t\tHOTEL MANAGEMENT SYSTEM"
    << "\n\t\t   * ROOMS ALLOTTED * "
    << "\n      ********************************************\n\n";
    cout << "\t    1. Display all available rooms\n"
    << "\t    2. Check a specific room\n"
    << "\t    3. Exit\n";
    cout << "\n      ********************************************"
    << "\n\tEnter you option here : ";
    cin >> choice;
    system("clear");
    switch (choice) {
        //Display all available rooms
        case '1':
            cout << "      ********************************************"
            << "\n\t\tHOTEL MANAGEMENT SYSTEM"
            << "\n\t\t   * ROOMS ALLOTTED * "
            << "\n      ********************************************\n\n";
            cout << "\tList of Available rooms:" << endl;
            for(int i = 1; i <= 10; i++) {
                /* as I mentioned above the rooms id are store in occupied_room array in the same position as it number.
                Every rooms/value in array that are not available will have 0 value.
                We will use it as indicator of available rooms*/
                if(occufied_room[i] == 0) {
                    cout << "\n\t   [Room No." << i << "]";
                }
            }
            cout << "\n\n      ********************************************" << endl;
            cout << "\tPress any key to continue" << endl;
            system("read");
            rooms_alloted();
            break;
        //Check a specific room if it is available
        case '2':
            cout << "      ********************************************"
            << "\n\t\tHOTEL MANAGEMENT SYSTEM"
            << "\n\t\t   * ROOMS ALLOTTED * "
            << "\n      ********************************************\n\n";
            int room_nom;
            cout << "\tEnter the room number : ";
            cin >> room_nom;
            for(int i = 1; i <= 10; i++) {
                //Check in the array of occupied_room if the value he entered has a value that is not 0
                if(occufied_room[room_nom] != 0) space = "Occupied";
                else space = "Available";
            }
            cout << "\n\t Room no. [" << room_nom << "] is " << space;
            cout << "\n\n      ********************************************\n\t";
            cout << "Press any key to continue" << endl;
            system("read");
            rooms_alloted();
            break;
        case '3':
            Main_menu();
            break;
        default:
            rooms_alloted();
            break;
    }
}
void check_out() {
    int room;
    while(true) {
        system("clear");
        cout << "      *******************************************"
        << "\n\t\tHOTEL MANAGEMENT SYSTEM"
        << "\n\t\t   * CHECK OUT *"
        << "\n      *******************************************";
        cout << "\n\n\t(Press 0 to Exit)";
        cout << "\n\tEnter room no. : ";
        cin >> room;
        if(room == 0) break;
        //check if the rooms are avaible
        if (guest[room].room != 0 && room <= 10) {
            checkout = true;
            //call the receipt function to process the payment
            reciept(room);
            //to display it again as available room we need to declare the room number as 0
            occufied_room[room] = 0;
            // delete all the data of user in this room
            guest[room] = Customer_info();
            cout << "\tRoom is now Available\n\t" << endl;
            system("read");
        } else {
            cout << "\n      *******************************************";
            cout << "\n\t\tRoom is not occupied" << endl;
            cout << "      *******************************************" << endl;
            system("read");
        }
    }
    Main_menu();
}
void modify_records() {
    int old_room, new_room;
    int child, adult, night;
    bool occupied = false;
    char option;
    system("clear");
    cout << "      ********************************************"
            << "\n\t\tHOTEL MANAGEMENT SYSTEM"
            << "\n\t\t   * MODIFY RECORDS * "
            << "\n      ********************************************\n\n"
            << "\t (Press 0 to exit)"
            << "\n\t Enter room no. : ";
    cin >> old_room;
    if(old_room == 0) Main_menu();
    if(occufied_room[old_room] != 0) {
        child = guest[old_room].children;
        adult = guest[old_room].adults;
        night = guest[old_room].nights;
        do {
            system("clear");
            cout << "      ********************************************"
            << "\n\t\tHOTEL MANAGEMENT SYSTEM"
            << "\n\t\t   * ENTER NEW DATA * "
            << "\n      ********************************************\n\n";
            cout << "\t Enter Room number(0 to exit) : ";
            // this value will become an indicator to where we place all the information
            cin >> new_room;
            if(new_room == 0) Main_menu();
            guest[new_room].room = new_room;
            if(guest[new_room].room == guest[old_room].room) break;
        } while(!room_available(guest[new_room].room));
        occufied_room[new_room] = guest[new_room].room;
        guest[new_room].balance = guest[old_room].balance;
        cout << "\t Nights : ";
        cin>>guest[new_room].nights;
        cin.ignore();
        cout << "\t First name : ";
        getline(cin, guest[new_room].first);
        cout << "\t Last name : ";
        getline(cin, guest[new_room].last);
        cout << "\t Full address : ";
        getline(cin, guest[new_room].address);
        cout << "\t Mobile No. : ";
        getline(cin, guest[new_room].mob);
        cout << "\t Email : ";
        getline(cin, guest[new_room].email);
        cout << "\t Check in date : ";
        getline(cin, guest[new_room].checkindate);
        cout << "\t Check in time : ";
        getline(cin, guest[new_room].checkintime);
        cout << "\t Check out date : ";
        getline(cin, guest[new_room].checkoutdate);
        cout << "\t Check out time : ";
        getline(cin, guest[new_room].checkouttime);
        cout << "\t Adults : ";
        cin>>guest[new_room].adults;
        cout << "\t Children : ";
        cin>>guest[new_room].children;
        //To prevent adding unnecessary debit
        if(child == 1) child = 2;
        if(adult == 1) adult = 2;
        //get the added person
        child = guest[new_room].children - child;
        adult = guest[new_room].adults - adult;
        night = guest[new_room].nights - night;
        //we will only add payment if the guest is more than two as we can see on the data gathered
        if(child > 0) child *= 150;
        else child = 0;
        if(adult > 0) adult *= 400;
        else adult = 0;
        if(night > 0) night *= 1200;
        else night = 0;
        // get the total amount of the added balance
        guest[new_room].balance += (child  + adult +  night);
        //compute the balance
        reciept(guest[new_room].room);
        cout << "      ********************************************\n"
            << "\tRecord Modified"
            << endl;
        cout << "\tPress any key to continue" << endl;
        system("read");
        if(guest[new_room].room != guest[old_room].room) {
            guest[old_room] = Customer_info();
            occufied_room[old_room] = 0;
        }
        Main_menu();
    } else {
        cout << "\n      *******************************************";
        cout << "\n\t\tRoom is not occupied" << endl;
        cout << "      *******************************************" << endl;
        system("read");
        modify_records();
    }
}
void reformat_file(){
    //Open our customer file and delete all the records
    fstream data;
    data.open("guest record.txt",ios::out | ios::trunc);
    data.close();
    fstream adata;
    adata.open("struct record.txt",ios::out | ios::trunc);
    adata.close();

}
void save_file() {
    ofstream file;//Creates file to store the information of the guests
    file.open("guest record.txt",ios::out | ios::app);
    if(!file) {
        cout << "Error: Cannot open file.\n";
        system("read");
    }
    /*iterate to the occupied_room array and check if the room has value as the indication that it has a guest
    to avoid printing information that has no value to the customer records*/
    for(int i = 1; i <= 10; i ++) {
        if(occufied_room[i] != 0) {
            file << "\n      *******************************************" << endl
            << endl
            << "\t Room No. : " << guest[i].room << endl
            << "\t Balance : " << guest[i].balance << endl
            << "\t Night stay. : " << guest[i].nights << endl
            << "\t The Name of the Guest is: " << guest[i].first << " " << guest[i].last << endl
            << "\t Address : " << guest[i].address << endl
            << "\t Mobile No. : " << guest[i].mob << endl
            << "\t Email : " << guest[i].email << endl
            << "\t Check in date : " << guest[i].checkindate << endl
            << "\t Check in time : " << guest[i].checkintime << endl
            << "\t Check out date : " << guest[i].checkoutdate << endl
            << "\t Check out time : " << guest[i].checkouttime << endl
            <<"\t Adults : "<<guest[i].adults<<endl
            <<"\t Children : "<<guest[i].children<<endl;
        }
    }
    file.close();
}
void reciept(int room){
    //check if the room balance is not greater than 0
    if (guest[room].balance > 0) {
        while (guest[room].balance > 0) {
            system("clear");
            //print the receipt with the total amount in it
            cout << "      ******************************************************************"
            << "\n\t\t\t   HOTEL MANAGEMENT SYSTEM"
            << "\n\t\t\t        * RECIEPT * "
            << "\n      ******************************************************************\n\n";
            cout << "\tRoom No: " << guest[room].room
            << "\n\tArrival: " << guest[room].checkindate << " at " << guest[room].checkintime
            << "\n\tDeparture: " << guest[room].checkoutdate << " at " << guest[room].checkouttime
            << "\n\tGuest Name: " << guest[room].last << " " << guest[room].first
            << "\n\t--------------------------------------------------------------\n"
            << "\tDATE\t\tDESCRIPTION\t\tDEBIT\t\tCREDIT\n\n"
            << "\t"<< guest[room].checkindate <<"\tROOM CHARGES\t\t" << guest[room].balance << endl
            << "\n\t--------------------------------------------------------------\n"
            <<"\t\t\t\t\t\t\tBalance : " << guest[room].balance << endl;
            cout << "\n      ******************************************************************";
            // ask to user for the payment
            cout << "\n\tEnter deposit : ";
            cin >> guest[room].deposit;
            if(guest[room].deposit == 0) break;
            system("clear");
            // display again the receipt with the deducted balance
            guest[room].balance -= guest[room].deposit;
            cout << "      ******************************************************************"
            << "\n\t\t\tHOTEL MANAGEMENT SYSTEM"
            << "\n\t\t\t   * CHECK OUT * "
            << "\n      ******************************************************************\n\n";
            cout << "\tRoom No: " << guest[room].room
            << "\n\tArrival: " << guest[room].checkindate << " at " <<
            guest[room].checkintime
            << "\n\tDeparture: " << guest[room].checkoutdate << " at " <<
            guest[room].checkouttime
            << "\n\tGuest Name: " << guest[room].last << " " << guest[room].first
            << "\n\t--------------------------------------------------------------\n"
            << "\tDATE\t\tDESCRIPTION\t\tDEBIT\t\tCREDIT\n\n"
            << "\t-TODAY- " <<"\tROOM CHARGES\t\t" << guest[room].balance<< "\t\t-" << guest[room].deposit << endl
            << "\n\t--------------------------------------------------------------\n"
            << "\t\t\t\t\t\t\tBalance : " << guest[room].balance << endl;
            cout << "\n      ******************************************************************" << endl;
            cout << "\tPress any key to continue" << endl;
            //If the user wanted to check out, this function will not stop until the guest has 0 balance.
            system("read");
            if(!checkout) break;
        }
    } else {
        cout << "\n      *******************************************";
        cout << "\n\t     Payment already been settled" << endl;
        cout << "      *******************************************" << endl;
        system("read");
    }
    checkout = false;
}
void record() {
    ofstream file;//Creates file to store the information of the guests
    file.open("struct record.txt",ios::out | ios::app);
    if(!file) {
        cout << "Error: Cannot open file.\n";
        system("read");
    }
    //save all the value of the struct into the "struct record.txt" files.
    for(int i = 1; i <= 10; i ++) {
        if(occufied_room[i] != 0) {
            file << guest[i].room << endl
            << guest[i].nights << endl
            //replaceChar is use incase we have a space on the input and we need to replace with a character in order to record it as one text
            << replaceChar(guest[i].first) << endl
            << replaceChar(guest[i].last)  << endl
            << replaceChar(guest[i].address)  << endl
            << guest[i].mob << endl
            << guest[i].email << endl
            << guest[i].checkindate << endl
            << guest[i].checkintime << endl
            << guest[i].checkoutdate << endl
            << guest[i].checkouttime << endl
            << guest[i].adults <<endl
            << guest[i].children << endl
            << guest[i].balance << endl
            << endl;
        }
    }
    file.close();
}
void records_to_struct() {
    //this function need to run only once when the program has started only, to avoid saving the deleted struct when we modified it.
    if(program_started) {
        //Read the "struct record.txt" files and send the value to the struct
        ifstream file;
        file.open("struct record.txt",ios::in);
        /*iterate to the occupied_room array and check if the room has value as the indication that it has a guest
        to avoid printing information that has no value to the customer records*/
        if(!file.eof()) {
            //store all the data of the rooms into the struct in the position of its number.
            for(int i = 1; i <= 10; i ++) {
                file >> guest[i].room
                >> guest[guest[i].room].nights
                >> guest[guest[i].room].first
                >> guest[guest[i].room].last
                >> guest[guest[i].room].address
                >> guest[guest[i].room].mob
                >> guest[guest[i].room].email
                >> guest[guest[i].room].checkindate
                >> guest[guest[i].room].checkintime
                >> guest[guest[i].room].checkoutdate
                >> guest[guest[i].room].checkouttime
                >> guest[guest[i].room].adults
                >> guest[guest[i].room].children
                >> guest[guest[i].room].balance;
                guest[guest[i].room].room = guest[i].room;
                occufied_room[guest[i].room] = guest[i].room;
            }
        }
    file.close();
    program_started = false;
    }
}
string replaceChar(string str) {
  for (int i = 0; i < str.length(); ++i)
    if (isspace((unsigned char)str[i]))
        str[i] = '_';
  return str;
}
int room_available(int room) {
    for(int i = 0; i < 11; i++) {
        if(guest[room].room == occufied_room[i] || room > 10) {
            cout << "\t Room is not available" << endl;
            system("read");
            return 0;
            break;
        }
    }
    return 1;
}
void compute_cost(int room) {
    // this variable store the payment in nights, 1 night = 1200 and 2400 for 2 nights stay. With 4 persons consist of 2 adults and 2 child.
    int room_cost1 = 1200;
    int room_cost2 = 2400;
    //we will add additional amount for the extra person
    if(guest[room].adults > 2) {
        //calculate the total value
        guest[room].cost += ((guest[room].adults -2) * 400);
    }
    if(guest[room].children > 2) {
        guest[room].cost += ((guest[room].children -2) * 150);
    }
    //check the amount of nights and add the correct amount to the customer balance
    if(guest[room].nights == 2) {
        guest[room].cost += room_cost2;
    } else {
        guest[room].cost += room_cost1;
    }
    guest[room].balance = guest[room].cost;
}

