#include "Observer.h"

#include <algorithm>

void Observer::Update(const Observable* observable) const
{
	//TODO::make update function ? 
	
}

Observer::~Observer()
{
	/*For every object we destroy his observer*/
	const_iterator ite = obs_list.end();

	for (iterator itb = obs_list.begin(); itb != ite; ++itb)
	{
		(*itb)->DelObs(this);
	}
}

void Observer::AddObs(Observable* obs)
{
	obs_list.push_back(obs);
}

void Observer::DelObs(Observable* obs)
{
	iterator it = find(obs_list.begin(), obs_list.end(), obs);
	if (it != obs_list.end())
		obs_list.erase(it);
}

//Observalbe

void Observable::AddObs(Observer* obs)
{
	//we add the observer to the list
	obs_list.push_back(obs);

	//we give an object to the observer
	obs->AddObs(this);
}

void Observable::DelObs(Observer* obs)
{
	iterator it = find(obs_list.begin(), obs_list.end(), obs);
	if (it != obs_list.end())
		obs_list.erase(it);
}


Observable::~Observable()
{
	/*For every object we destroy his observer*/
	iterator itb = obs_list.begin();
	const_iterator ite = obs_list.end();

	for (; itb != ite; ++itb)
	{
		(*itb)->DelObs(this);
	}
}

void Observable::Notify(void)
{
	/*We alert each observer than state's object have change*/
	iterator itb = obs_list.begin();
	const_iterator ite = obs_list.end();

	for (; itb != ite; ++itb)
	{
		(*itb)->Update(this);
	}
}