
(function(global) {

	global.include = function(file, callback, scope) {

		callback = callback instanceof Function ? callback : null;
		scope    = scope !== undefined ? scope : global;


		var script = new Script(file);

		script.load();

		var value = script.execute();


		if (callback !== null) {
			callback.call(scope, value);
		}


		return value;

	};


	global.main = function(argc, argv) {

		include('./source/bootstrap.js');

		include('./source/Main.js', function() {
			new adk.Main(argc, argv);
		}, this);

	};

})(this);

