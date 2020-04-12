/****************************************************************************
**
** Classe TeamMember
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#include "TeamMember.h"
#include "AbsComponentVisitor.h"

// Define class static members
TeamComponentContainer TeamMember::m_emptyContainer;

TeamMember::TeamMember(std::string name, const QImage & photo)
	: m_name(name), m_image(photo)
{
}

TeamMember::TeamMember(const TeamMember & mdd)
	: m_name(mdd.m_name), m_image(mdd.m_image)
{
}

TeamMember * TeamMember::clone(void) const
{
	return new TeamMember(*this);
}

const QImage & TeamMember::getImage(void) const
{
	return m_image;
}

QImage & TeamMember::getImage(void)
{
	return m_image;
}

std::string TeamMember::getName(void) const
{
	return m_name;
}

void TeamMember::setName(std::string name)
{
	m_name = name;
}

AbsTeamComponent& TeamMember::addTeamComponent(const AbsTeamComponent&)
{
	return *(*(m_emptyContainer.begin()));
}

TeamComponentIterator TeamMember::begin()
{
	return m_emptyContainer.begin();
}

TeamComponentIterator_const TeamMember::cbegin() const
{
	return m_emptyContainer.cbegin();
}

TeamComponentIterator_const TeamMember::cend() const
{
	return m_emptyContainer.cend();
}

TeamComponentIterator TeamMember::end()
{
	return m_emptyContainer.end();
}

void TeamMember::deleteTeamComponent(TeamComponentIterator_const)
{
}

void TeamMember::accept(AbsComponentVisitor & vis)
{
	vis.processTeamMember(*this);
}

