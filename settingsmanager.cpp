// settingsmanager.cpp

#include "settingsmanager.h"
#include <QSettings>

void SettingsManager::saveSettings(const QString &dataPath) {
    QSettings settings;
    settings.setValue("dataPath", dataPath);
    // settings.sync(); // Ensure settings are immediately written to disk
}


QString SettingsManager::loadSettings() {
    QSettings settings;
    QVariant value = settings.value("dataPath");
    if (value.isNull()) {
        qDebug() << "Failed to load dataPath setting. Using default value.";
        return QString(); // or any default value
    }
    return value.toString();
}

