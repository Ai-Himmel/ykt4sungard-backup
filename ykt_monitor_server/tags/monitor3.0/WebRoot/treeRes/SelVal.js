

function AddContent(p_aVal, p_aText, p_oSel)
{
	var nLength		= p_oSel.length;
	var nALen		= p_aText.length;
	var i, j;
	var bTag ;
	var sVal, sText ;

	for(i=0; i<nALen; i++)
	{
		bTag	= 0;
		sVal	= p_aVal[i];
		sText	= p_aText[i];
		
		for(j=0; j<nLength; j++)
		{
			if((sText==p_oSel.options[j].text) && (sVal==p_oSel.options[j].value)) 
			{
				bTag	= 1 ; 
				break;
			}
			if((sVal=="")||(sText=="")) 
			{
				bTag	= 1 ; 
				break;
			}
		}
		if(bTag == 0) 
		{
			p_oSel.options[nLength]	= new Option(sText,nLength);
			p_oSel.options[nLength].value	= sVal;
			nLength++;
		}
	}
}

function delContent(p_oSel)
{
	var nIndex	= p_oSel.selectedIndex;

	if(nIndex<1)
	{
		return ;			
	}
	else
	{
		var sText	= p_oSel.options[nIndex].text;
		if('----=全部取消=----' == sText) return;

		p_oSel.options[nIndex]	= null;
		p_oSel.selectedIndex	= -1;
	}
}

function delAllContent(p_oSel)
{
	p_oSel.length	= 1 ;
}


function moveUp(p_oSel)
{
	with (p_oSel)
	{
		if(1 == selectedIndex)
		{
			options[length]	= new Option(options[1].text,options[1].value) ;
			options[1]		= null ;
			selectedIndex	= length - 1 ;
		}
		else if(selectedIndex > 1) 
		{
			moveGo(p_oSel,-1) ;
		}
	}
}


function moveDown(p_oSel)
{
	with (p_oSel)
	{
		if(selectedIndex == (length-1) )
		{
			var i ;
			var sText	= options[selectedIndex].text ;
			var sVal	= options[selectedIndex].value ;

			for(i=selectedIndex; i>1; i--)
			{
				options[i].text		= options[i-1].text ;
				options[i].value	= options[i-1].value ;
			}
			options[i].text		= sText
			options[i].value	= sVal ;
			selectedIndex		= 1 ;
		}
		else if( (selectedIndex>0) && (selectedIndex<(length-1)) )
		{
			moveGo(p_oSel,+1) ;
		}
	}
}

function moveGo(p_oSel,nOffset)
{
	with (p_oSel)
	{
		nDesIndex	= selectedIndex + nOffset ;
		var sText	= options[nDesIndex].text ;
		var sVal	= options[nDesIndex].value ;
		options[nDesIndex].text		= options[selectedIndex].text ;
		options[nDesIndex].value	= options[selectedIndex].value ;
		options[selectedIndex].text		= sText ;
		options[selectedIndex].value	= sVal ;
		selectedIndex	= nDesIndex ;
	}
}
