/*
 * corporation.cpp
 *
 *  Created on: Oct 12, 2013
 *      Author: ricardo
 */

#include "corporation.h"

// constructor

Corporation::Corporation(){
	loadCondominiums("condominiums.csv");
}

// remove/add functions

void Corporation::removeCondominium(Condominium cond){
	// procurar o metodo que procura no vetor e associa à possição seguinte passado a dele
}

void Corporation::addCondominium(Condominium cond){
	condominiums.push_back(cond);
}

void Corporation::loadCondominiums(string filename) {
	ifstream file;
	string line;
	int id;
	vector <string> condominiumInfo;
	file.open("condominiums.csv");
	int lineNumber = 0;
	while (file.good())
	{
		cout << endl << "here";
		getline(file,line);
		if (lineNumber > 0) {
			istringstream iss(line);
			do
			{
				string sub;
				getline(iss, sub , ',');
				condominiumInfo.push_back(sub);
			} while (iss);

			id = atol(condominiumInfo[0].c_str());
			if(id>0) {
				Condominium condominium(id, condominiumInfo[1]);
				condominiums.push_back(condominium);
			}
			condominiumInfo.clear();
		}
		lineNumber++;
	}
	file.close();
}

void Corporation::loadProperties(int condominiumid) {
	stringstream ssfilename;
	ssfilename << "database/condominium" << condominiumid << ".csv";
	string filename = ssfilename.str();
	ifstream file(filename.c_str());
	string line;
	vector <string> propertyInfo;
	int lineNumber = 0;
	while (file.good())
	{
		getline(file,line);
		if (lineNumber > 0) {
			istringstream iss(line);
			do
			{
				string sub;
				getline(iss, sub , ',');
				propertyInfo.push_back(sub);
			} while (iss);

			Property property(propertyInfo[0]);

			Property *p = 0;
			*p = property;

			condominiums[searchCondominiumId(condominiumid)].addProperty(p);
			propertyInfo.clear();
		}
		lineNumber++;
	}
}

int Corporation::searchCondominiumId(int condominiumdid) {
	for(unsigned int i = 0; i<condominiums.size(); i++) {
		if(condominiums[i].getId() == condominiumdid) {
			return i;
		}
	}
	return 0;
}

void Corporation::showCondominium(int id) {
	cout << "Condominium ID: " << condominiums[id].getId() << endl;
	cout << "Condominium Name: " << condominiums[id].getName() << endl;
}

void Corporation::showAllCondominiums() {
	for(unsigned int i=0; i<condominiums.size(); i++) {
		showCondominium(i);
	}
}
