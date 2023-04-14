#include <Arduino.h>
#include <AsyncElegantOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ErriezMHZ19B.h>

const char* ssid = "ssid";
const char* password = "password";

AsyncWebServer server(80);

void setup()
{
	Serial.begin(9600);

	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println();

	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	if (!MDNS.begin("co2-control-loop")) {
		while (true) {
			Serial.println("Error setting up the mDNS responder!");
			delay(1000);
		}
	}
	Serial.println("mDNS responder started");

	AsyncElegantOTA.begin(&server);
	server.begin();
	Serial.println("HTTP server started");

	MDNS.addService("http", "tcp", 80);
}

void loop()
{
	MDNS.update();
}