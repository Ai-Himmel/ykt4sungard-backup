<%@page pageEncoding="UTF-8"%>
<%@ page import="org.king.classmanage.domain.Classmodel"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="java.util.HashMap"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ page import="org.king.classmanage.web.help.DormitoryBindInfo"%>
<%@ include file="../tiles/include.jsp"%>
<center>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
		<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
			<html:form action="gzclassAction.do?method=saveBinding" onsubmit="javascript:return setValue();">
				<tr>
					<td>
						<%if (request.getAttribute("myclass") != null) {
				String myclass = request.getAttribute("myclass").toString();

				%>
						<INPUT type="hidden" name="myclass" value="<%=myclass%>">
						<%} else {

			%>
						<INPUT type="hidden" name="myclass" value="">

						<%}

			%>
					</td>
					<td>
					<%if (request.getAttribute("myarea") != null) {
				String myarea = request.getAttribute("myarea")
						.toString();

				%>
						<INPUT type="hidden" name="myarea" value="<%=myarea%>">
						<%} else {

			%>
						<INPUT type="hidden" name="myarea" value="">

						<%}

			%>
						<%if (request.getAttribute("mylocation") != null) {
				String mylocation = request.getAttribute("mylocation")
						.toString();

				%>
						<INPUT type="hidden" name="mylocation" value="<%=mylocation%>">
						<%} else {

			%>
						<INPUT type="hidden" name="mylocation" value="">

						<%}

			%>
					</td>
					<td>
						<%if (request.getAttribute("mydormitory") != null) {
				String mydormitory = request.getAttribute("mydormitory")
						.toString();

				%>
						<INPUT type="hidden" name="mydormitory" value="<%=mydormitory%>">
						<%} else {

			%>
						<INPUT type="hidden" name="mydormitory" value="">

						<%}

			%>
					</td>					
				</tr>
				<html:hidden property="binddormitorys" />
				<html:hidden property="unbinddormitorys" />
				<tr>
					<td height="30" align="center" valign="middle" class="tdborder02">
						<strong><font class="medium"><bean:message bundle="classmanage" key="classBinding.classBinding" /></font></strong>
					</td>
				</tr>
				<tr>
					<td align="left" valign="top">
						<INPUT type="hidden" name="myerror" value="<html:errors bundle="classmanage" />">
					</td>
				</tr>
				<tr>
					<td align="center" valign="top">
						<table width="100%" border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td width="21%" align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td width="2%" align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td width="35%" align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td width="35%" align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
							</tr>
							<tr>
								<td align="center" valign="middle" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									<span class="medium">校区</span>
									<html:select property="dormitorymodel.area" onchange="javascript:changeArea(this.value);">
										<html:option value="">---------------------</html:option>
										<html:options collection="arealist" labelProperty="areaName" property="area" />
									</html:select>
									<br>	
									<span class="medium">区域</span>									
									<SELECT name="dormitorymodel.location" onchange="javascript:changeLocation(this.value);">
										<OPTION value="">
											---------------------
										</OPTION>
									</SELECT>
									<br>
									<span class="medium"><bean:message bundle="classmanage" key="classBinding.building" /></span>
									<SELECT name="dormitorymodel.dormitory" onchange="javascript:changeDormitory(this.value);">
										<OPTION value="">
											---------------------
										</OPTION>
									</SELECT>
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6" id="showlabel">
									--已绑定宿舍列表--
								</td>
							</tr>
							<tr>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
							</tr>
							<tr>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									--班级选择--
									<br>
									<select name="classes" size="20" style="width:140 px;" onchange="javascript:changeClass(this.value,this.options[this.selectedIndex].text);">
									<logic:present name="classlist" scope="request">
                                       <logic:iterate name="classlist" id="cl" type="java.util.Map">
                                          <option value="<bean:write name="cl" property="classId"/>"><bean:write name="cl" property="classNo"/>&nbsp;(男:<bean:write name="cl" property="maleNum"/>,女:<bean:write name="cl" property="femaleNum"/>)</option>
                                       </logic:iterate>
                                    </logic:present>
									</select>
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									--宿舍选择--
									<br>
									<select name="unbinddormitory" multiple="multiple" onDblClick="" size="20" style="width:250 px;">
									</select>

								</td>
								<td align="center">
									<p>
										<button name="moveRight" id="moveRight" type="button" class="button_nor" onclick="return classSelCheck();">
											<bean:message bundle="classmanage" key="classBinding.right" />
										</button>
										<br />
										<br />
										<button name="moveLeft" id="moveLeft" type="button" class="button_nor" onclick="returnOption(this.form.binddormitory, this.form.unbinddormitory,false)">
											<bean:message bundle="classmanage" key="classBinding.left" />
										</button>
										<br />
									</p>
								</td>
								<td width="28%" align="center" valign="top" bgcolor="#ECE6E6">
									<br>
									<font color="#FF0000"><select name="binddormitory" multiple="multiple" onDblClick="" size="20" style="width:250 px;">
										</select></font>

								</td>
							</tr>
							<tr>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#FFFFFF">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
								<td align="center">
									&nbsp;
								</td>
								<td align="center" valign="top" bgcolor="#ECE6E6">
									&nbsp;
								</td>
							</tr>

							<tr align="right" valign="middle">
								<td height="40" colspan="5">
									<html:submit property="sure" styleClass="button_nor">
										<bean:message bundle="classmanage" key="studentsearch.sure" />
									</html:submit>
								</td>
							</tr>
						</table>
					</td>
				</tr>
			</html:form>
		</table>
	</body>

</center>

<script language="JavaScript">
	var boyDorm = 0;
	var boyPlace = 0;
	var girlDorm = 0;
	var girlPlace = 0;	
	var boynum=0;
	var girlnum=0;
	var needbednum=0;//还需床位数
	
	<!--classnum list-->
	
	    var classnums=new Array();
	    var classcount=0;
	<%
	    ArrayList classnumlist=new ArrayList();
	    if(request.getAttribute("classlist")!=null)
	        classnumlist=(ArrayList)request.getAttribute("classlist");
	    int cnum=0;
	    for(cnum=0;cnum<classnumlist.size();cnum++){
	        HashMap classnum=(HashMap)classnumlist.get(cnum);
	     %>
          classnums[<%=cnum%>] = new Array("<%=(String)classnum.get("classId")%>","<%=(Integer)classnum.get("maleNum")%>","<%=(Integer)classnum.get("femaleNum")%>");//产生javascript二维数组，对应班号、男生数、女生数
         <%
	    
	    }
	
	%>
	    classcount=<%=cnum%>;
	 
	 <!-- location list -->
 
		var locationcount;
		locationcount = 0;
		locations = new Array(); 
	<%	
		String[][] locationlist=null;     
		int k = 0;		
		if(request.getAttribute("allist")!=null)
		    locationlist=(String[][])request.getAttribute("allist");
		    
		if(locationlist!=null){
         for(k=0;k<locationlist.length;k++)
         {
         %>
          locations[<%=k%>] = new Array("<%=locationlist[k][0]%>","<%=locationlist[k][1]%>","<%=locationlist[k][2]%>");//产生javascript二维数组，对应区域id、区域名称、校区id
         <%
         }
        }
   %>
        locationcount=<%=k%>;
	 
	 
	 <!-- dormitory list -->
 
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		String[][] dromitorylist=null;
		int l = 0;
		if(request.getAttribute("ldlist")!=null)
		    dromitorylist=(String[][])request.getAttribute("ldlist");
		if(dromitorylist!=null){
         for(l=0;l<dromitorylist.length;l++)
         {
         %>
          dormitorys[<%=l%>] = new Array("<%=dromitorylist[l][0]%>","<%=dromitorylist[l][1]%>","<%=dromitorylist[l][2]%>");//产生javascript二维数组，对应楼号id、楼号名称、区域id
         <%
         }
        }
    %>
        dormcount=<%=l%>;
 
 
function changeArea(area){
	document.all["dormitorymodel.location"].length=0;
	var areaId=area;
	var j; 
	document.all["dormitorymodel.location"].options[document.all["dormitorymodel.location"].length]= new Option("---------------------","");
		for (j=0;j < locationcount; j++) 
		{ 
			if (locations[j][2] == areaId) 
			{ 
				document.all["dormitorymodel.location"].options[document.all["dormitorymodel.location"].length]= new Option(locations[j][1],locations[j][0]);
			} 
		} 
} 

function changeLocation(location){
	document.all["dormitorymodel.dormitory"].length=0;
	var locationId=location;
	var j; 
	document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option("---------------------","");
		for (j=0;j < dormcount; j++) 
		{ 
			if (dormitorys[j][2] == locationId) 
			{ 
				document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
			} 
		} 
}
 
function changeClass(classId,title){
	boyDorm = 0;
	boyPlace = 0;
	girlDorm = 0;
	girlPlace = 0;	
	boynum=0;
	girlnum=0;
	document.all["binddormitory"].length=0;
	var classId=classId;
	var i;
	var j; 
	
	    for(i=0;i<classcount;i++){
	       if(classnums[i][0]==classId){
	           boynum=classnums[i][1];
	           girlnum=classnums[i][2];
	       }
	    }//该班住宿的男生数和女生数
	    	    	
		for (j=0;j < binddormcount; j++) { 
			if (binddormitorys[j][5] == classId) 
			{ 
				if(binddormitorys[j][3]=='1'){
					boyDorm++;
					boyPlace += parseInt(binddormitorys[j][4],10);
				}
				if(binddormitorys[j][3]=='2'){
					girlDorm++;
					girlPlace += parseInt(binddormitorys[j][4],10);
				}
				document.all["binddormitory"].options[document.all["binddormitory"].length]= new Option(binddormitorys[j][1],binddormitorys[j][0]);
			} 
		}
		document.getElementById("showlabel").innerHTML=title+' 已绑定宿舍列表<br> 男生宿舍数:'+boyDorm+'&nbsp;&nbsp;女生宿舍数:'+girlDorm+'<br>男生床位数:'+boyPlace+'&nbsp;&nbsp;女生床位数:'+girlPlace; 
}



<!-- bindeddormitory list -->
 
 
 		var binddormcount;
		binddormcount = 0;
		binddormitorys = new Array(); 
	<%	
		ArrayList binddormlist=new ArrayList();
		if(request.getAttribute("bindeddormList")!=null)
		    binddormlist=(ArrayList)request.getAttribute("bindeddormList");
		int m = 0;
		
		if(binddormlist!=null){
		   for(m=0;m<binddormlist.size();m++){
			HashMap dormitorybindinfo= (HashMap)binddormlist.get(m);
			String dormitoryId = (String)dormitorybindinfo.get("dormitoryId");
			String areaCode = (String)dormitorybindinfo.get("area");
			String areaStr =  (String)dormitorybindinfo.get("areaName");
			String locationCode = (String)dormitorybindinfo.get("location");
			String locationStr =  (String)dormitorybindinfo.get("locationName");
			String dormitoryCode =  (String)dormitorybindinfo.get("dormitory");
			String dormitoryStr =   (String)dormitorybindinfo.get("dormitoryName");
			String roomnumber=  (String)dormitorybindinfo.get("roomNumber");
			String genderCode =	 (String)dormitorybindinfo.get("gender");
			String genderStr =	 (String)dormitorybindinfo.get("genderName");
			String directionStr=(String)dormitorybindinfo.get("directionName");
			int accomodation =  ((Integer)dormitorybindinfo.get("distributeNum")).intValue();
			String classId =   (String)dormitorybindinfo.get("classId");
	%>
		    binddormitorys[<%=m%>]= new Array("<%=dormitoryId%>","<%=areaStr%><%=locationStr%><%=dormitoryStr%>-<%=roomnumber%> [<%=directionStr%>] [<%=genderStr%>] [<%=accomodation%>]","<%=dormitoryCode%>","<%=genderCode%>","<%=accomodation%>","<%=classId%>"); 
	<%	
		}	
	%>

	    binddormcount=<%=binddormlist.size()%>         
	
	<%}%>
	
<!-- unbindeddormitory list -->

 		var unbinddormcount;
		unbinddormcount = 0;
		unbinddormitorys = new Array(); 
	<%	
		ArrayList unbinddormlist=new ArrayList();		
		if(request.getAttribute("roomList")!=null)
		    unbinddormlist=(ArrayList)request.getAttribute("roomList");
		int n = 0;		
		for(n=0;n<unbinddormlist.size();n++){
		    HashMap dormitorybindinfo= (HashMap)unbinddormlist.get(n);
			String dormitoryId = (String)dormitorybindinfo.get("dormitoryId");
			String areaCode = (String)dormitorybindinfo.get("area");
			String areaStr =  (String)dormitorybindinfo.get("areaName");
			String locationCode =  (String)dormitorybindinfo.get("location");
			String locationStr =  (String)dormitorybindinfo.get("locationName");
			String dormitoryCode = (String)dormitorybindinfo.get("dormitory");
			String dormitoryStr =   (String)dormitorybindinfo.get("dormitoryName");
			String roomnumber=  (String)dormitorybindinfo.get("roomNumber");
			String genderCode =	(String)dormitorybindinfo.get("gender");
			String genderStr =	 (String)dormitorybindinfo.get("genderName");
			String directionStr=(String)dormitorybindinfo.get("directionName");
			int accomodation =  ((Integer)dormitorybindinfo.get("emptyNum")).intValue();
			String classId ="";
	%>
		unbinddormitorys[<%=n%>]= new Array("<%=dormitoryId%>","<%=areaStr%><%=locationStr%><%=dormitoryStr%>-<%=roomnumber%> [<%=directionStr%>] [<%=genderStr%>] [<%=accomodation%>]","<%=dormitoryCode%>","<%=genderCode%>","<%=accomodation%>","<%=classId%>"); 
	<%	
		}	
	%>

	unbinddormcount=<%=unbinddormlist.size()%> 
 
function changeDormitory(dormitory){
	document.all["unbinddormitory"].length=0;
	var dormitory=dormitory;
	var j; 	
		for (j=0;j < unbinddormcount; j++) 
		{   
			if (unbinddormitorys[j][2] == dormitory) 
			{ 
				document.all["unbinddormitory"].options[document.all["unbinddormitory"].length]= new Option(unbinddormitorys[j][1],unbinddormitorys[j][0]);
			} 
		} 
}

function classSelCheck(){//检验是否选择了班级，和床位数
	if(document.all("classes").value==""){
		alert("请选择需要绑定宿舍的班级");		
		return false;
	}
	
	transferOption(document.all.unbinddormitory, document.all.binddormitory,document.all.classes,false)
	return true;

}

function transferOption(e1,e2,e3,all){
  	var src = e2.options;//已绑定宿舍
  	var tgt = e1.options;//还可绑定宿舍
  	var index = e3.selectedIndex;
	var classes = e3.options;//班级
  	var items;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) { 
    	    
    	    var dormid;//选定宿舍id
	        var dormgender;//选定宿舍的入住性别
	        var dormbednum;//选定宿舍的可绑床位数
	
	        dormid=tgt[i].value;
    
            for(var j=0;j<unbinddormitorys.length;j++){	//可绑宿舍数组
	 	        if(unbinddormitorys[j][0]==dormid){
	 	            dormgender=unbinddormitorys[j][3];
	 	            dormbednum=unbinddormitorys[j][4];	 	    
	 	            break;
	 	        }
	         }
	
	         //alert("dormbednum:"+dormbednum);
			
	         if(dormgender=='1'){
	             needbednum=boynum-boyPlace;
	             //alert("needbednum:"+needbednum);	
	             if(needbednum<1){
	                 alert("该班男生床位数已绑定完毕!");
	                 break;    
	             }	
	         }
	         else if(dormgender=='2'){
	              needbednum=girlnum-girlPlace;
	              //alert("needbednum:"+needbednum);	
	              if(needbednum<1){
	                  alert("该班女生床位数已绑定完毕!");
	                  break;    
	              }	
	          }
		
	          var bindnum=dormbednum;//这次绑定床位数	
	          var leftnum=0;//剩余床位数
	
	          if(dormbednum>needbednum){//剩余床位数比需要的床位数多，只绑需要的床位数
	              bindnum=needbednum;
	              leftnum=dormbednum-bindnum;	    
	          }
	          //alert("curbindnum:"+bindnum+" leftbednum:"+leftnum);   
	
    	    //页面调整
			clone = uiCommon_cloneSelectOption(tgt[i],bindnum);
  			if(clone!=null)
  			   src.add(clone);
  			  			
  			if(leftnum>0){
  			    var newtext=tgt[i].text;
  			    newtext=newtext.substring(0,newtext.length-3);
	            newtext=newtext+"["+leftnum+"]";	            
	            tgt[i].text=newtext;  			
  			}
  			//数组调整
  			uiOptionTransfer_putArrayItem(tgt[i].value,classes[index].value,bindnum,leftnum);
  			  	
  			if(leftnum==0){  			   
  			   tgt[i]=null;
  			   i=tgt.length;  			   
  			}
  			   
  			needbednum=needbednum-bindnum;	
  		}
  	}  	
  	
}
	
function uiCommon_cloneSelectOption(opt,bindnum) {//页面展现：绑定
    
    var i;
	for (i = document.all.binddormitory.options.length - 1; i >= 0; --i) {
    	if (document.all.binddormitory.options[i].value==opt.value) { //界面上还有此宿舍
    	      //alert("on page");
    	      
    	      var newtext=document.all.binddormitory.options[i].text;  
    	      onum=newtext.substring(newtext.length-2,newtext.length-1);  
    	      //alert("onum:"+onum);    	      	 
    	      var resultnum=parseInt(onum,10)+parseInt(bindnum,10);     
    	      //alert("resultnum:"+resultnum);
    	      
    	      newtext=newtext.substring(0,newtext.length-3);
	          newtext=newtext+"["+resultnum+"]";
	          document.all.binddormitory.options[i].text=newtext; 
	          break;
    	}
    }
    if(i<0){//界面上无此宿舍 
        //alert("not on page");
        var newtext=opt.text;
	    newtext=newtext.substring(0,newtext.length-3);
	    newtext=newtext+"["+bindnum+"]";
	    return new Option(newtext, opt.value,
                    opt.defaultSelected, opt.selected); 
                                    	   
    }
    else
        return null;
 
}
	
//add classId to unbinddormitory's record   
//and add this record to binddormitory
//and delete this record from unbinddormitory
function uiOptionTransfer_putArrayItem(dormitoryId,classId,bindnum,leftnum){//绑定
	var dormitory_id = dormitoryId;//需要绑定的宿舍
	var class_id = classId;
	var i;
	var index = 0;
	index = binddormitorys.length;
	var newbind=false;
	
	for(i=0;i<binddormitorys.length;i++){	
	 	if(binddormitorys[i][0]==dormitory_id&&binddormitorys[i][5]==class_id){//还有此宿舍
	 	    index=i;
	 	    binddormitorys[i][4]=parseInt(binddormitorys[i][4],10)+parseInt(bindnum,10);//更新床位数，更新显示label
	 	    var text=binddormitorys[i][1];
	 	    text=text.substring(0,text.length-3);
	 		binddormitorys[i][1]=text+"["+binddormitorys[i][4]+"]";
	 		//alert("bindlist still has it.");
	 		break;
	 	}
	 	
	}
	
	for(i=0;i<unbinddormitorys.length;i++){	
	 	if(unbinddormitorys[i][0]==dormitory_id){
	 	    if(index>binddormitorys.length-1){	
	 	        var text=unbinddormitorys[i][1];
	 	        text=text.substring(0,text.length-3);
	 	        text=text+"["+bindnum+"]";	 	    
	 		    binddormitorys[index] = new Array(unbinddormitorys[i][0],text,unbinddormitorys[i][2],unbinddormitorys[i][3],bindnum,class_id);
	 		    binddormcount++;
	 		    newbind=true;
	 		}
	 		if(leftnum==0){
	 		    //alert(unbinddormitorys[i][1]+" is clear.")
	 		    unbinddormitorys[i][0]="";
	 		    unbinddormitorys[i][1]="";
	 		    unbinddormitorys[i][2]="";
	 		    unbinddormitorys[i][3]="";
	 		    unbinddormitorys[i][4]="";
	 		    unbinddormitorys[i][5]="";	 		    
	 		}
	 		else{
	 		    unbinddormitorys[i][4]=leftnum;//更新床位数，更新显示label
	 		    var text=unbinddormitorys[i][1];
	 		    text=text.substring(0,text.length-3);
	 		    unbinddormitorys[i][1]=text+"["+unbinddormitorys[i][4]+"]";
	 		}
	 		
	 		if(binddormitorys[index][3]=='1'){
	 		    if(newbind){	 		        
				    boyDorm++;
				    boyPlace += parseInt(bindnum,10);
				}
				else{
				    boyPlace+=parseInt(bindnum,10);
				}
			}
			if(binddormitorys[index][3]=='2'){
			    if(newbind){			        
				    girlDorm++;
				    girlPlace += parseInt(bindnum,10);
				}
				else{
				    girlPlace+=parseInt(bindnum,10);
				}
			}
			break;
	 	}	 	
 }
 document.getElementById("showlabel").innerHTML=document.all("classes").options[document.all("classes").selectedIndex].text+' 已绑定宿舍列表<br> 男生宿舍数:'+boyDorm+'&nbsp;&nbsp;女生宿舍数:'+girlDorm+'<br>男生床位数:'+boyPlace+'&nbsp;&nbsp;女生床位数:'+girlPlace; 

}

function returnOption(e1,e2,all){
  	var src = e2.options;//还可以绑定的宿舍
  	var tgt = e1.options;//已绑定的宿舍
  	var items;
  	var index;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) { 
			clone = uiCommon_cloneUnSelectOption(tgt[i]);
			if(clone!=null)
  			    src.add(clone);
  			    
  			var text=tgt[i].text;  			
  			var returnnum=text.substring(text.length-2,text.length-1);
  			  			
  			uiOptionReturn_putArrayItem(tgt[i].value,returnnum);//数组调整
  			
  			tgt[i] = null;
  			i=tgt.length;  
  			
  			needbednum=needbednum+returnnum;
  		}
  	}
}

function uiCommon_cloneUnSelectOption(opt) {//页面展现：撤销绑定

    //还可绑定宿舍
    var i;
	for (i = document.all.unbinddormitory.options.length - 1; i >= 0; --i) {
    	if (document.all.unbinddormitory.options[i].value==opt.value) { //界面上还有此宿舍
    	      //alert("on page");
    	      var returntext=opt.text;
    	      var returnnum=returntext.substring(returntext.length-2,returntext.length-1);  
    	      //alert("returnnum:"+returnnum);
    	      var newtext=document.all.unbinddormitory.options[i].text;  
    	      onum=newtext.substring(newtext.length-2,newtext.length-1);  
    	      //alert("onum:"+onum);    	      	 
    	      var resultnum=parseInt(onum,10)+parseInt(returnnum,10);     
    	      //alert("resultnum:"+resultnum);
    	      
    	      newtext=newtext.substring(0,newtext.length-3);
	          newtext=newtext+"["+resultnum+"]";
	          document.all.unbinddormitory.options[i].text=newtext; 
	          break;
    	}
    }
    if(i<0){//界面上已无此宿舍 
        //alert("not on page");
        var curdormitory="";
        var j=0;
        for(j=0;j<binddormitorys.length;j++){	
	 	    if(binddormitorys[j][0]==opt.value){//找到此宿舍的楼号
	 	        curdormitory=binddormitorys[j][2];
	 	        break;
	 	    }
	 	}	 	
	 	if(j<binddormitorys.length&&curdormitory==document.all["dormitorymodel.dormitory"].value){//与查询楼号一致
	 	    //alert("can in.");
	 	    return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);	 	
	 	}
	 	else
	 	    return null;
                                    	   
    }else
        return null;
}

function uiOptionReturn_putArrayItem(dormitoryId,returnnum){//撤销绑定
	var dormitory_id = dormitoryId;
	var i;
	var index=unbinddormitorys.length;
	
	for(i=0;i<unbinddormitorys.length;i++){	
	 	if(unbinddormitorys[i][0]==dormitory_id){//还有此宿舍
	 	    index=i;
	 	    unbinddormitorys[i][4]=parseInt(unbinddormitorys[i][4],10)+parseInt(returnnum,10);//更新床位数，更新显示label
	 	    var text=unbinddormitorys[i][1];
	 	    text=text.substring(0,text.length-3);
	 		unbinddormitorys[i][1]=text+"["+unbinddormitorys[i][4]+"]";
	 		//alert("unbindlist still has it.");
	 		break;
	 	}
	 	
	}
	for(i=0;i<binddormitorys.length;i++){	
	 	if(binddormitorys[i][0]==dormitory_id&&binddormitorys[i][5]==document.all("classes").value){
	 	    if(index>unbinddormitorys.length-1){	 		    
	 		    unbinddormitorys[index] = new Array(binddormitorys[i][0],binddormitorys[i][1],binddormitorys[i][2],binddormitorys[i][3],returnnum,"");
	 		    unbinddormcount++;
	 		    //alert("unbindlist add it.");
	 		}
	 		if(unbinddormitorys[index][3]=='1'){
					boyDorm--;
					boyPlace -=returnnum;					
			}
			if(unbinddormitorys[index][3]=='2'){
					girlDorm--;
					girlPlace -=returnnum;					
			}
	 	    binddormitorys[i][0]="";
	 		binddormitorys[i][1]="";
	 		binddormitorys[i][2]="";
	 		binddormitorys[i][3]="";
	 		binddormitorys[i][4]="";
	 		binddormitorys[i][5]="";	
	 		
	 		break; 		
	 	}
	 	 	
   }
   
   document.getElementById("showlabel").innerHTML=document.all("classes").options[document.all("classes").selectedIndex].text+' 已绑定宿舍列表<br> 男生宿舍数:'+boyDorm+'&nbsp;&nbsp;女生宿舍数:'+girlDorm+'<br>男生床位数:'+boyPlace+'&nbsp;&nbsp;女生床位数:'+girlPlace; 

}

function setValue(){//提交时
	document.all.binddormitorys.value=binddormitorys;
	document.all.unbinddormitorys.value=unbinddormitorys;
	//alert("bind:"+document.all.binddormitorys.value);
	//alert("unbind:"+document.all.unbinddormitorys.value);
	return true;
}


function my_onload(){

for(var j=0;j<classcount;j++){

    if(document.all("classes").options[j].value==document.all("myclass").value){
		document.all("classes").options[j].selected=true;
		changeClass(document.all("classes").value,document.all("classes").options[document.all("classes").selectedIndex].text);
	    break;
	}
}

if(document.all["dormitorymodel.area"].options[1]!=null)
    document.all["dormitorymodel.area"].options[1].selected=true;
	 	if(document.all("dormitorymodel.area").value!=""){	 	
	 		document.all["dormitorymodel.location"].length=0;
			var j; 
			document.all["dormitorymodel.location"].options[document.all["dormitorymodel.location"].length]= new Option("---------------------","");
			for (j=0;j < locationcount; j++) { 
				if (locations[j][2] == document.all("dormitorymodel.area").value) 
				{ 
					document.all["dormitorymodel.location"].options[document.all["dormitorymodel.location"].length]= new Option(locations[j][1],locations[j][0]);
				} 
				if(locations[j][0]==document.all("mylocation").value){
					document.all("dormitorymodel.location").options[document.all("dormitorymodel.location").length-1].selected=true;
					changeLocation(document.all("dormitorymodel.location").value);
				}
			} 
	 	}
	 	
	 	if(document.all("dormitorymodel.location").value!=""){	 	
	 		document.all["dormitorymodel.dormitory"].length=0;
			var j; 
			document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option("---------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("dormitorymodel.location").value) 
				{ 
					document.all["dormitorymodel.dormitory"].options[document.all["dormitorymodel.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitorymodel.dormitory").options[document.all("dormitorymodel.dormitory").length-1].selected=true;
					changeDormitory(document.all("dormitorymodel.dormitory").value);
				}
			} 
	 	}
	 	 	
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 } 


	 window.onload=my_onload;	

</script>
