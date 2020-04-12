/****************************************************************************
**
** Classe CommandTranslate
** Author: p482457
** Date: 17-nov-2019
**
****************************************************************************/

#include "CommandTranslate.h"
#include "MemberTextFindReplace.h"
#include "AbsTeamComponent.h"

std::pair<std::string, std::string> CommandTranslate::translations[] = {
{"Premier", "Prime"},
{"Ministre", "Minister"},
{"Chef de l'", "Chief of "},
{"Membre", "Member"},
{"du Parlement", "of Parliement"}
};

size_t CommandTranslate::translationsCount = sizeof(CommandTranslate::translations) / sizeof(std::pair<std::string, std::string>);


CommandTranslate::CommandTranslate(AbsTeamComponent & component, TargetLanguage language)
	: m_target(component), m_language(language)
{
}

void CommandTranslate::cancel()
{
	// Construire un visiteur de traduction et l'appliquer a la composante dans le sens inverse
	MemberTextFindReplace vis;
	if (m_language == TargetLanguage::English_t){
		for (auto i = 0; i < translationsCount; i++) {
			vis.setStrings(&translations[i].second, &translations[i].first);
			m_target.accept(vis);
		}
	}
	else {
		for (auto i = 0; i < translationsCount; i++) {
			vis.setStrings(&translations[i].first, &translations[i].second);
			m_target.accept(vis);
		}
	}	
}

void CommandTranslate::execute()
{
	// Construire un visiteur de traduction et l'appliquer a la composante
	MemberTextFindReplace vis;
	if (m_language == TargetLanguage::English_t) {
		for (auto i = 0; i < translationsCount; i++) {
			vis.setStrings(&translations[i].first, &translations[i].second);
			m_target.accept(vis);
		}
	}
	else {
		for (auto i = 0; i < translationsCount; i++) {
			vis.setStrings(&translations[i].second, &translations[i].first);
			m_target.accept(vis);
		}
	}
}
