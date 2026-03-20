#include "json_parser.h"

#include <QDebug>
#include <QJsonObject>
#include <QFile>

QByteArray JSONParser::getContents(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray contents = file.readAll();
        file.close();
        return contents;
    }
    return QByteArray();
}

QVariantMap JSONParser::parse(const QByteArray &jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString);

    if (doc.isObject()) {
        QVariantMap map = doc.object().toVariantMap();
        return map;
    }

    return QVariantMap();
}
