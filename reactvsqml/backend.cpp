/*--------------------------------------------------------------------------
* Project: Reat Over QML / Qt Project
* Author Fabrice Lainard Created : 18/01/2020
*
* Copyright (c) Fabtice Lainard Programming. All rights reserved.
* Licensed under the MIT License.
--------------------------------------------------------------------------*/


#include "backend.h"

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
}

QString BackEnd::userName()
{
    return _userName;
}

void BackEnd::setUserName(const QString &userName)
{
    if (userName == _userName)
        return;

    _userName = userName;
    emit userNameChanged();
}

void BackEnd::addListElement(const QString& str)
{
    _list.push_back(str);
    emit listChanged();
}

QStringList& BackEnd::list()
{
    return _list;
}
