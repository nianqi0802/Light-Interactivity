#define one 11
#define two 10
#define three 6
#define four 5


int threshold = -0;

int firstValue = 0;
int firstValue_past = 0;

int firstBright = 0;



int secondValue = 0;
int secondValue_past = 0;

int secondBright = 0;



int thirdValue = 0;
int thirdValue_past = 0;

int thirdBright = 0;


int fourValue = 0;
int fourValue_past = 0;

int fourBright = 0;

void setup() {
  Serial.begin(9600);
  pinMode(one, OUTPUT);
  pinMode(two, OUTPUT);
  pinMode(three, OUTPUT);
  pinMode(four, OUTPUT);
}
void loop() {
  if (Serial.available()) {

    for (int i = 0; i < 200; i++) {


      String fromSerial = Serial.readStringUntil('\n');               // read until you see a \n
      int firstValueEnd = fromSerial.indexOf(',');                    // find the first comma and tell me how deep into the string it is
      String firstValueString = fromSerial.substring(0, firstValueEnd); // give me a new string that includes everything till the first comma
      int firstValue = firstValueString.toInt();                      // give me the int interpretation of that string
      int firstbright = map(firstValue, 0, 500, 50, 255);
      //      analogWrite(one, firstbright);

      if (firstValue > (firstValue_past + threshold)) {
        firstBright += 1;
        if (firstBright > 255) {
          firstBright = 255;
        }
      }

      else if (firstValue <= (firstValue_past - threshold)) {
        firstBright -= 1;
        if (firstBright < 0) {
          firstBright = 0;
        }
      }

      //int secondbright = map(secondValue,0,500,50,255);



      analogWrite(one, firstBright);



      int secondValueEnd = fromSerial.indexOf(',', firstValueEnd + 1);                  // search for the second comma, start searching after the first one
      String secondValueString = fromSerial.substring(firstValueEnd + 1, secondValueEnd); //give me a new string with everything beween first and second comma
      secondValue = secondValueString.toInt();                                      // give me the int interpretation of that string


      if (secondValue > (secondValue_past + threshold)) {
        secondBright += 1;
        if (secondBright > 255) {
          secondBright = 255;
        }
      }

      else if (secondValue <= (secondValue_past - threshold)) {
        secondBright -= 1;
        if (secondBright < 0) {
          secondBright = 0;
        }
      }

      //int secondbright = map(secondValue,0,500,50,255);



      analogWrite(two, secondBright);





      int thirdValueEnd = fromSerial.indexOf(',', secondValueEnd + 1);                  // search for the second comma, start searching after the first one
      String thirdValueString = fromSerial.substring(secondValueEnd + 1, thirdValueEnd); //give me a new string with everything beween first and second comma
      int thirdValue = thirdValueString.toInt();                                      // give me the int interpretation of that string
      int thirdbright = map(thirdValue, 0, 500, 50, 255);
      //      analogWrite(three, thirdbright);

      if (thirdValue > (thirdValue_past + threshold)) {
        thirdBright += 1;
        if (thirdBright > 255) {
          thirdBright = 255;
        }
      }
      if (thirdValue <= (thirdValue_past - threshold)) {
        thirdBright += 1;
        if (thirdBright < 0) {
          thirdBright = 0;
        }
      }

      //int secondbright = map(secondValue,0,500,50,255);



      analogWrite(three, secondBright);

      int fourValueEnd = fromSerial.indexOf(',', thirdValueEnd + 1);                  // search for the second comma, start searching after the first one
      String fourValueString = fromSerial.substring(thirdValueEnd + 1, fourValueEnd); //give me a new string with everything beween first and second comma
      int fourValue = fourValueString.toInt();                                      // give me the int interpretation of that string
      int fourbright = map(fourValue, 0, 500, 50, 255);
      //      analogWrite(four, fourbright);

      if (fourValue > (fourValue_past + threshold)) {
        fourBright += 1;
        if (fourBright > 255) {
          fourBright = 255;
        }
      }
      else if (fourValue <= (fourValue_past - threshold)) {
        fourBright -= 1;
        if (fourBright < 0) {
          fourBright = 0;
        }
      }

    }
    firstValue_past = firstValue;
    secondValue_past = secondValue;
    thirdValue_past = thirdValue;
    fourValue_past = fourValue;
  }
}
