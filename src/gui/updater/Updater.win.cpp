/* Copyright (C) 2016 Alexander Shishenko <alex@shishenko.com>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
#ifdef BUILD_UPDATER

#include "Updater.h"
#include <winsparkle.h>

Updater::Updater(QObject* parent) : QObject(parent) {
	QString appcast_url = QStringLiteral("https://releases.librevault.com/appcast_win.rss");

	win_sparkle_set_appcast_url(appcast_url.toUtf8().data());
	win_sparkle_set_registry_path("Software\\Librevault\\Updates");
	win_sparkle_init();
}

Updater::~Updater() {
	win_sparkle_cleanup();
}

bool Updater::supportsUpdate() const {
	return true;
}

bool Updater::enabled() const {
	return (bool)win_sparkle_get_automatic_check_for_updates();
}

void Updater::checkUpdates() {
	win_sparkle_check_update_with_ui();
}

void Updater::checkUpdatesSilently() {
	win_sparkle_check_update_without_ui();
}

void Updater::setEnabled(bool enable) {
	win_sparkle_set_automatic_check_for_updates(enable);
}

#endif	/* BUILD_UPDATER */
