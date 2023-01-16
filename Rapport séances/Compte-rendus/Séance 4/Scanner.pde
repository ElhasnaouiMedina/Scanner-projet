import processing.serial.*;
import java.io.FileWriter;
import java.util.Calendar;
import java.text.SimpleDateFormat;

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
  //Read Serial 
  String serialString = serial.readStringUntil('\n');
  if (serialString != null) {
    String[] coordinates = split(serialString, ' ');
    if (coordinates.length == 2) {
      pointList.add(new PVector(float(coordinates[0]), float(coordinates[1]), 50));
    }
  }
 
  // Draw the point cloud
  for (int index = 0; index < pointList.size(); index++) {
    PVector v = pointList.get(index);
    stroke(600-v.z, 600-v.y, 600-v.x);
    point(v.x, v.y, v.z);
  }
}

//efface les points ou sauvegarder le fichier
void keyReleased() {
  if (key =='x') {
    // effacer tous les points
    pointList.clear();
  } else if(key == 's'){
    //appelle la méthode pour enregistrer dans un fichier
    saveToFile();
  }
 
  
}

// enregistre le nuage de points dans le fichier Processing install 
void saveToFile(){
  String fileName = "./points_"+
        new SimpleDateFormat("yyMMdd_HHmmss").format(Calendar.getInstance().getTime())+".xyz";
  PrintWriter pw = null;
 
  try{
    pw = new PrintWriter(new FileWriter(fileName,true));
    for(int i=0;i<pointList.size();i++)
      pw.println((int)pointList.get(i).x + " " + 
                  (int)pointList.get(i).y + " " +
                  (int)pointList.get(i).z);
  }
  catch(Exception e){
  }
  finally {
    if(pw != null) pw.close();
  }
}
