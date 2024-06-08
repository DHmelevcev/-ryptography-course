#include "MainForm.h"

using namespace CryptoPP;

SHA256 hash;

System::Void RBAC::MainForm::login_button_click(System::Object^ sender, System::EventArgs^ e)
{
	if (5 > textBox1->Text->Length || textBox1->Text->Length > 30) {
		MessageBox::Show("Неверная длина логина", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}
	if (1 > textBox2->Text->Length || textBox2->Text->Length > 32) {
		MessageBox::Show("Неверная длина пароля", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	auto ptr_username = Marshal::StringToHGlobalAnsi(textBox1->Text);
	auto username = static_cast<const char*>(ptr_username.ToPointer());
	auto ptr_password = Marshal::StringToHGlobalAnsi(textBox2->Text);
	auto password = static_cast<const char*>(ptr_password.ToPointer());

	std::string hashed_password;
	StringSource(password, true,
		new HashFilter(hash,
			new StringSink(hashed_password)));

	if (*permissions = server->authentication(
		username,
		hashed_password.c_str(),
		cookie
	)) {
		textBox1->Hide();
		label1->Hide();
		textBox2->Hide();
		label2->Hide();
		button1->Hide();

		textBox3->Show();
		button2->Show();
		if (*permissions & Server::Permissions::Read)
			button2->Enabled = true;

		button3->Show();
		if (*permissions & Server::Permissions::Write) {
			button3->Enabled = true;
			textBox3->ReadOnly = false;
		}

		button4->Show();
		if (*permissions & Server::Permissions::Clear)
			button4->Enabled = true;
	}
	else {
		MessageBox::Show("Неверный логин или пароль", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		textBox2->Text = "";
	}

	Marshal::FreeHGlobal(ptr_username);
	Marshal::FreeHGlobal(ptr_password);
}

System::Void RBAC::MainForm::read_button_click(System::Object^ sender, System::EventArgs^ e)
{
	int messages_lenght = 0;
	char* ptr_messages = server->get_all_messages
	(
		messages_lenght,
		cookie
	);

	if (ptr_messages) {
		textBox3->Text = Marshal::PtrToStringAnsi(IntPtr(ptr_messages), messages_lenght);
		delete[] ptr_messages;
	}
	else
		MessageBox::Show("Недоступная функция", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
}

System::Void RBAC::MainForm::write_button_click(System::Object^ sender, System::EventArgs^ e)
{
	if (1 > textBox3->Text->Length || textBox3->Text->Length > 1024) {
		MessageBox::Show("Недопустимая длина сообщения", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}

	auto ptr_message = Marshal::StringToHGlobalAnsi(textBox3->Text);
	auto message = static_cast<const char*>(ptr_message.ToPointer());

	if (!server->add_message(message, textBox3->Text->Length, cookie))
		MessageBox::Show("Недоступная функция", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);

	Marshal::FreeHGlobal(ptr_message);
}


System::Void RBAC::MainForm::clear_button_click(System::Object^ sender, System::EventArgs^ e)
{
	if (!server->delete_all_messages(cookie))
		MessageBox::Show("Недоступная функция", "", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
	else
		textBox3->Text = "";
}
