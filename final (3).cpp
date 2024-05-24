#include<iostream>
#include<string>		
#include<vector>		// vector
#include<iomanip>		// for std::setw(n), std::setfill(ch), std::left, std::right
#include<sstream>		// stringstrean
#include<fstream>		// file operations
#include<cctype>		// using tolower() function
#include<limits>		// clear buffer
#include<conio.h>		// for _kbhit() and _getch() functions
#include<cstdlib> 		// for exit function
#include<windows.h>
#undef max
using namespace std;


void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// Support functions
string lowercase(const string& str) {
	string result;
	for (char ch : str) {
		result += tolower(ch);
	}
	return result;
}
void clearScreen() {
	std::cout << "\033[2J\033[1;1H";  // ANSI escape sequence to clear screen
}

// Person class
class Person {
private:
	string full_name;
	string date_of_birth;
	string phone_number;
	string email;
	string account;
	string password;
public:
	string type;
	// Constructor
	Person() {
		type = "User";
		full_name = "";
		date_of_birth = "";
		phone_number = "";
		email = "";
		account = "";
		password = "";
	}
	virtual ~Person() {}
	// Getter methods
	string getFullname() {
		return full_name;
	}
	string getDateOfBirth() {
		return date_of_birth;
	}
	string getPhoneNumber() {
		return phone_number;
	}
	string getEmail() {
		return email;
	}
	string getAccount() {
		return account;
	}
	string getPassword() {
		return password;
	}
	// Setter methods (if needed)
	void setFullname(string& name) {
		full_name = name;
	}
	void setDateOfBirth(string& dob) {
		date_of_birth = dob;
	}
	void setPhoneNumber(string& phone) {
		phone_number = phone;
	}
	void setEmail(string& emailAddress) {
		email = emailAddress;
	}
	void setAccount(string& acc) {
		account = acc;
	}
	void setPassword(string& pass) {
		password = pass;
	}
	// Other member functions as needed
	virtual void print_info() {
		std::cout << "\033[33m-------------------------------------\033[0m" << endl;
		std::cout << setw(15) << left << "Loại tài khoản: " << type << endl;
		std::cout << setw(15) << left << "Họ và tên: " << full_name << endl;
		std::cout << setw(15) << left << "Ngày sinh: " << date_of_birth << endl;
		std::cout << setw(15) << left << "Số điện thoại: " << phone_number << endl;
		std::cout << setw(15) << left << "Email: " << email << endl;
		std::cout << setw(15) << left << "Username: " << account << endl;
	}
	virtual void input(vector<Person*>& people) {
		string temp;
		wcout << "Nhập họ và tên: ";
		std::getline(cin, temp);
		setFullname(temp);
		std::cout << "Nhập ngày sinh (dd.mm.yyyy): ";
		std::getline(cin, temp);
		setDateOfBirth(temp);
		std::cout << "Nhập số điện thoại: ";
		std::getline(cin, temp);
		setPhoneNumber(temp);
		std::cout << "Nhập email: ";
		std::getline(cin, temp);
		setEmail(temp);
		std::cout << "Nhập username: ";
		while (1) {
			bool found = false;
			getline(cin, temp);
			for (int i = 0; i < people.size(); i++) {
				if (temp == people[i]->getAccount()) found = true;
			}
			if (found == false) break;
			else cout << "Username đã tồn tại. Xin vui lòng nhập username: ";
		}
		setAccount(temp);
		cout << "Nhập password: ";
		getline(cin, temp);
		setPassword(temp);
	}
};
class Staff : public Person {
private:
	string staff_id;
	string school;
	string department;
public:
	Staff() {
		staff_id = "";
		school = "";
		department = "";
		type = "Staff";
	}
	// Getter
	string getStaffID() {
		return staff_id;
	}
	string getSchool() {
		return school;
	}
	string getDepartment() {
		return department;
	}
	// Setter
	void setStaffID(string& id) {
		staff_id = id;
	}
	void setSchool(string& schoolName) {
		school = schoolName;
	}
	void setDepartment(string& departmentName) {
		department = departmentName;
	}
	//
	void print_info() override {
		Person::print_info();
		cout << setw(15) << left << "Staff ID: " << staff_id << endl;
		cout << setw(15) << left << "Chuyên ngành: " << department << endl;
		cout << setw(15) << left << "Trường: " << school << endl;
	}
	virtual void input(vector<Person*>& people) {
		string temp;
		Person::input(people);
		cout << "Nhập StaffID: ";
		getline(cin, temp);
		setStaffID(temp);
		cout << "Nhập chuyên ngành: ";
		getline(cin, temp);
		setDepartment(temp);
		cout << "Nhập trường: ";
		getline(cin, temp);
		setSchool(temp);
	}
	//
	void createAdminAccount(vector<Person*>& people) {
		cout << "Nhập loại tài khoản (U for User | F for Staff | C for cancel): ";
		while (1) {
			string c; getline(cin, c);
			if (lowercase(c) == "u") {
				Person* ptr = new Person();
				ptr->input(people);
				people.push_back(ptr);
				cout << "Thành công!" << endl;
				return;
			}
			else if (lowercase(c) == "f") {
				Staff* ptr = new Staff();
				ptr->input(people);
				people.push_back(ptr);
				cout << "Thành công!" << endl;
				return;
			}
			else if (lowercase(c) == "c") {
				cout << "Cancel!" << endl;
				return;
			}
			else {
				cout << "Dữ liệu không hợp lệ. Xin hãy thử lại: ";
			}
		}
	}
	void listUser(vector<Person*>& people) {
		cout << "---------------Tài khoản đã tồn tại--------------- " << endl;
		for (int i = 0; i < people.size(); i++) {
			if (people[i]->type == "User") {
				cout << setw(20) << left << "\033[33mUser\033[0m" << people[i]->getAccount() << endl;
				cout << people[i]->getFullname() << endl;
			}
			if (people[i]->type == "Staff") {
				auto staff = dynamic_cast<Staff*>(people[i]);
				cout << setw(20) << left << "\033[31mStaff\033[0m" << staff->getAccount() << endl;
				cout << staff->getFullname() << endl;
				cout << staff->getStaffID() << endl;
				cout << staff->getDepartment() << endl;
				cout << staff->getSchool() << endl;
			}
			cout << "---------------------------------------------" << endl;
		}
	}
	void changePassword(vector<Person*>& people) {
		cout << "Username muốn thay đổi mật khẩu: ";
		string temp; getline(cin, temp);
		for (int i = 0; i < people.size(); i++) {
			if (people[i]->getAccount() == temp && people[i]->type != "Staff") {
				cout << "Đặt password mới: ";
				getline(cin, temp);
				people[i]->setPassword(temp);
				cout << "Thành công!" << endl;
				return;
			}
		}
		cout << "Không tìm được user nào với username đó." << endl;
	}
};

Person* current = nullptr; // Global
vector<Person*> people; // Vector to store Person* objects // Global

// Function to save data to a text file
void writeToFile(const vector<Person*>& people) {
	ofstream outFile("C:\\Users\\ADMIN\\c\\account_list.txt", ios::trunc);
	if (!outFile.is_open()) {
		cerr << "Error: Unable to open file for writing." << endl;
		return;
	}

	for (auto& person : people) {
		outFile << person->type << ",";
		outFile << person->getFullname() << ",";
		outFile << person->getDateOfBirth() << ",";
		outFile << person->getPhoneNumber() << ",";
		outFile << person->getEmail() << ",";
		outFile << person->getAccount() << ",";
		outFile << person->getPassword();
		if (person->type == "Staff") {
			auto staff = dynamic_cast<Staff*>(person);
			outFile << "," << staff->getStaffID() << ",";
			outFile << staff->getSchool() << ",";
			outFile << staff->getDepartment();
		}
		outFile << endl;
	}
	outFile.close();
}

// Function to read data from a text file and append to the vector
void readfile(vector<Person*>& people) {
	for (auto& personPtr : people) {
		delete personPtr;
	}
	people.clear();
	people.shrink_to_fit();
	ifstream inFile("C:\\Users\\ADMIN\\c\\account_list.txt");
	if (!inFile.is_open()) {
		cout << "Error: Unable to open file for reading." << endl;
		return;
	}
	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string type, fullname, dob, phone, email, account, password;

		getline(ss, type, ',');
		getline(ss, fullname, ',');
		getline(ss, dob, ',');
		getline(ss, phone, ',');
		getline(ss, email, ',');
		getline(ss, account, ',');
		getline(ss, password, ',');

		Person* person = nullptr;
		if (type == "User") {
			person = new Person();
			person->setFullname(fullname);
			person->setDateOfBirth(dob);
			person->setPhoneNumber(phone);
			person->setEmail(email);
			person->setAccount(account);
			person->setPassword(password);
		}
		else if (type == "Staff") {
			string staffID, school, department;

			getline(ss, staffID, ',');
			getline(ss, school, ',');
			getline(ss, department);

			Staff* staff = new Staff();
			staff->setFullname(fullname);
			staff->setDateOfBirth(dob);
			staff->setPhoneNumber(phone);
			staff->setEmail(email);
			staff->setAccount(account);
			staff->setPassword(password);
			staff->setStaffID(staffID);
			staff->setSchool(school);
			staff->setDepartment(department);

			person = staff;
		}
		if (person != nullptr) {
			people.push_back(person);
		}

	}
	cout << "Account list loaded!" << endl;
	inFile.close();
}

void createAccount(vector<Person*>& people) {
	cout << "Nhập loại tài khoản (U for User | C for Cancel): ";
	while (1) {
		string c; getline(cin, c);
		if (lowercase(c) == "u") {
			Person* ptr = new Person();
			ptr->input(people);
			people.push_back(ptr);
			cout << "Thành công!" << endl;
			clearScreen();
			return;

		}
		else if (lowercase(c) == "c") {
			cout << "Cancel!" << endl;
			return;
		}
		else {
			cout << "Dữ liệu không hợp lệ. Xin hãy thử lại: ";
		}
	}
}

void asterisk(string& pass) {
	pass = "";
	char ch;
	while (true) {
		ch = _getch(); // Get a character without echoing it to the console

		if (ch == 13) { // Check if the Enter key is pressed
			break;
		}
		else if (ch == 8 && !pass.empty()) { // Check if Backspace is pressed
			cout << "\b \b"; // Move the cursor back, print a space, move back again
			pass.pop_back();
		}
		else if (ch == 127 && !pass.empty()) { // Check if Delete is pressed
			cout << " \b";
			pass.pop_back();
		}
		else if (isprint(ch)) { // Check if the character is printable
			cout << '*';
			pass.push_back(ch);
		}
	}
}

void login(vector<Person*>& people) {
	string u, pass;
	bool access = false;
	while (1) {
		cout << setw(40) << left << "" << "\033[36m----------------------------------------------------------\033[0m" << endl;
		cout << setw(66) << left << "" << "\033[32mĐĂNG NHẬP\033[0m" << endl;
		cout << setw(40) << left << "" << "\033[36m----------------------------------------------------------\033[0m" << endl;
		cout << setw(40) << left << "" << "Username: ";
		getline(cin, u);
		cout << setw(40) << left << "" << "Password: ";
		asterisk(pass);
		for (int i = 0; i < people.size(); i++) {
			if (people[i]->getAccount() == u && people[i]->getPassword() == pass) {
				access = true;
				current = people[i];
			}
		}
		if (access == true) {
			clearScreen();
			cout << "\033[32mĐăng nhập thành công.\033[0m | Chào mừng \033[34m" << current->getAccount() << "\033[0m" << endl;
			cout << "Loại tài khoản: " << "\033[31m" << current->type << "\033[0m" << endl;
			cout << endl;
			return;
		}
		else {
			cout << endl;
			cout << setw(40) << left << "" << "\033[33mUsername hoặc password không hợp lệ. Xin hay thử lại.\033[0m" << endl;
			cout << setw(40) << left << "" << "\033[36m----------------------------------------------------------\033[0m" << endl;
		}
	}
}

// Manga class and relevant functions
class Manga {
public:
	string name;
	vector<string> tag;
	string author;
	string date;
	double rate;
};

vector<Manga> list;		// Vector to store Manga objects // Global

// Function to check the input number
template <typename T>
void inputNumber(T& i) {
	while (1) {
		if (cin >> i) {
			cin.ignore();
			break;
		}
		else {
			// Input failed
			cout << "Dữ liệu không hợp lệ. Xin hãy nhập một số: ";
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
			cin.ignore();
		}
	}
}
void input(Manga& m) {
	cout << "Tên: ";
	getline(cin, m.name);
	cout << "Thể loại: ";
	string tt;
	getline(cin, tt);
	stringstream ss(tt);
	string t;
	while (ss >> t) m.tag.push_back(t);
	cout << "Tác giả: ";
	getline(cin, m.author);
	cout << "Ngày ra mắt: ";
	getline(cin, m.date);
	cout << "Đánh giá: ";
	inputNumber(m.rate);
}
void show(const Manga& m) {
	cout << setfill(' ');
	cout << setw(45) << left << m.name;
	string allTags = m.tag[0];
	for (int i = 1; i < m.tag.size(); i++) {
		allTags += ", ";
		allTags += m.tag[i];
	}
	cout << setw(50) << left << allTags;
	cout << setw(22) << left << m.author;
	cout << setw(20) << left << m.date;
	cout << setw(5) << right << m.rate << endl;
}
void showList(const vector<Manga>& list) {
	if (list.size() == 0) {
		cout << "Empty list!" << endl;
		return;
	}
	cout << setfill(' ');
	cout << setw(2) << left << "" << "| ";
	cout << "\033[31m" << setw(45) << left << "Tên";
	cout << "\033[32m" << setw(50) << left << "Thể loại";
	cout << "\033[33m" << setw(22) << left << "     Tác giả";
	cout << "\033[34m" << setw(20) << left << "        Ngày ra mắt";
	cout << "\033[35m" << setw(5) << right << "        Đánh giá" << endl << "\033[0m";
	for (int i = 0; i < list.size(); i++) {
		cout << setfill(' ') << setw(2) << left << i + 1 << "| ";
		show(list[i]);
	}
}
void add(vector<Manga>& list) {
	cout << "Thêm manga mới..." << endl;
	Manga newManga;
	input(newManga);
	list.push_back(newManga);
}
void remove(vector<Manga>& list) {
	cout << "Chọn ra manga mà bạn muốn xóa: ";
	int n; inputNumber(n);
	if (n > 0 && n < list.size() + 1) {
		list.erase(list.begin() + n - 1);
		cout << "Manga được chọn = " << n << " đã bị xóa." << endl;
	}
	else cout << "Dữ liệu không hợp lệ." << endl;
}
void update(vector<Manga>& list) {
	cout << "Chọn số thứ tự trong list: ";
	int choice; inputNumber(choice);
	if (choice<1 || choice>list.size()) {
		cout << "Dữ liệu không hợp lệ." << endl;
		return;
	}
	else {
		cout << "Cập nhật manga [" << choice << "] " << list[choice - 1].name << endl;
		list[choice - 1].tag.clear();
		list[choice - 1].tag.shrink_to_fit();
		input(list[choice - 1]);
	}
}

vector<Manga> searchbyName(const vector<Manga>& list) {
	vector<Manga> result;
	string keyword;
	cout << "\nTìm theo keyword: ";
	getline(cin, keyword); keyword = lowercase(keyword);
	for (int i = 0; i < list.size(); i++) {
		if (lowercase(list[i].name).find(keyword) != string::npos) {
			result.push_back(list[i]);
		}
	}
	if (!result.size()) {
		cout << "Không tìm được manga nào với keyword đó." << endl;
	}
	showList(result);
	return result;
}
vector<Manga> searchbyTag(const vector<Manga>& list) {
	vector<Manga> result;
	string keyword;
	cout << "\nTìm theo thể loại: ";
	getline(cin, keyword); keyword = lowercase(keyword);
	for (int i = 0; i < list.size(); i++) {
		for (int j = 0; j < list[i].tag.size(); j++) {
			if (lowercase(list[i].tag[j]).find(keyword) != string::npos) {
				result.push_back(list[i]);
				break;
			}
		}
	}
	if (!result.size()) {
		cout << "Không tìm được manga nào với thể loại đó." << endl;
		return list;
	}
	showList(result);
	return result;
}
vector<Manga> searchbyAuthor(const vector<Manga>& list) {
	vector<Manga> result;
	string keyword;
	cout << "\nTìm theo tác giả: ";
	getline(cin, keyword); keyword = lowercase(keyword);
	for (int i = 0; i < list.size(); i++) {
		if (lowercase(list[i].author).find(keyword) != string::npos) {
			result.push_back(list[i]);
		}
	}
	if (!result.size()) {
		cout << "Không tìm được manga nào với tác giả đó" << endl;
		return list;
	}
	showList(result);
	return result;
}
vector<Manga> searchbyYear(const vector<Manga>& list) {
	vector<Manga> result;
	string keyword;
	cout << "\nTìm theo năm ra mắt: ";
	getline(cin, keyword);
	for (int i = 0; i < list.size(); i++) {
		if (list[i].date.find(keyword) != string::npos) {
			result.push_back(list[i]);
		}
	}
	if (!result.size()) {
		cout << "Không tìm được manga nào với năm ra mắt đó." << endl;
		return list;
	}
	showList(result);
	return result;
}
vector<Manga> searchbyRating(const vector<Manga>& list) {
	vector<Manga> result;
	double r;
	cout << "\nTìm manga với đánh giá: ";
	inputNumber(r);
	for (int i = 0; i < list.size(); i++) {
		if (list[i].rate >= r) {
			result.push_back(list[i]);
		}
	}
	if (!result.size()) {
		cout << "Không tìm được manga nào với đánh giá đó." << endl;
		return list;
	}
	showList(result);
	return result;
}
void search(const vector<Manga>& list)
{
here:
	vector<Manga> result = list;
	int Set6[] = { 7,7,7,7,7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;
	for (int i = 0;;)
	{
		gotoxy(5, 16);
		color(Set6[8]);
		cout << "Tiêu chí:" << endl;

		gotoxy(5, 17);
		color(Set6[0]);
		cout << "1. Tên";

		gotoxy(5, 18);
		color(Set6[1]);
		cout << "2. Thể loại";

		gotoxy(5, 19);
		color(Set6[2]);
		cout << "3. Tác giả";

		gotoxy(5, 20);
		color(Set6[3]);
		cout << "4. Năm";

		gotoxy(5, 21);
		color(Set6[4]);
		cout << "5. Đánh giá";

		gotoxy(5, 22);
		color(Set6[5]);
		cout << "6. Cập nhật lại tìm kiếm";

		gotoxy(5, 23);
		color(Set6[6]);
		cout << "0. Cancel";

		gotoxy(5, 24);
		color(Set6[7]);
		cout << "----------------------";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 7))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 6))
		{
			counter++;
		}
		if (key == '\r')//carriage return
		{
			if (counter == 1)
			{
				result = searchbyName(result);
				break;
			}
			if (counter == 2)
			{
				result = searchbyTag(result);
				break;
			}
			if (counter == 3)
			{
				result = searchbyAuthor(result);
				break;
			}
			if (counter == 4)
			{
				result = searchbyYear(result);
				break;
			}
			if (counter == 5)
			{
				result = searchbyRating(result);
				break;
			}
			if (counter == 6)
			{
				result = list;
				cout << "Dữ liệu được cập nhật." << endl;
				break;
			}
			if (counter == 7)
			{
				break;
			}
        }
			Set6[8] = 7;
			Set6[0] = 7;
			Set6[1] = 7;
			Set6[2] = 7;
			Set6[3] = 7;
            Set6[4] = 7;
            Set6[5] = 7;
            Set6[6] = 7;
            Set6[7] = 7;

			if (counter == 1)
			{
				Set6[0] = 12;
			}
			if (counter == 2)
			{
				Set6[1] = 12;
			}
			if (counter == 3)
			{
				Set6[2] = 12;
			}
			if (counter == 4)
			{
				Set6[3] = 12;
			}
			if (counter == 5)
			{
				Set6[4] = 12;
			}
			if (counter == 6)
			{
				Set6[5] = 12;
			}
			if (counter == 7)
			{
				Set6[6] = 12;
			}
	}
}
void readfile(vector<Manga>& list) {
	list.clear();
	list.shrink_to_fit();
	ifstream save("C:\\Users\\ADMIN\\c\\manga_list.txt");
	if (save.is_open()) {
		string line;
		while (getline(save, line)) {
			Manga m;
			m.name = line;
			if (getline(save, line)) {
				stringstream ss(line);
				string t;
				while (ss >> t) m.tag.push_back(t);
			}
			if (getline(save, line)) m.author = line;
			if (getline(save, line)) m.date = line;
			if (getline(save, line)) m.rate = stod(line);
			list.push_back(m);
		}
		cout << "Manga list loaded!" << endl;
	}
	else cout << "Failed to load manga list!" << endl;
	save.close();
}
void writeToFile(const vector<Manga>& list) {
	ofstream output("C:\\Users\\ADMIN\\c\\manga_list.txt", ios::trunc);
	if (output.is_open()) {
		for (const Manga& m : list) {
			// Write each field of the Manga object to the file
			output << m.name << endl;
			// Write tags with spaces between them
			for (const string& tag : m.tag) {
				output << tag << ' ';
			}
			output << endl;
			output << m.author << endl;
			output << m.date << endl;
			output << m.rate << endl;
		}
		cout << endl << "Dữ liệu đã được lưu." << endl;
	}
	else {
		cout << "Unable to open manga_list.txt for writing." << endl;
	}
	output.close();
}

void start(vector<Person*>& people) {
here:
	int Set[] = { 7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;
	for (int i = 0;;)
	{
		gotoxy(55, 19);
		color(Set[4]);
		cout << "---------MENU---------";


		gotoxy(55, 20);
		color(Set[0]);
		cout << "|1. Dang nhap        |";

		gotoxy(55, 21);
		color(Set[1]);
		cout << "|2. Tao tai khoan moi|";

		gotoxy(55, 22);
		color(Set[2]);
		cout << "|3. Exit             |";

		gotoxy(55, 23);
		color(Set[3]);
		cout << "----------------------";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 5))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4))
		{
			counter++;
		}
		if (key == '\r')//carriage return
		{
			if (counter == 1)
			{
				// if enter is click and highlight is on 1 the program will run the code here
				clearScreen();
				login(people);
				break;
			}
			if (counter == 2)
			{
				clearScreen();
				cout << "\033[36mTạo tài khoản mới...\033[0m" << endl;
				createAccount(people);
				goto here;
				break;
			}
			if (counter == 3)
			{
				cout << "\nThoát ra thành công";
			}

		}
		Set[4] = 7;
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}
		if (counter == 2)
		{
			Set[1] = 12;
		}
		if (counter == 3)
		{
			Set[2] = 12;
		}

	}
}
void menu();

void menuAdmin() {
here:
	string cf;
	Staff* st = nullptr;
	int Set3[] = { 7,7,7,7,7,7,7,7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 2;
	char key;
	for (int i = 0;;)
	{
		gotoxy(5, 4);
		color(Set3[11]);
		cout << "\033[33m---------------Lựa chọn---------------\033[0m" << endl;

		gotoxy(5, 5);
		color(Set3[0]);
		cout << "1. Các lựa chọn chính";

		gotoxy(5, 6);
		color(Set3[1]);
		cout << "2. Tất cả manga đang có sẵn";

		gotoxy(5, 7);
		color(Set3[2]);
		cout << "3. Tìm kiếm";

		gotoxy(5, 8);
		color(Set3[3]);
		cout << "4. Thêm manga mới";

		gotoxy(5, 9);
		color(Set3[4]);
		cout << "5. Xóa manga";

		gotoxy(5, 10);
		color(Set3[5]);
		cout << "6. Cập nhật manga";

		gotoxy(5, 11);
		color(Set3[6]);
		cout << "7. Tạo tài khoản mới";

		gotoxy(5, 12);
		color(Set3[7]);
		cout << "8. Các tài khoản đã được đăng kí";

		gotoxy(5, 13);
		color(Set3[8]);
		cout << "9. Xem/Chỉnh sửa thông tin tài khoản";

		gotoxy(5, 14);
		color(Set3[9]);
		cout << "0. Lưu và thoát";

		gotoxy(5, 15);
		color(Set3[10]);
		cout << "\033[33m--------------------------------------\033[0m" << endl;


		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 10))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 9))
		{
			counter++;
		}
		if (key == '\r')//carriage return
		{
			if (counter == 1)
			{
				menuAdmin();
				break;
			}
			if (counter == 2)
			{
				cout << "\n" << endl;
				showList(list);
				cout << "Nhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menuAdmin();
				cout << "\n" << endl;

				break;
			}
			if (counter == 3)
			{
				search(list);
                cout<<"\nNhập 0 để quay lại:";
                int c;
                inputNumber(c);
                if (c==0);
                clearScreen();
                menuAdmin();
				break;
			}
			if (counter == 4)
			{
				add(list);
				writeToFile(list);
				cout << "\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menuAdmin();
				break;
			}
			if (counter == 5)
			{
				remove(list);
				writeToFile(list);
				cout << "\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menuAdmin();
				break;
			}
			if (counter == 6)
			{
				update(list);
				writeToFile(list);
				cout << "\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menuAdmin();
				break;
			}
			if (counter == 7)
			{
				st = dynamic_cast<Staff*>(current);
				st->createAdminAccount(people);
				writeToFile(people);
				cout << "\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menuAdmin();
				break;
			}
			if (counter == 8)
			{
				cout << "\n" << endl;
				st = dynamic_cast<Staff*>(current);
				st->listUser(people);
				int Set1[] = { 7,7 }; // DEFAULT COLORS
				int counter = 1;
				char key;
				for (int i = 0;;)
				{
					gotoxy(5, 38);
					color(Set1[0]);
					cout << "0. Quay lại";


					gotoxy(5, 39);
					color(Set1[1]);
					cout << "1. Thay đổi mật khẩu của một người dùng";

					key = _getch();

					if (key == 72 && (counter >= 2 && counter <= 2))
					{
						counter--;
					}
					if (key == 80 && (counter >= 1 && counter <= 1))
					{
						counter++;
					}
					if (key == '\r')//carriage return
					{
						if (counter == 1)
						{
							clearScreen();
							menuAdmin();
							break;
						}
						if (counter == 2)
						{
							cout << "\n" << endl;
							st->changePassword(people);
							writeToFile(people);
							break;
						}

					}
					Set1[0] = 7;
					Set1[1] = 7;

					if (counter == 1)
					{
						Set1[0] = 12;
					}
					if (counter == 2)
					{
						Set1[1] = 12;
					}
				}
				break;

			}
			if (counter == 9)
			{
				int Set2[] = { 7,7,7 }; // DEFAULT COLORS
				int counter = 1;
				char key;
				for (int i = 0;;)
				{
					gotoxy(5, 17);
					color(Set2[0]);
					cout << "0. Quay lại";


					gotoxy(5, 18);
					color(Set2[1]);
					cout << "1. Thay đổi mật khẩu";

					gotoxy(5, 19);
					color(Set2[2]);
					cout << "2. Thay đổi tất cả thông tin";
					key = _getch();

					if (key == 72 && (counter >= 2 && counter <= 3))
					{
						counter--;
					}
					if (key == 80 && (counter >= 1 && counter <= 2))
					{
						counter++;
					}
					if (key == '\r')//carriage return
					{
						if (counter == 1)
						{
							clearScreen();
							menuAdmin();

							break;
						}
						if (counter == 2)
						{
							string newpass;
							cout << "\nMật khẩu mới: ";
							getline(cin, newpass);
							current->setPassword(newpass);
							writeToFile(people);
							break;
						}
						if (counter == 3)
						{
							cout << "\n" << endl;
							current->input(people);
							writeToFile(people);
							break;
						}

					}
					Set2[0] = 7;
					Set2[1] = 7;
					Set2[2] = 7;

					if (counter == 1)
					{
						Set2[0] = 12;
					}
					if (counter == 2)
					{
						Set2[1] = 12;
					}
					if (counter == 3)
					{
						Set2[2] = 12;
					}

				}

				break;
			}

			if (counter == 10)
			{
                clearScreen();
				start(people);
				int choice; string cf;
	            if (current->type == "User")
	            {
		           menu();
	            }
	                else
	            {
		           menuAdmin();
	             }


			}

		}
		Set3[10] = 7;
		Set3[11] = 7;
		Set3[0] = 7;
		Set3[1] = 7;
		Set3[2] = 7;
		Set3[3] = 7;
		Set3[4] = 7;
		Set3[5] = 7;
		Set3[6] = 7;
		Set3[7] = 7;
		Set3[8] = 7;
		Set3[9] = 7;


		if (counter == 1)
		{
			Set3[0] = 12;
		}
		if (counter == 2)
		{
			Set3[1] = 12;
		}
		if (counter == 3)
		{
			Set3[2] = 12;
		}
		if (counter == 4)
		{
			Set3[3] = 12;
		}
		if (counter == 5)
		{
			Set3[4] = 12;
		}
		if (counter == 6)
		{
			Set3[5] = 12;
		}
		if (counter == 7)
		{
			Set3[6] = 12;
		}
		if (counter == 8)
		{
			Set3[7] = 12;
		}
		if (counter == 9)
		{
			Set3[8] = 12;
		}
		if (counter == 10)
		{
			Set3[9] = 12;
		}

	}
}

void help() {
	cout << "Liên lạc Nguyễn Minh Quân cho bất cứ vất đề gì" << endl;
}
void about() {
	cout << "Manga management for the weebs" << endl;
}
void menu()
{
here:
	int Set4[] = { 7,7,7,7,7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;
	for (int i = 0;;)
	{
		gotoxy(5, 4);
		color(Set4[8]);
		cout << "\033[33m---------------Lựa chọn---------------\033[0m" << endl;

		gotoxy(5, 5);
		color(Set4[0]);
		cout << "1. Các lựa chọn chính";

		gotoxy(5, 6);
		color(Set4[1]);
		cout << "2. Tất cả manga đang có sẵn";

		gotoxy(5, 7);
		color(Set4[2]);
		cout << "3. Tìm kiếm";

		gotoxy(5, 8);
		color(Set4[3]);
		cout << "4. Xem/Chỉnh sửa thông tin tài khoản";

		gotoxy(5, 9);
		color(Set4[4]);
		cout << "5. Giúp đỡ";

		gotoxy(5, 10);
		color(Set4[5]);
		cout << "6. Thông tin khác";

		gotoxy(5, 11);
		color(Set4[6]);
		cout << "0. Lưu và thoát";

		gotoxy(5, 12);
		color(Set4[7]);
		cout << "\033[33m--------------------------------------\033[0m" << endl;

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 7))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 6))
		{
			counter++;
		}
		if (key == '\r')//carriage return
		{
			if (counter == 1)
			{
				menu();
				break;
			}
			if (counter == 2)
			{
				cout << "\n" << endl;
				showList(list);
				cout << "Nhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menu();
				cout << "\n" << endl;

				break;
			}
			if (counter == 3)
			{
				search(list);
                cout << "\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menu();
				break;
			}

			if (counter == 4)
			{
				int Set5[] = { 7,7,7 }; // DEFAULT COLORS
				int counter = 1;
				char key;
				for (int i = 0;;)
				{
					gotoxy(5, 17);
					color(Set5[0]);
					cout << "0. Quay lại";


					gotoxy(5, 18);
					color(Set5[1]);
					cout << "1. Thay đổi mật khẩu";

					gotoxy(5, 19);
					color(Set5[2]);
					cout << "2. Thay đổi tất cả thông tin";
					key = _getch();

					if (key == 72 && (counter >= 2 && counter <= 3))
					{
						counter--;
					}
					if (key == 80 && (counter >= 1 && counter <= 2))
					{
						counter++;
					}
					if (key == '\r')//carriage return
					{
						if (counter == 1)
						{
							clearScreen();
							menu();

							break;
						}
						if (counter == 2)
						{
							string newpass;
							cout << "\nMật khẩu mới: ";
							getline(cin, newpass);
							current->setPassword(newpass);
							writeToFile(people);
							break;
						}
						if (counter == 3)
						{
							cout << "\n" << endl;
							current->input(people);
							writeToFile(people);
							break;
						}

					}
					Set5[0] = 7;
					Set5[1] = 7;
					Set5[2] = 7;

					if (counter == 1)
					{
						Set5[0] = 12;
					}
					if (counter == 2)
					{
						Set5[1] = 12;
					}
					if (counter == 3)
					{
						Set5[2] = 12;
					}

				}
			}

			if (counter == 5)
			{
				help();
				cout<<"\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menu();
				break;
			}
			if (counter == 6)
			{
				about();
				cout<<"\nNhấn 0 để quay về:";
				int c;
				inputNumber(c);
				if (c == 0);
				clearScreen();
				menu();
				break;
			}
			if (counter == 7)
			{
                clearScreen();
				start(people);
				int choice; string cf;
	            if (current->type == "Staff")
	            {
		           menuAdmin();
	            }
	                else
	            {
		           menu();
	             }
			}

		}
		Set4[0] = 7;
		Set4[1] = 7;
		Set4[2] = 7;
		Set4[3] = 7;
		Set4[4] = 7;
		Set4[5] = 7;
		Set4[6] = 7;
		Set4[7] = 7;
		Set4[8] = 7;


		if (counter == 1)
		{
			Set4[0] = 12;
		}
		if (counter == 2)
		{
			Set4[1] = 12;
		}
		if (counter == 3)
		{
			Set4[2] = 12;
		}
		if (counter == 4)
		{
			Set4[3] = 12;
		}
		if (counter == 5)
		{
			Set4[4] = 12;
		}
		if (counter == 6)
		{
			Set4[5] = 12;
		}
		if (counter == 7)
		{
			Set4[6] = 12;
		}
		if (counter == 8)
		{
			Set4[7] = 12;
		}
	}
}

void printAnimegirl() {
	ifstream file("C:\\Users\\ADMIN\\c\\anime girl.txt");
	if (file.is_open()) {
		cout << file.rdbuf();
		file.close();
	}
}
int main()
{
begin:
	readfile(list);
	readfile(people);
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	clearScreen();
	printAnimegirl();
	start(people);
	int choice; string cf;
	if (current->type == "Staff")
	{
		menuAdmin();
	}
	else
	{
		menu();
	}
}