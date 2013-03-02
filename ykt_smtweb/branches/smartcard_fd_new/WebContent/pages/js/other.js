function document.onkeydown(){         
     
      //enter
      if(event.keyCode==13)
       {
            document.getElementById("send").click();  
            return false;                              
       }
       //esc
      if(event.keyCode==27)
      {
            document.getElementById("back").click();
            return false;
      }
      //????
      if(event.keyCode==38)
      {
            document.getElementById("previce").click();
            return false;
      }
      //????
      if(event.keyCode==40)
      {
            document.getElementById("next").click();
            return false;
      }    
   
     }
  
  function GetHeader(src) { 
		  var ForReading=1; 
          var fso=new ActiveXObject("Scripting.FileSystemObject"); 
          var f=fso.OpenTextFile(src,ForReading); 
          return(f.ReadAll()); 
   } 
  function   readfile(){
	      var arr=GetHeader("c:\\smartcard.txt").split("\r\n");
	      if(arr !=null && arr.length>0){
	       // alert(arr[0].substring(arr[0].indexOf("=")+1,arr[0].length));
	        return  arr[0].substring(arr[0].indexOf("=")+1,arr[0].length);
	      }else{
	        return "";
	      }
  }
  


  
