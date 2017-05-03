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
#include "CasterBoard.h"
#include "CasterPlayer.h"
#include <QGridLayout>

//Constructor=============================================
CasterBoard::CasterBoard(QWidget* parent) : QWidget(parent)
{
    auto const rowWidth = 8;
    Qt::Key const keys[] = {
        Qt::Key_1, Qt::Key_2, Qt::Key_3, Qt::Key_4,
        Qt::Key_5, Qt::Key_6, Qt::Key_7, Qt::Key_8,

        Qt::Key_Q, Qt::Key_W, Qt::Key_E, Qt::Key_R,
        Qt::Key_T, Qt::Key_Y, Qt::Key_U, Qt::Key_I,

        Qt::Key_A, Qt::Key_S, Qt::Key_D, Qt::Key_F,
        Qt::Key_G, Qt::Key_H, Qt::Key_J, Qt::Key_K,

        Qt::Key_Z, Qt::Key_X, Qt::Key_C, Qt::Key_V,
        Qt::Key_B, Qt::Key_N, Qt::Key_M, Qt::Key_Comma,
    };
    QString const letters =
      "12345678"
      "QWERTYUI"
      "ASDFGHJK"
      "ZXCVBNM,";

    QGridLayout *boardLayout = new QGridLayout(this);

    //WIDGETS
    auto offset = 0;
    for (auto const letter : letters)
    {
        auto widget = new CasterPlayerWidget();
        widget->setHotKeyLetter(letter);
        auto key = keys[offset];
        players[key] = widget;
        boardLayout->addWidget(widget, offset / rowWidth, offset % rowWidth);
        ++offset;
    }
}

void CasterBoard::keyReleaseEvent(QKeyEvent *event)
{
    //Handles All Hot Key Behavior
    auto const key = static_cast<Qt::Key>(event->key());
    auto entry = players.find(key);
    if (entry != players.end())
    {
        auto widget = entry.value();
        switch (widget->player->state())
        {
        case QMediaPlayer::PlayingState:
            widget->stopSound();
            break;
        case QMediaPlayer::PausedState:
            widget->playSound();
            break;
        case QMediaPlayer::StoppedState:
            widget->playSound();
            break;
        }
    }
}
