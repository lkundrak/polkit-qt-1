/*
 * This file is part of the Polkit-qt project
 * Copyright (C) 2009 Daniel Nicoletti <dantti85-pk@yahoo.com.br>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#define PK_NAME      "org.freedesktop.PolicyKit.AuthenticationAgent"
#define PK_PATH      "/"
#define PK_INTERFACE "org.freedesktop.PolicyKit.AuthenticationAgent"

#include "auth.h"
#include "action.h"
#include "context.h"

#include <limits.h>
#include <polkit-dbus/polkit-dbus.h>

#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtCore/QDebug>

using namespace PolkitQt;

bool Auth::computeAndObtainAuth(const QString &actionId, uint winId, uint pid)
{
    PolKitAction *pkAction = polkit_action_new();
    if (!polkit_action_set_action_id(pkAction, actionId.toAscii().data())) {
        return false;
    }
    PolKitResult result;
    // set revokeIfOneShot to false as we only want to check it,
    // otherwise we would be revoking one shot actions
    result = isCallerAuthorized(pkAction, pid, false);
    switch (result) {
    case POLKIT_RESULT_YES:
        // If PolicyKit says yes.. emit the 'activated' signal
        return true;
        break;
    case POLKIT_RESULT_ONLY_VIA_ADMIN_AUTH_ONE_SHOT:
    case POLKIT_RESULT_ONLY_VIA_ADMIN_AUTH:
    case POLKIT_RESULT_ONLY_VIA_ADMIN_AUTH_KEEP_SESSION:
    case POLKIT_RESULT_ONLY_VIA_ADMIN_AUTH_KEEP_ALWAYS:
    case POLKIT_RESULT_ONLY_VIA_SELF_AUTH_ONE_SHOT:
    case POLKIT_RESULT_ONLY_VIA_SELF_AUTH:
    case POLKIT_RESULT_ONLY_VIA_SELF_AUTH_KEEP_SESSION:
    case POLKIT_RESULT_ONLY_VIA_SELF_AUTH_KEEP_ALWAYS:
        // Otherwise, the action needs auth..
        // we now issue the obtain auth dialog
        if (pkAction != 0) {
            return obtainAuth(actionId, winId, pid);
        }
    default:
    case POLKIT_RESULT_NO:
        // if result is no then the user cannot even try to auth
        return false;
        break;
    }
}

bool Auth::obtainAuth(const QString &actionId, uint winId, uint pid)
{
    QDBusMessage message;
    message = QDBusMessage::createMethodCall(PK_NAME,
                                             PK_PATH,
                                             PK_INTERFACE,
                                             QLatin1String("ObtainAuthorization"));
    QList<QVariant> argumentList;
    argumentList << qVariantFromValue(actionId) << qVariantFromValue(winId) << qVariantFromValue(pid);
    message.setArguments(argumentList);
    // Do a session bus call with BlockWithGui to create an event loop
    // and INT_MAX to get the highier timeout
    QDBusMessage reply = QDBusConnection::sessionBus().call(message, QDBus::BlockWithGui, INT_MAX);
    if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().size() == 1) {
        return reply.arguments().first().toBool();
    } else if (reply.type() == QDBusMessage::MethodCallMessage) {
        qWarning() << "Message did not receive a reply (timeout by message bus)";
    }
    return false;
}

PolKitResult Auth::isCallerAuthorized(const QString &actionId, uint pid, bool revokeIfOneShot)
{
    PolKitAction *pk_action = polkit_action_new();

    if (!polkit_action_set_action_id(pk_action, actionId.toAscii().data())) {
        return POLKIT_RESULT_UNKNOWN;
    }

    return isCallerAuthorized(pk_action, pid, revokeIfOneShot);
}

PolKitResult Auth::isCallerAuthorized(PolKitAction *action, pid_t pid, bool revokeIfOneShot)
{
    PolKitCaller *pk_caller;
    PolKitResult pk_result;
    DBusError dbus_error;

    if (Context::instance()->hasError()) {
        return pk_result = POLKIT_RESULT_UNKNOWN;
    }

    dbus_error_init (&dbus_error);
    pk_caller = polkit_tracker_get_caller_from_pid(Context::instance()->getPolKitTracker(),
                                                   pid,
                                                   &dbus_error);
    if (pk_caller == NULL) {
        qWarning("Cannot get PolKitCaller object for target (pid=%d): %s: %s",
                 pid, dbus_error.name, dbus_error.message);
        dbus_error_free(&dbus_error);

        // this is bad so cop-out to UKNOWN
        pk_result = POLKIT_RESULT_UNKNOWN;
    } else {
        pk_result = polkit_context_is_caller_authorized (Context::instance()->getPolKitContext(),
                                                        action,
                                                        pk_caller,
                                                        revokeIfOneShot,
                                                        NULL);
        polkit_caller_unref (pk_caller);
    }

    return pk_result;
}

PolKitResult Auth::isCallerAuthorized(PolKitAction *action, const QString &dbusName, bool revokeIfOneShot)
{
    PolKitCaller *pk_caller;
    PolKitResult pk_result;
    DBusError dbus_error;

    if (Context::instance()->hasError()) {
        return pk_result = POLKIT_RESULT_UNKNOWN;
    }

    dbus_error_init (&dbus_error);
    pk_caller = polkit_tracker_get_caller_from_dbus_name(Context::instance()->getPolKitTracker(),
                                                         dbusName.toLatin1().data(),
                                                         &dbus_error);
    if (pk_caller == NULL) {
        qWarning("Cannot get PolKitCaller object for DBus name (dbusName=%d): %s: %s",
                 dbusName, dbus_error.name, dbus_error.message);
        dbus_error_free(&dbus_error);

        // this is bad so cop-out to UKNOWN
        pk_result = POLKIT_RESULT_UNKNOWN;
    } else {
        pk_result = polkit_context_is_caller_authorized (Context::instance()->getPolKitContext(),
                                                        action,
                                                        pk_caller,
                                                        revokeIfOneShot,
                                                        NULL);
        polkit_caller_unref (pk_caller);
    }

    return pk_result;
}
