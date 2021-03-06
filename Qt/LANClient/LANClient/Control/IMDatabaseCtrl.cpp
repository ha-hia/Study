#include "IMDatabaseCtrl.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <qdebug.h>
#include <QSqlError>
#include "Control/IMClientFileCtrl.h"

/************************message************************/
static const QString INSERT_MESSAGE_IN_HISTORYMESSAGE =
        "insert into ##HISTORY##MESSAGE## (senderID, receiverID, content, dateTime) "
        "values(?, ?, ?, ?);";
static const QString SEARCH_MESSAGE_IN_HISTORYMESSAGE =
        "select * from ##HISTORY##MESSAGE## where ( (senderID = ? and receiverID = ?) "
        "or (senderID = ? and receiverID = ?) )and dateTime >=? and dateTime < ?;";
static const QString EXPORT_ONE_MESSAGE_IN_HISTORY =
        "select * from ##HISTORY##MESSAGE## where (senderID = ? and receiverID = ?) or "
        "(senderID = ? and receiverID = ?) into outfile ? "
        "fields terminated by ',' optionally enclosed by '\"' escaped by '\"'"
        "lines terminated by '\\r\\n';";

static const QString EXPORT_ALL_MESSAGE_IN_HISTORY =
        "select * from ##HISTORY##MESSAGE## where senderID = ? or receiverID = ? "
        "into outfile ? "
        "fields terminated by ',' optionally enclosed by '\"' escaped by '\"'"
        "lines terminated by '\\r\\n';";

static const QString DELETE_ONE_MESSAGE_IN_HISTORY =
        "delete from ##HISTORY##MESSAGE## where (senderID = ? and receiverID = ?) "
        "or (senderID = ? and receiverID = ?)";
static const QString DELETE_ALL_MESSAGE_IN_HISTORY =
        "delete from ##HISTORY##MESSAGE## where senderID = ? or receiverID = ? ";

/********************create tables********************/
static const QString CREATE_TABLE_HISTORYMESSAGE_SQL =
"create table if not exists ##HISTORY##MESSAGE## "
"("
"messageID int(11) NOT nullptr AUTO_INCREMENT PRIMARY KEY, "
"senderID varchar(15) NOT nullptr, "
"receiverID varchar(15) NOT nullptr, "
"content varchar(1000) NOT nullptr DEFAULT '', "
"dateTime datetime NOT nullptr "
")ENGINE=InnoDB DEFAULT CHARSET=utf8;";

IMDatabaseCtrl::IMDatabaseCtrl(const QString myID, QObject *parent) :
    QObject(parent), m_myID(myID)
{
    m_localHistoryTableName = "HistoryMessage";
    m_localHistoryTableName.append(m_myID);

    m_db = new QSqlDatabase;
    createConnection();
    createTable();
    close();
}

IMDatabaseCtrl::IMDatabaseCtrl(QObject *parent) : QObject(parent)
{
//    m_myID(myID) ????????????
    m_localHistoryTableName = "HistoryMessage";
    m_localHistoryTableName.append(m_myID);

    m_db = new QSqlDatabase;
    createConnection();
    createTable();
    close();
}

IMDatabaseCtrl::~IMDatabaseCtrl()
{
    if (m_db != nullptr)
    {
        if (m_db->isOpen())
            m_db->close();
        delete m_db;
        m_db = nullptr;
    }
}

void IMDatabaseCtrl::setDatabseStrID(const QString& myID)
{
    m_myID = myID;
}

/*************************************************
Function Name??? createConnection()
Description: ????????????
*************************************************/
bool IMDatabaseCtrl::createConnection()
{
    if (m_db == nullptr)
        m_db = new QSqlDatabase;
    if (m_db->isOpen())
    {
        return true;
    }
    // ??????????????????
    if (QSqlDatabase::contains("clientIMDB"))
    {
        *m_db = QSqlDatabase::database("clientIMDB");
    }
    else
    {// ????????????????????????
        *m_db = QSqlDatabase::addDatabase("QMYSQL", "clientIMDB");
        m_db->setDatabaseName("clientIMDB");
    }

    m_db->setUserName("root");
    m_db->setPassword("123456");
    m_db->setHostName(QLatin1String("localhost"));
    if (!m_db->open())
    {
        return false;
    }
    return true;
}


/*************************************************
Function Name??? close()
Description: ???????????????
*************************************************/
void IMDatabaseCtrl::close()
{
    if (m_db != nullptr && m_db->isOpen())
        m_db->close();
}


/*************************************************
Function Name??? isOpen()
Description: ???????????????
*************************************************/
bool IMDatabaseCtrl::isOpen()
{
    return (m_db->isOpen());

}

/*************************************************
Function Name??? addHistoryMessage()
Description: ??????????????????
*************************************************/
bool IMDatabaseCtrl::addHistoryMessage(const TalkMessage & mes)
{
    if (!createConnection())
    {
        return false;
    }
    //sql ??????
    QSqlDatabase::database().transaction();

    QString queryStr = INSERT_MESSAGE_IN_HISTORYMESSAGE;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
//    QString str =
//            "insert into HistoryMessage2014050701 (senderID, receiverID, content, dateTime) "
//            "values(?, ?, ?, ?);";

    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    qDebug() << "my sql:" << str;
//    query.prepare(INSERT_MESSAGE_IN_HISTORYMESSAGE);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(mes.m_senderID);
    query.addBindValue(mes.m_receiverID);
    query.addBindValue(IMClientFileCtrl::simplifyRichText(mes.m_text));
    query.addBindValue(mes.m_dateTime);

    query.exec();

    errorSQLOrder(query, "inser-mes-to-HistoryMmesage");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    if (0 >= query.numRowsAffected())
    {
        return false;
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}

/*************************************************
Function Name??? searchHistoryMessage()
Description: ???????????????????????????
*************************************************/
bool IMDatabaseCtrl::searchHistoryMessage(const QString & myID, const QString & friendID,
                                          const QDate & date, QVector<TalkMessage> & mesVec)
{
    if (!createConnection())
    {
        return false;
    }
    //sql ??????
    QSqlDatabase::database().transaction();

    QString queryStr = SEARCH_MESSAGE_IN_HISTORYMESSAGE;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.prepare(SEARCH_MESSAGE_IN_HISTORYMESSAGE);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.addBindValue(date);//.toString("yyyy-MM-dd"));
    query.addBindValue(date.addDays(1));//.addDays(1).toString("yyyy-MM-dd"));

    query.exec();

    errorSQLOrder(query, "search-mes-in-HistoryMmesage");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return false;
    }

    TalkMessage mes;
    while (query.next())
    {
        mes.m_senderID = query.value(1).toString();
        mes.m_receiverID = query.value(2).toString();
        mes.m_text = query.value(3).toString();
        mes.m_dateTime = query.value(4).toDateTime();
        mesVec.push_back(mes);
    }

    QSqlDatabase::database().commit();

//    m_db->close();
    return true;
}


/*************************************************
Function Name??? searchHistoryMessage()
Description: ????????????????????????
*************************************************/
int IMDatabaseCtrl::exportHistoryMessageOneFriend(const QString &myID ,
                                                  const QString &friendID,
                                                  const QString &name)
{
    if (!createConnection())
    {
        return -1;
    }
    //sql ??????
//    QSqlDatabase::database().transaction();

    QString queryStr = EXPORT_ONE_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);

//    QString exportMessage = "select * from HistoryMessage into outfile ";
//    exportMessage.append("'/tmp/local_history_message").append(name).append(".xls';");
//    QString na = "/tmp/local_history_message5.xls";
//    static int i =100;
//    exportMessage.append("'/tmp/local_history_message").
//            append(QString::number(i++)).append(".xls';");
//    query.exec(exportMessage);
//    query.prepare();

//    query.prepare(EXPORT_ONE_MESSAGE_IN_HISTORY);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);
    query.addBindValue(name);

    query.exec();

    errorSQLOrder(query, "exportl-one-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}

/*************************************************
Function Name??? exportHistoryMessageAll()
Description: ????????????????????????
*************************************************/
int IMDatabaseCtrl::exportHistoryMessageAll(const QString &myID,
                                            const QString &fileName)
{
    if (!createConnection())
    {
        return -1;
    }

    QString queryStr = EXPORT_ALL_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.prepare(EXPORT_ALL_MESSAGE_IN_HISTORY);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(myID);
    query.addBindValue(fileName);

    query.exec();

    errorSQLOrder(query, "exportl-all-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}

/*************************************************
Function Name??? deleteHistoryMessageOneFriend()
Description: ??????????????????????????????
*************************************************/
int IMDatabaseCtrl::deleteHistoryMessageOneFriend(const QString myID,
                                                  const QString friendID)
{
    if (!createConnection())
    {
        return -1;
    }
    //sql ??????
//    QSqlDatabase::database().transaction();

    QString queryStr = DELETE_ONE_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.prepare(DELETE_ONE_MESSAGE_IN_HISTORY);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(friendID);
    query.addBindValue(friendID);
    query.addBindValue(myID);


    query.exec();

    errorSQLOrder(query, "delete-one-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}

/*************************************************
Function Name??? deleteHistoryMessageAll()
Description: ??????????????????????????????
*************************************************/
int IMDatabaseCtrl::deleteHistoryMessageAll(const QString myID)
{
    if (!createConnection())
    {
        return -1;
    }
    //sql ??????
//    QSqlDatabase::database().transaction();

    QString queryStr = DELETE_ALL_MESSAGE_IN_HISTORY;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
    query.prepare(queryStr);
//    query.addBindValue(m_localHistoryTableName);
    query.addBindValue(myID);
    query.addBindValue(myID);
    query.exec();

    errorSQLOrder(query, "delete-all-message");
    if (!query.isActive())
    {
        qDebug() << "QUERY_FAIL::" << query.lastError().text();
        m_db->close();
        return -1;
    }

    if (0 >= query.numRowsAffected())
    {
//        m_db->close();
        return 0;
    }

//    QSqlDatabase::database().commit();

//    m_db->close();
    return 1;
}



// mark: private----------------------------------------------------

/*************************************************
Function Name??? errorSQLOrder()
Description: ??????SQL??????????????????
*************************************************/
void IMDatabaseCtrl::errorSQLOrder(QSqlQuery query, QString mark)
{
    //??????SQL????????????????????????????????????
    if(!query.isActive())
    {
        QString str = query.lastError().text() + "\n" + mark;
        //QMessageBox::warning(nullptr, "ERROR", str);
        qDebug() << "Mysql qurey error: " << str;
        qDebug() << "query text:" << query.lastQuery();
    }
}

/*************************************************
Function Name??? createTable()
Description: ?????????????????????
*************************************************/
void IMDatabaseCtrl::createTable()
{
//    QString createHis =
//    "create table if not exists ";
//    createHis.append(m_localHistoryTableName).append(
//    " ("
//    "messageID int(11) NOT nullptr AUTO_INCREMENT PRIMARY KEY, "
//    "senderID varchar(15) NOT nullptr, "
//    "receiverID varchar(15) NOT nullptr, "
//    "content varchar(1000) NOT nullptr DEFAULT '', "
//    "dateTime datetime NOT nullptr "
//    ")ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    QString queryStr = CREATE_TABLE_HISTORYMESSAGE_SQL;
    queryStr.replace("##HISTORY##MESSAGE##", m_localHistoryTableName);
    QSqlQuery query(*m_db);
//    query.prepare(CREATE_TABLE_HISTORYMESSAGE_SQL);
//    query.addBindValue(queryStr);
    query.exec(queryStr);
    errorSQLOrder(query, "createTable-historymessage");
}
