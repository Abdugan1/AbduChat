#include "database_names.h"

namespace db {

    namespace users {
        const char* TableName = "contacts";

        namespace fieldnames {
            const char* Id = "id";
            const char* FirstName = "first_name";
            const char* LastName = "last_name";
            const char* Username = "username";
            const char* Date = "date";
        } // fieldnames

    } // contacts

    namespace chats {
        extern const char* TableName;

        namespace fieldnames {
            const char* Id = "id";
            const char* Type = "type";
            const char* Username = "username";
            const char* Date = "date";
        } // fieldnames


    } // chats

    namespace chat_participants {
        extern const char* TableName;

        namespace fieldnames {
            const char* Id = "id";
            const char* ChatId = "chat_id";
            const char* UserId = "user_id";
            const char* Date = "date";
        } // fieldnames

    } // chat_participants

    namespace messages {
        const char* TableName = "messages";

        namespace fieldnames {
            const char* Id = "id";
            const char* FromUserId = "from_user_id";
            const char* ChatId = "chat_id";
            const char* Text = "text";
            const char* Date = "date";
        } // fieldnames

    } // messages

    namespace server_logs {
        const char* TableName = "server_logs";

        namespace fieldnames {
            const char* Id = "id";
            const char* Text = "text";
            const char* Date = "date";
        } // fieldnames
    } // server_logs

    namespace users_server {

        const char* TableName = "users";

        namespace fieldnames {

            const char* Id = "id";
            const char* Username = "username";
            const char* Password = "password";

        } // fieldnames

    } // users_server

} // db
