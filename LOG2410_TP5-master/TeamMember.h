/****************************************************************************
**
** Classe TeamMember
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _TeamMember_Header_
#define _TeamMember_Header_

#include "AbsTeamComponent.h"

#include <QImage>

class TeamMember : public AbsTeamComponent
{
public:
	TeamMember(std::string name, const class QImage& photo);
	TeamMember(const TeamMember& mdd);
	virtual TeamMember* clone(void) const;

	virtual const class QImage& getImage(void) const;
	virtual class QImage& getImage(void);
	virtual std::string getName(void) const;
	virtual void setName(std::string name);

	virtual AbsTeamComponent& addTeamComponent(const AbsTeamComponent& member);
	virtual TeamComponentIterator begin();
	virtual TeamComponentIterator_const cbegin() const;
	virtual TeamComponentIterator_const cend() const;
	virtual TeamComponentIterator end();
	virtual void deleteTeamComponent(TeamComponentIterator_const child);

	virtual void accept(class AbsComponentVisitor& vis);

private:
	std::string m_name;
	QImage m_image;

	static TeamComponentContainer m_emptyContainer;
};

#endif
