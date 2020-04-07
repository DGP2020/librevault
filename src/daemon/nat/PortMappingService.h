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
#include <QAbstractSocket>
#include <QLoggingCategory>

#include "util/log.h"

Q_DECLARE_LOGGING_CATEGORY(log_portmapping)

namespace librevault {

class NATPMPService;
class UPnPService;
class PortMappingSubService;

struct MappingDescriptor {
  uint16_t port;
  QAbstractSocket::SocketType protocol;
};

class PortMappingService : public QObject {
  Q_OBJECT
  friend class PortMappingSubService;

 public:
  PortMappingService(QObject* parent);
  virtual ~PortMappingService();

  void map(const QString& id, MappingDescriptor descriptor, const QString& description);
  void unmap(const QString& id);
  uint16_t mapped_port(const QString& id);

 private:
  struct Mapping {
    MappingDescriptor descriptor;
    QString description;
    uint16_t port;
  };
  std::map<QString, Mapping> mappings_;

  NATPMPService* natpmp_;
  UPnPService* upnp_;

  void add_existing_mappings(PortMappingSubService* subservice);
};

}  // namespace librevault
