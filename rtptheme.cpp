#include "rtptheme.h"

#include <private/qguiapplication_p.h>
#include <qpa/qplatformtheme_p.h>
#include <qpa/qplatformthemefactory_p.h>
#include <qpa/qplatformintegration.h>

#include <QPalette>
#include <QFont>

QT_BEGIN_NAMESPACE

class RTPThemePrivate : public QPlatformThemePrivate
{
public:
    RTPThemePrivate()
        : QPlatformThemePrivate()
    { }

    ~RTPThemePrivate()
    {
        delete baseTheme;
    }

    QPlatformTheme *baseTheme;
};

RTPTheme::RTPTheme()
    : d_ptr(new RTPThemePrivate)
{
    Q_D(RTPTheme);
    
    m_font = new QFont("Verdana",8);
    QStringList active {
        "#000000", "#d3d3d3", "#ffffff", "#e9e9e9", "#696969", "#8d8d8d",
        "#000000", "#ffffff", "#000000", "#fdfcfa", "#d3d3d3", "#000000",
        "#232323", "#ffffff", "#0000ff", "#644a9b", "#faf6ef", "#000000",
        "#ffffdc", "#000000" };
    QStringList disabled {
        "#808080", "#d3d3d3", "#ffffff", "#f3f3f3", "#696969", "#8d8d8d",
        "#808080", "#ffffff", "#808080", "#fdfcfa", "#d3d3d3", "#000000",
        "#232323", "#808080", "#0000ff", "#644a9b", "#faf6ef", "#000000",
        "#ffffdc", "#000000" };
    QStringList inactive {
        "#000000", "#d3d3d3", "#ffffff", "#f3f3f3", "#696969", "#8d8d8d",
        "#000000", "#ffffff", "#000000", "#fdfcfa", "#d3d3d3", "#000000",
        "#232323", "#ffffff", "#0000ff", "#644a9b", "#faf6ef", "#000000",
        "#ffffdc", "#000000" };

    m_palette = new QPalette(Qt::black);
    for (int i = 0; i < qMin(active.count(), int(QPalette::NColorRoles)); ++i)
    {
        QPalette::ColorRole colorRole = (QPalette::ColorRole)i;
        m_palette->setColor(QPalette::Active,   colorRole, QColor(active[i]));
        m_palette->setColor(QPalette::Disabled, colorRole, QColor(disabled[i]));
        m_palette->setColor(QPalette::Inactive, colorRole, QColor(inactive[i]));
    }

    QStringList themeNames;
    themeNames += QGuiApplicationPrivate::platform_integration->themeNames();
    // 1) Look for a theme plugin.
    for (const QString &themeName : qAsConst(themeNames)) {
        d->baseTheme = QPlatformThemeFactory::create(themeName, nullptr);
        if (d->baseTheme)
            break;
    }

    // 2) If no theme plugin was found ask the platform integration to
    // create a theme
    if (!d->baseTheme) {
        for (const QString &themeName : qAsConst(themeNames)) {
            d->baseTheme = QGuiApplicationPrivate::platform_integration->createPlatformTheme(themeName);
            if (d->baseTheme)
                break;
        }
        // No error message; not having a theme plugin is allowed.
    }

    // 3) Fall back on the built-in "null" platform theme.
    if (!d->baseTheme)
        d->baseTheme = new QPlatformTheme;
}

RTPTheme::~RTPTheme()
{
    delete m_font;
    delete m_palette;
}

QPlatformMenuItem* RTPTheme::createPlatformMenuItem() const
{
    Q_D(const RTPTheme);
    return d->baseTheme->createPlatformMenuItem();
}

QPlatformMenu* RTPTheme::createPlatformMenu() const
{
    Q_D(const RTPTheme);
    return d->baseTheme->createPlatformMenu();
}

QPlatformMenuBar* RTPTheme::createPlatformMenuBar() const
{
    Q_D(const RTPTheme);
    return d->baseTheme->createPlatformMenuBar();
}

void RTPTheme::showPlatformMenuBar()
{
    Q_D(const RTPTheme);
    return d->baseTheme->showPlatformMenuBar();
}

bool RTPTheme::usePlatformNativeDialog(DialogType type) const
{
    Q_D(const RTPTheme);

    if (type == FileDialog)
        return true;

    return d->baseTheme->usePlatformNativeDialog(type);
}

QPlatformDialogHelper* RTPTheme::createPlatformDialogHelper(DialogType type) const
{
    Q_D(const RTPTheme);

    return d->baseTheme->createPlatformDialogHelper(type);
}

#ifndef QT_NO_SYSTEMTRAYICON
QPlatformSystemTrayIcon* RTPTheme::createPlatformSystemTrayIcon() const
{
    Q_D(const RTPTheme);
    return d->baseTheme->createPlatformSystemTrayIcon();
}
#endif

const QPalette *RTPTheme::palette(Palette type) const
{
    Q_D(const RTPTheme);

    if (type == SystemPalette)
        return m_palette;

    return d->baseTheme->palette(type);
}

const QFont* RTPTheme::font(Font type) const
{
    Q_D(const RTPTheme);

    return m_font;
}

QVariant RTPTheme::themeHint(ThemeHint hint) const
{
    Q_D(const RTPTheme);
    return d->baseTheme->themeHint(hint);
}

QPixmap RTPTheme::standardPixmap(StandardPixmap sp, const QSizeF &size) const
{
    Q_D(const RTPTheme);
    return d->baseTheme->standardPixmap(sp, size);
}

QIcon RTPTheme::fileIcon(const QFileInfo &fileInfo,
                              QPlatformTheme::IconOptions iconOptions) const
{
    Q_D(const RTPTheme);
    return d->baseTheme->fileIcon(fileInfo, iconOptions);
}

QIconEngine * RTPTheme::createIconEngine(const QString &iconName) const
{
    Q_D(const RTPTheme);
    return d->baseTheme->createIconEngine(iconName);
}

#if QT_CONFIG(shortcut)
QList<QKeySequence> RTPTheme::keyBindings(QKeySequence::StandardKey key) const
{
    Q_D(const RTPTheme);
    return d->baseTheme->keyBindings(key);
}
#endif

QString RTPTheme::standardButtonText(int button) const
{
    Q_D(const RTPTheme);
    return d->baseTheme->standardButtonText(button);
}

QT_END_NAMESPACE
