#ifndef SERVERLOGSTABLE_H
#define SERVERLOGSTABLE_H

#include <QSqlTableModel>

class ServerLogsTable : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit ServerLogsTable(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

public slots:
    void insertLog(const QString& text, const QString& insertDatetime);

private:
    void createTable();
};

#endif // SERVERLOGSTABLE_H
