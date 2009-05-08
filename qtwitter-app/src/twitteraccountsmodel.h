/***************************************************************************
 *   Copyright (C) 2008-2009 by Dominik Kapusta       <d@ayoy.net>         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 2.1 of      *
 *   the License, or (at your option) any later version.                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this program; if not, write to                     *
 *   the Free Software Foundation, Inc.,                                   *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef TWITTERACCOUNTSMODEL_H
#define TWITTERACCOUNTSMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <QMetaType>

struct TwitterAccount
{
  bool isEnabled;
  QString login;
  QString password;
  bool directMessages;
  bool operator==( const TwitterAccount &other ) const {
    return ( isEnabled == other.isEnabled &&
             login == other.login &&
             password == other.password &&
             directMessages == other.directMessages );
  }
};

Q_DECLARE_METATYPE(TwitterAccount)

class TwitterAccountsModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  TwitterAccountsModel( QObject *parent = 0 );
  ~TwitterAccountsModel();

  int rowCount( const QModelIndex &parent = QModelIndex() ) const;
  int columnCount( const QModelIndex &parent = QModelIndex() ) const;

  QModelIndex index( int row, int column, const QModelIndex &parent = QModelIndex() ) const;
  QModelIndex parent( const QModelIndex &index ) const;

  Qt::ItemFlags flags(const QModelIndex &index) const;

  QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const;
  bool setData( const QModelIndex &index, const QVariant & value, int role );
  QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

  bool insertAccount( int row, TwitterAccount* account);
  bool insertRows( int row, int count, const QModelIndex &parent = QModelIndex() );
  bool removeRows( int row, int count, const QModelIndex &parent = QModelIndex() );
  void clear();

  QList<TwitterAccount*>& getAccounts();
  TwitterAccount* account( int index );
  TwitterAccount* account( const QString &login );
  int indexOf( TwitterAccount* account );

private:
  TwitterAccount* emptyAccount();
  QList<TwitterAccount*> accounts;
};

#endif // TWITTERACCOUNTSMODEL_H
