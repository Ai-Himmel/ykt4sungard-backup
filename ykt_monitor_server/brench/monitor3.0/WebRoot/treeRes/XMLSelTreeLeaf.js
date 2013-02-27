/************************************************
** �ļ���:
** Copyright (c) 2003 
** ������:	moonpiazza
** �� ��:	2003.6.29
** �޸���:
** �� ��:
** �� ��:	XML�˵���
**
** �� ��:	1.0
************************************************/

var m_oConfig ;
function TreeConfig(p_sXSLFile, p_oSrcDiv, p_bAutoGoFisrtLeaf, p_bChangeLeafImg)
{


	this.bImgAsync		= true ;		// ���ͼ���ʱ���Ƿ�ѡ�иýڵ�
											// true:  ��ѡ�иýڵ�; 
											// false: ѡ�иýڵ�

	this.bShowElseBranch	= true ;		// �Ƿ�ֻ��ʾ��ǰ�˵���֦����Ĳ˵���֦
											// true:  ֻ��ʾ��ǰ1����֦������������֦; 
											// false: ��ʾ�Ѿ�չ���ķ�֦

	if (true == p_bChangeLeafImg)			// ��Ҷ�ڵ��ý��㣬�Ƿ�ı�ͼ��
		this.bChangeLeafImg	= true;					// true:  �ı�;              
	else									// false: ���ı�                
		this.bChangeLeafImg	= false;


	this.bDataAsync			= true ;		// �첽��ȡ����(ÿ���Ƿ񶼴��¶�������)
											// true:  ����; 
											// false: ��


	this.bCheckDataAsync	= true ;		// �첽��ȡ����(ÿ���Ƿ񶼴��¶�������)
											// true:  ����; 
											// false: ��


	this.bUseCheck			= true ;		// �Ƿ�����ѡ��

	this.sSelVal			= "" ;			// ѡ���ֵ
	this.oSrcDiv			= p_oSrcDiv ;	// 
	this.sCheckKey			= "," ;			// checkdata �ָ���

	this.bCheckAsync		= true;			// ���ڵ��ý��㣬�Ƿ�ѡ��
											// true:  ��ѡ��; 
											// false: ѡ��
	
	this.bCheckShowBranch	= false;		// ��֦�ڵ�ѡ�У��Ƿ�չ���ӽڵ�
											// true:  չ��; 
											// false: ��չ��

	if (true == p_bAutoGoFisrtLeaf)			// �Ƿ��Զ������ǰ�ڵ��µ�һ����'����'�Ľڵ�  
		this.bAutoGoFisrtLeaf	= true;		// true:  �Զ�;                
	else									// false: ���Զ�                
		this.bAutoGoFisrtLeaf	= false;


	this.bAutoScroll		= false ;

	this.oCurrentNode		= "moonpiazza" ;				// ��ǰ�ڵ�
	this.sLoadingText		= "Loading..." ;

	this.sClsMouseDown		= "clsMouseDown" ;	
	this.sClsMouseOver		= "clsMouseOver" ;
	this.sClsCurrentFocus	= "clsCurrentFocus"



	this.oXSLDoc = new ActiveXObject("Microsoft.XMLDOM") ;	// xsl�ĵ�������ʾxml����
	this.oXSLDoc.async = false ;
	this.oXSLDoc.load(p_sXSLFile) ;
}





/************************************************
** InitTree()
************************************************/
function InitTree(p_sXMLFile, p_sXSLPath, p_oSrcDiv, p_bAutoGoFisrtLeaf, p_bChangeLeafImg)
{

	var bIE	= (navigator.appName=="Microsoft Internet Explorer")?true:false ;

	if (!bIE) 
	{
		alert('������������IE�����,XMlSelTree��֧�ִ��������лл���֧�֣�');
		return false ;
	}
	var sXSLPath	= ("/" == (p_sXSLPath.charAt((p_sXSLPath.length-1))) ) ? p_sXSLPath:(p_sXSLPath + '/')
	var sXSLFile	= sXSLPath + GetXSLFileName() ;

	m_oConfig	= new TreeConfig(sXSLFile, p_oSrcDiv, p_bAutoGoFisrtLeaf, p_bChangeLeafImg) ;

	var oXMLDom	= new ActiveXObject("Microsoft.XMLDOM") ;
		oXMLDom.async	= false ;
		oXMLDom.load(p_sXMLFile) ;
		
	var sHtml	= oXMLDom.transformNode(m_oConfig.oXSLDoc) ;	
		
	p_oSrcDiv.innerHTML	= sHtml ;

	//if (m_oConfig.bAutoGoFisrtLeaf)
	//{
	//	GoFisrtLink( p_oSrcDiv.getElementsByTagName("DIV")[0] ) ;		
	//}	
}

/*************************************************************************
** GetXSLFileName()
*************************************************************************/
function GetXSLFileName()
{
	var sReturnVal ;
	var oAgent	= navigator.userAgent ;
	var fIEVersion	= parseFloat(oAgent.substring(oAgent.indexOf("MSIE ")+5, oAgent.indexOf(";",oAgent.indexOf("MSIE ")))) ;
	
	if (fIEVersion < 6)
	{
		sReturnVal	= "XMLSelTreeforIE5Leaf.xsl" ;
	}
	else
	{
		sReturnVal	= "XMLSelTreeLeaf.xsl" ;
	}

	return sReturnVal ;
}
/*************************************************************************
** selectstart()
*************************************************************************/
function selectstart()
{
	window.event.cancelBubble = true;
	window.event.returnValue = false;
	return false;
}

//-------------------------------------------------------------------------------------------------
//					���(����)���� GET (SET) FUNCTIONS		
//-------------------------------------------------------------------------------------------------


/*************************************************************************
** GetXML(p_sXMLSrc, p_oContainerElement, p_sContainerElementState)
*************************************************************************/
function GetXML(p_sXMLSrc, p_oContainerElement)
{
    var sHtml	= "" ;

	var oXMLDom	= new ActiveXObject("Microsoft.XMLDOM") ;
		oXMLDom.async	= false ;   
		oXMLDom.load(p_sXMLSrc) ;  

    if ( (oXMLDom != null) && (oXMLDom.xml != "") )
    {

        if (m_oConfig.oXSLDoc.xml != "")
        {
			sHtml	= oXMLDom.transformNode(m_oConfig.oXSLDoc) ;
        } 

        if ( (sHtml != null) && (sHtml != "") )
        {
            p_oContainerElement.innerHTML	= sHtml ;
            p_oContainerElement.className	= "shown" ;
        }
    }
}


/************************************************
** GetChildElement(p_oSrcElement, p_sType) 
** ���ܣ���λĳ�ڵ����ӽڵ����(�ӽڵ�����Ψһ:type)
************************************************/
function GetChildElement(p_oSrcElement, p_sType)
{
	var i	= 0 ;
	var oReturnValue	= null ;
	var oChildren		= null ;

	if(p_oSrcElement!=null)
	{
		oChildren	= p_oSrcElement.children ;
	}

	if (oChildren != null)
	{
		for (i=0; i < oChildren.length; i++)
		{
			if ( (oChildren[i].type==p_sType) || (p_sType == null) )
			{
				oReturnValue	= oChildren[i] ;
				break ;
			}
		}	
	}

	return oReturnValue ;
}


/************************************************
** GetParentElement(p_oSrcElement)
************************************************/
function GetParentElement(p_oSrcElement)
{
	var oReturnValue	= null ;

	if ( (p_oSrcElement!=null) && (p_oSrcElement.parentElement != null) )
	{
		oReturnValue	= p_oSrcElement.parentElement.parentElement ;
	}

	if ( (oReturnValue != null) && (oReturnValue.type!="branch") )
	{
		oReturnValue	= null ;
	}
	
	return oReturnValue ;
}


/************************************************
** GetImgSrc(p_sImgSrc, p_sType)
** ���ܣ����ͼ��·��
************************************************/
function GetImgSrc(p_sImgSrc, p_sType)
{
	var sReturnVal ;
	var aImgSrcInfo ;
	var sImgPath, sImgType ;
	
	aImgSrcInfo	= p_sImgSrc.split(".") ;
	sImgType	= aImgSrcInfo[ (aImgSrcInfo.length-1) ] ;

	sImgPath	= p_sImgSrc.substring(0, (p_sImgSrc.length - (sImgType.length + 2) ) ) ;

	sReturnVal	= sImgPath + p_sType + "." + sImgType ;

	return sReturnVal ;
}

/************************************************
** GoFisrtLink(p_oSrcElement)
************************************************/
function GoFisrtLink(p_oSrcElement)
{
	if (null == p_oSrcElement) return ;

	if (m_oConfig.oCurrentNode != "moonpiazza")
	{
		var oTag	= m_oConfig.oCurrentNode.getElementsByTagName("SPAN")[0];
		var oLink	= GetChildElement(oTag, "link") ;
		if (null != oLink) 	return ;
	}

	var oTag	= p_oSrcElement.getElementsByTagName("SPAN")[0];
	var oLink	= GetChildElement(oTag, "link") ;
	ShowHideNode(p_oSrcElement) ;
	SelectNode(p_oSrcElement) ;
	
	if (null != oLink) 
	{		
		return ;
	}
	else
	{
		oTag		= oTag.parentElement.getElementsByTagName("DIV")[1] ;
		GoFisrtLink(oTag);
	}
}


/************************************************
** GetAllCheckData()
** ���ܣ���ýڵ㷵��ֵ:CheckData
************************************************/

function GetAllCheckData()
{
	var sSelKey	= "#$#$#$" ;	// ���ݷָ���(��ʾֵtext������ֵvalue)
	
	var sReturnVal	= "";
	var i ;
	var sTmpVal ; 
	var sTmpText ; 
	var bEnsData ;

	var oCheck	= m_oConfig.oSrcDiv.getElementsByTagName("INPUT") ;
	var nLen	= oCheck.length ;	

	for (i=0; i<nLen; i++)
	{
		if (oCheck[i].checked)
		{
			sTmpVal		= oCheck[i].value;  
			sTmpText    = oCheck[i].text;
			if (('0' == oCheck[i].read) && ('' != oCheck[i].src) )
			{
				sTmpVal	= GetCheckUrlData(oCheck[i].src);
			}

			bEnsData	= ((m_oConfig.sCheckKey + sReturnVal + m_oConfig.sCheckKey).indexOf((m_oConfig.sCheckKey + sTmpVal + m_oConfig.sCheckKey)) > 0 ) ;

			if (!bEnsData)
			{
				sReturnVal += m_oConfig.sCheckKey + sTmpText + sSelKey + sTmpVal;
				//sReturnVal += m_oConfig.sCheckKey + sTmpVal ;
			}
		}
	}
	sReturnVal	= sReturnVal.replace(m_oConfig.sCheckKey, '');
	
	return sReturnVal ;
}


/************************************************
** SetCheck(p_oSrcElement, p_bAsync)
** ���ܣ�
************************************************/
function SetCheck(p_oSrcElement, p_bAsync)
{
	if (null == p_oSrcElement) return  ;
	
	SetChildrenCheck(p_oSrcElement, p_bAsync) ;
	SetParentElementCheck(p_oSrcElement) ;
	return  ;
}

/************************************************
** SetParentElementCheck(p_oSrcElement) 
** ���ܣ��踸���
************************************************/
function SetParentElementCheck(p_oSrcElement) 
{
	var bChecked	= p_oSrcElement.checked ;
	var oTargetNode	= p_oSrcElement.parentElement.parentElement ;

	if (bChecked)
	{
		var oCheck		= oTargetNode.getElementsByTagName("INPUT") ;
		var nLen		= oCheck.length ;	
		var i ;

		for (i=0; i<nLen; i++)
		{
			if (!oCheck[i].checked)
			{
//				return ;
			}
		}
	}else{
		var oCheck		= oTargetNode.getElementsByTagName("INPUT") ;
		var nLen		= oCheck.length ;	
		var i ;

		for (i=0; i<nLen; i++)
		{
			if (oCheck[i].checked)
			{
				return ;
			}
		}	
	}

	var oTargetNode		= GetChildElement(p_oSrcElement.parentElement.parentElement.parentElement, "checkbox") ;
		
	if (null != oTargetNode)
	{
//		if(bChecked)
			oTargetNode.checked =  bChecked ;
		SetParentElementCheck(oTargetNode) ;
	}

	return  ;
}
/************************************************
** SetChildrenCheck(p_oSrcElement, p_bAsync)
** ���ܣ�***
************************************************/
function SetChildrenCheck(p_oSrcElement, p_bAsync)
{

	var oContainerElement	= GetChildElement(p_oSrcElement.parentElement, "container") ;
	if (null == oContainerElement) return  ;

	var i ;
	var bChecked	= p_oSrcElement.checked ;
	var oCheck		= oContainerElement.getElementsByTagName("INPUT") ;
	var nLen		= oCheck.length ;		
	
	if ( (p_bAsync) && (bChecked) )
	{
		for (i=0; i<nLen; i++)
		{
			oCheck[i].checked = true; 
		}		
	}
	else
	{		
		for (i=0; i<nLen; i++)
		{
			oCheck[i].checked = bChecked; 
		}		
	}

	return  ;
}


/************************************************
** SetOneCheckData(p_oSrcElement)
** ���ܣ���õ�ǰ�ڵ㷵��ֵ:CheckData
************************************************/
function SetOneCheckData(p_oSrcElement)
{
	var sReturnVal		= "";
	var sVal			= p_oSrcElement.value ;
	var sCheckDataSrc	= p_oSrcElement.src ;
	
	if ( (sVal.length < 1) || (!m_oConfig.bCheckDataAsync) )
	{
		sReturnVal	= GetCheckUrlData(sCheckDataSrc) ;
			
		p_oSrcElement.value	= sReturnVal ;
	}

	return  ;
}

/************************************************
** GetCheckUrlData(p_sURL)
** ���ܣ����URL����ֵ:CheckData
************************************************/
function GetCheckUrlData(p_sURL)
{
	var sReturnVal	= "";
	var oXMLHttp	= new ActiveXObject ("Microsoft.XMLHTTP");
		oXMLHttp.Open("get", p_sURL, false);
		oXMLHttp.Send("");

	sReturnVal	= oXMLHttp.responseText;

	return sReturnVal ;
}

//-------------------------------------------------------------------------------------------------
//					�ڵ��¼� (����״̬�ı�)
//-------------------------------------------------------------------------------------------------

/************************************************
** SelectNode(p_oSrcElement)
************************************************/
function SelectNode(p_oSrcElement)
{
	UpdateMessages(p_oSrcElement) ;
	HighlightNode(p_oSrcElement) ;
	LoadNodeContent(p_oSrcElement) ;    
    ScrollIntoView(p_oSrcElement) ;  
	
	if ( (m_oConfig.bUseCheck) && (!m_oConfig.bCheckAsync) )
	{
		var oTargetNode	= GetChildElement(p_oSrcElement, "checkbox") ;
		if (null != oTargetNode)
		{			
			oTargetNode.click();
		}
	}
}


/************************************************
** HighlightNode(p_oSrcElement)
************************************************/
function HighlightNode(p_oSrcElement)
{
    var oNewLabel ;
	var oOldLabel ;

	oNewLabel	= GetChildElement(p_oSrcElement, "label") ;
	
	if (m_oConfig.bChangeLeafImg)
	{
		var cType	= p_oSrcElement.type;		

		if (cType == "leaf")
		{
			oImg		= GetChildElement(p_oSrcElement, "img") ;
			oImg.src	= GetImgSrc(oImg.src,3) ;	// �ı�ͼ��
		}

		if ( (m_oConfig.oCurrentNode != "moonpiazza") && (p_oSrcElement != m_oConfig.oCurrentNode) )
		{
			if (m_oConfig.oCurrentNode.type == "leaf")
			{
				oImg		= GetChildElement(m_oConfig.oCurrentNode, "img") ;
				oImg.src	= GetImgSrc(oImg.src,0) ;	// �ı�ͼ��				
			}		
		}
	}

	if (oNewLabel != null)
    {
		oNewLabel.className	= m_oConfig.sClsCurrentFocus ;
		oNewLabel.classType	= m_oConfig.sClsCurrentFocus ;

		if ( (m_oConfig.oCurrentNode != "moonpiazza") && (p_oSrcElement != m_oConfig.oCurrentNode) )
		{
				oOldLabel	= GetChildElement(m_oConfig.oCurrentNode, "label") ;

				if (oOldLabel != null)
				{
					oOldLabel.className	= "" ;
					oOldLabel.classType	= "" ;
				}
		}
		
		m_oConfig.oCurrentNode	= p_oSrcElement ;
	}
}


/************************************************
** UpdateMessages(p_oSrcElement)
************************************************/
function UpdateMessages(p_oSrcElement)
{
    oLabel	= GetChildElement(p_oSrcElement, "label") ;
    if(oLabel != null)
    {
        window.defaultStatus	= oLabel.caption ;
        //top.document.title	= oLabel.title ;
    }
}


/************************************************
** LoadNodeContent(p_oSrcElement)
************************************************/
function LoadNodeContent(p_oSrcElement)
{
    var oLabel ;
    var oLink ;

    oLabel = GetChildElement(p_oSrcElement, "label") ;

    if (oLabel != null)
    {
        oLink	= GetChildElement(oLabel, "link")
        if (oLink != null)
        {

            var sHref		= String(oLink.href) ;

			if(oLink.target)
            {
				GoLink(sHref, oLink.target) ;
            }
        }
    }
}


/************************************************
** ScrollIntoView(p_oSrcElement)
************************************************/
function ScrollIntoView(p_oSrcElement)
{
	if (m_oConfig.bAutoScroll)
	{
		var nY = p_oSrcElement.offsetTop - (window.document.body.clientHeight / 2) ;
		var nX = p_oSrcElement.offsetLeft - 15 ;
		window.scrollTo(nX, nY) ;
	}
}



//-------------------------------------------------------------------------------------------------
//		�ڵ��¼� (����ڵ����ݶ�ȡ����ʾ������)
//-------------------------------------------------------------------------------------------------

/************************************************
** FoldElseBranch(p_oSrcElement)
************************************************/
function FoldElseBranch(p_oSrcElement)
{
	if (m_oConfig.oCurrentNode == p_oSrcElement)
	{
		return ;
	}

	if (m_oConfig.oCurrentNode != "moonpiazza")
	{
		var bIsAncestorNode		= false;
		var bIsOffspringNode	= false;

			bIsAncestorNode		= IsAncestorNode(m_oConfig.oCurrentNode, p_oSrcElement) ;

		if ( !bIsAncestorNode )
		{
			bIsOffspringNode	= IsAncestorNode(p_oSrcElement, m_oConfig.oCurrentNode) ;

			if ( !bIsOffspringNode )
			{
				FoldOffspringNode(p_oSrcElement.parentElement) ;			// ��������ڵ�

				FoldNode(m_oConfig.oCurrentNode) ;							// ��������

				FoldAncestorNode(p_oSrcElement, m_oConfig.oCurrentNode);		// �������Ƚڵ�		
			}
		}


	}	
}


/************************************************
** FoldOffspringNode(p_oSrcElement)
************************************************/
function FoldOffspringNode(p_oSrcElement)
{				
	var i	= 0 ;
	var oChildren ;
	oChildren	= p_oSrcElement.children ;

	if (oChildren != null)
	{
		for (i=0; i < oChildren.length; i++)
		{
			FoldNode( oChildren[i] ) ;
			if (oChildren[i].type == "branch")
			{
				var oContainerElement = GetChildElement(oChildren[i], "container") ;

				FoldOffspringNode(oContainerElement) ;
			}

		}
	}
}


/*************************************************************************
** FoldAncestorNode(p_oSrcElement, p_oTargetNode)
*************************************************************************/
function FoldAncestorNode(p_oSrcElement, p_oTargetNode)
{				
	var oSrcParentNode	= GetParentElement(p_oSrcElement) ;
	var oTargetNode		= GetParentElement(p_oTargetNode) ;
		
	while (oTargetNode != null)
	{
		if (oTargetNode == oSrcParentNode) 
		{
			break ;
		}
		FoldNode(oTargetNode) ;
		
		oTargetNode	= GetParentElement(oTargetNode) ;
	}		
}



/************************************************
** ShowHideNode(p_oSrcElement)
************************************************/
function ShowHideNode(p_oSrcElement)
{

	if (p_oSrcElement.state == "shown")
	{
		FoldNode(p_oSrcElement) ;
	}
	else
	{
		if (!m_oConfig.bShowElseBranch)
		{
			FoldElseBranch(p_oSrcElement) ;
		}

		OutspreadNode(p_oSrcElement) ;		
	}

}


/************************************************
** FoldNode(p_oSrcElement)
************************************************/
function FoldNode(p_oSrcElement)
{
	var oContainerElement ;
	var oImg ;

	oContainerElement = GetChildElement(p_oSrcElement, "container") ;

	if (oContainerElement != null)
	{
		oImg	= GetChildElement(p_oSrcElement, "img") ;

		p_oSrcElement.state			= "hidden" ;

		oContainerElement.className	= "hide" ;

		oImg.src	= GetImgSrc(oImg.src,1) ;	// �ı�ͼ��
		
	 
		if (IsAncestorNode(m_oConfig.oCurrentNode, p_oSrcElement)==true)
		{
			SelectNode(p_oSrcElement) ;
		}
	}
}


/************************************************
** IsAncestorNode(p_oSrcElement, p_oTargetNode)
************************************************/
function IsAncestorNode(p_oSrcElement, p_oTargetNode)
{
	var oTmpElement ;
	var bReturnValue	= false ;

	oTmpElement	= GetParentElement(p_oSrcElement) ;

	while (oTmpElement != null)
	{
		if (oTmpElement == p_oTargetNode)
		{
			bReturnValue	= true ;
			break ;
		}

		oTmpElement	= GetParentElement(oTmpElement) ;
	}

	return bReturnValue ;
}


/************************************************
** OutspreadNode(p_oSrcElement)
************************************************/
function OutspreadNode(p_oSrcElement)
{
	var oContainerElement ;
	var oImg ;
	var oLabel ;

	oContainerElement	= GetChildElement(p_oSrcElement, "container") ;
	
	if (oContainerElement != null)
	{
		oImg	= GetChildElement(p_oSrcElement, "img") ;

		if (oImg != null)
		{
			p_oSrcElement.state			= "shown" ;

			oContainerElement.className	= "shown" ;

			oImg.src	= GetImgSrc(oImg.src,2) ;	// �ı�ͼ��

			if (!m_oConfig.bDataAsync)
			{
				var i;			
				var oDivContainer	= oContainerElement.getElementsByTagName("Div") ;
				var nLen	= oDivContainer.length;
				for (i=0; i<nLen; i++)
				{
					if ('shown' == oDivContainer[i].state)
					{
						//oDivContainer[i].parentElement.state	= "hidden" ;
						FoldNode(oDivContainer[i]);
					}
				}
			}

			LoadChildren(p_oSrcElement) ;
		}
	}
}


/************************************************
** LoadChildren(p_oSrcElement)
************************************************/
function LoadChildren(p_oSrcElement)
{
    var cXMLSrc ;
    var oLabel ;
    var oContainerElement	= GetChildElement(p_oSrcElement, "container") ;

    if (oContainerElement != null)
    {
		oLabel = GetChildElement(p_oSrcElement, "label")
		
	    if ( (oContainerElement.children.length == 0) || ( (!m_oConfig.bDataAsync) && (oContainerElement.children.length > 0) ) )
        {       
            if (oLabel != null)
            {
                cXMLSrc	= oLabel.xmlsrc ;
                GetXML(cXMLSrc, oContainerElement) ;
				//return true ;
            }            
        }

		if (m_oConfig.bUseCheck)
		{
			var oTargetNode	= GetChildElement(p_oSrcElement, "checkbox") ;
			if (null != oTargetNode)
			{
				SetChildrenCheck(oTargetNode, false) ;
			}
		}
    }

    return  ;
}



//-------------------------------------------------------------------------------------------------
//					Mouse �¼� (Click) and (Down, Over, Out)
//-------------------------------------------------------------------------------------------------

/************************************************
** MouseClick(p_oSrcElement)
************************************************/
function MouseClick(p_oSrcElement)
{
	var sSrcElementType	= p_oSrcElement.type ;
	var oTargetNode		= p_oSrcElement.parentElement ;

	if (sSrcElementType == "label")
	{
		ShowHideNode(oTargetNode) ;
		SelectNode(oTargetNode) ;	

		if (m_oConfig.bAutoGoFisrtLeaf)
		{
			var	oParentElement		= GetParentElement(p_oSrcElement) ;
			var oContainerElement	= GetChildElement(p_oSrcElement.parentElement, "container") ;
			if (null != oContainerElement)
				GoFisrtLink(oContainerElement.getElementsByTagName("DIV")[0]) ;
		}	
		
		return ;
	}
    else if(sSrcElementType == "img")
    {		
		if (oTargetNode.type == "leaf")
		{
			ShowHideNode(oTargetNode) ;
			SelectNode(oTargetNode) ;
		}
		else
		{
			if (m_oConfig.bImgAsync) 
			{
				ShowHideNode(oTargetNode) ;
			}
			else
			{				
				ShowHideNode(oTargetNode) ;
				SelectNode(oTargetNode) ;
			}
			
		}

		return ;
	}
    else if(sSrcElementType == "checkbox")
    {
		if (m_oConfig.bCheckShowBranch)
		{
			MouseClick(GetChildElement(p_oSrcElement.parentElement, "label"));
		}

		if (!m_oConfig.bCheckAsync)
		{
			oTargetNode	= p_oSrcElement.parentElement ;
			SelectNode(oTargetNode) ;
		}

		if ("" != p_oSrcElement.src)
		{
			SetOneCheckData(p_oSrcElement);	
		}

		SetCheck(p_oSrcElement, true) ;

		return ;
	}
}


/************************************************
** Mouse �¼� (Down, Over, Out)
** NodeMouseDown(p_oSrcElement)
** NodeMouseOver(p_oSrcElement)
** NodeMouseOut(p_oSrcElement)
** ChangeNodeCls(p_oSrcElement, p_sClassName)
************************************************/
function NodeMouseDown(p_oSrcElement)
{
	return ChangeNodeCls(p_oSrcElement, m_oConfig.sClsMouseDown) ;
}

function NodeMouseOver(p_oSrcElement)
{
	return ChangeNodeCls(p_oSrcElement, m_oConfig.sClsMouseOver) ;
}

function NodeMouseOut(p_oSrcElement)
{
	return ChangeNodeCls(p_oSrcElement, "") ;
}

function ChangeNodeCls(p_oSrcElement, p_sClassName)
{
	if (p_sClassName == "")
	{
		p_oSrcElement.className	= p_oSrcElement.classType ;
	}
	else
	{
		p_oSrcElement.className	= p_sClassName ;
	}			

	return true ;
}


