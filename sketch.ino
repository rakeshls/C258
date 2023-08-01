#include <ezButton.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//  button objects
ezButton button1(13);
ezButton button2(33);
ezButton button3(14);
ezButton button4(27);
ezButton button5(26);

int vote1 = 0, vote2 = 0, vote3 = 0, vote4 = 0;

int buttonState = 0;

int voting_completed = 0;

void setup()
{
  Serial.begin(9600);

  button1.setDebounceTime(25);
  button2.setDebounceTime(25);
  button3.setDebounceTime(25);
  button4.setDebounceTime(25);
  button5.setDebounceTime(25);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  };

  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.clearDisplay();

  oled.setCursor(2, 5);       // set position to display
  oled.println("Start voting.."); // set text
  oled.setCursor(2, 15);       // set position to display
  oled.println("A - Green ");
  oled.setCursor(2, 25);       // set position to display
  oled.println("B - Yellow");
  oled.setCursor(2, 35);       // set position to display
  oled.println("C - Red");     // display on OLED
  oled.setCursor(2, 45);       // set position to display
  oled.println("D - White");

  oled.display();              // display on OLED

  Serial.println("Result will be shown after the black button is pressed!");
}

void loop() {

  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();

  if (voting_completed == 0) {
    if (button1.isPressed()) {
      vote1++;
    }
    else if (button2.isPressed()) {
      vote2++;
    }
    else if (button3.isPressed()) {
      vote3++;
    }
    else if (button4.isPressed()) {
      vote4++;
    }
    else if (button5.isPressed()) {
      voting_completed = 1;
      vote_count();
      delay(2000);
      Serial.println("voting completed");
    }
  } else {
    determine_winner();
  }
  delay(10);
}

void vote_count() {
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);

  oled.setCursor(1, 0);
  oled.print("A  B  C  D");

  oled.setCursor(1, 20);
  oled.print(vote1);

  oled.setCursor(35, 20);
  oled.print(vote2);

  oled.setCursor(65, 20);
  oled.print(vote3);

  oled.setCursor(100, 20);
  oled.print(vote4);

  oled.display();

}

void determine_winner() {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(1, 10);

  if ((vote1 > vote2 && vote1 > vote3 && vote1 > vote4))
    oled.print("A is the winner");
  else if (vote2 > vote1 && vote2 > vote3 && vote2 > vote4)
    oled.print("B is the winner");
  else if (vote3 > vote1 && vote3 > vote2 && vote3 > vote4)
    oled.print("C is the winner");
  else if(vote4 > vote1 && vote4 > vote2 && vote4 > vote3)
    oled.print("D is the winner");
  else 
    oled.print("There was a tie. Vote again!");

  oled.display();
}