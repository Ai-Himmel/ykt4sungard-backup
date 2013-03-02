
function showKeyName(e) {
    var keyName;
    switch (e.keyCode) {
      case 65:
        keyName = "a";
        break;
      case 66:
        keyName = "b";
        break;
      case 67:
        keyName = "c";
        break;
      case 68:
        keyName = "d";
        break;
      case 69:
        keyName = "e";
        break;
      case 70:
        keyName = "f";
        break;
      case 71:
        keyName = "g";
        break;
      case 72:
        keyName = "h";
        break;
      case 13:
        keyName="enter";  
        break;
    }
    return keyName;
  }
  
  function document.onkeydown(){
      if(event.keyCode==13)
       {
            document.getElementById("send").click();  
            return false;                              
       }
  }
  
  
  
