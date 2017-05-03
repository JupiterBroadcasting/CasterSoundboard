/*
 *
 *
 * Copyright 2013 Oscar Cerna
 *
 * This file is part of CasterSoundboard. An application for playing hot-keyed sounds.
 * For more information, please visit http://sourceforge.net/projects/castersb.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU LESSER GENERAL PUBLIC LICENSE for more details.
 *
 * You should have received a copy of the GNU LESSER GENERAL PUBLIC LICENSE
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef CASTERBOARD_H
#define CASTERBOARD_H
#include <QMap>
#include <QWidget>

//forward declarations
class CasterPlayerWidget;

class CasterBoard : public QWidget //inherit from QWidget
{
    Q_OBJECT
public:
    //Constructor
    CasterBoard(QWidget* parent = 0); //don't forget to pass the parent

    //Properties


protected:
    //========
    void keyReleaseEvent(QKeyEvent *event);//Capture Hot Keys

private:
    //Private Methods

    //WIDGETS
    QMap<Qt::Key, CasterPlayerWidget*> players;

signals:
    //SIGNALS

public slots:
    //SLOTS

};
#endif // CASTERBOARD_H
