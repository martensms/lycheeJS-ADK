
(function(global, adk, shell) {

	adk.template.Linux = function(main) {

		this.__main = main;

	};


	adk.template.Linux.DESCRIPTION = 'Linux builds with V8GL (requires OpenGL 2.1 on targeted system).';


	adk.template.Linux.prototype = {

		getEnvironment: function(env, indir, outdir) {
			return env;
		},

		build: function(arch, indir, outdir) {

			console.group('adk.template.Linux.prototype.build(' + arch + ', ' + indir + ', ' + outdir + ')');

			var builder = this.__main.getBuilder();

			builder.buildV8GL(arch, outdir + '/v8gl', false);

			console.groupEnd();

		},

		clean: function(arch, indir, outdir) {

		},

		debug: function(arch, indir, outdir) {

			console.log('DEBUGGING...');

			var valgrindlog = this.__main.getRoot() + '/' + this.__main.getTemporaryFolder() + '/valgrind.log';

			var args = [
				'G_SLICE=always-malloc',
				'G_DEBUG=gc-friendly',
				'valgrind -v',
				'--tool=memcheck',
				'--leak-check=full',
				'--num-callers=40',
				'--log-file=' + valgrindlog,
				'$(which ./v8gl)'
			];


			var cmd = 'cd ' + folder + ' && ' + args.join(' ') + ';';
			shell.exec(cmd);

		}

	};

})(this, this.adk, this.shell);

