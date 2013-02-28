<%@page pageEncoding="UTF-8" %>
<%@ include file="../tiles/include.jsp" %>
<html>
<head>
    <title>支付平台</title>
    <meta http-equiv="Content-Type" content="text/html;">

    <link href="<c:url value="/theme/style/default/style.css"/>" type="text/css" rel=stylesheet>
    <link href="<c:url value="/theme/style/default/info.css"/>" type="text/css" rel=stylesheet>
    <script type="text/javascript">
        function submitForm(){
            var editForm = document.forms[0];
            var key = shopInfoForm["tShopinfo.key"].value;
            var checkurl = shopInfoForm["tShopinfo.checkurl"].value;
            if(key.length<1){
              var str = "商户认证密钥不能为空!"; 
		      alert(str);
		      return false; 
            }
            if(checkurl.length<1){
              var str = "商户对账URL不能为空!"; 
		      alert(str);
		      return false; 
            }
            
            if(key.length<12){
              var str = "认证密钥长度不能小于12个字符!"; 
		      alert(str);
		      return false; 
			}
            var flag=0;
            if(/\d/.test(key)){
               flag=flag+1;
            }
            if(/[a-z]/.test(key)){
              flag=flag+1;
            }
            if(/[A-Z]/.test(key)){
              flag=flag+1;
            }
            if(/\W/.test(key)){
              flag=flag+1;
			}
			if(flag<3){
			  var str = "密钥必须含有数字、大写字母、小写字母,符号四类中的三类!"; 
		      alert(str);
		      return false; 
			}
			
            editForm.submit();
        }
	   	
    </script>
</head>
<body>
<div id="breadcrumbe"><span>当前位置：编辑商家信息</span> </div>
<div class="content">	
<html:form action="editShopInfo.do?method=eidtShopInfo" method="post">
<html:hidden property="type" />
 
        <html:errors/>
        <table class="ProfileTable" >
            <tr>
                <td width="20%" class="list01">商户号：</td>
                <td >
                    <html:text property="tShopinfo.shopid"  maxlength="200" readonly="true" />
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr>
                <td width="20%" class="list01">商户显示名：</td>
                <td >
                    <html:text property="tShopinfo.showname"  maxlength="200"/>
                </td>
            </tr>
          
            <tr>
                <td width="20%" class="list01">商户认证密钥：</td>
                <td >
                    <html:text property="tShopinfo.key"  maxlength="200"/>
                    <font color="#ff0000">*</font>
                </td>
            </tr>
            <tr>
                <td width="20%" class="list01">是否需要对账：</td>
                <td >
                    <html:checkbox property="tShopinfo.ischeck" value="1"/>
                </td>
            </tr>
            <tr>
                <td width="20%" class="list01">商户对账URL：</td>
                <td >
                     <html:text property="tShopinfo.checkurl"  maxlength="200"/>
                    <font color="#ff0000">*</font> 
                </td>
            </tr>
            <tr>
                <td></td>
                <td>
                    &nbsp;&nbsp;
                    <input type="button" class="button_nor"  onclick="javascript:submitForm();" value=" 保 存 " />
                    <input type="reset" class="button_nor"  value=" 重 置 " />
                </td>
            </tr>
        </table>
</html:form>
</div>
</div>
</body>

</html>
