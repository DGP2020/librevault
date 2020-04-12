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
#pragma once
#include <string>
#include <cstdint>

namespace librevault {

struct url;

url parse_url(std::string url_str);

struct url {
	url() {}
	url(std::string str) {*this = parse_url(std::move(str));}
	std::string scheme;
	std::string userinfo;
	std::string host;
	uint16_t port = 0;
	std::string query;

	bool is_ipv6 = false;

	operator std::string() const;
	bool operator==(const url& u) const {
		return (scheme == u.scheme) && (userinfo == u.userinfo) && (host == u.host) && (port == u.port) && (query == u.query);
	}
	bool empty() const {return *this == url();}   // Not optimal, but simple
};

} /* namespace librevault */
