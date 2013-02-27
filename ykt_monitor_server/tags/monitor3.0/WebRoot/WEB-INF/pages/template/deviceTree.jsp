<%@ page pageEncoding="GBK" %>
<HTML>
<HEAD>
<TITLE> XMLSelTree(V1.0) ==> 选择菜单 </TITLE>
<META NAME="Author" CONTENT="moonpiazza">
<META NAME="Keywords" CONTENT="xml,xsl,moonpiazza,XMLSelTree,选择菜单">
<META NAME="Description" CONTENT="xml,xsl,moonpiazza,XMLSelTree,选择菜单">
<META http-equiv=Content-Type content="text/html; charset=gbk">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<META HTTP-EQUIV="Cache-Control" CONTENT="no-cache">
<META HTTP-EQUIV="Expires" CONTENT="0">
<link rel="stylesheet" type="text/css" href="treeRes/XMLSelTree.css">

</HEAD>
<BODY  topmargin="0" leftmargin="5" marginheight="0" marginwidth="0" text="#000000" >
<DIV id="SrcDiv"></DIV>
</BODY>
</HTML>

<SCRIPT LANGUAGE=javascript src="treeRes/XMLSelTree.js"></SCRIPT>
<SCRIPT LANGUAGE=javascript>
<!--
//var m_sXMLFile	= document.getElementById("xml").value;
//var m_sXMLFile	= "treeRes/TreeNode.xml";
var templateId = <%=request.getAttribute("templateId")%>;
var m_sXMLFile	= "termdevTemplate.do?method=getDeviceXmlTree&templateId="+templateId;
var m_sXSLPath	= "treeRes/";
var m_oSrcDiv	= SrcDiv;							// HTML标记(菜单容器，菜单在此容器显示)


function window.onload()
{
	InitTree(m_sXMLFile, m_sXSLPath, m_oSrcDiv);
}


/************************************************
** GoLink(p_sHref, p_sTarget)
************************************************/
function GoLink(p_sHref, p_sTarget)
{
	var sHref	= p_sHref;
	var sTarget	= p_sTarget;
	window.open(sHref, sTarget);
}
/************************************************
** 子设备被选中时，父设备可以不被选中
************************************************/
function SetParentElementCheck(p_oSrcElement) {
}
/************************************************
**父设备被选中时，disabled的子设备不被选中
************************************************/
function SetChildrenCheck(p_oSrcElement, p_bAsync) {
    var oContainerElement = GetChildElement(p_oSrcElement.parentElement, "container");
    if (null == oContainerElement) return;

    var i;
    var bChecked = p_oSrcElement.checked;
    var oCheck = oContainerElement.getElementsByTagName("INPUT");
    var nLen = oCheck.length;

    if ((p_bAsync) && (bChecked)){
        for (i = 0; i < nLen; i++){
            if(oCheck[i].disabled==false){
                oCheck[i].checked = true;
            }
        }
    }else{
        for (i = 0; i < nLen; i++){
            oCheck[i].checked = bChecked;
        }
    }
    return;
}
//-->
</SCRIPT>

