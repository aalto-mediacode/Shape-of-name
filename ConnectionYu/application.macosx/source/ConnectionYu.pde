import geomerative.*;


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

void setup()
{
  fullScreen(P2D);

  //size(1024, 768, P2D);

  noCursor();

  myWidth = width;
  myHeight = height;

  centerPosX = (myWidth/2);
  centerPosY = (myHeight/2)+ (height/12);

  background(0);

  smooth();

  strokeWeight(0.5);

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

void initObjects()
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

void initTypo()
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

void runObjects()
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

void changeColor()
{
  JLObject srcObj;

  for (int i=0; i<OBJECT_COUNT; i++)
  {
    srcObj = (JLObject) objList.get(i);

    srcObj.changeColor();
  }
}

void checkSattle()
{
  long timeDiff;
  float textAlpha;

  textAlpha = 0;

  timeDiff = (millis() - lastMillis);

  DISTANCE = (int)map(timeDiff, 0, SATTLE_TIME, 200, 0);
  DISTANCE = constrain(DISTANCE, 20, 100);
}

void goHome()
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

void checkGoHome()
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

void draw()
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

  curDist += (4.0 * distPolarity);

  if (curDist <=0)
  {
    curDist = 0;
  }
  
  if (curDist >= 4000)
  {
    curDist = 4000;
  }
}


void keyPressed()
{
  drawByGrayColor = !drawByGrayColor;

  changeColor();
}

void mousePressed()
{
  curDist = 900;

  distPolarity = -1;
}

void mouseReleased()
{  
  curDist = 2000;

  distPolarity = 2;
}
