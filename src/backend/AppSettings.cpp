// Pegasus Frontend
// Copyright (C) 2017-2018  Mátyás Mustoha
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


#include "AppSettings.h"

#include "Paths.h"
#include "ScriptRunner.h"
#include "parsers/SettingsFile.h"

#include "providers/pegasus_favorites/Favorites.h"
#include "providers/pegasus_metadata/PegasusProvider.h"
#include "providers/pegasus_playtime/PlaytimeStats.h"

#include <QFile>


namespace {
HashMap<KeyEvent, QVector<QKeySequence>, EnumHash> default_keymap()
{
    return {
        { KeyEvent::LEFT, { Qt::Key_Left }},
        { KeyEvent::RIGHT, { Qt::Key_Right }},
        { KeyEvent::UP, { Qt::Key_Up }},
        { KeyEvent::DOWN, { Qt::Key_Down }},
        { KeyEvent::ACCEPT, { Qt::Key_Return, Qt::Key_Enter, GamepadKeyId::A }},
        { KeyEvent::CANCEL, { Qt::Key_Escape, Qt::Key_Backspace, GamepadKeyId::B }},
        { KeyEvent::DETAILS, { Qt::Key_I, GamepadKeyId::X }},
        { KeyEvent::FILTERS, { Qt::Key_F, GamepadKeyId::Y }},
        { KeyEvent::NEXT_PAGE, { Qt::Key_E, Qt::Key_D, GamepadKeyId::R1 }},
        { KeyEvent::PREV_PAGE, { Qt::Key_Q, Qt::Key_A, GamepadKeyId::L1 }},
        { KeyEvent::PAGE_UP, { Qt::Key_PageUp, GamepadKeyId::L2 }},
        { KeyEvent::PAGE_DOWN, { Qt::Key_PageDown, GamepadKeyId::R2 }},
        { KeyEvent::MAIN_MENU, { Qt::Key_Tab, GamepadKeyId::START }},
    };
}

std::map<QKeySequence, QString> gamepad_button_names()
{
    return {
        { QKeySequence(GamepadKeyId::A), QStringLiteral("A") },
        { QKeySequence(GamepadKeyId::B), QStringLiteral("B") },
        { QKeySequence(GamepadKeyId::X), QStringLiteral("X") },
        { QKeySequence(GamepadKeyId::Y), QStringLiteral("Y") },
        { QKeySequence(GamepadKeyId::L1), QStringLiteral("L1") },
        { QKeySequence(GamepadKeyId::L2), QStringLiteral("L2") },
        { QKeySequence(GamepadKeyId::L3), QStringLiteral("L3") },
        { QKeySequence(GamepadKeyId::R1), QStringLiteral("R1") },
        { QKeySequence(GamepadKeyId::R2), QStringLiteral("R2") },
        { QKeySequence(GamepadKeyId::R3), QStringLiteral("R3") },
        { QKeySequence(GamepadKeyId::SELECT), QStringLiteral("Select") },
        { QKeySequence(GamepadKeyId::START), QStringLiteral("Start") },
        { QKeySequence(GamepadKeyId::GUIDE), QStringLiteral("Guide") },
    };
}

std::vector<std::unique_ptr<providers::Provider>> create_providers()
{
#define MKENTRY(T) out.emplace_back(new providers::T());

    std::vector<std::unique_ptr<providers::Provider>> out;
        MKENTRY(pegasus::PegasusProvider)
        MKENTRY(favorites::Favorites)
        MKENTRY(playtime::PlaytimeStats)

    out.shrink_to_fit();
    return out;

#undef MKENTRY
}

} // namespace


namespace appsettings {

General::General()
    : DEFAULT_LOCALE(QStringLiteral("en"))
    , DEFAULT_THEME(QStringLiteral(":/themes/fvi/"))
    , portable(false)
    , fullscreen(false)
    , mouse_support(true)
    , locale(DEFAULT_LOCALE)
    , theme(DEFAULT_THEME)
{}


Keys::Keys()
    : m_event_keymap(default_keymap())
{}
void Keys::add_key(KeyEvent event, QKeySequence keyseq)
{
    for (auto& entry : m_event_keymap)
        entry.second.removeOne(keyseq);

    m_event_keymap.at(event).append(std::move(keyseq));
}
void Keys::del_key(KeyEvent event, const QKeySequence& keyseq)
{
    m_event_keymap.at(event).removeOne(keyseq);
}
void Keys::clear(KeyEvent event)
{
    m_event_keymap.at(event).clear();
}
void Keys::resetAll()
{
    m_event_keymap = default_keymap();
}
const QVector<QKeySequence>& Keys::at(KeyEvent event) const {
    return m_event_keymap.at(event);
}
const QVector<QKeySequence>& Keys::operator[](KeyEvent event) const {
    return at(event);
}

} // namespace appsettings


namespace {



} // namespace


appsettings::General AppSettings::general;
appsettings::Keys AppSettings::keys;
const std::map<QKeySequence, QString> AppSettings::gamepadButtonNames = gamepad_button_names();
const std::vector<std::unique_ptr<providers::Provider>> AppSettings::providers = create_providers();

void AppSettings::load_config()
{
	
    appsettings::LoadContext().load();
	
}

void AppSettings::save_config()
{
    // sanity check
    if (general.locale.isEmpty())
        general.locale = general.DEFAULT_LOCALE;
    if (general.theme.isEmpty())
        general.theme = general.DEFAULT_THEME;


    appsettings::SaveContext().save();


    ScriptRunner::run(ScriptEvent::CONFIG_CHANGED);
    ScriptRunner::run(ScriptEvent::SETTINGS_CHANGED);
}

void AppSettings::parse_gamedirs(const std::function<void(const QString&)>& callback)
{
    constexpr int LINE_MAX_LEN = 4096;

    for (QString& path : paths::configDirs()) {
        path += QStringLiteral("/game_dirs.txt");

        QFile config_file(path);
        if (!config_file.open(QFile::ReadOnly | QFile::Text))
            continue;

        QTextStream stream(&config_file);
        QString line;
        while (stream.readLineInto(&line, LINE_MAX_LEN)) {
            if (!line.startsWith('#'))
                callback(line);
        }
    }
}
