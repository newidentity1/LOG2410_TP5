/****************************************************************************
**
** Classe CommandTranslate
** Author: p482457
** Date: 17-nov-2019
**
****************************************************************************/

#ifndef _CommandTranslate_Header_
#define _CommandTranslate_Header_

#include "AbsCommand.h"
#include <string>
class CommandTranslate : public AbsCommand
{
public:
	enum class TargetLanguage { English_t, French_t };
	CommandTranslate(class AbsTeamComponent& component, TargetLanguage language = TargetLanguage::English_t);
	virtual ~CommandTranslate() = default;

	virtual void cancel();
	virtual void execute();

private:
	TargetLanguage m_language;
	AbsTeamComponent& m_target;

	static std::pair<std::string, std::string> translations[];
	static size_t translationsCount;
};
#endif
