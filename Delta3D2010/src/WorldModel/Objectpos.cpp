
#include "WorldModel.h"

#include "../Behavior/BhvBasicStandup.h"
#include <assert.h>


/*******************************************Polar Ball Position*****************************************/

VisionSense WorldModel::getPolarBallPos()
{
  if( 10 <=  getConfidence(mObjectToSenseMap[BALL] ) )
   {
    //EVisionObject      tmpball;
    v.theta=sinDeg(mObjectToSenseMap[BALL].theta)*sinDeg(90-mObjectToSenseMap[BALL].phi);
    v.theta=asinDeg(v.theta);
    v.theta+=getHJoint(JID_HEAD_1).angle;
    v.distance=sqrt(abs(pow(mObjectToSenseMap[BALL].distance,2)-pow(.45,2)));//A distance
    }
   return v;
 }
 
/*******************************************Ball Position**********************************************/ 
void WorldModel::setBallPos ()
{
   
  if( 10 <=  getConfidence(mObjectToSenseMap[BALL] ) )
   {
    EVisionObject      tmpball;
    double balltheta;
    tmpball=EVisionObject(BALL);
    mBallTheta=sinDeg(mObjectToSenseMap[BALL].theta)*sinDeg(90-mObjectToSenseMap[BALL].phi);
    mBallTheta=asinDeg(mBallTheta);
    mBallTheta+=getHJoint(JID_HEAD_1).angle;// theta khodet ta tup
    mBallDistance=sqrt(abs(pow(mObjectToSenseMap[tmpball].distance,2)-pow(.45,2)));//A distance
    balltheta=mBallTheta+z;
    mBallPos.x()=cosDeg(balltheta)*mBallDistance;
    mBallPos.y()=sinDeg(balltheta)*mBallDistance;
    mBallPos.z()=balltheta;// theta nesbat be markaze zamin
    mBallPos=Vector3f( mBallPos.x()+getMyPos().x(),
                  mBallPos.y()+getMyPos().y(),
                  mBallPos.z()
                );
    if ((abs(mConstBallPos.x() - mBallPos.x()) > 0.10) && ((abs(mConstBallPos.y() - mBallPos.y()) > 0.10)))
      mConstBallPos = mBallPos;
      
    cout<<"  ball x###"<<mBallPos.x()<<"  ball y###"<<mBallPos.y()<<"  ball z###"<<mBallPos.z()<< "  tmpdistance###"<<mBallDistance<<std::endl;
    }
}

Vector3f WorldModel::getConstBallPos() const
{
  return mConstBallPos;
}

/** calculate all object real position
    must call after normalize
**/

void WorldModel::calcVisionObjectRealPos()
{
  for (int i = (int)(BALL); i < (int)(OPPONENT_11); ++i)
  {
    VisionSense & vs = mObjectToSenseMap[static_cast<EVisionObject>(i)];
    double theta=0,distance=0,phi=0,tmpX,tmpY,tmpZ;
    if(10<= getConfidence(vs))
    {
      theta = sinDeg(vs.theta)*sinDeg(90-vs.phi);/// sin(theta)*sin(phi)
      theta = asinDeg(theta);
      theta += getHJoint(JID1_HEAD_1).angle;
      distance =sqrt(abs(pow(vs.distance,2)-pow(0.45,2)));//A distance
      theta =theta + z;
      phi = vs.phi + getHJoint(JID_HEAD_2).angle;
      tmpX = cosDeg(theta)*distance;
      tmpY = sinDeg(theta)*distance;      
      tmpZ = NaoHeaght + sinDeg(phi)*distance;// theta nesbat be markaze zamin      
      vs.realPos = Vector3f(tmpX + getMyPos().x(),tmpY+getMyPos().y(),tmpZ);  
      std::cout<<"phi ="<<  vs.phi <<"+"<< getHJoint(JID_HEAD_2).angle<<std::endl;
      std::cout<<"object ("<<i<<").realpos ="<<vs.realPos<<std::endl;      
    }

  }
	
}