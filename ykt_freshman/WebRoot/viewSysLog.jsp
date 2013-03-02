<%

String webPath = request.getRealPath("/");

String filePath = webPath + "/WEB-INF/logs/freshmen.log";
String sText = "";   

org.king.utils.TextFileReader fileReader = new org.king.utils.TextFileReader();

fileReader.setFileName(filePath);

sText = fileReader.getContent();

%>

<textarea cols="100" rows="30" name="log"  style="overflow:auto"><%=sText%></textarea>




