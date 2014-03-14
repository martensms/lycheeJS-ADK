
this.window = glut.createWindow('V8GL runtime');

(function(dependencies) {

	for (var d = 0, dl = dependencies.length; d < dl; d++) {

		var script = new Script(dependencies[d]);

		script.load();
		script.execute();

	}

})([
	'./lychee/core.js',
	'./lychee/Builder.js',
	'./lychee/Preloader.js',
	'./lychee/platform/v8gl/bootstrap.js',
	'./game/Main.js'
]);

