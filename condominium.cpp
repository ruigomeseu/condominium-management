#include "condominium.h"
#include "menu.h"
#include "Meeting.h"
long Condominium::condominiumId = 0;

/* constructor */

Condominium::Condominium(string name, float areaMultiplier, float floorMultiplier, float baseApartmentCost, float baseOfficeCost, float baseStoreCost) {
	condominiumId++;
	id = condominiumId;
	this->name = name;
	this->areaMultiplier = areaMultiplier;
	this->floorMultiplier = floorMultiplier;
	this->baseApartmentCost = baseApartmentCost;
	this->baseOfficeCost = baseOfficeCost;
	this->baseStoreCost = baseStoreCost;
}

Condominium::Condominium(long id, string name, float areaMultiplier, float floorMultiplier, float baseApartmentCost, float baseOfficeCost, float baseStoreCost) {
	condominiumId = id;
	this->id = id;
	this->name = name;
	this->areaMultiplier = areaMultiplier;
	this->floorMultiplier = floorMultiplier;
	this->baseApartmentCost = baseApartmentCost;
	this->baseOfficeCost = baseOfficeCost;
	this->baseStoreCost = baseStoreCost;
}

/* add/remove functions */

bool Condominium::removeProperty(Property* property){
	string propertyAdd = property->getAddress();
	for (unsigned int i = 0; i < properties.size(); i++)
	{
		if(propertyAdd == properties[i]->getAddress()){
			properties.erase(properties.begin()+ i);
			return true; // if it has been erased
		}
	}
	return false; // if the property to erase doesn't exist
}

void Condominium::addMaintenance(Maintenance* m1){
	maintenance.push_back(m1);
}

void Condominium::addProperty(Property* p1){
	properties.push_back(p1);
	vector<float> baseCost;
	baseCost.push_back(areaMultiplier);
	baseCost.push_back(floorMultiplier);
	switch (p1->returnType()) {
	case 1:
		baseCost.push_back(baseApartmentCost);
		break;
	case 2:
		baseCost.push_back(baseOfficeCost);
		break;
	case 3:
		baseCost.push_back(baseStoreCost);
		break;
	default:
		break;
	}

	Equity e1(p1->getFloor(),p1->getArea(),p1->getAddress(),baseCost,p1->getOwnerId());
	priorProperties.push(e1);
}

void Condominium::addProptoCond(vector <Owner*> owners) {
	string address;
	float area;
	int floor;
	if(owners.size()>0) {
		Menu Menu("Which type of property would you like to build?\n");
		Menu.addMenuItem("Apartment");
		Menu.addMenuItem("Office");
		Menu.addMenuItem("Store");
		Menu.addMenuItem("Go BACK to the PREVIOUS menu");
		while(Menu.isActive()) {
			switch(Menu.showMenu()) {
			case 1:{
				address = Menu::promptString("Apartament Address: ");
				area = Menu::promptFloat("Apartment Area: ");
				floor = Menu::promptInt("Which floor is the apartment? ");
				cout << "Which owner will be living here? " << endl;
				Owner* owner = getOwnerFromList(owners);
				this->addProperty(new Apartment(address, area, floor,owner));
				break;
			}
			case 2:{
				address = Menu::promptString("Office Address: ");
				area = Menu::promptFloat("Office Area: ");
				floor = Menu::promptInt("Which floor is the office? ");
				cout << "Which owner will be living here?  " << endl;
				Owner* owner = getOwnerFromList(owners);
				this->addProperty(new Office(address, area, floor,owner));
				break;
			}
			case 3:{
				address = Menu::promptString("Store Address: ");
				area = Menu::promptFloat("Store Area: ");
				floor = Menu::promptInt("Which floor is the store? ");
				cout << "Which owner will be living here?  " << endl;
				Owner* owner = getOwnerFromList(owners);
				this->addProperty(new Store(address, area, floor,owner));
				break;
			}
			default:
				break;
			}
			Menu.toggleMenu();
		}
		//save the properties
		saveProperties();
	} else {
		cout << "There are no Owners yet." << endl << "Please go back to the Main Menu and add a Owner to continue." << endl << endl;
	}
}

void Condominium::addMaintenanceToCondominium(vector <Worker*> workers) {
	string name = Menu::promptString("Maintenance Name: ");
	Menu typeMenu("Maintenance Schedule");
	typeMenu.addMenuItem("Monthly");
	typeMenu.addMenuItem("Trimestral");
	typeMenu.addMenuItem("Annually");
	int type = typeMenu.showMenu() - 1;
	float duration = Menu::promptFloat("How long will each maintenance take? ");
	cout << "Which worker will do this task? " << endl;
	Worker* worker = getWorkerFromList(workers);
	this->addMaintenance(new Maintenance(type,duration,name,worker));
	saveMaintenances();
}


/* GET FUNCTIONS */

int Condominium::getId() {
	return id;
}

string Condominium::getName() {
	return name;
}

float Condominium::getAreaMultiplier() {
	return areaMultiplier;
}

float Condominium::getFloorMultiplier() {
	return floorMultiplier;
}

float Condominium::getBaseApartmentCost() {
	return baseApartmentCost;
}

float Condominium::getBaseOfficeCost() {
	return baseOfficeCost;
}

float Condominium::getBaseStoreCost() {
	return baseStoreCost;
}

Worker* Condominium::getWorkerFromList(vector <Worker*> workers) {

	Menu workersMenu("Workers List");
	for (unsigned int i=0; i<workers.size(); i++) {
		workersMenu.addMenuItem(workers[i]->getName());
	}
	workersMenu.addMenuItem("Go back to the PREVIOUS menu");
	unsigned int option=workersMenu.showMenu();
	if(option>workers.size()){
		return 0;
	} else {
		return workers[option-1];
	}
}

Owner* Condominium::getOwnerFromList(vector <Owner*> owners) {
	Menu ownersMenu("Owners List");
	for (unsigned int i=0; i<owners.size(); i++) {
		ownersMenu.addMenuItem(owners[i]->getName());
	}
	unsigned int option=ownersMenu.showMenu();
	if(option>owners.size()){
		return 0;
	} else {
		return owners[option-1];
	}
}

/* SET FUNCTIONS*/

void Condominium::setAreaMultiplier(float areaMultiplier) {
	this->areaMultiplier = areaMultiplier;
}

void Condominium::setFloorMultiplier(float floorMultiplier) {
	this->floorMultiplier = floorMultiplier;
}

void Condominium::setBaseApartmentCost(float baseApartmentCost) {
	this->baseApartmentCost = baseApartmentCost;
}

void Condominium::setBaseOfficeCost(float baseOfficeCost) {
	this->baseOfficeCost = baseOfficeCost;
}

void Condominium::setBaseStoreCost(float baseStoreCost) {
	this->baseStoreCost = baseStoreCost;
}

/*Manage functions */

void Condominium::manageCond(vector <Worker*> workers, vector<Owner*> owners,int date) {
	stringstream topic;
	topic << "Managing " << endl;
	string topic2 = topic.str();
	Menu showMenu(topic2.c_str());
	showMenu.addMenuItem("Add a new property");
	showMenu.addMenuItem("Remove property");
	showMenu.addMenuItem("Manage the existing properties");
	showMenu.addMenuItem("Add maintenance task");
	showMenu.addMenuItem("Remove maintenance task");
	showMenu.addMenuItem("Manage the existing maintenance tasks");
	showMenu.addMenuItem("Manage the condominium fixed values");
	showMenu.addMenuItem("Confirm meeting's attendances");
	showMenu.addMenuItem("Check past Meetings");
	showMenu.addMenuItem("Go BACK to the previous Menu");

	while(showMenu.isActive()) {
		switch(showMenu.showMenu()) {
		case 1:
			//add
			addProptoCond(owners);
			break;
		case 2:
			//remove
			if(this->isEmpty()) {
				cout << "There are no properties yet. Please add one property first." << endl << endl;
			} else {
				removePropertyFromCond();
			}
			break;
		case 3:
			//manage properties
			if(this->isEmpty()) {
				cout << "There are no properties yet. Please add one property first." << endl << endl;
			} else {
				managePropertyFromCond(owners);
			}
			break;
		case 4:
			if(workers.size()==0) {
				cout << "There are no workers yet. Please add one worker from the Main Menu first." << endl << endl;
			} else {
				addMaintenanceToCondominium(workers);
			}
			break;
		case 5:
			if(workers.size()==0) {
				cout << "There are no workers yet. Please add one worker from the Main Menu first." << endl << endl;
			} else {
				removeMaintenanceFromCond();
			}
			break;
		case 6:
			if(maintenance.size()==0) {
				cout << "There are no maintenances yet. Please add one first." << endl << endl;
			} else {
				manageTaskFromCond(workers);
			}
			break;
		case 7:
			manageCondFixedValues();
			break;
		case 8:{
			if(meetings.size()==0) {
				cout << "There are no meetings yet. Please schedule one first." << endl << endl;
			}
			else {
				confirmAttendance(date,owners);
			}
		}
		case 9:
			if(meetings.size() == 0){
				cout << "There are no past meetings for this condominium" << endl;
			} else {
				checkLastMeetings(owners);
			}
			break;
		default:
			showMenu.toggleMenu();
			break;
		}
	}
}

void Condominium::managePropertyFromCond(vector<Owner*> owners) {
	stringstream name;
	unsigned int id;
	string newAddress;
	Menu menu("Choose one of the IDs");
	for(unsigned int i=0;i<properties.size();i++) {
		name << "Address: " << properties[i]->getAddress() << " - Owner: " << properties[i]->getOwnerName();
		menu.addMenuItem(name.str());
		name.clear();
		name.str("");
	}
	menu.addMenuItem("Go back to the PREVIOUS menu");
	id = menu.showMenu();
	if(id<=properties.size()) {
		Menu manage("Managing");
		manage.addMenuItem("Edit address");
		manage.addMenuItem("Change the dweller");
		manage.addMenuItem("Go to the PREVIOUS menu");
		while(manage.isActive()){
			switch (manage.showMenu()) {
			case 1:
				cout << "New Address: ";
				getline(cin,newAddress);
				properties[id-1]->setAddress(newAddress);
				saveProperties();
				break;
			case 2:{
				cout << "Which owner will be living here? " << endl;
				Owner* owner = getOwnerFromList(owners);
				if(owner == 0){
					break;
				}
				properties[id-1]->setOwner(owner);
				saveProperties();
				break;
			}
			case 3:
				manage.toggleMenu();
				break;
			}
		}
	}
}

void Condominium::manageTaskFromCond(vector<Worker*> workers) {
	stringstream name;
	unsigned int id,type;
	float duration;
	string newName;
	Menu menu("Choose one of the IDs");
	for(unsigned int i=0;i<maintenance.size();i++) {
		name << "Name: " << maintenance[i]->getName() << ", Type: " << maintenance[i]->printType() <<
				", Duration: " << maintenance[i]->getDuration() << ", worker: " << maintenance[i]->getWorkerName();
		menu.addMenuItem(name.str());
		name.clear();
		name.str("");
	}
	menu.addMenuItem("Go back to the PREVIOUS menu");
	id = menu.showMenu();
	if(id<=maintenance.size()) {
		Menu manage("Managing");
		manage.addMenuItem("Edit name");
		manage.addMenuItem("Edit method of payment");
		manage.addMenuItem("Edit worker");
		manage.addMenuItem("Edit duration");
		manage.addMenuItem("Go to the PREVIOUS menu");
		while(manage.isActive()){
			switch (manage.showMenu()) {
			case 1:{
				newName = Menu::promptString("New Name: ");
				maintenance[id-1]->setName(newName);
				manage.toggleMenu();
				saveMaintenances();
				break;
			}
			case 2:{
				Menu subMenu("Choose the new method");
				subMenu.addMenuItem("monthly");
				subMenu.addMenuItem("trimestral");
				subMenu.addMenuItem("annually");
				type = subMenu.showMenu();
				maintenance[id-1]->setType(type-1);
				manage.toggleMenu();
				saveMaintenances();
				break;
			}
			case 3:{
				cout << "Which worker will do the task? " << endl;
				Worker* worker = getWorkerFromList(workers);
				if(worker == 0){
					break;
				}
				maintenance[id-1]->setWorker(worker);
				saveMaintenances();
				break;
			}
			case 4:
			{
				duration = Menu::promptFloat("New maintenance duration: ");
				maintenance[id-1]->setDuration(duration);
				manage.toggleMenu();
				saveMaintenances();
				break;
			}
			case 5:
				manage.toggleMenu();
				break;
			}
		}

	}
}

/* save functions */

void Condominium::saveProperties(){
	stringstream ssfilename;
	ssfilename << "properties" << id << ".csv";
	string filename = ssfilename.str();
	ofstream file(filename.c_str());
	file << "type" << "," << "address" << "," << "area" << "," << "floor" << "," << "ownerId" << "," << "totalDue" << "," << "monthsLeft" << endl;
	for(unsigned int i = 0; i < properties.size(); i++)
	{
		file << properties[i]->returnType() << "," << properties[i]->getAddress() << "," << properties[i]->getArea() << "," << properties[i]->getFloor() << "," << properties[i]->getOwnerId() << "," << properties[i]->getDue() << "," << properties[i]->getMonthsLeft();
		if(i < (properties.size() -1))
			file << endl;
	}
	file.close();
}

void Condominium::saveMaintenances() {
	stringstream ssfilename;
	ssfilename << "maintenance" << id << ".csv";
	string filename = ssfilename.str();
	ofstream file(filename.c_str());
	file << "MonthsLeft" << "," << "Type" << "," << "Name" << "," << "WorkerId" << "," << "Duration" << endl;
	for(unsigned int i = 0; i < maintenance.size(); i++){
		file << maintenance[i]->getMonth() << "," << maintenance[i]->getType() << "," << maintenance[i]->getName() << "," << maintenance[i]->getWorkerId() << "," << maintenance[i]->getDuration();
		if(i < (maintenance.size() -1))
			file << endl;
	}
	file.close();
}

void Condominium::saveMeetings() {
	stringstream ssfilename;
	ssfilename << "meetingCond" << id << ".csv";
	string filename = ssfilename.str();
	ofstream file(filename.c_str());
	file << "Date" << "," << "Subject Discussed" << "," << "Attending Owners Id"<< endl;

	for(unsigned int i=0;i<meetings.size();i++){
		file << meetings[i].getDate() <<"," <<meetings[i].getSubject() ;
		for(unsigned int j=0;j<meetings[i].getAttendance().size();j++){
			file << ",";
			if(meetings[i].getAttendance()[j]!=0){
				file << meetings[i].getAttendance()[j];
			}
		}
		if(i < (meetings.size() -1))
			file << endl;
	}
	file.close();
}
/* remove functions */

void Condominium::removePropertyFromCond() {
	stringstream name;
	unsigned int id;
	Menu menu("Choose one of the id's");
	for(unsigned int i=0;i<properties.size();i++) {
		name << "Address: " << properties[i]->getAddress();
		menu.addMenuItem(name.str());
		name.clear();
		name.str("");
	}
	menu.addMenuItem("Go back to the PREVIOUS menu");
	id = menu.showMenu();
	if(id<=properties.size()){
		properties.erase(properties.begin() + (id - 1));
		saveProperties();
	}
}

void Condominium::removeMaintenanceFromCond() {
	stringstream name;
	unsigned int id;
	Menu menu("Choose one of the id's");
	for(unsigned int i=0;i<maintenance.size();i++) {
		name << "name: " << maintenance[i]->getName() << " , method of payment: ";
		if(maintenance[i]->getType()==0){
			name << "monthly";
		}else if(maintenance[i]->getType() == 1){
			name << "trimestral";
		} else {
			name << "annually";
		}
		menu.addMenuItem(name.str());
		name.clear();
		name.str("");
	}
	menu.addMenuItem("Go back to the PREVIOUS menu");
	id = menu.showMenu();
	if(id<=maintenance.size()){
		maintenance.erase(maintenance.begin() + (id - 1));
		saveMaintenances();
	}
}

/* show & other */

bool Condominium::isEmpty() {
	if(properties.size() > 0) {
		return false;
	} else {
		return true;
	}
}

void Condominium::showCondominium() {
	cout << "Condominium ID: " << id << endl;
	cout << "Condominium Name: " << name << endl;
	cout << "Properties #: " << properties.size() << endl << endl;
}

void Condominium::showProperties() {
	for(unsigned int i = 0; i < properties.size(); i++)	{
		cout << "Property #" << i+1 << endl;
		cout << "Type: " << properties[i]->printType() << endl;
		cout << "Area: " << properties[i]->getArea() << endl;
		cout << "Floor: " << properties[i]->getFloor() << endl;
		cout << "Address: " << properties[i]->getAddress() << endl << endl;
	}
}

float Condominium::getPropertyCost(int propertyid) {
	int type = properties[propertyid]->returnType();
	float cost = (properties[propertyid]->getArea()*areaMultiplier) + (properties[propertyid]->getFloor()*floorMultiplier);
	if(type == 1) {
		cost += baseApartmentCost;
	} else if(type == 2) {
		cost += baseOfficeCost;
	} else if(type == 3) {
		cost += baseStoreCost;
	} else {
		return 0;
	}
	return cost;
}

float Condominium::getProfitLoss() {
	float revenue = 0;
	float cost = 0;
	for (unsigned int i = 0; i < properties.size(); i++) {
		if(properties[i]->payMonth()) {
			revenue += properties[i]->getDue();
			properties[i]->resetDue();
		} else {
			properties[i]->addDue(getPropertyCost(i));
		}
	}
	for (unsigned int i = 0; i < maintenance.size(); i++) {
		if(maintenance[i]->payMonth()) {
			cost += maintenance[i]->getDuration() * maintenance[i]->getWorkerWage();
		}
	}
	return (revenue-cost);
}

vector <vector <string> > Condominium::getMaintenanceReport() {
	vector <vector <string> > result;
	for(unsigned int i=0; i < maintenance.size(); i++) {
		if(maintenance[i]->payMonth()) {
			vector <string> temp;
			stringstream idConvert, workerConvert, costConvert;
			temp.push_back(maintenance[i]->getName());
			idConvert << id;
			temp.push_back(idConvert.str());
			workerConvert << maintenance[i]->getWorkerId();
			temp.push_back(workerConvert.str());
			costConvert << maintenance[i]->getDuration() * maintenance[i]->getWorkerWage();
			temp.push_back(costConvert.str());
			result.push_back(temp);
		}
	}
	return result;
}

vector <vector <string> > Condominium::getPropertiesReport() {
	vector <vector <string> > result;
	float lastDue=0;
	for(unsigned int i=0; i < properties.size(); i++) {
		if(properties[i]->payMonth()) {
			vector <string> temp;
			stringstream idConvert, ownerConvert, costConvert;
			temp.push_back(properties[i]->getAddress());
			idConvert << id;
			temp.push_back(idConvert.str());
			ownerConvert << properties[i]->getOwnerId();
			temp.push_back(ownerConvert.str());
			switch (properties[i]->returnType()) {
			case 1:
				lastDue = this->baseApartmentCost*properties[i]->getArea();
				break;
			case 2:
				lastDue = this->baseOfficeCost*properties[i]->getArea();
				break;
			case 3:
				lastDue = this->baseStoreCost*properties[i]->getArea();
				break;
			}
			properties[i]->addDue(lastDue);
			costConvert << properties[i]->getDue();
			temp.push_back(costConvert.str());
			result.push_back(temp);
		}
	}
	return result;
}

void Condominium::advanceOneMonth() {
	for(unsigned int i = 0; i < maintenance.size(); i++) {
		maintenance[i]->decMonth();
	}
	for(unsigned int i = 0; i < properties.size(); i++) {
		properties[i]->decMonth();
	}
}

void Condominium::manageCondFixedValues() {
	Menu manage("Managing");
	manage.addMenuItem("Edit name");
	manage.addMenuItem("Edit Area Multiplier");
	manage.addMenuItem("Edit Floor Multiplier");
	manage.addMenuItem("Edit Base Office cost");
	manage.addMenuItem("Edit Base Apartment cost");
	manage.addMenuItem("Edit Base Store cost");
	manage.addMenuItem("Go to the PREVIOUS menu");
	switch (manage.showMenu()) {
	case 1:{
		string name = Menu::promptString("New name: ");
		this->name=name;
		break;
	}
	case 2:{
		float area = Menu::promptFloat("New area: ");
		this->areaMultiplier=area;
		break;
	}
	case 3:{
		float floor = Menu::promptFloat("New floor: ");
		this->floorMultiplier=floor;
		break;
	}
	case 4:{
		float baseOffice = Menu::promptFloat("New base Office cost: ");
		this->baseOfficeCost=baseOffice;
		break;
	}
	case 5:{
		float baseApartment = Menu::promptFloat("New base Apartment cost: ");
		this->baseApartmentCost=baseApartment;
		break;
	}
	case 6:{
		float baseStore = Menu::promptFloat("New base Store cost: ");
		this->baseStoreCost=baseStore;
		break;
	}
	case 7:{
		manage.toggleMenu();
		break;
	}
	}
}

void Condominium::condShowPrior() {
	priority_queue<Equity> temp = priorProperties;
	while(!temp.empty()){
		cout << temp.top().getAddress() << " - Cost: " << temp.top().getCost() << " euros" << endl;
		temp.pop();
	}
}

void Condominium::arrangeMeeting(int currentDate) {
	if(meetings.size()!=0){
		if(meetings[meetings.size()-1].getDate() >= currentDate){
			cout << "There is already a meeting scheduled for this cond, ";
			cout << "scheduled date: " << meetings[meetings.size()-1].getDate()%100 << " - " << meetings[meetings.size()-1].getDate()/100 << endl;
			return;
		}
	}
	cout << "Choose one date for the meeting, it should be whithin 2years max." << endl << endl;
	cout << "Current date: " << currentDate%100 << " - " << currentDate/100 << endl;
	int month=0;
	int year=0;

	while(year<currentDate/100||year>currentDate/100+2){
		year = Menu::promptInt("Choose a year (2 year max):");
	}
	bool correctMonth=false;
	while(!correctMonth){
		month = Menu::promptInt("Choose a month (between the current month and 12):");
		if(year == currentDate/100) {
			if(month >= currentDate%100 && month < 13) {
				correctMonth=true;
			}
		}
		else if(month>0&&month<13){
			correctMonth = true;
		}
	}
	cout << "Which subject would you like to see discussed?:"; string subject; getline(cin,subject);

	cout << "\nThe meeting has been scheduled" << endl << endl;

	while(!priorProperties.empty()){
		priorProperties.pop();
	}
	for(unsigned int i=0;i<properties.size();i++) {
		vector<float> baseCost;
		baseCost.push_back(areaMultiplier);
		baseCost.push_back(floorMultiplier);
		switch (properties[i]->returnType()) {
		case 1:
			baseCost.push_back(baseApartmentCost);
			break;
		case 2:
			baseCost.push_back(baseOfficeCost);
			break;
		case 3:
			baseCost.push_back(baseStoreCost);
			break;
		default:
			break;
		}

		Equity e1(properties[i]->getFloor(),properties[i]->getArea(),properties[i]->getAddress(),baseCost,properties[i]->getOwnerId());
		priorProperties.push(e1);
	}

	int date = year*100+month;
	Meeting m1(date,subject);
	meetings.push_back(m1);
	saveMeetings();
}

void Condominium::confirmAttendance(int currentDate,vector<Owner *> owners) {
	if(meetings.size()!=0){
		if(meetings[meetings.size()-1].getDate() >= currentDate){
			vector<int> atual = meetings[meetings.size()-1].getAttendance();
			bool found = true;
			while(found==true && !priorProperties.empty()){
				int top = priorProperties.top().getId();
				if(existeEm(atual,top) == true){
					priorProperties.pop();
				} else {
					found = false;
				}
			}
		}
		else {
			cout << "There are no meetings arranged, please schedule one first" << endl << endl;
			return;
		}
	}
	vector<int> atual = meetings[meetings.size()-1].getAttendance();
	for(unsigned int i=0;i<atual.size();i++){
		if(atual[i]==0){
			atual.erase(atual.begin()+i);
		}
	}
	meetings[meetings.size()-1].setAttendance(atual);
	stringstream title;
	int option;
	while(option != 4){
		if(!priorProperties.empty()){
			title << "The next owner that needs confirmation is " << getOwner(owners,priorProperties.top().getId())->getName() << " - " << priorProperties.top().getAddress() << endl;
		} else {
			title << "There are no more owners to confirm their presence." << endl;
		}
		Menu manage(title.str());
		manage.addMenuItem("Confirm presence");
		manage.addMenuItem("Reject presence");
		manage.addMenuItem("Edit preview confirmations");
		manage.addMenuItem("Go back");
		option=manage.showMenu();
		switch (option) {
		case 1:{
			if(!priorProperties.empty()){
				meetings[meetings.size()-1].addAttendance(priorProperties.top().getId());
				priorProperties.pop();
			}
		}
		break;
		case 2:
			if(!priorProperties.empty()){
				priorProperties.pop();
			}
			break;
		case 3:{
			if(meetings[meetings.size()-1].getAttendance().size() != 0) {
				int option2=0;
				int i=0;
				while(option2!=4 && meetings[meetings.size()-1].getAttendance().size() != 0) {
					string title;
					title = getOwner(owners,meetings[meetings.size()-1].getAttendance()[i])->getName();
					Menu editConf(title);
					editConf.addMenuItem("Remove this confirmation");
					editConf.addMenuItem("Next Confirmation");
					editConf.addMenuItem("Previews Confirmation");
					editConf.addMenuItem("Go Back");
					option2=editConf.showMenu();
					switch (option2) {
					case 1:
						meetings[meetings.size()-1].removeAttendance(meetings[meetings.size()-1].getAttendance()[i]);
						break;
					case 2:
						i = (i+1) % meetings[meetings.size()-1].getAttendance().size();
						break;
					case 3:
						i = (i-1) % meetings[meetings.size()-1].getAttendance().size();
						break;
					default:
						break;
					}
				}
			}
		}
		break;
		case 4:
			manage.toggleMenu();
			break;
		}
		vector<int> atual = meetings[meetings.size()-1].getAttendance();
		bool found = true;
		while(found==true && !priorProperties.empty()){
			int top = priorProperties.top().getId();
			if(existeEm(atual,top) == true){
				priorProperties.pop();
			} else {
				found = false;
			}
		}
		title.str("");
	}
	saveMeetings();
}

void Condominium::checkLastMeetings(vector<Owner*> owners) {
	int option=0;
	int i=0;
	while(option!=3){
		stringstream title;
		vector<int> attendance = meetings[i].getAttendance();
		unsigned int j=0;
		title << "Year:" << meetings[i].getDate() /100 << " - Month:" << meetings[i].getDate()%100 << "|| Subject discussed: " << meetings[i].getSubject() <<endl << "Attendance: ";
		for(unsigned int x=0;x<attendance.size();x++){
			if(attendance[x]==0){
				attendance.erase(attendance.begin()+x);
			}
		}
		while(j<attendance.size()) {
			title << getOwner(owners,attendance[j])->getName();
			if(j+1<attendance.size()){
				title << ",";
			}
			j++;
		}
		Menu meeting(title.str());
		meeting.addMenuItem("Go to the next");
		meeting.addMenuItem("Go to the previous");
		meeting.addMenuItem("Go Back to the PREVIOUS menu");
		option = meeting.showMenu();
		switch (option) {
		case 1:
			i = (i+1) % meetings.size();
			break;
		case 2:
			i = (i-1) % meetings.size();
			break;
		default:
			break;
		}
	}
}

