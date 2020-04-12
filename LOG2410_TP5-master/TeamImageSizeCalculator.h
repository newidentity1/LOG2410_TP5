/****************************************************************************
**
** Classe TeamImageSizeCalculator
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _TeamImageSizeCalculator_Header_
#define _TeamImageSizeCalculator_Header_

#include "AbsComponentVisitor.h"

class TeamImageSizeCalculator : public AbsComponentVisitor
{
public:
	TeamImageSizeCalculator(void);

	virtual void processTeamMember(class TeamMember& member);
	virtual void processTeamMemberRole(class TeamMemberRole& member);
	virtual void processTeam(class Team& team);

	virtual size_t getTotalSize(void) const;
	virtual void clearTotalSize(void);

private:
	size_t m_totalSize;
};

#endif
