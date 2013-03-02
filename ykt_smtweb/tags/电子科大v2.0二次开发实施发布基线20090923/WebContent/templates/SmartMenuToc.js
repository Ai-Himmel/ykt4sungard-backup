//////////////////////////////////////////////

// Cross DHTML TOC

// SmartMenuToc.js

// COPYRIGHT ADVANTYS 1999

// Last modified : August 19 1999

//////////////////////////////////////////////





// SmartMenuToc_toc

// Constructor	 

function SmartMenuToc_toc(tocName)

{ 

	// Data member

	//////////////////////////////

	this.name= tocName

	this.doc = document 

	this.rootNode = 0	

	this.nodesIndex = new Array 

	this.nodesCounter = 0 	

	this.currentTopPos = 0

	this.showRoot = true 

	this.showIcons =true

	this.showTextLinks = true 

	if (this.doc.all) 

		this.browserVersion = 1 

	else 

		if (this.doc.layers) 

			this.browserVersion = 2 

		else	 

			this.browserVersion = 0 

	

	// Styles

	this.styleItemFolderLink=0

	this.styleItemFolderNoLink=0

	this.styleItemLink=0

	this.styleItemNoLink=0



	// Icons

	this.iconPath					= "/images"

	this.iconWidth					= "24"

	this.iconHeight					= "22"

	this.iconPlus					= this.iconPath + "/plus.gif"

	this.iconMinus					= this.iconPath + "/minus.gif"

	this.iconPlus1					= this.iconPath + "/plus1.gif"

	this.iconPlus2					= this.iconPath + "/plus2.gif"

	this.iconMinus1					= this.iconPath + "/minus1.gif"

	this.iconMinus2					= this.iconPath + "/minus2.gif"

	this.iconItem					= this.iconPath + "/item.gif"

	this.iconFolderCollapsed		= this.iconPath + "/foldercol.gif"

	this.iconFolderExpanded			= this.iconPath + "/folderexp.gif"

	this.iconEmpty					= this.iconPath + "/empty.gif"

	this.iconLine1					= this.iconPath + "/line1.gif"

	this.iconLine2					= this.iconPath + "/line2.gif"

	this.iconLine3					= this.iconPath + "/line3.gif"



	// Methods

	this.display		= SmartMenuToc_tocDisplay	

	this.makeFolder		= SmartMenuToc_tocmakeFolder

	this.makeItem		= SmartMenuToc_tocmakeItem

	this.insertNode		= SmartMenuToc_tocInsertNode

	this.nodeClicked	= SmartMenuToc_tocnodeClicked	

	this.expand			= SmartMenuToc_tocExpand

	this.expandAll		= SmartMenuToc_tocExpandAll	

	this.collapseAll	= SmartMenuToc_tocCollapseAll



}



// SmartMenuToc_tocDisplay

// Display the Toc

function SmartMenuToc_tocDisplay(startNode,expandLevel) 

{   

	this.rootNode = startNode



	if (!this.showIcons){

		this.iconPlus1			= this.iconPlus

		this.iconPlus2			= this.iconPlus

		this.iconMinus			= this.iconMinus

		this.iconMinus1			= this.iconMinus		

		this.iconMinus2			= this.iconMinus				

		this.iconLine3			= this.iconEmpty	

	}



	if (this.browserVersion == 2) 

		this.doc.write("<ILAYER position='relative' id='" + this.name +"'>\n")   



	this.rootNode.initialize(0, 1, '') 

	this.rootNode.display()



	if (this.browserVersion == 2) 

		this.doc.write("</ILAYER>\n")   



	if (this.browserVersion > 0){ 	

		 this.rootNode.expand(expandLevel)				 		 

	} 	

} 



// SmartMenuToc_tocmakeFolder

// Create a folder

function SmartMenuToc_tocmakeFolder(description,href,target,icon) 

{ 

	newFolder = new SmartMenuToc_folder(this,description,href,target,icon) 

	return newFolder ;

} 



// SmartMenuToc_tocmakeItem

// Create a item

function SmartMenuToc_tocmakeItem(description, href,target,icon) 

{ 	

	newItem = new SmartMenuToc_item(this,description, href,target,icon)           

	return newItem

} 



// insertNode

// Insert a item

function SmartMenuToc_tocInsertNode(parentFolder, nodeToInsert) 

{ 

	return parentFolder.addChild(nodeToInsert)   

} 





// nodeClicked

// Event

function SmartMenuToc_tocnodeClicked(nodeId) 

{ 

	var clickedNode = this.nodesIndex[nodeId] 

	clickedNode.setState(!clickedNode.isExpanded) 

} 



// SmartMenuToc_tocExpandAll

// 

function SmartMenuToc_tocExpandAll() 

{ 

	this.rootNode.expandAll();

} 





// SmartMenuToc_tocExpand

// 

function SmartMenuToc_tocExpand(maxlevel) 

{ 

	this.rootNode.expand(maxlevel);

} 





// SmartMenuToc_tocCollapseAll

// 

function SmartMenuToc_tocCollapseAll() 

{ 		

	this.expand(1)

}









// SmartMenuToc_folder

// Constructor

function SmartMenuToc_folder(activeToc,description,href,target,icon) 

{ 

	// Data member

	this.id = -1   

	this.toc = activeToc

	this.desc = description

	this.href = href

	this.target = target

	this.layer = 0  

	this.iconSrc = this.toc.iconFolderExpanded

	this.iconPersoSrc = icon

	if (icon)

		this.iconSrc = this.iconPersoSrc

	this.iconImg = 0  

	this.nodeImg = 0  

	this.isLastNode = 0 

	this.isExpanded = true   

	this.isFolder = true   

	this.children = new Array 

	this.childrensCounter = 0 



	// Methods

	this.initialize		= SmartMenuToc_folderInitialize 

	this.setState		= SmartMenuToc_folderSetState 

	this.addChild		= SmartMenuToc_folderAddChild 

	this.createIndex	= SmartMenuToc_createIndex 

	this.hide			= SmartMenuToc_folderHide 

	this.display		= SmartMenuToc_display 

	this.draw			= SmartMenuToc_folderDraw 

	this.totalHeight	= SmartMenuToc_totalHeight 

	this.subEntries		= SmartMenuToc_folderSubEntries 

	this.outputLink		= SmartMenuToc_folderOutputLink 

	this.expand			= SmartMenuToc_folderExpand

	this.expandAll		= SmartMenuToc_folderExpandAll

	this.expandRec		= SmartMenuToc_folderExpandRec

} 



// SmartMenuToc_folderInitialize

// 

function SmartMenuToc_folderInitialize(level, lastNode, leftSide) 

{ 

	var j=0 

	var i=0 

	var numberOfFolders 

	var numberOfDocs 

	var nc 

	

	nc = this.childrensCounter 



	this.createIndex() 



	if (level==0 && !this.toc.showRoot) {

		   

	}

	else {

	   var auxEv = '' 

	   if (this.toc.browserVersion > 0) 

		 auxEv ="<a href='javascript:" + this.toc.name +".nodeClicked("+this.id+")'>" 

	   else 

		 auxEv = "<a>"

		 

	   if (level>0)

		 if (lastNode) //the last 'brother' in the children array 

		 { 

		   this.draw(leftSide + auxEv + "<img name='" + this.toc.name + "nodeIcon" + this.id + "' src='" + this.toc.iconMinus1 + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + " border=0></a>")

		   leftSide = leftSide + "<img src='" + this.toc.iconEmpty + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">" 

		   this.isLastNode = 1 

		 } 

		 else 

		 { 

		   this.draw(leftSide + auxEv + "<img name='" + this.toc.name + "nodeIcon" + this.id + "' src='" + this.toc.iconMinus2 + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + " border=0></a>") 

		   leftSide = leftSide + "<img src='" + this.toc.iconLine3 + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">" 

		   this.isLastNode = 0 

		  } 

	   else 

		 this.draw('') 

	}



	if (nc > 0) 

	{ 

	 level = level + 1 

	 for (i=0 ; i < this.childrensCounter; i++)  

	 { 

	   if (i == this.childrensCounter-1) 

		 this.children[i].initialize(level, 1, leftSide) 

	   else 

		 this.children[i].initialize(level, 0, leftSide) 

	  } 

	}    

} 



// SmartMenuToc_folderDraw

// 

function SmartMenuToc_folderDraw(leftSide) 

{ 

	if (this.toc.browserVersion == 2) { 

		if (!this.toc.currentTopPos) 

			this.toc.currentTopPos=8 

		this.toc.doc.write("<layer postion='absolute' id='" + this.toc.name + "folder" + this.id + "' top=" + this.toc.currentTopPos + " visibility=hidden>\n") 

	} 



	this.toc.doc.write("<table ") 

	if (this.toc.browserVersion == 1) 

		this.toc.doc.write(" id='" + this.toc.name + "folder" + this.id + "' style='position:block;' ")   

	this.toc.doc.write(" border=0 cellspacing=0 cellpadding=0>\n") 



	this.toc.doc.write('<tr><td>') 

	this.toc.doc.write(leftSide) 

	if (this.toc.showIcons){

		this.outputLink() 

		this.toc.doc.write("<img name='" + this.toc.name + "folderIcon" + this.id + "' ") 

		this.toc.doc.write("src='" + this.iconSrc + "' border=0></a>") 

	}

	this.toc.doc.write('</td><td valign=middle nowrap>') 

	if (this.toc.showTextLinks && this.href){ 

		this.outputLink() 

		this.toc.doc.write(this.desc + '</a>') 		

	} 

	else 

		this.toc.doc.write("<font class='" + this.toc.styleItemFolderNoLink + "'>" + this.desc + "</font>")



	this.toc.doc.write('</td>')  

	this.toc.doc.write("</table>\n") 



	if (this.toc.browserVersion == 2) { 

		this.toc.doc.write("</layer>\n\n") 

	} 



	if (this.toc.browserVersion == 1) { 

		this.layer  = eval(this.toc.name + "folder" + this.id)	

		if (this.toc.showIcons)

			this.iconImg = eval(this.toc.name + "folderIcon"+ this.id)	

		if (this.id>0)

			  this.nodeImg = eval(this.toc.name + "nodeIcon" + this.id) 			

	} 

	if (this.toc.browserVersion == 2) { 

		this.layer  = eval("document." + this.toc.name +".document." + this.toc.name + "folder"+this.id);

		if (this.toc.showIcons)

			this.iconImg = this.layer.document.images[this.toc.name +"folderIcon"+this.id] 

		if (this.id>0)

			this.nodeImg = this.layer.document.images[this.toc.name +"nodeIcon"+this.id] ;

		this.toc.currentTopPos=this.toc.currentTopPos+this.layer.clip.height 

	} 

} 





// SmartMenuToc_folderOutputLink

// 

function SmartMenuToc_folderOutputLink() 

{ 

	if (this.toc.browserVersion > 0) 		

		if (this.href)

			this.toc.doc.write("<a class='" + this.toc.styleItemFolderLink + "' href='" + this.href +  "' target='" + this.target + "'>") 		

} 



// SmartMenuToc_folderSetState

// Change the state of a folder

function SmartMenuToc_folderSetState(isExpanded) 

{ 

	var subEntries 

	var totalHeight 

	var fIt = 0 

	var i=0 



	if (isExpanded == this.isExpanded) 

		return 



	if (this.toc.browserVersion == 2){ 

		totalHeight = 0 

		for (i=0; i < this.childrensCounter; i++) 

			totalHeight = totalHeight + this.children[i].layer.clip.height 

		subEntries = this.subEntries() 

		if (this.isExpanded) 

			totalHeight = 0 - totalHeight 

		for (fIt = this.id + subEntries + 1; fIt < this.toc.nodesCounter; fIt++) 

			this.toc.nodesIndex[fIt].layer.moveBy(0, totalHeight) 

	}  

	this.isExpanded = isExpanded 

	SmartMenuToc_applyChanges(this) 

} 





// hide folder

// 

function SmartMenuToc_folderHide() 

{ 

	if (this.toc.browserVersion >0) { 

	  if (this.toc.browserVersion == 1) { 

		if (this.layer.style.display == 'none') 

		  return 

		this.layer.style.display = 'none'

	  } else { 

		if (this.layer.visibility == 'hidden') 

		  return 

		this.layer.visibility = 'hidden'

	  } 

	  this.setState(0) 

	}

} 





// SmartMenuToc_folderAddChild

// 

function SmartMenuToc_folderAddChild(childNode) 

{ 

	this.children[this.childrensCounter] = childNode 

	this.childrensCounter++ 

	return childNode 

} 



// SmartMenuToc_folderSubEntries

// 

function SmartMenuToc_folderSubEntries() 

{ 

	var i = 0 

	var se = this.childrensCounter 

	for (i=0; i < this.childrensCounter; i++){ 

		if (this.children[i].children)

		  se = se + this.children[i].subEntries() 

	} 

	return se 

} 







// SmartMenuToc_folderExpandAll

// 

function SmartMenuToc_folderExpandAll() 

{ 		

	this.expand(1000)

}



// SmartMenuToc_folderExpand

// 

function SmartMenuToc_folderExpand(maxLevel) 

{ 		

	if (this.isExpanded)

		this.toc.nodeClicked(this.id)

	var currentLevel = 1

	if (maxLevel)

		this.expandRec(maxLevel,currentLevel)

	else

		this.expandRec(1,currentLevel)

}



// SmartMenuToc_folderExpand

// 

function SmartMenuToc_folderExpandRec(maxlevel,currentlevel) 

{ 

	var i = 0 	

	this.toc.nodeClicked(this.id)

	if 	(currentlevel<maxlevel){	

		currentlevel++;

		for (i=0; i < this.childrensCounter; i++){ 

			if (this.children[i].isFolder)						

						this.children[i].expandRec(maxlevel,currentlevel) 		

		} 

	}	

} 







// SmartMenuToc_item

// Constructor

function SmartMenuToc_item(activeToc, description, href,target,icon)

{ 

	// Data member

	this.id = -1 

	this.toc = activeToc

	this.desc = description 

	this.href = href 

	this.target = target  

	this.layer = 0 

	this.iconImg = 0 

	this.iconSrc = this.toc.iconItem 

	if (icon)

	this.iconSrc = icon



	// Methods

	this.initialize		= SmartMenuToc_itemInitialize 

	this.draw			= SmartMenuToc_itemDraw 

	this.hide			= SmartMenuToc_itemHide 

	this.createIndex	= SmartMenuToc_createIndex   

	this.display		= SmartMenuToc_display   

	this.totalHeight	= SmartMenuToc_totalHeight 

} 



// SmartMenuToc_itemInitialize

// 

function SmartMenuToc_itemInitialize(level, lastNode, leftSide) 

{  

	this.createIndex() 

	if (level>0) 

		if (lastNode){ 

			if (this.toc.showIcons) {  

				this.draw(leftSide + "<img src='" + this.toc.iconLine1 + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">")

				leftSide = leftSide + "<img src='" + this.toc.iconEmpty + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">"  

				}

			else 

				this.draw(leftSide +"<img src='" + this.toc.iconEmpty + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">") 

		} 

		else { 

		   if (this.toc.showIcons) {  

				this.draw(leftSide + "<img src='" + this.toc.iconLine2 + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">") 

				leftSide = leftSide + "<img src='" + this.toc.iconLine3 + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">" 

			    } 

		   else 

				this.draw(leftSide +"<img src='" + this.toc.iconEmpty + "' width=" + this.toc.iconWidth + " height=" + this.toc.iconHeight + ">")

		} 

	else

		this.draw('')

} 



// SmartMenuToc_itemDraw

// 

function SmartMenuToc_itemDraw(leftSide) 

{ 

	if (this.toc.browserVersion == 2) 

		this.toc.doc.write("<layer postion='absolute' id='" + this.toc.name + "item" + this.id + "' top=" + this.toc.currentTopPos + " visibility=hidden>\n") 



	this.toc.doc.write("<table ") 

	if (this.toc.browserVersion == 1) 

		this.toc.doc.write(" id='" + this.toc.name + "item" + this.id + "' style='position:block;' ") 

	this.toc.doc.write(" border=0 cellspacing=0 cellpadding=0>\n") 



	this.toc.doc.write('<tr><td>') 



	this.toc.doc.write(leftSide) 

	if (this.toc.showIcons) {  

		if (this.href)

			this.toc.doc.write("<a href='" + this.href + "' target='" + this.target + "'>") 

		this.toc.doc.write("<img id='" + this.toc.name + "itemIcon" + this.id +"' src='"+ this.iconSrc +"' border=0>") 

		if (this.href)

			this.toc.doc.write('</a>') 

	}

	this.toc.doc.write('</td><td valign=middle nowrap>') 

	if (this.href && this.toc.showTextLinks) 

		this.toc.doc.write("<a class='" + this.toc.styleItemLink + "' href='" + this.href + "' target='" + this.target + "'>" + this.desc + "</a>") 

	else 

		this.toc.doc.write("<font class='" + this.toc.styleItemNoLink + "'>" + this.desc + "</font>")



	this.toc.doc.write("</table>\n") 



	if (this.toc.browserVersion == 2) 

		this.toc.doc.write("</layer>\n\n") 



	if (this.toc.browserVersion == 1) {  

		this.layer = eval(this.toc.name + "item" + this.id)

		if (this.toc.showIcons)

			this.iconImg = eval(this.toc.name + "itemIcon"+ this.id)        

	} 

	if (this.toc.browserVersion == 2) { 		

		this.layer = eval("document." + this.toc.name +".document." + this.toc.name + "item"+this.id);		

		this.iconImg = this.layer.document.images[this.toc.name + "itemIcon"+this.id] 

		this.toc.currentTopPos=this.toc.currentTopPos+this.layer.clip.height 

	} 

} 



// SmartMenuToc_itemHide

// 

function SmartMenuToc_itemHide() 

{ 

	if (this.toc.browserVersion >0) { 

		if (this.toc.browserVersion == 1) { 

			if (this.layer.style.display == 'none') 

			  return 

			this.layer.style.display = 'none' 

		} else { 

			if (this.layer.visibility == 'hidden') 

				return 

			this.layer.visibility = 'hidden' 

		}     

	}

} 





// SmartMenuToc_applyChanges

// 

function SmartMenuToc_applyChanges(folder) 

{   

	var i=0 

	if (folder.isExpanded){ 

	

		if (folder.nodeImg) 

			if (folder.isLastNode) 

				folder.nodeImg.src = folder.toc.iconMinus1

			else 

				folder.nodeImg.src = folder.toc.iconMinus2



		if (folder.iconPersoSrc)

			folder.iconImg.src =folder.iconPersoSrc

		else

			folder.iconImg.src = folder.toc.iconFolderExpanded



		for (i=0; i<folder.childrensCounter; i++) 

			folder.children[i].display() 

	} 

	else { 

		if (folder.nodeImg) 

			if (folder.isLastNode) 

				folder.nodeImg.src = folder.toc.iconPlus1 

			else 

				folder.nodeImg.src = folder.toc.iconPlus2



		if (folder.iconPersoSrc)

			folder.iconImg.src =folder.iconPersoSrc

		else

			folder.iconImg.src = folder.toc.iconFolderCollapsed



		for (i=0; i<folder.childrensCounter; i++) 

			folder.children[i].hide() 

	}  

} 



// SmartMenuToc_display

// 

function SmartMenuToc_display() 

{ 

	if (this.layer){

		if (this.toc.browserVersion == 1)

			this.layer.style.display = 'block' 

		else 

			this.layer.visibility = 'show' 

	}

} 



// SmartMenuToc_createIndex

// 

function SmartMenuToc_createIndex() 

{ 

	this.id = this.toc.nodesCounter       

	this.toc.nodesIndex[this.toc.nodesCounter] = this 

	this.toc.nodesCounter++    

} 



// SmartMenuToc_totalHeight

// 

function SmartMenuToc_totalHeight()

{ 

	var h = this.layer.clip.height 

	var i = 0 

	if (this.isExpanded)

		for (i=0 ; i < this.childrensCounter; i++)  

			h = h + this.children[i].SmartMenuToc_totalHeight() 

	return h 

} 





// END

