/*--------------------------------------------------------------------------
* Project: Reat Over QML / Qt Project
* Author Fabrice Lainard Created : 18/01/2020
*
* Copyright (c) Fabtice Lainard Programming. All rights reserved.
* Licensed under the MIT License.
--------------------------------------------------------------------------*/

import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import QtWebEngine 1.6
import backend 1.0

ApplicationWindow {
    id: root
    width: 500
    height: 400
    visible: true
    title: "Qml Vs React - Fabrice Lainard Programming"


    WebEngineView {
        anchors.fill: parent
        url: "http://localhost:3000/"
        settings.autoLoadImages: true
              settings.javascriptEnabled: true
              settings.errorPageEnabled: false
              settings.pluginsEnabled: true
              settings.fullScreenSupportEnabled: true

              settings.javascriptCanOpenWindows: true
              settings.javascriptCanAccessClipboard: true
              settings.localContentCanAccessRemoteUrls: true
              backgroundColor: "transparent"
              profile: WebEngineProfile {
                  httpCacheType: WebEngineProfile.NoCache
              }

              onCertificateError: function(error) {
                  error.ignoreCertificateError()
              }

              onFeaturePermissionRequested: function(securityOrigin, feature) {
                  grantFeaturePermission(securityOrigin, feature, true);
              }

    }
}
