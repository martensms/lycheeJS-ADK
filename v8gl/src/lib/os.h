
#ifndef LIB_OS_H_
#define LIB_OS_H_

#include <v8.h>


namespace lib {

	class OS {

		private:

		public:

			static v8::Handle<v8::ObjectTemplate> generate(void);

			static v8::Handle<v8::Value> handleLog(const v8::Arguments& args);
			static v8::Handle<v8::Value> handleInfo(const v8::Arguments& args);
			static v8::Handle<v8::Value> handleWarn(const v8::Arguments& args);
			static v8::Handle<v8::Value> handleError(const v8::Arguments& args);
			static v8::Handle<v8::Value> handleExec(const v8::Arguments& args);

			static void log(char* message);
			static void info(char* message);
			static void warn(char* message);
			static void error(char* message);

	};

};

#endif
 
