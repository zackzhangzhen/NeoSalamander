#pragma once
#include "CSmtp.h"
#include <iostream>
class Courier
{
public:
	Courier(void);
	~Courier(void);
	static void sendMail(char* msg);
};

