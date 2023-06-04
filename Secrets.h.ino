#include <pgmspace.h>
 
#define SECRET
 
const char WIFI_SSID[] = "YOUR_WIFI_NAME";          //NAME OF WIFI
const char WIFI_PASSWORD[] = "YOUR_WIFI_PASSWORD";  //PASSWORD
 
#define THINGNAME "YOUR_THING_NAME_IN_AWS"
 
int8_t TIME_ZONE = -3; //TIMEZONE_BRAZIL
 
const char MQTT_HOST[] = "YOUR_IOT_CORE_DEVICEDATA_ENDPOINT";
 
// Copy contents from YOUR AWS CERTIFICATE HERE
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here 
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
 
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here 
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
 
)KEY";