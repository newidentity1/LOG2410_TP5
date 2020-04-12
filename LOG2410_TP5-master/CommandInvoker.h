///////////////////////////////////////////////////////////
//  CommandInvoker.h
//  Implementation of the Class CommandInvoker
//  Created on:      08-nov.-2018 21:05:18
//  Original author: p482457
///////////////////////////////////////////////////////////

#if !defined(EA_58D999ED_BB97_4cec_AA75_A5ADB8F6662F__INCLUDED_)
#define EA_58D999ED_BB97_4cec_AA75_A5ADB8F6662F__INCLUDED_

#include "AbsCommand.h"

class CommandInvoker
{
public:
	static CommandInvoker* getInstance(void);

	void execute(const CmdPtr& cmd);
	void undo();
	void redo();

	size_t getDoneCount(void) const;
	size_t getUndoneCount(void) const;

private:
	CommandInvoker() = default;
	virtual ~CommandInvoker() = default;

	static CommandInvoker* m_instance;
	CmdContainer m_cmdDone;
	CmdContainer m_cmdUndone;
};
#endif // !defined(EA_58D999ED_BB97_4cec_AA75_A5ADB8F6662F__INCLUDED_)
