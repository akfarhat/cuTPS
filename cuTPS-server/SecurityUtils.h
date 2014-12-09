#ifndef SECURITYUTILS_H
#define SECURITYUTILS_H

#include <QString>
#include <QByteArray>

class SecurityUtils
{
public:
    SecurityUtils();

    QString  makePasswordHash(QString uname,
                              QString pwd,
                              QString salt="");

    bool     validatePassword(QString uname,
                              QString pwd,
                              QString h);

    static QString  makeSecureValue(QString str);
    // Returns value on match or empty string otherwise.
    static QString  checkSecureValue(QString str);

private:
    QString  generateSalt(int length=5);

    static QString  hashPassword(QString password);
    static QString  hashString(QString string);
    static QString  hmacSha1(QByteArray key, QByteArray baseString);
};

#endif // SECURITYUTILS_H
