#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


void MainMenu();
void Transactions_Menu();


const string ClientsFile = "ClinetsFile.txt";

int ReadNumber(string Message)
{
    int Number = 0;
    cout << Message;
    cin >> Number;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
        cout << "Invalid Number , Enter a valid one : " << endl;
        cin >> Number;
    }
    return Number;
}

struct st_ClientInfo
{
    string AcountNumber;
    string PinCode;
    string Name;
    string Phone;
    float Balance;
    bool MarkToDelete = false;
};

enum en_MainMenuOptions
{
    E_show = 1, E_add = 2, E_deletee = 3, E_update = 4, E_find = 5, E_Transactions = 6, E_exit = 7
};

string Read_AcoutNumber()
{
    string AcountNum = "";
    cout << "Enter An Acount Number : ";
    getline(cin >> ws, AcountNum);

    return AcountNum;
}

st_ClientInfo Read_Struct_ClinetInfo()
{
    st_ClientInfo sInfo1;
    
        cout << "\n__________ Read Info : __________\n\n";
        cout << "Enter Acount Number : ";
        getline(cin >> ws, sInfo1.AcountNumber);

        cout << "Enter Pin Code      : ";
        getline(cin, sInfo1.PinCode);
    
        cout << "Enter Your Name     : ";
        getline(cin, sInfo1.Name);
    
        cout << "Enter Your Phone    : ";
        getline(cin, sInfo1.Phone);
    
        cout << "Enter Your Balance  : ";
        cin >> sInfo1.Balance;
        cout << "\n---------------------------------\n";
    
        return sInfo1;
}

string Join_Struct_Info(st_ClientInfo info, string sep = "#//#")
{
    string str = "";

    str += info.AcountNumber + sep;
    str += info.PinCode + sep;
    str += info.Name + sep;
    str += info.Phone + sep;
    str += to_string(info.Balance);

    return str;
}

void Save_OneRecord_ToFile(string FileName, string record)
{
    fstream file;
    file.open(FileName, ios::out | ios::app);

    if (file.is_open())
    {
        file << record << endl;

        file.close();
    }
}

void AddClient()
{
    char a = 'n';
    do
    {
        system("cls");
        cout << "\n\tADDING NEW CLIENT : \n";
        cout << "____________________________________\n";

        Save_OneRecord_ToFile(ClientsFile, Join_Struct_Info(Read_Struct_ClinetInfo()));

        cout << "\nAdded Succesfully, Do You Want To Add More : ";
        cin >> a;

    } while (toupper(a) == 'Y');
}

void ScreenWait()
{
    cout << endl << "\n\nPress Any Key To Go Back...";
    system("pause>0");
}

vector<string> ft_Split(string str, string delm = "#//#")
{
    vector<string> vStrings;
    string Word = "";
    int Pos = 0;

    while ((Pos = str.find(delm)) != str.npos)
    {
        Word = str.substr(0, Pos);
        if (Word != "")
        {
            vStrings.push_back(Word);
        }

        str = str.erase(0, (Pos + delm.length()));
    }

    if (str != "")
    {
        vStrings.push_back(str);
    }

    return vStrings;
}

st_ClientInfo Fill_StructInfo(string line)
{
    vector<string> vStrings = ft_Split(line);
    st_ClientInfo info;

    info.AcountNumber = vStrings[0];
    info.PinCode = vStrings[1];
    info.Name = vStrings[2];
    info.Phone = vStrings[3];
    info.Balance = stoi(vStrings[4]);

    return info;
}

vector<st_ClientInfo> LoadData_FromFile_ToVector()
{
    vector<st_ClientInfo> vData;
    st_ClientInfo info;
    fstream file;
    string Line = "";

    file.open(ClientsFile, ios::in);
    if (file.is_open())
    {
        
        while (getline(file, Line))
        {
            info = Fill_StructInfo(Line);
            vData.push_back(info);
        }

        file.close();
    }

    return vData;
}

void Print_Struct_Info(st_ClientInfo info)
{
    cout << "\t\t|    " << setw(12) << info.AcountNumber << "|" << setw(12) << info.PinCode << "|" << setw(20) << info.Name << "|" <<
        setw(15) << info.Phone << "|" << setw(12) << info.Balance << " |" << endl;
}

void ShowClients()
{
    system("cls");
    vector<st_ClientInfo> vData = LoadData_FromFile_ToVector();
    cout << "\n\n\t\t ________________________________________________________________________________\n";
    cout << "\t\t\t\t\t\t  " << vData.size() << "   Client(s).\n";
    cout << "\t\t|________________________________________________________________________________|\n";
    cout << "\t\t|  Acount Number:|   Pin Code:|       Name :       |   Phone :     |  Balance :  |\n";
    cout << "\t\t|________________________________________________________________________________|\n";

    for (st_ClientInfo& i : vData)
    {
        Print_Struct_Info(i);
    }
    cout << "\t\t|________________________________________________________________________________|\n";
}

bool isClientExists_get_it(string AcountNum, st_ClientInfo &info)
{
    vector<st_ClientInfo> vData = LoadData_FromFile_ToVector();

    for (st_ClientInfo& s : vData)
    {
        if (s.AcountNumber == AcountNum)
        {
            info = s;
            return true;
        }
    }
    return false;
}

void PrintCardOfClinet(st_ClientInfo info)
{
    cout << "\n\nClinet Info : ";
    cout << "\n_________________________\n";
    cout << "Acount Num : " << info.AcountNumber << endl;
    cout << "Pin Code   : " << info.PinCode << endl;
    cout << "Name       : " << info.Name << endl;
    cout << "Phone      : " << info.Phone << endl;
    cout << "Balance    : " << info.Balance << endl;
    cout << "_________________________\n";
}

void Sava_VectorOfStruct_ToFile(vector<st_ClientInfo> vData)
{
    fstream file;

    file.open(ClientsFile, ios::out);

    if (file.is_open())
    {
        string line = "";

        for (st_ClientInfo& s : vData)
        {
            if (s.MarkToDelete == false)
            {
                line = Join_Struct_Info(s);
                file << line << endl;
            }
        }

        file.close();
    }
}

void Mark_Client_For_Delete(vector<st_ClientInfo> &vData, string AcountNum)
{
    for (st_ClientInfo& s : vData)
    {
        if (s.AcountNumber == AcountNum)
        {
            s.MarkToDelete = true;
            return;
        }
    }
}

void DeleteClient()
{
    system("cls");
    cout << "\nDeleting a Client :\n";
    cout << "__________________________________\n";

    string AcountNum = Read_AcoutNumber();
    st_ClientInfo info;
    char ans = 'n';

    vector<st_ClientInfo> vData = LoadData_FromFile_ToVector();

    if (isClientExists_get_it(AcountNum, info))
    {
        PrintCardOfClinet(info);
        cout << endl << "Are You Sure : ";
        cin >> ans;

        if (toupper(ans) == 'Y')
        {
            Mark_Client_For_Delete(vData, AcountNum);
            Sava_VectorOfStruct_ToFile(vData);
            cout << endl << "Deleted\n";
        }
    }
    else
    {
        cout << "\nAcount Number not found\n";
    }
}

st_ClientInfo Read_New_Client_Info_update(string AN)
{
    st_ClientInfo info;
    info.AcountNumber = AN;

    cout << "\n\n__________ Read New Info : __________\n";
    cout << "Enter Pin Code      : ";
    getline(cin >> ws, info.PinCode);

    cout << "Enter Your Name     : ";
    getline(cin, info.Name);

    cout << "Enter Your Phone    : ";
    getline(cin, info.Phone);

    cout << "Enter Your Balance  : ";
    cin >> info.Balance;
    cout << "\n-------------------------------------\n";

    return info;

}

void UpDateClient()
{
    system("cls");
    cout << "\n\tUPDATING CLIENT : \n";
    cout << "--------------------------------\n\n";

    string AcountNumber = Read_AcoutNumber();
    st_ClientInfo info;
    char ans = 'v';

    vector<st_ClientInfo> vData = LoadData_FromFile_ToVector();

    if (isClientExists_get_it(AcountNumber, info))
    {
        PrintCardOfClinet(info);

        cout << endl << "Are You Sure You Want To UpDate it : ";
        cin >> ans;

        if (toupper(ans) == 'Y')
        {
            for (st_ClientInfo& i : vData)
            {
                if (AcountNumber == i.AcountNumber)
                {
                    i = Read_New_Client_Info_update(i.AcountNumber);
                    break;
                }
            }

            Sava_VectorOfStruct_ToFile(vData);
            cout << "\nUpDated Succesuflly\n";
        }
    }
    else
    {
        cout << endl << "Client Does Noot Exists\n";
    }
}

void FindClient()
{
    system("cls");
    cout << "\n\tFinding Clients : \n";
    cout << "__________________________________\n\n";

    string AcoutN = Read_AcoutNumber();
    st_ClientInfo info;

    if (isClientExists_get_it(AcoutN, info))
    {
        PrintCardOfClinet(info);
    }
    else
    {
        cout << endl << endl << "Client Does not Exists.\n";
    }
}

void Exit()
{
    system("cls");
    cout << "\n_____________________________\n\n";
    cout << "\tProgram Ended\n";
    cout << "\n-----------------------------\n";
}

//......

enum en_Transaction_Menu
{
    E_Deposite = 1, E_WithDraw = 2, E_TotalBalances = 3, E_BackMainMenu = 4
};

en_Transaction_Menu Read_TransactionsMenu_Option()
{
    int num = ReadNumber("\n\tEnter Your Option Here [1 -> 4] : ");
    return (en_Transaction_Menu)num;
}

void Increase_And_Decrease_AmountBalance(string Acount, int Amount)
{
    vector<st_ClientInfo> vData = LoadData_FromFile_ToVector();
    int NewBalance = 0;

    for (st_ClientInfo& s : vData)
    {
        if (s.AcountNumber == Acount)
        {
            s.Balance += Amount;
            NewBalance = s.Balance;
            break;
        }
    }
    cout << endl << "New Balance is : " << NewBalance << endl;
    Sava_VectorOfStruct_ToFile(vData);
}

void Deposite()
{
    system("cls");
    cout << "\n---------------------------------\n";
    cout << "\t Deposite Screen :\n";
    cout << "---------------------------------\n\n";

    string AcountNum = Read_AcoutNumber();
    st_ClientInfo info;

    while (!isClientExists_get_it(AcountNum, info))
    {
        cout << "\nClient With Acount Number " << AcountNum << " Not Found, Enter Again : ";
        AcountNum = Read_AcoutNumber();
    }

    PrintCardOfClinet(info);
    int Amount = ReadNumber("\nEnter Deposite Amount : ");

    char ans = 'n';
    cout << endl << "Are You Sure : ";
    cin >> ans;

    if (toupper(ans) == 'Y')
    {
        Increase_And_Decrease_AmountBalance(AcountNum, Amount);
        cout << "\nAdded Successfull\n";
    }
}

void WithDraw()
{
    system("cls");
    cout << "\n---------------------------------\n";
    cout << "\tWith Draw Screen :\n";
    cout << "---------------------------------\n\n";

    string AcountNum = Read_AcoutNumber();
    st_ClientInfo info;

    while (!isClientExists_get_it(AcountNum, info))
    {
        cout << "\nClient With Acount : " << AcountNum << " Not Found, : ";
        AcountNum = Read_AcoutNumber();
    }

    PrintCardOfClinet(info);
    int Amount = ReadNumber("\nEnter With Draw Amount : ");

    while (info.Balance < Amount)
    {
        cout << endl << "Balance is Less Than Amount To Draw it : ";
        Amount = ReadNumber("Enter With Draw Amount : ");
    }

    char ans = 'n';
    cout << endl << "Are You Sure : ";
    cin >> ans;

    if (toupper(ans) == 'Y')
    {
        Increase_And_Decrease_AmountBalance(AcountNum, (Amount*(-1)));
        cout << "\nWith Draw Successfully\n";
    }
}

void ShowTotalBalances()
{
    system("cls");
    vector<st_ClientInfo> vData = LoadData_FromFile_ToVector();
    cout << "\n\n\t\t ________________________________________________________________________________\n";
    cout << "\t\t\t\t\t\t" << vData.size() << "   Client(s).\n";
    cout << "\t\t|________________________________________________________________________________|\n";
    cout << "\t\t|  Acount Number:|   Pin Code:|       Name :       |   Phone :     |  Balance :  |\n";
    cout << "\t\t|________________________________________________________________________________|\n";

    for (st_ClientInfo& i : vData)
    {
        Print_Struct_Info(i);
    }
    cout << "\t\t|________________________________________________________________________________|\n";


    int TotalBalances = 0;
    for (st_ClientInfo& s : vData)
    {
        TotalBalances += s.Balance;
    }

    cout << "\t\t\t\t\t   TOTAL BALANCES : " << TotalBalances << endl;
    cout << "\t\t|________________________________________________________________________________|\n";
}

void Working_TransactionsMenu(en_Transaction_Menu Option)
{
    switch (Option)
    {
    case en_Transaction_Menu::E_BackMainMenu:
        MainMenu();
        break;


    case en_Transaction_Menu::E_Deposite:
        Deposite();
        ScreenWait();
        Transactions_Menu();
        break;


    case en_Transaction_Menu::E_WithDraw:
        WithDraw();
        ScreenWait();
        Transactions_Menu();
        break;


    case en_Transaction_Menu::E_TotalBalances:
        ShowTotalBalances();
        ScreenWait();
        Transactions_Menu();
        break;


    default:
        cout << "\nWrong Choice, maaaaan!!!\n";
        break;
    }
}

void Transactions_Menu()
{
    system("cls");
    cout << "\t\tVersion 1 + Extantions :\n\n";
    cout << "\t=========================================\n";
    cout << "\t\t TRANSACTIONS MAIN MENU : \n";
    cout << "\t=========================================\n";
    cout << "\t\t   [1] Deposite.\n";
    cout << "\t\t   [2] With Draw.\n";
    cout << "\t\t   [3] Total Balances.\n";
    cout << "\t\t   [4] Go Back To Main Menu.\n";
    cout << "\t=========================================\n";

    Working_TransactionsMenu(Read_TransactionsMenu_Option());
}

//......

en_MainMenuOptions Read_Option_MainMenu()
{
    int num = ReadNumber("\n\tEnter Your Option Here [1 -> 7] : ");
    return (en_MainMenuOptions)num;
}

void Wording_MainMenu(en_MainMenuOptions MenuOption)
{
    switch (MenuOption)
    {
    case en_MainMenuOptions::E_add:
        AddClient();
        ScreenWait();
        MainMenu();
        break;


    case en_MainMenuOptions::E_deletee:
        DeleteClient();
        ScreenWait();
        MainMenu();
        break;


    case en_MainMenuOptions::E_show:
        ShowClients();
        ScreenWait();
        MainMenu();
        break;


    case en_MainMenuOptions::E_update:
        UpDateClient();
        ScreenWait();
        MainMenu();
        break;


    case en_MainMenuOptions::E_find:
        FindClient();
        ScreenWait();
        MainMenu();
        break;

    case en_MainMenuOptions::E_Transactions:
        Transactions_Menu();
        break;


    case en_MainMenuOptions::E_exit:
        Exit();
        break;


    default:
        cout << "\nWrong Choice, maaaaan!!!\n";
        break;
    }
}

void MainMenu()
{
    system("cls");
    cout << "\t\t Version 1 + Extantions :\n\n";
    cout << "\t=========================================\n";
    cout << "\t\t     MAIN MENU SCREEN : \n";
    cout << "\t=========================================\n";
    cout << "\t\t   [1] Show Clients.\n";
    cout << "\t\t   [2] Add New Client.\n";
    cout << "\t\t   [3] Delete Client.\n";
    cout << "\t\t   [4] UpDate Client.\n";
    cout << "\t\t   [5] Find Client.\n";
    cout << "\t\t   [6] Transactions Menu.\n";
    cout << "\t\t   [7] Exiiit.\n";
    cout << "\t=========================================\n";

    Wording_MainMenu(Read_Option_MainMenu());
}




int main()
{

    MainMenu();



    return 0;
}