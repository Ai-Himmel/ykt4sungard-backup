function Tree(treeId, nodes, icons, className, selectedItems) {
    this.nodes = nodes;
    this.treeId = treeId;
    this.icons = icons;
	this.className = className;
	this.openNodes = new Array();
	this.selectedItems = selectedItems;

    this.addNode = Tree_addNode;
    this.create = Tree_create;
    this.hasChildNode = Tree_hasChildNode;
    this.isNodeOpen = Tree_isNodeOpen;
    this.setOpenNodes = Tree_setOpenNodes;
    this.toggle = Tree_toggle;
    this.chooseOptions = Tree_chooseOptions;
    this.validateChooseOptions = Tree_validateChooseOptions;
    this.clickcheckbox = Tree_clickcheckbox;
}

function Tree_create(openNodes) {
	if (this.nodes.length > 0) {
		if (openNodes != null) {
			this.setOpenNodes(openNodes);
		}

		var nodeValues = this.nodes[0].split("|");
		
		document.write("<div style=\"visibility=hidden;position:absolute;\"><input type=checkbox name=idsallbox ");
		if (isChecked(this.selectedItems, nodeValues[6])) {
			document.write("checked");
		}
		document.write(" value=\"" + nodeValues[6]+ "\" id=box1 onclick=\"javascript:" + this.treeId + ".chooseOptions('box1')\"></div>");
		document.write("<a class=\"" + this.className + "\" style=\"text-decoration: none;\">");
			
		document.write("&nbsp;" + nodeValues[4] + "");
		document.write("</a><br>");
		document.write("<div id=\"" + this.treeId + "div" + nodeValues[0] + "\">");
		var recursedNodes = new Array();
		//this.addNode(0, recursedNodes);
		this.addNode(1, recursedNodes);
		document.write("</div>");
	}
}

function Tree_addNode(parentNode, recursedNodes) {
	for (var i = parentNode; i < this.nodes.length; i++) {
		var nodeValues = this.nodes[i].split("|");

		if (nodeValues[1] == parentNode) {
			var ls = false;
			if (nodeValues[2] == "1") {
				ls = true;
			}

			var hcn = this.hasChildNode(nodeValues[0]);
			var ino = this.isNodeOpen(nodeValues[0]);

			for (var j = 0; j < recursedNodes.length; j++) {
				if (recursedNodes[j] != 1) {
					document.write("<img align=\"absmiddle\" border=\"0\" height=\"20\" hspace=\"0\" src=\"" + this.icons[1] + "\" vspace=\"0\" width=\"19\">");
				}
				else {
					document.write("<img align=\"absmiddle\" border=\"0\" height=\"20\" hspace=\"0\" src=\"" + this.icons[2] + "\" vspace=\"0\" width=\"19\">");
				}
			}

			// Line and empty icons

			if (ls) {
				recursedNodes.push(0);
			}
			else {
				recursedNodes.push(1);
			}

			// Write out join icons

			if (hcn) {
				if (ls) {
					document.write("<a class=\"" + this.className + "\" href=\"javascript: " + this.treeId + ".toggle('" + this.treeId + "', " + nodeValues[0] + ", 1);\" style=\"text-decoration: none;\">");
					document.write("<img align=\"absmiddle\" border=\"0\" height=\"20\" hspace=\"0\" id=\"" + this.treeId + "join" + nodeValues[0] + "\" src=\"");

					if (ino) {
						document.write(this.icons[6]);	// minus_bottom.gif
					}
					else {
						document.write(this.icons[8]);	// plus_bottom.gif
					}

					document.write("\" vspace=\"0\" width=\"19\"></a>");
				}
				else {
					document.write("<a class=\"" + this.className + "\" href=\"javascript: " + this.treeId + ".toggle('" + this.treeId + "', " + nodeValues[0] + ", 0);\" style=\"text-decoration: none;\">");
					document.write("<img align=\"absmiddle\" border=\"0\" height=\"20\" hspace=\"0\" id=\"" + this.treeId + "join" + nodeValues[0] + "\" src=\"");

					if (ino) {
						document.write(this.icons[5]);	// minus.gif
					}
					else {
						document.write(this.icons[7]);	// plus.gif
					}

					document.write("\" vspace=\"0\" width=\"19\"></a>");
				}
			}
			else {
				if (ls) {
					document.write("<img align=\"absmiddle\" border=\"0\" height=\"20\" hspace=\"0\" src=\"" + this.icons[3] + "\" vspace=\"0\" width=\"19\">");
				}
				else {
					document.write("<img align=\"absmiddle\" border=\"0\" height=\"20\" hspace=\"0\" src=\"" + this.icons[4] + "\" vspace=\"0\" width=\"19\">");
				}
			}

			// Link
			//create checkbox
			document.write("<div style=\"visibility=hidden;position:absolute;\"><input type=checkbox ");
			if (isChecked(this.selectedItems, nodeValues[6])) {
				document.write("checked");
			}
			document.write(" name=ids id=\"box" + nodeValues[0] + "\" value=\"" + nodeValues[6]+ "\" onclick=\"javascript:" + this.treeId + ".chooseOptions('box" + nodeValues[0] + "');" + this.treeId + ".validateChooseOptions('box" + nodeValues[0] + "');\"></div>");
			
			document.write("<a class=\"" + this.className + "\" style=\"text-decoration: none;\">");
			

			document.write("&nbsp;");
			document.write(nodeValues[4]);
			document.write("</a><br>");

			// Recurse if node has children

			if (hcn) {
				document.write("<div id=\"" + this.treeId + "div" + nodeValues[0] + "\"");

				if (!ino) {
					document.write(" style=\"display: none;\"");
				}

				document.write(">");

				this.addNode(nodeValues[0], recursedNodes);

				document.write("</div>");
			} else {
				document.write("<div id=\"" + this.treeId + "div" + nodeValues[0] + "\" style=\"visibility=hidden;position:absolute;\"></div>");
			}

			// Pop last line or empty icon

			recursedNodes.pop();
		}
	}
}

function Tree_hasChildNode(parentNode) {
	if (parentNode >= this.nodes.length) {
		return false;
	}

	var nodeValues = this.nodes[parentNode].split("|");

	if (nodeValues[1] == parentNode) {
		return true;
	}

	return false;
}

function Tree_isNodeOpen(node) {
	for (i = 0; i < this.openNodes.length; i++) {
		if (this.openNodes[i] == node) {
			return true;
		}
	}

	return false;
}

function Tree_setOpenNodes(openNodes) {
	if (openNodes != null) {
		this.openNodes = openNodes.split(",");
	}
}

function Tree_toggle(treeId, node, bottom) {
	var divEl = document.getElementById(treeId + "div" + node);
	var joinEl	= document.getElementById(treeId + "join" + node);
	var iconEl = document.getElementById(treeId + "icon" + node);

	var openNode = false;

	if (divEl.style.display == "none") {
		if (bottom == 1) {
			joinEl.src = this.icons[6];	// minus_bottom.gif
		}
		else {
			joinEl.src = this.icons[5]; // minus.gif
		}

		//iconEl.src = this.icons[10];	// folder_open.gif
		divEl.style.display = "";

		openNode = true;
	}
	else {
		if (bottom == 1) {
			joinEl.src = this.icons[8];	// plus_bottom.gif
		}
		else {
			joinEl.src = this.icons[7]; // plus.gif
		}

		//iconEl.src = this.icons[9];		// folder.gif
		divEl.style.display = "none";
	}
	self.focus();
}

function Tree_chooseOptions(boxid) {
	var divEl;
	var checkstatus = document.getElementById(boxid).checked;
	divEl = document.getElementById(this.treeId + "div" + boxid.substring(3));
	var selfImage = document.getElementById("boximage" + boxid.substring(3));
	if (checkstatus) {
		if (endsWith(selfImage.src, this.icons[13])) {
			selfImage.src = this.icons[12];
		}
	} else {
		if (endsWith(selfImage.src, this.icons[12])) {
			selfImage.src = this.icons[13];
		}
	}
	if (!divEl) {
		return;
	}	
	var allChilds = divEl.all;
	for (var i = 0; i < allChilds.length; i++){
		var element = allChilds.item(i);
		if (element.type == 'checkbox' && element.checked != checkstatus) {
			element.checked = checkstatus;
			//set image
			var imageElem = document.getElementById("boximage" + element.id.substring(3));

			if (checkstatus) {					
				imageElem.src = this.icons[12];
			} else {
				imageElem.src = this.icons[13];
			}
		}
	}
}

function Tree_validateChooseOptions(boxid) {
	var divEl;
	var checkstatus = document.getElementById(boxid).checked;
	divEl = document.getElementById(this.treeId + "div" + boxid.substring(3));
	var parentDivEl = divEl.parentNode;	
	if (parentDivEl.id.indexOf(this.treeId + "div") != 0) {
		return;
	}		
	var parentNodeId = parentDivEl.id.substring(this.treeId.length + 3);
	var parentElement = document.getElementById("box" + parentNodeId);
	var allChilds = parentDivEl.all;
	var allChecked = true;
	for (var i = 0; i < allChilds.length; i++){
		var element = allChilds.item(i);
		if (element.type == 'checkbox' && !element.checked) {
			allChecked = false;
			break;
		}
	}
	
	parentElement.checked = allChecked;
	//set image
	var imageElem = document.getElementById("boximage" + parentElement.id.substring(3));
	if (allChecked) {
		imageElem.src = this.icons[12];
	} else {
		imageElem.src = this.icons[13];
	}
	this.validateChooseOptions(parentElement.id);	
}

function Tree_clickcheckbox(boxid) {
	 var box = document.getElementById(boxid);
	 box.click();
}

if (!Array.prototype.push) {
	function array_push() {
		for(var i = 0; i < arguments.length; i++) {
			this[this.length] = arguments[i];
		}

		return this.length;
	}

	Array.prototype.push = array_push;
}

function endsWith(str, x) {
	if (str.lastIndexOf(x) == str.length - x.length) {
		return true;
	}
	else {
		return false;
	}
}

function isChecked(formatstr, indexstr) {
	if (formatstr.indexOf(',') == -1) {
		return formatstr == indexstr;
	}
	if (formatstr.indexOf(',' + indexstr + ',') != -1 || 
		formatstr.indexOf(indexstr + ',') == 0 || 
		endsWith(formatstr, ',' + indexstr)) {
		return true;
	}
	return false;
}

if (!Array.prototype.pop) {
	function array_pop(){
		lastElement = this[this.length - 1];
		this.length = Math.max(this.length - 1, 0);

		return lastElement;
	}

	Array.prototype.pop = array_pop;
}