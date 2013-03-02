<%@page pageEncoding="GBK"%>

<html>
  <head>
    <title>菜单失效</title>
  </head>
  
  <body>
  <br>
  <br>
  <br>
  
  <br>
  <br>
    <font size="5" color="#990000">
    当前不在此菜单的有效时间内，    
    <p>
    有效时间为&nbsp;<%=request.getAttribute("timespan")==null?"任意时间":request.getAttribute("timespan")%>。
    </font>
  </body>
</html>
