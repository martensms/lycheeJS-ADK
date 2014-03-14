
#include "glut.h"

#ifdef __APPLE__
	#include <OpenGL/OpenGL.h>
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif


/*
 * The GLUT bindings were implemented following the spec document available here:
 * http://www.opengl.org/resources/libraries/glut/spec3/spec3.html
 *
 * MISSING bindings (due to cross-platform conflictions):
 *
 *
 * - 4. from Window Management:
 *   > glut.setCursor
 *
 * - 6. Menu Management
 *
 * - 7. from Callback Registration:
 *   > glut.passiveMotionFunc
 *   > glut.entryFunc
 *   > glut.specialFunc
 *   > glut.spaceballMotionFunc, glut.spaceballRotationFunc, glut.spaceballButtonFunc
 *   > glut.dialsFunc
 *   > glut.tabletMotionFunc
 *   > glut.tabletButtonFunc
 *   > glut.menuStatusFunc
 *
 * - 8. Color Index Colormap Management
 *
 * - 9. from State Retrieval:
 *   > glut.layerGet
 *   > glut.deviceGet
 *
 * - 10. Font Rendering (use lychee.Font instead)
 * - 13. FORTRAN Binding
 *
 */


namespace binding {

	/*
	 * Initialization
	 */

	v8::Handle<v8::Value> GLUT::handleInit(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 2
			&& args[0]->IsNumber()
			&& args[1]->IsArray()
		) {

			int argc = args[0]->IntegerValue();
			v8::Local<v8::Object> arr_argv = args[1]->ToObject();


			char* argv[argc];

			const v8::Local<v8::Array> props = arr_argv->GetPropertyNames();
			const uint32_t length = props->Length();

			for (uint32_t a = 0; a < length; a++) {

				v8::Local<v8::Value> key = props->Get(a);
				v8::String::Utf8Value value(arr_argv->Get(key));

				argv[a] = *value;

			}

			glutInit(&argc, argv);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleMainLoop(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutMainLoop();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleInitWindowPosition(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 2
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
		) {

			int posx = args[0]->IntegerValue();
			int posy = args[1]->IntegerValue();

			glutInitWindowPosition((int) posx, (int) posy);

		}

		return scope.Close(v8::Undefined());

	}
 
	v8::Handle<v8::Value> GLUT::handleInitWindowSize(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 2
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
		) {

			int width = args[0]->IntegerValue();
			int height = args[1]->IntegerValue();

			glutInitWindowSize((int) width, (int) height);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleInitDisplayMode(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {

			unsigned int mode = args[0]->Uint32Value();
			glutInitDisplayMode((unsigned int) mode);

		}

		return scope.Close(v8::Undefined());

	}
 


	/*
	 * Window Management
	 */


	v8::Handle<v8::Value> GLUT::handleCreateSubWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 5
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
			&& args[3]->IsNumber()
			&& args[4]->IsNumber()
		) {

			int win    = args[0]->Uint32Value();
			int posx   = args[1]->Uint32Value();
			int posy   = args[2]->Uint32Value();
			int width  = args[3]->Uint32Value();
			int height = args[4]->Uint32Value();

			int id = glutCreateSubWindow((int) win, (int) posx, (int) posy, (int) width, (int) height);

			return v8::Uint32::New(id);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleGetWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		int id = glutGetWindow();

		return scope.Close(v8::Uint32::New(id));

	}

	v8::Handle<v8::Value> GLUT::handleSetWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {

			int win = args[0]->IntegerValue();
			glutSetWindow((int) win);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleDestroyWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {

			int win = args[0]->IntegerValue();
			glutDestroyWindow((int) win);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handlePostRedisplay(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutPostRedisplay();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSwapBuffers(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutSwapBuffers();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handlePositionWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 2
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
		) {

			int posx = args[0]->IntegerValue();
			int posy = args[1]->IntegerValue();

			glutPositionWindow((int) posx, (int) posy);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleReshapeWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 2
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
		) {

			int width  = args[0]->IntegerValue();
			int height = args[1]->IntegerValue();

			glutReshapeWindow((int) width, (int) height);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleFullScreen(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutFullScreen();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handlePopWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutPopWindow();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handlePushWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutPushWindow();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleShowWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutShowWindow();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleHideWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutHideWindow();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleIconifyWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutIconifyWindow();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSetWindowTitle(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {

			v8::String::Utf8Value raw(args[0]);
			char* name = *raw;

			glutSetWindowTitle((char*) name);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSetIconTitle(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {

			v8::String::Utf8Value raw(args[0]);
			char* name = *raw;

			glutSetIconTitle((char*) name);

		}

		return scope.Close(v8::Undefined());

	}



	/*
	 * Overlay Management
	 */

	v8::Handle<v8::Value> GLUT::handleEstablishOverlay(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutEstablishOverlay();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleRemoveOverlay(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutRemoveOverlay();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handlePostOverlayRedisplay(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutPostOverlayRedisplay();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleShowOverlay(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutShowOverlay();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleHideOverlay(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutHideOverlay();

		return scope.Close(v8::Undefined());

	}



	/*
	 * Callback Registration
	 */

	v8::Persistent<v8::Function> _glut_displayFuncCallback;

	void _glut_displayFunc() {

		v8::HandleScope scope;

		v8::Local<v8::Object> callback_scope = _glut_displayFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_displayFuncCallback->Call(callback_scope, 0, NULL);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleDisplayFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_displayFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_displayFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutDisplayFunc((void (*)(void)) _glut_displayFunc);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Persistent<v8::Function> _glut_overlayDisplayFuncCallback;

	void _glut_overlayDisplayFunc() {

		v8::HandleScope scope;

		v8::Local<v8::Object> callback_scope = _glut_overlayDisplayFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_overlayDisplayFuncCallback->Call(callback_scope, 0, NULL);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleOverlayDisplayFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_overlayDisplayFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_overlayDisplayFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutOverlayDisplayFunc((void (*)(void)) _glut_overlayDisplayFunc);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Persistent<v8::Function> _glut_reshapeFuncCallback;

	void _glut_reshapeFunc(int width, int height) {

		v8::HandleScope scope;

		v8::Handle<v8::Value> args[2];
		args[0] = v8::Integer::New(width);
		args[1] = v8::Integer::New(height);

		v8::Local<v8::Object> callback_scope = _glut_reshapeFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_reshapeFuncCallback->Call(callback_scope, 2, args);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleReshapeFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_reshapeFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_reshapeFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutReshapeFunc((void (*)(int width, int height)) _glut_reshapeFunc);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Persistent<v8::Function> _glut_keyboardFuncCallback;

	void _glut_keyboardFunc(unsigned char key, int x, int y) {

		v8::HandleScope scope;

		const char* keyval = (char*) &key;

		v8::Handle<v8::Value> args[2];
		args[0] = v8::String::New(keyval);
		args[1] = v8::Integer::New(x);
		args[2] = v8::Integer::New(y);

		v8::Local<v8::Object> callback_scope = _glut_keyboardFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_keyboardFuncCallback->Call(callback_scope, 2, args);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleKeyboardFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_keyboardFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_keyboardFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutKeyboardFunc((void (*)(unsigned char key, int x, int y)) _glut_keyboardFunc);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Persistent<v8::Function> _glut_mouseFuncCallback;

	void _glut_mouseFunc(int button, int state, int x, int y) {

		v8::HandleScope scope;

		v8::Handle<v8::Value> args[4];
		args[0] = v8::Integer::New(button);
		args[1] = v8::Integer::New(state);
		args[2] = v8::Integer::New(x);
		args[3] = v8::Integer::New(y);

		v8::Local<v8::Object> callback_scope = _glut_mouseFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_mouseFuncCallback->Call(callback_scope, 4, args);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleMouseFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_mouseFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_mouseFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutMouseFunc((void (*)(int button, int state, int x, int y)) _glut_mouseFunc);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Persistent<v8::Function> _glut_motionFuncCallback;

	void _glut_motionFunc(int x, int y) {

		v8::HandleScope scope;

		v8::Handle<v8::Value> args[2];
		args[0] = v8::Integer::New(x);
		args[1] = v8::Integer::New(y);

		v8::Local<v8::Object> callback_scope = _glut_motionFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_motionFuncCallback->Call(callback_scope, 2, args);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleMotionFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_motionFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_motionFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutMotionFunc((void (*)(int x, int y)) _glut_motionFunc);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Persistent<v8::Function> _glut_visibilityFuncCallback;

	void _glut_visibilityFunc(int x, int y) {

		v8::HandleScope scope;

		v8::Handle<v8::Value> args[2];
		args[0] = v8::Integer::New(x);
		args[1] = v8::Integer::New(y);

		v8::Local<v8::Object> callback_scope = _glut_visibilityFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_visibilityFuncCallback->Call(callback_scope, 2, args);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleVisibilityFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_visibilityFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_visibilityFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutMotionFunc((void (*)(int x, int y)) _glut_visibilityFunc);

		}

		return scope.Close(v8::Undefined());

	}
 
	v8::Persistent<v8::Function> _glut_idleFuncCallback;

	void _glut_idleFunc(void) {

		v8::HandleScope scope;

		v8::Handle<v8::Value> args[0];

		v8::Local<v8::Object> callback_scope = _glut_idleFuncCallback->CreationContext()->Global()->Get(v8::String::NewSymbol("glut"))->ToObject();
		v8::Local<v8::Value> result = _glut_idleFuncCallback->Call(callback_scope, 0, args);

		scope.Close(result);

	}

	v8::Handle<v8::Value> GLUT::handleIdleFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsFunction()) {

			_glut_idleFuncCallback.Dispose();
			v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast(args[0]);
			_glut_idleFuncCallback = v8::Persistent<v8::Function>::New(callback);

			glutIdleFunc(_glut_idleFunc);

		}

		return scope.Close(v8::Undefined());

	}


	typedef struct {
		v8::Persistent<v8::Object> scope;
		v8::Persistent<v8::Function> callback;
		v8::Persistent<v8::Value> value;
	} _glut_timer_data;

	_glut_timer_data * _glut_timerStack[50] = { NULL };

	void _glut_timerFunc(int id) {

		_glut_timer_data * timer = _glut_timerStack[id];

		if (timer != NULL) {

			v8::HandleScope scope;

			v8::Handle<v8::Value> args[1];
			args[0] = timer->value;

			timer->callback->Call(timer->scope, 1, args);

			timer->scope.Dispose();
			timer->callback.Dispose();
			timer->value.Dispose();

			delete timer;

			_glut_timerStack[id] = NULL;

			scope.Close(v8::Undefined());

		}

	}

	v8::Handle<v8::Value> GLUT::handleTimerFunc(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 3
			&& args[0]->IsNumber()
			&& args[1]->IsFunction()
			&& args[2]->IsUndefined() == false
		) {

			unsigned int milliseconds = args[0]->Uint32Value();

			v8::Handle<v8::Function> func = v8::Handle<v8::Function>::Cast(args[1]);
			v8::Persistent<v8::Function> callback = v8::Persistent<v8::Function>::New(func);

			v8::Local<v8::Object> argsThis = args.This();
			v8::Persistent<v8::Object> self = v8::Persistent<v8::Object>::New(argsThis);

			v8::Local<v8::Value> argsValue = args[2];
			v8::Persistent<v8::Value> value = v8::Persistent<v8::Value>::New(argsValue);

			bool found = false;
			int stackId = 0;
			for (; stackId < 50; stackId++) {

				if (_glut_timerStack[stackId] == NULL) {

					_glut_timer_data * data = new _glut_timer_data;

					data->value = value;
					data->scope = self;
					data->callback = callback;

					_glut_timerStack[stackId] = data;

					found = true;
					break;

				}

				stackId++;

			}


			if (found == true) {
				glutTimerFunc((unsigned int) milliseconds, (void (*)(int)) _glut_timerFunc, (int) stackId);
			}

		}

		return scope.Close(v8::Undefined());

	}



	/*
	 * State Retrieval
	 */

	v8::Handle<v8::Value> GLUT::handleGet(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1) {

			int state = args[0]->IntegerValue();
			int result = glutGet((GLenum) state);

			return v8::Integer::New(result);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleGetModifiers(const v8::Arguments& args) {

		v8::HandleScope scope;

		int modifiers = glutGetModifiers();

		return v8::Uint32::New(modifiers);

	}

	v8::Handle<v8::Value> GLUT::handleExtensionSupported(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (args.Length() == 1 && args[0]->IsString()) {

			v8::String::Utf8Value raw(args[0]);
			char* extension = *raw;

			int isSupported = glutExtensionSupported(extension);
			if (isSupported != 0) {
				return scope.Close(v8::True());
			}

		}


		return scope.Close(v8::False());

	}



	/*
	 * Geometric Object Rendering
	 */

	v8::Handle<v8::Value> GLUT::handleSolidSphere(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 3
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
		) {

			double radius = args[0]->NumberValue();
			int slices = args[1]->IntegerValue();
			int stacks = args[2]->IntegerValue();

			glutSolidSphere((GLdouble) radius, (GLint) slices, (GLint) stacks);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireSphere(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 3
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
		) {

			double radius = args[0]->NumberValue();
			int slices = args[1]->IntegerValue();
			int stacks = args[2]->IntegerValue();

			glutWireSphere((GLdouble) radius, (GLint) slices, (GLint) stacks);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidCube(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {

			double size = args[0]->NumberValue();

			glutSolidCube((GLdouble) size);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireCube(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {

			double size = args[0]->NumberValue();

			glutWireCube((GLdouble) size);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidCone(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 4
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
			&& args[3]->IsNumber()
		) {

			double base = args[0]->NumberValue();
			double height = args[1]->NumberValue();
			int slices = args[2]->IntegerValue();
			int stacks = args[3]->IntegerValue();

			glutSolidCone((GLdouble) base, (GLdouble) height, (GLint) slices, (GLint) stacks);

		}

		return scope.Close(v8::Undefined());

	}
 
	v8::Handle<v8::Value> GLUT::handleWireCone(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 4
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
			&& args[3]->IsNumber()
		) {

			double base = args[0]->NumberValue();
			double height = args[1]->NumberValue();
			int slices = args[2]->IntegerValue();
			int stacks = args[3]->IntegerValue();

			glutWireCone((GLdouble) base, (GLdouble) height, (GLint) slices, (GLint) stacks);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidTorus(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 4
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
			&& args[3]->IsNumber()
		) {

			double innerRadius = args[0]->NumberValue();
			double outerRadius = args[1]->NumberValue();
			int nsides = args[2]->IntegerValue();
			int rings = args[3]->IntegerValue();

			glutSolidTorus((GLdouble) innerRadius, (GLdouble) outerRadius, (GLint) nsides, (GLint) rings);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireTorus(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 4
			&& args[0]->IsNumber()
			&& args[1]->IsNumber()
			&& args[2]->IsNumber()
			&& args[3]->IsNumber()
		) {

			double innerRadius = args[0]->NumberValue();
			double outerRadius = args[1]->NumberValue();
			int nsides = args[2]->IntegerValue();
			int rings = args[3]->IntegerValue();

			glutWireTorus((GLdouble) innerRadius, (GLdouble) outerRadius, (GLint) nsides, (GLint) rings);

		}

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidDodecahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutSolidDodecahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireDodecahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutWireDodecahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidTetrahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutSolidTetrahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireTetrahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutWireTetrahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidOctahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutSolidOctahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireOctahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutWireOctahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidIcosahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutSolidIcosahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireIcosahedron(const v8::Arguments& args) {

		v8::HandleScope scope;

		glutWireIcosahedron();

		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleSolidTeapot(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {
			double size = args[0]->NumberValue();
			glutSolidTeapot((GLdouble) size);
		}
 
		return scope.Close(v8::Undefined());

	}

	v8::Handle<v8::Value> GLUT::handleWireTeapot(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsNumber()
		) {
			double size = args[0]->NumberValue();
			glutWireTeapot((GLdouble) size);
		}

		return scope.Close(v8::Undefined());
	}



	/*
	 * Window Management: glut.createWindow()
	 *
	 * This is down here to automatically rebind all callbacks
	 */

	v8::Handle<v8::Value> GLUT::handleCreateWindow(const v8::Arguments& args) {

		v8::HandleScope scope;

		if (
			args.Length() == 1
			&& args[0]->IsString()
		) {

			v8::String::Utf8Value raw(args[0]);
			char* name = *raw;

			int win = glutCreateWindow((char*) name);


			if (_glut_displayFuncCallback.IsEmpty() == false) {
				glutDisplayFunc((void (*)(void)) _glut_displayFunc);
			}

			if (_glut_reshapeFuncCallback.IsEmpty() == false) {
				glutReshapeFunc((void (*)(int width, int height)) _glut_reshapeFunc);
			}

			if (_glut_keyboardFuncCallback.IsEmpty() == false) {
				glutKeyboardFunc((void (*)(unsigned char key, int x, int y)) _glut_keyboardFunc);
			}

			if (_glut_mouseFuncCallback.IsEmpty() == false) {
				glutMouseFunc((void (*)(int button, int state, int x, int y)) _glut_mouseFunc);
			}

			if (_glut_motionFuncCallback.IsEmpty() == false) {
				glutMotionFunc((void (*)(int x, int y)) _glut_motionFunc);
			}


			if (_glut_overlayDisplayFuncCallback.IsEmpty() == false) {
				glutOverlayDisplayFunc((void (*)(void)) _glut_overlayDisplayFunc);
			}


			return scope.Close(v8::Uint32::New(win));

		}


		return scope.Close(v8::Uint32::New(0));

	}

	v8::Handle<v8::ObjectTemplate> GLUT::generate() {

		v8::HandleScope scope;

		v8::Handle<v8::ObjectTemplate> gluttpl = v8::ObjectTemplate::New();



		/*
		 * Initialization
		 */
		gluttpl->Set(v8::String::NewSymbol("init"),               v8::FunctionTemplate::New(GLUT::handleInit));
		gluttpl->Set(v8::String::NewSymbol("initWindowPosition"), v8::FunctionTemplate::New(GLUT::handleInitWindowPosition));
		gluttpl->Set(v8::String::NewSymbol("initWindowSize"),     v8::FunctionTemplate::New(GLUT::handleInitWindowSize));
		gluttpl->Set(v8::String::NewSymbol("initDisplayMode"),    v8::FunctionTemplate::New(GLUT::handleInitDisplayMode));

		gluttpl->Set(v8::String::NewSymbol("RGBA"),        v8::Uint32::New(GLUT_RGBA),        v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("RGB"),         v8::Uint32::New(GLUT_RGB),         v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("INDEX"),       v8::Uint32::New(GLUT_INDEX),       v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("SINGLE"),      v8::Uint32::New(GLUT_SINGLE),      v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("DOUBLE"),      v8::Uint32::New(GLUT_DOUBLE),      v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("ACCUM"),       v8::Uint32::New(GLUT_ACCUM),       v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("ALPHA"),       v8::Uint32::New(GLUT_ALPHA),       v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("DEPTH"),       v8::Uint32::New(GLUT_DEPTH),       v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("STENCIL"),     v8::Uint32::New(GLUT_STENCIL),     v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("MULTISAMPLE"), v8::Uint32::New(GLUT_MULTISAMPLE), v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("STEREO"),      v8::Uint32::New(GLUT_STEREO),      v8::ReadOnly);

		// FIXME: Evaluate where this is available
		// gluttpl->Set(v8::String::NewSymbol("LUMINANCE"), v8::Uint32::New(GLUT_LUMINANCE), v8::ReadOnly);


		/*
		 * Event Processing
		 */
		gluttpl->Set(v8::String::NewSymbol("mainLoop"), v8::FunctionTemplate::New(GLUT::handleMainLoop));


		/*
		 * Window Management
		 */
		gluttpl->Set(v8::String::NewSymbol("createWindow"),    v8::FunctionTemplate::New(GLUT::handleCreateWindow));
		gluttpl->Set(v8::String::NewSymbol("createSubWindow"), v8::FunctionTemplate::New(GLUT::handleCreateSubWindow));
		gluttpl->Set(v8::String::NewSymbol("setWindow"),       v8::FunctionTemplate::New(GLUT::handleSetWindow));
		gluttpl->Set(v8::String::NewSymbol("getWindow"),       v8::FunctionTemplate::New(GLUT::handleGetWindow));
		gluttpl->Set(v8::String::NewSymbol("destroyWindow"),   v8::FunctionTemplate::New(GLUT::handleDestroyWindow));
		gluttpl->Set(v8::String::NewSymbol("postRedisplay"),   v8::FunctionTemplate::New(GLUT::handlePostRedisplay));
		gluttpl->Set(v8::String::NewSymbol("swapBuffers"),     v8::FunctionTemplate::New(GLUT::handleSwapBuffers));
		gluttpl->Set(v8::String::NewSymbol("positionWindow"),  v8::FunctionTemplate::New(GLUT::handlePositionWindow));
		gluttpl->Set(v8::String::NewSymbol("reshapeWindow"),   v8::FunctionTemplate::New(GLUT::handleReshapeWindow));
		gluttpl->Set(v8::String::NewSymbol("fullScreen"),      v8::FunctionTemplate::New(GLUT::handleFullScreen));
		gluttpl->Set(v8::String::NewSymbol("popWindow"),       v8::FunctionTemplate::New(GLUT::handlePopWindow));
		gluttpl->Set(v8::String::NewSymbol("pushWindow"),      v8::FunctionTemplate::New(GLUT::handlePushWindow));
		gluttpl->Set(v8::String::NewSymbol("showWindow"),      v8::FunctionTemplate::New(GLUT::handleShowWindow));
		gluttpl->Set(v8::String::NewSymbol("hideWindow"),      v8::FunctionTemplate::New(GLUT::handleHideWindow));
		gluttpl->Set(v8::String::NewSymbol("iconifyWindow"),   v8::FunctionTemplate::New(GLUT::handleIconifyWindow));
		gluttpl->Set(v8::String::NewSymbol("setWindowTitle"),  v8::FunctionTemplate::New(GLUT::handleSetWindowTitle));
		gluttpl->Set(v8::String::NewSymbol("setIconTitle"),    v8::FunctionTemplate::New(GLUT::handleSetIconTitle));


		/*
		 * Overlay Management
		 */
		gluttpl->Set(v8::String::NewSymbol("establishOverlay"),     v8::FunctionTemplate::New(GLUT::handleEstablishOverlay));
		gluttpl->Set(v8::String::NewSymbol("removeOverlay"),        v8::FunctionTemplate::New(GLUT::handleRemoveOverlay));
		gluttpl->Set(v8::String::NewSymbol("postOverlayRedisplay"), v8::FunctionTemplate::New(GLUT::handlePostOverlayRedisplay));
		gluttpl->Set(v8::String::NewSymbol("showOverlay"),          v8::FunctionTemplate::New(GLUT::handleShowOverlay));
		gluttpl->Set(v8::String::NewSymbol("hideOverlay"),          v8::FunctionTemplate::New(GLUT::handleHideOverlay));


		/*
		 * Callback Registration
		 */
		gluttpl->Set(v8::String::NewSymbol("displayFunc"),           v8::FunctionTemplate::New(GLUT::handleDisplayFunc));
		gluttpl->Set(v8::String::NewSymbol("overlayDisplayFunc"),    v8::FunctionTemplate::New(GLUT::handleOverlayDisplayFunc));
		gluttpl->Set(v8::String::NewSymbol("reshapeFunc"),           v8::FunctionTemplate::New(GLUT::handleReshapeFunc));
		gluttpl->Set(v8::String::NewSymbol("keyboardFunc"),          v8::FunctionTemplate::New(GLUT::handleKeyboardFunc));
		gluttpl->Set(v8::String::NewSymbol("LEFT_BUTTON"),           v8::Uint32::New(GLUT_LEFT_BUTTON),   v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("MIDDLE_BUTTON"),         v8::Uint32::New(GLUT_MIDDLE_BUTTON), v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("RIGHT_BUTTON"),          v8::Uint32::New(GLUT_RIGHT_BUTTON),  v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("UP"),                    v8::Uint32::New(GLUT_UP),            v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("DOWN"),                  v8::Uint32::New(GLUT_DOWN),          v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("mouseFunc"),             v8::FunctionTemplate::New(GLUT::handleMouseFunc));
		gluttpl->Set(v8::String::NewSymbol("motionFunc"),            v8::FunctionTemplate::New(GLUT::handleMotionFunc));
		gluttpl->Set(v8::String::NewSymbol("VISIBLE"),               v8::Uint32::New(GLUT_VISIBLE),     v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("NOT_VISIBLE"),           v8::Uint32::New(GLUT_NOT_VISIBLE), v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("visibilityFunc"),        v8::FunctionTemplate::New(GLUT::handleVisibilityFunc));
		gluttpl->Set(v8::String::NewSymbol("idleFunc"),              v8::FunctionTemplate::New(GLUT::handleIdleFunc));
		gluttpl->Set(v8::String::NewSymbol("timerFunc"),             v8::FunctionTemplate::New(GLUT::handleTimerFunc));


		/*
		 * State Retrieval
		 */

		gluttpl->Set(v8::String::NewSymbol("DISPLAY_MODE_POSSIBLE"), v8::Uint32::New(GLUT_DISPLAY_MODE_POSSIBLE), v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("INIT_DISPLAY_MODE"),     v8::Uint32::New(GLUT_INIT_DISPLAY_MODE),     v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("INIT_WINDOW_X"),         v8::Uint32::New(GLUT_INIT_WINDOW_X),         v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("INIT_WINDOW_Y"),         v8::Uint32::New(GLUT_INIT_WINDOW_Y),         v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("INIT_WINDOW_WIDTH"),     v8::Uint32::New(GLUT_INIT_WINDOW_WIDTH),     v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("INIT_WINDOW_HEIGHT"),    v8::Uint32::New(GLUT_INIT_WINDOW_HEIGHT),    v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("WINDOW_X"),              v8::Uint32::New(GLUT_WINDOW_X),              v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("WINDOW_Y"),              v8::Uint32::New(GLUT_WINDOW_Y),              v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("WINDOW_WIDTH"),          v8::Uint32::New(GLUT_WINDOW_WIDTH),          v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("WINDOW_HEIGHT"),         v8::Uint32::New(GLUT_WINDOW_HEIGHT),         v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("SCREEN_WIDTH"),          v8::Uint32::New(GLUT_SCREEN_WIDTH),          v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("SCREEN_HEIGHT"),         v8::Uint32::New(GLUT_SCREEN_HEIGHT),         v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("get"),                   v8::FunctionTemplate::New(GLUT::handleGet));
		gluttpl->Set(v8::String::NewSymbol("ACTIVE_SHIFT"),          v8::Uint32::New(GLUT_ACTIVE_SHIFT), v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("ACTIVE_CTRL"),           v8::Uint32::New(GLUT_ACTIVE_CTRL),  v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("ACTIVE_ALT"),            v8::Uint32::New(GLUT_ACTIVE_ALT),   v8::ReadOnly);
		gluttpl->Set(v8::String::NewSymbol("getModifiers"),          v8::FunctionTemplate::New(GLUT::handleGetModifiers));
		gluttpl->Set(v8::String::NewSymbol("extensionSupported"),    v8::FunctionTemplate::New(GLUT::handleExtensionSupported));


		/*
		 * Geometric Object Rendering
		 */
		gluttpl->Set(v8::String::NewSymbol("solidSphere"),       v8::FunctionTemplate::New(GLUT::handleSolidSphere));
		gluttpl->Set(v8::String::NewSymbol("wireSphere"),        v8::FunctionTemplate::New(GLUT::handleWireSphere));
		gluttpl->Set(v8::String::NewSymbol("solidCube"),         v8::FunctionTemplate::New(GLUT::handleSolidCube));
		gluttpl->Set(v8::String::NewSymbol("wireCube"),          v8::FunctionTemplate::New(GLUT::handleWireCube));
		gluttpl->Set(v8::String::NewSymbol("solidCone"),         v8::FunctionTemplate::New(GLUT::handleSolidCone));
		gluttpl->Set(v8::String::NewSymbol("WireCone"),          v8::FunctionTemplate::New(GLUT::handleWireCone));
		gluttpl->Set(v8::String::NewSymbol("solidTorus"),        v8::FunctionTemplate::New(GLUT::handleSolidTorus));
		gluttpl->Set(v8::String::NewSymbol("wireTorus"),         v8::FunctionTemplate::New(GLUT::handleWireTorus));
		gluttpl->Set(v8::String::NewSymbol("solidDodecahedron"), v8::FunctionTemplate::New(GLUT::handleSolidDodecahedron));
		gluttpl->Set(v8::String::NewSymbol("wireDodecahedron"),  v8::FunctionTemplate::New(GLUT::handleWireDodecahedron));
		gluttpl->Set(v8::String::NewSymbol("solidOctahedron"),   v8::FunctionTemplate::New(GLUT::handleSolidOctahedron));
		gluttpl->Set(v8::String::NewSymbol("wireOctahedron"),    v8::FunctionTemplate::New(GLUT::handleWireOctahedron));
		gluttpl->Set(v8::String::NewSymbol("solidTetrahedron"),  v8::FunctionTemplate::New(GLUT::handleSolidTetrahedron));
		gluttpl->Set(v8::String::NewSymbol("wireTetrahedron"),   v8::FunctionTemplate::New(GLUT::handleWireTetrahedron));
		gluttpl->Set(v8::String::NewSymbol("solidIcosahedron"),  v8::FunctionTemplate::New(GLUT::handleSolidIcosahedron));
		gluttpl->Set(v8::String::NewSymbol("wireIcosahedron"),   v8::FunctionTemplate::New(GLUT::handleWireIcosahedron));
		gluttpl->Set(v8::String::NewSymbol("solidTeapot"),       v8::FunctionTemplate::New(GLUT::handleSolidTeapot));
		gluttpl->Set(v8::String::NewSymbol("wireTeapot"),        v8::FunctionTemplate::New(GLUT::handleWireTeapot));

		return scope.Close(gluttpl);

	}

}

