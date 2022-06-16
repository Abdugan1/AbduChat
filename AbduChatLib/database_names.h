#ifndef DATABASE_NAMES_H
#define DATABASE_NAMES_H

namespace db {

//--------users--------
    namespace users {

        extern const char* TableName;


        namespace fieldnames {

            extern const char* Id;
            extern const char* FirstName;
            extern const char* LastName;
            extern const char* Username;
            extern const char* Date;

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
        extern const char* TableName;

        namespace fieldnames {
            extern const char* Id;
            extern const char* Type;
            extern const char* Username;
            extern const char* Date;
        } // fieldnames

        namespace fieldnums {
            enum FieldNums {
                Id,
                Type,
                Username,
                Date,
            };
        } // fieldnums


    } // chats
//--------!chats--------


//--------chat_participants--------
    namespace chat_participants {
        extern const char* TableName;

        namespace fieldnames {
            extern const char* Id;
            extern const char* ChatId;
            extern const char* UserId;
            extern const char* Date;
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


//--------messages--------
    namespace messages {

    extern const char* TableName;


    namespace fieldnames {

        extern const char* Id;
        extern const char* FromUserId;
        extern const char* ChatId;
        extern const char* Text;
        extern const char* Date;

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
        extern const char* TableName;

        namespace fieldnames {

            extern const char* Id;
            extern const char* Text;
            extern const char* Date;

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

        extern const char* TableName;

        namespace fieldnames {

            extern const char* Id;
            extern const char* Username;
            extern const char* Password;

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
