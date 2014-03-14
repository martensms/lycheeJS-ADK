
(function(global, adk, shell) {

	adk.template.Android = function(main) {

		this.__main = main;

	};


	adk.template.Android.DESCRIPTION = 'Android mobile builds (generates installable APK).';


	adk.template.Android.prototype = {

		getEnvironment: function(env, indir, outdir) {
			// Don't modify the paths, keep them as the Adapter requested it
			return env;
		},

		build: function(arch, indir, outdir) {

			console.group('adk.template.Android.prototype.build(' + arch + ', ' + indir + ', ' + outdir + ')');

			var builder = this.__main.getBuilder();

			builder.buildPNG(arch, outdir + '/lib/libpng.a', true);
			builder.buildV8(arch, outdir + '/lib/libv8_*.a', true);
			builder.buildV8GL(arch, outdir + '/lib/libv8gl.a', true);

			console.groupEnd();

		},

		clean: function(arch, indir, outdir) {
		},

		debug: function(arch, indir, outdir) {
		}

	};

})(this, this.adk, this.shell);

