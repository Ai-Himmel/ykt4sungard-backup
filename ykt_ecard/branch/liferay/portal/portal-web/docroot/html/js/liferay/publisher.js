Liferay.Publisher = {
	publishers: {},

	deliver: function(publisher) {
		var instance = this;

		var scope = window;
		var data;

		if (arguments.length == 2) {
			data = [arguments[1]];
		}
		else {
			data = jQuery.map(arguments,
				function(item, i) {
					 return (i > 0) ? item : null;
				}
			);
		}

		jQuery.each(instance.publishers[publisher],
			function(i, el) {
				var classScope = el.obj || scope;
				el.func.apply(classScope, data);
			}
		);
	},

	register: function(publisher) {
		var instance = this;

		if (!instance.publishers[publisher]) {
			instance.publishers[publisher] = [];
		}
	},

	subscribe: function(publisher, func, obj) {
		var instance = this;

		if (instance.publishers[publisher] == null) {
			instance.register(publisher);
		}

		var alreadyExists = false;

		jQuery.each(instance.publishers[publisher],
			function(i, el) {
				if (el === func) {
					alreadyExists = true;
					return false;
				}
			}
		);

		if (!alreadyExists) {
			var data = {
				func: func,
				obj: obj || null
			};

			instance.publishers[publisher].push(data);
		}

	},

	unsubscribe: function(publisher, func) {
		var instance = this;

		if (!instance.publishers[publisher]) {
			return;
		}

		 jQuery.each(instance.publishers[publisher],
			function(i, el) {
				if (el.func === func) {
					instance.publishers[publisher].pop(el);
					return false;
				}
			}
		);
	}
};