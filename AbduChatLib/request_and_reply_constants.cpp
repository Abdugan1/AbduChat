#include "request_and_reply_constants.h"

namespace request {

namespace types {

const char* Login = "login";
const char* Register = "register";
const char* SendMessage = "send_message";

// synchronize
const char* SynchronizeContacts = "synchronize_contacts";
const char* SynchronizeMessages = "synchronize_messages";

} // types

namespace headers {

const char* Type = "type";
const char* FromUserId = "from_user_id";
const char* ToUserId = "to_user_id";
const char* Text = "text";
const char* SentDatetime = "sent_datetime";

const char* Username = "username";
const char* Password = "password";

const char* InsertDatetime = "insert_datetime";

} // headers

namespace values {

const char* AllData = "ALL_DATA";

} // values

} // requqest


namespace reply {

namespace types {

const char* Login = "login";
const char* Register = "register";
const char* Message = "message";
const char* NewUser = "new_user";
const char* UserDisconnected = "user_disconnected";
const char* UserList = "user_list";
const char* MessageList = "message_list";

} // types

namespace headers {

const char* Type = "type";
const char* Id = "id";
const char* FromUserId = "from_user_id";
const char* ToUserId = "to_user_id";
const char* Text = "text";
const char* SentDatetime = "sent_datetime";

const char* Success = "success";
const char* Reason = "reason";

const char* Username = "username";

const char* Users = "users";
const char* Messages = "messages";

const char* InsertDatetime = "insert_datetime";

} // headers

namespace values {

const char* AllData = "ALL_DATA";

} // values

} // reply
