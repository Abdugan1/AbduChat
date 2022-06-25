#ifndef REQUEST_AND_REPLY_CONSTANTS_H
#define REQUEST_AND_REPLY_CONSTANTS_H

namespace request {

namespace types {

extern const char* Login;
extern const char* Register;
extern const char* SendMessage;
extern const char* CreateChat;

// synchronize
extern const char* SynchronizeUsers;
extern const char* SynchronizeMessages;

} // types

namespace headers {

extern const char* Type;
extern const char* FromUserId;
extern const char* ToUserId;
extern const char* Text;
extern const char* Date;

extern const char* RegisterInfo;
extern const char* Username;
extern const char* Password;

extern const char* Chat;

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
extern const char* ChatAdd;

} // types

namespace headers {

extern const char* Type;

extern const char* Success;
extern const char* Reason;

extern const char* Username;

extern const char* User;
extern const char* Users;

extern const char* Chat;

extern const char* Message;
extern const char* Messages;

extern const char* Date;

} // headers

namespace values {

extern const char* LoginFailed;
extern const char* UsernameIsUsed;

} // values

} // reply


namespace user {

namespace headers {

extern const char* Id;
extern const char* FirstName;
extern const char* LastName;
extern const char* Username;
extern const char* Date;

} // headers

} // user


namespace chat {

namespace headers {

extern const char* Id;
extern const char* Type;
extern const char* User1Id;
extern const char* User2Id;
extern const char* Date;

} // headers

namespace values {

extern const char* Private;

} // values

} // chat


namespace message {

namespace headers {

extern const char* Id;
extern const char* From;
extern const char* Chat;
extern const char* Text;
extern const char* Date;

} // headers

} // message

#endif // REQUEST_AND_REPLY_CONSTANTS_H
