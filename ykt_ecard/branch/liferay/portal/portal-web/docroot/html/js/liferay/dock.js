Liferay.Dock = {
	init: function() {
		var instance = this;

		var dock = jQuery('.lfr-dock');

		if (!dock.is('.interactive-mode')) {
			return;
		}

		dock.addClass('lfr-component');

		var dockList = dock.find('.lfr-dock-list');

		if (dockList.length > 0){
			var myPlaces = jQuery('.my-places', dock);

			instance._dock = dock;
			instance._dockList = dockList;
			instance._myPlaces = myPlaces;

			instance._hideCommunities(myPlaces);

			dockList.hide();
			dockList.wrap('<div class="lfr-dock-list-container"></div>');

			var dockData = {
				dock: dock,
				dockList: dockList
			};

			dock.css(
				{
					cursor: 'pointer',
					position: 'absolute',
					zIndex: Liferay.zIndex.DOCK
				}
			);

			var dockOver = function(event) {
				event.data = dockData;

				jQuery(document).one(
					'click',
					function(internalEvent) {
						var currentEl = jQuery(internalEvent.target);
						var dockParent = currentEl.parents('.lfr-dock');

						if ((dockParent.length == 0) && !currentEl.is('.lfr-dock')) {
							instance._toggle(event, 'hide');
						}
					}
				);

				instance._toggle(event, 'show');
			};

			var dockOut = function(event) {
				event.data = dockData;

				instance._toggle(event, 'hide');
			};

			var myPlacesToggle = function(event) {
				event.data = myPlaces;

				instance._togglePlaces(event);
			};

			dock.hoverIntent(
				{
					interval: 0,
					out: dockOut,
					over: dockOver,
					timeout: 500
				}
			);

			myPlaces.hoverIntent(
				{
					interval: 0,
					out: myPlacesToggle,
					over: myPlacesToggle,
					timeout: 250
				}
			);

			myPlaces.find('.my-places-toggle, a[@href=javascript: ;]').click(
				function() {
					return false;
				}
			);

			if (Liferay.Browser.is_ie && Liferay.Browser.version() <= 6) {
				myPlaces.find('>ul').css('zoom', 1);
			}

			var dockParent = dock.parent();

			dockParent.css(
				{
					position: 'relative',
					zIndex: Liferay.zIndex.DOCK_PARENT
				}
			);

			instance._handleDebug();
		}
	},

	_handleDebug: function() {
		var instance = this;

		var dock = instance._dock;
		var dockList = instance._dockList;
		var myPlacesList = instance._myPlaces.find('> ul');

		if (dock.is('.debug')) {
			dock.show();
			dockList.show();
			dockList.addClass('expanded');
			myPlacesList.addClass('show-my-places');
		}
	},

	_hideCommunities: function(jQueryObj) {
		var myPlaces = jQueryObj;

		var communities = myPlaces.find('> ul > li');
		var communityList = communities.find('ul');
		var currentCommunity = communityList.find('li.current');
		var heading = communities.find('h3');

		heading.wrap('<div class="my-places-toggle"></div>');

		heading = heading.parent();

		communityList.hide();
		currentCommunity.parent().show();

		var currentCommunityHeading = currentCommunity.parent().prev();

		currentCommunityHeading.addClass('hide');

		heading.click(
			function() {
				var heading = jQuery(this);

				heading.next("ul").BlindToggleVertically("fast");
				heading.toggleClass('hide');
			}
		);
	},

	_toggle: function(event, state) {
		var params = event.data;

		var dock = params.dock;
		var dockList = params.dockList;

		if (state == 'hide') {
			dockList.hide();
			dock.removeClass('expanded');
		}
		else if (state == 'show') {
			dockList.show();
			dock.addClass('expanded');
		}
		else {
			dockList.toggle();
			dock.toggleClass('expanded');
		}
	},

	_togglePlaces: function(event) {
		var myPlaces = event.data;

		var myPlacesList = myPlaces.find('> ul');

		myPlacesList.toggleClass('show-my-places');

		if (Liferay.Browser.is_ie && Liferay.Browser.version() <= 6) {
			myPlacesList.find('li ul li').css('position', 'relative');
		}
	}
};