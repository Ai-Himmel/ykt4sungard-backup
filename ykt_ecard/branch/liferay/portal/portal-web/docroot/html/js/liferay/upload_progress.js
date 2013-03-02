function UploadProgress(uploadProgressId, redirect) {
	this.uploadProgressId = uploadProgressId;
	this.redirect = decodeURIComponent(redirect);
	this.count = 0;
	this.currentPercent = 0;
	this.currentSpeed = 0.1;
	this.startTime = 0;

	this.animateBar = UploadProgress_animateBar;
	this.hideProgress = UploadProgress_hideProgress;
	this.sendRedirect = UploadProgress_sendRedirect;
	this.startProgress = UploadProgress_startProgress;
	this.updateBar = UploadProgress_updateBar;
	this.updateIFrame = UploadProgress_updateIFrame;
	this.updateProgress = UploadProgress_updateProgress;
}

function UploadProgress_animateBar(percent) {
	this.count++
	this.currentPercent = percent;

	var barContainer = document.getElementById(this.uploadProgressId + "-bar-div");
	var progressBar = document.getElementById(this.uploadProgressId + "-bar");
	var progressText = progressBar.getElementsByTagName("div")[1];

	barContainer.style.display = "block";

	if (percent < 100) {
		progressBar.style.width = percent + "%";
		progressText.innerHTML = Math.round(percent) + "%";

		setTimeout(this.uploadProgressId + ".animateBar(" + (percent + this.currentSpeed) + ")", 100);
	}
	else {
		progressBar.style.width = "100%";
		progressText.innerHTML = "Done";

		setTimeout(this.uploadProgressId + ".hideProgress()", 1000);
	}
}

function UploadProgress_hideProgress() {
	var barContainer = document.getElementById(this.uploadProgressId + "-bar-div");

	barContainer.style.display = "none";
}

function UploadProgress_sendRedirect() {
	window.location = this.redirect;
}

function UploadProgress_startProgress() {
	var barContainer = document.getElementById(this.uploadProgressId + "-bar-div");
	var timeLeftText = barContainer.getElementsByTagName("span")[0];

	var d = new Date();

	this.count = 0;
	this.currentPercent = 0;
	this.currentSpeed = 0.01;
	this.startTime = d.getTime();

	this.animateBar(0);

	setTimeout(this.uploadProgressId + ".updateProgress()", 1000);
}

function UploadProgress_updateBar(percent, filename) {
	var barContainer = document.getElementById(this.uploadProgressId + "-bar-div");
	var timeLeftText = barContainer.getElementsByTagName("span")[0];

	var d = new Date();

	var elapsedTime = d.getTime() - this.startTime;
	var countLeft = this.count * (100 / percent - 1);
	var timeLeft = elapsedTime * (100 / percent - 1);
	var minLeft = Math.floor(timeLeft / 60000);

	if (countLeft > 0) {
		this.currentSpeed = (100 - percent) / countLeft;
	}
	else {
		this.currentSpeed = 100;
	}
}

function UploadProgress_updateIFrame(height) {
	var uploadPollerIFrame = document.getElementById(this.uploadProgressId + "-iframe");

	uploadPollerIFrame.height = height + 20;

	jQuery(uploadPollerIFrame.contentWindow.document.body).height(height);
}

function UploadProgress_updateProgress() {
	var uploadProgressPoller = document.getElementById(this.uploadProgressId + "-poller");

	uploadProgressPoller.src = themeDisplay.getPathMain() + "/portal/upload_progress_poller?uploadProgressId=" + this.uploadProgressId;
}