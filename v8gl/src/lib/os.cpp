
#include "os.h"
#include "string.h"


#ifdef __ANDROID__

	#include <android/log.h>

#endif


namespace lib {

	v8::Handle<v8::ObjectTemplate> OS::generate() {

		v8::Handle<v8::ObjectTemplate> tpl = v8::ObjectTemplate::New();

		tpl->Set(v8::String::NewSymbol("log"),   v8::FunctionTemplate::New(OS::handleLog),   v8::ReadOnly);
		tpl->Set(v8::String::NewSymbol("info"),  v8::FunctionTemplate::New(OS::handleInfo),  v8::ReadOnly);
		tpl->Set(v8::String::NewSymbol("warn"),  v8::FunctionTemplate::New(OS::handleWarn),  v8::ReadOnly);
		tpl->Set(v8::String::NewSymbol("error"), v8::FunctionTemplate::New(OS::handleError), v8::ReadOnly);
		tpl->Set(v8::String::NewSymbol("exec"),  v8::FunctionTemplate::New(OS::handleExec),  v8::ReadOnly);

		return tpl;

	}

	v8::Handle<v8::Value> OS::handleLog(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {
			v8::String::Utf8Value message(args[0]->ToString());
			OS::log(*message);
		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> OS::handleInfo(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {
			v8::String::Utf8Value message(args[0]->ToString());
			OS::info(*message);
		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> OS::handleWarn(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {
			v8::String::Utf8Value message(args[0]->ToString());
			OS::warn(*message);
		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> OS::handleError(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {
			v8::String::Utf8Value message(args[0]->ToString());
			OS::error(*message);
		}

		return scope.Close(v8::Undefined());

	}


	v8::Handle<v8::Value> OS::handleExec(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {

			char buffer[BUFSIZ + 1];

			memset(buffer, '\0', sizeof(buffer));

			v8::String::Utf8Value cmd(args[0]->ToString());

			FILE *stream = popen(*cmd, "r");
			if (stream != NULL) {

				int chars = fread(buffer, sizeof(char), BUFSIZ, stream);
				while (chars > 0) {
					buffer[chars - 1] = '\0';
					chars = fread(buffer, sizeof(char), BUFSIZ, stream);
				}

				pclose(stream);

			}


			return v8::String::New(buffer, strlen(buffer));

		}


		return v8::Null();

	}

	void OS::log(char* message) {

#ifdef __ANDROID__
		__android_log_write(ANDROID_LOG_VERBOSE, "ms.martens.v8gl", message);
#else
		fprintf(stdout, "%s\n", message);
#endif

	}

	void OS::info(char* message) {

#ifdef __ANDROID__
		__android_log_write(ANDROID_LOG_INFO, "ms.martens.v8gl", message);
#else
		fprintf(stdout, "(i) %s\n", message);
#endif

	}

	void OS::warn(char* message) {

#ifdef __ANDROID__
		__android_log_write(ANDROID_LOG_WARN, "ms.martens.v8gl", message);
#else
		fprintf(stdout, "(w) %s\n", message);
#endif

	}

	void OS::error(char* message) {

#ifdef __ANDROID__
		__android_log_write(ANDROID_LOG_ERROR, "ms.martens.v8gl", message);
#else
		fprintf(stderr, "(e) %s\n", message);
#endif

	}

} 
