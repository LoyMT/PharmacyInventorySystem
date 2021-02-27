#include <iostream>
#include<string>
#include<conio.h>
#include "MedicineStock.cpp"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

bool login();
string getpass();
void header();

int main(int argc, char** argv) {
	//creat a new instance of a class MedicineStock
	MedicineStock medicineStock(argc ,argv);
	if(login()){
		medicineStock.loading("Welcome", 2, "full");
		system("cls");
		while(true){
			string select;
			
			header();
			//menu
			cout << "\t  *** Welcome to Pharmacy Inventory System ***\n" << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t\tMedicine Phase" << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t1. Add Medicine" << endl;
			cout << "\t\t2. Search" << endl;
			cout << "\t\t3. View Medicine List" << endl;
			cout << "\t\t4. Edit Medicine" << endl;
			cout << "\t\t5. Delete Medicine" << endl;
			cout << "\t\t6. Clear Medicine By Type" << endl;
			cout << "\t\t7. Clear Medicine" << endl << endl;
			cout << "\t\t01 >> Update Medicine Record" << endl << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t\tStock Phase" << endl;
			cout << "\t\t*****************************" << endl;
			cout << "\t\t8. Stock In & Stock Out" << endl;
			cout << "\t\t9. Stock History" << endl;
			cout << "\t\t10. Clear Stock History" << endl << endl;
			cout << "\t\t02 >> Update Stock Record" << endl << endl;
			cout << "\t\t0. Close Application" << endl;
			cout << "\n\tEnter your option >> ";
			cin >> select;
			fflush(stdin);
			system("cls");
			if (select.compare("1") == 0){
				//invoke method
				string medicType = medicineStock.getType(medicineStock.displayType("add"));
				if(medicType!="empty"){
					//invoke method
					medicineStock.addMedicine(medicType);
				}
			}
			else if (select.compare("2") == 0){
				//invoke method
				medicineStock.stockRecord_medic(medicineStock.searchMedicine());	
			}
			else if (select.compare("3") == 0){
				//invoke method
				medicineStock.viewMedicine("id", 0, 0);
			}
			else if (select.compare("4") == 0){
				//invoke method
				medicineStock.editMedicine();
			}
			else if (select.compare("5") == 0){
				//invoke method
				medicineStock.deleteMedicine();
			}
			else if (select.compare("6") == 0){
				//invoke method
				medicineStock.clearMedicineByType();
			}
			else if (select.compare("7") == 0){
				//invoke method
				medicineStock.clearMedicine();
			}
			else if (select.compare("8") == 0){
				string select;
				while(select.compare("0") != 0){
					system("cls");
					//menu for stock in and stock out
					cout << "\n\n";
					cout << "\t       *** Pharmacy Inventory System ***\n" << endl;
					cout << "\t-----------------------------------------------"<<endl;
					cout << "\t\t Choose one type of Stock \n";
					cout << "\t-----------------------------------------------\n"<<endl;
					cout << "\t\t    1. Stock In "<<endl;
					cout << "\t\t    2. Stock Out" << endl << endl;
					cout << "\t\t    0 >> Go Back" << endl;
					cout << "\n\tEnter your options >> " ;
					cin >> select;
					fflush(stdin);
					
					if(select.compare("1") == 0){
						//invoke method
						medicineStock.stockManage("in");
					}
					else if(select.compare("2") == 0){
						//invoke method
						medicineStock.stockManage("out");
					}
					else if(select.compare("0") != 0){
						cout << "\n\tPlease input proper selection!!!";
						getch();
					}
				}
			}
			else if (select.compare("9") == 0){
				//invoke method
				medicineStock.stockRecord_all("all", 0, 0);
			}
			else if (select.compare("10") == 0){
				//invoke method
				medicineStock.cleatStockHistory();
			}
			else if (select.compare("01") == 0){
				//invoke method
				medicineStock.updateMedicine();
				medicineStock.loading("Updating", 3, "full");
			}
			else if (select.compare("02") == 0){
				//invoke method
				medicineStock.updateStock();
				medicineStock.loading("Updating", 3, "full");
			}
			else if (select.compare("0") == 0){
				break; //break the loop
			}
			else{
				cout << "\n\tPlease input proper selection!!!";
			}
			fflush(stdin);
			system("cls");
		}
	}
	return 0;
}
// function to display header
void header()
{
	cout << "\n\n\t----------------------------------------------" << endl;
	cout << "\t            Pharmacy Inventory System" << endl;
	cout << "\t----------------------------------------------" << endl;
}
//function to check login
bool login()
{
	string pass;
	header();
	cout << "\n\n\t\t ******WELCOME BACK!!!******" <<endl;
	cout << "\n\n\t ENTER PASSWORD TO LOGIN : ";
	pass = getpass();
	if(pass.compare("1234") == 0){ //compare password
		system("cls");
		return true;
	}else
	{
		cout << "\n\n\t\t    WRONG PASSWORD!!!!"<<endl;
		cout << "\t\t    PLEASE TRY AGAIN...";
		getch();
		system("cls");
		login();
	}
}
//funvtion to get input password
string getpass(){
	const char BACKSPACE = 8;
	const char RETURN = 13;	
	unsigned char ch = 0;
	string password;

	while ((ch = getch()) != RETURN){
		if (ch == BACKSPACE){
        	if (password.length() != 0){
            	cout << "\b \b";
                password.resize(password.length()-1);
            }
        }
    	else{
        	password += ch;
        	cout << '*';
        }
	}
	cout << endl;
	return password;
}
