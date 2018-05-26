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

  color startColor;
  color finishColor;

  boolean isSattled;

  void initDefaultData()
  {
    isSattled = false;

    goHome = false;

    hitCount = 0;

    polarity = 1;

    maxSpeed = 4;
    maxForce = 0.1;

    changeColor();

    acceleration = new PVector(0, 0);

    myRadious = random(10, 50);

    curPos = new PVector(random(0, myWidth), random(0, myHeight));
    orgPos = new PVector(width/2, height/2);

    createVelocity();
  }

  void createVelocity()
  {
    velocity = new PVector(random(-6, 6), random(-6, 6));
    orgVelocity = new PVector(velocity.x,velocity.y);
    
    freeMoveVelocity = new PVector(velocity.x,velocity.y);
    
    isSattled = false;
  }

  void changeColor()
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

  void applyForce(PVector force) 
  {
    acceleration.add(force);
  }

  void backHome()
  {
    PVector target;
    PVector steer;
    float dist;
    float scale;

    target = PVector.sub(orgPos, curPos);

    dist = target.mag();

    target.normalize();
    
    maxForce = map(curDist,300,900,0.9,0.0001);
    maxForce = constrain(maxForce,0.0001,0.9);
    
    if (dist < 10) 
    {
      scale = map(dist, 0, 100, 0.8, maxSpeed);

      target.mult(scale);

      isSattled = true;

      if (scale >= 0.5 && scale <= 2)
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

  void freeMove()
  {
    float tempPolarity;
    
    curPos.add(freeMoveVelocity);
    
    tempPolarity = random(-1, -1.1);

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

  void move()
  {
    float speedOffset;
    
    speedOffset = map(curDist,0,3000,0.8,2.5);
    
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

  void update(float data)
  {
    move();
  }
}
