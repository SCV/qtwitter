#include "oauthwizard.h"
#include "ui_oauthwizard.h"
#include "ui_pindialog.h"
#include <QOAuth>

#include <QDesktopServices>
#include <QUrl>
#include <QDateTime>
#include <QDebug>
#include <QRegExpValidator>

const QByteArray OAuthWizard::TwitterRequestTokenURL = "http://twitter.com/oauth/request_token";
const QByteArray OAuthWizard::TwitterAccessTokenURL  = "http://twitter.com/oauth/access_token";
const QByteArray OAuthWizard::TwitterAuthorizeURL    = "http://twitter.com/oauth/authorize";

const QByteArray OAuthWizard::ConsumerKey    = "tIFvBZ10xbiOq5p60EcEdA";
const QByteArray OAuthWizard::ConsumerSecret = "5gXfCncW8qEilc3kAw05db2bbfw8RNsDhEAEl9iijdA";

const QByteArray OAuthWizard::ParamCallback      = "oauth_callback";
const QByteArray OAuthWizard::ParamCallbackValue = "oob";
const QByteArray OAuthWizard::ParamVerifier      = "oauth_verifier";
const QByteArray OAuthWizard::ParamScreenName    = "screen_name";


OAuthWizard::OAuthWizard(QWidget *parent) :
    QDialog(parent),
    state( false ),
    screenName( QByteArray() ),
    token( QByteArray() ),
    tokenSecret( QByteArray() ),
    qoauth( new QOAuth( this ) ),
    ui_o(new Ui::OAuthWizard),
    ui_p(new Ui::PinDialog)
{
  qoauth->setConsumerKey( ConsumerKey );
  qoauth->setConsumerSecret( ConsumerSecret );

  ui_o->setupUi(this);
  adjustSize();

  connect( ui_o->allowButton, SIGNAL(clicked()), this, SLOT(openUrl()) );
}

OAuthWizard::~OAuthWizard()
{
  delete ui_o;
  delete ui_p;
}

QByteArray OAuthWizard::getScreenName() const
{
  if ( screenName.isEmpty() ) {
    qWarning() << __PRETTY_FUNCTION__ << "screenName is empty, did you finished the authorization procedure?";
  }
  return screenName;
}

QByteArray OAuthWizard::getOAuthKey() const
{
  if ( token.isEmpty() || tokenSecret.isEmpty() ) {
    qWarning() << __PRETTY_FUNCTION__ << "token and/or tokenSecret are empty, did you finished the authorization procedure?";
  }
  return token + "&" + tokenSecret;
}

bool OAuthWizard::authorized() const
{
  return state;
}

void OAuthWizard::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui_o->retranslateUi(this);
    ui_p->retranslateUi(this);
    break;
  default:
    break;
  }
}

void OAuthWizard::setOkButtonEnabled()
{
  if ( ui_p->pinEdit->text().isEmpty() ) {
    ui_p->okButton->setEnabled( false );
  } else {
    ui_p->okButton->setEnabled( true );
  }
}

void OAuthWizard::openUrl()
{
  QOAuth::ParamMap requestToken = qoauth->requestToken( TwitterRequestTokenURL, QOAuth::GET,
                                                        QOAuth::HMAC_SHA1, 10000 );

  if ( qoauth->error() != QOAuth::NoError ) {
    ui_o->allowLabel->setText( tr( "There was a network-related problem with completing the request. Please try again later." ) );
    ui_o->allowButton->setText( tr( "Close" ) );
    resize( width(), height() * 1.5 );
    disconnect( ui_o->allowButton, SIGNAL(clicked()), this, SLOT(openUrl()) );
    connect( ui_o->allowButton, SIGNAL(clicked()), this, SLOT(reject()) );
    state = false;
    return;
  }

  token = requestToken.value( QOAuth::ParamToken );
  tokenSecret = requestToken.value( QOAuth::ParamTokenSecret );

  QString url = TwitterAuthorizeURL;

  url.append( "?" );
  url.append( "&" + QOAuth::ParamToken + "=" + token );
  url.append( "&" + ParamCallback + "=" + ParamCallbackValue );

  QDesktopServices::openUrl( QUrl( url ) );

  delete layout();

  ui_o->allowLabel->deleteLater();
  ui_o->allowButton->deleteLater();
  ui_p->setupUi(this);
  ui_p->pinEdit->setValidator( new QRegExpValidator( QRegExp( "\\d{6}" ), this ) );
  connect( ui_p->okButton, SIGNAL(clicked()), this, SLOT(authorize()) );
  connect( ui_p->pinEdit, SIGNAL(textChanged(QString)), this, SLOT(setOkButtonEnabled()) );
}

void OAuthWizard::authorize()
{
  ui_p->pinEdit->setEnabled( false );
  QOAuth::ParamMap otherArgs;
  otherArgs.insert( ParamVerifier, ui_p->pinEdit->text().toAscii() );
  QOAuth::ParamMap accessToken = qoauth->accessToken( TwitterAccessTokenURL, QOAuth::POST, QOAuth::HMAC_SHA1,
                                                      token, tokenSecret, 10000, otherArgs );

  if ( qoauth->error() != QOAuth::NoError ) {
    ui_p->pinEdit->hide();
    ui_p->pinLabel->setText( tr( "Either the PIN you entered is incorrect, or a network-related problem occured. Please try again later." ) );
    ui_p->okButton->setText( tr( "Close" ) );
    resize( width(), height() * 1.5 );
    disconnect( ui_p->okButton, SIGNAL(clicked()), this, SLOT(authorize()) );
    connect( ui_p->okButton, SIGNAL(clicked()), this, SLOT(reject()) );
    state = false;
    return;
  }

  screenName = accessToken.value( ParamScreenName );
  token = accessToken.value( QOAuth::ParamToken );
  tokenSecret = accessToken.value( QOAuth::ParamTokenSecret );
  state = true;
  accept();
}
