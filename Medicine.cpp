//Filename: Medicine.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "MedicineDetail.cpp"
#include "MedicineType.cpp"

using namespace std;

class Medicine: public MedicineType{
	private:
		//stucture declaration
		struct medicine{
			MedicineDetail medicineDetail;
			medicine *next;
		}medic, *curr, *head, *temp, *newPtr, *row, *prev;
		int test;
		
	public:
		//constructor for class Medicine
		Medicine(){
			test = 0;
		};
		
		//destructor for class Medicine
		~Medicine(){};
		
		//method to add a medicine record
		void addMedicine(string type){
			add:
				system("cls");
				medic.medicineDetail.setType(type);
				medic.medicineDetail.printMedicineType();
				cout << "-----------------------------------------------------------------" << endl;
				cin.sync();
				//ask input for medicine id
				int askInput = medic.medicineDetail.askId(test);
				if(askInput==1){
					string id = medic.medicineDetail.getId();
					if(this->searching(id)==true){
						MedicineType::loading("Check id", 1, "");
						cout << endl << " The ID is already exist... Pleadt try again..." << endl;
						getch();
						goto add;
					}else ++test;
					medic.medicineDetail.setId(id);
					medic.medicineDetail.setType(type);
				}else if(askInput==3){
					MedicineType::alert(2, "Empty");
					goto add;
				}else if(askInput==4){
					MedicineType::alert(3, "15");
					goto add;
				}
				//ask input for medicine title
				askInput = medic.medicineDetail.askTitle(test);
				if(askInput==1)
					++test;
				else if(askInput==3){
					MedicineType::alert(2, "Empty");
					goto add;
				}else if(askInput==4){
					MedicineType::alert(3, "18");
					goto add;
				}
				//ask input for medicine description
				askInput = medic.medicineDetail.askDescribe(test);
				if(askInput==1)
					++test;
				else if(askInput==4){
					MedicineType::alert(3, "80");
					goto add;
				}
				//ask input for medicine purchase price
				askInput = medic.medicineDetail.askPurchasePrice(test);
				if(askInput==1)
					++test;
				else if(askInput==3){
					MedicineType::alert(1, "price");
					goto add;
				}else if(askInput==4){
					MedicineType::alert(3, "18");
					goto add;
				}
				//ask input for medicine sold out price
				askInput = medic.medicineDetail.askSoldOutPrice(test);
				if(askInput==1)
					++test;
				else if(askInput==3){
					MedicineType::alert(1, "price");
					goto add;
				}else if(askInput==4){
					MedicineType::alert(3, "18");
					goto add;
				}
				medic.medicineDetail.setQuantity(0);
			
			if(MedicineType::openfw(1, "medicine_record.txt")=="0"){
				perror(" Error open file : ");
				system("pause");
			}else{
				this->writeToFile();
				w.close();
				this->updateMedicine();
				MedicineType::loading("Adding", 2, "");
				cout << endl << " Medicine : " << medic.medicineDetail.getTitle() << " add successful!!" << endl;
			}
			w.close();
			test = 0;
			cout << endl << "\t";
			system("pause");
		};
		
		//method to edit a medicine data
		void editMedicine(){
			system("cls");
			if(this->medicineList()){
				string id;
				cout << endl << " Enter id to edit : ";
				getline(cin, id);
				MedicineType::loading("Searching", 2, "");
				system("cls");
				string oldf = MedicineType::openfr(1, "medicine_record.txt");
				if(oldf=="0"){
					cout << endl << endl << " Currently do not insert for any record..." << endl;
				}else{
					r.close();
					if(!searching(id)){
						cout << endl << endl << " The id " << id << " is not found... Please try again..." << endl;
					}else{
						MedicineType::openfr(1, "medicine_record.txt");
						int choice=99;
						int type;
						string newf = MedicineType::openfw(1, "temp.txt");
						r.seekg(0, ios::beg);
						while(this->readFromFile()){
							if(id==medic.medicineDetail.getId()){
								while(choice!=0){
									int askInput;
									system("cls");
									medic.medicineDetail.displayMedicine(0);
									cout << "-------------------------------------------------------------------------" << endl << endl;
									cout << " Update for >> " << endl;
									cout << " 1. Title" << endl;
									cout << " 2. Type" << endl;
									cout << " 3. Description" << endl;
									cout << " 4. Buy in price" << endl;
									cout << " 5. Sold out price" << endl;
									cout << " 0. Save and Exit" << endl;
									cout << endl << " Enter your choice >> ";
									if(!(cin >> choice)){
										cin.clear();
										cin.ignore(1000,'\n');
									}
									cin.sync();
									if(choice==1){
										//code to edit title
										askInput = medic.medicineDetail.askTitle(1);
										if(askInput==3){
											MedicineType::alert(2, "Empty");
										}else if(askInput==4){
											MedicineType::alert(3, "18");
										}
									}else if(choice==2){
										//code to edit type
										int position = r.tellg();
										r.close();
										medic.medicineDetail.setType(MedicineType::getType(MedicineType::displayType("update")));
										MedicineType::openfr(1, "medicine_record.txt");
										r.seekg(position, ios::beg);
									}else if(choice==3){
										//code to edit description
										askInput = medic.medicineDetail.askDescribe(2);
										if(askInput==4){
											MedicineType::alert(3, "80");
										}
									}else if(choice==4){
										//code to edit buy in price
										askInput = medic.medicineDetail.askPurchasePrice(3);
										if(askInput==3){
											MedicineType::alert(1, "price");
										}else if(askInput==4){
											MedicineType::alert(3, "18");
										}
									}else if(choice==5){
										//code to edit sold out price
										askInput = medic.medicineDetail.askSoldOutPrice(4);
										if(askInput==3){
											MedicineType::alert(1, "price");
										}else if(askInput==4){
											MedicineType::alert(3, "18");
										}
									}else if(choice==0){
										break;
									}else{
										MedicineType::alert(1, "choice");
									}
								}
							}
								this->writeToFile();
						}
						r.close();
						w.close();
						int test=0;
						if(remove(oldf.c_str()))
							perror(" Error remove file : ");
						else ++test;
						if(rename(newf.c_str(), oldf.c_str()))
							perror(" Error rename file : ");
						else ++test;
						if(test==2){
							this->updateMedicine();
							MedicineType::loading("Editing", 2, "");
							cout << endl << " Medicine id : " << id << " edited!!" << endl;
						}
					}
				}
				r.close();
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to manage quantity
		void manageQuantity(string id, int qty, string type){
			string oldf = openfr(1, "medicine_record.txt");
			string newf = openfw(1, "temp.txt");
			while(this->readFromFile()){
				if(medic.medicineDetail.getId()==id){
					if(type=="in")
						medic.medicineDetail.setQuantity((medic.medicineDetail.getQuantity() + qty));
					else if(type=="out")
						medic.medicineDetail.setQuantity((medic.medicineDetail.getQuantity() - qty));
				}
				this->writeToFile();
			}
			r.close();
			w.close();
			if(remove(oldf.c_str()))
				perror(" Error remove file : ");
			if(rename(newf.c_str(), oldf.c_str()))
				perror(" Error rename file : ");
			this->updateMedicine();
		};
		
		//method to view all medicine record
		void viewMedicine(string type, int count, int check){
			system("cls");
			int sorting = count % 2;
			int i=0;
			int colWidth=16, noWidth=4, titleWidth=20, descWidth=35, priceWidth=20;
			int width = (colWidth*2) + noWidth + (titleWidth*2) + descWidth + (priceWidth*2);
			int desc = noWidth + colWidth + (titleWidth*2) + descWidth;
			if(this->medicineListArrange(type, sorting)){
				
				//instruction
				cout << endl << "Enter 1 >> ID "; if(type=="id") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 2 >> Title "; if(type=="title") this->displaySort(sorting); else cout << "\t";
				cout << "\tEnter 3 >> Type "; if(type=="type") this->displaySort(sorting); else cout << "\t";
				cout << "\tEnter 4 >> Quantity "; if(type=="qty") this->displaySort(sorting); else cout << "\t\t";
				cout << "\tEnter 0 >> exit" << endl;
				
				//table header
				cout << setfill('=') << setw(width) << "=" << endl;
				cout << setfill(' ') << fixed;
				cout << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
					 << "Title" << setw(titleWidth) << "Type" << setw(descWidth)
					 << "Description" << setw(priceWidth) << "Purchase Price" << setw(priceWidth)
					 << "Sold Out Price" << setw(colWidth) << "Quantity" << endl;
				cout << setfill('-') << setw(width) << "-" << endl;
				cout << setfill(' ') << fixed;
				
				//table body
				curr=head;
				while(curr!=NULL){
					cout << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->medicineDetail.getId() << setw(titleWidth)
						 << curr->medicineDetail.getTitle() << setw(titleWidth) << curr->medicineDetail.getType() << setw(descWidth)
						 << curr->medicineDetail.getDescribeRow1() << setprecision(2) << setw(priceWidth) << curr->medicineDetail.getPurchasePrice() << setprecision(2)
						 << setw(priceWidth) << curr->medicineDetail.getSoldOutPrice() << setprecision(0) << setw(colWidth) << curr->medicineDetail.getQuantity() << endl;
					cout << setw(desc) << curr->medicineDetail.getDescribeRow2() << endl;
					cout << setw(desc) << curr->medicineDetail.getDescribeRow3() << endl;
					curr=curr->next;
				}
				
				//table end line
				cout << setfill('=') << setw(width) << "=" << endl;
				
				cout << endl << " Enter choice >> ";
				char choice = getch();
				cout << choice << endl;
				if(choice!='0' && choice!='1' && choice!='2' && choice!='3' && choice!='4'){
					MedicineType::alert(1, "choice");
					this->viewMedicine("id", 0, 0);
				}else if(choice=='1'){
					if(check==choice)
						++count;
					else count=0;
					this->viewMedicine("id", count, choice);
				}else if(choice=='2'){
					if(check==choice)
						++count;
					else count=0;
					this->viewMedicine("title", count, choice);
				}else if(choice=='3'){
					if(check==choice)
						++count;
					else count=0;
					this->viewMedicine("type", count, choice);
				}else if(choice=='4'){
					if(check==choice)
						++count;
					else count=0;
					this->viewMedicine("qty", count, choice);
				}
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
				cout << endl << "\t";
				system("pause");
			}
		};
		
		//method to search a medicine detail
		string searchMedicine(){
			system("cls");
			string id;
			if(this->medicineList()){
				cout << endl << " Enter id to search : ";
				getline(cin, id);
				MedicineType::loading("Searching", 2, "");
				system("cls");
				if(MedicineType::openfr(1, "medicine_record.txt")=="0"){
					cout << endl << endl << " Currently do not insert for any record..." << endl;
					id = "0";
				}else{
					r.close();
					if(!searching(id)){
						cout << endl << endl <<  " The Medicine : " << id << " is not found... Please try again..." << endl;
						id = "0";
					}else{
						medic.medicineDetail.displayMedicine(1);
					}
				}
				r.close();
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
				id = "0";
			}
			return id;
		};
		
		//method to delete a medicine detail
		void deleteMedicine(){
			system("cls");
			if(this->medicineList()){
				string id;
				cout << endl << " Enter id to delete : ";
				getline(cin, id);
				MedicineType::loading("Searching", 2, "");
				system("cls");
				string oldf = MedicineType::openfr(1, "medicine_record.txt");
				if(oldf=="0"){
					cout << endl << endl << " Currently do not insert for any record..." << endl;
				}else{
					r.close();
					if(!searching(id)){
						cout << endl << endl << " The id " << id << " is not found... Please try again..." << endl;
					}else{
						MedicineType::openfr(1, "medicine_record.txt");
						char choose='0';
						string newf = MedicineType::openfw(1, "temp.txt");
						r.seekg(0, ios::beg);
						while(this->readFromFile()==true){
							if(id==medic.medicineDetail.getId()){
								while(choose=='0'){
										medic.medicineDetail.displayMedicine(0);
									cout << "-------------------------------------------------------------------------" << endl << endl;
									cout << endl << " Are you sure to delete the record? [Y/N] " << endl;
									choose = getch();
									if(choose=='N'||choose=='n'){
										cout << endl << " The record is still remain." << endl;
										this->writeToFile();
									}else if(choose!='Y'&&choose!='y'){
										MedicineType::alert(1, "confirmation");
										system("cls");
										choose='0';
									}
								}
								
							}else
								this->writeToFile();
						}
						r.close();
						w.close();
						int test=0;
						if(remove(oldf.c_str()))
							perror(" Error remove file : ");
						else ++test;
						if(rename(newf.c_str(), oldf.c_str()))
							perror(" Error rename file : ");
						else ++test;
						string checkFile = openfr(1, "medicine_record.txt");
						if(this->readFromFile()==false){
							r.close();
							if(remove(checkFile.c_str()))
							perror(" Error remove file : ");
								else ++test;
						}
						r.close();
						
						if(test==2 && (choose=='Y'||choose=='y')){
							this->updateMedicine();
							MedicineType::loading("Deleting", 2, "");
							cout << endl << endl  << " Medicine id : " << id << " deleted!!" << endl;
						}else if(test==3 && (choose=='Y'||choose=='y')){
							this->updateMedicine();
							MedicineType::loading("Deleting", 2, "");
							cout << endl << endl  << " Medicine id : " << id << " deleted!!" << endl;
							cout << " There is no more record of in the file, the file had been removed!!" << endl;
						}
					}
				}
				r.close();
			}else{
				cout << endl << endl << " Currently do not insert for any record..." << endl;
			}
			cout << endl << "\t";
			system("pause");
		};
		
		//method to clear all medicine record
		void clearMedicine(){
			if(this->medicineList()){
				char choose='0';
				while(choose=='0'){
					system("cls");
					cout << endl << " All the rocord can not be recovery after clear..." << endl;
					cout << " Are you sure to clear all the record? [Y/N]" << endl;
					choose = getch();
					if(choose=='Y' || choose=='y'){
						string delf=openfr(1, "medicine_record.txt");
						if(delf=="0"){
								cout << endl << endl << " Currently do not insert for any record..." << endl;
							r.close();
						}else{
							r.close();
							if(remove(delf.c_str()))
								perror(" Error remove file : ");
							else{
								if(remove("database/type_list.txt"))
									perror(" Error remove file : ");
								this->updateMedicine();
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
		
		//method to clear medicine record by type
		void clearMedicineByType(){
			if(this->medicineList()){
				char choose='0';
				while(choose=='0'){
					system("cls");
					cout << endl << " All the rocord can not be recovery after clear..." << endl;
					cout << " Are you sure to clear all the record? [Y/N]" << endl;
					choose = getch();
					if(choose=='Y' || choose=='y'){
						string oldf = MedicineType::openfr(1, "medicine_record.txt");
						if(oldf=="0"){
							cout << endl << endl << " Currently do not insert for any record..." << endl;
						}else{
							r.close();
							string clear = MedicineType::deleteType();
							if(clear!="0"){
								MedicineType::openfr(1, "medicine_record.txt");
								string newf = MedicineType::openfw(1, "temp.txt");
								r.seekg(0, ios::beg);
								while(this->readFromFile()==true){
									if(clear!=medic.medicineDetail.getType())
										this->writeToFile();
								}
								r.close();
								w.close();
								int test=0;
								if(remove(oldf.c_str()))
									perror(" Error remove file : ");
								else ++test;
								if(rename(newf.c_str(), oldf.c_str()))
									perror(" Error rename file : ");
								else ++test;
								string checkFile = openfr(1, "medicine_record.txt");
								if(this->readFromFile()==false){
									r.close();
									if(remove(checkFile.c_str()))
									perror(" Error remove file : ");
										else ++test;
								}
								r.close();
								if(test==2){
									this->updateMedicine();
									MedicineType::loading("Processing", 2, "");
									cout << endl << endl  << " Medicine record for type " << clear << " is clear!!" << endl;
								}else if(test==3){
									this->updateMedicine();
									MedicineType::loading("Processing", 2, "");
									cout << endl << endl  << " Medicine record for type " << clear << " is clear!!" << endl;
									cout << " There is no more record of in the file, the file had been removed!!" << endl;
								}
							}	
						}
						r.close();
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
				while(this->readFromFile()==true){
					if(id==medic.medicineDetail.getId()){
						r.close();
						return true;
					}
				}
			}
			r.close();
			return false;
		};
		
		//method to list all medicine with link-list
		bool medicineList(){
			if(openfr(1, "medicine_record.txt")!="0"){
				head=NULL;
				while(this->readFromFile()!=false){
					newPtr = new medicine;
					newPtr->medicineDetail = medic.medicineDetail;
					newPtr->next = NULL;
					
					if(head==NULL){
						head=newPtr;
						curr=head;
					}else{
						curr->next=newPtr;
						curr=newPtr;
					}
				}
				r.close();
				return true;
			}
			r.close();
			return false;
		};
		
		//method to arrange list
		bool medicineListArrange(string type, int sort){
			if(this->medicineList()){
				row=head;
				while(row!=NULL){
					curr=head;
					prev=NULL;
					while(curr->next!=NULL){
						//sort by id in ascending oder
						if(type=="id" && sort==0){
							if(curr->medicineDetail.getId() > curr->next->medicineDetail.getId()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by id in descending oder
						else if(type=="id" && sort==1){
								if(curr->medicineDetail.getId() < curr->next->medicineDetail.getId()){
									temp=curr->next;
									curr->next=temp->next;
									temp->next=curr;
									if(curr==head){
										head=temp;
										row=head;
									}
									else prev->next=temp;
								}else
									curr=curr->next;
						}
						//sort by title in ascending oder
						else if(type=="title" && sort==0){
							if(curr->medicineDetail.getTitle() > curr->next->medicineDetail.getTitle()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by title in descending oder
						else if(type=="title" && sort==1){
							if(curr->medicineDetail.getTitle() < curr->next->medicineDetail.getTitle()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by type in ascending oder
						else if(type=="type" && sort==0){
							if(curr->medicineDetail.getType() > curr->next->medicineDetail.getType()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by type in descending oder
						else if(type=="type" && sort==1){
							if(curr->medicineDetail.getType() < curr->next->medicineDetail.getType()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by quantity in ascending oder
						else if(type=="qty" && sort==0){
							if(curr->medicineDetail.getQuantity() > curr->next->medicineDetail.getQuantity()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						//sort by quantity in descending oder
						else if(type=="qty" && sort==1){
							if(curr->medicineDetail.getQuantity() < curr->next->medicineDetail.getQuantity()){
								temp=curr->next;
								curr->next=temp->next;
								temp->next=curr;
								if(curr==head){
									head=temp;
									row=head;
								}
								else prev->next=temp;
							}else
								curr=curr->next;
						}
						
						if(head->next==curr){
							prev=head;
						}else prev=prev->next;
					}
					row=row->next;
				}
				return true;
			}
			return false;
		};
		
		//method to save all medicine into file with table form
		void printMedicine(string type, int sort){
			int i=0;
			int colWidth=16, noWidth=4, titleWidth=20, descWidth=35, priceWidth=20;
			int width = (colWidth*2) + noWidth + (titleWidth*2) + descWidth + (priceWidth*2);
			int desc = noWidth + colWidth + (titleWidth*2) + descWidth;
			
			this->medicineListArrange(type, sort);
			
			//table header
			w << setfill('=') << setw(width) << "=" << endl;
			w << setfill(' ') << fixed;
			w << setw(noWidth) << "No." << setw(colWidth) << "ID" << setw(titleWidth)
				 << "Title" << setw(titleWidth) << "Type" << setw(descWidth)
				 << "Description" << setw(priceWidth) << "Purchase Price" << setw(priceWidth)
				 << "Sold Out Price" << setw(colWidth) << "Quantity" << endl;
			w << setfill('-') << setw(width) << "-" << endl;
			w << setfill(' ') << fixed;
			
			//table body
			curr=head;
			while(curr!=NULL){
				w << setprecision(0) << setw(noWidth) << ++i << setw(colWidth) << curr->medicineDetail.getId() << setw(titleWidth)
					 << curr->medicineDetail.getTitle() << setw(titleWidth) << curr->medicineDetail.getType() << setw(descWidth)
					 << curr->medicineDetail.getDescribeRow1() << setprecision(2) << setw(priceWidth) << curr->medicineDetail.getPurchasePrice() << setprecision(2)
					 << setw(priceWidth) << curr->medicineDetail.getSoldOutPrice() << setprecision(0) << setw(colWidth) << curr->medicineDetail.getQuantity() << endl;
				w << setw(desc) << curr->medicineDetail.getDescribeRow2() << endl;
				w << setw(desc) << curr->medicineDetail.getDescribeRow3() << endl;
				curr=curr->next;
			}
			
			//table end line
			w << setfill('=') << setw(width) << "=" << endl;
		};
		
		//method to update file
		void updateMedicine(){
			remove("record/medicine/medicine_record - by id (ASC).txt");
			remove("record/medicine/medicine_record - by id (DESC).txt");
			remove("record/medicine/medicine_record - by title (ASC).txt");
			remove("record/medicine/medicine_record - by title (DESC).txt");
			remove("record/medicine/medicine_record - by type (ASC).txt");
			remove("record/medicine/medicine_record - by type (DESC).txt");
			remove("record/medicine/medicine_record - by qty (ASC).txt");
			remove("record/medicine/medicine_record - by qty (DESC).txt");
			
			if(this->medicineList()){
				openfw(2, "medicine_record - by id (ASC).txt");
				this->printMedicine("id", 0);
				w.close();
				openfw(2, "medicine_record - by id (DESC).txt");
				this->printMedicine("id", 1);
				w.close();
				openfw(2, "medicine_record - by title (ASC).txt");
				this->printMedicine("title", 0);
				w.close();
				openfw(2, "medicine_record - by title (DESC).txt");
				this->printMedicine("title", 1);
				w.close();
				openfw(2, "medicine_record - by type (ASC).txt");
				this->printMedicine("type", 0);
				w.close();
				openfw(2, "medicine_record - by type (DESC).txt");
				this->printMedicine("type", 1);
				w.close();
				openfw(2, "medicine_record - by qty (ASC).txt");
				this->printMedicine("qty", 0);
				w.close();
				openfw(2, "medicine_record - by qty (DESC).txt");
				this->printMedicine("qty", 1);
				w.close();
			}
		};
		
		//method to print medicine into table by type
		void printMedicineByType();
		
		//method to write medicine data into .txt file
		void writeToFile(){
			w << medic.medicineDetail.getId() << endl;
			w << medic.medicineDetail.getTitle() << endl;
			w << medic.medicineDetail.getType() << endl;
			w << medic.medicineDetail.getDescribeRow1() << endl;
			w << medic.medicineDetail.getDescribeRow2() << endl;
			w << medic.medicineDetail.getDescribeRow3() << endl;
			w << medic.medicineDetail.getPurchasePrice() << endl;
			w << medic.medicineDetail.getSoldOutPrice() << endl;
			w << medic.medicineDetail.getQuantity() << endl;
		};
		
		//method to read medicine data from .txt file
		bool readFromFile(){
			char* end;
			string empty, id, title, type, describe[3], pPrice="", sOutPrice="";
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
			
			purchasePrice = strtod(pPrice.c_str(), &end);
			soldOutPrice = strtod(sOutPrice.c_str(), &end);
			
			medic.medicineDetail.setId(id);
			if(medic.medicineDetail.getId()=="") return false;
			medic.medicineDetail.setTitle(title);
			medic.medicineDetail.setType(type);
			medic.medicineDetail.setDescribe(describe[0], 0);
			medic.medicineDetail.setDescribe(describe[1], 1);
			medic.medicineDetail.setDescribe(describe[2], 2);
			medic.medicineDetail.setPurchasePrice(purchasePrice);
			medic.medicineDetail.setSoldOutPrice(soldOutPrice);
			medic.medicineDetail.setQuantity(quantity);
			return true;
		};
		
		void displaySort(int sort){
			if(sort==0)
				cout << "(ASC)\t";
			else if(sort==1)
				cout << "(DESC)\t";
		};
};
