/****************************************************************************
**
** Classe TeamComponentView
** Author: p482457
** Date: 25-oct-2019
**
****************************************************************************/

#ifndef _TeamComponentView_Header_
#define _TeamComponentView_Header_

#include <QLabel>

#include "AbsTeamComponent.h"

class TeamComponentView
{
public:
	TeamComponentView( const AbsTeamComponent& member);
	TeamComponentView(const TeamComponentView& mdd);
	virtual ~TeamComponentView();

	virtual QLabel* getWidget(void) const;
	virtual const QImage& getImage(void) const;

private:
	const AbsTeamComponent& m_component;
	QLabel *m_imageLabel;
};

#endif
