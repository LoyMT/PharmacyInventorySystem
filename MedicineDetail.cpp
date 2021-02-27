//Filename: MedicineDetail.cpp
#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

//class about medicine detail
class MedicineDetail{
	private:
		string _id; 			//variable for medicine id
		string _title; 			//variable for medicine title
		string _type; 			//variable for medicine type
		string _describe[3];	//variable for medicine description
		double _purchasePrice;	//variable for medicine purchase price
		double _soldOutPrice;	//variable for medicine sold out price
		int _quantity; 			//variable for medicine quantity
		string _date; 			//variable for stock record date
		string _time; 			//variable for stock record time
		string _status;			//variable for stock status
		int test;
		
	public:
		//constructor for class MedicineDetail
		MedicineDetail(){
			test=0;
		};
		
		//destructor for class MedicineDetail
		~MedicineDetail(){};
		
		//method to display medicine detail
		void displayMedicine(int type){
			
			cout << endl << " ID\t\t\t: " << _id << endl;
			cout << " Title\t\t\t: " << _title << endl;
			cout << " Type\t\t\t: " << _type << endl;
			cout << " Description\t\t: " << _describe[0] << endl;
			cout << "\t\t\t  " << _describe[1] << endl;
			cout << "\t\t\t  " << _describe[2] << endl;
			cout << " Purchase Price\t\t: RM ";
			if(test==0){ cout << _purchasePrice << endl; }
			else if(test==1) cout << setprecision(2) << _purchasePrice << endl;
			cout << " Sold Out Price\t\t: RM ";
			if(test==0){
				cout << _soldOutPrice << endl;
				test=1;
			} 
			else if(test==1) cout << setprecision(2) << _soldOutPrice << endl;
			if(type==1){
				cout << " Current Quantity\t: " << _quantity << endl;
			}
		};
		
		//method to display medicine type
		void printMedicineType(){
			cout << endl << " Medicine type : " << _type << endl;
		};
		
		//method to ask user input for medicine id and check input
		int askId(int action){
			cout << " Enter id\t\t : ";
				if(action==0){
					getline(cin, _id);
					if(!(this->required(_id))) //check whether there is insert for any value
						return 3; //return 3 if the input is not valid
					if(_id.length()>15)
						return 4; //return 4 if input value is to long
					return 1; //return 1 if the input is valid
				}else{
					cout << _id << endl;
					return 2; //return 2 if the input is already inserted and valid
				}
		};
		
		//method to ask user input for medicine title and check input
		int askTitle(int action){
			cout << " Enter title\t\t : ";
				if(action==1){
					getline(cin, _title);
					if(!(this->required(_title))) //check whether there is insert for any value
						return 3; //return 3 if the input is not valid
					if(_title.length()>18)
						return 4; //return 4 if input value is to long
					return 1; //return 1 if the input is valid
				}else{
					cout << _title << endl;
					return 2; //return 2 if the input is already inserted and valid
				}
		};
		
		//method to ask user input for medicine description and check input
		int askDescribe(int action){
			string describe;
			cout << " Enter description\t : ";
				if(action==2){
					_describe[0] = "";
					_describe[1] = "";
					_describe[2] = "";
					getline(cin, describe);
					if(describe.length() > 90)
						return 4; //return 4 if input value is to long
					stringstream ss(describe);
					string desc="", word;
					while(ss >> word){
						word += " ";
						if(word.length()>25){
							for(int i=0; i<word.length(); i++){
								desc += word.at(i);
								if(desc.length()<=30)
									_describe[0] += word.at(i);
								else if(desc.length()>30 && desc.length()<=60)
									_describe[1] += word.at(i);
								else if(desc.length()>60 && desc.length()<=90)
									_describe[2] += word.at(i);
							}
						}else{
							desc += word;
							if(desc.length()<=30)
								_describe[0] += word;
							else if(desc.length()>30 && desc.length()<=60)
								_describe[1] += word;
							else if(desc.length()>60 && desc.length()<=90)
								_describe[2] += word;
						}
					}
					return 1; //return 1 if the input is valid
				}else{
					cout << _describe[0] << endl;
					cout << "\t\t\t   " << _describe[1] << endl;
					cout << "\t\t\t   " << _describe[2] << endl;
					return 2; //return 2 if the input is already inserted and valid
				}
		};
		
		//method to ask user input for medicine title and check input
		int askPurchasePrice(int action){
			string purchasePrice;
			char* end;
			cout << " Enter purchase price\t : RM ";
				if(action==3){
					getline(cin, purchasePrice);
					if(!(this->check_double(purchasePrice))){
						return 3; //return 3 if the input is not valid
					}else if(purchasePrice.length() > 18)
						return 4; //return 4 if input value is to long
					else _purchasePrice = strtod(purchasePrice.c_str(), &end);
					return 1; //return 1 if the input is valid
				}else{
					cout << _purchasePrice << endl;
					return 2; //return 2 if the input is already inserted and valid
				}
		};
		
		//method to ask user input for medicine title and check input
		int askSoldOutPrice(int action){
			string soldOutPrice;
			char* end;
			cout << " Enter sold out price\t : RM ";
				if(action==4){
					getline(cin, soldOutPrice);
					if(!(this->check_double(soldOutPrice))){
						return 3; //return 3 if the input is not valid
					}else if(soldOutPrice.length() > 18)
						return 4; //return 4 if input value is to long
					else _soldOutPrice = strtod(soldOutPrice.c_str(), &end);
					return 1; //return 1 if the input is valid
				}else{
					cout << _soldOutPrice << endl;
					return 2; //return 2 if the input is already inserted and valid
				}
		};
		
		//method to ask user input for medicine title and check input
		int askQuantity(string type){
			string qty;
			double quantity;
			cout << endl << " Enter the value to stock " << type << " : ";
			getline(cin, qty);
			for(int i=0; i<qty.length(); i++){
				if((int)qty.at(i)<48 || (int)qty.at(i)>57)
					return 3;
			}
			if(qty.length()>14)
				return 4;
			quantity = atoi(qty.c_str());
			if(type=="in")
				_quantity = quantity;
			else if(type=="out"){
				if((_quantity - quantity)<0) //check for stock quantity
					return 2; //return 2 if the stock quantity is not enough
				else _quantity = quantity;
			}
			return 1; //return 1 if the input is valid
		};
		
		//method to read current date from computer
		void currDate(){
			time_t now = time(0);
			tm* date = localtime(&now);
			stringstream day, mon, year;
			day << date->tm_mday;
			mon << 1 + date->tm_mon;
			year << 1900 + date->tm_year;
			_date = day.str() + "/" + mon.str() + "/" + year.str();
		};
		
		//method to read current time from computer
		void currTime(){
			time_t now = time(0);
			tm* time = localtime(&now);
			stringstream hour, min, sec;
			hour << time->tm_hour;
			min << 1 + time->tm_min;
			sec << 1 + time->tm_sec;
			_time = hour.str() + ":" + min.str() + ":" + sec.str();
		};
		
		//method to set the value for variable _id
		void setId(string id){
			_id = id;
		};
		
		//method to set the value for variable _title
		void setTitle(string title){
			_title = title;
		};
		
		//method to set the value for variable _type
		void setType(string type){
			_type = type;
		};
		
		//method to set the value for variable _describe
		void setDescribe(string describe, int row){
			_describe[row] = describe;
		};
		
		//method to set the value for variable _purchasePrice
		void setPurchasePrice(double purchasePrice){
			_purchasePrice = purchasePrice;
		};
		
		//method to set the value for variable _soldOutPrice
		void setSoldOutPrice(double soldOutPrice){
			_soldOutPrice = soldOutPrice;
		};
		
		//method to set the value for variable _quantity
		void setQuantity(int quantity){
			_quantity = quantity;
		};
		
		//method to set the value for variable _date
		void setDate(string date){
			_date = date;
		};
		
		//method to set the value for variable _time
		void setTime(string time){
			_time = time;
		};
		
		//method to set the value for variable _status
		void setStatus(string status){
			_status = status;
		};
		
		//method to return the value in variable _id
		string getId(){
			return _id;
		};
		
		//method to return the value in variable _title
		string getTitle(){
			return _title;
		};
		
		//method to return the value in variable _type
		string getType(){
			return _type;
		};
		
		//method to return the value in variable _describe[0]
		string getDescribeRow1(){
			return _describe[0];
		};
		
		//method to return the value in variable _describe[1]
		string getDescribeRow2(){
			return _describe[1];
		};
		
		//method to return the value in variable _describe[2]
		string getDescribeRow3(){
			return _describe[2];
		};
		
		//method to return the value in variable _purchasePrice
		double getPurchasePrice(){
			return _purchasePrice;
		};
		
		//method to return the value in variable _soldOutPrice
		double getSoldOutPrice(){
			return _soldOutPrice;
		};
		
		//method to return the value in variable _quantity
		int getQuantity(){
			return _quantity;
		};
		
		//method to return the value in variable _date
		string getDate(){
			return _date;
		};
		
		//method to return the value in variable _time
		string getTime(){
			return _time;
		};
		
		//method to return the value in variable _status
		string getStatus(){
			return _status;
		};
		
		//methid to check empty input
		bool required(string s){
			if(s.length()==0)
				return false;
			return true;
		};
		
		//method to check input for price
		bool check_double(string s){
			int a=0, b=0;
			for(int i=0; i < s.length(); i++){
				if((int)s.at(i) < 48 || (int)s.at(i) > 57){
					if((int)s.at(i) == 46){
						a++;
						if(a>1)
							return false;
					}else{
						b++;
					}
				}
			}
			if(b==0)
				return true;
		};
};
