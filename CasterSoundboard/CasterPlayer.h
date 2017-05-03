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
#ifndef CASTERPLAYER_H
#define CASTERPLAYER_H
#include <QWidget>
#include <QDropEvent>
#include <QtMultimedia/QMediaPlayer>

//forward declarations
class QMediaPlayer;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QSlider;
class QString;

class CasterPlayerWidget : public QWidget //inherit from QWidget
{
    Q_OBJECT
public:
    //Constructor
    CasterPlayerWidget(QWidget* parent = 0); //don't forget to pass the parent

    //Set Properties
    void setHotKeyLetter(QChar hotKey);

    //Media Player
    QMediaPlayer *player;

    //Player Methhods
    void playSound();//Plays sound
    void stopSound();//Stops sound

    //Properties
    QString *soundFilePath;
    QString *hotKeyLetter;
    float progress;
    int volume;

protected:
    //Focus Event
    void mouseMoveEvent(QMouseEvent *event);
    //Paint Event
    void paintEvent(QPaintEvent *event); //Overide Paint Event
    //Drag-N-Drop Events
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
    bool openFiles(const QStringList& pathList);

private:
    //Private Methods
    int getProgressWidth(); //Use to compute width of progress bar

    //contained widgets:
    QVBoxLayout *mainLayout;
    QHBoxLayout *subMainLayoutH;
    QVBoxLayout *subMainLayoutV;
    QHBoxLayout *topLayout;
    QHBoxLayout *centerLayout;
    QHBoxLayout *bottomLayout;
    QLabel *soundNameLabel;
    QLabel *hotKeyLabel;
    QLabel *timeLabel;
    QPushButton *playStateButton;
    QPushButton *subMenuButton;
    QSlider *volumeSlider;

    //Internal Properties
    bool newMediaLoaded;

signals:
    //MyWidget's signals....
public slots:
    //MyWidget's slots example:
    // void firstButtonClicked();
    //...
    void playerToggle();
    void volumeChanged(int value);
    void openSubMenu();
    void playerPositionChanged(qint64 position);
    void playerStateChanged(QMediaPlayer::State state);
    void playerMetaDataChanged();
};
#endif // CASTERPLAYER_H
