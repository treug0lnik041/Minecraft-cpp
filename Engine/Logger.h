#pragma once
#include <string>
#include <queue>
#include <mutex>
#include <chrono>

namespace Engine
{
	class Logger
	{
	public:
		enum class severity
		{
			high, medium, low, notification
		};

		struct message
		{
			std::string header, body;
			severity sev;

			message(std::string header, std::string body, severity sev = severity::notification)
			{
				this->header = header;
				this->body = body;
				this->sev = sev;
			}

			message(std::pair<std::string, std::string> msg, severity sev = severity::notification) : message(msg.first, msg.second, sev)
			{

			}
		};

	protected:
		std::queue<message> qMessages;
		std::recursive_mutex mtx;
	protected:
		inline std::tm currentTime()
		{
			std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			std::tm now;
			localtime_s(&now, &time);
			return now;
		}

	public:
		friend Logger& operator<< (Logger& logger, const message& msg)
		{
			std::lock_guard<std::recursive_mutex> lock(logger.mtx);
			logger.qMessages.push(msg);

			return logger;
		}

	public:
		void flush();

	protected:
		/*
			Function out is virtual because you can prefer print log information info a file, console or anything else.
			I also made logger for Windows (using MessageBox and output in file) and console.
			Perhaps, you'll decide to make your own logger. You have to include your logger in Application.h file instead of mine.
		*/
		virtual void out(const message& msg) = 0;
	};
}