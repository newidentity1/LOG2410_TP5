/****************************************************************************
**
** Classe TeamMemberRoleRole
** Author: p482457
** Date: 27-oct-2019
**
****************************************************************************/

#ifndef _TeamMemberRole_Header_
#define _TeamMemberRole_Header_

#include "TeamMember.h"

#include <QImage>

class TeamMemberRole : public AbsTeamComponent
{
public:
	TeamMemberRole(std::string name, const class QImage& photo, std::string role);
	TeamMemberRole(const TeamMemberRole& mdd);
	virtual TeamMemberRole* clone(void) const;

	virtual const class QImage& getImage(void) const;
	virtual class QImage& getImage(void);
	virtual std::string getName(void) const;
	virtual void setName(std::string name);
	virtual std::string getRole(void) const;
	virtual void setRole(std::string role);
	virtual AbsTeamComponent& getMember(void);
	virtual const AbsTeamComponent& getMember(void) const;

	virtual AbsTeamComponent& addTeamComponent(const AbsTeamComponent& member);
	virtual TeamComponentIterator begin();
	virtual TeamComponentIterator_const cbegin() const;
	virtual TeamComponentIterator_const cend() const;
	virtual TeamComponentIterator end();
	virtual void deleteTeamComponent(TeamComponentIterator_const child);

	virtual void accept(class AbsComponentVisitor& vis);

private:
	void paintRole(void);

	TeamComponentPtr m_member;
	std::string m_role;
	QImage m_image;
};

#endif
