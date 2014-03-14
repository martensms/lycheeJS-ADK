
(function(global, adk, shell) {

	adk.template.Web = function(main) {

		this.__main = main;

	};


	adk.template.Web.DESCRIPTION = 'Facebook or Web builds (generates hostable folder).';


	adk.template.Web.prototype = {

		getEnvironment: function(env, indir, outdir) {
			return env;
		},

		build: function(arch, indir, outdir) {
		},

		clean: function(arch, indir, outdir) {
		},

		debug: function(arch, indir, outdir) {
		}

	};

})(this, this.adk, this.shell);

