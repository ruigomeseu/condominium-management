#include "maintenance.h"

// Constructors
Maintenance::Maintenance() {
	name = "";
	monthsLeft = 0;
	duration=0;
	type=0;
	this->worker = new Worker("");
}

Maintenance::Maintenance(int type,float duration, string name, Worker* worker) {
	this->type = type;
	this->name = name;
	this->worker = worker;
	this->duration = duration;
	switch(type) {
		case 0:
			monthsLeft = 1;
			break;
		case 1:
			monthsLeft = 3;
			break;
		case 2: 
			monthsLeft = 12;
			break;
		default:
			monthsLeft = 0;
			break;
	}
}

Maintenance::Maintenance(int monthsLeft,float duration, int type, string name, Worker* worker) {
	this->monthsLeft = monthsLeft;
	this->duration = duration;
	this->type = type;
	this->name = name;
	this->worker = worker;
}


//set & get functions
void Maintenance::setMonth(int months) {
	monthsLeft = months;
}

int Maintenance::getMonth() {
	return monthsLeft;
}

void Maintenance::setName(string name) {
	this->name=name;
}

string Maintenance::getName() {
	return name;
}

int Maintenance::getType()  {
	return type;
}

void Maintenance::setType(int type) {
	this->type=type;
}

bool Maintenance::payMonth() {
	if(monthsLeft == 1){
		return true;
	}
	return false;
}

void Maintenance::decMonth() {
	monthsLeft--;
	if(monthsLeft == 0) {
		switch(type) {
		case 0:
			monthsLeft = 1;
			break;
		case 1:
			monthsLeft = 3;
			break;
		case 2: 
			monthsLeft = 12;
			break;
		default:
			monthsLeft = 0;
			break;
		}
	}
}

int Maintenance::getWorkerId() {
	return worker->getId();
}

string Maintenance::printType() {
	if(type==0){
		return "monthly";
	}else if(type==1) {
		return "trimestral";
	} else {
		return "annually";
	}
}

void Maintenance::setDuration(float duration) {
	this->duration = duration;
}

float Maintenance::getDuration() {
	return duration;
}

float Maintenance::getWorkerWage() {
	return worker->getWage();
}

void Maintenance::setWorkerId(int id) {
	worker->setId(id);
}

string Maintenance::getWorkerName() {
	return worker->getName();
}

void Maintenance::setWorker(Worker* w1){
	worker = w1;
}
