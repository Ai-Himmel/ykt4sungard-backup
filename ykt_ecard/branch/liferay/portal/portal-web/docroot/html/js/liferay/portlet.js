Liferay.Portlet = {
	fn: {},
	fnAll: [],
	fnLast: [],
	ajaxList: {},
	list: {},

	isAjax: function(id) {
		return (this.ajaxList[id] == 1);
	},

	flagAjax: function(id) {
		this.ajaxList[id] = 1;
	},

	process: function(id) {
		var status = this.list[id];
		var count = 0;

		this.list[id] = 0;

		if (status == 1) {
			this.processPortlet(id);
			this.processAll(id);
		}
		else if (status == 0) {

			// Already processed. Do nothing.

		}
		else {

			// New portlet. Process and mark.

			this.processPortlet(id);
		}

		for (var i in this.list) {
			count += this.list[i];
		}

		if (count == 0) {
			this.processLast(id);
		}
	},

	processAll: function(id) {
		for (var i = 0; i < this.fnAll.length; i++) {
			this.fnAll[i](id, jQuery("#p_p_id_" + id + "_"));
		}
	},

	processPortlet: function(id) {
		if (this.fn[id]) {
			for (var i = 0; i < this.fn[id].length; i++) {
				this.fn[id][i](id, jQuery("#p_p_id_" + id + "_"));
			}
			this.fn[id] = [];
		}
	},

	processLast: function(id) {
		for (var i = 0; i < this.fnLast.length; i++) {
			this.fnLast[i](id);
		}
		this.fnLast = [];
	},

	ready: function(arg1, arg2) {
		if (typeof arg1 == "function") {
			this.fnAll.push(arg1);
		}
		else if (typeof arg1 == "string" && typeof arg2 == "function") {
			if (!this.fn[arg1]) {
				this.fn[arg1] = [];
			}

			this.fn[arg1].push(arg2);
		}
	},

	remove: function(id) {
		this.ajaxList[id] = 0;
		this.list[id] = 1;
		this.fn[id] = [];
	},

	last: function(arg1) {
		this.fnLast.push(arg1);
	},

	/*
	 * Helper methods for portlets
	 */
	findIndex: function(portlet) {
		var index = -1;

		jQuery("> .portlet-boundary", portlet.parentNode).each(
			function(i) {
				if (this == portlet) {
					index = i;
				}
			}
		);

		return index;
	},

	move: function(data) {
		var portlet = data.portlet;
		var neighbor = data.neighbor;
		var quadrant = data.quadrant;
		var container = data.container;

		if (neighbor && quadrant) {
			if (quadrant == 1 || quadrant == 2) {
				jQuery(neighbor).before(portlet);
			}
			else {
				jQuery(neighbor).after(portlet);
			}

			if (portlet && portlet.originalColumn) {
				var oColumn = jQuery(portlet.originalColumn);
				var portlets = oColumn.find('.portlet-boundary:first');

				if (portlets.length == 0) {
					oColumn.addClass('empty');
				}

				oColumn = portlet.originalColumn = null;
			}
		}
		else if (container) {
			jQuery(container).append(portlet).removeClass('empty');
		}

		this.savePosition(portlet);
	},

	savePosition: function(portlet) {
		var currentColumnId = portlet.parentNode.id.replace(/^layout-column_/, '');
		var index = this.findIndex(portlet);
		var portletId = portlet.id.replace(/^(p_p_id_)/, '');
		portletId = portletId.substring(0, portletId.length - 1);

		AjaxUtil.request(themeDisplay.getPathMain() + "/portal/update_layout" +
			"?p_l_id=" + themeDisplay.getPlid() +
			"&p_p_id=" + portletId +
			"&p_p_col_id=" + currentColumnId +
			"&p_p_col_pos=" + index +
			"&doAsUserId=" + themeDisplay.getDoAsUserIdEncoded() +
			"&cmd=move");
	}
};

jQuery.fn.last = function(fn) {
	Liferay.Portlet.last(fn);
};