

#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;

        //  Email - robby@gmail.com   Password - robby@123

class shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
    int choice;
    string email, password;

    while(true)
    {
        cout << "\n\n==============================";
        cout << "\n     SUPERMARKET MAIN MENU";
        cout << "\n==============================";
        cout << "\n1. Administrator";
        cout << "\n2. Buyer";
        cout << "\n3. Exit";
        cout << "\nEnter your choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                cout << "\nEnter Email : ";
                cin >> email;
                cout << "Enter Password : ";
                cin >> password;

                if(email == "robby@gmail.com" && password == "robby@123")
                    administrator();
                else
                    cout << "\nInvalid Login!\n";
                break;

            case 2:
                buyer();
                break;

            case 3:
                exit(0);

            default:
                cout << "\nInvalid Choice!";
        }
    }
}

void shopping::administrator()
{
    int choice;

    while(true)
    {
        cout << "\n\n========== ADMIN MENU ==========";
        cout << "\n1. Add Product";
        cout << "\n2. Modify Product";
        cout << "\n3. Delete Product";
        cout << "\n4. Back";
        cout << "\n5. Exit";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                add();
                break;

            case 2:
                edit();
                break;

            case 3:
                rem();
                break;

            case 4:
                return;

            case 5:
                exit(0);

            default:
                cout << "\nInvalid Choice!";
        }
    }
}

void shopping::buyer()
{
    int choice;

    while(true)
    {
        cout << "\n\n========== BUYER MENU ==========";
        cout << "\n1. Buy Product";
        cout << "\n2. Back";
        cout << "\n3. Exit";

        cout << "\nEnter Choice : ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                receipt();
                break;

            case 2:
                return;

            case 3:
                exit(0);

            default:
                cout << "\nInvalid Choice!";
        }
    }
}


void shopping::add()
{
    fstream data;
    int c, token = 0;
    string n;
    float p, d;

    cout << "\nEnter Product Code : ";
    cin >> pcode;

    cout << "\n Enter Product Name : ";
    cin >> pname;

    cout << "\nEnter Price : ";
    cin >> price;

    cout << "\n Enter Discount (%) : ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if(data)
    {
        while(data >> c >> n >> p >> d)
        {
            if(c == pcode)
            {
                token = 1;
                break;
            }
        }
        data.close();
    }

    if(token)
    {
        cout << "\nProduct Code Already Exists!\n";
        return;
    }

    data.open("database.txt", ios::app);

    data << pcode << " "
         << pname << " "
         << price << " "
         << dis << endl;

    data.close();

    cout << "\nProduct Added Successfully!\n";
}

void shopping::edit()
{
    fstream data, temp;
    int key;
    bool found = false;
    int code;
    string name;
    float price1, dis1;

    cout << "\nEnter Product Code to Modify : ";
    cin >> key;

    data.open("database.txt", ios::in);

    if(!data)
    {
        cout << "\nDatabase File Not Found!\n";
        return;
    }

    temp.open("database1.txt", ios::out);

    while(data >> code >> name >> price1 >> dis1)
    {
        if(code == key)
        {
            found = true;

            cout << "\nNew Product Code : ";
            cin >> code;

            cout << "New Product Name : ";
            cin >> name;

            cout << "New Price : ";
            cin >> price1;

            cout << "New Discount : ";
            cin >> dis1;
        }

        temp << code << " "
             << name << " "
             << price1 << " "
             << dis1 << endl;
    }

    data.close();
    temp.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if(found)
        cout << "\nProduct Modified Successfully!\n";
    else
        cout << "\nProduct Not Found!\n";
}

void shopping::rem()
{
    fstream data, temp;
    int key;
    bool found = false;
    int code;
    string name;
    float price1, dis1;

    cout << "\nEnter Product Code to Delete : ";
    cin >> key;

    data.open("database.txt", ios::in);

    if(!data)
    {
        cout << "\nDatabase File Not Found!\n";
        return;
    }

    temp.open("database1.txt", ios::out);

    while(data >> code >> name >> price1 >> dis1)
    {
        if(code == key)
        {
            found = true;
            continue;
        }

        temp << code << " "
             << name << " "
             << price1 << " "
             << dis1 << endl;
    }

    data.close();
    temp.close();

    remove("database.txt");
    rename("database1.txt", "database.txt");

    if(found)
        cout << "\nProduct Deleted Successfully!\n";
    else
        cout << "\nProduct Not Found!\n";
}

void shopping::list()
{
    fstream data;

    data.open("database.txt", ios::in);

    if(!data)
    {
        cout << "\nNo Products Available!\n";
        return;
    }

    cout << "\n\n============================================";
    cout << "\nCode\tName\t\tPrice\tDiscount";
    cout << "\n============================================";

    while(data >> pcode >> pname >> price >> dis)
    {
        cout << "\n"
             << pcode << "\t"
             << pname << "\t\t"
             << price << "\t"
             << dis << "%";
    }

    data.close();
}

void shopping::receipt()
{
    fstream data;

    int arrCode[100];
    int arrQty[100];

    int count = 0;
    char choice;

    float amount;
    float discountAmount;
    float total = 0;

    data.open("database.txt", ios::in);

    if(!data)
    {
        cout << "\nDatabase is Empty!\n";
        return;
    }

    data.close();

    list();

    cout << "\n\nPlace Your Order";

    do
    {
        cout << "\nEnter Product Code : ";
        cin >> arrCode[count];

        cout << "Enter Quantity : ";
        cin >> arrQty[count];

        count++;

        cout << "Do you want to buy another product (Y/N)? ";
        cin >> choice;

    } while(choice == 'Y' || choice == 'y');

    cout << "\n\n===================== RECEIPT =====================";
    cout << "\nCode\tName\tQty\tPrice\tAmount\tAfter Discount";

    for(int i = 0; i < count; i++)
    {
        data.open("database.txt", ios::in);

        while(data >> pcode >> pname >> price >> dis)
        {
            if(pcode == arrCode[i])
            {
                amount = price * arrQty[i];
                discountAmount = amount - (amount * dis / 100);
                total += discountAmount;

                cout << "\n"
                     << pcode << "\t"
                     << pname << "\t"
                     << arrQty[i] << "\t"
                     << price << "\t"
                     << amount << "\t"
                     << discountAmount;
            }
        }

        data.close();
    }

    cout << "\n---------------------------------------------------";
    cout << "\nTOTAL BILL = " << total << endl;
}


int main()
{
    shopping s;
    s.menu();
    return 0;
    
}
