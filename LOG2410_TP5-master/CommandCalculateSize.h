/****************************************************************************
**
** Classe CommandCalculateSize
** Author: p482457
** Date: 17-nov-2019
**
****************************************************************************/

#ifndef _CommandCalculateSize_Header_
#define _CommandCalculateSize_Header_

#include "AbsCommand.h"

class CommandCalculateSize : public AbsCommand
{
public:
	CommandCalculateSize( class AbsTeamComponent& component);
	virtual ~CommandCalculateSize() = default;

	virtual void cancel();
	virtual void execute();

	virtual void clearSize(void);
	virtual size_t getSize(void) const;

private:
	AbsTeamComponent& m_target;
	size_t m_computedSize;
};
#endif
