#ifndef REQUEST_AND_REPLY_CONSTANTS_H
#define REQUEST_AND_REPLY_CONSTANTS_H

namespace request {

namespace types {

const char* Login = "login";
const char* Register = "register";
const char* SendMessage = "send_message";

} // types

namespace headers {

const char* Type = "type";
const char* FromUser = "from_user";
const char* ToUser = "to_user";
const char* Text = "text";
const char* SentDatetime = "sent_datetime";

const char* Username = "username";
const char* Password = "password";

} // headers

} // requqest


namespace reply {

namespace types {

const char* Login = "login";
const char* Register = "register";
const char* Message = "message";
const char* NewUser = "new_user";
const char* UserList = "user_list";

} // types

namespace headers {

const char* Type = "type";
const char* MessageId = "message_id";
const char* FromUser = "from_user";
const char* ToUser = "to_user";
const char* Text = "text";
const char* SentDatetime = "sent_datetime";

const char* Success = "success";
const char* Reason = "reason";

const char* Username = "username";

const char* Users = "users";

} // headers

} // reply

#endif // REQUEST_AND_REPLY_CONSTANTS_H
