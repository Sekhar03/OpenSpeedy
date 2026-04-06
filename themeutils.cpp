/*
 * OpenSpeedy - Open Source Game Speed Controller
 * Copyright (C) 2025 Game1024
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "themeutils.h"
#include <QStyleFactory>
#include <QPalette>
#include <QColor>
#include <QSettings>
#include <QApplication>
#include <QStyle>

void ThemeUtils::applyTheme(Theme theme)
{
    if (theme == System) {
        if (isSystemDarkMode()) {
            setDarkTheme();
        } else {
            setLightTheme();
        }
    } else if (theme == Dark) {
        setDarkTheme();
    } else if (theme == Modern) {
        setModernTheme();
    } else {
        setLightTheme();
    }
}

void ThemeUtils::setDarkTheme()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    if (!app) return;

    // 深色模式必须使用 Fusion 风格，因为 WindowsVista 风格强制使用浅色控件
    app->setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    QColor darkColor = QColor(45, 45, 45);
    QColor disabledColor = QColor(127, 127, 127);

    darkPalette.setColor(QPalette::Window, darkColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(18, 18, 18));
    darkPalette.setColor(QPalette::AlternateBase, darkColor);
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
    darkPalette.setColor(QPalette::Button, darkColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));

    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, disabledColor);

    app->setPalette(darkPalette);
    app->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

void ThemeUtils::setModernTheme()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    if (!app) return;

    app->setStyle(QStyleFactory::create("Fusion"));

    QPalette modernPalette;
    QColor baseColor = QColor(25, 25, 25);
    QColor accentColor = QColor(98, 197, 85); // Tech Green
    
    modernPalette.setColor(QPalette::Window, baseColor);
    modernPalette.setColor(QPalette::WindowText, QColor(230, 230, 230));
    modernPalette.setColor(QPalette::Base, QColor(15, 15, 15));
    modernPalette.setColor(QPalette::AlternateBase, baseColor);
    modernPalette.setColor(QPalette::Text, Qt::white);
    modernPalette.setColor(QPalette::Button, QColor(45, 45, 45));
    modernPalette.setColor(QPalette::ButtonText, Qt::white);
    modernPalette.setColor(QPalette::Highlight, accentColor);
    modernPalette.setColor(QPalette::HighlightedText, Qt::black);

    app->setPalette(modernPalette);

    QString qss = 
        "QMainWindow { background-color: #1a1a1a; }"
        "QGroupBox { font-weight: bold; border: 1px solid rgba(255, 255, 255, 0.1); border-radius: 12px; margin-top: 15px; padding-top: 10px; background-color: rgba(255, 255, 255, 0.03); }"
        "QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top left; left: 15px; padding: 0 5px; color: #62C555; }"
        "QPushButton#sliderLabel { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #62C555, stop:1 #4CAF50); border-radius: 20px; color: white; font-weight: bold; border: none; }"
        "QPushButton#sliderLabel:hover { background: #73d666; }"
        "QSlider::groove:horizontal { border: 1px solid rgba(255, 255, 255, 0.1); height: 6px; background: rgba(255, 255, 255, 0.05); margin: 2px 0; border-radius: 3px; }"
        "QSlider::handle:horizontal { background: #62C555; border: 1px solid #4CAF50; width: 18px; height: 18px; margin: -7px 0; border-radius: 9px; }"
        "QLineEdit#processNameFilter { background: rgba(255, 255, 255, 0.05); border: 1px solid rgba(255, 255, 255, 0.1); border-radius: 15px; padding: 5px 15px; color: white; selection-background-color: #62C555; }"
        "QLineEdit#processNameFilter:focus { border: 1px solid #62C555; background: rgba(255, 255, 255, 0.08); }"
        "QTreeWidget { background-color: transparent; border: none; outline: none; }"
        "QTreeWidget::item { height: 35px; border-bottom: 1px solid rgba(255, 255, 255, 0.02); }"
        "QTreeWidget::item:selected { background-color: rgba(98, 197, 85, 0.15); color: #62C555; border-radius: 4px; }"
        "QHeaderView::section { background-color: rgba(30, 30, 30, 0.8); color: #888; padding: 5px; border: none; border-bottom: 1px solid rgba(255, 255, 255, 0.1); font-weight: bold; }";

    app->setStyleSheet(qss);
}

void ThemeUtils::setLightTheme()
{
    QApplication* app = static_cast<QApplication*>(QApplication::instance());
    if (!app) return;

    // 浅色模式优先使用 WindowsVista (原生) 风格
    QStyle* style = QStyleFactory::create("Fusion");
    if (!style) {
        style = QStyleFactory::create("Windows");
    }
    app->setStyle(style);
    
    // 恢复默认调色板
    app->setPalette(style->standardPalette());
    
    // 清除全局样式表
    app->setStyleSheet("");
}

bool ThemeUtils::isSystemDarkMode()
{
#ifdef Q_OS_WIN
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", QSettings::NativeFormat);
    return settings.value("AppsUseLightTheme", 1).toInt() == 0;
#else
    return false; 
#endif
}
