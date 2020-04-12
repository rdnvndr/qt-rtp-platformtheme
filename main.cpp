#include <qpa/qplatformthemeplugin.h>
#include "rtptheme.h"

QT_BEGIN_NAMESPACE

class RTPThemePlugin : public QPlatformThemePlugin
{
   Q_OBJECT
   Q_PLUGIN_METADATA(IID QPlatformThemeFactoryInterface_iid FILE "rtptheme.json")

public:
    QPlatformTheme *create(const QString &key, const QStringList &params) override;
};

QPlatformTheme *RTPThemePlugin::create(const QString &key, const QStringList &params)
{
    Q_UNUSED(params);
    if (!key.compare(QLatin1String("rtptheme"), Qt::CaseInsensitive))
        return new RTPTheme;

    return nullptr;
}

QT_END_NAMESPACE

#include "main.moc"
