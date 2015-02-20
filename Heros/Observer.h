#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <list>

class Observable;

using namespace std;

/*TODO:: Define what kind of information we want for the Update */
typedef int Info; //int is just for testing and coding we have to change it maybe

class Observer{

protected:
	
	vector< Observable* > obs_list;
	typedef vector<Observable*>::iterator iterator;
	typedef vector<Observable*>::const_iterator const_iterator;
	virtual ~Observer() = 0;

public:
	//Update method who alert the Observer if the state of an object change
	virtual void Update(const Observable* observable) const;
	
	//Adding Observer to something
	void AddObs(Observable* obs);
	//Delete the Observer
	void DelObs(Observable* obs);

	virtual Info Statut(void) const = 0;
};

class Observable{

protected:
	vector<Observer*> obs_list;

	typedef vector<Observer*>::iterator iterator;
	typedef vector<Observer*>::const_iterator const_iterator;
	void Notify(void);

public:
	void AddObs(Observer* obs);
	void DelObs(Observer* obs);

	virtual Info Statut(void) const = 0;
	virtual ~Observable();



};