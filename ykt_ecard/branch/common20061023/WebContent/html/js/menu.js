var previousMenuId = "";
var mouseMenuId = "";

function menuMouseUp(e) {
	if (mouseMenuId != "") {
		hidePopUp(mouseMenuId);
	}
}

function menuOnMouseOut(id) {
	mouseMenuId = id;
}

function menuOnMouseOver(id) {
	mouseMenuId = "";
}

function hidePopUp(id) {
	var el = document.getElementById(id);
	el.style.visibility = "hidden";

	mouseMenuId = "";
}

function showPopUp(id) {
	var previousEl = document.getElementById(previousMenuId);

	if (previousEl != null) {
		hidePopUp(previousMenuId);
	}

	previousMenuId = id;

	var el = document.getElementById(id);

	if (is_mozilla) {
		el.style.left = mousePosX - 10;
		el.style.top = mousePosY - 10;
	}
	else {
		el.style.pixelLeft = mousePosX - 10;// - el.style.pixelLeft;
		el.style.pixelTop = mousePosY - 10;// - el.style.pixelTop;
	}

	el.style.visibility = "visible";
}