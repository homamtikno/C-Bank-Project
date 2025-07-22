
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip> // this library stored the std::setw
using namespace std;



enum enAtmMainMenue
{
	QuickWithDraw = 1,
	NormalWithDraw = 2,
	Deposit = 3,
	CheckBalance = 4,
	LogOut = 5
};
enum enQuickWithdraw
{
	Twenty = 1,
	Fifty = 2,
	OneHandred = 3,
	TwoHandreds = 4,
	FourHandreds = 5,
	SixHandreads = 6,
	EghitHandreds = 7,
	OneThousand = 8,
	Eexit = 9
};
struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkClient = 0;
};
stClient CurrenntClient;
const string ClientsFileName = "My Client.txt";
///////start/////////////
vector<string> SplitLine(string Line, string Seperator)
{
	vector<string> vString;
	string Temp;
	short Pos;
	while ((Pos = Line.find(Seperator)) != string::npos)
	{
		Temp = Line.substr(0, Pos);
		if (Temp != "")
		{
			vString.push_back(Temp);
		}
		Line.erase(0, Pos + Seperator.length());
	}
	if (!Line.empty())
	{
		vString.push_back(Line);
	}
	return vString;
}
stClient ConvertVectorToClient(string Line, string Seperator)
{
	stClient Client;
	vector<string> vString = SplitLine(Line, "#//#");
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccountBalance = stod(vString[4]);
	return Client;
}
string ConverClientToLine(stClient Client)
{
	string Line;
	Line += Client.AccountNumber + "#//#";
	Line += Client.PinCode + "#//#";
	Line += Client.Name + "#//#";
	Line += Client.Phone + "#//#";
	Line += to_string(Client.AccountBalance);
	return Line;
}
vector<stClient> LoadDataFromFile(string Filename)
{
	string Line;
	vector<stClient> vClient;
	stClient Client;
	fstream MyFile;
	MyFile.open(Filename, ios::in);
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
				Line = ConverClientToLine(C);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}
bool MarkClient(stClient& CurrenntClient, string AccountNumber)
{
	vector<stClient> vClient = LoadDataFromFile(ClientsFileName);
	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			CurrenntClient.MarkClient = true;
			return true;
		}
	}
	return false;
}
short ReadATMChoice()
{
	short Choice;
	cout << "Choose What Do Pou Want To Do ? [1 to 5]?\n";
	cin >> Choice;
	return Choice;
}
bool FindAccountNameAndPassword(string AccountName, string Password, stClient& CurrenntClient)
{
	vector<stClient> vClient = LoadDataFromFile(ClientsFileName);
	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountName && C.PinCode == Password)
		{
			CurrenntClient = C;
			return true;
		}
	}
	return false;
}
////////////QucikWithDraw////////////
short QuickAmount(short Choice)
{
	enQuickWithdraw QuickWithDraw;
	short Amount;
	switch (Choice)
	{
	case enQuickWithdraw::Twenty:
		Amount = -20;
		break;
	case enQuickWithdraw::Fifty:
		Amount = -50;
		break;
	case enQuickWithdraw::OneHandred:
		Amount = -100;
		break;
	case enQuickWithdraw::TwoHandreds:
		Amount = -200;
		break;
	case enQuickWithdraw::FourHandreds:
		Amount = -400;
		break;
	case enQuickWithdraw::SixHandreads:
		Amount = -600;
		break;
	case enQuickWithdraw::EghitHandreds:
		Amount = -800;
		break;
	case enQuickWithdraw::OneThousand:
		Amount = -1000;
		break;
	case enQuickWithdraw::Eexit:
		Amount = -1;

		break;

	default:
		break;
	}
	return Amount;
}

void ConfirmOperation(short Amount)
{
	vector<stClient> vClient = LoadDataFromFile(ClientsFileName);

	char Answer;
	CurrenntClient.AccountBalance += Amount;

	cout << "Are You Sure You Want Perform This Transaction?[y/n]?";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		for (stClient& C : vClient)
		{
			if (C.AccountNumber == CurrenntClient.AccountNumber)
			{
				C.AccountBalance = CurrenntClient.AccountBalance;
				break;
			}
		}
		LoadDataFromVector(ClientsFileName, vClient);
		cout << "Done Successfully Your Balance is " << CurrenntClient.AccountBalance << "\n";
	}
}
bool WithDrawAmount(short Amount)
{
	char Answer;

	if (Amount == -1)
	{
		return 0;
	}
	if (Amount > CurrenntClient.AccountBalance)
	{
		cout << "The Amount exceeds Your Balance, make Another Choice \n";
		return 0;
	}
	ConfirmOperation(Amount);
	return true;
}
void PrintQucikWithDrawScreen()
{
	short Choise;

	// stClient CurrenntClient;
	cout << "\n-------------------------------------------\n";
	cout << "\t\tQuick WithDraw";
	cout << "\n-------------------------------------------\n";
	cout << "\t" << left << setw(15) << "[1] 20" << "[2] 50" << endl;
	cout << "\t" << setw(15) << "[3] 100" << "[4] 200" << endl;
	cout << "\t" << setw(15) << "[5] 400" << "[6] 600" << endl;
	cout << "\t" << setw(15) << "[7] 800" << "[8] 1000" << endl;
	cout << "\t" << setw(15) << "[9] Exit" << endl;
	cout << "\n-------------------------------------------\n";
	cout << "Your Balance is " << CurrenntClient.AccountBalance << "\n";
	cout << "Choose What to Withdraw From [1] to [8] ? ";
	cin >> Choise;
	WithDrawAmount(QuickAmount(Choise));
}

///////////Normal Withdraw////////////
void PrintNormalWithDrawScreen()
{
	short Amount;
	cout << "\n-------------------------------------------\n";
	cout << "\t\t Normal WithDraw";
	cout << "\n-------------------------------------------\n";
	cout << "Enter Amount Multiple of 5's ? ";
	cin >> Amount;
	while (Amount % 5 != 0)
	{
		cout << "Enter Amount Multiple of 5's ? ";
		cin >> Amount;
	}
	WithDrawAmount(Amount);
}
//////////Deposit/////////
void DepositScreen()
{
	short Amount;
	cout << "\n-------------------------------------------\n";
	cout << "\t\t Deposit Screen";
	cout << "\n-------------------------------------------\n";
	cout << "Enter A Positive Deposit Amount ?\n";
	cin >> Amount;
	ConfirmOperation(Amount);
}
/////// Check Balance.///////
void CheckBalanceScreen()
{
	cout << "\n-------------------------------------------\n";
	cout << "\t\t Check Balance Screen ";
	cout << "\n-------------------------------------------\n";
	cout << "Your Balance is :" << CurrenntClient.AccountBalance << "\n";
}
//////////////////////
void Login();
void PrintAtmMainMenueScreen();
void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	PrintAtmMainMenueScreen();
}
/////////ATM SCREEN///////

void PerfromAtmMenueOption(enAtmMainMenue AtmMainMenue)
{
	switch (AtmMainMenue)
	{
	case enAtmMainMenue::QuickWithDraw:
		PrintQucikWithDrawScreen();
		GoBackToMainMenue();
		break;
	case enAtmMainMenue::NormalWithDraw:
		PrintNormalWithDrawScreen();
		GoBackToMainMenue();
		break;
	case enAtmMainMenue::Deposit:
		DepositScreen();
		GoBackToMainMenue();
		break;
	case enAtmMainMenue::CheckBalance:
		CheckBalanceScreen();
		GoBackToMainMenue();
		break;
	case enAtmMainMenue::LogOut:
		cout << "Have A Nice Day ;-)\n";
		// Login();
		break;

	default:
		break;
	}
}
void PrintAtmMainMenueScreen()
{
	cout << "\n-------------------------------------------\n";
	cout << "\t\t ATM Main Menue Screen";
	cout << "\n-------------------------------------------\n";
	cout << "[1] Quick Withdraw.\n";
	cout << "[2] Normal Withdraw.\n";
	cout << "[3] Deposit\n";
	cout << "[4] Check Balance.\n";
	cout << "[5]LogOut. \n";
	cout << "\n-------------------------------------------\n";
	PerfromAtmMenueOption((enAtmMainMenue)ReadATMChoice());
}
///////Login

bool LoadUserInfo(string AccountName, string Password)
{
	if (FindAccountNameAndPassword(AccountName, Password, CurrenntClient))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Login()
{
	string UserName, Password;
	bool LoginFild = false;
	do
	{
		cout << "\n-------------------------------------------\n";
		cout << "\t\tLogin Screen";
		cout << "\n-------------------------------------------\n";
		if (LoginFild)
		{
			cout << "userName Or Password Invild!!\n";
		}
		cout << "Enter Username? ";
		cin >> UserName;

		cout << "Enter Password? ";
		cin >> Password;
		LoginFild = !LoadUserInfo(UserName, Password);

	} while (LoginFild);
	MarkClient(CurrenntClient, UserName);
	PrintAtmMainMenueScreen();
}

int main()
{
	Login();

}
