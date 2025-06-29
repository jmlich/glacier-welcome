/****************************************************************************************
**
** Copyright (C) 2025 Chupligin Sergey <neochapay@gmail.com>
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

import QtQuick
import Nemo

Item {
    id:button
    width: Theme.itemWidthSmall
    height: width


    Rectangle{
        id: buttonBackground
        anchors.fill: parent
        color: Theme.backgroundColor
        radius: width/2
        opacity: 0.5
        visible: numLabel.text != "OK" && numLabel.text != "<"
    }

    Text {
        id: numLabel
        text: modelData
        font.pixelSize: Theme.fontSizeExtraLarge
        anchors.centerIn: parent
        color: Theme.textColor
        font.bold: true
    }

    MouseArea{
        anchors.fill: parent

        onPressed: {
            buttonBackground.color = Theme.accentColor
            buttonBackground.visible = true
        }

        onReleased: {
            if(numLabel.text == "OK" || numLabel.text == "<") {
                buttonBackground.visible = false
            }
            buttonBackground.color = Theme.backgroundColor
        }

        onClicked: {
            feedbackLabel.text = " "
            if (numLabel.text !== "<" && numLabel.text !== "OK") {
                lockCodeField.insert(lockCodeField.cursorPosition, numLabel.text)
            } else {
                if (numLabel.text === "OK") {
                    if(!welcome.pass1) {
                        welcome.pass1 = lockCodeField.text
                        lockCodeField.text = ""
                    } else {
                        if(welcome.pass1 == lockCodeField.text) {
                            welcome.setPassword(lockCodeField.text)
                        }
                    }
                } else if (numLabel.text === "<"){
                    lockCodeField.text = lockCodeField.text.slice(0, -1)
                }
            }
        }

        onPressAndHold: {
            if (numLabel.text === "<"){
                lockCodeField.text = ""
            }
        }
    }
}
