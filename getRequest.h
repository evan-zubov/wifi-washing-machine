#include "./settings.h";
const char *host = "api.telegram.org";
const int httpsPort = 443;

struct TeleResponse
{
  bool success;
  String body;
};

TeleResponse httpRequest(String type, String url, String body)
{
  WiFiClientSecure client;
  TeleResponse response;
  response.success = true;
  if (!client.connect(host, httpsPort))
  {
    response.success = false;
    response.body = "Failed to connect";
    return response;
  }

  if (!client.verify(fingerprint, host))
  {
    response.success = false;
    response.body = "Failed to verify certificate";
    return response;
  }

  url.replace("\n", "%0A");
  client.print(type + " /bot" + token + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n");
  if (type == "POST") {
    client.print("Content-type: application/json\r\n");
    client.print("Content-Length:" + String(body.length()) +"\r\n");
    client.print(body);
  } else {
    client.print("Connection: close\r\n\r\n");
  }

  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    if (line == "\r")
    {
      break;
    }
  }  
  response.body = client.readString();
  client.stop();
  response.body.replace("\n", "");

  return response;
}

TeleResponse postRequest(String url, String body)
{
  return httpRequest("POST", url, body);
}

TeleResponse getRequest(String url)
{
  return httpRequest("GET", url, "");
}
