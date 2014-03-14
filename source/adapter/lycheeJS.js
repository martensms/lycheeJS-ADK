
(function(global, adk, shell) {

	// Routine required for installation
	var _url = 'https://github.com/martensms/lycheeJS/archive/master.zip';
	var _install = function(temp, path) {

		if (shell.isDirectory(temp) === false) {
			shell.createDirectory(temp, true);
		}


		var cmd = '';

		if (shell.isDirectory(path) === false) {

			shell.createDirectory(path, true);

			cmd = 'wget -O ' + temp + '/lycheeJS.zip ' + _url + ';';
			shell.exec(cmd);

			if (shell.isFile(temp + '/lycheeJS.zip') === true) {

				cmd = 'unzip ' + temp + '/lycheeJS.zip -d ' + temp + ';';
				shell.exec(cmd);

				cmd = 'mv ' + temp + '/lycheeJS-master/* ' + path + ';';
				shell.exec(cmd);


				return true;

			}

		}


		return false;

	};



	adk.adapter.lycheeJS = function(main) {

		this.__main = main;

	};


	adk.adapter.lycheeJS.DESCRIPTION = 'Games made with the lycheeJS engine (http://martens.ms/lycheeJS).';


	adk.adapter.lycheeJS.prototype = {

		/*
		 * Helpers
		 */

		__trim: function(str) {
			return str.replace(/^\s+/,'').replace(/\s+$/,'');
		},

		__generateHTML: function(html, folder, buildenv) {

			console.group('adk.adapter.lycheeJS.prototype.__generateHTML(%html%, ' + folder + ', %buildenv%)');


			var lines = html.split('\n');
			var temp = this.__main.getTemporaryFolder() + '/index.html';


			var bases = {};
			for (var id in buildenv.bases) {
				var url = buildenv.bases[id][0];
				bases[id] = url.substr(folder.length + 1, url.length - (folder.length + 1));
			}


			var code = '';

			console.log('> Parsing ' + lines.length + ' lines of HTML...');

			for (var l = 0, ll = lines.length; l < ll; l++) {

				var line   = lines[l];
				var trline = this.__trim(line);
				if (trline.substr(0, '<script'.length) === '<script') {

					line = line.replace(/src=\"(.*)\"/, function(match, content, offset, str) {

						var base = null;
						var id   = null;
						for (var bid in bases) {

							if (content.substr(0, bases[bid].length) === bases[bid]) {
								base = bases[bid];
								id = bid;
								break;
							}

						}

						var value = 'src="' + content + '"';

						if (base !== null) {
							value = 'src="' + buildenv.bases[id][1] + content.substr(base.length, content.length - base.length) + '"';
						}

						console.log('> Parsed <script> with ' + value + '.');

						return value;

					});

					code += line + '\n';

				} else if (trline.substr(0, '<link'.length) === '<link') {

					line = line.replace(/href=\"(.*)\"/, function(match, content, offset, str) {

						var base = null;
						var id   = null;
						for (var bid in bases) {

							if (content.substr(0, bases[bid].length) === bases[bid]) {
								base = bases[bid];
								id = bid;
								break;
							}

						}

						var value = 'href="' + content + '"';

						if (base !== null) {
							value = 'href="' + buildenv.bases[id][1] + content.substr(base.length, content.length - base.length) + '"';
						}

						console.log('> Parsed <link> with ' + value + '.');

						return value;

					});

					code += line + '\n';

				} else {
					code += line + '\n';
				}

			}


			console.groupEnd();

			if (fs.write(temp, code) === true) {

				return temp;
			} else {
				return null;
			}

		},

		__generateMain: function(gameenv, buildenv, isV8GL) {

			isV8GL = isV8GL === true;


			var temp = this.__main.getTemporaryFolder() + '/main.js';

			// Use the new target folders, which were
			// linked by the Adapter and updated by
			// the Template
			var bases = {};
			for (var baseId in buildenv.bases) {
				bases[baseId] = buildenv.bases[baseId][1];
			}


			if (gameenv._build === null) {
				console.error('Could not parse lychee.build(callback, scope) in init.js');
				return null;
			}


			var code = '';
			if (isV8GL === true) {
				code = fs.read('./source/adapter/raw/lycheeJS/main.v8gl.js');
			}

			code += 'lychee.debug = ' + gameenv.debug + ';\n';
			code += 'lychee.rebase(' + JSON.stringify(bases) + ');\n';
			code += 'lychee.tag(' + JSON.stringify(gameenv.tags) + ');\n';
			code += 'lychee.build(' + gameenv._build + ', this);\n';


			if (fs.write(temp, code) === true) {
				return temp;
			} else {
				return null;
			}

		},



		/*
		 * Interaction with adk.Main
		 */

		getEnvironment: function(arch, indir, outdir) {

			if (shell.isFile(indir + '/init.js') === false) {
				return null;
			}


			console.group('adk.adapter.lycheeJS.prototype.getEnvironment(' + arch + ', ' + indir + ', ' + outdir + ')');

			if (shell.isDirectory('./external/lycheeJS') === false) {
				_install(this.__main.getTemporaryFolder(), './external/lycheeJS');
			}


			var env  = {
				data: {
					bases: {},
					tags: {}
				},
				folders: [],
				files:   []
			};

			var temp = this.__main.getTemporaryFolder() + '/lycheeJS_parser';

			if (shell.isDirectory(temp) === true) {
				shell.removeDirectory(temp);
			}


			if (shell.createDirectory(temp) === true) {

				var builder = this.__main.getBuilder();
				var arch    = this.__main.getHostArch();

				builder.buildV8GL(arch, temp + '/v8gl', false);

				shell.copyFile('./source/adapter/raw/lycheeJS/main.env.js', temp + '/main.js');
				shell.copyFile(indir + '/init.js', temp + '/init.js');

				shell.exec('cd "' + temp + '" && ./v8gl;');


				if (shell.isFile(temp + '/env.json') === true) {

					var data = null;
					var raw  = fs.read(temp + '/env.json');
					if (raw !== null) {

						try {
							data = JSON.parse(raw);
						} catch(e) {
						};

					}

					if (data !== null) {

						console.info('> Environment tracking from init.js succeeded.');

						for (var baseId in data.bases) {

							console.log('> Parsing base "' + baseId + '".');
							var arr = [ indir + '/' + data.bases[baseId], './' + baseId ];
							env.data.bases[baseId] = arr;

							console.log('> Adding folder "' + arr[0] + '" as "' + arr[1] + '".');
							env.folders.push(arr);

						}

						for (var tagId in data.tags) {
							console.log('> Setting tag "' + tagId + '" with value "' + data.tags[tagId] + '".');
							env.data.tags[tagId] = data.tags[tagId];
						}


						var assetdir = indir + '/asset';
						if (shell.isDirectory(assetdir) === true) {
							console.log('> Adding folder "' + assetdir + '" as "./asset".');
							env.folders.push([ assetdir, './asset' ]);
						}


						var template = this.__main.getTemplate();
						if (template !== null) {

							if (template instanceof adk.template.Web) {

								data.tags.platform = [ 'webgl', 'html' ];
								console.log('> Changing tag "platform" to value "' + data.tags.platform.toString() + '".');

								var html = fs.read(indir + '/index.html');
								if (html !== null) {

									var indexhtml = this.__generateHTML(html, indir, env.data);
									if (indexhtml !== null) {
										console.log('> Adding file "' + indexhtml + '" as "./index.html".');
										env.files.push([ indexhtml, './index.html' ]);
									}

								}

								var mainjs = this.__generateMain(data, env.data, false);
								if (mainjs !== null) {
									console.log('> Adding file "' + mainjs + '" as "./init.js".');
									env.files.push([ mainjs, './init.js' ]);
								}

							} else {

								data.tags.platform = [ 'v8gl' ];
								console.log('> Changing tag "platform" to value "' + data.tags.platform.toString() + '".');

								var mainjs = this.__generateMain(data, env.data, true);
								if (mainjs !== null) {
									console.log('> Adding file "' + mainjs + '" as "./main.js".');
									env.files.push([ mainjs, './main.js' ]);
								}

							}

						}

					}

				} else {

					env = null;
					console.error('> Environment tracking from init.js failed. Probably there\'s a JavaScript Parsing error thrown inside.');

				}

			}


			console.groupEnd();

			return env;

		},

		bootstrap: function() {

			console.group('adk.adapter.lycheeJS.prototype.bootstrap()');

			var temp = this.__main.getTemporaryFolder();

			if (shell.isDirectory('./external/lycheeJS') === true) {
				shell.removeDirectory('./external/lycheeJS');
			}

			_install(temp, './external/lycheeJS');

			console.groupEnd();

		}

	};

})(this, this.adk, this.shell);

