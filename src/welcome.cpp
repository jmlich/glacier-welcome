/****************************************************************************************
**
** Copyright (C) 2025 Sergey Chupligin <mail@neochapay.ru>
** All rights reserved.
**
** You may use this file under the terms of BSD license as follows:
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of the author nor the
**       names of its contributors may be used to endorse or promote products
**       derived from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
** DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
** ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
** (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
** ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
** SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
****************************************************************************************/

#include "welcome.h"

#include <QDBusPendingCall>
#include <QDBusVariant>
#include <QDebug>
#include <QFile>
#include <QStandardPaths>

#include <glacierdevicepassword.h>

Welcome::Welcome(QObject* parent)
    : QObject(parent)
    , m_mceDbus(new QDBusInterface("com.nokia.mce", "/com/nokia/mce/request", "com.nokia.mce.request", QDBusConnection::systemBus()))
    , m_password(new GlacierDevicePassword(this))
{
}

void Welcome::startWelcome()
{
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/display/inhibit_blank_mode").path(), QVariant::fromValue(QDBusVariant(3)));
    m_mceDbus->asyncCall("req_tklock_mode_change", "unlocked");
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/locks/tklock_blank_disable").path(), QVariant::fromValue(QDBusVariant(1)));
}

void Welcome::endWelcome()
{
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/display/inhibit_blank_mode").path(), QVariant::fromValue(QDBusVariant(0)));
    m_mceDbus->asyncCall("req_tklock_mode_change", "locked");
    m_mceDbus->asyncCall("set_config", QDBusObjectPath("/system/osso/dsm/locks/tklock_blank_disable").path(), QVariant::fromValue(QDBusVariant(0)));
}

bool Welcome::passwordIsSet()
{
    return m_password->isSet();
}

void Welcome::setPassword(const QString password)
{

    if (!m_password->setCode("", password.toUtf8())) {
        emit setPassError();
        qWarning() << "Setting of password failed";
    } else {
        emit setPassOk();
    }
}

QString Welcome::pass1() const
{
    return m_pass1;
}

void Welcome::setPass1(const QString& newPass1)
{
    if (m_pass1 == newPass1)
        return;
    m_pass1 = newPass1;
    emit pass1Changed();
}
