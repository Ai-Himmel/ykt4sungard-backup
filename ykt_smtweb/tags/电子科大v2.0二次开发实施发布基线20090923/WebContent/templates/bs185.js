<!--	


  function setTime(item,date1,time1,message){ 


	if(time1.value.length != 6){


  		alert(message + " ����ȷ�趨ʱ��"); 


  		return;


  	}  	 	  	 	


  	IsHour(time1.value.substring(0,2),message);


  	IsMin(time1.value.substring(2,4),message);


  	IsSec(time1.value.substring(4,6),message); 


  	if(date1.value.length == 0){


  		alert(message + " ��ѡ������"); 


  		return;


  	}  	 	
  	

  	item.value = date1.value + time1.value;  	  	


  }	  


  function IsHour(str,message)


  {


    if (IsNumber(str) && parseInt(str) >= 0 && parseInt(str) <= 24) return;


    alert(message + " Сʱ��Ч");


    event.returnValue = false;


  }





  function IsMin(str,message)


  {


    if (IsNumber(str) && str >= 0 && str <= 59) return;


    alert(message + " ������Ч");


    event.returnValue = false;


  }





  function IsSec(str,message)


  {


    if (IsNumber(str) && str >= 0 && str <= 59) return;


    alert(message + " ������Ч");


   event.returnValue = false;


  }


	


function OnTicketSelected()


{				


	document.select.submit();		


}


function OnSubmit()


{							


	if(!beforeSubmit())


		return;	


	document.order.submit();


}


function GotoGoodsCart()


{							


	document.order.action.value = "go_to_goodscart";


	document.order.nowurl.value = "http://localhost:7001/web/BusinessOrder.do?businessno=000023";


	document.order.submit();


}


function GotoOthers()


{							


	document.order.action.value = "go_to_others";


	document.order.submit();


}


function OnKeyDownInTextArea( item, maxlen ) {


   	if ( item.value.length > maxlen - 1 ) {


   		if ( event.keyCode != 8 && event.keyCode <= 32 || event.keyCode > 46 ) {


   		


	   		alert( "�ַ���̫��!" );  


	   		event.returnValue = false;





		}


	}


}


function IsNumber(s)


{


  var str = s;	  


  for (i=0; i<str.length; i++){


  	if (str.substring(i,i+1) < "0" || str.substring(i, i+1) > "9") return false;  		  	 


  }


  return true;


}		





function IsFloat(s)


{


  var str = s;


  var count = 0;


  for (i=0; i<str.length; i++)


  {


  	if (str.substring(i,i+1) < "0" || str.substring(i, i+1) > "9")


  	{


  		if(str.substring(i,i+1) == ".")


  		{


  		 if(i==0)


  		 	return false;


  		 count = count + 1;


  		 if(count > 1)


  		 	return false;


  		}


  		else


  			return false;


  	}


  }


  return true;


}





function CheckNumber(item,s){


	var str = item.value;


  	var returnvalue = s + " ������Ч����!";


  	if(!IsNumber(str)){


	  	alert(returnvalue);


	  	event.returnValue = false;


  	}	


}	





function CheckFloat(item,s){


	var str = item.value;


  	var returnvalue = s + " ������Ч�ĸ�����!";


  	if(!IsFloat(str)){


	  	alert(returnvalue);


	  	event.returnValue = false;


  	}	


}	


-->