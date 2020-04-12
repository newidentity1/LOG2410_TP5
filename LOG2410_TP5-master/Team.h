/****************************************************************************
**
** Classe Team
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _Team_Header_
#define _Team_Header_

#include "AbsTeamComponent.h"

#include <QImage>

class Team : public AbsTeamComponent
{
public:
	Team(std::string name);
	Team(const Team& mdd);
	virtual Team* clone(void) const;

	virtual const class QImage& getImage(void) const;
	virtual class QImage& getImage(void);
	virtual std::string getName(void) const;
	virtual void setName(std::string name);

	virtual AbsTeamComponent& addTeamComponent( const AbsTeamComponent& member);
	virtual TeamComponentIterator begin();
	virtual TeamComponentIterator_const cbegin() const;
	virtual TeamComponentIterator_const cend() const;
	virtual TeamComponentIterator end();
	virtual void deleteTeamComponent(TeamComponentIterator_const child);
	virtual void deleteAllComponents(void);

	virtual void accept(class AbsComponentVisitor& vis);

private:
	std::string m_name;
	QImage m_image;
	TeamComponentContainer m_members;
};

#endif