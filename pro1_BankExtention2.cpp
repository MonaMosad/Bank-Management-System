#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


const string ClientsFileName = "Clients.txt";
const string UsersFileName = "users.txt";

enum enProcess
{
	ShowClientList = 1,
	ADD = 2,
	Delete = 3,
	UpDate = 4,
	Search = 5,
	Transation = 6,
	eusertype = 7,
	Exit = 8
};
enum enTransationsType
{
	Deposite = 1,
	WithDraw = 2,
	TotalBalance = 3,
	MainMenue = 4

};
enum enUsersType
{
	listusers = 1,
	addNewUser = 2,
	DeleteUsers = 3,
	updateUsers = 4,
	FindUsers = 5,
	MainMeue = 6

};
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
struct sUsers
{
	string username;
	string password;
	short permission;
	bool MarkForDelete = false;

};

enum enMainMenuePermission
{
	enAll=-1,
	PlistClient=1,
	PAddClient=2,
	PDeleteClient=4,
	PUpdateClient=8,
	PFindClient=16,
	Ptranactions=32,
	PmanageUsers=64
};
sUsers CurrentUser;
void PerformMangeUsersMenueOption(enUsersType enUserTy);
void ShowMainMenue();
void GoToTransationMenue();
void ShowAcessDeniedMessage();
bool CheckAccessPermision(enMainMenuePermission Permission);
void GoBackToMainMeanu();
//start show client and user list

short ReadOperationType(short from ,short to)
{
	short op = 0;


	do
	{
		cout << "Enter Operation Type Number.\n";

		cin >> op;
	} while (op < from || op > to);

	return op;

}

vector <string> SplitString(string s1, string seperator)
{
	vector<string> vString;
	string sword;
	int pos;
	while ((pos = s1.find(seperator)) != std::string::npos)
	{
		sword = s1.substr(0, pos);

		if (sword != "")
		{
			vString.push_back(sword);
			s1.erase(0, pos + seperator.length());
		}
	}  if (s1 != "")
	{
		vString.push_back(s1);

	}
	return vString;
}
sClient ConvertlineToRecord(string line, string seperator = "#//#")
{
	sClient client;
	vector <string> Vclient;
	Vclient = SplitString(line, seperator);
	client.AccountNumber = Vclient[0];
	client.PinCode = Vclient[1];
	client.Name = Vclient[2];
	client.Phone = Vclient[3];
	client.AccountBalance = stod(Vclient[4]);
	return client;
}

sUsers ConvertLineToRecordUsers(string line, string seperator = "#//#")
{
	vector<string> Vusers;
	sUsers User;
	Vusers = SplitString(line, seperator);
	User.username = Vusers[0];
	User.password = Vusers[1];
	User.permission = stoi(Vusers[2]);
	return User;
}

vector <sClient>LoadClientDataFromFile(string filename)
{
	fstream MyFile;
	vector<sClient>vclients;
	MyFile.open(filename, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sClient client;
		while (getline(MyFile, line))
		{
			client = ConvertlineToRecord(line);
			vclients.push_back(client);
		}
		MyFile.close();
	}
	return vclients;

}

vector <sUsers>LoadUserDataFromFile(string filename)
{
	fstream MyFile;
	vector<sUsers>vUsers;
	MyFile.open(filename, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sUsers User;
		while (getline(MyFile, line))
		{
			User = ConvertLineToRecordUsers(line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;

}
void printClientRecord(sClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(15) << Client.AccountBalance;

}
void printUserRecord(sUsers User)
{
	cout << "| " << left << setw(15) << User.username;
	cout << "| " << left << setw(10) << User.password;
	cout << "| " << left << setw(40) << User.permission;
	

}
void ShowAcessDeniedMessage()
{
	cout << "\n____________________________________\n";
	cout << "Access Denied ,\n you dont Have permission to Do this,\nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

void ShowAllClientsScreen()
{
	vector<sClient> Vclients;
	Vclients = LoadClientDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << Vclients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sClient client : Vclients)
	{
		printClientRecord(client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void ShowAllUsersScreen()
{

	if (!CheckAccessPermision(enMainMenuePermission::PlistClient))
	{
		ShowAcessDeniedMessage();
		return;
	}
	vector<sUsers>Vuser;
	Vuser = LoadUserDataFromFile(UsersFileName);
	cout << "\n\t\t\t\t\tClient List (" << Vuser.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(25) << "User Name";
	cout << "| " << left << setw(20) << "Password";
	cout << "| " << left << setw(20) << "permission";
	
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (sUsers user : Vuser)
	{
		printUserRecord(user);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}



// End OF SHOW CLIENT LIST

// End Of Show User List

// Start OF ADD NEW CLIENT
// Start of Add New User

bool ClientExistsByAccountNumber(string accountnumber, string filename)
{
	vector <sClient>Vclient;
	fstream MyFile;
	MyFile.open(filename, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sClient client;
		while (getline(MyFile, line))
		{
			client = ConvertlineToRecord(line);

			if (client.AccountNumber == accountnumber)
			{
				MyFile.close();
				return true;
			}
			Vclient.push_back(client);
		}
		MyFile.close();
	}
	return false;
}


bool UserExistsByUserName(string Username, string filename)
{
	vector <sUsers>vUsers;
	fstream MyFile;
	MyFile.open(filename, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sUsers user;
		while (getline(MyFile, line))
		{
			user = ConvertLineToRecordUsers(line);

			if (user.username==Username)
			{
				MyFile.close();
				return true;
			}
			vUsers.push_back(user);
		}
		MyFile.close();
	}
	return false;
}
int ReadPermissionsToSet()
{
	int permission = 0;
	char answer = 'n';
	cout << "\nDo you want to give full acess? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		return -1;
	cout << "\nDo you want to give acess to: \n ";
	cout << "\nShow Client List? y/n";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::PlistClient;
	cout << "Add New Client? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::PAddClient;
	cout << "\nDelete Client? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::PDeleteClient;
	cout << "\nUpdate Client? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::PUpdateClient;
	cout << "\nFind Client? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::PFindClient;

	cout << "\nTransaction? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::Ptranactions;
	cout << "\nManage Users? y/n?";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
		permission += enMainMenuePermission::PmanageUsers;

	return permission;
}
bool CheckAccessPermision(enMainMenuePermission Permission)
{
	if (CurrentUser.permission == enMainMenuePermission::enAll)
		return true;
	if ((Permission & CurrentUser.permission) == Permission)
		return true;
	else
		return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number?";
	getline(cin >> ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode?";
	getline(cin, Client.PinCode);
	cout << "Enter Name?";
	getline(cin, Client.Name);
	cout << "Enter phone?";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance?";
	cin >> Client.AccountBalance;
	return Client;
}

sUsers ReadNewUser()
{
	sUsers User;
	cout << "Enter User Name";
	getline(cin >> ws, User.username);
	while (UserExistsByUserName(User.username,UsersFileName))
	{
		cout << "\nUser with [" << User.username << "] already exists, Enter another User Name? ";
		getline(cin >> ws, User.username);
	}
	cout << "Enter Password?";
	getline(cin, User.password);
	User.permission = ReadPermissionsToSet();
	return User;
}


string ConvertRecordToLine(sClient Client, string Seperator =
	"#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
string ConvertRecordToLineUsers(sUsers user, string Seperator =
	"#//#")
{
	string stUserRecord = "";
	stUserRecord += user.username + Seperator;
	stUserRecord += user.password + Seperator;
	stUserRecord += to_string(user.permission);
	return stUserRecord;
}


void AddDataToFile(string filename, string stdataline)
{
	fstream Myfile;

	Myfile.open(filename, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << stdataline << endl;

		Myfile.close();

	}
}


void AddNewClient()
{
	sClient client;
	client = ReadNewClient();
	AddDataToFile(ClientsFileName, ConvertRecordToLine(client));
}

void AddNewUser()
{
	sUsers user;
	user = ReadNewUser();
	AddDataToFile(UsersFileName, ConvertRecordToLineUsers(user));
}

void AddClients()
{
	char AddMore = 'Y';

	do
	{
		system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient();
		cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');


}
void AddUsers()
{
	char AddMore = 'Y';

	do
	{
		system("cls");
		cout << "Adding New Users:\n\n";
		AddNewUser();
		cout << "\nUser Added Successfully, do you want to add more Users? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');


}

void ShowAddClientsScreen()
{

	if (!CheckAccessPermision(enMainMenuePermission::PAddClient))
	{
		ShowAcessDeniedMessage();
		return;

	}
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";
	AddClients();
}
void ShowAddUsersScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tAdd New User Screen";
	cout << "\n-----------------------------------\n";
	AddUsers();
}



//END OF ADDING OPERATOR
//End Of Adding Users

//Start OF DELETE 
//Start of delete user
void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

void PrintUserCard(sUsers user)
{
	cout << "\nThe following are the client details:\n";
	cout << "\n	User Name: " << user.username;
	cout << "\nPassword    : " << user.password;
	cout << "\npermission      : " << user.permission;
	
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> Vclient, sClient& client)
{
	for (sClient C : Vclient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			client = C;
			return true;
		}
	}
	return false;
}

bool FindUserByUserName(string Username, vector<sUsers> Vusers, sUsers &user)
{
	for (sUsers C : Vusers)
	{
		if (C.username == Username)
		{
			user = C;
			return true;
		}
	}
	return false;
}

bool FindUserByUsernameAndPassword(string Username,string password, sUsers& user)
{
	vector<sUsers>vUser = LoadUserDataFromFile(UsersFileName);
	for (sUsers C : vUser)
	{
		if (C.username==Username&&C.password==password)
		{
			user = C; 
			return true;
		}
	}
	return false;
}

vector <sClient>SaveClientDataFromFile(string filename, vector <sClient>& Vclients)
{
	fstream Myfile;
	string dataline;
	Myfile.open(filename, ios::out);  //over whrite ->delete all data from file
	if (Myfile.is_open())
	{
		for (sClient c : Vclients)
		{
			if (c.MarkForDelete == false)
			{
				dataline = ConvertRecordToLine(c);
				Myfile << dataline << endl;
			}
		}
		Myfile.close();
	}
	return Vclients;

}

vector <sUsers>SaveUsertDataFromFile(string filename, vector <sUsers>& Vusers)
{
	fstream Myfile;
	string dataline;
	Myfile.open(filename, ios::out);  //over whrite ->delete all data from file
	if (Myfile.is_open())
	{
		for (sUsers c : Vusers)
		{
			if (c.MarkForDelete == false)
			{
				dataline = ConvertRecordToLineUsers(c);
				Myfile << dataline << endl;
			}
		}
		Myfile.close();
	}
	return Vusers;

}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool MarkUserForDeleteByUserName(string username, vector <sUsers>& Vusers)
{
	for (sUsers& C : Vusers)
	{
		if (C.username == username)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteAccountbyAccountNumber(string accountnumber, vector<sClient>& vclient)
{
	sClient client;
	char answer = 'n';
	if (FindClientByAccountNumber(accountnumber, vclient, client))
	{
		PrintClientCard(client);
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(accountnumber, vclient);
			SaveClientDataFromFile(ClientsFileName, vclient);
			vclient = LoadClientDataFromFile(ClientsFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << accountnumber << ") is Not Found!";
		return false;
	}

}

bool DeleteUserbyUserName(string Username, vector<sUsers>& Vusers)
{
	sUsers User;
	char answer = 'n';
	if (FindUserByUserName(Username,Vusers,User))
	{
		if (User.permission == enMainMenuePermission::enAll)
		{

			ShowAcessDeniedMessage();
			return 0;

		}

		PrintUserCard(User);
		cout << "\n\nAre you sure you want delete this user? y/n ? ";
		cin >> answer;
		if (answer == 'Y' || answer == 'y')
		{
			MarkUserForDeleteByUserName(Username, Vusers);
			SaveUsertDataFromFile(UsersFileName, Vusers);
			Vusers = LoadUserDataFromFile(UsersFileName);
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with UserName (" << Username << ") is Not Found!";
		return false;
	}

}


string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

string ReadUserName()
{
	string Username = "";
	cout << "\nPlease enter UserName? ";
	cin >> Username;
	return Username;
}


void ShowDeleteScreen()
{
	if (!CheckAccessPermision(enMainMenuePermission::PDeleteClient))
	{
		ShowAcessDeniedMessage();
		return;

	}
	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient>Vclient = LoadClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteAccountbyAccountNumber(AccountNumber, Vclient);
}

void ShowDeleteUserScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";
	vector<sUsers>Vuser = LoadUserDataFromFile(UsersFileName);
	string username = ReadUserName();
	DeleteUserbyUserName(username, Vuser);
}

//End OF DELETE
// End of User Delete

//srart update
//Start update Users

vector <sClient> SaveCleintsDataToFile(string FileName, vector
	<sClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				//we onl
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}

vector <sUsers> SaveUserDataToFile(string FileName, vector
	<sUsers> vuser)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite
	string DataLine;
	if (MyFile.is_open())
	{
		for (sUsers C : vuser)
		{
			if (C.MarkForDelete == false)
			{
				//we onl
				DataLine = ConvertRecordToLineUsers(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vuser;
}



sClient ReadDataClient(string accountnumber)
{
	sClient Client;
	cout << "Account Number?" << accountnumber << endl;
	Client.AccountNumber = accountnumber;
	cout << "Enter PinCode?";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name?";
	getline(cin, Client.Name);
	cout << "Enter phone?";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance?";
	cin >> Client.AccountBalance;
	return Client;
}
sUsers ReadDataUser(string username)
{
	
	sUsers User;
	cout << "Enter User Name"<<username<<endl;
	User.username = username;
	
	cout << "Enter Password?";
	getline(cin, User.password);
	User.permission = ReadPermissionsToSet();
	return User;
}


bool UpDateClientData(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,
		Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want Update this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{

			for (sClient& c : vClients)
			{
				if (c.AccountNumber == AccountNumber)
				{
					c = ReadDataClient(AccountNumber);
					break;
				}
			}

			SaveCleintsDataToFile(ClientsFileName, vClients);

			//Refresh Clients


			cout << "\n\nClient UpDate Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber
			<< ") is Not Found!";
		return false;
	}
}

bool UpDateUserData(string username, vector<sUsers>& Vusers)
{
	sUsers user;
	char Answer = 'n';
	if (FindUserByUserName(username,Vusers,user))
	{
		PrintUserCard(user);
		cout << "\n\nAre you sure you want Update this user? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{

			for (sUsers& c : Vusers)
			{
				if (c.username == username)
				{
					c = ReadDataUser(username);
					break;
				}
			}

			SaveUserDataToFile(UsersFileName, Vusers);

			//Refresh Clients


			cout << "\n\nUser UpDate Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser with UserName (" << username
			<< ") is Not Found!";
		return false;
	}
}

void ShowUPDateclientscreen()
{

	if (!CheckAccessPermision(enMainMenuePermission::PUpdateClient))
	{
		ShowAcessDeniedMessage();
		return;

	}
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient>Vclient = LoadClientDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpDateClientData(AccountNumber, Vclient);
}

void ShowUPDateUserscreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate User Info Screen";
	cout << "\n-----------------------------------\n";
	vector<sUsers>Vuser = LoadUserDataFromFile(UsersFileName);
	string username = ReadUserName();
	UpDateUserData(username, Vuser);
}
//EndUPDATE
//End UPdate Users
//STERT SEARCH 

//start search users


void ShowFindClientScreen()
{

	if (!CheckAccessPermision(enMainMenuePermission::PFindClient))
	{
		ShowAcessDeniedMessage();
		return;

	}
	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient>vclients = LoadClientDataFromFile(ClientsFileName);
	sClient client;
	string Accountnumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(Accountnumber, vclients, client))
	{
		printClientRecord(client);
	}
	else
	{
		cout << "\nClient with Account Number[" << Accountnumber << "] is not found!";
	}

	//start deposite




}
void ShowFindUsersScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n";
	vector<sUsers>vUsers = LoadUserDataFromFile(UsersFileName);
	sUsers user;
	string UserName = ReadUserName();
	if (FindUserByUserName(UserName,vUsers,user))
	{
		printUserRecord(user);
	}
	else
	{
		cout << "\nClient with User Name[" << UserName << "] is not found!";
	}

}
//end search user
//start deposite

bool DepositAccount(string accountnumber, double deposit, vector<sClient>& Vclient)
{
	sClient client;
	char Answer = 'n';


	cout << "\n\nAre you sure you want perform this Transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{

		for (sClient& c : Vclient)
		{
			if (c.AccountNumber == accountnumber)
			{
				c.AccountBalance += deposit;
				SaveCleintsDataToFile(ClientsFileName, Vclient);
				cout << "\n\nDone Successfully.New Balance is:" << c.AccountBalance;
				return true;
			}
		}

		return false;


	}
}


void Showdepositeclientscreen()
{

	sClient client;
	cout << "\n-----------------------------------\n";
	cout << "\tDeposite Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient>Vclient = LoadClientDataFromFile(ClientsFileName);
	string accountnumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(accountnumber, Vclient, client))
	{
		cout << "\nClient with [" << accountnumber << "] does not exist.\n";
		accountnumber = ReadClientAccountNumber();

	}
	PrintClientCard(client);
	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;
	DepositAccount(accountnumber, Amount, Vclient);
}

//End Deposite

//Start Withdraw


void ShowWithDrawclientscreen()
{
	sClient client;
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient>Vclient = LoadClientDataFromFile(ClientsFileName);
	string accountnumber = ReadClientAccountNumber();
	while (!FindClientByAccountNumber(accountnumber, Vclient, client))
	{
		cout << "\nClient with [" << accountnumber << "] does not exist.\n";
		accountnumber = ReadClientAccountNumber();

	}
	PrintClientCard(client);
	double Amount = 0;
	cout << "\nPlease enter Withdraw amount? ";
	cin >> Amount;
	while (Amount > client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}

	DepositAccount(accountnumber, Amount * -1, Vclient);
}

//End Withdraw

//start totalbalance

void PrintClientRecordBalanceLine(sClient client)
{
	cout << "| " << setw(15) << left << client.AccountNumber;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " << setw(12) << left << client.AccountBalance;
}

void ShowTotalBalances()
{
	vector <sClient>Vclient;
	Vclient = LoadClientDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tBalances List (" << Vclient.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double totalBalance = 0;
	if (Vclient.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (sClient client : Vclient)
		{
			PrintClientRecordBalanceLine(client);
			totalBalance += client.AccountBalance;
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << totalBalance;
}


//ENd TotalBalance

void PerformTransationMenueOption(enTransationsType enTranstionTy)
{
	switch (enTranstionTy)
	{
	case Deposite:
	{
		system("cls");
		Showdepositeclientscreen();
		GoToTransationMenue();
		break;
	}

	case WithDraw:
	{system("cls");
	ShowWithDrawclientscreen();
	GoToTransationMenue();
	break;
	}

	case TotalBalance:
	{system("cls");
	ShowTotalBalances();
	GoToTransationMenue();
	break;
	}

	case MainMenue:
	{
		system("cls");
		ShowMainMenue();
		break;
	}

	}
}

void ShowMangeUsersMenue()
{

	if (!CheckAccessPermision(enMainMenuePermission::PmanageUsers))
	{
		ShowAcessDeniedMessage();
		GoBackToMainMeanu();
		return;

	}
	system("cls");   
	cout << "===========================================\n";  
	cout << "\t\tManage Users Menue Screen\n";  
	cout << "===========================================\n";  
	cout << "\t[1] List Users.\n";  
	cout << "\t[2] Add New User.\n";  
	cout << "\t[3] Delete User.\n";  
	cout << "\t[4] Update User.\n";  
	cout << "\t[5] Find User.\n";  
	cout << "\t[6] Main Menue.\n";  
	cout << "===========================================\n";
	PerformMangeUsersMenueOption((enUsersType)ReadOperationType(1, 6));

}
void GoBackToManageUsersMenue()
{
	cout << "\n\nPress any key to go back to transactions Menue...";
	system("pause>0");
	ShowMangeUsersMenue();
}

void PerformMangeUsersMenueOption(enUsersType enUserTy)
{
	switch (enUserTy)
	{
	case listusers:
	{
		system("cls");
		ShowAllUsersScreen();
		GoBackToManageUsersMenue();
		break;
	}
		
	case addNewUser:
	{
		system("cls");
		ShowAddUsersScreen();
		GoBackToManageUsersMenue();
		break;
	}
		
	case DeleteUsers:
	{
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenue();
		break;
	}
		
	case updateUsers:
	{
		system("cls");
		ShowUPDateUserscreen();
		GoBackToManageUsersMenue();
		break;
	}
		
	case FindUsers:
	{
		system("cls");
		ShowFindUsersScreen();
		GoBackToManageUsersMenue();
		break;
	}
		
	case MainMeue:
	{
		ShowMainMenue();
	}
	
	}
}


void ShowTransactionsMenue()
{

	if (!CheckAccessPermision(enMainMenuePermission::Ptranactions))
	{
		ShowAcessDeniedMessage();
		return;

	}
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";
	PerformTransationMenueOption((enTransationsType)ReadOperationType(1,4));

}


void GoBackToMainMeanu()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoToTransationMenue()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}


void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}

void PerformMainMenueOption(enProcess Options)
{
	switch (Options)
	{
	case enProcess::ShowClientList:
	{
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMeanu();
		break;
	}
	case enProcess::ADD:
	{
		system("cls");
		ShowAddClientsScreen();
		GoBackToMainMeanu();
		break;
	}
	case enProcess::Delete:
	{
		system("cls");
		ShowDeleteScreen();
		GoBackToMainMeanu();
		break;
	}
	case  enProcess::UpDate:
	{
		system("cls");
		ShowUPDateclientscreen();
		GoBackToMainMeanu();
		break;
	}

	case enProcess::Search:

	{
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMeanu();
		break;
	}
	case enProcess::Transation:
	{
		system("cls");
		ShowTransactionsMenue();
		break;

	}
	case enProcess::eusertype:
	{
		system("cls");
		ShowMangeUsersMenue();
		break;
	}
	case enProcess::Exit:
	{
		system("cls");
		ShowEndScreen();
		break;
	}

	}
}
void ShowMainMenue()
{
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] transation.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";
	cout << "===========================================\n";
	PerformMainMenueOption((enProcess)ReadOperationType(1,8));
}

bool LoadUserInfo(string username, string password)
{
	if (FindUserByUsernameAndPassword(username, password, CurrentUser))
		return true;
	else
		return false;

}
void login()
{
	bool loginfaild = false;
	string username, password;
	do
	{
		system("cls");
		cout << "\n---------------------------------\n";     
		cout << "\tLogin Screen";    
		cout << "\n---------------------------------\n";
		if (loginfaild)
		{
			cout << "Invaild Username/Password!\n";
		}
		cout << "Enter Username? ";  
		cin >> username;
		cout << "Enter Password? ";     
		cin >> password;
		loginfaild = !LoadUserInfo(username, password);

	} while (loginfaild);
	ShowMainMenue();
}

int main()
{
	login();
	system("pause>0");
	return 0;
}