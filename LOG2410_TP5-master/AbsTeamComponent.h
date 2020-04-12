/****************************************************************************
**
** Classe AbsTeamComponent
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _AbsTeamComponent_Header_
#define _AbsTeamComponent_Header_
#include <string>
#include "TeamComponentContainer.h"

class AbsTeamComponent
{
public:
	AbsTeamComponent(void) {};
	virtual ~AbsTeamComponent(void) {};
	virtual AbsTeamComponent* clone(void) const = 0;

	virtual const class QImage& getImage(void) const = 0;
	virtual class QImage& getImage(void) = 0;
	virtual std::string getName(void) const = 0;
	virtual void setName(std::string name) = 0;
	
	virtual AbsTeamComponent& addTeamComponent(const AbsTeamComponent& member) = 0;
	virtual TeamComponentIterator begin() = 0;
	virtual TeamComponentIterator_const cbegin() const = 0;
	virtual TeamComponentIterator_const cend() const = 0;
	virtual TeamComponentIterator end() = 0;
	virtual void deleteTeamComponent( TeamComponentIterator_const child ) = 0;

	virtual void accept(class AbsComponentVisitor& vis) = 0;
};

#endif
