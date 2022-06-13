#ifndef REQUEST_AND_REPLY_CONSTANTS_H
#define REQUEST_AND_REPLY_CONSTANTS_H

namespace request {

namespace types {

extern const char* Login;
extern const char* Register;
extern const char* SendMessage;

// synchronize
extern const char* SynchronizeContacts;
extern const char* SynchronizeMessages;

} // types

namespace headers {

extern const char* Type;
extern const char* FromUserId;
extern const char* ToUserId;
extern const char* Text;
extern const char* SentDatetime;

extern const char* Username;
extern const char* Password;

extern const char* InsertDatetime;

} // headers

namespace values {

extern const char* AllData;

} // values

} // requqest


namespace reply {

namespace types {

extern const char* Login;
extern const char* Register;
extern const char* Message;
extern const char* NewUser;
extern const char* UserDisconnected;
extern const char* UserList;
extern const char* MessageList;

} // types

namespace headers {

extern const char* Type;
extern const char* Id;
extern const char* FromUserId;
extern const char* ToUserId;
extern const char* Text;
extern const char* SentDatetime;

extern const char* Success;
extern const char* Reason;

extern const char* Username;

extern const char* Users;
extern const char* Messages;

extern const char* InsertDatetime;

} // headers

namespace values {

extern const char* AllData;

} // values

} // reply

#endif // REQUEST_AND_REPLY_CONSTANTS_H
