
function DoClear(){
  
   document.all.enrollNo.value="";   
   document.all.studentNo.value="";
   document.all.gender[2].checked=true; 
   document.all.majorin.options[0].selected=true;
   document.all.s_classNo.options[0].selected=true; 
       
   
   document.all.henrollNo.value="";
   document.all.hstudentNo.value="";
   document.all.hmajorin.value="";   
   document.all.hgender.value="";
   document.all.hclassNo.value="";
   
   document.all.f_ifNeed.checked=false;     
   document.all.f_ifCheckedin.checked=false;
   document.all.f_ifChecked.checked=false;
   document.all.f_ifGotMaterial.checked=false;
   document.all.f_ifGotEcard.checked=false;
   document.all.f_ifGotStucard.checked=false;
   
   document.all.fh_ifNeed.value=='0'
   document.all.fh_ifCheckedin.value="";
   document.all.fh_ifChecked.value="";
   document.all.fh_ifGotMaterial.value="";
   document.all.fh_ifGotEcard.value="";
   document.all.fh_ifGotStucard.value="";
   
}

function document.onkeydown()
{
	var e=event.srcElement;
	if(event.keyCode==13)
	{
		DoFind();
		return false;
	}
}

function DoFind(){  

   document.forms[0].elements["pager.offset"].value="0"; 
  
   document.all.henrollNo.value=document.all.enrollNo.value;
   document.all.hstudentNo.value=document.all.studentNo.value;
   
   for(var i=0;i<document.all.gender.length;i++){
       if(document.all.gender[i].checked)
            document.all.hgender.value=document.all.gender[i].value;
   
   }  
   
   if(document.all.f_ifNeed.checked)
       document.all.fh_ifNeed.value="1";
   else
       document.all.fh_ifNeed.value="0"; 
   
   document.all.hmajorin.value=document.all.majorin.value;   
   document.all.hclassNo.value=document.all.s_classNo.value; 
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=find";
   document.stucheckininfoForm.submit();
   
}

init();

function init(){

   var sflag=1;
  
   if(document.all.ck_ifCheckedin!=null&&document.all.ck_ifCheckedin.length>1){
          for(var i=0;i<document.all.ck_ifCheckedin.length;i++){
              if(!document.all.ck_ifCheckedin[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall1.checked=true;
          }
       } 
    sflag=1;
    if(document.all.ck_ifChecked!=null&&document.all.ck_ifChecked.length>1){
          for(var i=0;i<document.all.ck_ifChecked.length;i++){
              if(!document.all.ck_ifChecked[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall2.checked=true;
          }
    } 
    sflag=1;
    if(document.all.ck_ifGotMaterial!=null&&document.all.ck_ifGotMaterial.length>1){
          for(var i=0;i<document.all.ck_ifGotMaterial.length;i++){
              if(!document.all.ck_ifGotMaterial[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall3.checked=true;
          }
    }     
    sflag=1;
    if(document.all.ck_ifGotEcard!=null&&document.all.ck_ifGotEcard.length>1){
          for(var i=0;i<document.all.ck_ifGotEcard.length;i++){
              if(!document.all.ck_ifGotEcard[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall4.checked=true;
          }
    } 
    sflag=1;
     if(document.all.ck_ifGotStucard!=null&&document.all.ck_ifGotStucard.length>1){
          for(var i=0;i<document.all.ck_ifGotStucard.length;i++){
              if(!document.all.ck_ifGotStucard[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall5.checked=true;
          }
       } 
    

}

function f1(ckb){
    if(ckb.checked)
        document.all.fh_ifCheckedin.value="1";
    else if(!ckb.checked)
        document.all.fh_ifCheckedin.value="0";
    else
        document.all.fh_ifCheckedin.value="";
}

function f2(ckb){
    if(ckb.checked)
        document.all.fh_ifChecked.value="1";
    else if(!ckb.checked)
        document.all.fh_ifChecked.value="0";
    else
        document.all.fh_ifChecked.value="";
}

function f3(ckb){
    if(ckb.checked)
        document.all.fh_ifGotMaterial.value="1";
    else if(!ckb.checked)
        document.all.fh_ifGotMaterial.value="0";
    else
        document.all.fh_ifGotMaterial.value="";
}

function f4(ckb){
    if(ckb.checked)
        document.all.fh_ifGotEcard.value="1";
    else if(!ckb.checked)
        document.all.fh_ifGotEcard.value="0";
    else
        document.all.fh_ifGotEcard.value="";
}

function f5(ckb){
    if(ckb.checked)
        document.all.fh_ifGotStucard.value="1";
    else if(!ckb.checked)  
        document.all.fh_ifGotStucard.value="0";  
    else
        document.all.fh_ifGotStucard.value="";
}

function f6(ckb){
if(ckb.checked){
   document.all.fh_ifNeed.value="1"; 
   document.all.f_ifCheckedin.checked=false;
   document.all.f_ifChecked.checked=false;
   document.all.f_ifGotMaterial.checked=false;
   document.all.f_ifGotEcard.checked=false;
   document.all.f_ifGotStucard.checked=false;    
   
   document.all.fh_ifCheckedin.value="0";
   document.all.fh_ifChecked.value="0";
   document.all.fh_ifGotMaterial.value="0";
   document.all.fh_ifGotEcard.value="0";
   document.all.fh_ifGotStucard.value="0";     
   } 
else{       
   document.all.f_ifCheckedin.checked=false;
   document.all.f_ifChecked.checked=false;
   document.all.f_ifGotMaterial.checked=false;
   document.all.f_ifGotEcard.checked=false;
   document.all.f_ifGotStucard.checked=false;
   
   document.all.fh_ifNeed.value=='0'
   document.all.fh_ifCheckedin.value="";
   document.all.fh_ifChecked.value="";
   document.all.fh_ifGotMaterial.value="";
   document.all.fh_ifGotEcard.value="";
   document.all.fh_ifGotStucard.value="";       
  }
}


function DoSelect(cb){

   var sflag=1;;
   var usflag=1;;
  
   if(cb.checked){
   
       document.all.updateid.value=cb.value;       

       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(!document.all.cbgroup[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall.checked=true;
          }
       } 
   }
   
   if(!cb.checked){
       document.all.checkall.checked=false;
       if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall.checked=false;
              document.all.updateid.value="";
          }
       } 
   }
   
}

function DoCheckall(ckall){
   
   if(ckall.checked){
   
      if(document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       document.all.updateid.value=document.all.cbgroup[document.all.cbgroup.length-1].value;
       }
       else{
          document.all.cbgroup.checked=true;
          document.all.updateid.value =document.all.cbgroup.value;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.cbgroup.length>1){
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       document.all.updateid.value="";
      }
      else{
         document.all.cbgroup.checked=false;
         document.all.updateid.value="";
      }
   }   

}

function DoCheckall1(ckall){

    if(ckall.checked){
   
      if(document.all.ck_ifCheckedin.length>1){   
       for(var i=0;i<document.all.ck_ifCheckedin.length;i++){
              if(document.all.ck_ifCheckedin[i].checked==false)
                  document.all.ck_ifCheckedin[i].click();
              document.all.ck_ifCheckedin[i].checked=true;
       }       
       }
       else{
          if(document.all.ck_ifCheckedin.checked==false)
              document.all.ck_ifCheckedin.click();
          document.all.ck_ifCheckedin.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ifCheckedin.length>1){
       for(var i=0;i<document.all.ck_ifCheckedin.length;i++){
            if(document.all.ck_ifCheckedin[i].checked==true)
                document.all.ck_ifCheckedin[i].click();
            document.all.ck_ifCheckedin[i].checked=false;
       }
      }
      else{
         if(document.all.ck_ifCheckedin.checked==true)
             document.all.ck_ifCheckedin.click();
         document.all.ck_ifCheckedin.checked=false;
      }
   }

}

function DoCheckall2(ckall){
   
   if(ckall.checked){
   
      if(document.all.ck_ifChecked.length>1){   
       for(var i=0;i<document.all.ck_ifChecked.length;i++){
            if(document.all.ck_ifChecked[i].checked==false)
                  document.all.ck_ifChecked[i].click();
              document.all.ck_ifChecked[i].checked=true;
       }       
       }
       else{
         if(document.all.ck_ifChecked.checked==false)
                  document.all.ck_ifChecked.click();
          document.all.ck_ifChecked.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ifChecked.length>1){
       for(var i=0;i<document.all.ck_ifChecked.length;i++){
           if(document.all.ck_ifChecked[i].checked==true)
                  document.all.ck_ifChecked[i].click();
              document.all.ck_ifChecked[i].checked=false;
       }
      }
      else{
        if(document.all.ck_ifChecked.checked==true)
                  document.all.ck_ifChecked.click();
         document.all.ck_ifChecked.checked=false;
      }
   }

}

function DoCheckall3(ckall){
   
   if(ckall.checked){
   
      if(document.all.ck_ifGotMaterial.length>1){   
       for(var i=0;i<document.all.ck_ifGotMaterial.length;i++){
           if(document.all.ck_ifGotMaterial[i].checked==false)
                  document.all.ck_ifGotMaterial[i].click();
              document.all.ck_ifGotMaterial[i].checked=true;
       }       
       }
       else{
             if(document.all.ck_ifGotMaterial.checked==false)
                  document.all.ck_ifGotMaterial.click();
             document.all.ck_ifGotMaterial.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ifGotMaterial.length>1){
       for(var i=0;i<document.all.ck_ifGotMaterial.length;i++){
           if(document.all.ck_ifGotMaterial[i].checked==true)
                  document.all.ck_ifGotMaterial[i].click();
              document.all.ck_ifGotMaterial[i].checked=false;
       }
      }
      else{
        if(document.all.ck_ifGotMaterial.checked==true)
                  document.all.ck_ifGotMaterial.click();
         document.all.ck_ifGotMaterial.checked=false;
      }
   }

}

function DoCheckall4(ckall){
   
    if(ckall.checked){
   
      if(document.all.ck_ifGotEcard.length>1){   
       for(var i=0;i<document.all.ck_ifGotEcard.length;i++){
            if(document.all.ck_ifGotEcard[i].checked==false)
                  document.all.ck_ifGotEcard[i].click();
              document.all.ck_ifGotEcard[i].checked=true;
       }       
       }
       else{
         if(document.all.ck_ifGotEcard.checked==false)
                  document.all.ck_ifGotEcard.click();
          document.all.ck_ifGotEcard.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ifGotEcard.length>1){
       for(var i=0;i<document.all.ck_ifGotEcard.length;i++){
           if(document.all.ck_ifGotEcard[i].checked==true)
                  document.all.ck_ifGotEcard[i].click();
              document.all.ck_ifGotEcard[i].checked=false;
       }
      }
      else{
         if(document.all.ck_ifGotEcard.checked==true)
                  document.all.ck_ifGotEcard.click();
          document.all.ck_ifGotEcard.checked=false;
      }
   }

}

function DoCheckall5(ckall){
   
      if(ckall.checked){
   
      if(document.all.ck_ifGotStucard.length>1){   
       for(var i=0;i<document.all.ck_ifGotStucard.length;i++){
           if(document.all.ck_ifGotStucard[i].checked==false)
                  document.all.ck_ifGotStucard[i].click();
              document.all.ck_ifGotStucard[i].checked=true;
       }       
       }
       else{
           if(document.all.ck_ifGotStucard.checked==false)
                  document.all.ck_ifGotStucard.click();
           document.all.ck_ifGotStucard.checked=true;
       }
   }
   else if(ckall.checked==false){
   
      if(document.all.ck_ifGotStucard.length>1){
       for(var i=0;i<document.all.ck_ifGotStucard.length;i++){
            if(document.all.ck_ifGotStucard[i].checked==true)
                  document.all.ck_ifGotStucard[i].click();
              document.all.ck_ifGotStucard[i].checked=false;
       }
      }
      else{
          if(document.all.ck_ifGotStucard.checked==true)
                  document.all.ck_ifGotStucard.click();
          document.all.ck_ifGotStucard.checked=false;
      }
   }

}

function DoCheck1(ck,hid){
    
   var sflag=1;
   var usflag=1;  
   //alert(hid);
   if(ck.checked){
       
      eval("document.stucheckininfoForm.ifCheckedin"+hid+".value='1';");
      
      eval("document.stucheckininfoForm.reason"+hid+"[3].checked=false;");
      eval("document.stucheckininfoForm.reason"+hid+"[2].checked=false;");
      eval("document.stucheckininfoForm.reason"+hid+"[1].checked=false;");
      eval("document.stucheckininfoForm.reason"+hid+"[0].checked=false;");
      
      eval("document.stucheckininfoForm.reason"+hid+"[3].disabled=true;");
      eval("document.stucheckininfoForm.reason"+hid+"[0].disabled=true;");
      eval("document.stucheckininfoForm.reason"+hid+"[1].disabled=true;");
      eval("document.stucheckininfoForm.reason"+hid+"[2].disabled=true;");
  
      if(document.all.ck_ifCheckedin.length>1){
          for(var i=0;i<document.all.ck_ifCheckedin.length;i++){
              if(!document.all.ck_ifCheckedin[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall1.checked=true;
          }
       } 
      
   }
   else if(ck.checked==false){
   
      document.all.checkall1.checked=false;
       
      eval("document.stucheckininfoForm.ifCheckedin"+hid+".value='0';");
      eval("document.stucheckininfoForm.ifChecked"+hid+".value='0';");
      eval("document.stucheckininfoForm.ifGotMaterial"+hid+".value='0';");
      eval("document.stucheckininfoForm.ifGotEcard"+hid+".value='0';");
      eval("document.stucheckininfoForm.ifGotStucard"+hid+".value='0';");
            
      eval("document.stucheckininfoForm.reason"+hid+"[2].checked=true;");
      
      eval("document.stucheckininfoForm.reason"+hid+"[3].disabled=false;");
      eval("document.stucheckininfoForm.reason"+hid+"[0].disabled=false;");
      eval("document.stucheckininfoForm.reason"+hid+"[1].disabled=false;");
      eval("document.stucheckininfoForm.reason"+hid+"[2].disabled=false;");
      
       if(document.all.ck_ifCheckedin.length>1){
          for(var i=0;i<document.all.ck_ifCheckedin.length;i++){
              if(document.all.ck_ifCheckedin[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall1.checked=false;
          }
       } 
   }
   //alert(eval("document.stucheckininfoForm.ifCheckedin"+hid+".value"));
    
}

function DoCheck2(ck,hid){
  
   var sflag=1;
   var usflag=1; 

   if(ck.checked){
       
      eval("document.stucheckininfoForm.ifChecked"+hid+".value='1';");
      
      if(document.all.ck_ifChecked.length>1){
          for(var i=0;i<document.all.ck_ifChecked.length;i++){
              if(!document.all.ck_ifChecked[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall2.checked=true;
          }
       } 
   
   }
   else if(ck.checked==false){
       
      eval("document.stucheckininfoForm.ifChecked"+hid+".value='0';");
      document.all.checkall2.checked=false;
      if(document.all.ck_ifChecked.length>1){
          for(var i=0;i<document.all.ck_ifChecked.length;i++){
              if(document.all.ck_ifChecked[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall2.checked=false;
          }
       } 
      
   }
   //alert(eval("document.stucheckininfoForm.ifChecked"+hid+".value"));
}

function DoCheck3(ck,hid){

var sflag=1;
var usflag=1; 
if(ck.checked){
       
      eval("document.stucheckininfoForm.ifGotMaterial"+hid+".value='1';");
      
      if(document.all.ck_ifGotMaterial.length>1){
          for(var i=0;i<document.all.ck_ifGotMaterial.length;i++){
              if(!document.all.ck_ifGotMaterial[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall3.checked=true;
          }
       } 
   
   }
   else if(ck.checked==false){
       
      eval("document.stucheckininfoForm.ifGotMaterial"+hid+".value='0';");
      document.all.checkall3.checked=false;
      if(document.all.ck_ifGotMaterial.length>1){
          for(var i=0;i<document.all.ck_ifGotMaterial.length;i++){
              if(document.all.ck_ifGotMaterial[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall3.checked=false;
          }
       } 
      
   }
}

function DoCheck4(ck,hid){
   var sflag=1;
   var usflag=1; 
   if(ck.checked){
       
      eval("document.stucheckininfoForm.ifGotEcard"+hid+".value='1';");
      
      if(document.all.ck_ifGotEcard.length>1){
          for(var i=0;i<document.all.ck_ifGotEcard.length;i++){
              if(!document.all.ck_ifGotEcard[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall4.checked=true;
          }
       } 
   
   }
   else if(ck.checked==false){
       
      eval("document.stucheckininfoForm.ifGotEcard"+hid+".value='0';");
      document.all.checkall4.checked=false;
      if(document.all.ck_ifGotEcard.length>1){
          for(var i=0;i<document.all.ck_ifGotEcard.length;i++){
              if(document.all.ck_ifGotEcard[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall4.checked=false;
          }
       } 
      
   }
}


function DoCheck5(ck,hid){
   var sflag=1;
   var usflag=1; 
   if(ck.checked){
       
      eval("document.stucheckininfoForm.ifGotStucard"+hid+".value='1';");
      
      if(document.all.ck_ifGotStucard.length>1){
          for(var i=0;i<document.all.ck_ifGotStucard.length;i++){
              if(!document.all.ck_ifGotStucard[i].checked){
                   sflag=0;
                   break;
              }
          }         
          if(sflag==1){
              document.all.checkall5.checked=true;
          }
       } 
   
   }
   else if(ck.checked==false){
       
      eval("document.stucheckininfoForm.ifGotStucard"+hid+".value='0';");
      document.all.checkall5.checked=false;
      if(document.all.ck_ifGotStucard.length>1){
          for(var i=0;i<document.all.ck_ifGotStucard.length;i++){
              if(document.all.ck_ifGotStucard[i].checked){
                   usflag=0;
                   break;
              }
          }         
          if(usflag==1){
              document.all.checkall5.checked=false;
          }
       } 
      
   }
}




function DoView(str){

   document.all.updateid.value=str;
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=stuinfoview";
   document.stucheckininfoForm.submit();
}