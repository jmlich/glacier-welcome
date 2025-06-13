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

#ifndef WELCOME_H
#define WELCOME_H

#include <QDBusInterface>
#include <QObject>
class GlacierDevicePassword;

class Welcome : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString pass1 READ pass1 WRITE setPass1 NOTIFY pass1Changed FINAL)
public:
    explicit Welcome(QObject* parent = nullptr);
    Q_INVOKABLE void startWelcome();
    Q_INVOKABLE void endWelcome();
    Q_INVOKABLE bool passwordIsSet();
    Q_INVOKABLE void setPassword(const QString password);

    QString pass1() const;
    void setPass1(const QString& newPass1);

signals:
    void pass1Changed();
    void setPassError();

private:
    QDBusInterface* m_mceDbus;
    GlacierDevicePassword* m_password;
    QString m_pass1;
};

#endif // WELCOME_H
