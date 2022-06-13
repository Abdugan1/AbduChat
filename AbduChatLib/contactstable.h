#ifndef CONTACTSTABLE_H
#define CONTACTSTABLE_H

#include <QSqlTableModel>

class ContactsTable : public QSqlTableModel
{
    Q_OBJECT
    Q_PROPERTY(int myId READ myId WRITE setMyId NOTIFY myIdChanged)
public:
    explicit ContactsTable(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    int myId() const;
    void setMyId(int newMyId);

public slots:
    void insertContacts(const QJsonArray& contacts);
    void insertContact(const QString& username, const QString& insertDatetime);

signals:
    void myIdChanged();

private:
    void createTable();

private:
    int myId_ = -1;
};

#endif // CONTACTSTABLE_H
