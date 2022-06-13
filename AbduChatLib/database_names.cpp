#include "database_names.h"

namespace db {

//--------contacts--------
    namespace contacts {

        const char* TableName = "contacts";


        namespace fieldnames {

            const char* Id = "id";
            const char* Username = "username";
            const char* InsertDatetime = "insert_datetime";

        } // fieldnames

    } // contacts
//--------!contacts--------

//--------messages--------
    namespace messages {

    const char* TableName = "messages";


    namespace fieldnames {

        const char* MessageId = "id";

        const char* FromUserId = "from_user_id";

        const char* ToUserId = "to_user_id";

        const char* Text = "text";

        const char* SentDatetime = "sent_datetime";

    } // fieldnames

    } // messages
//--------!messages--------

//--------server_logs--------
    namespace server_logs {
        const char* TableName = "server_logs";

        namespace fieldnames {

            const char* Id = "id";
            const char* Text = "text";
            const char* InsertDatetime = "insert_datetime";

        } // fieldnames
    }
//--------!server_logs--------

//--------users--------
    namespace users {

        const char* TableName = "users";

        namespace fieldnames {

            const char* Id = "id";
            const char* Username = "username";
            const char* Password = "password";
            const char* InsertDatetime = "insert_datetime";

        } // fieldnames

    }
//--------!users--------

} // db
