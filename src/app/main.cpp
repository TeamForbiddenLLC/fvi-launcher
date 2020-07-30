// Pegasus Frontend
// Copyright (C) 2017-2020  Mátyás Mustoha
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.


#include "backend/Backend.h"
#include "backend/LocaleUtils.h"
#include "backend/platform/TerminalKbd.h"

#include <QCommandLineParser>
#include <QGuiApplication>
#include <QIcon>
#include <QSettings>

backend::CliArgs handle_cli_args(QGuiApplication&);

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(frontend);
    Q_INIT_RESOURCE(themes);
    Q_INIT_RESOURCE(qmlutils);

    TerminalKbd::on_startup();

    QCoreApplication::addLibraryPath(QStringLiteral("lib/plugins"));
    QCoreApplication::addLibraryPath(QStringLiteral("lib"));
    QSettings::setDefaultFormat(QSettings::IniFormat);

    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("fvi-launcher"));
    app.setApplicationVersion(QStringLiteral(GIT_REVISION));
    app.setOrganizationName(QStringLiteral("fvi-launcher"));
    app.setOrganizationDomain(QStringLiteral("forbidden.gg"));
    app.setWindowIcon(QIcon(QStringLiteral(":/icon.png")));

    backend::CliArgs cli_args = handle_cli_args(app);
    backend::Backend backend(cli_args);
    backend.start();

    return app.exec();
}

QCommandLineOption add_cli_option(QCommandLineParser& parser, const QString& name, const QString& desc)
{
    QCommandLineOption arg(name, desc);
    parser.addOption(arg);
    return arg;
}

backend::CliArgs handle_cli_args(QGuiApplication& app)
{
    QCommandLineParser argparser;
    argparser.setApplicationDescription(tr_log(
        "\nFVI is a graphical frontend for browsing your game library (especially\n"
        "retro games) and launching them from one place. It's focusing on customization,\n"
        "cross platform support (including embedded devices) and high performance."));

    const QCommandLineOption arg_portable = add_cli_option(argparser,
        QStringLiteral("portable"),
        tr_log("Do not read or write config files outside the program's directory"));

    const QCommandLineOption arg_silent = add_cli_option(argparser,
        QStringLiteral("silent"),
        tr_log("Do not print log messages to the terminal"));

    const QCommandLineOption arg_menu_reboot = add_cli_option(argparser,
        QStringLiteral("disable-menu-reboot"),
        tr_log("Hides the system reboot entry in the main menu"));

    const QCommandLineOption arg_menu_shutdown = add_cli_option(argparser,
        QStringLiteral("disable-menu-shutdown"),
        tr_log("Hides the system shutdown entry in the main menu"));

    const QCommandLineOption arg_menu_appclose = add_cli_option(argparser,
        QStringLiteral("disable-menu-appclose"),
        tr_log("Hides the closing FVI entry in the main menu"));

    const QCommandLineOption arg_menu_settings = add_cli_option(argparser,
        QStringLiteral("disable-menu-settings"),
        tr_log("Hides the settings menu entry in the main menu"));

    const QCommandLineOption arg_menu_kiosk = add_cli_option(argparser,
        QStringLiteral("kiosk"),
	tr_log("Alias for:\n"
               "--disable-menu-reboot\n"
               "--disable-menu-shutdown\n"
               "--disable-menu-appclose\n"
               "--disable-menu-settings"));

    argparser.addHelpOption();
    argparser.addVersionOption();
    argparser.process(app); // may quit!

    backend::CliArgs args;
    args.silent = argparser.isSet(arg_silent);
    args.enable_menu_appclose = !(argparser.isSet(arg_menu_kiosk) || argparser.isSet(arg_menu_appclose));
    args.enable_menu_shutdown = !(argparser.isSet(arg_menu_kiosk) || argparser.isSet(arg_menu_shutdown));
    args.enable_menu_reboot = !(argparser.isSet(arg_menu_kiosk) || argparser.isSet(arg_menu_reboot));
    args.enable_menu_settings = !(argparser.isSet(arg_menu_kiosk) || argparser.isSet(arg_menu_settings));
    return args;
}