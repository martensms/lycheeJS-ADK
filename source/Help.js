
(function(global, adk, shell) {

	adk.Help = function(main) {

		this.__main = main;

		this.__whitespace = 10;

	};

	adk.Help.prototype = {

		/*
		 * PRIVATE API
		 */

		__getWhitespace: function(str, max) {

			max = typeof max === 'number' ? max : this.__whitespace;

			var space = '';
			for (var w = str.length; w < max; w++) {
				space += ' ';
			}

			return space;

		},


		/*
		 * PUBLIC API
		 */

		generate: function() {

			var self  = this.__main.getSelf();
			var str   = '';
			var space = '';

			str += 'lycheeJS ADK (App Development Kit) v0.6 pre-release\n';
			str += '\n';
			str += 'This program comes with ABSOLUT NO WARRANTY;\n';
			str += 'This is free software, and you are welcome to redistribute it under certain conditions;\n';
			str += 'See the LICENSE.txt for details.\n';
			str += '\n\n';
			str += 'Recommended development environment: Ubuntu 12.10 (amd64 CPU), with graphics card supporting OpenGL 4.2+\n';
			str += '\n\n';


			space = this.__getWhitespace('Usage:', this.__whitespace + 'Example:'.length);
			str += 'Usage:' + space + self + ' <task> <template [.<architecture>]> <game-folder> [--<flag>=value]\n';
			str += '\n';

			space = this.__getWhitespace('Example:', this.__whitespace + 'Example:'.length);
			str += 'Example:' + space + self + ' bootstrap --adapter=lycheeJS\n';


			space = this.__getWhitespace('', this.__whitespace + 'Example:'.length);
			str += space + self + ' build android.arm ./external/lycheeJS/game/boilerplate --adapter=lycheeJS\n';

			space = this.__getWhitespace('', 'Example:'.length);

			str += '\nAvailable <task>s:\n\n';

			for (var id in adk.Main.TASKS) {
				str += space + id + this.__getWhitespace(id) + adk.Main.TASKS[id] + '\n';
			}

			str += '\nAvailable <template>s:\n\n';

			for (var id in adk.template) {

				var description = '(No description)';
				if (typeof adk.template[id].DESCRIPTION === 'string') {
					description = adk.template[id].DESCRIPTION;
				}

				str += space + id + this.__getWhitespace(id) + description + '\n';

			}

			str += '\nAvailable <architecture>s:\n\n';

			for (var id in adk.Main.ARCHITECTURES) {
				str += space + id + this.__getWhitespace(id) + adk.Main.ARCHITECTURES[id] + '\n';
			}


			str += '\nAvailable <flag>s:\n\n';
			var values = [];
			for (var id in adk.adapter) { values.push(id); }
			str += space + 'adapter' + this.__getWhitespace('adapter') + 'The engine adapter, accepted values: ' + values.join(',') + '\n';


			console.log(str);

		}

	};

})(this, this.adk, this.shell);

