// settingsmanager.cpp

#include "settingsmanager.h"
#include <QSettings>

void SettingsManager::saveSettings(const QString &dataPath) {
    QSettings settings;
    settings.setValue("dataPath", dataPath);

}


QString SettingsManager::loadSettings() {
    QSettings settings;
    QVariant value = settings.value("dataPath");
    if (value.isNull()) {
        qDebug() << "Failed to load dataPath setting. Using default value.";
        return QString();
    }
    return value.toString();
}

