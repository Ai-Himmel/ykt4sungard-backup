
<html xmlns="http://www.w3.org/1999/xhtml">



<head>
<title></title>

</head>
<body >
<script type="text/javascript" src="json.js"></script>
<script>
var jsonObj2={begindate:"20080501",enddate:"20080530" ,persons:[{deptId:"0001",deptname:"???",manId:"32070519791220152"}, {deptId:"0001",deptname:"???",manId:"32070519791220151"}, {deptId:"0002",deptname:"???",manId:"32070519791220152"} ]}; 

function createXMLHttpRequest() {
    if(window.XMLHttpRequest) {
        xmlHttp = new XMLHttpRequest();
    }
    else if(window.ActiveXObject) {
        xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
}
function handleStateChange() {
    if(xmlHttp.readyState == 4) {
        if(xmlHttp.status == 200) {
            document.getElementById("response").innerHTML = xmlHttp.responseText;
        }
    }
}
  function sub(){
     document.form1.action="avgtradeQry.do";
     document.form1.json.value=jsonObj2.toJSONString();
     document.form1.submit();
  }


  alert(jsonObj2.toJSONString());
  function handleAccount() {
    
    //var json = prepareJSON();
    var url = "http://localhost:8080/advquery/JSONServlet" ;
    createXMLHttpRequest();
  //  xmlHttp.onreadystatechange = handleStateChange;
    xmlHttp.open("POST", url);
    xmlHttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xmlHttp.send(jsonObj2.toJSONString());
}
  
</script>
<form name="form1" method="post">
<table width="100%" height="100%" >
                
	<tr>
	<td>  
	     <input type="hidden" name="json" value="">
		 test  
		 <input type="button" name="tijiao" value="tijiao" onclick="javascript:sub()">
	</td>
	</tr>
</table>
</form>
</body>