#ifndef CONTACTSTABLE_H
#define CONTACTSTABLE_H

#include <QSqlTableModel>

class ContactsTable : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit ContactsTable(QObject* parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void insertUsername(const QString& username);

private:
    void createTable();
};

#endif // CONTACTSTABLE_H
