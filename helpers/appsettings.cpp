
// This file is part of Puzzle Master, a fun and addictive jigsaw puzzle game.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
// Copyright (C) 2010-2013, Timur Kristóf <venemo@fedoraproject.org>

#include <QDebug>
#include <QFile>
#include <QDataStream>
#include <QRegExp>

#include "helpers/appsettings.h"

// Increase this when anything changes in the settings
// (but don't if you just add a new setting)
#define APPSETTINGS_VERSION 1
#define APPSETTING_SETTINGSVERSION "SettingsVersion"

AppSettings::AppSettings(QObject *parent) :
    QObject(parent),
    _areSettingsDeleted(false)
{
    // Checking for settings version

    bool containedSettingsVersion = _backend.contains(APPSETTING_SETTINGSVERSION);
    int savedSettingsVersion = _backend.value(APPSETTING_SETTINGSVERSION, 0).toInt();

    if (savedSettingsVersion != APPSETTINGS_VERSION)
    {
        // Clearing all settings if the saved version is different than current one
        _backend.clear();
        _backend.setValue(APPSETTING_SETTINGSVERSION, APPSETTINGS_VERSION);

        if (containedSettingsVersion)
        {
            _areSettingsDeleted = true;
            emit areSettingsDeletedChanged();
            qDebug() << "Old settings are now deleted.";
        }
    }
}

QStringList AppSettings::loadCustomImages()
{
    QStringList list;
    QByteArray array = customImageListData();
    QDataStream stream(&array, QIODevice::ReadOnly);
    stream >> list;

    foreach (const QString &url, list)
    {
        if (!QFile::exists(url))
        {
            qDebug() << "removing saved custom image" << url << "because it doesn't exist";
            list.removeAll(url);
        }
    }

    QByteArray array2;
    QDataStream stream2(&array2, QIODevice::WriteOnly);
    stream2 << list;
    setCustomImageListData(array2);

    qDebug() << "loaded URLs are" << list;

    return list;
}

bool AppSettings::addCustomImage(const QString &url)
{
    QStringList list = loadCustomImages();

    if (!list.contains(url) && QFile::exists(url))
    {
        qDebug() << "adding custom image" << url;
        list.append(url);
        QByteArray array;
        QDataStream stream(&array, QIODevice::WriteOnly);
        stream << list;
        setCustomImageListData(array);
        return true;
    }
    else if (list.contains(url))
    {
        emit customImageAlreadyAdded(url);
    }

    qDebug() << "not adding custom image" << url << QFile::exists(url);

    return false;
}

bool AppSettings::removeCustomImage(const QString &url)
{
    QStringList list = loadCustomImages();

    if (list.contains(url))
    {
        qDebug() << "removing custom image" << url;
        list.removeAll(url);
        QByteArray array;
        QDataStream stream(&array, QIODevice::WriteOnly);
        stream << list;
        setCustomImageListData(array);
        return true;
    }

    return false;
}
