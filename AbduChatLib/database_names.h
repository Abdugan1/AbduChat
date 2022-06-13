#ifndef DATABASE_NAMES_H
#define DATABASE_NAMES_H

namespace db {

//--------contacts--------
    namespace contacts {

        extern const char* TableName;


        namespace fieldnames {

            extern const char* Id;
            extern const char* Username;
            extern const char* InsertDatetime;

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

    extern const char* TableName;


    namespace fieldnames {

        extern const char* MessageId;

        extern const char* FromUserId;

        extern const char* ToUserId;

        extern const char* Text;

        extern const char* SentDatetime;

    } // fieldnames


    namespace fieldnums {

        enum FieldNums {
            MessageId,
            FromUserId,
            ToUserId,
            Text,
            SentDatetime
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
            extern const char* InsertDatetime;

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

        extern const char* TableName;

        namespace fieldnames {

            extern const char* Id;
            extern const char* Username;
            extern const char* Password;
            extern const char* InsertDatetime;

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
