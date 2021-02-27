//Filename: MedicineType.cpp
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <direct.h>
#ifndef MEDICINE_TYPE_CPP
#define MEDICINE_TYPE_CPP
using namespace std;

class MedicineType{
	private:
		string _type;
	    char delimeter; //for Windows
	    string part, part_prev, DIR, file, FILE, VIEW_FILE, MEDIC_FILE, STOCK_FILE;
		string full;
	    
	protected:
		ifstream r;
		ofstream w;
		
	public:
		//constructor for class MedicineType
		MedicineType(){
			FILE = "database";
			VIEW_FILE = "record";
			MEDIC_FILE = "medicine";
			STOCK_FILE = "stock";
		};
		
		//constructor with parameter for class MedicineType
		MedicineType(int argc, char *argv[]){
			//code to get current file directory
			FILE = "database";
			VIEW_FILE = "record";
			MEDIC_FILE = "medicine";
			STOCK_FILE = "stock";
			full=""; part_prev=""; DIR=""; delimeter='\\';
			stringstream sst(argv[0]);
			while (getline(sst, part, delimeter))
			{
				DIR+=part_prev;
				part_prev=part+delimeter;
			}
			//coding to creat new folder at current directory
		    full=DIR;
		    full += FILE + '\\';
		    mkdir(full.c_str());
		    full=DIR;
		    full += VIEW_FILE + '\\';
		    mkdir(full.c_str());
		    full += MEDIC_FILE + '\\';
		    mkdir(full.c_str());
		    full=DIR;
		    full += VIEW_FILE + '\\';
		    mkdir(full.c_str());
		    full += STOCK_FILE + '\\';
		    mkdir(full.c_str());
		    full=DIR;
		};
		
		//destructor for class MedicineType
		~MedicineType(){};
		 
		//method to add medicine type
		void addType(){
			system("cls");
			string type;
			cout << endl << " Enter type name : ";
			getline(cin, type);
			if(type.length()==0){
				this->alert(2, "empty");
				this->addType();
			}else if(type.length()>18){
				this->alert(3, "18");
				this->addType();
			}else{
				if(openfr(1, "type_list.txt")!="0"){
					while(getline(r, _type)!=0){
						if(_type==type){
							this->loading("Processing", 1, "");
							cout << endl << " The type is already inserted..." << endl;
							type="existed";
						}
					}
				}
				r.close();
				if(type!="existed"){
					_type=type;
					openfw(1, "type_list.txt");
					w << _type << endl;
					w.close();
				}
			}
		};
		
		//method to display medicine type
		int displayType(string type){
			system("cls");
			int choice;
			if(openfr(1, "type_list.txt")=="0"){
				cout << endl << endl << " Currently do not insert for any record..." << endl;
				if(type=="add"){
					cout << endl << endl << endl << " \t\t99 >> To add new medicine type" << endl << endl;
					cout << " \t\t0 >> Go Back" << endl;
					cout << endl << " \t" << " Enter your choice >> ";
					if((!(cin >> choice)) || (choice != 99 && choice != 0)){
						cin.clear();
						cin.ignore(1000,'\n');
						this->alert(1, "choice");
						this->displayType(type);
					}
				}
			}else{
				int i=0;
				r.seekg(0, ios::beg);
				while(getline(r, _type)!=0){
					cout << endl << " \t\t" << ++i << ". " << _type << endl;
				}
				cout << endl << endl << " \t\t99 >> To add new medicine type" << endl << endl;
				cout << " \t\t0 >> Go Back" << endl;
				cout << endl << " \t" << " Choose a medicien type to "<< type << " : ";
				if((!(cin >> choice)) || ((choice > i && choice!=99 && choice!=0) || choice < 0)){
					cin.clear();
					cin.ignore(1000,'\n');
					this->alert(1, "choice");
					this->displayType(type);
				}
			}
			cin.ignore(1000, '\n');
			r.close();
			return choice;
		};
		
		//method to get the selected medicine type
		string getType(int select){
			string type;
			if(select==99){
				this->addType();
				type = this->getType(this->displayType("add"));
			}else{
				if(select==0){
					type = "empty";
				}else{
					openfr(1, "type_list.txt");
					int i=0;
					r.seekg(0, ios::beg);
					while(getline(r, _type)!=0){
						++i;
						if(i==select)
							type = _type;
					}
				}
				r.close();
			}
			return type;
		};
		
		//method to delete a medicine type
		string deleteType(){
			string del;
			string oldf = openfr(1, "type_list.txt");
			if(oldf=="0"){
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}else{
				r.close();
				del = this->getType(this->displayType("delete"));
				if(del!="empty"){
					cout << endl << " All the medicine record for this type will be clear!!!" << endl;
					cout << " Are you sure to delete the type? [Y/N]" << endl;
					char confirm=getch();
					if(confirm=='Y'||confirm=='y'){
						openfr(1, "type_list.txt");
						string newf = openfw(1, "temp.txt");
						r.seekg(0, ios::beg);
						while(getline(r, _type)!=0){
							if(_type!=del){
								w << _type << endl;
							}
						}
						r.close();
						w.close();
						int test = 0;
						if(remove(oldf.c_str()))
							perror(" Error remove file : ");
						else ++test;
						if(rename(newf.c_str(), oldf.c_str()))
							perror(" Error rename file : ");
						else ++test;
						int i=0;
						string checkFile = openfr(1, "type_list.txt");
						if(getline(r, _type)==0){
							r.close();
							if(remove(checkFile.c_str()))
								perror(" Error remove file : ");
							else ++test;
						}
						r.close();
						if(test==2){
							this->loading("Deleting", 2, "");
							cout << endl << endl << " The type of " << del << " is deleted!" << endl;
						}
						if(test==3){
							this->loading("Deleting", 2, "");
							cout << endl << endl  << " The type of " << del << " is deleted!" << endl;
							cout << " There is no more record of type in the file, the file had been removed!!" << endl;
						}				
					}else if(confirm=='N'||confirm=='n'){
						cout << endl << " The type of " << del << " is still remain." << endl;
						del = "0";
					}else{
						this->alert(1, "confirmation");
						cout << endl << " See you next time... Bye Bye" << endl;
						del = "0";
					}
				}
					
			}
			r.close();
			return del;
		};
		
		//method to open file for read
		string openfr(int type, string f1){
			switch(type){
				case 1:
					file = FILE + '\\' + f1;
					break;
			}
			r.open(file.c_str(), ios::in);
			if(!r.is_open()){
				file = "0";
			}
			return file;
		};
		
		//method to open file for write
		string openfw(int type, string f1){
			switch(type){
				case 1:
					file = FILE + '\\' + f1;
					break;
				case 2:
					file = VIEW_FILE + '\\' + MEDIC_FILE + '\\' + f1;
					break;
				case 3:
					file = VIEW_FILE + '\\' + STOCK_FILE + '\\' + f1;
					break;
			}
			w.open(file.c_str(), ios::out | ios::app);
			if(!w.is_open()){
				file = "0";
			}
			return file;
		};
		
		//method to display alert notification
		void alert(int TYPE, string type){
			cout << endl << "\t==================================================================================" << endl;
			if(TYPE==1)
				cout << "\t\tInvalid input for " << type << "... Please try again... Thank." << endl;
			else if(TYPE==2)
				cout << "\t\t" << type << " is not allow in this phase... Please try again... Thank." << endl;
			else if(TYPE==3)
				cout << "\t\tExisted the limit space... Only " << type << " character is allow" << endl;
			cout << "\t==================================================================================" << endl << "\t\t";
			system("pause");
		};
		
		//method to dispaly loading animatin
		void loading(string type, int speed, string layout){
			if(layout=="full")
				cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
			cout << endl << "\t\t\t\t" << type;
			int count = 0, run = 1;
			string loading;
			for(int i=0; i<=1000000000; i++){
				if(i%100000000==0){
					for(int j=0; j<count; j++)
						cout << "\b \b";
					loading += ".";
					cout << loading;
					++count;
				}
				if(i==1000000000 && run!=speed){
					++run;
					for(int j=0; j<count; j++){
						cout << "\b \b";
					}
					loading.resize(0);
					i=0;
					count=0;
				}
			}
			for(int j=0; j<count+200; j++)
				cout << "\b \b";
		};
};
#endif
