#ifndef DATABASE_NAMES_H
#define DATABASE_NAMES_H

namespace db {

//--------contacts--------
    namespace contacts {

        static const char* TableName = "contacts";


        namespace fieldnames {

            static const char* Id = "id";
            static const char* Username = "username";
            static const char* InsertDatetime = "insert_datetime";

        } // fieldnames


        namespace fieldnums {

            enum FieldNums {
                Id,
                Username,
                InsertDatetime
            };

        } // fieldnums

    } // contacts
//--------!contacts--------

//--------messages--------
    namespace messages {

    static const char* TableName = "messages";


    namespace fieldnames {

        static const char* MessageId = "id";

        static const char* FromUser = "from_user";

        static const char* ToUser = "to_user";

        static const char* Text = "text";

        static const char* SentDatetime = "sent_datetime";

    } // fieldnames


    namespace fieldnums {

        enum FieldNums {
            MessageId,
            FromUser,
            ToUser,
            Text,
            SentDatetime
        };

    } // fieldnums

    } // messages
//--------!messages--------

//--------server_logs--------
    namespace server_logs {
        static const char* TableName = "server_logs";

        namespace fieldnames {

            static const char* Id = "id";
            static const char* Text = "text";
            static const char* InsertDatetime = "insert_datetime";

        } // fieldnames


        namespace fieldnums {

            enum FieldNums {
                Id,
                Text,
                InsertDatetime
            };

        } // fieldnums
    }
//--------!server_logs--------

//--------users--------
    namespace users {

        static const char* TableName = "users";

        namespace fieldnames {

            static const char* Id = "id";
            static const char* Username = "username";
            static const char* Password = "password";
            static const char* InsertDatetime = "insert_datetime";

        } // fieldnames


        namespace fieldnums {

            enum FieldNums {
                Id,
                Username,
                Password,
                InsertDatetime
            };

        } // fieldnums

    }
//--------!users--------

} // db

#endif // DATABASE_NAMES_H
