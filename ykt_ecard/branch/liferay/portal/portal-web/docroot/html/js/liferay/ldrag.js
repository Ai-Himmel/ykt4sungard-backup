(function($){

	$.fn.lDrag = function(options) {
		this.each(function() {
			$.lDrag.create(this, options);
		});
	};

	$.fn.lDragBind = function(type, fn) {
		this.each(function() {
			$.lDrag.bind(this, type, fn);
		});
	};

	$.fn.lDragUnbind = function(type, fn) {
		this.each(function() {
			$.lDrag.unbind(this, type, fn);
		});
	};


	/* Define lDrag */

	$.lDrag = function(container, options) {
		/* OPTIONS
		 * handle (object): drag handle
		 * onStart (function): excute at start
		 * onMove (function): execute during dragging
		 * onComplete (function):  execute when completed
		 */
		$.lDrag.create(container, options)
	};

	$.lDrag.extendNativeFunctionObject({
		container : null,
		isDragging : false,
		scrollDirection: "",
		scrollTimer: 0,

		bind: function(container, type, fn) {
			if (container.dragSettings && type && fn) {
				if (type == "start") {
					container.dragSettings.onDragStart.push(fn);
				}
				else if (type == "move") {
					container.dragSettings.onDrag.push(fn);
				}
				else if (type == "complete") {
					container.dragSettings.onDragEnd.push(fn);
				}
			}
		},

		unbind: function(container, type, fn) {
			if (container.dragSettings && type && fn) {
				var settings = container.dragSettings;
				var prop = "";

				if (type == "start") {
					prop = "onDragStart";
				}
				else if (type == "move") {
					prop = "onDrag";
				}
				else if (type == "complete") {
					prop = "onDragEnd";
				}

				for (var i = 0; i < settings[prop].length; i++) {
					if (settings[prop][i] == fn) {
						settings[prop].splice(i,1);
					}
				}
			}
		},

		create: function(container, options) {
			options = options || {};
			options.container = container;

		    if (options.handle == null) {
	    		options.handle = container;
    		}
    		else {
    			if (typeof options.handle == "string") {
    				options.handle = $(options.handle)[0];
    			}
				options.handle.dragSettings = options;
    		}
			container.dragSettings = options;

			options.onDragStart = [];
			options.onDrag = [];
			options.onDragEnd = [];

			// Bind event listeners
			if (options.onStart) {
				$.lDrag.bind(container, "start", options.onStart);
			}
			if (options.onMove) {
				$.lDrag.bind(container, "move", options.onMove);
			}
			if (options.onComplete) {
				$.lDrag.bind(container, "complete", options.onComplete);
			}

			jQuery(options.handle).mousedown($.lDrag.onMouseDown);
		},

		scroll: function() {
			Liferay.Animate("layoutDragScroll", $.lDrag.scrollStart);
		},

	    scrollStart: function() {
	        var nwPosition;
	        var container = $.lDrag.container;
	        var jContainer = $($.lDrag.container);
	        var setTimer = false;
	        var scrollSpeed = 20;
	        var scrollTop = Viewport.scroll().y;

	        if ($.lDrag.scrollDirection == "down") {
	            nwPosition = jContainer.northwestPosition();
	            nwPosition.y += scrollSpeed;
	            nwPosition.reposition(container);
	            window.scrollTo(0, scrollTop + scrollSpeed);
	            setTimer = true;
	        }
	        else if ($.lDrag.scrollDirection == "up" && scrollTop > 0) {
	            nwPosition = jContainer.northwestPosition();
	            nwPosition.y -= scrollSpeed;
	            nwPosition.reposition(container);
	            window.scrollTo(0, scrollTop - scrollSpeed);
	            setTimer = true;
	        }
	        else {
	            setTimer = false;
	        }

	        if (!setTimer) {
	            $.lDrag.scrollDirection = "";
	            $.lDrag.scrollTimer = 0;
	            return false;
	        }
	    },

		onMouseDown: function(event) {
			mousePos.update(event);

			var settings = this.dragSettings;
			var container = settings.container;
			var jContainer = $(settings.container);

			if (!container._LFR_noDrag) {
				$.lDrag.container = container;

				var nwOffset = jContainer.northwestOffset(true);
				var seOffset = nwOffset.plus(jContainer.xySize());

				settings.originalZIndex = container.style.zIndex;

				// Offset of the mouse relative to the dragging container
				// This should remain constant.
				settings.mouseNwOffset = mousePos.minus(nwOffset);
				settings.mouseSeOffset = mousePos.minus(seOffset);
				settings.mouseStart = new Coordinate(mousePos.x, mousePos.y);
				settings.browserEvent = event;

				$.lDrag._processListeners(settings, "start");

				$.lDrag._setConstraint(settings);

				jQuery(document).mousemove($.lDrag.onMouseMove);
				jQuery(document).mouseup($.lDrag.onMouseUp);

				return false;
			}
			else {
				return;
			}
		},

		onMouseMove: function(event) {
			mousePos.update(event);
			// Assigning "container" because event is associated with the document
			// and not the dragging obj.  This is for robustness during a drag
			var container = $.lDrag.container;
			var settings = container.dragSettings;

			if (!$.lDrag._isAboveThreshold(settings)) {
				return false;
			}
			else {
				$.lDrag.isDragging = true;
			}

			container = settings.clone ? $.lDrag._createClone(settings) : settings.container;

			var jContainer = $(container);
			var nwOffset = jContainer.northwestOffset(true);
			var nwPosition = jContainer.northwestPosition();
			var size = jContainer.xySize();
			var seOffset = nwOffset.plus(size);
			var sePosition = nwPosition.plus(size);

			$.lDrag._setScrolling(settings);

			// new-pos = cur-pos + (mouse-pos - mouse-offset - screen-offset)
			//
			//	 new-pos: where we want to position the element using styles
			//	 cur-pos: current styled position of container
			//	 mouse-pos: mouse position
			//	 mouse-offset: mouse position relative to the dragging container
			//	 screen-offset: screen position of the current element
			//
			nwPosition = nwPosition.plus(mousePos.minus(nwOffset).minus(settings.mouseNwOffset));

			var offsetBefore = settings.autoCorrect ? jContainer.northwestOffset(true) : null;

			if (!settings.noDrag) {
				nwPosition.reposition(container);
			}

			settings.browserEvent = event;

			$.lDrag._processListeners(settings, "move");

			// once dragging has started, the position of the container
			// relative to the mouse should stay fixed.  They can get out
			// of sync if the DOM is manipulated while dragging, so we
			// correct the error here
			//
			// changed to be recursive/use absolute offset for corrections


			if (settings.autoCorrect) {
				var offsetAfter = jContainer.northwestOffset(true);

				if (!offsetBefore.equals(offsetAfter)) {
					// Position of the container has changed after the onDrag call.
					// Move element to the current mouse position
					var errorDelta = offsetBefore.minus(offsetAfter);
					nwPosition = jContainer.northwestPosition().plus(errorDelta);
					nwPosition.reposition(container);
				}
			}

			return false;
		},

		onMouseUp: function(event) {
			event = mousePos.update(event);
			var container = $.lDrag.container;
			var settings = container.dragSettings;

			if (settings.clone) $.lDrag._destroyClone(settings);

			jQuery(document).unbind("mousemove", $.lDrag.onMouseMove);
			jQuery(document).unbind("mouseup", $.lDrag.onMouseUp);

			settings.browserEvent = event;

			$.lDrag._processListeners(settings, "complete");
			$.lDrag.container = null;
			$.lDrag.isDragging = false;
		},

		_createClone: function(settings) {
			if (!settings.clonedNode) {
				var jClone = $("<div></div>");
				var jContainer = $(settings.container);
				var nwPosition = jContainer.northwestOffset(true);

				jClone.css({
					height: jContainer.height() + "px",
					left: nwPosition.x + "px",
					position: "absolute",
					top: nwPosition.y + "px",
					width: jContainer.width() + "px",
					zIndex: Liferay.zIndex.DRAG_ITEM
				});

				if (settings.opacity) jClone.css("opacity", settings.opacity);
				if (settings.dragClass) jClone.addClass(settings.dragClass);

				jClone[0].dragSettings = settings;
				settings.clonedNode = jClone[0];

				$("body").append(jClone);
			}

			return settings.clonedNode;
		},

		_destroyClone: function(settings) {
			if (settings.clonedNode) {
				var jClone = $(settings.clonedNode);
				var jContainer = $(settings.container);
				var containerPos = jContainer.northwestPosition();
				var newPos = containerPos.plus(mousePos.minus(settings.mouseStart));

				newPos.reposition(settings.container);

				jClone.remove();
				settings.clonedNode = null;
			}
		},

		_isAboveThreshold: function(settings) {
			var rt = true;
			if (!$.lDrag.isDragging && settings.threshold) {
				var distance = settings.mouseStart.distance(mousePos);
				if (distance < settings.threshold) {
					rt = false;
				}
			}

			return rt;
		},

		_processListeners: function(settings, type) {
			var prop = "";

			if (type == "start") {
				prop = "onDragStart";
			}
			else if (type == "move") {
				prop = "onDrag";
			}
			else if (type == "complete") {
				prop = "onDragEnd";
			}

			for (var i = 0; i < settings[prop].length; i++) {
				settings[prop][i](settings);
			}
		},

		_setConstraint: function(settings) {
			// Constraint coordinates are translated to mouse constraint coordinates.
			// The algorithm below will looks at the bounds of the dragging container and
			// makes sure that no part of it extends outside the constraint bounds.

			var minMouseX;
			var minMouseY;
			var maxMouseX;
			var maxMouseY;

			if (settings.minX != null)
				minMouseX = settings.minX + settings.mouseNwOffset.x;
			if (settings.minY != null)
				minMouseY = settings.minY + settings.mouseNwOffset.y;
			if (settings.maxX != null)
				maxMouseX = settings.maxX + settings.mouseSeOffset.x;
			if (settings.maxY != null)
				maxMouseY = settings.maxY + settings.mouseSeOffset.y;

			if (minMouseX && maxMouseX && minMouseX > maxMouseX)
				maxMouseX = minMouseX;
			if (minMouseY && maxMouseY && minMouseY > maxMouseY)
				maxMouseY = minMouseY;

			settings.mouseMin = new Coordinate(minMouseX, minMouseY);
			settings.mouseMax = new Coordinate(maxMouseX, maxMouseY);
		},

		_setScrolling: function(settings) {
			// Automatically scroll the page it drags near the top or bottom
			if (settings.scroll) {
				var scrollZone = 30;
				var scrollSpeed = 5;
				var scrollTop = Viewport.scroll().y;
				var pageHeight = Viewport.page().y;
				var clientHeight = Viewport.frame().y;

				if ((scrollTop + clientHeight + 2 * scrollZone) < pageHeight
						&& mousePos.y > (scrollTop + clientHeight - scrollZone)) {

		            if ($.lDrag.scrollDirection != "down"){
		                $.lDrag.scrollDirection = "down";
		                $.lDrag.scroll();
		            }
				}
				else if (scrollTop > 0 && mousePos.y < (scrollTop + scrollZone)) {
		            if ($.lDrag.scrollDirection != "up"){
		                $.lDrag.scrollDirection = "up";
		                $.lDrag.scroll();
		            }
				}
				else {
		            $.lDrag.scrollDirection = "";
				}
			}
		}
	});
})(jQuery);