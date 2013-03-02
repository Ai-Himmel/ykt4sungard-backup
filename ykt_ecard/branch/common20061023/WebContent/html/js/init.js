//
// Capture mouse clicks
//

document.onmouseup = getMouseUp;

function getMouseUp(e) {
	menuMouseUp(e);

	return true;
}

//
// Capture mouse positions
//

if (!is_ie) {
	document.captureEvents(Event.MOUSEMOVE)
}

document.onmousemove = getMouseXY;

var mousePosX = 0;
var mousePosY = 0;

function getMouseXY(e) {
	if (is_ie) {
		mousePosX = event.clientX + document.body.scrollLeft;
		mousePosY = event.clientY + document.body.scrollTop;
	}
	else {
		mousePosX = e.pageX;
		mousePosY = e.pageY;
	}

	if (mousePosX < 0) {
		mousePosX = 0;
	}

	if (mousePosY < 0) {
		mousePosY = 0;
	}

	return true;
}