#include "Server.h"

using namespace CryptoPP;

extern SHA256 hash;

Server::Server() :
	_DB_users_read("DB_users.txt", std::ios_base::in | std::ios_base::binary),
	_DB_messages_read("DB_messages.txt", std::ios_base::in | std::ios_base::binary)
{
	//_DB_users_write("_DB_users.txt", std::ios_base::app | std::ios_base::binary)
	//DBEntry entry;
	//std::string hashed_password;
	//
	//StringSource("0", true,
	//	new HashFilter(hash,
	//		new StringSink(hashed_password)));
	//entry.permissions = Permissions::Admin;
	//strncpy(entry.username, "admin", username_lenght);
	//strncpy(entry.password, hashed_password.c_str(), password_lenght);
	//_DB_users_write.write(reinterpret_cast<const char*>(&entry), sizeof(DBEntry));
	//
	//StringSource("1", true,
	//	new HashFilter(hash,
	//		new StringSink(hashed_password)));
	//entry.permissions = Permissions::Read;
	//strncpy(entry.username, "user1", username_lenght);
	//strncpy(entry.password, hashed_password.c_str(), password_lenght);
	//_DB_users_write.write(reinterpret_cast<const char*>(&entry), sizeof(DBEntry));
}

Server::ActiveUser::ActiveUser(const char* new_username, const char* new_cookie)
{
	strncpy(username, new_username, username_lenght);
	strncpy(cookie, new_cookie, cookie_lenght);
}

uint16_t Server::authentication
(
	const char* username,
	const char* password,
	const char* cookie
)
{
	DBEntry entry = find_username(username);

	if (strnlen(entry.username, username_lenght) == 0)
		return Permissions::None;

	if (strncmp(entry.password, password, password_lenght) != 0)
		return Permissions::None;

	std::string hashed_username;
	StringSource(entry.username, true,
		new HashFilter(hash,
			new StringSink(hashed_username)));

	xorbuf(
		(byte*)cookie,
		(byte*)hashed_username.c_str(),
		(byte*)entry.password,
		cookie_lenght
	);

	if (_active_users.end() == std::find_if
	(
			_active_users.begin(),
			_active_users.end(),
			[ &cookie ] (const ActiveUser& user)
			{
				return strncmp(user.cookie, cookie, cookie_lenght) == 0;
			}
	))
		_active_users.emplace_back(ActiveUser(entry.username, cookie));

	return entry.permissions;
}

char* Server::get_all_messages
(
	int& lenght,
	const char* cookie
)
{
	char* ptr_messages = nullptr;

	auto user = std::find_if
	(
		_active_users.begin(),
		_active_users.end(),
		[&cookie](const ActiveUser& user)
		{
			return strncmp(user.cookie, cookie, cookie_lenght) == 0;
		}
	);
	
	if (user == _active_users.end() ||
		!(find_username(user->username).permissions & Permissions::Read)
		)
		return 0;

	std::stringstream messages_buffer;
	_DB_messages_read.clear();
	_DB_messages_read.seekg(0);

	messages_buffer << _DB_messages_read.rdbuf();

	const std::string& messages_string = messages_buffer.str();
	lenght = static_cast<int>(messages_string.size() + 1);

	ptr_messages = new char[lenght];

	memcpy((void*)ptr_messages, messages_string.c_str(), lenght);

	return ptr_messages;
}

bool Server::add_message
(
	const char* message,
	int lenght,
	const char* cookie
)
{
	auto user = std::find_if
	(
		_active_users.begin(),
		_active_users.end(),
		[&cookie](const ActiveUser& user)
		{
			return strncmp(user.cookie, cookie, cookie_lenght) == 0;
		}
	);

	if (user == _active_users.end() ||
		!(find_username(user->username).permissions & Permissions::Write)
		)
		return false;


	std::ofstream DB_messages_write("DB_messages.txt", std::ios_base::app | std::ios_base::binary);

	DB_messages_write.write(
		user->username,
		strnlen(
			user->username,
			username_lenght
		)
	);

	DB_messages_write.write(": ", 2);

	DB_messages_write.write(
		message,
		lenght
	);

	DB_messages_write.write("\r\n", 2);
	DB_messages_write.close();

	return true;
}

bool Server::delete_all_messages
(
	const char* cookie
)
{
	auto user = std::find_if
	(
		_active_users.begin(),
		_active_users.end(),
		[&cookie](const ActiveUser& user)
		{
			return strncmp(user.cookie, cookie, cookie_lenght) == 0;
		}
	);

	if (user == _active_users.end() ||
		!(find_username(user->username).permissions & Permissions::Clear)
		)
		return false;

	std::ofstream DB_messages_write("DB_messages.txt", std::ios_base::out | std::ios_base::binary);
	DB_messages_write.close();

	return true;
}

Server::DBEntry Server::find_username
(
	const char* username
)
{
	DBEntry entry;
	size_t index = 0;
	char db_username[username_lenght];
	_DB_users_read.clear();
	_DB_users_read.seekg(0);

	while (true) {
		if (!_DB_users_read.read(db_username, username_lenght))
			break;

		if (strncmp(db_username, username, username_lenght) == 0) {
			_DB_users_read.seekg(index * sizeof(DBEntry));
			_DB_users_read.read(reinterpret_cast<char*>(&entry), sizeof(DBEntry));
			break;
		}

		_DB_users_read.seekg(++index * sizeof(DBEntry));
	}

	return entry;
}
