import processing.serial.*;

Serial serial;

ArrayList<PVector> pointList;

final int SERIAL_SPEED = 115200;

void setup() {
  size(800, 640, P3D);
  colorMode(RGB, 255, 255, 255);
  pointList = new ArrayList<PVector>();
  
  
  // Serial Port 
  serial = new Serial(this, Serial.list()[0], SERIAL_SPEED);
}

void draw() {
  perspective();
  background(33);
  //Read Serial Port
  String serialString = serial.readStringUntil('\n');
  if (serialString != null) {
    String[] coordinates = split(serialString, ' ');
    if (coordinates.length == 1) {
      pointList.add(new PVector(float(coordinates[0]), 50, 50));
    }
  }
 
  // Draw the actual point cloud
  for (int index = 0; index < pointList.size(); index++) {
    PVector v = pointList.get(index);
    stroke(255-v.z, 255-v.y, 255-v.x);
    point(v.x, v.y, v.z);
  }
}
