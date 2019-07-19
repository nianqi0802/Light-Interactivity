




/*
Based on our teacher, Tom Igoe's DMX fader board example code.

*/


let video;
let poseNet;
let wlX = 0;  // left waist x position
let wlY = 0;  // left waist y position
let wrX = 0;  // right waist x position
let wrY = 0;  // right waist y position

let d = 0;


let song;
let amplitude;
let songlevel;

var url = '/set';								// the route to set a DMX channel in the server
var responseDiv;								// the div where the server response goes
var requestDiv;									// the div where the server response goes
var dmxAddress = 101;     		    // the light's starting address (0-indexed)

// channel definitions for an Elation ProSpot LED:
var ProSpot = {
	// red: 1,
	// green:2,
	// blue:3,
	// whole:4

	pan:1,
	tilt:3,
	colorWheel:5,
	rotatingGobo:7,
	fixedGobos:10,
	rotatingPrism:11,
	focus:12,
	zoom:14,
	frost:16,
	shutter:17,
	intensity:18,
	iris:19
};

var Source4Lustr = {		// Lustr in general HSI mode
	Hue: 1,
	HueFine: 2,
	Saturation: 3,
	Intensity: 4,
	Strobe: 5,
	Fan:6
};

var DesireD40 = {		// Lustr in general HSI mode
	Intensity: 1,
	Strobe: 2,
	Fan: 3
};

// choose the type of fixture you're controlling:
FixtureType = ProSpot;

function preload(){
	song = loadSound('MistyMountains.mp3');
}


function setup() {
	createCanvas(640, 480);
    video = createCapture(VIDEO);
    video.hide();
    poseNet = ml5.poseNet(video, modelReady);
    poseNet.on('pose', gotPoses);
	amplitude = new p5.Amplitude();



					// no canvas

}

function gotPoses(poses) {
  // console.log(poses);
  if (poses.length > 0) {
    let nX = poses[0].pose.keypoints[9].position.x;
    let nY = poses[0].pose.keypoints[9].position.y;
    let eX = poses[0].pose.keypoints[10].position.x;
    let eY = poses[0].pose.keypoints[10].position.y;
    wlX = lerp(wlX, nX, 0.3);
    wlY = lerp(wlY, nY, 0.3);
    wrX = lerp(wrX, eX, 0.3);
    wrY = lerp(wrY, eY, 0.3);
  }
}

function modelReady() {
  console.log('model ready');
}




function draw() {
  image(video, 0, 0);

// left and right
  level = map(wlX,0,640,155,190);
  var request = url + '/' + 101 + '/' + level;

  httpGet(request); // make HTTP call

// up and down
  level = map(wlY,0,480,80,10);
  var request = url + '/' + 103 + '/' + level;
  httpGet(request); // make HTTP call

//light
  var request = url + '/' + 113 + '/' + 255;
  httpGet(request); // make HTTP call




  songlevel = map(amplitude.getLevel(),0,0.1,50,255);
  console.log(songlevel);
  var request = url + '/' + 114 + '/' + songlevel;
  httpGet(request); // make HTTP call

  d = dist(wlX, wlY, wrX, wrY);

// color
  if(d<100){
	  //effect
	    var request = url + '/' + 105 + '/' + 230;
	    httpGet(request); // make HTTP call

  }
  else{
  	  var request = url + '/' + 105 + '/' + 0;
	  httpGet(request); // make HTTP call
  }




  fill(255, 0, 0);
  ellipse(wlX, wlY, 10);
  ellipse(wrX, wrY, 10);



}

function mousePressed(){
	song.setVolume(0.1);
    song.play();
}
