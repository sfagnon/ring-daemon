/*
 *  Copyright (C) 2013 Savoir-Faire Linux Inc.
 *  Author: Patrick Keroulas <patrick.keroulas@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 *
 *  Additional permission under GNU GPL version 3 section 7:
 *
 *  If you modify this program, or any covered work, by linking or
 *  combining it with the OpenSSL project's OpenSSL library (or a
 *  modified version of that library), containing parts covered by the
 *  terms of the OpenSSL or SSLeay licenses, Savoir-Faire Linux Inc.
 *  grants you additional permission to convey the resulting work.
 *  Corresponding Source for a non-source form of such a combination
 *  shall include the source code for the parts of OpenSSL used as well
 *  as that of the covered work.
 */

#ifndef PRESENCEMANAGERI_H
#define PRESENCEMANAGERI_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <vector>
#include <map>
#include <string>
#include <functional>

#include "dring.h"

namespace DRing {

// Presence signal type definitions
struct PresenceSignal {
        struct NewServerSubscriptionRequest {
                constexpr static const char* name = "NewServerSubscriptionRequest";
                using cb_type = void(const std::string& /*remote*/);
        };
        struct ServerError {
                constexpr static const char* name = "ServerError";
                using cb_type = void(const std::string& /*account_id*/, const std::string& /*error*/, const std::string& /*msg*/);
        };
        struct NewBuddyNotification {
                constexpr static const char* name = "NewBuddyNotification";
                using cb_type = void(const std::string& /*account_id*/, const std::string& /*buddy_uri*/, int /*status*/, const std::string& /*line_status*/);
        };
        struct SubscriptionStateChanged {
                constexpr static const char* name = "SubscriptionStateChanged";
                using cb_type = void(const std::string& /*account_id*/, const std::string& /*buddy_uri*/, int /*state*/);
        };
};

void registerPresHandlers(const std::map<std::string, std::shared_ptr<CallbackWrapperBase>>&);

/* Presence subscription/Notification. */
void publish(const std::string& accountID, bool status, const std::string& note);
void answerServerRequest(const std::string& uri, bool flag);
void subscribeBuddy(const std::string& accountID, const std::string& uri, bool flag);
std::vector<std::map<std::string, std::string>> getSubscriptions(const std::string& accountID);
void setSubscriptions(const std::string& accountID, const std::vector<std::string>& uris);

} // namespace DRing

#endif //PRESENCEMANAGERI_H