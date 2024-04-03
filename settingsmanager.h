#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QString>

class SettingsManager
{
public:
    static void saveSettings(const QString &dataPath);
    static QString loadSettings();
};

#endif // SETTINGSMANAGER_H
