#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <QJsonDocument>

namespace JSONParser {
    QByteArray getContents(const QString &filePath);
    QVariantMap parse(const QByteArray &jsonString = R"({"key":"value"})");
}

#endif // JSON_PARSER_H
