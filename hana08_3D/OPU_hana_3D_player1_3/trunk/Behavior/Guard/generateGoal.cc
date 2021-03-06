#include "guard.ih"

rf<Behavior::Goal> Guard::generateGoal(unsigned step, unsigned slot)
{
  rf<Goal> goal = new Goal();
  rf<OrNode> dis = goal->addDisjunct();
  rf<AndNode> con = dis->addConjunct();
  

  WorldModel& wm = WorldModel::getInstance();

  Vector3D ballPos;
  Vector3D goalPos;
  Vector3D targetPos;
  ballPos = wm.getObjectPosition(Types::BALL).getMu();
  goalPos = ( wm.getObjectPosition(Types::GOAL1US).getMu() +
	      wm.getObjectPosition(Types::GOAL2US).getMu() ) / 2;
  targetPos = (ballPos + goalPos) / 2;

  Vector3D goalToTarget = targetPos - goalPos;
  Vector3D goalToBall = ballPos - goalPos;

  if( goalToBall.length() >= 0.8)
  {
      goalToTarget = goalToTarget * (0.8 / goalToTarget.length());
      targetPos = goalToTarget + goalPos;
  }

  targetPos.setZ(0);
  
  switch (step)
  {
      case 0: 
      case 1:

	  con->addVar("TPos", targetPos);

	  break;
      default:
	  break;
  }

  return goal;
}
