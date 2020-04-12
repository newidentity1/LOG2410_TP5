/****************************************************************************
**
** Classe TeamManager
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _TeamManager_Header_
#define _TeamManager_Header_

#include "TeamMember.h"
#include "TeamMemberRole.h"
#include "Team.h"

class TeamManager
{
public:
	TeamManager(void);

	virtual void loadTeamFromFile(std::string fileName);
	virtual const TeamMember& addMemberToTeam(Team& team, std::string name, const class QImage& photo);
	virtual const TeamMemberRole& addMemberToTeamwRole(Team& team, std::string name, const class QImage& photo, std::string role);
	virtual Team& addTeam(std::string name);
	virtual TeamComponentIterator begin();
	virtual TeamComponentIterator_const cbegin() const;
	virtual TeamComponentIterator_const cend() const;
	virtual TeamComponentIterator end();
	virtual void deleteTeam(TeamComponentIterator_const child);
	virtual void deleteAllTeams(void);

private:
	TeamComponentContainer m_teams;
};

#endif