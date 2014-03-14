
#include <string.h>

#include "v8gl.h"

#include "./lib/fs.h"
#include "./lib/os.h"

#ifdef __ANDROID__

	#include "./binding/gles.h"
//	#include "./binding/glues.h"

#else

	#include "./binding/gl.h"
	#include "./binding/glu.h"
	#include "./binding/glut.h"

#endif


#include "./api/arraybuffer.h"
#include "./api/navigator.h"
#include "./api/script.h"
#include "./api/text.h"
#include "./api/texture.h"


// Advanced @built-in JavaScript headers
#include "./js/console.h"
#include "./js/interval.h"
#include "./js/timeout.h"



namespace v8gl {

	v8::Persistent<v8::Context> V8GL::initialize(int argc, char* argv[]) {

		v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New();


#ifdef __ANDROID__

		// GLES/GLUES/GLUT Bindings
		global->Set(v8::String::New("gl"), binding::GLES::generate());

		// TODO: GLUES port and freeglut android port
		// global->Set(v8::String::New("glu"), binding::GLUES::generate());
		// global->Set(v8::String::New("glut"), binding::GLUT::generate());

#else

		// GL/GLU/GLUT Bindings
		global->Set(v8::String::New("gl"),   binding::GL::generate());
		global->Set(v8::String::New("glu"),  binding::GLU::generate());
		global->Set(v8::String::New("glut"), binding::GLUT::generate());

#endif

		// Static APIs
		global->Set(v8::String::New("fs"),        lib::FS::generate(),        v8::ReadOnly);
		global->Set(v8::String::New("os"),        lib::OS::generate(),        v8::ReadOnly);
		global->Set(v8::String::New("navigator"), api::Navigator::generate(), v8::ReadOnly);


		v8::Persistent<v8::Context> context = v8::Context::New(NULL, global);

		context->AllowCodeGenerationFromStrings(false);

		context->Enter();


		// Dynamic APIs
		context->Global()->Set(v8::String::New("ArrayBuffer"), api::ArrayBuffer::generate()->GetFunction(), v8::ReadOnly);
		context->Global()->Set(v8::String::New("Script"),      api::Script::generate()->GetFunction(),      v8::ReadOnly);
		context->Global()->Set(v8::String::New("Text"),        api::Text::generate()->GetFunction(),        v8::ReadOnly);
		context->Global()->Set(v8::String::New("Texture"),     api::Texture::generate()->GetFunction(),     v8::ReadOnly);

		v8::Handle<v8::Array> argv_array = v8::Array::New(argc);

		int c = 0;
		for (int i = 0; i < argc; i++) {

			v8::Handle<v8::Number> key = v8::Number::New(c);
			v8::Handle<v8::String> value = v8::String::New(argv[i]);

			argv_array->Set(key, value);
			c++;

		}

		context->Global()->Set(v8::String::New("argc"), v8::Number::New(argc));
		context->Global()->Set(v8::String::New("argv"), argv_array);


		context->Exit();


		return context;

	}


	bool V8GL::dispatch(v8::Handle<v8::Context> context) {

		// @built-in Polyfills for BOM/DOM like behaviours
		execute(context, v8::String::New((char*) js_console_js),  v8::String::New("@built-in/console.js"));
		execute(context, v8::String::New((char*) js_interval_js), v8::String::New("@built-in/interval.js"));
		execute(context, v8::String::New((char*) js_timeout_js),  v8::String::New("@built-in/timeout.js"));

		return true;

	}



	v8::Handle<v8::Value> V8GL::executeVM(v8::Handle<v8::Context> context, v8::Handle<v8::String> source, v8::Handle<v8::String> filename) {

		char* filepath = *v8::String::Utf8Value(filename);

		char *old_root = lib::FS::pushVMRoot(filepath);
		v8::Handle<v8::Value> result = V8GL::execute(context, source, filename);
		lib::FS::popVMRoot(old_root);

		delete old_root;

		return result;

	}

	v8::Handle<v8::Value> V8GL::execute(v8::Handle<v8::Context> context, v8::Handle<v8::String> source, v8::Handle<v8::String> filename) {

		context->Enter();

		v8::HandleScope scope;
		v8::TryCatch try_catch;

		v8::Local<v8::Script> script = v8::Script::Compile(source, filename);
		v8::Handle<v8::Value> value;
		if (script.IsEmpty()) {

			V8GL::logException(&try_catch);
			value = v8::Null();

		} else {

			v8::Handle<v8::Value> result = script->Run();
			if (result.IsEmpty()) {

				// assert(try_catch.HasCaught());
				V8GL::logException(&try_catch);
				value = v8::Null();

            } else if (result->IsUndefined()) {

				value = v8::Undefined();

			} else {

				value = result;

			}

		}


		context->Exit();
		return scope.Close(value);

	}



	void V8GL::logException(v8::TryCatch* try_catch) {

		v8::HandleScope scope;

		v8::String::Utf8Value exception(try_catch->Exception());

		const char* exception_string = *exception;
		v8::Handle<v8::Message> message = try_catch->Message();

		fprintf(stderr, "\n");

		if (message.IsEmpty()) {

			fprintf(stderr, "%s\n", exception_string);

		} else {

			// Print (filename):(line number): (message).
			v8::String::Utf8Value filename(message->GetScriptResourceName());
			const char* filename_string = *filename;
			int linenum = message->GetLineNumber();
			fprintf(stderr, "%s:%i: %s\n", filename_string, linenum, exception_string);

			// Print line of source code.
			v8::String::Utf8Value sourceline(message->GetSourceLine());
			const char* sourceline_string = *sourceline;
			fprintf(stderr, "%s\n", sourceline_string);

			// Print wavy underline (GetUnderline is deprecated).
			int start = message->GetStartColumn();
			for (int i = 0; i < start; i++) {
				fprintf(stderr, "~");
			}

			int end = message->GetEndColumn();
			for (int i = start; i < end; i++) {
				fprintf(stderr, "^");
			}

			fprintf(stderr, "\n");


			v8::String::Utf8Value stack_trace(try_catch->StackTrace());
			if (stack_trace.length() > 0) {
				const char* stack_trace_string = *stack_trace;
				fprintf(stderr, "%s\n", stack_trace_string);
			}

		}

	}

}
