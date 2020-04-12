///////////////////////////////////////////////////////////
//  AbsCommand.h
//  Implementation of the Class AbsCommand
//  Created on:      08-nov.-2018 21:04:43
//  Original author: p482457
///////////////////////////////////////////////////////////

#if !defined(EA_6DA0EB48_3EA7_4ad9_AE79_4CFC912AAB16__INCLUDED_)
#define EA_6DA0EB48_3EA7_4ad9_AE79_4CFC912AAB16__INCLUDED_

#include <list>
#include <memory>

class AbsCommand
{
public:
	AbsCommand() = default;
	virtual ~AbsCommand() = default;

	virtual void cancel() =0;
	virtual void execute() =0;
};

using CmdPtr = std::shared_ptr<AbsCommand>;
using CmdContainer = std::list<CmdPtr>;

#endif // !defined(EA_6DA0EB48_3EA7_4ad9_AE79_4CFC912AAB16__INCLUDED_)
