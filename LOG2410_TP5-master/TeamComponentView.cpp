#include "TeamComponentView.h"

#include <QLabel>

TeamComponentView::TeamComponentView(const AbsTeamComponent& member)
	: m_component(member), m_imageLabel(new QLabel)
{
	const QImage& image = member.getImage();
	if (!image.isNull())
	{
		m_imageLabel->setBackgroundRole(QPalette::Base);
		m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		m_imageLabel->setScaledContents(true);
		m_imageLabel->setPixmap(QPixmap::fromImage(image));
		m_imageLabel->setFixedSize(image.width(), image.height());
	}
}

TeamComponentView::TeamComponentView(const TeamComponentView & mdd)
	: m_component(mdd.m_component), m_imageLabel(new QLabel)
{
	const QImage& image = m_component.getImage();

	if (!image.isNull())
	{
		m_imageLabel->setBackgroundRole(QPalette::Base);
		m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
		m_imageLabel->setScaledContents(true);
		m_imageLabel->setPixmap(QPixmap::fromImage(image));
		m_imageLabel->setFixedSize(image.width(), image.height());
	}
}

TeamComponentView::~TeamComponentView()
{
	delete m_imageLabel;
}

QLabel * TeamComponentView::getWidget(void) const 
{ 
	return m_imageLabel; 
}

const QImage & TeamComponentView::getImage(void) const
{
	return m_component.getImage();
}
