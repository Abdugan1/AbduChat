#ifndef DATABASE_NAMES_H
#define DATABASE_NAMES_H

#include <QString>
class QVariant;
class QModelIndex;

QVariant getData(const QModelIndex& index, int role);

namespace db {

//--------users--------
    namespace users {

        extern const QString TableName;


        namespace fieldnames {

            extern const QString Id;
            extern const QString FirstName;
            extern const QString LastName;
            extern const QString Username;
            extern const QString Date;

        } // fieldnames


        namespace fieldnums {

            enum FieldNums {
                Id,
                FirstName,
                LastName,
                Username,
                Date,
            };

        } // fieldnums

    } // users
//--------!users--------


//--------chats--------
    namespace chats {
        extern const QString TableName;

        namespace fieldnames {
            extern const QString Id;
            extern const QString Type;
            extern const QString User1Id;
            extern const QString User2Id;
            extern const QString Date;
        } // fieldnames

        namespace fieldnums {
            enum FieldNums {
                Id,
                Type,
                User1Id,
                User2Id,
                Date,
            };
        } // fieldnums


    } // chats
//--------!chats--------


//--------chat_participants--------
    namespace chat_participants {
        extern const QString TableName;

        namespace fieldnames {
            extern const QString Id;
            extern const QString ChatId;
            extern const QString UserId;
            extern const QString Date;
        } // fieldnames

        namespace fieldnums {
            enum FieldNums {
                Id,
                ChatId,
                UserId,
                Date,
            };
        }

    } // chat_participants
//--------!chat_participants--------

//--------chats_view--------
    namespace chats_view {
    extern const QString ViewName;

    namespace fieldnames {
        extern const QString ChatId;
        extern const QString ChatType;
        extern const QString User1Id;
        extern const QString User2Id;
        extern const QString LastMessage;
        extern const QString FromUser;
        extern const QString Date;
        extern const QString User1Username;
        extern const QString User2Username;
    } // fieldnames

    namespace fieldnums {
        enum FieldNums {
            ChatId,
            ChatType,
            User1Id,
            User2Id,
            LastMessage,
            FromUser,
            Date,
            User1Username,
            User2Username,
        };
    } // fieldnums

    } // chats_view
//--------!chats_view--------


//--------messages--------
    namespace messages {

    extern const QString TableName;


    namespace fieldnames {

        extern const QString Id;
        extern const QString FromUserId;
        extern const QString ChatId;
        extern const QString Text;
        extern const QString Date;

    } // fieldnames


    namespace fieldnums {

        enum FieldNums {
            Id,
            FromUserId,
            ChatId,
            Text,
            Date
        };

    } // fieldnums

    } // messages
//--------!messages--------

//--------server_logs--------
    namespace server_logs {
        extern const QString TableName;

        namespace fieldnames {

            extern const QString Id;
            extern const QString Text;
            extern const QString Date;

        } // fieldnames


        namespace fieldnums {

            enum FieldNums {
                Id,
                Text,
                Date
            };

        } // fieldnums
    }
//--------!server_logs--------

//--------users_server--------
    namespace users_server {

        extern const QString TableName;

        namespace fieldnames {

            extern const QString Id;
            extern const QString Username;
            extern const QString Password;

        } // fieldnames


        namespace fieldnums {

            enum FieldNums {
                Id,
                Username,
                Password,
            };

        } // fieldnums

    }
//--------!users_server--------

} // db

#endif // DATABASE_NAMES_H
