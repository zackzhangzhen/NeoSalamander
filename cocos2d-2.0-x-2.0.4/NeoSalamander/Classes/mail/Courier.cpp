#include "Courier.h"


Courier::Courier(void)
{
}


Courier::~Courier(void)
{
}

void Courier::sendMail(char* msg)
{
	try
	{
		if(msg == NULL)
		{
			return;
		}

		CSmtp mail;

		mail.SetSMTPServer("smtp.126.com",25);
		mail.SetLogin("zackzhangzhen@126.com");
		mail.SetPassword("6296812");
  		mail.SetSenderName("zack");
  		mail.SetSenderMail("zackzhangzhen@126.com");
  		mail.SetReplyTo("zackzhangzhen@126.com");
  		mail.SetSubject("The message");
  		mail.AddRecipient("zackzhangzhen@gmail.com");
  		mail.SetXPriority(XPRIORITY_NORMAL);
  		mail.SetXMailer("The Bat! (v3.02) Professional");
  		mail.AddMsgLine(msg);

		mail.Send();
	}
	catch(ECSmtp e)
	{
		//do nothing
	}
}
