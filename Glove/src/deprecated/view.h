// #ifndef VIEW_H
// #define VIEW_H
// #include <ESP8266WebServer.h>

// class View {
//   private:
//     ESP8266WebServer* server;

//   public:
//     View(ESP8266WebServer* webServer) {
//       server = webServer;
//     }


//  void renderHomePage() {
//     String html = "<html><body><h1>ESP Master</h1>";
//     html += "<form action=\"/setpattern\" method=\"get\">";
//     html += "Text for the vibration pattern<br>";
//     html += "<input type=\"text\" name=\"pattern\"><br><br>";
//     html += "<input type=\"submit\" value=\"Set Pattern\">";
//     html += "</form>";
//     html += "<button onclick=\"location.href='/start'\">Start Braille Sequence</button>";
//     html += "<p id=\"response\">response</p>"; // For displaying the response
    
//     html += "<script>";
    
//     html += "async function speakText(text) {";
//     html += "    return new Promise((resolve) => {";
//     html += "        let utterance = new SpeechSynthesisUtterance(text);";
//     html += "        utterance.onend = resolve;"; // Resolve when speech ends
//     html += "        window.speechSynthesis.speak(utterance);";
//     html += "    });";
//     html += "}";

//     // Function to make an AJAX request to the server to get the next character
//     html += "async function makeAjaxRequest() {";
//     html += "    var xhr = new XMLHttpRequest();";
//     html += "    xhr.onreadystatechange = async function() {";
//     html += "        if (xhr.readyState === 4 && xhr.status === 200) {";
//     html += "            var text = xhr.responseText;";
//     html += "            if (text) {";
//     html += "                document.getElementById('response').innerText = text;";
//     html += "                await speakText(text);";  // Speak the received text
//     html += "                await new Promise(resolve => setTimeout(resolve, 1000));";  // Optional delay
//     html += "                makeAjaxRequest();";  // Continue to request the next character
//     html += "            } else {";
//     html += "                console.log('Sequence complete, no more text to speak.');";
//     html += "            }";
//     html += "        }";
//     html += "    };";
//     html += "    xhr.open('GET', '/ajax', true);";  // Send request to the server to get the next character
//     html += "    xhr.send();";
//     html += "}";

//     html += "makeAjaxRequest();";  // Initial call to start the process

//     html += "</script>";
//     html += "</body></html>";

//     server->send(200, "text/html", html);
// }


// };

// #endif
