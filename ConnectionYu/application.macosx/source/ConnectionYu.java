import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import geomerative.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class ConnectionYu extends PApplet {




RFont f;
RShape grp;
RPoint[] points;

PFont font;

long lastMillis;

float scaleX;
float scaleY;
float distOffSet;

int SATTLE_TIME = 10000;
int OBJECT_COUNT = 400;
int DISTANCE = 100;
int SEC_10 = 10000;

int centerPosX;
int centerPosY;
int myWidth;
int myHeight;
int sattleCount;
int distPolarity;

boolean drawByGrayColor;
boolean goHome;
boolean goHomeStarted;

ArrayList<JLObject> objList;
String[] textLines;

String Seperator = ",";
String myID = "p10/";
String tokenAll = myID+"*";
String tokenTemp = myID+"tmp";
String tokenDist = myID+"dst";
String tokenGyro = myID+"gyr";
String tokenHumidity = myID+"hum";
String name;

float curTemp;
float curDist;
float curHumidity;

float []curGyro;

public void setup()
{
  

  //size(1024, 768, P2D);

  noCursor();

  myWidth = width;
  myHeight = height;

  centerPosX = (myWidth/2);
  centerPosY = (myHeight/2)+ (height/12);

  background(0);

  

  strokeWeight(0.5f);

  stroke(0);

  RG.init(this);
  
  name = "VK18";
  
  grp = RG.getText(name, "font1.ttf", 200, CENTER);

  textLines = loadStrings("text.txt");

  if (textLines != null)
  {
    if (textLines.length > 0)
    {
      println(textLines[0]);
      
      grp = RG.getText(textLines[0], "font1.ttf", 200, CENTER);
      
      name = textLines[0];
    } 
  }

  initTypo();

  println("System ready!");
}

public void initObjects()
{
  curDist = 2000;

  distPolarity = 1;

  goHome = false;

  drawByGrayColor = true;

  objList = new ArrayList<JLObject>();

  for (int i=0; i<OBJECT_COUNT; i++)
  {
    objList.add(new JLObject());
  }

  //keyPressed();
}

public void initTypo()
{
  JLObject srcObj;

  scaleX = 2;
  scaleY = 2;

  distOffSet = 0;

  font = loadFont("ITCAvantGardePro-XLt-12.vlw");

  textFont(font, 13);

  RG.setPolygonizer(RG.ADAPTATIVE);
  RG.setPolygonizer(RG.UNIFORMLENGTH);
  RG.setPolygonizerLength(7);

  points = grp.getPoints();

  OBJECT_COUNT = points.length;

  initObjects();

  for (int i=0; i<OBJECT_COUNT; i++)
  {
    srcObj = (JLObject) objList.get(i);

    srcObj.orgPos.set(centerPosX + points[i].x*scaleX, centerPosY +  points[i].y*scaleY);
  }
}

public void runObjects()
{
  float tempDist;
  JLObject srcObj;
  JLObject destObj;

  tempDist = 0;

  sattleCount = 0;

  for (int i=0; i<OBJECT_COUNT; i++)
  {
    srcObj = (JLObject) objList.get(i);

    srcObj.hitCount = 0;

    srcObj.update(curDist);

    for (int j=i; j<OBJECT_COUNT; j++)
    {
      destObj = (JLObject) objList.get(j);

      tempDist = dist(srcObj.curPos.x, srcObj.curPos.y, destObj.curPos.x, destObj.curPos.y);

      if (tempDist <= (DISTANCE+distOffSet))
      {
        line(srcObj.curPos.x, srcObj.curPos.y, destObj.curPos.x, destObj.curPos.y);
      }
    }
  }
}

public void changeColor()
{
  JLObject srcObj;

  for (int i=0; i<OBJECT_COUNT; i++)
  {
    srcObj = (JLObject) objList.get(i);

    srcObj.changeColor();
  }
}

public void checkSattle()
{
  long timeDiff;
  float textAlpha;

  textAlpha = 0;

  timeDiff = (millis() - lastMillis);

  DISTANCE = (int)map(timeDiff, 0, SATTLE_TIME, 200, 0);
  DISTANCE = constrain(DISTANCE, 20, 100);
}

public void goHome()
{
  JLObject srcObj;

  goHomeStarted = true;

  sattleCount = 0;

  if (goHome == false)
  {
    for (int i=0; i<OBJECT_COUNT; i++)
    {
      srcObj = (JLObject) objList.get(i);

      srcObj.createVelocity();
    }

    DISTANCE = 100;
  } else
  {
    lastMillis = millis();
  }
}

public void checkGoHome()
{
  if (curDist > 1400)
  {
    goHome = false;

    distOffSet = 0;

    if (goHomeStarted == true)
    {
      goHome();

      drawByGrayColor = true;

      changeColor();

      goHomeStarted = false;
    }
  } else
  {
    goHome = true;

    distOffSet = map(curDist, 0, 600, 0, 60);

    if (goHomeStarted == false)
    {
      goHome();

      drawByGrayColor = false;

      changeColor();
    }
  }
}

public void draw()
{
  fill(0, 15);

  noStroke();

  rect(0, 0, myWidth, myHeight);

  runObjects();

  checkGoHome();

  if (goHome == true)
  {
    checkSattle();
  }

  curDist += (4.0f * distPolarity);

  if (curDist <=0)
  {
    curDist = 0;
  }
  
  if (curDist >= 4000)
  {
    curDist = 4000;
  }
}


public void keyPressed()
{
  drawByGrayColor = !drawByGrayColor;

  changeColor();
}

public void mousePressed()
{
  curDist = 900;

  distPolarity = -1;
}

public void mouseReleased()
{  
  curDist = 2000;

  distPolarity = 2;
}
// this is JLObect represents a human


public class JLObject
{
  PVector orgPos;
  PVector curPos;
  float myRadious;
  PVector velocity;
  PVector orgVelocity;
  PVector freeMoveVelocity;
  PVector acceleration;
  float halfRadious;
  float checkWidth;
  float checkHeight;
  float normalPosition;
  float polarity;
  float maxForce;
  float maxSpeed;

  int hitCount;

  int startColor;
  int finishColor;

  boolean isSattled;

  public void initDefaultData()
  {
    isSattled = false;

    goHome = false;

    hitCount = 0;

    polarity = 1;

    maxSpeed = 4;
    maxForce = 0.1f;

    changeColor();

    acceleration = new PVector(0, 0);

    myRadious = random(10, 50);

    curPos = new PVector(random(0, myWidth), random(0, myHeight));
    orgPos = new PVector(width/2, height/2);

    createVelocity();
  }

  public void createVelocity()
  {
    velocity = new PVector(random(-6, 6), random(-6, 6));
    orgVelocity = new PVector(velocity.x,velocity.y);
    
    freeMoveVelocity = new PVector(velocity.x,velocity.y);
    
    isSattled = false;
  }

  public void changeColor()
  {
    if (drawByGrayColor == true)
    {
      startColor  = color(255);
      finishColor = color(128);
    } else
    {
      startColor = color(17, 67, 240);
      finishColor = color(217, 17, 240);
    }
  }

  public void applyForce(PVector force) 
  {
    acceleration.add(force);
  }

  public void backHome()
  {
    PVector target;
    PVector steer;
    float dist;
    float scale;

    target = PVector.sub(orgPos, curPos);

    dist = target.mag();

    target.normalize();
    
    maxForce = map(curDist,300,900,0.9f,0.0001f);
    maxForce = constrain(maxForce,0.0001f,0.9f);
    
    if (dist < 10) 
    {
      scale = map(dist, 0, 100, 0.8f, maxSpeed);

      target.mult(scale);

      isSattled = true;

      if (scale >= 0.5f && scale <= 2)
      {
        isSattled = true;
      }
    } else 
    {
      target.mult(maxSpeed);
    }
    
    target.mult(maxSpeed);

    steer = PVector.sub(target, velocity);

    steer.limit(maxForce); 
    applyForce(steer);

    velocity.add(acceleration);
    velocity.limit(maxSpeed);
    curPos.add(velocity);

    acceleration.mult(0);
  }

  public void freeMove()
  {
    float tempPolarity;
    
    curPos.add(freeMoveVelocity);
    
    tempPolarity = random(-1, -1.1f);

    if (curPos.x >= myWidth || curPos.x <= 0)
    {
      freeMoveVelocity.x *= tempPolarity;
      orgVelocity.x *= tempPolarity;
    }

    if (curPos.y  >= myHeight || curPos.y <= 0)
    {
      freeMoveVelocity.y *= tempPolarity;
      orgVelocity.y *= tempPolarity;
    }
  }

  public void move()
  {
    float speedOffset;
    
    speedOffset = map(curDist,0,3000,0.8f,2.5f);
    
    freeMoveVelocity.set(orgVelocity.x/speedOffset , orgVelocity.y/speedOffset);

    if (goHome == true)
    {
      backHome();
    } else
    {
      freeMove();
    }

    normalPosition = map(curPos.x, 0, width, 0, 1);

    stroke(lerpColor(startColor, finishColor, normalPosition),50);
    fill(lerpColor(startColor, finishColor, normalPosition),50);

    if (goHome == true)
    {
      ellipse(curPos.x, curPos.y, 4, 4);
    }
  }

  JLObject()
  {
    initDefaultData();
  }

  public void update(float data)
  {
    move();
  }
}
  public void settings() {  fullScreen(P2D);  smooth(); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "--present", "--window-color=#000000", "--hide-stop", "ConnectionYu" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
