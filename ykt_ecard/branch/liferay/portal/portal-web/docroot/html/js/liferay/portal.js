var DragLink = {
	create: function(item, dragId) {
		item.dragId = jQuery.getOne(dragId);
		item.clickLink = item.href;
		item.href = "javascript:void(0)";
		item.onclick = DragLink.onLinkClick;
	},

	onLinkClick: function() {
		if (this.dragId.wasClicked) {
			if (Liferay.Browser.is_ie) {
				setTimeout("window.location = \"" + this.clickLink + "\";", 0);
			}
			else {
				window.location = this.clickLink;
			}
		}
	}
};

var NavFlyout = {
	zIndex: 1,
	initialize: function (nav) {
		var nav = jQuery.getOne(nav);
		var navMapList = jQuery("portlet-nav-map-list", nav);

		navMapList.not(".portlet-nav-map-level_1, .portlet-nav-map-level_2")
			.css({position: "absolute", display: "none"});

		jQuery(".portlet-nav-map-list a", nav).each(function(){
			var item = jQuery(this.parentNode.parentNode);
				if (item.is(".portlet-nav-map-level_1")) {
					item.mouseover(function() {
						NavFlyout.hide(this.parentNode);
					});
				}
				else {
					item.mouseover(NavFlyout.onHoverOver);
				}
		});
	},

	initToggle: function(nav, imgSrc) {
		var nav = jQuery.getOne(nav);
		var navMapList = jQuery(".portlet-nav-map-level_1 > li", nav);
		navMapList.click(NavFlyout.onToggle);
		navMapList.css({ backgroundImage: "url(" + imgSrc + ")" });
	},

	hide: function(listItem) {
		NavFlyout.initialize(listItem.parentNode);
	},

	onHoverOver: function() {
		var listItem = this.parentNode;

		// Hide all other submenus
		if (jQuery(listItem.parentNode).is(".portlet-nav-map-level_2")) {
			NavFlyout.hide(listItem.parentNode.parentNode.parentNode);
		}
		else {
			NavFlyout.hide(listItem);
		}

		// Show current submenu
		jQuery(listItem.childNodes).filter("ul")
			.css({
				display: "block",
				top: "5px",
				left: "100px"
			});

		// Fix Z-Index
		zItem = listItem;
		while (zItem.nodeName.toLowerCase() != "div") {
			if (zItem.nodeName.toLowerCase() == "li") {
				zItem.style.zIndex = NavFlyout.zIndex;
			}
			zItem = zItem.parentNode;
		}

		NavFlyout.zIndex++;
	},

	onToggle: function() {
		var subMenu = jQuery("ul:first", this).get(0);

		if (this.isShowing) {
			subMenu.style.display = "none";
			this.style.backgroundImage = this.style.backgroundImage.replace(/02_minus/, "02_plus");
			this.isShowing = false;
		}
		else {
			subMenu.style.display = "block";
			subMenu.style.backgroundImage = "none";
			this.style.backgroundImage = this.style.backgroundImage.replace(/02_plus/, "02_minus");
			this.isShowing = true;
		}
	}
};

var PortletHeaderBar = {
	mode: {},

	fade: function(data) {
		var count = data.count;
		var id = data.id;

		var changed = false;
		var icons = jQuery("#portlet-header-bar_" + id + " .portlet-small-icon-bar");

		if (PortletHeaderBar.mode[id] == "in") {
			if (count <= 10) {
				if (count >= 0) {
					icons.css({"opacity": (count/10), "display": ""});
				}
				changed = true;
				data.count++;
			}
		}
		else if (PortletHeaderBar.mode[id] == "out") {
			if (count >= 0) {
				if (count <= 10) {
					icons.css("opacity", (count/10));
				}
				data.count--;
				changed = true;
			}
			else {
				icons.css("display", "none");
			}
		}

		return changed;
	},

	hide: function (id) {
		this.mode[id] = "out";
		Liferay.Animate("header-icon-fade_" + id,
			PortletHeaderBar.fade,
			{ count: 15, id: id }
		);
	},

	show: function (id) {
		this.mode[id] = "in";
		Liferay.Animate("header-icon-fade_" + id,
			PortletHeaderBar.fade,
			{ count: -5, id: id }
		);
	}
};

var PhotoSlider = Class.create();
PhotoSlider.prototype = {

	initialize: function (slidingWindow, windowWidth, photos, totalPages, varName) {
		this.TOTAL_FRAMES = 20;
		this.count = 0;
		this.page = 0;
		this.timer = 0;
		this.start = 0;

		this.photos = jQuery.getOne(photos);
		this.photos.style.position = "relative";
		this.photos.style.left = "0px";

		this.slidingWindow = _J$.getOne(slidingWindow);
		this.windowWidth = windowWidth;
		this.totalPages = totalPages;
		this.varName = varName;
	},

	animate: function() {
		if (this.count <= this.TOTAL_FRAMES) {
			var ratio = this.count / this.TOTAL_FRAMES;
			var ratio2 = Math.sin(ratio * (Math.PI/2));
			var delta = -(this.page * this.windowWidth) - this.start;

			this.photos.style.left = this.start + (delta * ratio2);
			this.count++;
			this.timer = setTimeout(this.varName + ".animate()", 30);
		}
		else {
			this.timer = 0;
		}
	},

	left: function() {
		this.start = parseInt(this.photos.style.left);

		if (this.page > 0) {
			this.page--;
			this.count = 0;

			if (!this.timer) {
				this.timer = setTimeout(this.varName + ".animate()", 30);
			}
		}
	},

	right: function() {
		this.start = parseInt(this.photos.style.left);

		if (this.page < (this.totalPages - 1)) {
			this.page++;
			this.count = 0;

			if (!this.timer) {
				this.timer = setTimeout(this.varName + ".animate()", 30);
			}
		}
	}
};

var Tabs = {
	show : function (namespace, names, id) {
		var el = document.getElementById(namespace + id + "TabsId");

		if (el) {
			el.className = "current";
		}

		el = document.getElementById(namespace + id + "TabsSection");

		if (el) {
			el.style.display = "block";
		}

		for (var i = 0; (names.length > 1) && (i < names.length); i++) {
			if (id != names[i]) {
				el = document.getElementById(namespace + names[i] + "TabsId");

				if (el) {
					el.className = "none";
				}

				el = document.getElementById(namespace + names[i] + "TabsSection");

				if (el) {
					el.style.display = "none";
				}
			}
		}
	}
};

var StarRating = new Class({
	initialize: function(id, options) {
		/* OPTIONS
		 * displayOnly: (boolean) non-modifiable display
		 * onComplete: (function) executes when rating is selected
		 * rating: rating to initialize to
		 */
			this.options = options || {};
			this.rating = this.options.rating || 0;
			var item = jQuery("#" + id);
			this.stars = item.find("img");
			var self = this;

			if (!this.options.displayOnly) {
				item.bind("mouseout",  {self: this}, this.onHoverOut);

				this.stars.each(function(index) {
					this.index = index + 1;
					jQuery(this).bind("click", {self: self}, self.onClick)
						   .bind("mouseover", {self: self}, self.onHoverOver);
				})
			}

			this.display(this.rating, "rating");
		}
	});

StarRating.implement({
	display: function(rating, mode) {
		var self = this;
		rating = rating == null ? this.rating : rating;

		var whole = Math.floor(rating);
		var fraction = rating - whole;

		this.stars.each(function(index) {
			image = this;
			if (index < whole) {
				if (mode == "hover") {
					image.src = image.src.replace(/\bstar_.*\./, "star_hover.");
				}
				else {
					image.src = image.src.replace(/\bstar_.*\./, "star_on.");
				}
			}
			else {
				if (fraction < 0.25) {
					image.src = image.src.replace(/\bstar_.*\./, "star_off.");
				}
				else if (fraction < 0.50) {
					image.src = image.src.replace(/\bstar_.*\./, "star_on_quarter.");
				}
				else if (fraction < 0.75) {
					image.src = image.src.replace(/\bstar_.*\./, "star_on_half.");
				}
				else if (fraction < 1.00) {
					image.src = image.src.replace(/\bstar_.*\./, "star_on_threequarters.");
				}
				fraction = 0;
			}
		});
	},

	onHoverOver: function(event) {
		event.data.self.display(this.index, "hover");
	},
	onHoverOut: function(event) {
		event.data.self.display();
	},
	onClick: function(event) {
		var target = this;
		var newRating = target.index;
		var self = event.data.self;
		self.rating = newRating;

		if (self.options.onComplete) {
			self.options.onComplete(newRating);
		}

		self.display(newRating);
	}
});

var ToolTip = {
	container: null,

	show: function(event, obj, text) {
		var instance = this;

		var container = instance.container;
		var currentItem = jQuery(obj);
		var position = currentItem.offset();

		var dimensions = instance._windowCalculation();

		if (!container) {
			container = jQuery('<div class="portal-tool-tip"></div>').appendTo('body');

			instance.container = container;
		}

		container.html(text);

		container.show();

		var boxWidth = container.width();
		var width = currentItem.width();
		var height = currentItem.height();
		var boxHeight = container.height();
		var left = position.left - (boxWidth / 2);
		var top = position.top + height + 5;

		if (left < 0) {
			left = 5;
		}
		else {
			left += 5;
		}

		if (left + boxWidth > dimensions.right) {
			left = (left - (boxWidth / 2 )) + width;
		}

		if (top + boxHeight > dimensions.bottom) {
			top = top - (height + boxHeight + 5);
		}

		container.css(
			{
				cursor: 'default',
				left: left + 'px',
				position: 'absolute',
				top: top + 'px',
				zIndex: Liferay.zIndex.TOOLTIP
			}
		);

		currentItem.one(
			'mouseout',
			function() {
				instance.hide();
			}
		);
	},

	hide: function(event) {
		var instance = this;

		instance.container.hide();
	},

	_windowCalculation: function() {
		var instance = this;

		if (instance._window.right == null) {
			var windowSize = {};
			var body = instance._body;
			if (!body) {
				body = jQuery('body');
				instance._body = body;
			}

			instance._window = {
				bottom: body.height(),
				left: 0,
				right: body.width(),
				top: 0
			};

			jQuery(window).resize(
				function() {
					instance._window.bottom = body.height();
					instance._window.right = body.width();
				}
			);
		}
		return instance._window;
	},
	_body: null,
	_window: {}
};