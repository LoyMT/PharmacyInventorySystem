//Filename: MedicineStock.cpp
#include <iostream>
#include <iomanip>
#include "Medicine.cpp"

using namespace std;

class MedicineStock: public Medicine{
	private:
		//structure declaration
		struct medicineStock{
			MedicineDetail medicineDetail;
			medicineStock *next;
		}stock, *curr, *head, *temp, *newPtr, *row, *prev;
		
	public:
		//constructor for class MedicineStock
		MedicineStock(int argc, char *argv[]){
			MedicineType(argc, argv);
		};
		
		//destructor for class MedicineStock
		~MedicineStock(){
			MedicineType::loading("System Clossing", 2, "full");
			system("cls");
		};
		
		//method to manage stock in and stock out
		void stockManage(string type){
			system("cls");
			if(Medicine::medicineList()){
				string id;
				cout << endl << " Enter medicine ID to stock " << type << " : ";
				getline(cin, id);
				MedicineType::loading("Searching", 2, "");
				system("cls");
				if(!(this->searching(id))){
					cout << " The id " << id << " is not found... Please try again..." << endl;
				}else{
					int qty;
					while(qty!=1){
						stock.medicineDetail.displayMedicine(1);
						cout << "-------------------------------------------------------------------------" << endl << endl;
						if(type=="out" && stock.medicineDetail.getQuantity()==0){
							cout << endl << " Currently out of stock!!" << endl;
							break;
						}else{
							qty = stock.medicineDetail.askQuantity(type);
							if(qty==3){
								MedicineType::alert(1, "quantity");
								system("cls");
							}else if(qty==4){
								MedicineType::alert(3, "14");
								system("cls");
							}else if(qty==2){
								cout << endl << " Stock is currently not enough... Please add stock and try again... Thank!" << endl;
								break;
							}else if(qty==1){
								stock.medicineDetail.currDate();
								stock.medicineDetail.currTime();
								stock.medicineDetail.setStatus(type);
								if(openfw(1, "stock_record.txt")=="0"){
									perror(" Error create file : ");
									system("pause");
								}else{
									this->writeToFile();
									w.close();
									Medicine::manageQuantity(stock.medicineDetail.getId(), stock.medicineDetail.getQuantity(), type);
									this->updateStock();
									MedicineType::loading("Processing", 2, "");
									cout << endl << " Stock for " << stock.medicineDetail.getTitle() << " with id number " << stock.medicineDetail.getId() << " edited!!" << endl;
								}
							}
						}
					}
				}
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to display all stock record history
		void stockRecord_all(string type, int count, char check){
			system("cls");
			int i=0;
			int sorting = count % 2;
			
			int colWidth=16, noWidth=4, titleWidth=20, priceWidth=20, dateWidth=20, timeWidth=20;
			int width = (colWidth*3) + noWidth + titleWidth + (priceWidth*2) + (dateWidth*2) + timeWidth;
			if(this->stockList(type, sorting)){
				
				//instruction
				cout << endl << "Enter 1 >> All "; if(type=="all") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 2 >> Stock In "; if(type=="in") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 3 >> Stock Out "; if(type=="out") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 0 >> exit" << endl;
				//table header
				cout << setfill('=') << setw(width) << "=" << endl;
				cout << setfill(' ') << fixed;
				cout << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
					 << "Title" << setw(dateWidth) << "Type" << setw(priceWidth)
					 << "Purchase Price" << setw(priceWidth) << "Sold Out Price" << setw(dateWidth)
					 << "Date" << setw(timeWidth) << "Time" << setw(colWidth) << "Quantity"
					 << setw(colWidth) << "Status" << endl;
				cout << setfill('-') << setw(width) << "-" << endl;
				cout << setfill(' ') << fixed;
					 
				//table body
				curr=head;
				while(curr!=NULL){
					cout << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->medicineDetail.getId() << setw(titleWidth)
						 << curr->medicineDetail.getTitle() << setw(dateWidth) << curr->medicineDetail.getType() << setprecision(2) << setw(priceWidth)
						 << curr->medicineDetail.getPurchasePrice() << setprecision(2) << setw(priceWidth) << curr->medicineDetail.getSoldOutPrice()
						 << setw(dateWidth) << curr->medicineDetail.getDate() << setw(timeWidth) << curr->medicineDetail.getTime()
						 << setprecision(0) << setw(colWidth) << curr->medicineDetail.getQuantity() << setw(colWidth) << curr->medicineDetail.getStatus() << endl;
					curr=curr->next;
				}
					 
				//table end
				cout << setfill('=') << setw(width) << "=" << endl;
				
				cout << endl << " Enter choice >> ";
				char choice = getch();
				cout << choice << endl;
				if(choice!='0' && choice!='1' && choice!='2' && choice!='3'){
					MedicineType::alert(1, "choice");
					this->stockRecord_all("all", 0, 0);
				}else if(choice=='1'){
					if(check==choice)
						++count;
					else count=0;
					this->stockRecord_all("all", count, choice);
				}else if(choice=='2'){
					if(check==choice)
						++count;
					else count=0;
					this->stockRecord_all("in", count, choice);
				}else if(choice=='3'){
					if(check==choice)
						++count;
					else count=0;
					this->stockRecord_all("out", count, choice);
				}
			}else{
				cout << endl << endl << " Current do not have any stock..." << endl;
				cout << endl << "\t";
				system("pause");
			}
		};
		
		//method to display stock record history for a specific medicine
		void stockRecord_medic(string id){
			if(id!="0"){
				if(this->stockList("all", 0)){
					int i=0;
					int colWidth=16, noWidth=4, titleWidth=20, priceWidth=20, dateWidth=20, timeWidth=20;
					int width = (colWidth*3) + noWidth + titleWidth + (priceWidth*2) + (dateWidth*2) + timeWidth;
					//table header
					cout << endl << setfill('=') << setw(width) << "=" << endl;
					cout << setfill(' ') << fixed;
					cout << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
						 << "Title" << setw(dateWidth) << "Type" << setw(priceWidth)
						 << "Purchase Price" << setw(priceWidth) << "Sold Out Price" << setw(dateWidth)
						 << "Date" << setw(timeWidth) << "Time" << setw(colWidth) << "Quantity"
						 << setw(colWidth) << "Status" << endl;
					cout << setfill('-') << setw(width) << "-" << endl;
					cout << setfill(' ') << fixed;
						 
					//table body
					curr=head;
					while(curr!=NULL){
						if(curr->medicineDetail.getId()==id){
							cout << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->medicineDetail.getId() << setw(titleWidth)
								 << curr->medicineDetail.getTitle() << setw(dateWidth) << curr->medicineDetail.getType() << setprecision(2) << setw(priceWidth)
								 << curr->medicineDetail.getPurchasePrice() << setprecision(2) << setw(priceWidth) << curr->medicineDetail.getSoldOutPrice()
								 << setw(dateWidth) << curr->medicineDetail.getDate() << setw(timeWidth) << curr->medicineDetail.getTime()
								 << setprecision(0) << setw(colWidth) << curr->medicineDetail.getQuantity() << setw(colWidth) << curr->medicineDetail.getStatus() << endl;
						}
						curr=curr->next;
					}
						 
					//table end
					cout << setfill('=') << setw(width) << "=" << endl;
				}
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to clear stock history
		void cleatStockHistory(){
			if(this->stockList("all", 0)){
				char choose='0';
				while(choose=='0'){
					system("cls");
					cout << endl << " All the rocord can not be recovery after clear..." << endl;
					cout << " Are you sure to clear all the record? [Y/N]" << endl;
					choose = getch();
					if(choose=='Y' || choose=='y'){
						string delf=openfr(1, "stock_record.txt");
						if(delf=="0"){
								cout << endl << endl << " Currently do not insert for any record..." << endl;
							r.close();
						}else{
							r.close();
							if(remove(delf.c_str()))
								perror(" Error remove file : ");
							else{
								this->updateStock();
								MedicineType::loading("Processing", 2, "");
								cout << endl << endl  << " All the record had been clear..." << endl;
							}
						}
					}else if(choose=='N' || choose=='n'){
						cout << endl << endl  << " The record is still remain. Thank you!!" << endl;
					}else{
						MedicineType::alert(1, "confirmation");
						choose='0';
					}
				}
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to search for existence of a medicine
		bool searching(string id){
			if(openfr(1, "medicine_record.txt")!="0"){
				while(this->readFromFile(0)==true){
					if(id==stock.medicineDetail.getId()){
						r.close();
						return true;
					}
				}
			}
			r.close();
			return false;
		};
		
		//method to list all medicine with link-list
		bool stockList(string type, int sort){
			if(openfr(1, "stock_record.txt")!="0"){
				head=NULL;
				while(this->readFromFile(1)!=false){
					newPtr = new medicineStock;
					newPtr->medicineDetail = stock.medicineDetail;
					newPtr->next = NULL;
					if(type=="all"){
						if(sort==0){
							if(head==NULL){
								head=newPtr;
								curr=head;
							}else{
								curr->next=newPtr;
								curr=newPtr;
							}
						}else if(sort==1){
							if(head!=NULL)
								newPtr->next=head;
							head=newPtr;
						}
					}else if(stock.medicineDetail.getStatus()==type){
						if(sort==0){
							if(head==NULL){
								head=newPtr;
								curr=head;
							}else{
								curr->next=newPtr;
								curr=newPtr;
							}
						}else if(sort==1){
							if(head!=NULL)
								newPtr->next=head;
							head=newPtr;
						}
					}
				}
				r.close();
				return true;
			}
			r.close();
			return false;
		};
		
		//method to print all medicine into table
		void printStock(string type, int sort){
			int i=0;
			
			int colWidth=16, noWidth=4, titleWidth=20, priceWidth=20, dateWidth=20, timeWidth=20;
			int width = (colWidth*3) + noWidth + titleWidth + (priceWidth*2) + (dateWidth*2) + timeWidth;
			this->stockList(type, sort);
				
			//table header
			w << setfill('=') << setw(width) << "=" << endl;
			w << setfill(' ') << fixed;
			w << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
				 << "Title" << setw(dateWidth) << "Type" << setw(priceWidth)
				 << "Purchase Price" << setw(priceWidth) << "Sold Out Price" << setw(dateWidth)
				 << "Date" << setw(timeWidth) << "Time" << setw(colWidth) << "Quantity"
				 << setw(colWidth) << "Status" << endl;
			w << setfill('-') << setw(width) << "-" << endl;
			w << setfill(' ') << fixed;
				 
			//table body
			curr=head;
			while(curr!=NULL){
				w << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->medicineDetail.getId() << setw(titleWidth)
					 << curr->medicineDetail.getTitle() << setw(dateWidth) << curr->medicineDetail.getType() << setprecision(2) << setw(priceWidth)
					 << curr->medicineDetail.getPurchasePrice() << setprecision(2) << setw(priceWidth) << curr->medicineDetail.getSoldOutPrice()
					 << setw(dateWidth) << curr->medicineDetail.getDate() << setw(timeWidth) << curr->medicineDetail.getTime()
					 << setprecision(0) << setw(colWidth) << curr->medicineDetail.getQuantity() << setw(colWidth) << curr->medicineDetail.getStatus() << endl;
				curr=curr->next;
			}
				 
			//table end
			w << setfill('=') << setw(width) << "=" << endl;
		};
		
		//method to print medicine into table by type
		void updateStock(){
			remove("record/stock/all (ASC).txt");
			remove("record/stock/all (DESC).txt");
			remove("record/stock/in (ASC).txt");
			remove("record/stock/in (DESC).txt");
			remove("record/stock/out (ASC).txt");
			remove("record/stock/out (DESC).txt");
			
			if(this->stockList("all", 0)){
				openfw(3, "all (ASC).txt");
				this->printStock("all", 0);
				w.close();
				openfw(3, "all (DESC).txt");
				this->printStock("all", 1);
				w.close();
				openfw(3, "in (ASC).txt");
				this->printStock("in", 0);
				w.close();
				openfw(3, "in (DESC).txt");
				this->printStock("in", 1);
				w.close();
				openfw(3, "out (ASC).txt");
				this->printStock("out", 0);
				w.close();
				openfw(3, "out (DESC).txt");
				this->printStock("out", 1);
				w.close();
			}
		};
		
		//method to write medicine data into .txt file
		void writeToFile(){
			w << stock.medicineDetail.getId() << endl;
			w << stock.medicineDetail.getTitle() << endl;
			w << stock.medicineDetail.getType() << endl;
			w << stock.medicineDetail.getDescribeRow1() << endl;
			w << stock.medicineDetail.getDescribeRow2() << endl;
			w << stock.medicineDetail.getDescribeRow3() << endl;
			w << stock.medicineDetail.getPurchasePrice() << endl;
			w << stock.medicineDetail.getSoldOutPrice() << endl;
			w << stock.medicineDetail.getQuantity() << endl;
			w << stock.medicineDetail.getDate() << endl;
			w << stock.medicineDetail.getTime() << endl;
			w << stock.medicineDetail.getStatus() << endl;
		};
		
		//method to read medicine data from .txt file
		bool readFromFile(int TYPE){
			char* end;
			string empty, id, title, type, describe[3], pPrice, sOutPrice, date, time, status;
			double purchasePrice, soldOutPrice;
			int quantity;
			getline(r, id);
			getline(r, title);
			getline(r, type);
			getline(r, describe[0]);
			getline(r, describe[1]);
			getline(r, describe[2]);
			getline(r, pPrice);
			getline(r, sOutPrice);
			r >> quantity;
			getline(r, empty);
			if(TYPE==1){
				getline(r, date);
				getline(r, time);
				getline(r, status);
			}
			
			purchasePrice = strtod(pPrice.c_str(), &end);
			soldOutPrice = strtod(sOutPrice.c_str(), &end);
			
			stock.medicineDetail.setId(id);
			if(stock.medicineDetail.getId()=="") return false;
			stock.medicineDetail.setTitle(title);
			stock.medicineDetail.setType(type);
			stock.medicineDetail.setDescribe(describe[0], 0);
			stock.medicineDetail.setDescribe(describe[1], 1);
			stock.medicineDetail.setDescribe(describe[2], 2);
			stock.medicineDetail.setPurchasePrice(purchasePrice);
			stock.medicineDetail.setSoldOutPrice(soldOutPrice);
			stock.medicineDetail.setQuantity(quantity);
			if(TYPE==1){
				stock.medicineDetail.setDate(date);
				stock.medicineDetail.setTime(time);
				stock.medicineDetail.setStatus(status);
			}
			return true;
		};
}; 
