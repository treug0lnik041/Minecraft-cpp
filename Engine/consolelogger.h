#pragma once
#include "Logger.h"
#include <iostream>

namespace Engine
{
	class logger : public Logger
	{
	private:
		void out(const message& msg) override
		{
			std::lock_guard<std::recursive_mutex> lock(this->mtx);

			std::tm now = this->currentTime();
			std::cout << "[" << now.tm_hour << ":" << now.tm_min << ":" << now.tm_sec << "] " << msg.header << ": " << msg.body << std::endl;
		}
	};
}