#pragma once
#include "my_global.h"
#include "mysql.h"


class myconnectorclassDB
{
private:
	#define SERVER "db.tecnico.ulisboa.pt"
	#define USER "ist181014"
	#define PASSWORD "ftjy0761"
	#define DATABASE "ist181014"

	void Query(CString query);
	MYSQL *connection;

public:
	MYSQL_ROW row;
	MYSQL_RES *result;
	void connect();

	CString CPtoUnicode(const char* CPString, UINT CodePage);

	// Login Window
	BOOL VerifyUser(CString email, CString usertype);
	BOOL VerifyUserIsMonitor(CString email);
	BOOL VerifyPass(CString email, CString pass);
	BOOL ForgotPassword(CString email);
	BOOL SeeIDExists(CString id);
	void InsertStudEmpl(CString pcid, CString studentid, CString dattte, CString timenow, CString usertype);

	// Employee Window
	void LogOutEmployee(CString employeeIDist, CString tnow);
	CString GetPersonISTid(CString email, CString UserT, CString usertype);
	int GetNTPCs(void);
	int GetNPCsUsed(CString usertype);
	CString GetPCseLocation(int pc, CString column_type);
	CString GetPCsNotAvail(int pc);
	void RemoveStudentFrPC(CString pcid, CString end_time_now, CString istid, CString date_of_startTime, CString time_of_startTime);
	CString GetStimeEdateFRid(CString pcid, CString & istid, CString & date_of_startTime);

	// AttEmail Window
	BOOL VerifyID(CString id, CString user);
	BOOL VerifyUserHasPC(CString istid, CString usertype);

	// Student Window
	BOOL VerifyStIDhasOnlineAccount(CString istid);
	void InsertStudentInHas(CString istid, CString account_number);
	void InsertInOA(CString account_number);
	int GetNPrintsECourses(CString table);
	CString GetPrintsECourses(int n, CString column_type);
	CString GetNumOnAcc(CString istid);
	CString GetNumOnAccPrice(CString istid);
	CString GetProdIDeUnitPrice(CString name, CString & productid);
	void AddPayPrints(CString account_number, CString product_ID, CString quantity);
	void UpdateOABalance(CString account_number, CString balance_new);

	// Purchases Window
	int NumbOfPID(CString istid);
	CString GetPNameQtdPriceOFStd(int n, CString column_type, CString istid);
	int NumbOfCID(CString istid);
	CString GetCNameQtdPriceOFStd(int n, CString column_type, CString istid);
	// Add Money
	void AddMoneyToAccount(CString account_number, CString balance_new);
	// Change IBAN
	// void ChangeIBAN(CString account_number, CString account_number_old);

	// Courses Window
	CString GetCourses(int n, CString column_type);
	BOOL CheckStdISinC(CString istid, CString name_prod);
	int NumbofCRegist(CString istid);
	CString GetCoursesRegist(int n, CString istid);
	void UnenrollCourseOfStd(CString acc_numb, CString prodid);
	CString GetIDofProdName(CString name_prod);
	void AddToPayCourses(CString account_number, CString product_ID);


	//Computer Technician
	void NewPerson(CString ID, CString Name, CString NIF, CString email, CString pass);
	void NewStdOREmployee(CString ID, CString TabletoADD);
	int NumbofProducts();
	void NewProduct(CString ID, CString Name, CString UnitPrice);
	void NewPrints(CString ID);
	void NewCourses(CString ID);
	

	myconnectorclassDB(void);
	virtual ~myconnectorclassDB(void);
};

