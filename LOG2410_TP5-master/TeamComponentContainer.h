///////////////////////////////////////////////////////////
//  TeamComponentContainer.h
//  Implementation of the Class TeamComponentContainer
//  Created on:      26-oct.-2019
//  Original author: p482457
///////////////////////////////////////////////////////////

#if !defined(EA_1A8475D5_4734_484c_8758_A92F295DDED0__INCLUDED_)
#define EA_1A8475D5_4734_484c_8758_A92F295DDED0__INCLUDED_

#include <memory>
#include <list>

// Configuration du stockage des enfants des objets composites
using TeamComponentPtr = std::unique_ptr<class AbsTeamComponent>;
using TeamComponentContainer = std::list<TeamComponentPtr>;
using TeamComponentBaseIterator = TeamComponentContainer::iterator;
using TeamComponentBaseIterator_const = TeamComponentContainer::const_iterator;

class TeamComponentIterator : public TeamComponentBaseIterator
{
public:
	TeamComponentIterator(void) = default;
	TeamComponentIterator(const TeamComponentContainer::iterator& it) : TeamComponentBaseIterator(it) {}

	// Operateurs simplifiant l'acces a l'objet 3D sur lequel pointe l'iterateur
	// pour TeamComponentIterator it;
	//    *it est l'objet 3D
	//    it-> permet d'invoquer une methode sur l'objet 3D
	class AbsTeamComponent& operator*() { return *((*(TeamComponentBaseIterator(*this))).get()); }
	class AbsTeamComponent* operator->() { return (*(TeamComponentBaseIterator(*this))).get(); }
};

class TeamComponentIterator_const : public TeamComponentBaseIterator_const
{
public:
	TeamComponentIterator_const(void) = default;
	TeamComponentIterator_const(const TeamComponentContainer::const_iterator& it) : TeamComponentBaseIterator_const(it) {}

	// Operateurs simplifiant l'acces a l'objet 3D sur lequel pointe l'iterateur
	// pour TeamComponentIterator_const it;
	//    *it est l'objet 3D constant
	//    it-> permet d'invoquer une methode const sur l'objet 3D
	const class AbsTeamComponent& operator*() { return *((*(TeamComponentBaseIterator_const(*this))).get()); }
	const class AbsTeamComponent* operator->() { return (*(TeamComponentBaseIterator_const(*this))).get(); }
};

#endif // !defined(EA_1A8475D5_4734_484c_8758_A92F295DDED0__INCLUDED_)
