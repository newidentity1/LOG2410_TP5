/****************************************************************************
**
** Classe AbsComponentVisitor
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _AbsComponentVisitor_Header_
#define _AbsComponentVisitor_Header_
#include "Team.h"
#include "TeamMember.h"
#include "TeamMemberRole.h"

class AbsComponentVisitor
{
public:
	AbsComponentVisitor(void) {};
	virtual ~AbsComponentVisitor(void) {};

	virtual void processTeamMember(TeamMember& member) = 0;
	virtual void processTeamMemberRole(TeamMemberRole& member) = 0;
	virtual void processTeam(Team& team) = 0;
};

#endif
