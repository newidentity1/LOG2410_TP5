/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "Teamviewer.h"
#include "TeamImageSizeCalculator.h"
#include "MemberTextFindReplace.h"
#include "CommandInvoker.h"
#include "CommandCalculateSize.h"
#include "CommandTranslate.h"

TeamViewer::TeamViewer()
   : m_teamManager()
	, m_rootTeam(m_teamManager.addTeam("House"))
	, scrollArea(new QScrollArea)
	, container(new QWidget)
	, hBoxLayout(new QHBoxLayout)
{
	container->setLayout(hBoxLayout);

	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setVisible(false);
	scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

	createActions();

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

bool TeamViewer::loadFile(AbsTeamComponent& team, const QString& fileName, const QString& role)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

	if (role.isEmpty())
	{
		const TeamMember& newMember = m_teamManager.addMemberToTeam(dynamic_cast<Team&>(team), fileName.toStdString(), newImage);
		m_viewWidgets.push_back(TeamComponentView(newMember));
	}
	else
	{
		const TeamMemberRole& newMember = m_teamManager.addMemberToTeamwRole(dynamic_cast<Team&>(team), fileName.toStdString(), newImage, role.toStdString());
		m_viewWidgets.push_back(TeamComponentView(newMember));
	}

	hBoxLayout->addWidget(m_viewWidgets.back().getWidget());
	scrollArea->setWidget(container);

	scrollArea->setVisible(true);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(newImage.width()).arg(newImage.height()).arg(newImage.depth());
    statusBar()->showMessage(message);
    return true;
}

void TeamViewer::updateImages( AbsTeamComponent& parent)
{
	// Process parent
	if (!parent.getImage().isNull())
	{
		m_viewWidgets.push_back(TeamComponentView(parent));
		hBoxLayout->addWidget(m_viewWidgets.back().getWidget());
	}

	// Process children
	for (auto it = parent.begin(); it != parent.end(); ++it)
		updateImages(*it);
}

void TeamViewer::updateWidgets()
{
	m_viewWidgets.clear();
	updateImages(m_rootTeam);
}

bool TeamViewer::loadFile(const QString & fileName)
{
	m_viewWidgets.clear();
	m_rootTeam.deleteAllComponents();
	return loadFile(m_rootTeam, fileName, QString());
}

void TeamViewer::openTeam()
{
	m_viewWidgets.clear(); 
	m_rootTeam.deleteAllComponents();

	AbsTeamComponent& team_govrmt(m_rootTeam.addTeamComponent(Team("Gouvernement")));
	loadFile(team_govrmt, ".\\photos\\Trudeau.jpg", QString());
	loadFile(team_govrmt, ".\\photos\\Freeland.jpg", QString());

	AbsTeamComponent& team_opposit(m_rootTeam.addTeamComponent(Team("Opposition")));
	loadFile(team_opposit, ".\\photos\\Scheer.jpg", QString());
	loadFile(team_opposit, ".\\photos\\Raitt.jpg", QString());

	// Calculer et afficher la taille totale des images chargees
	std::shared_ptr<CommandCalculateSize> cmdSize = std::make_shared<CommandCalculateSize>(m_rootTeam);
	CommandInvoker::getInstance()->execute(cmdSize);
	size_t totalSize = cmdSize->getSize();

	const QString message = tr("Total size of images loaded: %1").arg(totalSize);
	statusBar()->showMessage(message);

	updateActions();
}

void TeamViewer::openRole()
{
	m_viewWidgets.clear();
	m_rootTeam.deleteAllComponents();

	AbsTeamComponent& team_govrmt(m_rootTeam.addTeamComponent(Team("Gouvernement")));
	loadFile(team_govrmt, ".\\photos\\Trudeau.jpg", QString("Premier Ministre"));
	loadFile(team_govrmt, ".\\photos\\Freeland.jpg", QString("Ministre"));

	AbsTeamComponent& team_opposit(m_rootTeam.addTeamComponent(Team("Opposition")));
	loadFile(team_opposit, ".\\photos\\Scheer.jpg", QString("Chef de l'opposition"));
	loadFile(team_opposit, ".\\photos\\Raitt.jpg", QString("Ex Membre du Parlement"));

	// Calculer et afficher la taille totale des images chargees
	std::shared_ptr<CommandCalculateSize> cmdSize = std::make_shared<CommandCalculateSize>(m_rootTeam);
	CommandInvoker::getInstance()->execute(cmdSize);
	size_t totalSize = cmdSize->getSize();

	const QString message = tr("Total size of images loaded: %1").arg(totalSize);
	statusBar()->showMessage(message);

	updateActions();
}

void TeamViewer::undo()
{
	CommandInvoker::getInstance()->undo();
	updateWidgets();
	updateActions();

	const QString message = tr("Last command undone");
	statusBar()->showMessage(message);
}

void TeamViewer::redo()
{
	CommandInvoker::getInstance()->redo();
	updateWidgets();
	updateActions();

	const QString message = tr("Last command redone");
	statusBar()->showMessage(message);
}

void TeamViewer::translateToEnglish()
{
	std::shared_ptr<CommandTranslate> cmdSize = std::make_shared<CommandTranslate>(m_rootTeam, CommandTranslate::TargetLanguage::English_t);
	CommandInvoker::getInstance()->execute(cmdSize);
	updateWidgets();
	updateActions();

	const QString message = tr("Translated to English");
	statusBar()->showMessage(message);
}

void TeamViewer::translateToFrench()
{
	std::shared_ptr<CommandTranslate> cmdSize = std::make_shared<CommandTranslate>(m_rootTeam, CommandTranslate::TargetLanguage::French_t);
	CommandInvoker::getInstance()->execute(cmdSize);
	updateWidgets();
	updateActions();

	const QString message = tr("Translated to French");
	statusBar()->showMessage(message);
}

void TeamViewer::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Team Viewer</b> application shows how to combine Qt "
               "with the Composite and Decorator design patterns "
               "for displaying groups of images structured in teams. "
               "The QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates QLabel's ability to display images and text."
				"</p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}

void TeamViewer::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

	QAction *openTeamAct = fileMenu->addAction(tr("Open &Team"), this, &TeamViewer::openTeam);
	openTeamAct->setShortcut(tr("Ctrl+T"));

	QAction *openRoleAct = fileMenu->addAction(tr("Open &Role"), this, &TeamViewer::openRole);
	openRoleAct->setShortcut(tr("Ctrl+R"));

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));

    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));

	undoAct = editMenu->addAction(tr("&Undo"), this, &TeamViewer::undo);
	undoAct->setShortcut(tr("Ctrl+Z"));
	undoAct->setEnabled(false);

	redoAct = editMenu->addAction(tr("&Redo"), this, &TeamViewer::redo);
	redoAct->setShortcut(tr("Ctrl+Y"));
	redoAct->setEnabled(false);

	translateToEnglishAct = editMenu->addAction(tr("&English"), this, &TeamViewer::translateToEnglish);
    translateToEnglishAct->setShortcut(tr("Ctrl+E"));
    translateToEnglishAct->setEnabled(false);

	translateToFrenchAct = editMenu->addAction(tr("&French"), this, &TeamViewer::translateToFrench);
	translateToFrenchAct->setShortcut(tr("Ctrl+F"));
	translateToFrenchAct->setEnabled(false);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    helpMenu->addAction(tr("&About"), this, &TeamViewer::about);
    helpMenu->addAction(tr("About &Qt"), &QApplication::aboutQt);
}

void TeamViewer::updateActions()
{
	undoAct->setEnabled(CommandInvoker::getInstance()->getDoneCount()!=0);
	redoAct->setEnabled(CommandInvoker::getInstance()->getUndoneCount()!=0);
	translateToEnglishAct->setEnabled(m_viewWidgets.size() != 0);
	translateToFrenchAct->setEnabled(m_viewWidgets.size() != 0);
}
