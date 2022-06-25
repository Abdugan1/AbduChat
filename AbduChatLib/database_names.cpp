#include "database_names.h"

namespace db {

    namespace users {
        const QString TableName = "users";

        namespace fieldnames {
            const QString Id = "id";
            const QString FirstName = "first_name";
            const QString LastName = "last_name";
            const QString Username = "username";
            const QString Date = "date";
        } // fieldnames

    } // contacts

    namespace chats {
        const QString TableName = "chats";

        namespace fieldnames {
            const QString Id = "id";
            const QString Type = "type";
            const QString User1Id = "user_1_id";
            const QString User2Id = "user_2_id";
            const QString Date = "date";
        } // fieldnames


    } // chats

    namespace chat_participants {
        const QString TableName = "chat_participants";

        namespace fieldnames {
            const QString Id = "id";
            const QString ChatId = "chat_id";
            const QString UserId = "user_id";
            const QString Date = "date";
        } // fieldnames

    } // chat_participants

    namespace chats_view {
    const QString ViewName = "chats_view";

    namespace fieldnames {
        const QString ChatId = "chat_id";
        const QString ChatType = "chat_type";
        const QString User1Id = "user_1_id";
        const QString User2Id = "user_2_id";
        const QString LastMessage = "last_message";
        const QString FromUser = "from_user";
        const QString Date = "date";
        const QString User1Username = "user_1_username";
        const QString User2Username = "user_2_username";
    } // fieldnames

    } // chats_view

    namespace messages {
        const QString TableName = "messages";

        namespace fieldnames {
            const QString Id = "id";
            const QString FromUserId = "from_user_id";
            const QString ChatId = "chat_id";
            const QString Text = "text";
            const QString Date = "date";
        } // fieldnames

    } // messages

    namespace server_logs {
        const QString TableName = "server_logs";

        namespace fieldnames {
            const QString Id = "id";
            const QString Text = "text";
            const QString Date = "date";
        } // fieldnames

    } // server_logs

    namespace users_server {

        const QString TableName = "users_server";

        namespace fieldnames {

            const QString Id = "id";
            const QString Username = "username";
            const QString Password = "password";

        } // fieldnames

    } // users_server

} // db
