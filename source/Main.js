
this.adk = {
	adapter:  {},
	config:   {},
	template: {}
};


(function(global, adk, shell) {

	adk.extend = function(obj) {

		for (var a = 1, al = arguments.length; a < al; a++) {

			var obj2 = arguments[a];
			if (obj2) {

				for (var prop in obj2) {
					obj[prop] = obj2[prop];
				}

			}

		}

	};


	(function(dependencies) {

		// Remember, lycheeJS-adk/ is root folder
		for (var d = 0, dl = dependencies.length; d < dl; d++) {
			include('./source/' + dependencies[d]);
		}

	})([
		'Builder.js',
		'Help.js',
		'adapter/lycheeJS.js',
		'template/Android.js',
		'template/Linux.js',
		'template/Web.js'
	]);


	adk.Main = function(argc, argv) {

		var settings = this.__parseArguments(argc, argv);


		this.__self     = argv[0];
		this.__root     = shell.exec('cd "$(dirname "' + this.__self + '")"; pwd;');
		this.__builder  = new adk.Builder(this);
		this.__help     = new adk.Help(this);
		this.__adapter  = null;
		this.__template = null;


		if (adk.adapter[settings.flags.adapter] !== undefined) {
			this.__adapter = new adk.adapter[settings.flags.adapter](this);
		} else {
			this.__adapter = new adk.adapter.lycheeJS(this);
		}


		// Dispatch shell log
		shell.log = this.getRoot() + '/log';


		if (settings.task === null) {
			this.__help.generate();
			return this;
		}


		if (settings.task !== 'bootstrap') {

			if (settings.template !== null) {
				this.__template = new adk.template[settings.template](this);
			} else {
				console.error('Invalid <template>!');
				return this;
			}

			if (settings.indir === null && settings.task !== 'debug') {
				console.error('Invalid <game-folder>!');
				return this;
			}

		}


		if (settings.arch === null) {

			settings.arch = this.getHostArch();

			if (settings.arch === null) {
				console.error('Unsupported <architecture>!');
				return this;
			} else {
				console.warn('Using host <architecture> (' + settings.arch + ')');
			}

		}

		if (settings.outdir === null) {
			settings.outdir = './out/' + settings.template + '.' + settings.arch;
		}

		settings.tmpdir = './.temp';


		this.__settings = settings;

		switch(settings.task) {

			case "bootstrap": this.bootstrap(); break;
			case "build":     this.build(); break;
			case "clean":     this.clean(); break;
			case "debug":     this.debug(); break;

			default:
				this.__help.generate();
			break;

		}

	};


	adk.Main.TASKS = {
		bootstrap: 'Bootstraps the ADK with externally required files, depends on the adapter.',
		build:     'Starts the build process, output depends on the <template>.',
		clean:     'Cleans up temporary files.',
		debug:     'Starts the debugger for the built (and installed) app, depends on the <template>.'
	};


	adk.Main.ARCHITECTURES = {
		ia32: '32 Bit (i686, x86)',
		x64:  '64 Bit (amd64, x86_64)',
		arm:  'ARM (armeabi-v7a)'
	};


	adk.Main.prototype = {

		/*
		 * PRIVATE API
		 */

		getBuildTarget: function(arch) {

			if (this.__settings.task === 'debug') {
// TODO: Enable this after all Makefiles are supporting debug symbol variants
//				return arch + '.debug';
				return arch + '.release';
			} else {
				return arch + '.release';
			}

		},

		getHostArch: function() {

			var arch   = null;
			var unamep = shell.exec("uname -p");

			if (unamep === 'x86_64') {
				arch = "x64";
			} else if (unamep === 'i686') {
				arch = 'ia32';
			}


			return arch;

		},

		__parseArguments: function(argc, argv) {

			var data = {
				task:     null,
				template: null,
				arch:     null,
				indir:    null,
				outdir:   null,
				flags:    {
					adapter: null
				}
			};


			var tmp;

			for (var av = 1, al = argv.length; av < al; av++) {

				var str  = argv[av];
				var id   = null;
				var arch = null;

				if (argv[av].match(/\./)) {

					tmp  = argv[av].split('.')[0];
					id   = tmp.charAt(0).toUpperCase() + tmp.substr(1);
					arch = argv[av].split('.')[1];

				} else {
					id = str.charAt(0).toUpperCase() + str.substr(1);
				}


				// ./adk build
				if (adk.Main.TASKS[str] !== undefined) {

					data.task = str;

				// ./adk build web
				} else if (adk.template[id] !== undefined) {

					data.template = id;


					// TODO: This needs a more generic solution
					if (id === 'Android') {

						if (arch === 'arm') {
							data.arch = 'android_arm';
						} else if (arch === 'ia32') {
							data.arch = 'android_ia32';
						}

					} else {
						data.arch = arch;
					}


				// ./adk build web ./external/lycheeJS/game/pong
				} else if (shell.isDirectory(str) === true) {

					data.indir = str;

				// ./adk build web ./game/path --flag=value
				} else if (str.substr(0, 2) === "--"){

					str = str.substr(2);

					var tmp = str.split('=');
					if (tmp[0] && tmp[1]) {

						if (tmp[0] === 'adapter' && adk.adapter[tmp[1]] !== undefined) {
							data.flags[tmp[0]] = tmp[1];
						} else {
							data.flags[tmp[0]] = tmp[1];
						}

					}

				} else {

					console.warn('Could not interpret argument "' + str + '"');

				}

			}


			return data;

		},



		/*
		 * PUBLIC API
		 */

		getBuilder: function() {
			return this.__builder;
		},

		getRoot: function() {
			return this.__root;
		},

		getSelf: function() {
			return this.__self;
		},

		getSettings: function() {
			return this.__settings;
		},

		getTemplate: function() {
			return this.__template;
		},

		getTemporaryFolder: function() {

			if (shell.isDirectory(this.__settings.tmpdir) === false) {
				shell.createDirectory(this.__settings.tmpdir);
			}

			return this.__settings.tmpdir;

		},



		/*
		 * Tasks
		 */

		bootstrap: function() {

			if (this.__adapter !== null) {
				this.__adapter.bootstrap();
			}

		},

		build: function() {

			var indir  = this.__settings.indir;
			var outdir = this.__settings.outdir;
			var arch   = this.__settings.arch;


			var env = null;
			if (this.__adapter !== null) {
				env = this.__adapter.getEnvironment(arch, indir, outdir);
			} else {
				console.warn('No valid <adapter> selected!');
			}

			if (this.__template !== null) {
				env = this.__template.getEnvironment(env, indir, outdir);
			} else {
				console.warn('No valid <template> selected!');
			}


			if (env !== null) {

				// Cleanup old builds
				if (shell.isDirectory(outdir) === true) {
					shell.removeDirectory(outdir);
				}

				shell.createDirectory(outdir, true);


				for (var f = 0, fl = env.folders.length; f < fl; f++) {
					shell.copyDirectory(env.folders[f][0], outdir + '/' + env.folders[f][1]);
				}

				for (var f = 0, fl = env.files.length; f < fl; f++) {
					shell.copyFile(env.files[f][0], outdir + '/' + env.files[f][1]);
				}

			} else {
				console.error('Could not determine game environment.');
				return;
			}


			if (this.__template !== null) {
				this.__template.build(arch, indir, outdir);
			}

		},

		clean: function() {

		},

		debug: function() {

			var indir  = this.__settings.indir;
			var outdir = this.__settings.outdir;
			var arch   = this.__settings.arch;

			if (this.__template !== null) {
				this.__template.debug(arch, indir, outdir);
			}

		}

	};

})(this, this.adk, this.shell);

