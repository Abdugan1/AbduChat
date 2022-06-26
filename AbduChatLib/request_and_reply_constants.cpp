#include "request_and_reply_constants.h"

namespace request {

namespace types {

const char* Login = "login";
const char* Register = "register";
const char* SendMessage = "send_message";
const char* CreateChat = "create_chat";

// synchronize
const char* SynchronizeUsers = "synchronize_users";
const char* SynchronizeMessages = "synchronize_messages";

} // types

namespace headers {

const char* Type = "type";
const char* FromUserId = "from_user_id";
const char* ToUserId = "to_user_id";
const char* Text = "text";
const char* Date = "sent_datetime";

const char* RegisterInfo = "register_info";
const char* Username = "username";
const char* Password = "password";

const char* Chat = "chat";
const char* Message = "message";

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
const char* ChatAdd = "chat_add";

} // types

namespace headers {

const char* Type = "type";

const char* Success = "success";
const char* Reason = "reason";

const char* Username = "username";

const char* User = "user";
const char* Users = "users";

const char* Chat = "chat";

const char* Message = "message";
const char* Messages = "messages";

const char* Date = "date";

} // headers

namespace values {

const char* LoginFailed = "Login failed";
const char* UsernameIsUsed = "The username is already in use";

} // values

} // reply


namespace user {

namespace headers {

const char* Id = "id";
const char* FirstName = "first_name";
const char* LastName = "last_name";
const char* Username = "username";
const char* Date = "date";

} // headers

} // user


namespace chat {

namespace headers {

const char* Id = "id";
const char* Type = "type";
const char* User1Id = "user_1_id";
const char* User2Id = "user_2_id";
const char* Date = "date";

} // headers

namespace values {

const char* Private = "private";

} // values

} // chat


namespace message {

namespace headers {

const char* Id = "id";
const char* From = "from";
const char* Chat = "chat";
const char* Text = "text";
const char* Date = "date";

} // headers

} // message
