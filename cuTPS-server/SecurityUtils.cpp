#include "SecurityUtils.h"

#include <QStringList>
#include <QCryptographicHash>
#include <QChar>
#include <QTime>

#include "Secrets.h"

SecurityUtils::SecurityUtils()
{
    qsrand(QTime::currentTime().msec());
}

QString SecurityUtils::makePasswordHash(QString uname, QString pwd, QString salt)
{
    if (salt.isEmpty())
    {
        salt = generateSalt();
    }

    QString concat = uname + pwd + salt;

    QString hash = hmacSha1(TPSSecretDef::PWD_SECRET.toUtf8(), concat.toUtf8());

    return QString("%1|%2").arg(hash, salt);
}

bool SecurityUtils::validatePassword(QString uname, QString pwd, QString h)
{
    // second part of the hash is the salt
    QString salt = h.split("|").at(1);
    return h == makePasswordHash(uname, pwd, salt);
}

QString SecurityUtils::makeSecureValue(QString s)
{
    return QString("%1|%2").arg(s, hashString(s));
}

QString SecurityUtils::checkSecureValue(QString h)
{
    // checks secure value of its argument
    QString h_copy = QString(h);
    QString val = h_copy.split("|").at(0);

    if (h == makeSecureValue(val)) {
        return val;
    } else {
        return QString(); // empty string.
    }
}

QString SecurityUtils::hashPassword(QString pwd)
{
    return hmacSha1(TPSSecretDef::PWD_SECRET.toUtf8(), pwd.toUtf8());
}

QString SecurityUtils::hashString(QString s)
{
    return hmacSha1(TPSSecretDef::SECRET.toUtf8(), s.toUtf8());
}

QString SecurityUtils::generateSalt(int length)
{
    QString salt;
    salt.resize(length);

    for (int i = 0; i < length; ++i)
    {
        // 66% chance to insert a letter, 33% to digit
        if ((qrand() % 3) == 0) {
            // insert random digit 0-9
            salt[i] = QString::number(qrand() % 10).at(0);
        } else {
            // insert random character A-Z
            salt[i] = QChar('A' + char(qrand() % ('Z' - 'A')));
        }
    }

    return salt;
}

QString SecurityUtils::hmacSha1(QByteArray key, QByteArray baseString)
{
    // Source: http://qt-project.org/wiki/HMAC-SHA1
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "\"
    // ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }

    // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed.toHex();
}
