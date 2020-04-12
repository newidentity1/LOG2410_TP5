/****************************************************************************
**
** Classe MemberTextFindReplace
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _MemberTextFindReplace_Header_
#define _MemberTextFindReplace_Header_

#include <string>

#include "AbsComponentVisitor.h"
#include "TeamComponentContainer.h"

// Container for TeamComponentIterator 
using TeamComponentIteratorContainer = std::list<TeamComponentIterator>;

class MemberTextFindReplace : public AbsComponentVisitor
{
public:
	MemberTextFindReplace(const std::string* find_s = nullptr, const std::string* replace_s = nullptr);

	virtual void processTeamMember(class TeamMember& member);
	virtual void processTeamMemberRole(class TeamMemberRole& member);
	virtual void processTeam(class Team& team);

	virtual void setStrings(const std::string* find_s, const std::string* replace_s = nullptr);
	virtual std::string findString(void) const;
	virtual std::string replaceString(void) const;
	virtual bool doReplace(void) const;
	virtual TeamComponentIteratorContainer searchResult(void) const;
	virtual void clearSearch(void);

private:
	std::string m_findString;
	bool m_doReplace;
	std::string m_replaceString;

	TeamComponentIterator m_currentMember;
	TeamComponentIteratorContainer m_result;
};

#endif
