Liferay.Upload = new Class({
	/*
	 * PARAMETERS:
	 * allowedFileTypes (string) *Required - a comma seperated list of allowable filetypes
	 * container (jQuery Selector | DOM Element) *Required - container where the uploader will be placed
	 * maxFileSize (int) *Required - the maximum file size that can be uploaded
	 * uploadFile (string) *Required - the URL to where the file will be uploaded
	 *
	 * fallbackContainer (jQuery Selector | DOM Element) *Optional - the container holding a fallback (in case flash is not supported)
	 * namespace (string) *Optional - A unique string so that the global callback methods don't collide
	 * fileDescription (string) *Optional - a string describing what files can be uploaded
	 */
	initialize: function(params) {
		var instance = this;

		params = params || {};

		instance._container = jQuery(params.container);
		instance._fallbackContainer = jQuery(params.fallbackContainer || []);
		instance._namespaceId = params.namespace || '_liferay_pns_' + Liferay.Util.randomInt() + '_';
		instance._maxFileSize = params.maxFileSize || 0;
		instance._allowedFileTypes = params.allowedFileTypes;
		instance._uploadFile = params.uploadFile;

		instance._classicUploaderParam = 'uploader=classic';
		instance._newUploaderParam = 'uploader=new';

		// Check for an override via the query string

		var loc = location.href;

		if (loc.indexOf(instance._classicUploaderParam) > -1 && instance._fallbackContainer.length) {
			instance._fallbackContainer.show();

			if (!instance._fallbackIframe) {
				instance._fallbackIframe = instance._fallbackContainer.find('iframe[@id$=-iframe]');

				instance._fallbackIframe.height(300);
			}

			return;
		}

		// Language keys

		instance._browseText = Liferay.Language.get('browse-you-can-select-multiple-files');
		instance._cancelUploadsText = Liferay.Language.get('cancel-all-uploads');
		instance._cancelFileText = Liferay.Language.get('cancel-upload');
		instance._clearRecentUploadsText = Liferay.Language.get('clear-recent-uploads');
		instance._fileListPendingText = Liferay.Language.get('x-files-ready-to-be-uploaded', '0');
		instance._fileListText = Liferay.Language.get('file-list');
		instance._fileTypesDescriptionText = params.fileDescription || instance._allowedFileTypes;
		instance._uploadsCompleteText = Liferay.Language.get('all-uploads-complete');
		instance._uploadStatusText = Liferay.Language.get('uploading-file-x-of-x', ['[$POS$]','[$TOTAL$]']);
		instance._uploadFilesText = Liferay.Language.get('upload-files');

		if (instance._fallbackContainer.length) {
			instance._useFallbackText = Liferay.Language.get('use-the-classic-uploader');
			instance._useNewUploaderText = Liferay.Language.get('use-the-new-uploader');
		}

		instance._setupCallbacks();
		instance._setupUploader();
	},

	 fileAdded: function(file, listLength) {
		var instance = this;

		var listingFiles = instance._fileList;
		var listingUl = listingFiles.find('ul');

		if (!listingUl.length) {
			instance._listInfo.append('<h4>' + instance._fileListText + '</h4>');
			listingFiles.append('<ul></ul>');

			instance._uploadTarget.append(instance._clearUploadsButton);
			instance._clearUploadsButton.hide();

			instance._cancelButton.click(
				function() {
					instance.cancelUploads();
					instance._clearUploadsButton.hide();
				}
			);
		}

		instance._cancelButton.show();
		instance._uploadButton.show();

		listingFiles = listingFiles.find('ul');

		var fileId = instance._namespace(file.id);
		var fileName = file.name;

		var li = jQuery(
			'<li class="upload-file" id="' + fileId + '">' +
				'<span class="file-title">' + fileName + '</span>' +
				'<span class="progress-bar">' +
					'<span class="progress" id="' + fileId + 'progress"></span>' +
				'</span>' +
				'<a class="lfr-button cancel-button" href="javascript: ;" id="' + fileId+ 'cancelButton">' + instance._cancelFileText + '</a>' +
			'</li>');

		li.find('.cancel-button').click(
			function() {
				instance._uploader.cancelFile(file.id);
			}
		);

		var uploadedFiles = listingFiles.find('.upload-complete');

		uploadedFiles = uploadedFiles.filter(':first');

		if (uploadedFiles.length) {
			uploadedFiles.before(li);
		}
		else {
			listingFiles.append(li);
		}

		instance._updateList(listLength);
	},

	fileCancelled: function(file, listLength) {
		var instance = this;

		var fileId = instance._namespace(file.id);
		var fileName = file.name;
		var li = jQuery('#' + fileId);

		instance._updateList(listLength);

		li.fadeOut('slow');
	},

	flashLoaded: function() {
		var instance = this;

		instance._setupControls();
	},

	uploadStart: function(file, position, listLength) {
		var instance = this;

		var currentListText = instance._uploadStatusText.replace('[$POS$]', position).replace('[$TOTAL$]', listLength);
		var fileId = instance._namespace(file.id);

		instance._updateList(listLength, currentListText);

		var li = jQuery('#' + fileId);

		li.addClass('file-uploading');

		return true;
	},

	uploadProgress: function(file, bytesLoaded) {
		var instance = this;
		var fileId = instance._namespace(file.id);
		var progress = document.getElementById(fileId + 'progress');
		var percent = Math.ceil((bytesLoaded / file.size) * 100);

		progress.style.width = percent + '%';
	},

	uploadError: function(errno) {

		// SWFUpload.debug(errno);

	},

	fileUploadComplete: function(file) {
		var instance = this;

		var fileId = instance._namespace(file.id);
		var li = jQuery('#' + fileId);

		li.removeClass('file-uploading').addClass('upload-complete');
	},

	cancelUploads: function() {
		var instance = this;

		instance._uploader.cancelQueue();
		instance._uploadButton.hide();
		instance._cancelButton.hide();
	},

	uploadsComplete: function(file) {
		var instance = this;

		instance._cancelButton.hide();
		instance._updateList(0, instance._uploadsCompleteText);
		instance._uploadButton.hide();

		if (instance._clearUploadsButton.is(':hidden')) {
			instance._clearUploadsButton.show();
		}
	},

	_clearUploads: function() {
		var instance = this;

		var completeUploads = instance._fileList.find('.upload-complete');

		completeUploads.fadeOut('slow',
			function() {
				jQuery(this).remove();
			}
		);

		instance._clearUploadsButton.hide();
	},

	_namespace: function(txt) {
		var instance = this;

		txt = txt || '';

		return instance._namespaceId + txt;

	},

	_setupCallbacks: function() {
		var instance = this;

		// Global callback references

		instance._cancelUploads = instance._namespace('cancelUploads');
		instance._fileAdded = instance._namespace('fileAdded');
		instance._fileCancelled = instance._namespace('fileCancelled');
		instance._flashLoaded = instance._namespace('flashLoaded');
		instance._uploadStart = instance._namespace('uploadStart');
		instance._uploadProgress = instance._namespace('uploadProgress');
		instance._uploadError = instance._namespace('uploadError');
		instance._fileUploadComplete = instance._namespace('fileUploadComplete');
		instance._uploadsComplete = instance._namespace('uploadsComplete');
		instance._uploadsCancelled = instance._namespace('uploadsCancelled');

		// Global swfUpload var

		instance._swfUpload = instance._namespace('cancelUploads');

		window[instance._cancelUploads] = function() {
			instance.cancelUploads.apply(instance, arguments);
		};

		window[instance._fileAdded] = function() {
			instance.fileAdded.apply(instance, arguments);
		};

		window[instance._fileCancelled] = function() {
			instance.fileCancelled.apply(instance, arguments);
		};

		window[instance._uploadStart] = function() {
			instance.uploadStart.apply(instance, arguments);
		};

		window[instance._uploadProgress] = function() {
			instance.uploadProgress.apply(instance, arguments);
		};

		window[instance._uploadError] = function() {
			instance.uploadError.apply(instance, arguments);
		};

		window[instance._fileUploadComplete] = function() {
			instance.fileUploadComplete.apply(instance, arguments);
		};

		window[instance._uploadsComplete] = function() {
			instance.uploadsComplete.apply(instance, arguments);
		};

		window[instance._flashLoaded] = function() {
			instance.flashLoaded.apply(instance, arguments);
		};

	},

	_setupControls: function() {
		var instance = this;

		instance._uploadTargetId = instance._namespace('uploadTarget');
		instance._listInfoId = instance._namespace('listInfo');
		instance._fileListId = instance._namespace('fileList');

		instance._uploadTarget = jQuery('<div id="' + instance._uploadTargetId + '" class="float-container upload-target"></div>');
		instance._listInfo = jQuery('<div id="' + instance._listInfoId + '" class="upload-list-info"></div>');
		instance._fileList = jQuery('<div id="' + instance._fileListId + '" class="upload-list"></div>');
		instance._cancelButton = jQuery('<a class="lfr-button cancel-uploads" href="javascript: ;">' + instance._cancelUploadsText + '</a>');
		instance._clearUploadsButton = jQuery('<a class="lfr-button clear-uploads" href="javascript: ;">' + instance._clearRecentUploadsText + '</a>');

		instance._browseButton = jQuery('<a class="lfr-button browse-button" href="javascript: ;">' + instance._browseText + '</a>');
		instance._uploadButton = jQuery('<a class="lfr-button upload-button" href="javascript: ;">' + instance._uploadFilesText + '</a>');

		instance._container.prepend([instance._uploadTarget[0], instance._listInfo[0], instance._fileList[0]]);
		instance._uploadTarget.append([instance._browseButton[0], instance._uploadButton[0], instance._cancelButton[0]]);

		instance._clearUploadsButton.click(
			function() {
				instance._clearUploads();
			}
		);

		instance._browseButton.click(
			function() {
				instance._uploader.browse();
			}
		);

		instance._uploadButton.click(
			function() {
				instance._uploader.upload();
			}
		);

		instance._uploadButton.hide();
		instance._cancelButton.hide();

		if (instance._fallbackContainer.length) {
			instance._useFallbackButton = jQuery('<a class="use-fallback using-new-uploader" href="javascript: ;">' + instance._useFallbackText + '</a>');
			instance._fallbackContainer.after(instance._useFallbackButton);

			instance._useFallbackButton.click(
				function() {
					var fallback = jQuery(this);
					var newUploaderClass = 'using-new-uploader';
					var fallbackClass = 'using-classic-uploader';

					if (fallback.is('.' + newUploaderClass)) {
						instance._container.hide();
						instance._fallbackContainer.show();

						fallback.text(instance._useNewUploaderText);
						fallback.removeClass(newUploaderClass).addClass(fallbackClass);

						if (!instance._fallbackIframe) {
							instance._fallbackIframe = instance._fallbackContainer.find('iframe[@id$=-iframe]');

							instance._fallbackIframe.height(300);
						}

						var classicUploaderUrl = '';

						if (location.hash.length) {
							classicUploaderUrl = '&';
						}

						location.hash += classicUploaderUrl + instance._classicUploaderParam;
					}
					else {
						instance._container.show();
						instance._fallbackContainer.hide();
						fallback.text(instance._useFallbackText);
						fallback.removeClass(fallbackClass).addClass(newUploaderClass);

						location.hash = location.hash.replace(instance._classicUploaderParam, instance._newUploaderParam);
					}
				}
			);
		}
	},


	_setupUploader: function() {
		var instance = this;

		if (instance._allowedFileTypes.indexOf('*') == -1) {
			var fileTypes = instance._allowedFileTypes.split(',');

			fileTypes = jQuery.map(
				fileTypes,
				function(value, key) {
					var fileType = value;
					if (value.indexOf('*') == -1) {
						fileType = '*' + value;
					}
					return fileType;
				}
			);

			instance._allowedFileTypes = fileTypes.join(';');
		}

		instance._uploader = new SWFUpload({
			upload_script: instance._uploadFile,
			target: instance._uploadTargetId,
			flash_path: '/html/js/misc/swfupload/SWFUpload.swf',
			allowed_filesize: instance._maxFileSize,
			allowed_filetypes: instance._allowedFileTypes,
			allowed_filetypes_description: instance._fileTypesDescriptionText,
			browse_link_innerhtml: instance._browseText,
			upload_link_innerhtml: instance._uploadFilesText,
			browse_link_class: 'browse-button liferay-button',
			upload_link_class: 'upload-button liferay-button',
			flash_loaded_callback: instance._flashLoaded,
			upload_file_queued_callback: instance._fileAdded,
			upload_file_start_callback: instance._uploadStart,
			upload_progress_callback: instance._uploadProgress,
			upload_file_complete_callback: instance._fileUploadComplete,
			upload_file_cancel_callback: instance._fileCancelled,
			upload_queue_complete_callback: instance._uploadsComplete,
			upload_error_callback: instance._uploadError,
			upload_cancel_callback: instance._cancelUploads,
			auto_upload : false,
			upload_field_name: 'file',
			create_ui: true,
			debug: false
		});

		window[instance._swfUpload] = instance._uploader;
	},

	_updateList: function(listLength, message) {
		var instance = this;

		var infoTitle = instance._listInfo.find('h4');
		var listText = '';

		if (!message) {
			listText = instance._fileListPendingText;
			listText = listText.replace(/\d+/g, listLength);
		}
		else {
			listText = message;
		}

		infoTitle.html(listText);
	}
});