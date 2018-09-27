#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QString>
#include <QFile>
#include <QSettings>

class Settings
{
public:
  static Settings *instance() {
    if(!_instance) {
          Settings::_instance = new Settings();
    }
    return Settings::_instance;
  }

    QString sitePath();
    QString title();
    QString cover();
    QString logo();
    QString favicon();
    QString baseURL();
    QString twitter();
    QString facebook();
    QString disqusShortname();
    bool disqusIsActive();
    QString googleAnalytics();
    QString relativeSource();
    QString destination();
    bool siteFolderIsValid();

    bool setSiteFolder(QDir folder);
    void setTitle(QString title);
    void setCover(QString relative_path);
    void setLogo(QString relative_path);
    void setFavicon(QString relative_path);
    void setBaseURL(QString url);
    void setTwitter(QString twitter);
    void setFacebook(QString facebook);
    void toggleDisqus(bool active);
    void setDisqusShorname(QString name);
    void setGoogleAnalytics(QString id);
    void setRelativeSource(QString relative_path);
    void setDestination(QString relative_path);

    bool save();

private:
    Settings();

    static Settings *_instance;

    QSettings _settings;

    bool parseYAML(QString file_path);
    bool relativeFileExists(QString relative_path);
    bool setSiteFolder();

    QDir _site_folder;
    QString _title;
    QString _cover;
    QString _logo;
    QString _favicon;
    QString _baseURL;
    QString _twitter;
    QString _facebook;
    QString _disqus_shortname;
    bool _disqus_is_active;
    QString _google_analytics;
    QString _relative_source;
    QString _relative_destination;
    bool _site_folder_is_valid;
};

#endif // SETTINGS_H
