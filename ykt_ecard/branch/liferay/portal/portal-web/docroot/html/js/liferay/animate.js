Liferay.Animate = function(id, fn, data) {

	/* id - unique identifier for this process
	 * fn - animation function
	 * data - object that is passed to the animation function
	 * data.delay - assign a number (in milliseconds) to this property
	 *				to delay the start of the animation process
	 */
	var lib = Liferay.Animate;

	if (!lib.q[id]) {
		lib.q[id] = {"id": id, "fn": fn, "data": data};
	}

	if (!lib.timer) {
		lib.start();
	}
};

Liferay.Animate.extendNativeFunctionObject({
	q: {},
	timer: 0,

	process: function() {
		var processed = false;
		for (var i in this.q) {
			var item = this.q[i];
			if (item) {
				var rt = item.fn(item.data);

				if (rt == false) {
					this.q[i] = null;
				}
				processed = true;
			}
		}

		if (!processed) {
			this.stop();
		}
	},

	start: function() {
		var lib = Liferay.Animate;
		if (!lib.timer) {
			Liferay.Animate.process();
			Liferay.Animate.timer = setInterval("Liferay.Animate.process()", 30);
		}
	},

	stop: function() {
		clearInterval(Liferay.Animate.timer);
		Liferay.Animate.timer = 0;
	}
});