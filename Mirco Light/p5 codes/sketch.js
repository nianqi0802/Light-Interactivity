var serial; // variable to hold an instance of the serialport library
var fromSerial = 0; //variable to hold the data


var colors;
var capture;
var trackingData;

var zone_one =0;
var zone_two =0;
var zone_three = 0;
var zone_four =0;

function setup() {
  createCanvas(windowWidth,windowHeight);

  serial = new p5.SerialPort(); // make a new instance of  serialport librar
  serial.on('list', printList); // callback function for serialport list event
  serial.on('data', serialEvent); // callback for new data coming in
  serial.list(); // list the serial ports
  serial.open("/dev/cu.usbmodem143401"); // open a port

  capture = createCapture(VIDEO); //capture the webcam
  capture.position(0,0) //move the capture to the top left
  capture.style('opacity',0.5)// use this to hide the capture later on (change to 0 to hide)...
  capture.id("myVideo"); //give the capture an ID so we can use it in the tracker below.

  tracking.ColorTracker.registerColor('green', function(r, g, b) {
  if (2*g > (r+b+10) && g<150) {
    return true;
  }
  return false;
});

  colors = new tracking.ColorTracker(['green']);
  tracking.track('#myVideo', colors); // start the tracking of the colors above on the camera in p5


  //start detecting the tracking
  colors.on('track', function(event) { //this happens each time the tracking happens
      trackingData = event.data // break the trackingjs data into a global so we can access it with p5
  });

}

function draw() {

  // console.log(trackingData);
  if(trackingData){ //if there is tracking data to look at, then...
    for (var i = 0; i < trackingData.length; i++) { //loop through each of the detected colors
      // console.log( trackingData[i] )
      if(trackingData[i].width*trackingData[i].height>10000){
      rect(trackingData[i].x,trackingData[i].y,trackingData[i].width,trackingData[i].height)
      // console.log(mouseY);


      if((trackingData[i].x + (trackingData[i].width)/2)>320 && (trackingData[i].y + (trackingData[i].height)/2)< 240){
          zone_one += int(Math.sqrt(trackingData[i].width*trackingData[i].width+trackingData[i].height*trackingData[i].height));
      }
      if((trackingData[i].x + (trackingData[i].width)/2)<320 && (trackingData[i].y + (trackingData[i].height)/2)< 240){
          zone_two += int(Math.sqrt(trackingData[i].width*trackingData[i].width+trackingData[i].height*trackingData[i].height));
      }
      if((trackingData[i].x + (trackingData[i].width)/2)<320 && (trackingData[i].y + (trackingData[i].height)/2)> 240){
          zone_three += int(Math.sqrt(trackingData[i].width*trackingData[i].width+trackingData[i].height*trackingData[i].height));
      }
      if((trackingData[i].x + (trackingData[i].width)/2)>320 && (trackingData[i].y + (trackingData[i].height)/2)> 240){
          zone_four += int(Math.sqrt(trackingData[i].width*trackingData[i].width+trackingData[i].height*trackingData[i].height));
      }
      Math.sqrt(trackingData[i].width*trackingData[i].width+trackingData[i].height*trackingData[i].height);
    }
}
    // console.log("zone_one"+zone_one);
    // console.log("zone_two"+zone_two);
    // console.log("zone_three"+zone_three);
    // console.log("zone_four"+zone_four);

    fill(0,85,0);
    rect(0,480,640,50);
    fill(255);
    text("zone_one"+zone_one,320,500);
    text("zone_two"+zone_two,10,500);
    text("zone_three"+zone_three,10,510);
    text("zone_four"+zone_four,320,510);

    serial.write(constrain(zone_one,0,500) + ","); // this makes it a string and adds a comma
    serial.write(constrain(zone_two,0,500) +","); // this makes it a string and adds a comma
    serial.write(constrain(zone_three,0,500) +","); // this makes it a string and adds a comma
    serial.write(constrain(zone_four,0,500) +","); // this makes it a string and adds a comma
    serial.write("\n" ); 								// this adds a linefeed in end (ascii 10)

    zone_one = 0;
    zone_two = 0;
    zone_three = 0;
    zone_four = 0;
  }
}

function printList(portList) {
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    println(i + " " + portList[i]);
  }
}

function serialEvent() {
  // this is called when data is recieved
}
