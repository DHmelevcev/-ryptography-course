#pragma once
#include <fstream>
#include <string>
#include <sstream>

#include <cryptlib.h>
#include <filters.h>
#include <sha.h>
#include <misc.h>

class Server
{
public:
	Server();

	inline static const size_t username_lenght = 30;
	inline static const size_t password_lenght = 32;
	inline static const size_t cookie_lenght = password_lenght;

	enum Permissions : uint16_t
	{
		None = 0x0000,
		Read = 0x0001,
		Write = 0x0002,
		Clear = 0x0004,
		p4 = 0x0008,
		p5 = 0x0010,
		p6 = 0x0020,
		p7 = 0x0040,
		p8 = 0x0080,
		p9 = 0x0100,
		p10 = 0x0200,
		p11 = 0x0400,
		p12 = 0x0800,
		p13 = 0x1000,
		p14 = 0x2000,
		p15 = 0x4000,
		p16 = 0x8000,
		Admin = 0xFFFF
	};

private:
	std::ifstream _DB_users_read;

	std::ifstream _DB_messages_read;

	struct DBEntry
	{
		char username[username_lenght] = {};
		uint16_t  permissions = Permissions::None;
		char password[password_lenght] = {};
	};

	struct ActiveUser
	{
		char username[username_lenght] = {};
		char cookie[cookie_lenght] = {};

		ActiveUser
		(
			const char* new_username,
			const char* new_cookie
		);
	};

	std::vector<ActiveUser> _active_users;

public:
	uint16_t authentication
	(
		const char* username,
		const char* password,
		const char* cookie
	);

	char* get_all_messages
	(
		int& lenght,
		const char* cookie
	);

	bool add_message
	(
		const char* message,
		int lenght,
		const char* cookie
	);

	bool delete_all_messages
	(
		const char* cookie
	);

private:
	DBEntry find_username
	(
		const char* username
	);
};
