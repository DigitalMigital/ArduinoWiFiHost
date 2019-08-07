#ifndef sergomor_host_html_h
#define sergomor_host_html_h

const char *index_html PROGMEM = "<!DOCTYPE html>\
<html><head>\
<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
<style>\
input{display:block}\
@media screen and (max-width:600px){\
form{width:100%;margin:0;}\
input{width:100%;font-size:120%;margin-top:2%;padding:2%;}}\
</style>\
</head>\
<body>\
<form action=\"/wifi\" method=\"POST\">\
<input type=\"text\" name=\"ssid\" required placeholder=\"ssid\">\
<input type=\"password\" name=\"pass\" required placeholder=\"password\">\
<input type=\"submit\" value=\"Save\">\
</form>\
</body></html>";

#endif;