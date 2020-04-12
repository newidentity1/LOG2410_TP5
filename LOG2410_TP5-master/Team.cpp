#include "Team.h"
#include "AbsComponentVisitor.h"

Team::Team(std::string name)
	: m_name(name)
{
}

Team::Team(const Team & mdd)
	: m_name(mdd.m_name),
	  m_image(mdd.m_image)
{
	for (auto it = mdd.cbegin(); it != mdd.cend(); ++it)
		addTeamComponent(*it);
}

Team * Team::clone(void) const
{
	return new Team(*this);
}

const QImage & Team::getImage(void) const
{
	return m_image;
}

QImage & Team::getImage(void)
{
	return m_image;
}

std::string Team::getName(void) const
{
	return m_name;
}

void Team::setName(std::string name)
{
	m_name = name;
}

AbsTeamComponent& Team::addTeamComponent(const AbsTeamComponent & member)
{
	m_members.push_back(TeamComponentPtr(member.clone()));
	return *(m_members.back());
}

TeamComponentIterator Team::begin()
{
	return m_members.begin();
}

TeamComponentIterator_const Team::cbegin() const
{
	return m_members.cbegin();
}

TeamComponentIterator_const Team::cend() const
{
	return m_members.cend();
}

TeamComponentIterator Team::end()
{
	return m_members.end();
}

void Team::deleteTeamComponent(TeamComponentIterator_const child)
{
	m_members.erase(child);
}

void Team::deleteAllComponents(void)
{
	m_name = "";
	m_image.fill(0);
	m_members.clear();
}

void Team::accept(AbsComponentVisitor & vis)
{
	vis.processTeam(*this);
}
