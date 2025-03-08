#include "datamanager.h"
#include <QDebug>
#include <QSqlError>

DataManager &DataManager::instance()
{
    static DataManager instance;
    return instance;
}

void DataManager::closeDataBase()
{
    if(db.open()){
        db.close();
    }
}

bool DataManager::openDataBase(const QString &dbpath)
{
    db.setDatabaseName(dbpath);
    if(!db.open()){
        qDebug() << "无法打开数据库" ;
        return false;
    }
    return true;
}

QString DataManager::getDatabasePath() const
{
    return dbPath;
}

void DataManager::setDatabasePath(const QString &path)
{
    if(path!=dbPath){
        closeDataBase();
        dbPath = path;
        openDataBase(dbPath);
    }
}

DataManager::DataManager(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    openDataBase(dbPath);
}

DataManager::~DataManager(){
    if(db.open()){
        closeDataBase();
    }
}
