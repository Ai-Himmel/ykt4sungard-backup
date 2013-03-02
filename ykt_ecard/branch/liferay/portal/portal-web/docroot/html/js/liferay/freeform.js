(function(lib){

	lib.Freeform = function(portlet) {
		lib.Freeform.init(portlet);
	};

	lib.Freeform.extendNativeFunctionObject({
		_current: null,

		init: function(options) {
			var instance = this;

			// Set private variables
			instance._columns = options.columnSelector;
			instance._portlets = options.boxSelector;

			jQuery(instance._columns).find(instance._portlets).each(function() {
				instance.add(this);
			});
		},

		add: function(portlet) {
			var instance = this;
			portlet = jQuery.getOne(portlet);

			var handle = jQuery(".portlet-header-bar, .portlet-title-default, .portlet-topper", portlet).get(0);

			handle.style.cursor = "move";
			portlet.style.position = "absolute";

			jQuery(portlet).lDrag({
				handle: handle,
				portlet: portlet,
				onStart: function(settings) {
					settings.wasClicked = true;
					settings.container.style.zIndex = 99;
				},
				onMove: function(settings) {
					settings.wasClicked = false;
				},
				onComplete: function(settings) {
					var portlet = settings.portlet;

					if (!settings.wasClicked) {
						var left = parseInt(portlet.style.left);
						var top = parseInt(portlet.style.top);

						left = Math.round(left/10) * 10;
						top = Math.round(top/10) * 10;

						portlet.style.left = left + "px";
						portlet.style.top = top + "px";

						instance.moveToTop(portlet);
						instance.savePosition(portlet);
					}
					portlet.style.zIndex = "";
				}
			});

			jQuery(portlet).click(function() {
				if (instance._current != this) {
					instance.moveToTop(this);
					instance.savePosition(this, true);
					instance._current = this;
				}
			});

			var resizeBox = jQuery(".portlet-content-container, .portlet-borderless-container", portlet);
			var resizeHandle = jQuery(".portlet-resize-handle", portlet);

			if (!resizeHandle.length) {
				resizeBox.append("<div style='position:relative'><div class='portlet-resize-handle'></div></div>");
				resizeHandle = jQuery(".portlet-resize-handle", portlet);
			}

			if (resizeBox.length && resizeHandle.length) {
				jQuery(portlet).lResize({
					handle: resizeHandle[0],
					direction: "horizontal",
					mode: "add",
					portlet: portlet,
					onStart: function(settings) {
						instance.moveToTop(settings.container.resizeSettings.portlet);
					},
					onComplete: function(settings) {
						var portlet = settings.container.resizeSettings.portlet;
						var resizeBox = jQuery(portlet).getOne(".portlet-content-container, .portlet-borderless-container");
						var height = parseInt(resizeBox.style.height);
						var width = parseInt(portlet.style.width);

						height = Math.round(height/10) * 10;
						width = Math.round(width/10) * 10;

						resizeBox.style.height = height + "px";
						portlet.style.width = width + "px";
						instance.savePosition(portlet);
					}
				});

				resizeBox.lResize({
					handle: resizeHandle[0],
					direction: "vertical",
					mode: "add"
				});
			}

			if ((parseInt(portlet.style.top) + parseInt(portlet.style.left)) == 0) {
				portlet.style.top = (20 * portlet.columnPos) + "px";
				portlet.style.left = (20 * portlet.columnPos) + "px";
			}
		},

		findPosition: function(portlet) {
			var position = -1;

			jQuery(".portlet-boundary", portlet.parentNode).each(function(i) {
				if (this == portlet) {
					position = i;
				}
			});

			return position;
		},

		moveToTop: function(portlet) {
			var container = portlet.parentNode;
			portlet.oldPosition = this.findPosition(portlet);

			container.removeChild(portlet);
			container.appendChild(portlet);
		},

		savePosition : function(portlet, wasClicked) {
			var instance = this;
			var resizeBox = jQuery(portlet).find(".portlet-content-container, .portlet-borderless-container")[0];
			var newPosition = Liferay.Portlet.findIndex(portlet);
			var cmd;

			if (newPosition != portlet.oldPosition) {
				Liferay.Portlet.savePosition(portlet);
			}

			if (resizeBox && !wasClicked) {
				AjaxUtil.request(themeDisplay.getPathMain() + "/portal/update_layout" +
					"?p_l_id=" + themeDisplay.getPlid() +
					"&height=" + resizeBox.style.height +
					"&width=" + portlet.style.width +
					"&top=" + portlet.style.top +
					"&left=" + portlet.style.left +
					"&p_p_id=" + portlet.portletId +
					"&doAsUserId=" + themeDisplay.getDoAsUserIdEncoded() +
					"&cmd=drag");
			}
		}
	});
})(Liferay);