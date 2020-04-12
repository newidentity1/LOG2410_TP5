///////////////////////////////////////////////////////////
//  CommandInvoker.cpp
//  Implementation of the Class CommandInvoker
//  Created on:      08-nov.-2018 21:05:19
//  Original author: p482457
///////////////////////////////////////////////////////////

#include "CommandInvoker.h"

CommandInvoker* CommandInvoker::m_instance = nullptr;

CommandInvoker * CommandInvoker::getInstance(void)
{
	// Verifier si l'instance unique a deja ete allouee et sinon l'allouer
	if (m_instance == nullptr) {
		m_instance = new CommandInvoker();
	}
	return m_instance;
}

void CommandInvoker::execute(const CmdPtr & cmd)
{
	// Executer la commande et la stocker dans la liste des commandes faites
	cmd->execute();
	m_cmdDone.push_back(cmd);
	// Vider la liste des commandes defaites
	m_cmdUndone.clear();
}

void CommandInvoker::undo()
{
	// Verifier si la liste des commandes faites n'est pas vide et si oui defaire la derniere commande faite
	if (!m_cmdDone.empty()) {
		m_cmdDone.back()->cancel();
		m_cmdUndone.push_back(m_cmdDone.back());
		m_cmdDone.pop_back();
	}
}

void CommandInvoker::redo()
{
	// Verifier si la liste des commandes defaites n'est pas vide et si oui refaire la derniere commande defaite
	if (!m_cmdUndone.empty()) {
		m_cmdUndone.back()->execute();
		m_cmdDone.push_back(m_cmdUndone.back());
		m_cmdUndone.pop_back();
	}
}

size_t CommandInvoker::getDoneCount(void) const
{
	// Retourner le nombre de commandes faites
	return m_cmdDone.size();
}

size_t CommandInvoker::getUndoneCount(void) const
{
	// Retourner le nombre de commandes defaites
	return m_cmdUndone.size();;
}
