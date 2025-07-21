void PrintTransactionScreen();
struct stClient
{
	string Accountnumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalanc;
	bool MarkClient = false;
};
struct stUsers
{
	string UserName;
	string Password;
	short Permisstion = 0;
	bool MarkUser = 0;
};

enum enMainMenueOption
{
	eListClients = 1,
	eAddNewClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransaction = 6,
	eMenageUsers = 7,
	eExit = 8
};
enum enTransactionMenueOption
{
	eDeposit = 1,
	eWithDraw = 2,
	eTotalBalance = 3,
	MainMenue = 4
};
enum enMenageUsers
{
	eListUser = 1,
	eAddNewUser = 2,
	eDeleteUser = 3,
	eUpdateUser = 4,
	eFindUser = 5,
	eMainMenue = 6
};
stUsers CurrentUser;
void PrintTransactionScreen();
void LoginScreen();
void PrintMenageUserScreen();
void PrintScreenOfProgram();
vector<string> SplitLine(string Line, string Seperator = "#//#")
{
	vector<string> vString;
	short pos = 0;
	string Temp;
	while ((pos = Line.find(Seperator)) != string::npos)
	{
		Temp = Line.substr(0, pos);
		if (Temp != "")
		{
			vString.push_back(Temp);
		}
		Line.erase(0, pos + Seperator.length());
	}
	if (!Line.empty())
	{

		vString.push_back(Line);
	}
	return vString;
}
stClient ConvertVectorToClient(string Line, string Separator)
{
	stClient Client;
	vector<string> vString = SplitLine(Line, Separator);
	Client.Accountnumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalanc = stod(vString[4]);
	return Client;
}

vector<stClient> LoadDataFromFile(string FileName)
{
	vector<stClient> vClient;
	stClient Client;
	fstream MyFile;
	string Line;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			Client = ConvertVectorToClient(Line, "#//#");
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}
/////////////// ClientList///////////////
/// @param vClient
void PrintClientCards(stClient Client)
{
	cout << "| " << left << setw(22) << Client.Accountnumber
		<< "| " << left << setw(8) << Client.PinCode
		<< "| " << left << setw(32) << Client.Name
		<< "| " << left << setw(12) << Client.Phone
		<< "| " << left << setw(14) << Client.AccountBalanc;
}

void PrintClientList()
{
	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	cout << "\t\t\t\tClient List (" << vClient.size() << ") Client(s)";
	cout << "\n________________________________________________";
	cout << "________________________________________________\n";
	cout << "| Account Number" << setw(18);
	cout << "| Pin Code" << setw(13);
	cout << "| Client Name" << setw(28);
	cout << "| Phone" << setw(16);
	cout << "| Balance";
	cout << "\n________________________________________________";
	cout << "________________________________________________\n";
	if (vClient.size() == 0)
	{
		cout << "\t\t\tNo Clients Available In The System !";
	}
	else
	{
		for (stClient C : vClient)
		{
			PrintClientCards(C);
			cout << endl;
		}
		cout << "\n________________________________________________";
		cout << "________________________________________________\n";
	}
}
///////////////ADD New Client///////////////
string ConvertRecordToLine(stClient& Client, string Separator)
{
	string Line;
	Line += Client.Accountnumber + Separator;
	Line += Client.PinCode + Separator;
	Line += Client.Name + Separator;
	Line += Client.Phone + Separator;
	Line += to_string(Client.AccountBalanc);
	return Line;
}
bool IsAccountNameExist(string UserInput, string FileName)
{
	vector<stClient> vClient;
	for (stClient C : vClient)
	{
		if (C.Accountnumber == UserInput)
		{
			return true;
		}
	}
	return false;
}

void AddNewClientToFile(string FileName, string Line)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{

		MyFile << Line << endl;
		MyFile.close();
	}
}

stClient ReadNewClient()
{
	stClient Client;
	cout << "Enter Account Number ? ";
	getline(cin >> ws, Client.Accountnumber);
	while (IsAccountNameExist(Client.Accountnumber, "My Client.txt"))
		;
	{
		cout << "\nClient With [" << Client.Accountnumber << "] Already Exists, Enter Another Account Number ?";
		getline(cin >> ws, Client.Accountnumber);
	}
	cout << "Enter Pin Code :\n";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name :\n";
	getline(cin, Client.Name);
	cout << "Enter Phone :\n";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance :\n";
	cin >> Client.AccountBalanc;
	return Client;
}

stClient UpdateClientDetils(string AccountName)
{
	stClient Client;
	// string AccountName;
	Client.Accountnumber = AccountName;
	cout << "Enter Pin Code :\n";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name :\n";
	getline(cin, Client.Name);
	cout << "Enter Phone :\n";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance :\n";
	cin >> Client.AccountBalanc;
	return Client;
}
void AddNewClient()
{
	stClient Client;
	Client = ReadNewClient();
	AddNewClientToFile("My Client.txt", ConvertRecordToLine(Client, "#//#"));
}
void PrintAddNewClient()
{
	cout << "________________________________________________\n";
	cout << "\t\t Add New Client Screen \n";
	cout << "________________________________________________\n";
	cout << "Adding New Client :\n";
	char Answer;
	do
	{
		AddNewClient();
		cout << "Client Added Successfully, do you Wont To Add More ?[Y/N]\n";
		cin >> Answer;
	} while (tolower(Answer) == 'y');
}

//////////Delet Client//////////////////
string ReadAccountNumber(string msg)
{
	cout << msg << "\n";
	string AccountNumber;
	cin >> AccountNumber;
	return AccountNumber;
}
bool FindAccountNumber(string AccountNumber, stClient& Client, vector<stClient> vClient)
{
	for (stClient C : vClient)
	{
		if (C.Accountnumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
///  With out & fanction will not work!!!!

bool MarkToDelet(string AccountNumber, vector<stClient>& vClient)
{

	for (stClient& C : vClient)
	{
		if (C.Accountnumber == AccountNumber)
		{
			C.MarkClient = true;
			return true;
		}
	}
	return false;
}
void PrintClientCard(stClient& Client)
{
	cout << "The Following Are The Client Details: \n";
	cout << "--------------------------------------------\n";
	cout << setw(20) << "Account Number :" << Client.Accountnumber << "\n";
	cout << setw(20) << "Pin Code: :" << Client.PinCode << "\n";
	cout << setw(20) << "Name :" << Client.Name << "\n";
	cout << setw(20) << "Phone :" << Client.Phone << "\n";
	cout << setw(20) << "Account Balance :" << Client.AccountBalanc << "\n";
	cout << "--------------------------------------------\n";
}
vector<stClient> LoadDataFromVector(string FileName, vector<stClient>& vClient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string Line;
	if (MyFile.is_open())
	{
		for (stClient& C : vClient)
		{
			if (!C.MarkClient)
			{
				Line = ConvertRecordToLine(C, "#//#");
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}
bool DeletClientFromFile(string AccountNumber, stClient& Client, vector<stClient>& vClient)
{

	char Answer;
	if (FindAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);
		cout << "Do You Wont To Delet This  Client y/n ?\n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			// MarkToDelet(AccountNumber, Client, vClient);

			MarkToDelet(AccountNumber, vClient);
			LoadDataFromVector("My Client.txt", vClient);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << AccountNumber << ") is Not Found!!\n";
	}
	return false;
}
void PrintDeletClientScreen()
{
	cout << "--------------------------------------------\n";
	cout << "\t\tDelet Client Screen\n";
	cout << "--------------------------------------------\n";
	string AccountNumber = ReadAccountNumber("Pleac Enter Account Number :\n");
	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	stClient Client;
	DeletClientFromFile(AccountNumber, Client, vClient);
}
//////////Udate Client//////////////
bool UpdateClientFromFile(string AccountNumber, stClient& Client, vector<stClient>& vClient)
{

	char Answer;
	if (FindAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);
		cout << "Do You Wont To Update This  Client y/n ?\n";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			// MarkToDelet(AccountNumber, Client, vClient);
			for (stClient& C : vClient)
			{
				if (C.Accountnumber == AccountNumber)
				{
					C = UpdateClientDetils(AccountNumber);
					break;
				}
			}
			LoadDataFromVector("My Client.txt", vClient);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << AccountNumber << ") is Not Found!!\n";
	}
	return false;
}
void PrintUpdateClientScreen()
{
	cout << "--------------------------------------------\n";
	cout << "\t\t Update Client Screen\n";
	cout << "--------------------------------------------\n";
	string AccountNumber = ReadAccountNumber("Pleac Enter Account Number :\n");
	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	stClient Client;
	UpdateClientFromFile(AccountNumber, Client, vClient);
}
//////////Find Client/////////////
void FindClientScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	stClient Client;
	string AccountNumber = ReadAccountNumber("Pleac Enter Account Number :\n");
	if (FindAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "Client With Account Number (" << AccountNumber << ") is Not Found!!\n";
	}
	// return false;
}
//////Exit screen/////
void ExitScreen()
{
	cout << "--------------------------------------------\n";
	cout << "\t\t Program Ends :-)\n";
	cout << "--------------------------------------------\n";
}
///////transaction Part///////////////////////
///////////Deposite
bool DepositeClaculit(string AccountNumber, double Amount, vector<stClient> vClient)
{
	char Answer;
	cout << "Are You Sure You Want Perfrom This Transaction ? y/n ? \n";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		for (stClient& C : vClient)
		{
			if (C.Accountnumber == AccountNumber)
			{
				C.AccountBalanc += Amount;
				LoadDataFromVector("My Client.txt", vClient);
				cout << "Done Successfully. New balance is : \n";
				cout << "Your New Account Balance IS : " << C.AccountBalanc << "\n";
				return true;
			}
		}
	}
	return false;
}
void PrintDepositScreen()
{
	cout << "--------------------------------------------\n";
	cout << "\t\t Deposit Screen\n";
	cout << "--------------------------------------------\n";
	double Amount = 0;
	stClient Client;
	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	string AccountNumber = ReadAccountNumber("Pleace Enter Account Number");
	while (!FindAccountNumber(AccountNumber, Client, vClient))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber("Pleace Enter Account Number");
	}
	PrintClientCard(Client);
	cout << "Pleace Enter Amount ?\n";
	cin >> Amount;
	DepositeClaculit(AccountNumber, Amount, vClient);
}
/////////withdraw//////
void PrintWithDraw()
{
	cout << "--------------------------------------------\n";
	cout << "\t\t WithDraw Screen\n";
	cout << "--------------------------------------------\n";
	double Amount = 0;
	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	string AccountNumber = ReadAccountNumber("Pleace Enter Account Number :\n");
	stClient Client;
	while (!FindAccountNumber(AccountNumber, Client, vClient))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber("Pleace Enter Account Number");
	}
	PrintClientCard(Client);
	cout << "Pleace Enter Amount ?\n";
	cin >> Amount;
	while (Amount > Client.AccountBalanc)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalanc << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DepositeClaculit(AccountNumber, Amount * (-1), vClient);
}

/////totalBalance////////
void PrintClientTotal(stClient Client)
{
	cout << "| " << left << setw(22) << Client.Accountnumber
		<< "| " << left << setw(32) << Client.Name
		<< "| " << left << setw(14) << Client.AccountBalanc;
}
void TotalBalanceScreen()
{

	vector<stClient> vClient = LoadDataFromFile("My Client.txt");
	cout << "\t\t\t\tClient List (" << vClient.size() << ") Client(s)";
	cout << "\n________________________________________________";
	cout << "________________________________________________\n";
	cout << "| Account Number" << setw(21);
	cout << "| Client Name" << setw(30);
	cout << "| Balance";
	cout << "\n________________________________________________";
	cout << "________________________________________________\n";
	double Total = 0;

	for (stClient Client : vClient)
	{
		PrintClientTotal(Client);
		cout << endl;
		Total += Client.AccountBalanc;
	}
	cout << "\n________________________________________________";
	cout << "________________________________________________\n";

	cout << "\t\t\tTotal Balance : " << Total;
}
///////////////////////////////////////////User Menage////////////////////////////////////////
stUsers ConvertVectorToUser(string Line, string Separtor)
{
	stUsers Users;
	vector<string> vUser = SplitLine(Line, "#//#");
	Users.UserName = vUser[0];
	Users.Password = vUser[1];
	Users.Permisstion = stoi(vUser[2]);
	return Users;
}
string ConverUsersToLineData(stUsers Users, string Seperator)
{
	string Line;
	Line += Users.UserName + Seperator;
	Line += Users.Password + Seperator;
	Line += to_string(Users.Permisstion);
	return Line;
}
vector<stUsers> LoadUsersDataFromFile(string FileName)
{
	string Line;
	vector<stUsers> vUsers;
	stUsers Users;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		while (getline(MyFile, Line))
		{
			Users = ConvertVectorToUser(Line, "#//#");
			vUsers.push_back(Users);
		}
		MyFile.close();
	}
	return vUsers;
}
void LoadDataFromStUser(string Filename, stUsers Users)
{
	fstream MyFile;
	string Line = ConverUsersToLineData(Users, "#//#");
	MyFile.open(Filename, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << Line << endl;
	}
}
void PrintUserList(stUsers Users)
{
	cout << "| " << left << setw(19) << Users.UserName
		<< "| " << setw(13) << Users.Password
		<< "| " << setw(10) << Users.Permisstion;
}
bool FindUserByusernameAndPassword(string UserName, string Password, stUsers& Users)
{
	vector<stUsers> vUsers = LoadUsersDataFromFile("Users.txt");
	for (stUsers U : vUsers)
	{
		if (U.UserName == UserName && U.Password == Password)
		{
			Users = U;
			return true;
		}
	}
	return false;
}
////////////Users List///////////////
void ListUser()
{
	vector<stUsers> vUsers = LoadUsersDataFromFile("Users.txt");
	cout << "\t\tUser List " << vUsers.size() << " User(s)";
	cout << "\n----------------------------------------------------------------\n";
	cout << "| User Name" << setw(20) << " | Password" << setw(18) << "| Perimmstion";
	cout << "\n----------------------------------------------------------------\n";
	for (stUsers U : vUsers)
	{
		PrintUserList(U);
		cout << endl;
	}
	cout << "\n----------------------------------------------------------------\n";
}
/////////Add New User//////////////
bool IsUserExist(string UserName, stUsers& Users)
{
	vector<stUsers> vUsers = LoadUsersDataFromFile("Users.txt");
	for (stUsers U : vUsers)
	{
		if (U.UserName == UserName)
		{
			Users = U;
			return true;
		}
	}
	return false;
}
enum enMinMenuePermission
{
	eAll = -1,
	pListClient = 2,
	pDeleteClient = 4,
	pUpdateClients = 8,
	pFindClient = 16,
	pTranactions = 32,
	pManageUsers = 64
};
short GiveAccessTo(short Permisstion)
{

	char Answer;
	cout << "Do You Want To Give User Full Accses y/n?";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		Permisstion = -1;
	}
	else
	{
		cout << "do You Want To Give Access To :\n\n";

		cout << "Show Client List ? y/n? ";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 1 : Permisstion);
		cout << endl;
		cout << "Add New Client ? y/n ?";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 2 : Permisstion);
		cout << endl;
		cout << "Delet Client? y/n ?";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 4 : Permisstion);
		cout << endl;
		cout << "Update Client? y/n?";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 8 : Permisstion);
		cout << endl;
		cout << "Find Client ? y/n?";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 16 : Permisstion);
		cout << endl;
		cout << "Transection ? y/n ?";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 32 : Permisstion);
		cout << endl;
		cout << "Menage Users? y/n? ";
		cin >> Answer;
		(toupper(Answer) == 'Y' ? Permisstion += 64 : Permisstion);
		cout << endl;
	}
	return Permisstion;
}
stUsers AddUser(stUsers Users)
{
	char Answer;
	cout << "Enter User Name :";
	getline(cin >> ws, Users.UserName);
	while (IsUserExist(Users.UserName, Users))
	{
		cout << "User Name Is exist Try Agein\n";
		getline(cin >> ws, Users.UserName);
	}
	cout << endl;

	cout << "Enter User Password :";
	getline(cin, Users.Password);
	cout << endl;
	Users.Permisstion = GiveAccessTo(Users.Permisstion);
	return Users;
}

void PrintAddNewUserScreen()
{
	stUsers Users;

	cout << "\n--------------------------------------------\n";
	cout << "\t\t Add New User Screen\n";
	cout << "\n--------------------------------------------\n";
	cout << "Adding New User : \n";

	LoadDataFromStUser("Users.txt", AddUser(Users));
}
//////////Delet User////////////
void PrintUserCard(stUsers& Users)
{
	// IsUserExist(Users.UserName);
	cout << "The Follwing Are The User Details : \n";
	cout << "\n--------------------------------------------\n";
	cout << "User Name : " << Users.UserName << "\n";
	cout << "Password : " << Users.Password << "\n";
	cout << "Permissions : " << Users.Permisstion << "\n";
	cout << "\n--------------------------------------------\n";
}
/////&vUsers without& fanction not working!!!!!!!!!!
bool MarkUser(string UserName, vector<stUsers>& vUsers)
// bool MarkUser(string UserName,stUsers &Users, vector<stUsers> vUsers)
{
	for (stUsers& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkUser = 1;
			return true;
		}
	}
	return 0;
}
vector<stUsers> LoadUserDataFromVector(string FileName, vector<stUsers> vUsers)
{
	string Line;
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (stUsers& U : vUsers)
		{
			if (!U.MarkUser)
				// error!!!   if (!MarkUser(UserName, vUsers))
			{
				Line = ConverUsersToLineData(U, "#//#");
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}

bool DeletUser(stUsers& Users, string UserName, vector<stUsers>& vUsers)
{
	char Answer;
	// cout << "Pleace Enter User Name ?\n";
	// cin >> UserName;
	while (!IsUserExist(UserName, Users))
	{
		cout << "User Name Not Found!! Pleace Try Again\n";
		cin >> UserName;
	}
	PrintUserCard(Users);
	cout << "Are You Wont To Delet This User ?\n";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		MarkUser(UserName, vUsers);
		LoadUserDataFromVector("Users.txt", vUsers);
		cout << "User Deleted Seccessfully. \n";
		return true;
	}
	return false;
}
void PrintDeletScreen()
{
	stUsers Users;
	string UserName;
	vector<stUsers> vUsers = LoadUsersDataFromFile("Users.txt");
	cout << "\n--------------------------------------------\n";
	cout << "\t\t Delete User Screen\n";
	cout << "\n--------------------------------------------\n";
	cout << "Pleace Enter User Name ?\n";
	cin >> UserName;
	DeletUser(Users, UserName, vUsers);
}
/////////Update User/////////
stUsers UpdateUserDetails(stUsers Users, string UserName)
{
	Users.UserName = UserName;
	cout << "Enter User Password :";
	getline(cin >> ws, Users.Password);
	cout << endl;
	Users.Permisstion = GiveAccessTo(Users.Permisstion);
	return Users;
}
vector<stUsers> UPdateUser(string FileName, string Username, vector<stUsers>& vUsers)
{

	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		for (stUsers& U : vUsers)
		{
			if (U.UserName == Username)
			{
				U = UpdateUserDetails(U, Username);
				LoadUserDataFromVector("Users.txt", vUsers);
				// break;
			}
		}
		MyFile.close();
	}
	return vUsers;
}
bool UpdateUserDate(string UserName, stUsers& Users, vector<stUsers>& vUsers)
{
	char Answer;
	while (!IsUserExist(UserName, Users))
	{
		cout << "User Name Not Found!! Pleace Try Again\n";
		cin >> UserName;
	}
	PrintUserCard(Users);
	cout << "Are You Wont To Update This User ?\n";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		UPdateUser("User.txt", UserName, vUsers);
		cout << "User Updated Sccessfully\n";
		return true;
	}
	return false;
}
void PrintUpdateUser()
{
	stUsers Users;
	string UserName;
	vector<stUsers> vUsers = LoadUsersDataFromFile("Users.txt");
	cout << "\n--------------------------------------------\n";
	cout << "\t\t Update User Screen\n";
	cout << "\n--------------------------------------------\n";
	cout << "Pleace Enter User Name ?\n";
	cin >> UserName;
	UpdateUserDate(UserName, Users, vUsers);
}
///////Find-User///////////
void FindUserName(string UserName, stUsers Users)
{
	while (!IsUserExist(UserName, Users))
	{
		cout << "User Name Not Found!! Pleace Try Again\n";
		cin >> UserName;
	}
	PrintUserCard(Users);
}
void PrintFindUserScreen()
{
	string UserName;
	stUsers Users;
	cout << "\n--------------------------------------------\n";
	cout << "\t\t Find User Screen\n";
	cout << "\n--------------------------------------------\n";
	cout << "Pleace Enter User Name ?\n";
	cin >> UserName;
	FindUserName(UserName, Users);
}
///////////////////////////////////////////End User Menage////////////////////////////////////////
void PrintMenageUserScreen();
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
short ReadTransactionMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
short ReadMenageUserMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	PrintScreenOfProgram();
}
void GoBackToTransaction()
{
	cout << "\n\nPress any key to go back to Transaction Menue";
	system("pause>0");
	PrintTransactionScreen();
}
void GoBackToMenageUsess()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	PrintMenageUserScreen();
}
bool LoadUserInfo(string Username, string Password)
{
	if (FindUserByusernameAndPassword(Username, Password, CurrentUser))
		return true;
	else
		return false;
}
bool IsHavePermission(short UserChoice)
{
	if (CurrentUser.Permisstion == -1)
	{
		return true;
	}
	return (CurrentUser.Permisstion & UserChoice) == UserChoice;
	// Importint without ()fanction will not return false
}
void AccessDenied()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}
void ProgramFanctions(enMainMenueOption MainMenueOption)
{
	stUsers CurrentUser;
	switch (MainMenueOption)
	{
	case enMainMenueOption::eListClients:
		system("cls");
		(IsHavePermission(enMainMenueOption::eListClients)) ? PrintClientList() : AccessDenied();
		GoBackToMainMenue();

		break;
	case enMainMenueOption::eAddNewClient:
		system("cls");
		(IsHavePermission(enMainMenueOption::eAddNewClient)) ? PrintAddNewClient() : AccessDenied();
		// PrintAddNewClient();
		GoBackToMainMenue();
		break;
	case enMainMenueOption::eDeleteClient:
		system("cls");
		(IsHavePermission(enMainMenueOption::eDeleteClient)) ? PrintDeletClientScreen() : AccessDenied();
		// PrintDeletClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOption::eUpdateClient:
		(IsHavePermission(enMainMenueOption::eUpdateClient)) ? PrintUpdateClientScreen() : AccessDenied();
		GoBackToMainMenue();
		// PrintUpdateClientScreen();
		break;
	case enMainMenueOption::eFindClient:
		(IsHavePermission(enMainMenueOption::eFindClient)) ? FindClientScreen() : AccessDenied();
		GoBackToMainMenue();
		// FindClientScreen();
		break;
	case enMainMenueOption::eTransaction:
		(IsHavePermission(enMainMenueOption::eTransaction)) ? PrintTransactionScreen() : AccessDenied();
		GoBackToMainMenue();
		// PrintTransactionScreen();
		break;
	case enMainMenueOption::eMenageUsers:
		(IsHavePermission(enMainMenueOption::eMenageUsers)) ? PrintMenageUserScreen() : AccessDenied();
		GoBackToMainMenue();
		// PrintMenageUserScreen();
		break;
	case enMainMenueOption::eExit:
		GoBackToMainMenue();
		ExitScreen();
		break;
	}
}
void PrintScreenOfProgram()
{

	cout << "==========================================\n";
	cout << "\t Main Menue Screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delet Client .\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Menage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "==========================================\n";

	ProgramFanctions((enMainMenueOption)ReadMainMenueOption());
}
void TransactionFunction(enTransactionMenueOption TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionMenueOption::eDeposit:
		PrintDepositScreen();
		PrintTransactionScreen();

		break;
	case enTransactionMenueOption::eWithDraw:
		PrintWithDraw();
		PrintTransactionScreen();

		break;
	case enTransactionMenueOption::eTotalBalance:
		TotalBalanceScreen();
		PrintTransactionScreen();

		break;
	case enTransactionMenueOption::MainMenue:
		PrintScreenOfProgram();
		break;
	}
}

void PrintTransactionScreen()
{
	cout << "==========================================\n";
	cout << "\t Transaction Menue Screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Deposit .\n";
	cout << "\t[2] WithDraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menue.\n";
	TransactionFunction((enTransactionMenueOption)ReadTransactionMenueOption());
}
void MenageUsserFunction(enMenageUsers MenageUsers)
{
	switch (MenageUsers)
	{
	case enMenageUsers::eListUser:
		ListUser();
		PrintMenageUserScreen();
		break;
	case enMenageUsers::eAddNewUser:
		PrintAddNewUserScreen();
		PrintMenageUserScreen();
		break;
	case enMenageUsers::eDeleteUser:
		PrintDeletScreen();
		PrintMenageUserScreen();
		break;
	case enMenageUsers::eUpdateUser:
		PrintUpdateUser();
		PrintMenageUserScreen();
		break;
	case enMenageUsers::eFindUser:
		PrintFindUserScreen();
		PrintMenageUserScreen();

		break;
	case enMenageUsers::eMainMenue:
		PrintScreenOfProgram();
		break;
	}
}
void PrintMenageUserScreen()
{
	cout << "==========================================\n";
	cout << "\t Menage Users Menue Screen\n";
	cout << "==========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User .\n";
	cout << "\t[4] Update User Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue .\n";
	MenageUsserFunction((enMenageUsers)ReadMenageUserMenueOption());
}
bool Login(string UserName, string Password)
{
	bool LoginFaild = false;
	do
	{
		cout << "Enter User Name :\n";
		cin >> UserName;
		cout << "Enter Password: \n";
		cin >> Password;

		if (LoginFaild)
		{
			cout << "Invilid UserName/Password !!\nTry Agein\n";
		}
		LoginFaild = !LoadUserInfo(UserName, Password);
	} while (LoginFaild);
	PrintScreenOfProgram();
	return 0;
}

void LoginScreen()
{
	string UserName, Password;
	stUsers Users;
	cout << "==========================================\n";
	cout << "\t Login Screen\n";
	cout << "==========================================\n";

	Login(UserName, Password);
}
int main()
{
	//PrintScreenOfProgram();
	LoginScreen();
	system("pause>0");
	return 0;
}
