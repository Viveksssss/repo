#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DataManager : public QObject
{
    Q_OBJECT
public:
    static DataManager& instance();
    void closeDataBase();
    bool openDataBase(const QString& dbpath);
    QString getDatabasePath()const;
    void setDatabasePath(const QString&path);
    ~DataManager();

private:
    explicit DataManager(QObject *parent = nullptr);
    QSqlDatabase db;
    QString dbPath= "/home/vivek/Depends/sqlitedb/test.db";

signals:
};


#endif // DATAMANAGER_H
