#!/bin/sh

echo -e "Content-Type: text/html\n"

/userfs/bin/tcapi set System_Entry reboot_type 7
/userfs/bin/tcapi commit System_Entry

echo "<html><head><meta http-equiv=Content-Script-Type
content=text/javascript><meta http-equiv=Content-Style-Type
content=text/css><meta http-equiv=Content-Type content=\"text/html;
charset=gb2312\"></head>
<body onload=\"javascript:window.location='/cgi-bin/test_factory.asp'\">

<table width=\"580\" border=\"0\" align=\"center\" cellpadding=\"0\" cellspacing=\"0\" bordercolor=\"#CCCCCC\" bgcolor=\"#FFFFFF\">"

echo "</table></body></html>"

