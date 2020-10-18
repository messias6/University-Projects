#include "stdafx.h"
#include "myconnectorclassDB.h"
#include "EWApp.h"
#include "stdlib.h"

myconnectorclassDB::myconnectorclassDB()
{
}


myconnectorclassDB::~myconnectorclassDB()
{
}

void myconnectorclassDB::connect()
{
	connection = mysql_init(NULL);
	connection = mysql_real_connect(connection, SERVER, USER,
		PASSWORD, DATABASE, 0, NULL, 0);
	CString message;
	if (connection == NULL) {
		message.Format(_T("Unable to connect!"));
		AfxMessageBox(message);
	}
}


void myconnectorclassDB::Query(CString query) 
{
	wchar_t *p = query.GetBuffer();
	char bufUTF8[MAX_PATH];
	WideCharToMultiByte(CP_UTF8, 0, p, -1, bufUTF8, sizeof(bufUTF8), NULL, NULL);
	mysql_query(connection, bufUTF8);
	result = mysql_store_result(connection);
}

CString myconnectorclassDB::CPtoUnicode(const char* CPString, UINT CodePage) 
{
	CString retValue;

	int len = MultiByteToWideChar(CodePage, 0, CPString, -1, NULL, 0);
	if (len == 0) { return retValue; }
	LPWSTR buffer = retValue.GetBuffer(len);
	MultiByteToWideChar(CodePage, 0, CPString, -1, buffer, len);
	retValue.ReleaseBuffer();
	return retValue;
}

/*----------------------------------------------------------
                          CODE WRITTEN BY ME
------------------------------------------------------------*/

BOOL myconnectorclassDB::VerifyUser(CString email, CString usertype) {
	CString value;
	CString query = _T("SELECT Person.ID FROM Person, ") + usertype + _T(" WHERE email = '") + email + _T("' and Person.ID = ") + usertype + _T(".ID");
	Query(query);
	// If a wrong email is written, it jumbs right to the end of this class, returning TRUE to this boolean
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}	
	return (value[0]=='\0'); //False
}

// Verify if the employee is Monitor or computer tech
BOOL myconnectorclassDB::VerifyUserIsMonitor(CString email) {
	CString value;
	CString query = _T("SELECT P.ID FROM Person P, Employee E, Monitor M WHERE P.ID = E.ID and E.employee_ID = M.employee_ID and P.email = '") + email + _T("'");
	Query(query);
	
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0'); //False
}

BOOL myconnectorclassDB::VerifyPass(CString email, CString pass) {
	CString value;
	CString query = _T("SELECT password FROM Person WHERE email = '") + email + _T("'");
	Query(query);
	while ((row = mysql_fetch_row(result)) != NULL) {
		value = CPtoUnicode(row[0], 1251);
	}
	// Verifies if the value from the querie is = to the pass and returns a true/false
	return (value != pass); 
}

BOOL myconnectorclassDB::ForgotPassword(CString email) {
	CString value;
	CString query = _T("SELECT ID FROM Person WHERE email = '") + email + _T("'");
	Query(query);
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0');
}

BOOL myconnectorclassDB::SeeIDExists(CString id) {
	CString value;
	CString query = _T("SELECT NIF FROM Person WHERE ID = '") + id + _T("'");
	Query(query);
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0');
}

// INSERT Employee in use_employee table - meaning he logged in and is working
void myconnectorclassDB::InsertStudEmpl(CString pcid, CString studentid, CString datte, CString timenow, CString usertype) {
	CString query = _T("INSERT INTO use_") + usertype + _T(" VALUES (") + pcid + _T(",'") + studentid + _T("','") + datte + _T("','") + timenow + _T("',NULL)");
	Query(query);
}

/*------------------------
    EMPLOYEE WINDOW App
-------------------------*/

void myconnectorclassDB::LogOutEmployee(CString employeeISTid, CString tnow) {
	CString query = _T("UPDATE use_employee SET end_time = '") + tnow + _T("' WHERE employee_ID = '") + employeeISTid + _T("'");
	Query(query);
}

// Get the ist'number' from email
CString myconnectorclassDB::GetPersonISTid(CString email, CString UserT, CString usertype) {
	CString value;
	CString query = _T("SELECT ") + UserT + _T(".") + usertype + _T("_ID FROM Person, ") + UserT + _T(" WHERE Person.email = '") + email + _T("' and Person.ID = ") + UserT + _T(".ID");
	Query(query);
	row = mysql_fetch_row(result);
	value = row[0];

	return value;
}

int myconnectorclassDB::GetNTPCs(void) {
	int n;
	CString query = _T("SELECT pc_ID FROM PC");
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

int myconnectorclassDB::GetNPCsUsed(CString usertype) {
	int n;
	CString query = _T("SELECT pc_ID FROM use_") + usertype + _T(" WHERE end_time is NULL");
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

CString myconnectorclassDB::GetPCseLocation(int pc, CString column_type) {
	CString value;
	CString query = _T("SELECT ") + column_type + _T(" FROM PC WHERE pc_ID not in (SELECT pc_ID FROM use_employee WHERE end_time is NULL) and pc_ID not in (SELECT pc_ID FROM use_student WHERE end_time is NULL) ORDER BY pc_ID desc");
	Query(query);
	for (int i = 0; i < pc + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
	}
	return value;
}

// Pcs being used!!
CString myconnectorclassDB::GetPCsNotAvail(int pc) {
	CString value;
	CString query = _T("SELECT pc_ID FROM PC WHERE pc_ID in (SELECT pc_ID FROM use_student WHERE end_time is NULL)");
	Query(query);
	for (int i = 0; i < pc + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
		
	}
	return value;
}

/*
void myconnectorclassDB::RemoveStudentFrPC(CString end_time_now, CString istid, CString date_of_startTime, CString time_of_startTime) {
	CString query = _T("UPDATE use_student SET end_time = '") + end_time_now + _T("' WHERE student_ID = '") + istid + _T("' and date = '") + date_of_startTime + _T("' and start_time = '") + time_of_startTime + _T("'");
	Query(query);
}*/

CString myconnectorclassDB::GetStimeEdateFRid(CString pcid, CString & istid, CString & date_of_startTime) {
	CString value;
	// Obtain istid
	CString query = _T("SELECT student_ID FROM use_student WHERE pc_ID = '") + pcid + _T("' and end_time is NULL");
	Query(query);
	row = mysql_fetch_row(result);
	istid = row[0];
	
	// Obtain date
	query = _T("SELECT date FROM use_student WHERE pc_ID = '") + pcid + _T("' and end_time is NULL");
	Query(query);
	row = mysql_fetch_row(result);
	date_of_startTime = row[0];

	// Obtain time
	query = _T("SELECT start_time FROM use_student WHERE pc_ID = '") + pcid + _T("' and end_time is NULL");
	Query(query);
	row = mysql_fetch_row(result);
	value = row[0];
	
	return value;
}

// Remove Student from pc
void myconnectorclassDB::RemoveStudentFrPC(CString pcid, CString end_time_now, CString istid, CString date_of_startTime, CString time_of_startTime) {
	CString query = _T("UPDATE use_student SET end_time = '") + end_time_now + _T("' WHERE pc_ID = ") + pcid + _T(" and student_ID = '") + istid + _T("' and date = '") + date_of_startTime + _T("' and start_time = '") + time_of_startTime + _T("'");
	Query(query);
}

/*------------------------
	Att Email window
-------------------------*/

BOOL myconnectorclassDB::VerifyID(CString id, CString user) {
	CString value;
	CString query = _T("SELECT ID FROM ") + user + _T(" WHERE ID = '") + id + _T("'");
	Query(query);
	// If a wrong number is written, it jumbs right to the end of this class, returning TRUE to this boolean
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0'); //False
}

// Verify if ist'number' (employee and student) has a PC (end_time = NULL)
BOOL myconnectorclassDB::VerifyUserHasPC(CString istid, CString usertype) {
	CString value;
	CString query = _T("SELECT use_") + usertype + _T(".") + usertype + _T("_ID FROM use_") + usertype + _T(" WHERE use_") + usertype + _T(".") + usertype + _T("_ID = 'ist") + istid + _T("' and use_") + usertype + _T(".end_time is NULL");
	Query(query);
	// If a wrong email is written, it jumbs right to the end of this class, returning TRUE to this boolean
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0');
}

/*--------------------------------------
	Student Window App - SWApp
---------------------------------------*/

// See if student_ID has Online Account 
BOOL myconnectorclassDB::VerifyStIDhasOnlineAccount(CString istid) {
	CString value;
	CString query = _T("SELECT S.student_ID FROM Student S, has h WHERE S.student_ID = '") + istid + _T("' and S.student_ID = h.student_ID");
	Query(query);
	// If a wrong email is written, it jumbs right to the end of this class, returning TRUE to this boolean
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0');
}

// Create online account - insert student in "has" table with an account number
void myconnectorclassDB::InsertStudentInHas(CString istid, CString account_number) {
	CString query = _T("INSERT INTO has VALUES ('") + istid + _T("','") + account_number + _T("')");
	Query(query);
}

// Create online account - Table: Online Account
void myconnectorclassDB::InsertInOA(CString account_number) {
	CString query = _T("INSERT INTO Online_account VALUES ('") + account_number + _T("', 0)");
	Query(query);
}

int myconnectorclassDB::GetNPrintsECourses(CString table) {
	int n;
	CString query = _T("SELECT product_ID FROM ") + table;
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

CString myconnectorclassDB::GetPrintsECourses(int n, CString column) {
	CString value;
	CString query = _T("SELECT Product.") + column + _T(" FROM Product, Prints WHERE Product.product_ID = Prints.product_ID ORDER BY product_name desc");
	Query(query);
	for (int i = 0; i < n + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
	}
	return value;
}

// Get Account_number from Student_ID
CString myconnectorclassDB::GetNumOnAcc(CString istid) {
	CString value;
	CString query = _T("SELECT account_number FROM has WHERE student_ID = '") + istid + _T("'");
	Query(query);
	row = mysql_fetch_row(result);
	value = row[0];

	return value;
}

// Get current balance from Student_ID
CString myconnectorclassDB::GetNumOnAccPrice(CString istid) {
	CString value;
	CString query = _T("SELECT Online_account.balance FROM has, Online_account WHERE has.account_number = Online_account.account_number and has.student_ID = '") + istid + _T("'");
	Query(query);
	row = mysql_fetch_row(result);
	value = row[0];

	return value;
}

CString myconnectorclassDB::GetProdIDeUnitPrice(CString name, CString & productid) {
	CString value;
	// Obtain product_id
	CString query = _T("SELECT product_ID FROM Product WHERE product_name = '") + name + _T("'");
	Query(query);
	row = mysql_fetch_row(result);
	productid = row[0];

	// Obtain unit_price
	query = _T("SELECT price FROM Product WHERE product_name = '") + name + _T("'");
	Query(query);
	row = mysql_fetch_row(result);
	value = row[0];

	return value;
}

void myconnectorclassDB::AddPayPrints(CString account_number, CString product_ID, CString quantity) {
	CString query = _T("INSERT INTO pay_prints VALUES ('") + account_number + _T("',") + product_ID + _T(",") + quantity + _T(")");
	Query(query);
}

void myconnectorclassDB::UpdateOABalance(CString account_number, CString balance_new) {
	CString query = _T("UPDATE Online_account SET balance = ") + balance_new + _T(" WHERE account_number = '") + account_number + _T("'");
	Query(query);
}

/*---------------------------
          PURCHASES
-----------------------------*/

// Number of Prints_ID of a given student_ID
int myconnectorclassDB::NumbOfPID(CString istid) {
	int n;
	CString query = _T("SELECT pp.product_ID FROM pay_prints pp, has h WHERE pp.account_number = h.account_number and h.student_ID = '") + istid + _T("' GROUP BY pp.product_ID");
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

// Number of Courses_ID of a given student_ID
int myconnectorclassDB::NumbOfCID(CString istid) {
	int n;
	CString query = _T("SELECT pc.product_ID FROM pay_courses pc, has h WHERE pc.account_number = h.account_number and h.student_ID = '") + istid + _T("' GROUP BY pc.product_ID");
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

// Get from PRINTS: Name, Quantity and Price of a given student_ID
CString myconnectorclassDB::GetPNameQtdPriceOFStd(int n, CString column_type, CString istid) {
	CString value;
	CString query = _T("SELECT ") + column_type + _T(" FROM Product P, pay_prints pp, has h WHERE pp.account_number = h.account_number and pp.product_ID = P.product_ID and h.student_ID = '") + istid + _T("' GROUP BY pp.product_ID ORDER BY pp.product_ID desc");
	Query(query);
	for (int i = 0; i < n + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
	}
	return value;
}

// Get from Courses: Name and Price of a given student_ID
CString myconnectorclassDB::GetCNameQtdPriceOFStd(int n, CString column_type, CString istid) {
	CString value;
	CString query = _T("SELECT ") + column_type + _T(" FROM Product P, pay_courses pc, has h WHERE pc.account_number = h.account_number and pc.product_ID = P.product_ID and h.student_ID = '") + istid + _T("' GROUP BY pc.product_ID ORDER BY pc.product_ID desc");
	Query(query);
	for (int i = 0; i < n + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
	}
	return value;
}

/*--------------------------------
          COURSES WINDOW
---------------------------------*/

// 
CString myconnectorclassDB::GetCourses(int n, CString column_type) {
	CString value;
	CString query = _T("SELECT ") + column_type + _T(" FROM Product P, Courses C LEFT JOIN pay_courses pc ON pc.product_ID = C.product_ID WHERE P.product_ID = C.product_ID GROUP BY P.product_ID");
	Query(query);
	for (int i = 0; i < n + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
	}
	return value;
}

// Check if student is register in course
BOOL myconnectorclassDB::CheckStdISinC(CString istid, CString name_prod) {
	CString value;
	CString query = _T("SELECT P.product_name FROM pay_courses pc, has h, Product P WHERE h.account_number = pc.account_number and P.product_ID = pc.product_ID and h.student_ID = '") + istid + _T("' and P.product_name = '") + name_prod + _T("'");
	Query(query);
	// If doesn't find, returns TRUE to this boolean
	while ((row = mysql_fetch_row(result)) != NULL)
	{
		value = CPtoUnicode(row[0], 1251);
	}
	return (value[0] == '\0');
}

// Number of courses each person is registered
int myconnectorclassDB::NumbofCRegist(CString istid) {
	int n;
	CString query = _T("SELECT pc.product_ID FROM pay_courses pc, has h WHERE h.account_number = pc.account_number and h.student_ID = '") + istid + _T("'");
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

CString myconnectorclassDB::GetCoursesRegist(int n, CString istid) {
	CString value;
	CString query = _T("SELECT P.product_name FROM pay_courses pc, has h, Product P WHERE h.account_number = pc.account_number and P.product_ID = pc.product_ID and h.student_ID = '") + istid + _T("'");
	Query(query);
	for (int i = 0; i < n + 1; i++) {
		row = mysql_fetch_row(result);
		value = row[0];
	}
	return value;
}

// Get the ID of the name of the product
CString myconnectorclassDB::GetIDofProdName(CString name_prod) {
	CString value;
	CString query = _T("SELECT product_ID FROM Product WHERE product_name = '") + name_prod + _T("'");
	Query(query);
	row = mysql_fetch_row(result);
	value = row[0];

	return value;
}

// Unenrool person from course
void myconnectorclassDB::UnenrollCourseOfStd(CString acc_numb, CString prodid) {
	CString query = _T("DELETE FROM pay_courses WHERE account_number = '") + acc_numb + _T("' and product_ID = ") + prodid;
	Query(query);
}

// Insert purchase in pay_courses
void myconnectorclassDB::AddToPayCourses(CString account_number, CString product_ID) {
	CString query = _T("INSERT INTO pay_courses VALUES ('") + account_number + _T("',") + product_ID + _T(")");
	Query(query);
}

void myconnectorclassDB::AddMoneyToAccount(CString account_number, CString balance_new) {
	CString query = _T("UPDATE Online_account SET balance = balance + ") + balance_new + _T(" WHERE account_number = '") + account_number + _T("'");
	Query(query);
}


void myconnectorclassDB::NewPerson(CString ID, CString Name, CString NIF, CString email, CString pass) {
	CString query = _T("INSERT INTO Person VALUES ('") + ID + _T("','") + Name + _T("','") + NIF + _T("','") + email + _T("','") + pass + _T("')");
	Query(query);
}

void myconnectorclassDB::NewStdOREmployee(CString ID, CString TabletoADD) {
	CString query = _T("INSERT INTO ") + TabletoADD + _T(" VALUES ('ist") + ID + _T("','") + ID + _T("')");
	Query(query);
}

int myconnectorclassDB::NumbofProducts() {
	int n;
	CString query = _T("SELECT product_ID FROM Product");
	Query(query);
	n = mysql_num_rows(result);
	return n;
}

void myconnectorclassDB::NewProduct(CString ID, CString Name, CString UnitPrice) {
	CString query = _T("INSERT INTO Product VALUES (") + ID + _T(",'") + Name + _T("',") + UnitPrice + _T(")");
	Query(query);
}


void myconnectorclassDB::NewPrints(CString ID) {
	CString query = _T("INSERT INTO Prints VALUES (") + ID + _T(")");
	Query(query);
}

void myconnectorclassDB::NewCourses(CString ID) {
	CString query = _T("INSERT INTO Courses VALUES (") + ID + _T(", 15)");
	Query(query);
}