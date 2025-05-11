void web_server(){
  EthernetClient client = server.available();  // try to get client


  if (client) {  // got client?
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {   // client data available to read
        char c = client.read(); // read 1 byte (character) from client
        //buffer first part of HTTP request in HTTP_req array (string)
        //leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
        if (req_index < (REQ_BUF_SZ -1)){
          HTTP_req[req_index] = c;    //save HTTP request character
          req_index++;
        }
        // last line of client request is blank and ends with \n
        // respond to client only after last line received
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          //remainder of header follows below, depending on if
          //web page or XML page is requested
          //Ajax request - send XML file
          if(StrContains(HTTP_req, "ajax_inputs")){
            //send rest of HTTP header
            client.println("Content-Type: text/xml");
            client.println("Connection: keep-alive");
            client.println();
            //send XML file containing input states
            //Serial.println("XMP_RPM_MPH(client)");
            XML_RPM_MPH(client);
          }

          else {  //web page request
            //send rest of HTTP header
            client.println("Content-Type:text/html");
            client.println("Connection: close");
            client.println();
            //send web page
            Serial.println("Sending Index.htm");
            webFile = SD.open("index.htm");    //open web page file
            if(webFile){
              while(webFile.available()){
                client.write(webFile.read());  //send web page to client
              }
              webFile.close();
            }
            if (StrContains(HTTP_req, "justgage.js")){
              client.println("HTTP/1.1 200 OK"); //send javescript
              client.println("Content-Type: application/x-javascript");
              client.println(); 
              //send web page
              Serial.println("Sending justgage.js");
              justgage = SD.open("justgage.js");    //open web page file
              if(justgage){
                while(justgage.available()){
                  client.write(justgage.read());  //send web page to client
                }
                justgage.close();
              }
            }
            if (StrContains(HTTP_req, "raphael.js")){
              client.println("HTTP/1.1 200 OK"); //send javescript
              client.println("Content-Type: application/x-javascript");
              client.println(); 
              //send web page
              Serial.println("Sending raphael.js");
              client.write(SD.open("raphael.js"));
/*              
              raphael = SD.open("raphael.js");    //open web page file
              if(raphael){
                while(raphael.available()){
                  client.write(raphael.read());  //send web page to client
                }
                raphael.close();
              }
*/              
            }
          }
          // display received HTTP request on serial port
          //Serial.print("Received HTTP Request: ");
          Serial.println(HTTP_req);
          //reset buffer index and all buffer elements to 0
          req_index = 0;
          StrClear(HTTP_req, REQ_BUF_SZ);
          break;
        }
        // every line of text received from the client ends with \r\n
        if (c == '\n') {
          // last character on line of received text
          // starting new line with next character read
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // a text character was received from client
          currentLineIsBlank = false;
        }
      } // end if (client.available())
    } // end while (client.connected())
    delay(1);      // give the web browser time to receive the data
    client.stop(); // close the connection
  } // end if (client)
}

//send the XML file with switch statuses and analog value 
void XML_RPM_MPH(EthernetClient cl){
  //Serial.println("XML_RPM_MPH Begin");
  long newPositionL = encL.read();
  if(newPositionL != oldPositionL){
    oldPositionL = newPositionL;
  }

  long newPositionR = encR.read();
  if(newPositionR != oldPositionR){
    oldPositionR = newPositionR;
  }

  long rpmL = ((long)abs(newPositionL)*60)/(millis()-last);
  long rpmR = ((long)abs(newPositionR)*60)/(millis()-last);

  long mphL = (rpmL*960*float(3.14159)/63360);
  long mphR = (rpmR*960*float(3.14159)/63360);

  //Serial.println("XML file Begin");
  cl.print("<?xml version = \"1.0\" ?>");
  //Serial.print("   <?xml version = \"1.0\" ?>");
  cl.print("<inputs>");
  //Serial.print("   <inputs>");
  cl.print("<mphleft>");
  //Serial.print("   <mphleft>   ");
  cl.print(mphL);
  //Serial.print(mphL);
  cl.print("</mphleft>");
  //Serial.print("   </mphleft>");
  cl.print("<mphright>");
  //Serial.print("   <mphright>   ");
  cl.print(mphR);
  //Serial.print(mphR);
  cl.print("</mphright>");
  //Serial.print("   </mphright>");
  cl.print("</inputs>");
  //Serial.println("   </inputs>");
  //Serial.println("XML File finish");

  //Reset Encoder Count
  encL.write(0);
  encR.write(0);

  //Sets millis count to previous count to etermine difference
  last = millis();
}

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
  for (int i = 0; i < length; i++) {
    str[i] = 0;
  }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
  char found = 0;
  char index = 0;
  char len;

  len = strlen(str);

  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    }
    else {
      found = 0;
    }
    index++;
  }

  return 0;
}











