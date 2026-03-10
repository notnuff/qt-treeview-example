#include "sqlite_om_data_provider.h"

#include <QCoreApplication>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>

SqliteOMDataProvider::SqliteOMDataProvider(const QString& dbPath)
    : m_isValid(false)
{
    QString fullPath = dbPath;
    if (!QDir::isAbsolutePath(dbPath)) {
        fullPath = QCoreApplication::applicationDirPath() + "/" + dbPath;
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE", "om_data_connection");
    m_database.setDatabaseName(fullPath);

    if (m_database.open()) {
        m_isValid = true;
    } else {
        qWarning() << "Failed to open database:" << m_database.lastError().text();
    }
}

SqliteOMDataProvider::~SqliteOMDataProvider()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
    QSqlDatabase::removeDatabase("om_data_connection");
}

int SqliteOMDataProvider::getCountriesCount()
{
    if (!m_isValid) {
        return 0;
    }

    QSqlQuery query(m_database);
    query.exec("SELECT COUNT(*) FROM countries");
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QString SqliteOMDataProvider::getCountryName(int countryIdx)
{
    if (!m_isValid) {
        return {};
    }

    QSqlQuery query(m_database);
    query.prepare("SELECT name FROM countries ORDER BY name LIMIT 1 OFFSET :offset");
    query.bindValue(":offset", countryIdx);
    query.exec();
    if (query.next()) {
        return query.value(0).toString();
    }
    return {};
}

QString SqliteOMDataProvider::getCountryCode(int countryIdx)
{
    if (!m_isValid) {
        return {};
    }

    QSqlQuery query(m_database);
    query.prepare("SELECT code FROM countries ORDER BY name LIMIT 1 OFFSET :offset");
    query.bindValue(":offset", countryIdx);
    query.exec();
    if (query.next()) {
        return query.value(0).toString();
    }
    return {};
}

int SqliteOMDataProvider::getCountryMcc(int countryIdx)
{
    return getMccForCountryIdx(countryIdx);
}

int SqliteOMDataProvider::getCountryOperatorsCount(int countryIdx)
{
    if (!m_isValid) {
        return 0;
    }

    int mcc = getMccForCountryIdx(countryIdx);
    if (mcc == 0) {
        return 0;
    }

    QSqlQuery query(m_database);
    query.prepare("SELECT COUNT(*) FROM operators WHERE mcc = :mcc");
    query.bindValue(":mcc", QString::number(mcc));
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

QString SqliteOMDataProvider::getOperatorName(int countryIdx, int operatorIdx)
{
    if (!m_isValid) {
        return {};
    }

    int mcc = getMccForCountryIdx(countryIdx);
    if (mcc == 0) {
        return {};
    }

    QSqlQuery query(m_database);
    query.prepare("SELECT name FROM operators WHERE mcc = :mcc ORDER BY name LIMIT 1 OFFSET :offset");
    query.bindValue(":mcc", QString::number(mcc));
    query.bindValue(":offset", operatorIdx);
    query.exec();
    if (query.next()) {
        return query.value(0).toString();
    }
    return {};
}

int SqliteOMDataProvider::getOperatorMnc(int countryIdx, int operatorIdx)
{
    if (!m_isValid) {
        return 0;
    }

    int mcc = getMccForCountryIdx(countryIdx);
    if (mcc == 0) {
        return 0;
    }

    QSqlQuery query(m_database);
    query.prepare("SELECT mnc FROM operators WHERE mcc = :mcc ORDER BY name LIMIT 1 OFFSET :offset");
    query.bindValue(":mcc", QString::number(mcc));
    query.bindValue(":offset", operatorIdx);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

int SqliteOMDataProvider::getMccForCountryIdx(int countryIdx) const
{
    if (!m_isValid) {
        return 0;
    }

    QSqlQuery query(m_database);
    query.prepare("SELECT mcc FROM countries ORDER BY name LIMIT 1 OFFSET :offset");
    query.bindValue(":offset", countryIdx);
    query.exec();
    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

