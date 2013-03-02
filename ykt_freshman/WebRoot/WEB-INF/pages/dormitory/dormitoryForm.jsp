<%@ page pageEncoding="UTF-8"%>
<%@ page import="java.util.ArrayList"%>
<%@ page import="org.king.classmanage.domain.Dictionary"%>
<%@ include file="../tiles/include.jsp"%>
<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
	<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
		<tr>
			<td height="30" align="center" valign="middle" class="tdborder02">
				<strong><font class="medium"><bean:message bundle="dormitorymanage" key="dormitoryResource.dormitoryResource" /></font></strong>
			</td>
		</tr>
		<tr>
			<td align="left" valign="middle">
				<INPUT type="hidden" name="myerror" value="<html:errors bundle="dormitorymanage" />">
			</td>
		</tr>
		<tr>
			<td align="center" valign="top">
				<html:form method="post" action="DormitoryAction.do?method=save">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						<tr>
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

						<tbody>
							<tr align="center" valign="middle">
								<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<span class="medium">宿舍所属区域</span>
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select onchange="changeLocation(this.value)" styleClass="select01" property="dormitory.location">
										<html:option value="">-----------------------</html:option>
										<html:options collection="locationList" property="id.dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>
								<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<span class="medium">宿舍楼号</span>
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<html:select styleClass="select01" property="dormitory.dormitory">
										<html:option value="">-----------------------</html:option>
									</html:select>
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td width="15%" height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<span class="medium">入住性别</span>
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<html:select styleClass="select01" property="dormitory.gender">
										<html:option value="">-----------------------</html:option>
										<html:options collection="genderList" property="id.dictValue" labelProperty="dictCaption" />
									</html:select>
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									<span class="medium">宿舍号</span>
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<html:text styleClass="input_box" property="dormitory.roomNumber" maxlength="10" />
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									床位数
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<html:text styleClass="input_box" property="dormitory.accomodation" maxlength="3" />
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									宿舍电话
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<html:text styleClass="input_box" property="dormitory.telphone" maxlength="30" />
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td height="24" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									住宿费
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<html:text styleClass="input_box" property="dormitory.fee" maxlength="8" />
								</td>
							</tr>
						</tbody>
					</table>
					<tr>
						<td height="40" align="right" valign="middle" class="tdborder02">
							<html:submit property="save" styleClass="button_nor" onclick="javascript: return on_validate();">
								<bean:message key="button.save" />
							</html:submit>
							<input type="button" name="goback" class="button_nor" value="<bean:message bundle="classmanage" key="class.return" />" onclick="javascript:howtoreturn();">
						</td>
					</tr>
				</html:form>
			</td>
		</tr>
	</table>
</body>
<script language="JavaScript">
		var dormcount;
		dormcount = 0;
		dormitorys = new Array(); 
	<%	
		ArrayList dromitorylist=(ArrayList)request.getAttribute("dormitoryList");
		int l = 0;
		for(l=0;l<dromitorylist.size();l++){
			Dictionary building = (Dictionary)dromitorylist.get(l);
			String dormitoryid = building.getId().getDictValue();
			String dormtioryname = building.getDictCaption();
			String location = building.getDictParent();
	%>
		dormitorys[<%=l%>]= new Array("<%=dormitoryid%>","<%=dormtioryname%>","<%=location%>"); 
	<%	
		}	
	%>

	dormcount=<%=dromitorylist.size()%> 
 
	function changeLocation(location){
		document.all["dormitory.dormitory"].length=0;
		var locationId=location;
		var j; 
		document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option("-----------------------","");
			for (j=0;j < dormcount; j++) 
			{ 
				if (dormitorys[j][2] == locationId) 
				{ 
					document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
			} 
	}
		function on_validate(){
		if(document.all("dormitory.location").value==""){
			alert("宿舍所属区域不可为空");
			document.all("dormitory.location").focus();
			return false;
		}		
		if(document.all("dormitory.dormitory").value==""){
			alert("宿舍楼号不可为空");
			document.all("dormitory.dormitory").focus();
			return false;
		}
		if(document.all("dormitory.roomNumber").value==""){
			alert("宿舍号不可为空");
			document.all("dormitory.roomNumber").focus();
			return false;
		}		
		if(document.all("dormitory.gender").value==""){
			alert("入住学生不可为空");
			document.all("dormitory.gender").focus();
			return false;
		}		
		if(document.all("dormitory.accomodation").value==""){
			alert("床位数不可为空");
			document.all("dormitory.accomodation").focus();
			return false;
		}
		if(fucCheckNUM(document.all("dormitory.accomodation").value)==0){
			alert("床位数应为整数");
			document.all("dormitory.accomodation").focus();
			return false;
		}
		if(document.all("dormitory.fee").value==""){
			alert("费用不可为空");
			document.all("dormitory.fee").focus();
			return false;
		}
		if(fucCheckFloat(document.all("dormitory.fee").value)==0){
			alert("费用应为数值");
			document.all("dormitory.fee").focus();
			return false;
		}		
		return true;

}

function fucCheckNUM(NUM)
{
 var i,j,strTemp;
 strTemp="0123456789";
 if ( NUM.length== 0)
  return 0
 for (i=0;i<NUM.length;i++)
 {
  j=strTemp.indexOf(NUM.charAt(i)); 
  if (j==-1)
  {
  //说明有字符不是数字
   return 0;
  }
 }
 //说明是数字
 return 1;
}

function fucCheckFloat(NUM)
{
 var i,j,strTemp;
 strTemp="0123456789.";
 var staus;
 status = 0;
 if ( NUM.length== 0)
  return 0
 for (i=0;i<NUM.length;i++){
  j=strTemp.indexOf(NUM.charAt(i)); 
  if (j==-1)
  {
  //说明有字符不是数字
   return 0;
  }
  if (NUM.charAt(i)=='.')
  {
   status++;
  }
  if (status>1) 
  {
  return 0;  
  }
  
 }
 //说明是数字
 return 1;
}

	 function my_onload(){
	 	
	 	if(document.all("dormitory.location").value!=""){	 	
	 		document.all["dormitory.dormitory"].length=0;
			var j; 
			document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option("--------------------","");
			for (j=0;j < dormcount; j++) { 
				if (dormitorys[j][2] == document.all("dormitory.location").value) 
				{ 
					document.all["dormitory.dormitory"].options[document.all["dormitory.dormitory"].length]= new Option(dormitorys[j][1],dormitorys[j][0]);
				} 
				if(dormitorys[j][0]==document.all("mydormitory").value){
					document.all("dormitory.dormitory").options[document.all("dormitory.dormitory").length-1].selected=true;
				}
			} 
	 	}
	 	if(document.all.myerror.value != ""){
			alert(document.all.myerror.value);
		}
	 }
	 
	 window.onload=my_onload;	 
	 
	 	function howtoreturn(){
		if(document.all.myerror.value != ""){
			window.location.href='managerAction.do?method=load4Search';
		}else{
			history.go(-1);	
		}
	}

</script>

