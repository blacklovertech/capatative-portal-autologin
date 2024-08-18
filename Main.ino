#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";  // Replace with your WiFi SSID

String base_url = "http://ip_address_of_your_login_portal";
String login_url = base_url + "/login.xml";
String logout_url = base_url + "/logout.xml";

const char* username = "#";  // Replace with your actual username
const char* user_password = "#";  // Replace with your actual password

// Function to login to the captive portal
void login_to_portal() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(login_url);

    // Prepare payload
    String payload = "mode=191&username=" + String(username) + "&password=" + String(user_password) + "&a=1&producttype=0";

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("User-Agent", "ESP32");

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode == 200) {
      String response = http.getString();
      Serial.println("Login successful!");
      Serial.println("Response: " + response);
    } else {
      Serial.println("Login failed with code: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

// Function to logout from the captive portal
void logout_from_portal() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(logout_url);

    // Prepare payload
    String payload = "mode=193&username=" + String(username) + "&a=1&producttype=0";

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("User-Agent", "ESP32");

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode == 200) {
      String response = http.getString();
      Serial.println("Logout successful!");
      Serial.println("Response: " + response);
    } else {
      Serial.println("Logout failed with code: " + String(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Log in to the portal
  login_to_portal();

  // Wait for a specified amount of time before logging out
  int delayInSeconds = 3600;  // Delay in seconds (e.g., 3600 seconds = 1 hour)
  Serial.println("Waiting for " + String(delayInSeconds / 60) + " minutes before auto logging out...");
  delay(delayInSeconds * 1000);

  // Log out from the portal
  logout_from_portal();
}

void loop() {
  // Your main code here
}
