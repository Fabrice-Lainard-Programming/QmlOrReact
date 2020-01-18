#ifndef BACKEND_H
#define BACKEND_H
/*--------------------------------------------------------------------------
* Project: Reat Over QML / Qt Project
* Author Fabrice Lainard Created : 18/01/2020
*
* Copyright (c) Fabtice Lainard Programming. All rights reserved.
* Licensed under the MIT License.
--------------------------------------------------------------------------*/

#include <QObject>
#include <QString>
#include <QStringList>

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QStringList list MEMBER _list NOTIFY listChanged)
public:
    explicit BackEnd(QObject *parent = nullptr);
    QString userName();
    void setUserName(const QString &userName);
    QStringList& list();
signals:
    void userNameChanged();
    void listChanged();
public slots:
    void addListElement(const QString& str);
private:
    QString _userName;
    QStringList _list;
};

#endif // BACKEND_H
