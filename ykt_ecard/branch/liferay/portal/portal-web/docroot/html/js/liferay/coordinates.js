/**********************************************************
 Very minorly modified from the example by Tim Taylor
 http://tool-man.org/examples/sorting.html

 Added Coordinate.prototype.inside( northwest, southeast );

 **********************************************************/


var Coordinates = {
	ORIGIN : new Coordinate(0, 0),

	coordinatesData: function(element, recurse) {
		var data = {};

		data.recurse = recurse;
		data.size = new Coordinate(element.offsetWidth, element.offsetHeight);
		data.nwOffset = Coordinates.northwestOffset(element, recurse);
		data.seOffset = data.nwOffset.plus(data.size);
		data.midPoint = data.nwOffset.plus(new Coordinate(Math.round(data.size.x/2), Math.round(data.size.y/2)));

		return data;
	},

	northwestPosition : function(element) {
		var x = parseInt(element.style.left);
		var y = parseInt(element.style.top);

		return new Coordinate(isNaN(x) ? 0 : x, isNaN(y) ? 0 : y);
	},

	southeastPosition : function(element) {
		return Coordinates.northwestPosition(element).plus(
				new Coordinate(element.offsetWidth, element.offsetHeight));
	},

	northwestOffset : function(element, isRecursive) {
		var offset = new Coordinate(element.offsetLeft, element.offsetTop);

		if (!isRecursive) return offset;

		var parent = element.offsetParent;
		while (parent) {
			offset = offset.plus(
					new Coordinate(parent.offsetLeft, parent.offsetTop));
			parent = parent.offsetParent;
		}
		return offset;
	},

	southeastOffset : function(element, isRecursive) {
		return Coordinates.northwestOffset(element, isRecursive).plus(
				new Coordinate(element.offsetWidth, element.offsetHeight));
	}
};

function Coordinate(x, y) {
	this.x = x || 0;
	this.y = y || 0;
}

Coordinate.prototype.toString = function() {
	return "(" + this.x + "," + this.y + ")";
};

Coordinate.prototype.plus = function(that) {
	return new Coordinate(this.x + that.x, this.y + that.y);
};

Coordinate.prototype.minus = function(that) {
	return new Coordinate(this.x - that.x, this.y - that.y);
};

Coordinate.prototype.distance = function(that) {
	var deltaX = this.x - that.x;
	var deltaY = this.y - that.y;

	return Math.sqrt(Math.pow(deltaX, 2) + Math.pow(deltaY, 2));
};

Coordinate.prototype.max = function(that) {
	var x = Math.max(this.x, that.x);
	var y = Math.max(this.y, that.y);
	return new Coordinate(x, y);
};

Coordinate.prototype.constrain = function(min, max) {
	if (min.x > max.x || min.y > max.y) return this;

	var x = this.x;
	var y = this.y;

	if (min.x != null) x = Math.max(x, min.x);
	if (max.x != null) x = Math.min(x, max.x);
	if (min.y != null) y = Math.max(y, min.y);
	if (max.y != null) y = Math.min(y, max.y);

	return new Coordinate(x, y);
};

Coordinate.prototype.reposition = function(element) {
	element.style["top"] = this.y + "px";
	element.style["left"] = this.x + "px";
};

Coordinate.prototype.equals = function(that) {
	if (this == that) return true;
	if (!that || that == null) return false;

	return this.x == that.x && this.y == that.y;
};

// returns true of this point is inside specified box
Coordinate.prototype.inside = function(northwest, southeast) {
	if ((this.x >= northwest.x) && (this.x <= southeast.x) &&
		(this.y >= northwest.y) && (this.y <= southeast.y)) {

		return true;
	}
	else {
		return false;
	}
};

Coordinate.prototype.insideObject = function(obj, recurse) {
	var data = Coordinates.coordinatesData(obj);
	data.recurse = recurse;
	data.quadrant = this.insideObjectData(data);

	return data.quadrant ? data : null;
};

Coordinate.prototype.insideObjectData = function(data) {
	var nwOffset = data.nwOffset;
	var seOffset = data.seOffset;
	var rt = 0;

	if (this.inside(nwOffset, seOffset)) {
		var mid = data.midPoint;

		if (this.x <= mid.x && this.y <= mid.y) {
			rt = 1;
		}
		else if (this.x >= mid.x && this.y <= mid.y) {
			rt = 2;
		}
		else if (this.x >= mid.x && this.y >= mid.y) {
			rt = 3;
		}
		else if (this.x <= mid.x && this.y >= mid.y) {
			rt = 4;
		}
	}

	return rt;
};

function MousePos () { };

// Extend the "Coordinate" class
MousePos.prototype = new Coordinate();

MousePos.prototype.update = function(event) {

	if (typeof event == 'undefined') {
		event = window.event;
	}

	var position = new Coordinate(event.clientX, event.clientY);

	var scrollOffset = Viewport.scroll();

	this.x = position.x + scrollOffset.x;
	this.y = position.y + scrollOffset.y;

	if (this.x < 0) this.x = 0;

	if (this.y < 0) this.y = 0;

	return event;
};

// Track mouse's absolute position (counting scrollbars)
var mousePos = new MousePos(0,0);

/*
 * jQuery extension
 */
jQuery.each([
				"coordinatesData",
				"northwestPosition",
				"southeastPosition",
				"northwestOffset",
				"southeastOffset"
			], function(i,n){

	jQuery.fn[ n ] = function(h) {
		return this.length > 0 ? Coordinates[n](this[0], h) : null;
	};
});

jQuery.fn.xySize = function() {
	return new Coordinate(this.width(), this.height());
};