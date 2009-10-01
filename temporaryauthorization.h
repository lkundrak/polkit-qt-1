/*
 * This file is part of the PolKit1-qt project
 * Copyright (C) 2009 Radek Novacek <rnovacek@redhat.com>
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

#ifndef TEMPORARYAUTHORIZATION_H
#define TEMPORARYAUTHORIZATION_H

#include <polkit/polkit.h>
#include <QtCore/QObject>
#include <QtCore/QDateTime>
#include "subject.h"

/**
 * \namespace PolkitQt PolkitQt
 *
 * \brief Namespace wrapping PolicyKit-Qt classes
 *
 * This namespace wraps all PolicyKit-Qt classes.
 */
namespace PolkitQt
{

/**
 * \class TemporaryAuthorization temporaryauthorization.h TemporaryAuthorization
 * \author Radek Novacek <rnovacek@redhat.com>
 *
 * \brief This class represents PolicyKit temporary authorization
 *
 * This class encapsulates the PolkitTemporaryAuthorization interface.
 */
class POLKIT_QT_EXPORT TemporaryAuthorization : public QObject
{
    Q_OBJECT
public:
    TemporaryAuthorization(PolkitTemporaryAuthorization *tempAuth);

    /**
     * \brief Gets the identifier for the authorization.
     *
     * This identifier can be user by the revokeTemporaryAuthorization function
     *
     * \return Unique identifier for the authorization
     */
    QString id() const;

    /**
     * \brief Gets the identifier of the action that authorization is for
     *
     * \return String that identifies the action
     */
    QString actionId() const;

    /**
     * \brief Gets the subject that authorization is for
     *
     * \return A Subject.
     */
    Subject *subject();

    /**
     * \brief Gets the time when authorization was obtained
     *
     * \return Time of obtaining the authorization
     */
    QDateTime timeObtained() const;

    /**
     * \brief Gets the time when authorizaton will expire
     *
     * \return Time of expiration
     */
    QDateTime timeExpires() const;

    /**
     * \brief Revoke temporary authorization
     *
     * \return \c true Authorization has been revoked
     *         \c false Revoking authorization failed
     */
    bool revoke();

private:
    PolkitTemporaryAuthorization *m_temporaryAuthorization;
    QString m_id, m_actionId;
    Subject *m_subject;
    QDateTime m_timeObtained, m_timeExpires;
};
}

#endif // TEMPORARYAUTHORIZATION_H