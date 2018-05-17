

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,8);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    //Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 1");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
         
            int sensorReading = analogRead(A0);
            //client.print(" is ");
            if(sensorReading>20)
            {
              client.println("|not detected|");
              client.println("<br />");
              client.println("<br />");
              client.println("<br />");
              client.println("<br />");
            
            }
            else
            {
               client.println("|detected|");
               client.println("<br />");
              client.println("<br />");
              client.println("<br />");
              client.println("<br />");
            
            }
            client.print("<tb >");
            client.println(sensorReading);
            client.println("|" );
            client.println("<br />");
              client.println("<br />");
              client.println("<br />");
              client.println("<br />");
            
            client.println("<br />");
     if(sensorReading>20)
            {
              client.println("waiting");
               client.println("<br />");
               client.println("<br />");
              client.println("<br />");
              client.println("<br />");
              client.println("<br />");
                       
            }
            else
            {
               client.println("welcome ,visit again");
                client.println("<br />");
               client.println("<br />");
              client.println("<br />");
              client.println("<br />");
              client.println("<br />");
              
          }       
                    client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    //Serial.println("client disonnected");
  }
}

