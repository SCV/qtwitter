/***************************************************************************
 *   Copyright (C) 2009 by Mariusz Pietrzyk       <wijet@wijet.pl>         *
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


#ifndef URLSHORTENER_H
#define URLSHORTENER_H

#include <QObject>

class QNetworkReply;
class QNetworkAccessManager;

class UrlShortener : public QObject
{
  Q_OBJECT

public:
  UrlShortener( QObject *parent = 0 );
  virtual ~UrlShortener();
  virtual void shorten( const QString &url ) = 0;

  enum Shorteners {
    SHORTENER_ISGD,
    SHORTENER_TRIM,
    SHORTENER_METAMARK,
    SHORTENER_TINYURL,
    SHORTENER_TINYARROWS,
    SHORTENER_UNU
  };

protected:
    QNetworkAccessManager *connection;
    int replyStatus( QNetworkReply *reply ) const;

signals:
    void shortened( const QString &url );
    void errorMessage( const QString &message );

protected slots:
    virtual void replyFinished( QNetworkReply* ) = 0;
};

class IsgdShortener : public UrlShortener
{
  Q_OBJECT

  public:
    IsgdShortener( QObject *parent = 0);
    void shorten( const QString &url );
  protected slots:
    virtual void replyFinished( QNetworkReply* );
};

class TrimShortener : public UrlShortener
{
  Q_OBJECT

  public:
    TrimShortener( QObject *parent = 0);
    void shorten( const QString &url );
  protected slots:
    virtual void replyFinished( QNetworkReply* );
};

class MetamarkShortener : public UrlShortener
{
  Q_OBJECT

  public:
    MetamarkShortener( QObject *parent = 0);
    void shorten( const QString &url );
  protected slots:
    virtual void replyFinished( QNetworkReply* );
};

class TinyurlShortener : public UrlShortener
{
  Q_OBJECT

  public:
    TinyurlShortener( QObject *parent = 0);
    void shorten( const QString &url );
  protected slots:
    virtual void replyFinished( QNetworkReply* );
};

class TinyarrowsShortener : public UrlShortener
{
  Q_OBJECT

  public:
    TinyarrowsShortener( QObject *parent = 0);
    void shorten( const QString &url );
  protected slots:
    virtual void replyFinished( QNetworkReply* );
};

class UnuShortener : public UrlShortener
{
  Q_OBJECT

  public:
    UnuShortener( QObject *parent = 0);
    void shorten( const QString &url );
  protected slots:
    virtual void replyFinished( QNetworkReply* );
};

#endif // URLSHORTENER_H
